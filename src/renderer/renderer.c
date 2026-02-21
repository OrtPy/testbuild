#include "ef2/renderer.h"
#include "ef2/program.h"
#include "ef2/buffer.h"
#include "ef2/texture.h"
#include "ef2/shaderfile.h"
#include "ef2/meshgen.h"
#include "ef2/theme.h"
#include "ef2/timeutil.h"
#include "ef2/curve_offsets.h"
#include "ef2/rendererdata.h"
#include "ef2/gles.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>

// Match ref binary: uses double-precision libm entry points (cos/fmod/floor/ceil) and avoids sinf/cosf imports.
#define EF2_PI 3.14159265358979323846
static inline float ef2_cos_f(float x) { return (float)cos((double)x); }
static inline float ef2_sin_f(float x) { return (float)cos((double)x - EF2_PI * 0.5); }
static inline float ef2_sqrt_f(float x)
{
#if defined(__arm__) && (defined(__ARM_FP) || defined(__VFP_FP__))
  // Force hardware sqrt without pulling in libm sqrtf symbol (ref has no sqrt/sqrtf imports).
  float out;
  __asm__ volatile ("vsqrt.f32 %0, %1" : "=t"(out) : "t"(x));
  return out;
#else
  return __builtin_sqrtf(x);
#endif
}

// Local helpers (forward declarations; defined near bottom of file).
static inline uint8_t ef2__read_u8(const void* base, size_t off);
static inline double ef2__read_f64(const void* base, size_t off);


// ---- internal renderer side-car runtime ----

typedef struct ef2_RendererResources {
  ef2_Program prog_background;
  ef2_Program prog_line;
  ef2_Texture tex_noise;
  ef2_Texture tex_bg;
  ef2_Buffer  meshA_vb;
  ef2_Buffer  meshA_ib;
  ef2_Buffer  meshB_vb;
  ef2_Buffer  meshB_ib;
  int built;
} ef2_RendererResources;

typedef struct ef2_RendererRuntime {
  ef2_AAssetManager* mgr;
  int resources_dirty;
  int is_initialized;
  int screen_w;
  int screen_h;
  ef2_RendererResources res;
  Curve curve; // backing Curve instance; public renderer stores Curve* at +0x5c
  uint8_t curve_dump_pad[8]; // ensure safe 0x180 dump like allocator-rounded original
} ef2_RendererRuntime;

typedef struct ef2_RendererRtEntry {
  ef2_Renderer* owner;
  ef2_RendererRuntime* rt;
} ef2_RendererRtEntry;

static ef2_RendererRtEntry* g_renderer_rt_entries = NULL;
static size_t g_renderer_rt_count = 0;
static size_t g_renderer_rt_cap = 0;

static ef2_RendererRuntime* ef2__renderer_rt(ef2_Renderer* self)
{
  if (!self) return NULL;
  size_t i;
  for (i = 0; i < g_renderer_rt_count; ++i) {
    if (g_renderer_rt_entries[i].owner == self) return g_renderer_rt_entries[i].rt;
  }
  return NULL;
}

static void ef2__renderer_set_rt(ef2_Renderer* self, ef2_RendererRuntime* rt)
{
  if (!self) return;

  {
    size_t i;
    for (i = 0; i < g_renderer_rt_count; ++i) {
    if (g_renderer_rt_entries[i].owner == self) {
      g_renderer_rt_entries[i].rt = rt;
      return;
    }
    }
  }

  if (g_renderer_rt_count == g_renderer_rt_cap) {
    size_t new_cap = (g_renderer_rt_cap == 0) ? 8 : (g_renderer_rt_cap * 2);
    ef2_RendererRtEntry* p = (ef2_RendererRtEntry*)realloc(g_renderer_rt_entries, new_cap * sizeof(*p));
    if (!p) return;
    g_renderer_rt_entries = p;
    g_renderer_rt_cap = new_cap;
  }

  g_renderer_rt_entries[g_renderer_rt_count].owner = self;
  g_renderer_rt_entries[g_renderer_rt_count].rt = rt;
  g_renderer_rt_count++;
}

static ef2_RendererRuntime* ef2__renderer_detach_rt(ef2_Renderer* self)
{
  if (!self) return NULL;
  {
    size_t i;
    for (i = 0; i < g_renderer_rt_count; ++i) {
    if (g_renderer_rt_entries[i].owner == self) {
      ef2_RendererRuntime* rt = g_renderer_rt_entries[i].rt;
      g_renderer_rt_entries[i] = g_renderer_rt_entries[g_renderer_rt_count - 1];
      g_renderer_rt_count--;
      return rt;
    }
    }
  }
  return NULL;
}

static void ef2__renderer_set_curve_ptr(ef2_Renderer* self, Curve* curve_ptr)
{
  if (!self) return;
  // Store Curve* at raw+0x5c (no strict-aliasing UB).
  memcpy(&self->raw[EF2_R_CURVE_PTR], &curve_ptr, sizeof(curve_ptr));
}

static Curve* ef2__renderer_get_curve_ptr(ef2_Renderer* self)
{
  if (!self) return NULL;
  Curve* c = NULL;
  memcpy(&c, &self->raw[EF2_R_CURVE_PTR], sizeof(c));
  return c;
}


#if EF2_PLATFORM_ANDROID
#include <android/log.h>
#endif

#if EF2_PLATFORM_ANDROID && EF2_USE_REAL_GLES
#include <GLES2/gl2.h>


#endif
#if EF2_PLATFORM_ANDROID && EF2_USE_REAL_GLES
// --- GLES2 draw path (real rendering) ---



