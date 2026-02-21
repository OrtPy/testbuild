#include "ef2/platform.h"

#include <stdlib.h>
#include <string.h>

// Minimal dynamic string builder (file-local) used for shader concatenation.
// Keep everything static to avoid exporting extra symbols.
typedef struct ef2_dynstr {
  char*  p;
  size_t n;
  size_t cap;
} ef2_dynstr;

static void ds_init(ef2_dynstr* s)
{
  s->p = NULL;
  s->n = 0;
  s->cap = 0;
}

static int ds_reserve(ef2_dynstr* s, size_t need)
{
  if (need <= s->cap) return 1;
  {
    size_t ncap = (s->cap == 0) ? 256 : s->cap;
    while (ncap < need) ncap *= 2;
    {
      char* np = (char*)realloc(s->p, ncap);
      if (!np) return 0;
      s->p = np;
      s->cap = ncap;
      return 1;
    }
  }
}

static int ds_append_n(ef2_dynstr* s, const char* data, size_t len)
{
  if (!len) return 1;
  if (!ds_reserve(s, s->n + len + 1)) return 0;
  memcpy(s->p + s->n, data, len);
  s->n += len;
  s->p[s->n] = '\0';
  return 1;
}

static int ds_append_c(ef2_dynstr* s, char c)
{
  if (!ds_reserve(s, s->n + 2)) return 0;
  s->p[s->n++] = c;
  s->p[s->n] = '\0';
  return 1;
}

static char* ds_release(ef2_dynstr* s)
{
  // Ensure non-NULL, NUL-terminated return.
  if (!s->p) {
    s->p = (char*)malloc(1);
    if (s->p) s->p[0] = '\0';
  }
  {
    char* out = s->p;
    s->p = NULL;
    s->n = 0;
    s->cap = 0;
    return out;
  }
}

static void ef2__append_cstr(char* out, size_t* pos, size_t cap, const char* s)
{
  size_t p = *pos;
  while (*s && p + 1 < cap) {
    out[p++] = *s++;
  }
  out[p] = '\0';
  *pos = p;
}

static void ef2__append_ch(char* out, size_t* pos, size_t cap, char c)
{
  size_t p = *pos;
  if (p + 1 < cap) {
    out[p++] = c;
    out[p] = '\0';
    *pos = p;
  }
}

// Build "pkg.name.tail".
static void ef2__build_asset_name(char* out, size_t cap, const char* pkg, const char* name, const char* tail)
{
  if (!out || cap == 0) return;
  out[0] = '\0';
  {
    size_t pos = 0;
    ef2__append_cstr(out, &pos, cap, pkg ? pkg : "");
    ef2__append_ch(out, &pos, cap, '.');
    ef2__append_cstr(out, &pos, cap, name ? name : "");
    ef2__append_ch(out, &pos, cap, '.');
    ef2__append_cstr(out, &pos, cap, tail ? tail : "");
  }
}

// Build "pkg.name".
static void ef2__build_asset_name2(char* out, size_t cap, const char* pkg, const char* name)
{
  if (!out || cap == 0) return;
  out[0] = '\0';
  {
    size_t pos = 0;
    ef2__append_cstr(out, &pos, cap, pkg ? pkg : "");
    ef2__append_ch(out, &pos, cap, '.');
    ef2__append_cstr(out, &pos, cap, name ? name : "");
  }
}

static void ef2__append_asset(ef2_dynstr* ds, ef2_AAssetManager* mgr, const char* asset_name)
{
  ef2_AAsset* a = ef2_AAssetManager_open(mgr, asset_name, 3 /* AASSET_MODE_BUFFER */);
  if (a) {
    const void* buf = ef2_AAsset_getBuffer(a);
    const size_t len = (size_t)ef2_AAsset_getLength(a);
    if (buf && len) {
      ds_append_n(ds, (const char*)buf, len);
    }
    ef2_AAsset_close(a);
  }
}

char* ef2_renderer_buildShaderFile(ef2_AAssetManager* mgr, const char* package, const char* name)
{
  // Match original asset access order (trace_out_step11 / slight):
  //   inputs.base
  //   <package>.<vert|frag>.header
  //   header.<vert|frag>.base
  //   <package>.<vert|frag>
  //   footer.<vert|frag>.base
  // and concatenate with '\n' separators.
  if (!mgr || !package || !name) return NULL;

  char per_header[128];
  char header_base[128];
  char per_body[128];
  char footer_base[128];

  ef2__build_asset_name(per_header, sizeof(per_header), package, name, "header");
  ef2__build_asset_name(header_base, sizeof(header_base), "header", name, "base");
  ef2__build_asset_name2(per_body, sizeof(per_body), package, name);
  ef2__build_asset_name(footer_base, sizeof(footer_base), "footer", name, "base");

  ef2_dynstr ds;
  ds_init(&ds);

  ef2__append_asset(&ds, mgr, "inputs.base");
  ds_append_c(&ds, '\n');

  ef2__append_asset(&ds, mgr, per_header);
  ds_append_c(&ds, '\n');

  ef2__append_asset(&ds, mgr, header_base);
  ds_append_c(&ds, '\n');

  ef2__append_asset(&ds, mgr, per_body);
  ds_append_c(&ds, '\n');

  ef2__append_asset(&ds, mgr, footer_base);

  return ds_release(&ds);
}
