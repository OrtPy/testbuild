#include "ef2/curve.h"
#include "ef2/platform.h"
#include "ef2/curve_offsets.h"
#include "ef2/theme.h"
#include "ef2/theme_tree.h"
#include "ef2/timeutil.h"
#include "ef2/lodepng.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

// lodepng is compiled as C++ in the original binary, so key entry points are exported
// with C++ mangled names. Our C code must bind to those exact symbols.
extern unsigned ef2_lodepng_decode32(
    unsigned char **out,
    unsigned *w,
    unsigned *h,
    const unsigned char *in,
    size_t insize) __asm__("_Z16lodepng_decode32PPhPjS1_PKhj");

static void* ef2__zmalloc(size_t sz) {
  void* p = malloc(sz);
  if (p) memset(p, 0, sz);
  return p;
}

// Side-car runtime state.
// IMPORTANT: we must not store pointers inside the decomp-layout structs if we
// want the raw struct memory to match the original binary. We therefore keep
// the runtime pointer in a tiny global registry keyed by Curve*.
typedef struct ef2_CurveRuntime {
  ef2_theme_map theme;
  int theme_id;
} ef2_CurveRuntime;

#if UINTPTR_MAX == 0xffffffffu
#  define EF2_THEME_TREE_EMBEDDED 1
#else
#  define EF2_THEME_TREE_EMBEDDED 0
#endif

/*
 * Side-car runtime registry
 * ------------------------
 * We keep per-Curve runtime state (parsed theme, etc.) out of the decomp-layout
 * structs to avoid changing their raw memory image.
 *
 * Multiple Curve instances can exist (theme0/theme1, preview, etc.), so we must
 * not use a single global owner slot.
 */
typedef struct ef2_CurveRtEntry {
  const Curve* owner;
  ef2_CurveRuntime* rt;
} ef2_CurveRtEntry;

static ef2_CurveRtEntry* g_curve_rt_entries = NULL;
static size_t g_curve_rt_count = 0;
static size_t g_curve_rt_cap = 0;

static ef2_CurveRuntime* ef2__curve_rt(const Curve* self)
{
  if (!self) return NULL;
  size_t i;
  for (i = 0; i < g_curve_rt_count; ++i) {
    if (g_curve_rt_entries[i].owner == self) return g_curve_rt_entries[i].rt;
  }
  return NULL;
}

static void ef2__curve_set_rt(const Curve* self, ef2_CurveRuntime* rt)
{
  if (!self) return;

  // Update if already present.
  size_t i;
  for (i = 0; i < g_curve_rt_count; ++i) {
    if (g_curve_rt_entries[i].owner == self) {
      g_curve_rt_entries[i].rt = rt;
      return;
    }
  }

  // Append.
  if (g_curve_rt_count == g_curve_rt_cap) {
    size_t new_cap = (g_curve_rt_cap == 0) ? 8 : (g_curve_rt_cap * 2);
    ef2_CurveRtEntry* p = (ef2_CurveRtEntry*)realloc(g_curve_rt_entries, new_cap * sizeof(*p));
    if (!p) return; // OOM: leak-safe, but rt won't be tracked.
    g_curve_rt_entries = p;
    g_curve_rt_cap = new_cap;
  }
  g_curve_rt_entries[g_curve_rt_count].owner = self;
  g_curve_rt_entries[g_curve_rt_count].rt = rt;
  g_curve_rt_count++;
}

static ef2_CurveRuntime* ef2__curve_detach_rt(const Curve* self)
{
  if (!self) return NULL;
  size_t i;
  for (i = 0; i < g_curve_rt_count; ++i) {
    if (g_curve_rt_entries[i].owner == self) {
      ef2_CurveRuntime* rt = g_curve_rt_entries[i].rt;
      // Remove by swap-with-last (order doesn't matter).
      g_curve_rt_entries[i] = g_curve_rt_entries[g_curve_rt_count - 1];
      g_curve_rt_count--;
      return rt;
    }
  }
  return NULL;
}

// ---- Packed-field helpers ----------------------------------------------------
// We keep Curve/CurveClient layouts close to the decompiled binary using raw bytes.
// Access by offset using memcpy to avoid strict-aliasing UB.