static void ef2__renderer_draw_mesh(ef2_Program* prog, const ef2_Buffer* vb, const ef2_Buffer* ib, const char* tag)
{
  if (!prog || prog->id == 0 || !vb || vb->id == 0 || !ib || ib->id == 0) {
    ef2_log_print(ANDROID_LOG_WARN, "lwplocal", "draw(%s): missing program/buffer (prog=%u vb=%u ib=%u)",
                  tag ? tag : "?", (unsigned)(prog ? prog->id : 0u), (unsigned)(vb ? vb->id : 0u), (unsigned)(ib ? ib->id : 0u));
    return;
  }

  GLint a_linedata = ef2_Program_getAttribLocation(prog, "linedata");
  if (a_linedata < 0) {
    ef2_log_print(ANDROID_LOG_WARN, "lwplocal", "draw(%s): attrib 'linedata' not found", tag ? tag : "?");
    return;
  }

  glBindBuffer(GL_ARRAY_BUFFER, vb->id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id);
  glEnableVertexAttribArray((GLuint)a_linedata);
  glVertexAttribPointer((GLuint)a_linedata, 2, GL_FLOAT, GL_FALSE, 2 * (GLsizei)sizeof(float), (const void*)0);

  const GLsizei index_count = (GLsizei)(ib->size / sizeof(uint16_t));
  glDrawElements(GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_SHORT, (const void*)0);
}


// Minimal MT19937 (matches std::mersenne_twister_engine<uint32_t, ...> usage in decomp).
typedef struct ef2_mt19937 {
  uint32_t mt[624];
  int idx;
} ef2_mt19937;

static void ef2__mt_seed(ef2_mt19937* s, uint32_t seed)
{
  if (!s) return;
  s->mt[0] = seed;
  {
    int i;
    for (i = 1; i < 624; ++i) {
    uint32_t x = s->mt[i - 1] ^ (s->mt[i - 1] >> 30);
    s->mt[i] = (uint32_t)(1812433253u * x + (uint32_t)i);
    }
  }
  s->idx = 624;
}

static uint32_t ef2__mt_next_u32(ef2_mt19937* s)
{
  if (!s) return 0;
  if (s->idx >= 624) {
    // twist
    int i;
    for (i = 0; i < 624; ++i) {
      uint32_t y = (s->mt[i] & 0x80000000u) | (s->mt[(i + 1) % 624] & 0x7fffffffu);
      uint32_t x = s->mt[(i + 397) % 624] ^ (y >> 1);
      if (y & 1u) x ^= 0x9908B0DFu;
      s->mt[i] = x;
    }
    s->idx = 0;
  }
  uint32_t y = s->mt[s->idx++];
  // temper
  y ^= (y >> 11);
  y ^= (y << 7) & 0x9d2c5680u;
  y ^= (y << 15) & 0xefc60000u;
  y ^= (y >> 18);
  return y;
}

static void ef2__renderer_render_gles(ef2_RendererRuntime* rt)
{
  if (!rt) return;
  ef2_RendererResources* res = &rt->res;
  if (!res->built) return;

  const int screen_w = rt->screen_w;
  const int screen_h = rt->screen_h;
  if (screen_w <= 0 || screen_h <= 0) return;

  glViewport(0, 0, screen_w, screen_h);
  // Bind textures (noise=unit0, bg=unit1) to match decomp.
  glActiveTexture(GL_TEXTURE0);
  ef2_Texture_bind(&res->tex_noise, 0);
  glActiveTexture(GL_TEXTURE1);
  ef2_Texture_bind(&res->tex_bg, 1);

  // Background pass (no blending).
  glDisable(GL_BLEND);
  ef2_Program_use(&res->prog_background);
  ef2_Program_setUniform1i(&res->prog_background, "noise", 0);
  ef2_Program_setUniform1i(&res->prog_background, "bg", 1);
  ef2_Buffer_bindArray(&res->meshA_vb);
  ef2_Buffer_bindElement(&res->meshA_ib);
  ef2_Program_enableAttrib(&res->prog_background, "linedata", 2, GL_FLOAT, GL_FALSE, (GLsizei)(2 * sizeof(float)), (const void*)0);
  ef2_Program_applyUniforms(&res->prog_background);

  // meshA indices count: rows=2, cols=1 -> 2*2*(1+2)-2 = 10
  glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_SHORT, 0);

  // Line pass (blended).
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  ef2_Program_use(&res->prog_line);
  ef2_Program_setUniform1i(&res->prog_line, "noise", 0);
  ef2_Program_setUniform1i(&res->prog_line, "bg", 1);
  ef2_Buffer_bindArray(&res->meshB_vb);
  ef2_Buffer_bindElement(&res->meshB_ib);
  ef2_Program_enableAttrib(&res->prog_line, "linedata", 2, GL_FLOAT, GL_FALSE, (GLsizei)(2 * sizeof(float)), (const void*)0);

  // Pull live touch delta from CurveClient to mirror decomp's integer quantization.
  const void* cc = (const void*)rt->curve.client_0x8;
  const int touch_active = (ef2__read_u8(cc, EF2_CC_TOUCH_ACTIVE) != 0);
  const double dy = ef2__read_f64(cc, EF2_CC_DY);
  const float v126 = touch_active ? (float)dy : 0.0f;

  // Quantized magnitudes (decomp uses int(v126*0.1) and int(v126*0.025)).
  const float v49 = (float)abs((int)(v126 * 0.025f));  // l1m.y
  const float v52 = (float)abs((int)(v126 * 0.1f));    // l1m.x
  const float v53 = 1.0f / (v49 + 1.0f);

  // curveWidthRange is scaled by v53 in decomp.
  ef2_theme_parameter tw = {0};
  if (ef2_Curve_themeGet(&rt->curve, "curveWidthRange", &tw)) {
    ef2_Program_setUniform2f(&res->prog_line, "curveWidthRange", tw.v0 * v53, tw.v1 * v53);
  }
  ef2_Program_setUniform2f(&res->prog_line, "l1m", v52, v49);

  int lineCount = 4;
  ef2_theme_parameter tlc = {0};
  if (ef2_Curve_themeGet(&rt->curve, "lineCount", &tlc)) lineCount = (int)tlc.v0;
  if (lineCount < 1) lineCount = 1;

  // Theme ranges used by per-line precalc uniforms.
  ef2_theme_parameter amp = {0}, freq = {0}, speed = {0};
  (void)ef2_Curve_themeGet(&rt->curve, "curveAmplitudeRange", &amp);
  (void)ef2_Curve_themeGet(&rt->curve, "curveFrequencyRange", &freq);
  (void)ef2_Curve_themeGet(&rt->curve, "curveSpeedRange", &speed);

  const float amp_min = amp.v0;
  const float amp_max = amp.v1;
  const float amp_diff = amp_max - amp_min;

  const float freq_min = freq.v0;
  const float freq_diff = freq.v1 - freq.v0;

  const float speed_min = speed.v0;
  const float speed_diff = speed.v1 - speed.v0;

  // RNG (decomp seeds 5489 then 1337; final seed = 1337).
  ef2_mt19937 rng;
  ef2__mt_seed(&rng, 5489u);
  ef2__mt_seed(&rng, 1337u);

  const float U32_TO_F = 2.3283064365386963e-10f; // 1/2^32

  {
    int i;
    for (i = 0; i < lineCount; ++i) {
    const float radlc = (float)i / (float)lineCount;
    ef2_Program_setUniform1f(&res->prog_line, "precalc_radlc", radlc);
    ef2_Program_setUniform1f(&res->prog_line, "ra", (float)i);
    ef2_Program_setUniform1f(&res->prog_line, "precalc_ratio", radlc * 0.2f + 0.8f);

    const float v77 = (radlc * 0.5f + 0.5f) * v53;
    ef2_Program_setUniform2f(&res->prog_line, "precalc_car", (amp_diff * (ef2__mt_next_u32(&rng) * U32_TO_F)) * v77, amp_min * v77);

    const float r0 = ef2__mt_next_u32(&rng) * U32_TO_F;
    const float r1 = ef2__mt_next_u32(&rng) * U32_TO_F;
    const float r2 = ef2__mt_next_u32(&rng) * U32_TO_F;
    const float r3 = ef2__mt_next_u32(&rng) * U32_TO_F;

    ef2_Program_setUniform4f(&res->prog_line, "precalc_randval", r0, r1, r2 * 0.13f, r3);

    const float f = freq_min + r0 * freq_diff;
    const float sp = speed_min + r1 * speed_diff;
    const float c = ef2_cos_f(r3 * 3.1415927f);
    ef2_Program_setUniform3f(&res->prog_line, "precalc_curveParams", f, sp, c);

    ef2_Program_applyUniforms(&res->prog_line);

    // meshB indices count: rows=3, cols=20 -> 3*2*(20+2)-2 = 130
      glDrawElements(GL_TRIANGLE_STRIP, 130, GL_UNSIGNED_SHORT, 0);
    }
  }
}

#endif

// Small helpers for blob-style reads/writes.
static inline uint8_t ef2__read_u8(const void* base, size_t off)
{
  const uint8_t* p = (const uint8_t*)base;
  return p[off];
}

static inline int32_t ef2__read_i32(const void* base, size_t off)
{
  int32_t v;
  memcpy(&v, (const uint8_t*)base + off, sizeof(v));
  return v;
}

static inline double ef2__read_f64(const void* base, size_t off)
{
  double v;
  memcpy(&v, (const uint8_t*)base + off, sizeof(v));
  return v;
}

static inline void ef2__write_f64(void* base, size_t off, double v)
{
  memcpy((uint8_t*)base + off, &v, sizeof(v));
}

static inline float ef2__clampf(float x, float lo, float hi)
{
  return (x < lo) ? lo : (x > hi) ? hi : x;
}

// buildShaderFile() always returns a non-NULL string (it may contain only '\n' separators
// when assets are missing). For fallbacks, treat a source as empty if it contains only
// whitespace/newlines.
static int ef2__src_effectively_empty(const char* s)
{
  if (!s) return 1;
  for (; *s; ++s) {
    if (*s != ' ' && *s != '\t' && *s != '\r' && *s != '\n') return 0;
  }
  return 1;
}

static void ef2__res_init(ef2_RendererResources* res)
{
  memset(res, 0, sizeof(*res));
  ef2_Program_init(&res->prog_background);
  ef2_Program_init(&res->prog_line);
  ef2_Texture_init(&res->tex_noise, GL_TEXTURE_2D, 1);
  ef2_Texture_init(&res->tex_bg, GL_TEXTURE_2D, 1);
}

static void ef2__res_deinit(ef2_RendererResources* res)
{
  if (!res) return;

  ef2_Program_deinit(&res->prog_background);
  ef2_Program_deinit(&res->prog_line);

  ef2_Texture_deinit(&res->tex_noise);

  ef2_Texture_deinit(&res->tex_bg);
  ef2_Buffer_deinit(&res->meshA_vb);
  ef2_Buffer_deinit(&res->meshA_ib);
  ef2_Buffer_deinit(&res->meshB_vb);
  ef2_Buffer_deinit(&res->meshB_ib);

  memset(res, 0, sizeof(*res));
}