static int32_t ef2__read_i32(const void* base, size_t off)
{
  int32_t v = 0;
  memcpy(&v, (const uint8_t*)base + off, sizeof(v));
  return v;
}

static void ef2__write_i32(void* base, size_t off, int32_t v)
{
  memcpy((uint8_t*)base + off, &v, sizeof(v));
}

static double ef2__read_f64(const void* base, size_t off)
{
  double v = 0.0;
  memcpy(&v, (const uint8_t*)base + off, sizeof(v));
  return v;
}

static void ef2__write_f64(void* base, size_t off, double v)
{
  memcpy((uint8_t*)base + off, &v, sizeof(v));
}

static uint8_t ef2__read_u8(const void* base, size_t off)
{
  uint8_t v = 0;
  memcpy(&v, (const uint8_t*)base + off, sizeof(v));
  return v;
}

static void ef2__write_u8(void* base, size_t off, uint8_t v)
{
  memcpy((uint8_t*)base + off, &v, sizeof(v));
}

// Offsets are centralized in ef2/curve_offsets.h

// ---- Noise buffer loader -----------------------------------------------------

static int ef2__try_load_noise_rgba(Curve* self, ef2_AAssetManager* mgr)
{
  if (!self || !mgr) return 0;

  ef2_AAsset* meta = ef2_AAssetManager_open(mgr, "noise.rgba.meta", 3);
  ef2_AAsset* raw  = ef2_AAssetManager_open(mgr, "noise.rgba", 3);
  if (!meta || !raw) {
    if (meta) ef2_AAsset_close(meta);
    if (raw) ef2_AAsset_close(raw);
    return 0;
  }

  const char* meta_txt = (const char*)ef2_AAsset_getBuffer(meta);
  size_t meta_len = ef2_AAsset_getLength(meta);

  int w = 0, h = 0;
  if (meta_txt && meta_len) {
    char tmp[64];
    size_t n = (meta_len < sizeof(tmp)-1) ? meta_len : (sizeof(tmp)-1);
    memcpy(tmp, meta_txt, n);
    tmp[n] = '\0';
    (void)sscanf(tmp, "%d %d", &w, &h);
  }

  const uint8_t* buf = (const uint8_t*)ef2_AAsset_getBuffer(raw);
  size_t len = ef2_AAsset_getLength(raw);

  if (w <= 0 || h <= 0) {
    ef2_AAsset_close(meta);
    ef2_AAsset_close(raw);
    return 0;
  }
  if (!buf || len != (size_t)w * (size_t)h * 4u) {
    ef2_AAsset_close(meta);
    ef2_AAsset_close(raw);
    return 0;
  }

  // Copy before closing the asset. AAsset_close frees the backing buffer.
  uint8_t* dst = (uint8_t*)malloc(len);
  if (!dst) {
    ef2_AAsset_close(meta);
    ef2_AAsset_close(raw);
    return 0;
  }
  memcpy(dst, buf, len);

  ef2_AAsset_close(meta);
  ef2_AAsset_close(raw);

  self->ptr_0xB0 = dst;
  memcpy(&self->field_0x168, &w, sizeof(int32_t));
  memcpy(&self->field_0x16C, &h, sizeof(int32_t));
  int32_t ilen = (int32_t)len;
  memcpy(&self->field_0x170, &ilen, sizeof(int32_t));
  return 1;
}