static int ef2__res_build_shaders(ef2_RendererResources* res, ef2_AAssetManager* mgr)
{
  // background
  char* bg_vs = ef2_renderer_buildShaderFile(mgr, "gfxbackground", "vert");
  char* bg_fs = ef2_renderer_buildShaderFile(mgr, "gfxbackground", "frag");

  int ok_bg = ef2_Program_setSource(&res->prog_background, bg_vs ? bg_vs : "", bg_fs ? bg_fs : "");

  free(bg_vs);
  free(bg_fs);

  // line
  // Baseline/original trace prefers gfxlineB.frag (+.header) over gfxline.frag.
  // Some packages also provide gfxlineA.frag as an alternative. To match the
  // original asset open sequence, try B -> A -> (plain) in that order.
  char* ln_vs = ef2_renderer_buildShaderFile(mgr, "gfxline", "vert");

  char* ln_fs = ef2_renderer_buildShaderFile(mgr, "gfxlineB", "frag");
  if (ef2__src_effectively_empty(ln_fs)) { free(ln_fs); ln_fs = NULL; }

  if (!ln_fs) {
    ln_fs = ef2_renderer_buildShaderFile(mgr, "gfxlineA", "frag");
    if (ef2__src_effectively_empty(ln_fs)) { free(ln_fs); ln_fs = NULL; }
  }

  if (!ln_fs) {
    ln_fs = ef2_renderer_buildShaderFile(mgr, "gfxline", "frag");
    if (ef2__src_effectively_empty(ln_fs)) { free(ln_fs); ln_fs = NULL; }
  }

  int ok_ln = ef2_Program_setSource(&res->prog_line, ln_vs ? ln_vs : "", ln_fs ? ln_fs : "");

  free(ln_vs);
  free(ln_fs);

  return ok_bg && ok_ln;
}

static int ef2__res_build_meshes(ef2_RendererResources* res)
{
  // Matches the values observed in the decompiled renderer on reset:
  // meshA: cols=1, rows=2
  // meshB: cols=20, rows=3
  int okA = ef2_mesh_createVertices(&res->meshA_vb, 1, 2) &&
            ef2_mesh_createIndices(&res->meshA_ib, 1, 2);
  int okB = ef2_mesh_createVertices(&res->meshB_vb, 20, 3) &&
            ef2_mesh_createIndices(&res->meshB_ib, 20, 3);
  return okA && okB;
}

// Uniform arity map extracted from assets/inputs.base.
//
// Notes:
// - Theme values are stored as 4 doubles per key, but the shader uniforms have
//   concrete types (float/vec2/vec3/vec4). Using the correct setter keeps the
//   internal uniform cache consistent and avoids GL errors when enabling real
//   GLES.
// - sampler2D uniforms are set explicitly elsewhere (noise/bg).
static int ef2__uniform_components_for_key(const char* key)
{
  if (!key) return 4;

  // float
  if (strcmp(key, "force") == 0) return 1;
  if (strcmp(key, "ra") == 0) return 1;
  if (strcmp(key, "lsByx") == 0) return 1;
  if (strcmp(key, "curveBendFactor") == 0) return 1;
  if (strcmp(key, "curveBendSpeed") == 0) return 1;
  if (strcmp(key, "curveOffsetSpeed") == 0) return 1;
  if (strcmp(key, "precalc_radlc") == 0) return 1;
  if (strcmp(key, "precalc_ratio") == 0) return 1;

  // vec2
  if (strcmp(key, "l1") == 0) return 2;
  if (strcmp(key, "l1m") == 0) return 2;
  if (strcmp(key, "l2") == 0) return 2;
  if (strcmp(key, "l3") == 0) return 2;
  if (strcmp(key, "l4") == 0) return 2;
  if (strcmp(key, "curveWidthRange") == 0) return 2;
  if (strcmp(key, "curveAmplitudeRange") == 0) return 2;
  if (strcmp(key, "curveFrequencyRange") == 0) return 2;
  if (strcmp(key, "curveSpeedRange") == 0) return 2;
  if (strcmp(key, "curveBendRange") == 0) return 2;
  if (strcmp(key, "curveOffsetRange") == 0) return 2;
  if (strcmp(key, "noiseTextureScale") == 0) return 2;
  if (strcmp(key, "precalc_car") == 0) return 2;

  // vec3
  if (strcmp(key, "precalc_curveParams") == 0) return 3;

  // vec4 (default)
  return 4;
}

static void ef2__apply_theme_uniforms_to_program(ef2_Program* p, const ef2_theme_map* theme)
{
  if (!p || !theme) return;
  {
    size_t i;
    for (i = 0; i < theme->count; ++i) {
    const ef2_theme_entry* e = &theme->items[i];
    if (!e->key) continue;
    // Convention observed in lwp.-1.theme: keys beginning with '.' are grouped variants.
    // We skip those here and apply them later (per-frame) using the transition logic.
    if (e->key[0] == '.') continue;

    // Samplers are bound explicitly (noise/bg).
    if (strcmp(e->key, "noise") == 0 || strcmp(e->key, "bg") == 0) continue;

    const float a = (float)e->value.v0;
    const float b = (float)e->value.v1;
    const float c = (float)e->value.v2;
    const float d = (float)e->value.v3;

    const int n = ef2__uniform_components_for_key(e->key);
    if (n == 1) {
      ef2_Program_setUniform1f(p, e->key, a);
    } else if (n == 2) {
      ef2_Program_setUniform2f(p, e->key, a, b);
    } else if (n == 3) {
      ef2_Program_setUniform3f(p, e->key, a, b, c);
    } else {
      ef2_Program_setUniform4f(p, e->key, a, b, c, d);
    }
    }
  }
}

// ---- Theme grouped variants (lwp.-1.theme) ---------------------------------
// Keys like ".0.bgc1" are palette variants. The theme contains a special key
// ".transitions" which appears to control how often the palette morphs.

static int ef2__theme_parse_variant_key(const char* key, int* out_idx, const char** out_base_key)
{
  if (!key || key[0] != '.') return 0;
  const char* p = key + 1;
  if (*p < '0' || *p > '9') return 0;
  int idx = 0;
  while (*p >= '0' && *p <= '9') {
    idx = idx * 10 + (*p - '0');
    ++p;
  }
  if (*p != '.') return 0;
  ++p;
  if (!*p) return 0;
  if (out_idx) *out_idx = idx;
  if (out_base_key) *out_base_key = p;
  return 1;
}

static int ef2__theme_variant_count(const ef2_theme_map* theme)
{
  if (!theme) return 0;
  int max_idx = -1;
  {
    size_t i;
    for (i = 0; i < theme->count; ++i) {
    const ef2_theme_entry* e = &theme->items[i];
    int idx = 0;
    const char* base = NULL;
    (void)base;
    if (ef2__theme_parse_variant_key(e->key, &idx, &base)) {
      if (idx > max_idx) max_idx = idx;
    }
    }
  }
  return (max_idx >= 0) ? (max_idx + 1) : 0;
}

static int ef2__theme_get_transitions_count(const ef2_theme_map* theme, int* out_count)
{
  if (!theme || !out_count) return 0;
  ef2_theme_parameter v;
  if (!ef2_theme_map_get(theme, ".transitions", &v)) return 0;
  *out_count = (int)v.v0;
  return 1;
}

static int ef2__theme_get_variant_value(const ef2_theme_map* theme, int variant, const char* base_key,
                                       ef2_theme_parameter* out)
{
  if (!theme || !base_key || !out) return 0;
  char tmp[96];

  // Build ".<variant>.<base>" without snprintf (match original symbol set).
  size_t pos = 0;
  if (pos + 1 < sizeof(tmp)) tmp[pos++] = '.';

  // append decimal variant
  {
    unsigned int u = (variant < 0) ? (unsigned int)(-variant) : (unsigned int)variant;
    char digits[16];
    size_t n = 0;
    if (variant < 0) {
      if (pos + 1 < sizeof(tmp)) tmp[pos++] = '-';
    }
    do {
      digits[n++] = (char)('0' + (u % 10u));
      u /= 10u;
    } while (u && n < sizeof(digits));
    {
      size_t i;
      for (i = 0; i < n; ++i) {
      if (pos + 1 >= sizeof(tmp)) break;
      tmp[pos++] = digits[n - 1 - i];
      }
    }
  }

  if (pos + 1 < sizeof(tmp)) tmp[pos++] = '.';

  // append base key
  {
    const char* s;
    for (s = base_key; s && *s; ++s) {
    if (pos + 1 >= sizeof(tmp)) break;
    tmp[pos++] = *s;
    }
  }

  tmp[pos] = '\0';

  if (ef2_theme_map_get(theme, tmp, out)) return 1;
  return ef2_theme_map_get(theme, base_key, out);
}

static void ef2__apply_theme_variant_uniforms_to_program(ef2_Program* p, const ef2_theme_map* theme, const Curve* curve)
{
  if (!p || !theme) return;
  const int vcount = ef2__theme_variant_count(theme);
  if (vcount <= 0) return;

  int tcount = 0;
  (void)ef2__theme_get_transitions_count(theme, &tcount);
  if (tcount <= 0) return;
  if (vcount > 0 && tcount > vcount) tcount = vcount;

  // Phase source: Curve accumulator at 0x128 (matches decomp).
  double phase_src = 0.0;
  if (curve) memcpy(&phase_src, ((const uint8_t*)curve) + 0x128, sizeof(phase_src));

  double phase = fmod(phase_src, (double)tcount);
  if (phase < 0.0) phase += (double)tcount;

  int cur = (int)floor(phase);
  if (cur < 0) cur = 0;
  if (cur >= tcount) cur = tcount - 1;

  int nxt = (int)ceil(phase);
  if (nxt < 0) nxt = 0;
  nxt = (tcount > 0) ? (nxt % tcount) : 0;

  float a = (float)(phase - (double)cur);
  if (a < 0.0f) a = 0.0f;
  if (a > 1.0f) a = 1.0f;



  // Collect the base keys that are present in either the current or next palette.
  const char* keys[64];
  int kcount = 0;
  {
    size_t ti;
    for (ti = 0; ti < theme->count && kcount < (int)(sizeof(keys) / sizeof(keys[0])); ++ti) {
      const ef2_theme_entry* e = &theme->items[ti];
      int idx = 0;
      const char* base = NULL;
      if (!ef2__theme_parse_variant_key(e->key, &idx, &base)) continue;
      if (idx != cur && idx != nxt) continue;

      // Dedup (small list, linear search ok).
      {
        int seen = 0;
        int j;
        for (j = 0; j < kcount; ++j) {
          if (strcmp(keys[j], base) == 0) { seen = 1; break; }
        }
        if (!seen) keys[kcount++] = base;
      }
    }
  }

  {
    int ki;
    for (ki = 0; ki < kcount; ++ki) {
      const char* k = keys[ki];
    if (!k) continue;
    if (strcmp(k, "noise") == 0 || strcmp(k, "bg") == 0) continue;

    ef2_theme_parameter v0, v1;
    if (!ef2__theme_get_variant_value(theme, cur, k, &v0)) continue;
    (void)ef2__theme_get_variant_value(theme, nxt, k, &v1);

    const float f0 = (float)(v0.v0 + (v1.v0 - v0.v0) * (double)a);
    const float f1 = (float)(v0.v1 + (v1.v1 - v0.v1) * (double)a);
    const float f2 = (float)(v0.v2 + (v1.v2 - v0.v2) * (double)a);
    const float f3 = (float)(v0.v3 + (v1.v3 - v0.v3) * (double)a);

    const int n = ef2__uniform_components_for_key(k);
    if (n == 1) {
      ef2_Program_setUniform1f(p, k, f0);
    } else if (n == 2) {
      ef2_Program_setUniform2f(p, k, f0, f1);
    } else if (n == 3) {
      ef2_Program_setUniform3f(p, k, f0, f1, f2);
    } else {
      ef2_Program_setUniform4f(p, k, f0, f1, f2, f3);
    }
    }
  }
}