static int ef2__try_load_noise_png(Curve* self, ef2_AAssetManager* mgr)
{
  if (!self || !mgr) return 0;

  ef2_AAsset* png = ef2_AAssetManager_open(mgr, "noise.png", 3);
  if (!png) return 0;

  const unsigned char* buf = (const unsigned char*)ef2_AAsset_getBuffer(png);
  size_t len = ef2_AAsset_getLength(png);

  unsigned char* out = NULL;
  unsigned w = 0, h = 0;
  unsigned err = 1;
  if (buf && len) {
    // Original uses lodepng::decode into a temporary buffer then copies into Curve-owned storage.
    err = ef2_lodepng_decode32(&out, &w, &h, buf, len);
  }
  ef2_AAsset_close(png);

  if (err || !out || w == 0 || h == 0) {
    if (out) free(out);
    return 0;
  }

  size_t out_len = (size_t)w * (size_t)h * 4u;

  // Match the decompiled behavior: allocate Curve-owned buffer and memcpy into it, then free the decoder buffer.
  uint8_t* heap = (uint8_t*)malloc(out_len);
  if (!heap) {
    free(out);
    return 0;
  }
  memcpy(heap, out, out_len);
  free(out);

  self->ptr_0xB0 = heap;
  // field_0xB4 is observed as 0 right after the pointer store; keep explicit for clarity.
  int32_t zero = 0;
  memcpy(&self->field_0xB4, &zero, sizeof(int32_t));

  int32_t iw = (int32_t)w;
  int32_t ih = (int32_t)h;
  int32_t ilen = (int32_t)out_len;
  memcpy(&self->field_0x168, &iw, sizeof(int32_t));
  memcpy(&self->field_0x16C, &ih, sizeof(int32_t));
  memcpy(&self->field_0x170, &ilen, sizeof(int32_t));
  return 1;
}


// ---- Public API --------------------------------------------------------------

void ef2_Curve_init(Curve* self, ef2_AAssetManager* mgr)
{
  if (!self) return;

  memset(self, 0, sizeof(*self));

#if EF2_THEME_TREE_EMBEDDED
  // Initialize embedded std::map-like RB-tree area (Curve+0x20).
  ef2_theme_tree_init_inplace((uint8_t*)self + 0x20);
#endif

  // runtime
  ef2_CurveRuntime* rt =  (ef2_CurveRuntime*)ef2__zmalloc(sizeof(*rt));
  if (rt) ef2_theme_map_init(&rt->theme);
  ef2__curve_set_rt(self, rt);

  // allocate client
  // NOTE: rendererdata_fillFromCurve() touches extra cached slots beyond the
  // localtypes-minimum CurveClient size, so we allocate a slightly larger blob.
  const size_t cc_blob_size = 0x60; // 96 bytes (covers dword[22] and qword[9])
  CurveClient* cc =  (CurveClient*)ef2__zmalloc(cc_blob_size);
  if (cc) {
    ef2_CurveClient_init(cc);
    self->client_0x8 = cc;
  }

  // Default flags matches decomp constant (=2).
  ef2__write_i32(self, EF2_C_FLAGS, 2);

  // init last_time used by timesince
  ef2_timespec32* ts = (ef2_timespec32*)((uint8_t*)self + EF2_C_LAST_TIME);
  (void)ef2_clock_gettime_monotonic32(ts);

  // Load default theme (-1)
  ef2_Curve_requestColors(self, mgr, -1);

  // Load noise.png (RGBA8) as done in the original binary.
  (void)ef2__try_load_noise_png(self, mgr);
}

void ef2_Curve_deinit(Curve* self)
{
  if (!self) return;

#if EF2_THEME_TREE_EMBEDDED
  // Free embedded theme tree nodes before tearing down other allocations.
  ef2_theme_tree_clear_inplace((uint8_t*)self + 0x20);
#endif

  free(self->ptr_0xB0);
  self->ptr_0xB0 = NULL;

  free(self->client_0x8);
  self->client_0x8 = NULL;

  ef2_CurveRuntime* rt = ef2__curve_detach_rt(self);
  if (rt) {
    ef2_theme_map_deinit(&rt->theme);
    free(rt);
  }

  memset(self, 0, sizeof(*self));
}

void ef2_Curve_requestColors(Curve* self, ef2_AAssetManager* mgr, int theme_id)
{
  if (!self) return;
  ef2_CurveRuntime* rt = ef2__curve_rt(self);
  if (!rt) return;

  // 1) Load theme asset into a parsed representation.
  (void)ef2_theme_load(&rt->theme, mgr, theme_id);
  rt->theme_id = theme_id;

#if EF2_THEME_TREE_EMBEDDED
  // 2) Reflect into the embedded std::map-compatible RB-tree stored in Curve.
  //    This matches the original's requestColors() side-effects on Curve memory.
  (void)ef2_theme_tree_build_from_map_inplace((uint8_t*)self + 0x20, &rt->theme);
#endif
}