static void ef2__apply_static_uniforms(ef2_RendererRuntime* rt)
{
  if (!rt) return;

  const ef2_theme_map* theme = NULL;
  if (ef2_Curve_themeMap(&rt->curve, &theme) && theme) {
    ef2__apply_theme_uniforms_to_program(&rt->res.prog_background, theme);
    ef2__apply_theme_uniforms_to_program(&rt->res.prog_line, theme);
  }

  // Sampler bindings (mimic original: noise=0, bg=1)
  ef2_Program_setUniform1i(&rt->res.prog_background, "noise", 0);
  ef2_Program_setUniform1i(&rt->res.prog_background, "bg", 1);
  ef2_Program_setUniform1i(&rt->res.prog_line, "noise", 0);
  ef2_Program_setUniform1i(&rt->res.prog_line, "bg", 1);

  // noiseTextureScale (vec2): computed from screen size vs noise texture size
  int nw = 0, nh = 0, nlen = 0;
  const uint8_t* npix = NULL;
  (void)ef2_Curve_getNoiseRGBA(&rt->curve, &npix, &nw, &nh, &nlen);
  float sx = 1.0f;
  float sy = 1.0f;
  if (nw > 0 && nh > 0 && rt->screen_w > 0 && rt->screen_h > 0) {
    sx = (float)rt->screen_w / (float)nw;
    sy = (float)rt->screen_h / (float)nh;
  }
  ef2_Program_setUniform2f(&rt->res.prog_background, "noiseTextureScale", sx, sy);
  ef2_Program_setUniform2f(&rt->res.prog_line, "noiseTextureScale", sx, sy);
}

static int ef2__res_build_textures(ef2_RendererRuntime* rt)
{
  if (!rt) return 0;
  const uint8_t* rgba = NULL;
  int w = 0, h = 0, len = 0;
  if (!ef2_Curve_getNoiseRGBA(&rt->curve, &rgba, &w, &h, &len)) {
    return 1; // optional
  }
  int ok_noise = ef2_Texture_setRGBA8(&rt->res.tex_noise, w, h, rgba, (size_t)len);
  // bg is optional in our current harness; keep a valid texture bound on unit 1.
  int ok_bg = ef2_Texture_setRGBA8(&rt->res.tex_bg, w, h, rgba, (size_t)len);
  if (!ok_bg) {
    const uint8_t px[4] = {0,0,0,255};
    ok_bg = ef2_Texture_setRGBA8(&rt->res.tex_bg, 1, 1, px, sizeof(px));
  }
  return ok_noise && ok_bg;
}

static int ef2__res_build(ef2_RendererRuntime* rt, ef2_AAssetManager* mgr)
{
  if (!rt) return 0;
  if (!mgr) mgr = rt->mgr;
  if (!mgr) return 0;

  // Rebuild (safe even if first time).
  ef2__res_deinit(&rt->res);
  ef2__res_init(&rt->res);

  if (!ef2__res_build_shaders(&rt->res, mgr)) return 0;
  if (!ef2__res_build_meshes(&rt->res)) return 0;
  if (!ef2__res_build_textures(rt)) return 0;

  // Apply theme and other static uniforms once after (re)build.
  ef2__apply_static_uniforms(rt);

  rt->res.built = 1;
  rt->resources_dirty = 0;
  return 1;
}

void ef2_Renderer_init(ef2_Renderer* r, ef2_AAssetManager* mgr)
{

  if (!r) return;

  // Preserve ABI layout: public struct is raw[0x60].
  memset(r->raw, 0, sizeof(r->raw));

  // If this renderer already has a runtime attached, deinit first.
  ef2_RendererRuntime* old_rt = ef2__renderer_detach_rt(r);
  if (old_rt) {
    ef2__res_deinit(&old_rt->res);
    ef2_Curve_deinit(&old_rt->curve);
    free(old_rt);
  }

  ef2_RendererRuntime* rt = (ef2_RendererRuntime*)malloc(sizeof(*rt));
  if (rt) memset(rt, 0, sizeof(*rt));
  if (!rt) return;

  rt->mgr = mgr;
  rt->resources_dirty = 1;
  rt->is_initialized = 1;
  rt->screen_w = 0;
  rt->screen_h = 0;

  ef2__res_init(&rt->res);
  ef2_Curve_init(&rt->curve, mgr);

  // Store Curve* at +0x5c (matches 95KB liblwplocal.so renderer layout).
  ef2__renderer_set_curve_ptr(r, &rt->curve);

  ef2__renderer_set_rt(r, rt);
}

void ef2_Renderer_deinit(ef2_Renderer* r)
{

  if (!r) return;

  ef2_RendererRuntime* rt = ef2__renderer_detach_rt(r);
  if (rt) {
    ef2__res_deinit(&rt->res);
    ef2_Curve_deinit(&rt->curve);
    free(rt);
  }

  memset(r->raw, 0, sizeof(r->raw));
}

// Update the uniforms that the original renderer updates per-frame.
//
// This function focuses on the "major" dynamic parameters:
// - time (stored as time*100)
// - touch-driven vectors (l1/l1m/l2) and the accumulated motion (l3/l4)
// - aspect/ratio helpers (lsByx, precalc_ratio)
// - precomputed helpers derived from theme ranges (precalc_curveParams, etc.)
static void ef2__renderer_apply_dynamic_uniforms(ef2_RendererRuntime* rt, const rendererdata* rd, double time100)
{
  if (!rt || !rd) return;
  if (!rt->res.built) return;

  float sw = 0.f;
  float sh = 0.f;
  memcpy(&sw, rd->field_0x38, sizeof(sw));
  memcpy(&sh, rd->field_0x3C, sizeof(sh));
  if (sw <= 0.f) sw = (float)rt->screen_w;
  if (sh <= 0.f) sh = (float)rt->screen_h;

  // Touch state from CurveClient.
  const void* cc = (const void*)rt->curve.client_0x8;
  const int touch_active = (ef2__read_u8(cc, EF2_CC_TOUCH_ACTIVE) != 0);
  const double tx = ef2__read_f64(cc, EF2_CC_TOUCH_X);
  const double ty = ef2__read_f64(cc, EF2_CC_TOUCH_Y);
  const double dx = ef2__read_f64(cc, EF2_CC_DX);
  const double dy = ef2__read_f64(cc, EF2_CC_DY);

  // NOTE: The original normalizes both axes using the layout height.
  // This is required to match the step11 uniform hit values (l1/l2/l3) bitwise.
  const float base = (sh > 0.f) ? sh : 1.f;
  const float invBase = 1.0f / base;

  const float ftx = (float)tx;
  const float fty = (float)ty;
  const float fdx = (float)dx;
  const float fdy = (float)dy;

  const float nx = ftx * invBase;
  const float ny = fty * invBase;

  // l1 = instantaneous drag delta (same normalization as l2)
  const float l1x = touch_active ? (fdx * invBase) : 0.f;
  const float l1y = touch_active ? (fdy * invBase) : 0.f;
  const float l1m = ef2_sqrt_f(l1x * l1x + l1y * l1y);

  // l3/l4 = accumulated motion stored in Curve (accX/accY) + time modulation.
  const float accX = (float)ef2__read_f64((const void*)&rt->curve, EF2_C_ACC_X);
  const float accY = (float)ef2__read_f64((const void*)&rt->curve, EF2_C_ACC_Y);
  const float l3x = accX * invBase;
  const float l3y = accY * invBase;
  const float l4x = (l3x * 0.5f) + 0.25f * ef2_sin_f((float)time100 * 0.010f);
  const float l4y = (l3y * 0.5f) + 0.25f * ef2_cos_f((float)time100 * 0.013f);

  // Screen-ratio helpers.
  const float ratio = (sh > 0.f) ? (sw / sh) : 1.f;
  const float precalc_ratio = (ratio > 0.5625f) ? (ratio - 0.5625f + 1.0f) : 1.0f;
  const float lsByx = (sw > 0.f) ? (sh / sw) * 1.3f : 1.3f;

  // Defensive defaults for uniforms that are not theme-driven.
  // If left at 0, some shaders hit 0/0 or NaN paths and can render black on some GPUs.
  const float lsW = (sw > 0.f) ? sw : 1.f;
  const float lsH = (sh > 0.f) ? sh : 1.f;
  const float lsInvW = 1.0f / lsW;
  const float lsInvH = 1.0f / lsH;
  const float ra = 1.0f;


  // Theme midpoints (used as lightweight "precalc" inputs).
  ef2_theme_parameter tp;
  float ampMid = 0.f, freqMid = 0.f, speedMid = 0.f;
  if (ef2_Curve_themeGet(&rt->curve, "curveAmplitudeRange", &tp)) ampMid = (float)((tp.v0 + tp.v1) * 0.5);
  if (ef2_Curve_themeGet(&rt->curve, "curveFrequencyRange", &tp)) freqMid = (float)((tp.v0 + tp.v1) * 0.5);
  if (ef2_Curve_themeGet(&rt->curve, "curveSpeedRange", &tp)) speedMid = (float)((tp.v0 + tp.v1) * 0.5);

  const float force = ((1.0f) < (l1m * 0.10f) ? (1.0f) : (l1m * 0.10f));

  // A tiny deterministic pseudo-rand vector from time.
  const float rv0 = 0.5f + 0.5f * ef2_sin_f((float)time100 * 0.002f);
  const float rv1 = 0.5f + 0.5f * ef2_sin_f((float)time100 * 0.0037f + 1.0f);
  const float rv2 = 0.5f + 0.5f * ef2_cos_f((float)time100 * 0.0013f + 2.0f);
  const float rv3 = 0.5f + 0.5f * ef2_cos_f((float)time100 * 0.0021f + 3.0f);

  // Apply to both programs (background + line), as the original does.
  ef2_Program* progs[2] = { &rt->res.prog_background, &rt->res.prog_line };
  {
    int i;
    for (i = 0; i < 2; ++i) {
      ef2_Program_setUniform1f(progs[i], "lsByx", lsByx);

    // Mandatory: used by background shader (aspect / normalization). Must not stay at 0.
    ef2_Program_setUniform4f(progs[i], "lsB", lsW, lsH, lsInvW, lsInvH);
    // Not currently used by our shipped shaders (kept for parity / future shader variants).
    ef2_Program_setUniform4f(progs[i], "lsA", lsW, lsH, lsInvW, lsInvH);
    // Avoid pow(x, 0) / pow(0, 0) edge cases on some drivers.
    ef2_Program_setUniform1f(progs[i], "ra", ra);

    ef2_Program_setUniform1f(progs[i], "precalc_ratio", precalc_ratio);
    ef2_Program_setUniform4f(progs[i], "precalc_randval", rv0, rv1, rv2, rv3);
    ef2_Program_setUniform3f(progs[i], "precalc_curveParams", freqMid, speedMid, ampMid);
    ef2_Program_setUniform2f(progs[i], "precalc_car", ampMid, freqMid);

    ef2_Program_setUniform1f(progs[i], "force", force);

    ef2_Program_setUniform2f(progs[i], "l2", nx, ny);
    ef2_Program_setUniform2f(progs[i], "l1", l1x, l1y);
    ef2_Program_setUniform2f(progs[i], "l1m", l1m, l1m);
    ef2_Program_setUniform2f(progs[i], "l3", l3x, l3y);
      ef2_Program_setUniform2f(progs[i], "l4", l4x, l4y);
    }
  }
}