void ef2_Curve_updateScreenLayout(Curve* self, int x, int y, int w, int h, int screenW, int screenH)
{
  if (!self || !self->client_0x8) return;
  CurveClient* cc = self->client_0x8;

  ef2__write_i32(cc, EF2_CC_OFF_X, x);
  ef2__write_i32(cc, EF2_CC_OFF_Y, y);
  ef2__write_i32(cc, EF2_CC_W, w);
  ef2__write_i32(cc, EF2_CC_H, h);

  ef2__write_i32(self, EF2_C_ROTATION, screenW);
  ef2__write_i32(self, EF2_C_DENSITY, screenH);
}

void ef2_Curve_touchDown(Curve* self, float x, float y)
{
  if (!self || !self->client_0x8) return;
  CurveClient* cc = self->client_0x8;

  ef2__write_f64(cc, EF2_CC_DX, 0.0);
  ef2__write_f64(cc, EF2_CC_DY, 0.0);

  int offX = ef2__read_i32(cc, EF2_CC_OFF_X);
  int offY = ef2__read_i32(cc, EF2_CC_OFF_Y);

  // Match the original: compute in float space, then store into a double slot.
  // (The decompiler shows a float cast before assigning into a double field.)
  float fx = (float)((float)x + (float)offX);
  float fy = (float)((float)y + (float)offY);
  ef2__write_f64(cc, EF2_CC_TOUCH_X, (double)fx);
  ef2__write_f64(cc, EF2_CC_TOUCH_Y, (double)fy);

  ef2_timespec32* ts = (ef2_timespec32*)((uint8_t*)self + EF2_C_LAST_TIME);
  double t = timesince(ts, 0);
  ef2__write_f64(cc, EF2_CC_TIME1, t);
  ef2__write_f64(cc, EF2_CC_TIME0, ef2__read_f64(cc, EF2_CC_TIME1));

  uint8_t active = ef2__read_u8(cc, EF2_CC_TOUCH_ACTIVE);
  if (!active) {
    int32_t cnt = ef2__read_i32(self, EF2_C_TOUCH_COUNT);
    cnt++;
    ef2__write_i32(self, EF2_C_TOUCH_COUNT, cnt);
  }
  ef2__write_u8(cc, EF2_CC_TOUCH_ACTIVE, 1);
  return;
}

void ef2_Curve_touch(Curve* self, float x, float y)
{
  if (!self || !self->client_0x8) return;
  CurveClient* cc = self->client_0x8;

  if (!ef2__read_u8(cc, EF2_CC_TOUCH_ACTIVE)) return;

  int offX = ef2__read_i32(cc, EF2_CC_OFF_X);
  int offY = ef2__read_i32(cc, EF2_CC_OFF_Y);

  double touchX = ef2__read_f64(cc, EF2_CC_TOUCH_X);
  double touchY = ef2__read_f64(cc, EF2_CC_TOUCH_Y);

  double dx = touchX - (double)x - (double)offX;
  double dy = touchY - (double)y - (double)offY;

  ef2__write_f64(cc, EF2_CC_DX, dx);
  ef2__write_f64(cc, EF2_CC_DY, dy);

  // Match original: update stored touch position using float conversion.
  float fx = (float)((float)x + (float)offX);
  float fy = (float)((float)y + (float)offY);
  ef2__write_f64(cc, EF2_CC_TOUCH_X, (double)fx);
  ef2__write_f64(cc, EF2_CC_TOUCH_Y, (double)fy);

  ef2_timespec32* ts = (ef2_timespec32*)((uint8_t*)self + EF2_C_LAST_TIME);
  double t = timesince(ts, 0);
  ef2__write_f64(cc, EF2_CC_TIME0, t);

  if (fabs(dx) <= 4000.0 && fabs(dy) <= 4000.0) {
    int flags = ef2__read_i32(self, EF2_C_FLAGS);
    double divisor = (flags & 1) ? 60.0 : 220.0;

    double accX = ef2__read_f64(self, EF2_C_ACC_X);
    double accY = ef2__read_f64(self, EF2_C_ACC_Y);

    accX += dx / 320.0;
    accY += dy / divisor;

    ef2__write_f64(self, EF2_C_ACC_X, accX);
    ef2__write_f64(self, EF2_C_ACC_Y, accY);
  }

  return;
}

void ef2_Curve_touchUp(Curve* self, float x, float y)
{
  if (!self) return;
  (void)ef2_Curve_touch(self, x, y);

  if (!self->client_0x8) return;
  CurveClient* cc = self->client_0x8;

  if (ef2__read_u8(cc, EF2_CC_TOUCH_ACTIVE)) {
    int32_t cnt = ef2__read_i32(self, EF2_C_TOUCH_COUNT);
    cnt--;
    if (cnt < 0) cnt = 0;
    ef2__write_i32(self, EF2_C_TOUCH_COUNT, cnt);
  }
  ef2__write_u8(cc, EF2_CC_TOUCH_ACTIVE, 0);
  return;
}

void ef2_Curve_activate(Curve* self)
{
  if (!self || !self->client_0x8) return;
  CurveClient* cc = self->client_0x8;
  ef2__write_u8(cc, 0, 0);
}

void ef2_Curve_deactivate(Curve* self)
{
  if (!self || !self->client_0x8) return;
  CurveClient* cc = self->client_0x8;

  if (ef2__read_u8(cc, EF2_CC_TOUCH_ACTIVE)) {
    int32_t cnt = ef2__read_i32(self, EF2_C_TOUCH_COUNT);
    cnt--;
    if (cnt < 0) cnt = 0;
    ef2__write_i32(self, EF2_C_TOUCH_COUNT, cnt);
  }
  ef2__write_u8(cc, EF2_CC_TOUCH_ACTIVE, 0);
  ef2__write_u8(cc, 0, 0);
}

int ef2_Curve_getSleepRecommendation(Curve* self)
{
  if (!self) return 0;

  // Original (ARMv7 decomp):
  //   return (int)(200000.0 / (s*s*800.0 + 0.1));
  // where s is the double at EF2_C_SLEEP_FACTOR.
  const double s = ef2__read_f64(self, EF2_C_SLEEP_FACTOR);
  const double denom = (s * s * 800.0) + 0.1;

  // Defensive: avoid division by 0 / negative.
  if (denom <= 0.0) return 0;

  const double v = 200000.0 / denom;

  // Decomp casts to int (truncate toward 0).
  if (v <= 0.0) return 0;
  if (v > 2147483647.0) return 2147483647;
  return (int)v;
}

int ef2_Curve_themeGet(Curve* self, const char* key, ef2_theme_parameter* out)
{
  if (!self || !key || !out) return 0;

#if EF2_THEME_TREE_EMBEDDED
  // Prefer the embedded RB-tree (std::map-like) representation on ARMv7.
  if (ef2_theme_tree_find_inplace((uint8_t*)self + 0x20, key, out)) {
    return 1;
  }
#endif

  ef2_CurveRuntime* rt = ef2__curve_rt(self);
  if (!rt) return 0;
  return ef2_theme_map_get(&rt->theme, key, out);
}

int ef2_Curve_themeMap(const Curve* self, const ef2_theme_map** out_map)
{
  if (out_map) *out_map = NULL;
  if (!self || !out_map) return 0;
  ef2_CurveRuntime* rt = ef2__curve_rt(self);
  if (!rt) return 0;
  *out_map = &rt->theme;
  return 1;
}

int ef2_Curve_getNoiseRGBA(const Curve* self, const uint8_t** out_rgba,
                           int* out_w, int* out_h, int* out_len)
{
  if (out_rgba) *out_rgba = NULL;
  if (out_w) *out_w = 0;
  if (out_h) *out_h = 0;
  if (out_len) *out_len = 0;
  if (!self) return 0;

  const uint8_t* p = (const uint8_t*)self->ptr_0xB0;
  if (!p) return 0;

  int32_t w = 0, h = 0, len = 0;
  memcpy(&w, &self->field_0x168, sizeof(w));
  memcpy(&h, &self->field_0x16C, sizeof(h));
  memcpy(&len, &self->field_0x170, sizeof(len));
  if (w <= 0 || h <= 0 || len <= 0) return 0;

  if ((size_t)len != (size_t)w * (size_t)h * 4u) return 0;

  if (out_rgba) *out_rgba = p;
  if (out_w) *out_w = w;
  if (out_h) *out_h = h;
  if (out_len) *out_len = len;
  return 1;
}