__attribute__((visibility("default"), used))
void ef2_compat_renderer_render_impl(ef2_Renderer* r, ef2_AAssetManager* mgr)
    __asm__("_ZN8renderer6renderEP13AAssetManager");
void ef2_compat_renderer_render_impl(ef2_Renderer* r, ef2_AAssetManager* mgr)
{

  ef2_RendererRuntime* rt = ef2__renderer_rt(r);
  if (!rt) return;

  if (!mgr) mgr = rt->mgr;

  // Matches original renderer(...) in the 95KB liblwplocal.so:
  // it calls Curve::updateRenderer(out, curve) and returns early when
  // out->field_0x0[0] == 0.
  rendererdata rd;
  ef2_rendererdata_fillFromCurve(&rd, &rt->curve);
  if (rd.field_0x0[0] == 0) {
    return;
  }

  // Ensure resources exist (programs + meshes).
  if (rt->resources_dirty || !rt->res.built) {
    (void)ef2__res_build(rt, mgr);
  }

  // Update time uniform every frame (original code multiplies seconds by 100).
  double tsec = 0.0;
  memcpy(&tsec, rd.time_0x8, sizeof(tsec));
  const double time100 = tsec * 100.0;
  ef2__write_f64(&rt->curve, EF2_C_TIME100, time100);

  const float time_v = (float)time100;
  ef2_Program_setUniform1f(&rt->res.prog_background, "time", time_v);
  ef2_Program_setUniform1f(&rt->res.prog_line, "time", time_v);

  // Other major dynamic parameters.
  ef2__renderer_apply_dynamic_uniforms(rt, &rd, time100);

  // Theme palette variants (used by lwp.-1.theme) are time-dependent.
  // Apply them per-frame so requestColors() and transitions take effect
  // without forcing a full resource rebuild.
  const ef2_theme_map* theme = NULL;
  if (ef2_Curve_themeMap(&rt->curve, &theme) && theme) {
    // IMPORTANT: The variant phase source lives inside Curve, so this is safe.
    ef2__apply_theme_uniforms_to_program(&rt->res.prog_background, theme);
    ef2__apply_theme_uniforms_to_program(&rt->res.prog_line, theme);
  }

#if EF2_PLATFORM_ANDROID && EF2_USE_REAL_GLES
  ef2__renderer_render_gles(rt);
#else
  (void)mgr;
  // Non-Android build: no real GLES. We keep the CPU-side updates and logging.
#endif
}

void ef2_Renderer_render(ef2_Renderer* r, ef2_AAssetManager* mgr)
{
  ef2_compat_renderer_render_impl(r, mgr);
}


void ef2_Renderer_requestColors(ef2_Renderer* r, ef2_AAssetManager* mgr, int theme_id)
{

  ef2_RendererRuntime* rt = ef2__renderer_rt(r);
  if (!rt) return;

  // Original JNI loads Curve* from renderer+0x5c and calls Curve::requestColors.
  ef2_Curve_requestColors(&rt->curve, mgr ? mgr : rt->mgr, theme_id);
}

void ef2_Renderer_updateScreenLayout(ef2_Renderer* r, int x, int y, int w, int h, int screenW, int screenH)
{

  ef2_RendererRuntime* rt = ef2__renderer_rt(r);
  if (!rt) return;

  rt->screen_w = screenW;
  rt->screen_h = screenH;

  ef2_Curve_updateScreenLayout(&rt->curve, x, y, w, h, screenW, screenH);

  // Theme-dependent uniforms can depend on screen size; no need to fully rebuild.
  // But we ensure resources exist (if a later render happens before shaders are built).
  // Leave resources_dirty as-is; render() will rebuild when needed.
}

void ef2_Renderer_touchDown(ef2_Renderer* r, float x, float y)
{

  ef2_RendererRuntime* rt = ef2__renderer_rt(r);
  if (!rt) return;
  ef2_Curve_touchDown(&rt->curve, x, y);
}

void ef2_Renderer_touch(ef2_Renderer* r, float x, float y)
{

  ef2_RendererRuntime* rt = ef2__renderer_rt(r);
  if (!rt) return;
  ef2_Curve_touch(&rt->curve, x, y);
}

void ef2_Renderer_touchUp(ef2_Renderer* r, float x, float y)
{

  ef2_RendererRuntime* rt = ef2__renderer_rt(r);
  if (!rt) return;
  ef2_Curve_touchUp(&rt->curve, x, y);
}

void ef2_Renderer_activate(ef2_Renderer* r)
{

  ef2_RendererRuntime* rt = ef2__renderer_rt(r);
  if (!rt) return;
  ef2_Curve_activate(&rt->curve);
}

void ef2_Renderer_deactivate(ef2_Renderer* r)
{

  ef2_RendererRuntime* rt = ef2__renderer_rt(r);
  if (!rt) return;
  ef2_Curve_deactivate(&rt->curve);
}

int ef2_Renderer_getSleepRecommendation(ef2_Renderer* r)
{

  ef2_RendererRuntime* rt = ef2__renderer_rt(r);
  if (!rt) return 0;
  return ef2_Curve_getSleepRecommendation(&rt->curve);
}
