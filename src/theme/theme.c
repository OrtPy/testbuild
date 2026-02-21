#include "ef2/theme.h"
#include "ef2/platform.h"

#include <stdlib.h>
#include <string.h>

static char* ef2__strdup(const char* s)
{
  if (!s) return NULL;
  size_t n = strlen(s);
  char* p = (char*)malloc(n + 1);
  if (!p) return NULL;
  memcpy(p, s, n + 1);
  return p;
}

void ef2_theme_map_init(ef2_theme_map* m)
{
  if (!m) return;
  memset(m, 0, sizeof(*m));
}

static void ef2__entry_free(ef2_theme_entry* e)
{
  if (!e) return;
  free(e->key);
  e->key = NULL;
}

void ef2_theme_map_clear(ef2_theme_map* m)
{
  if (!m) return;
  {
    size_t i;
    for (i = 0; i < m->count; ++i) {
      ef2__entry_free(&m->items[i]);
    }
  }
  m->count = 0;
}

void ef2_theme_map_deinit(ef2_theme_map* m)
{
  if (!m) return;
  ef2_theme_map_clear(m);
  free(m->items);
  m->items = NULL;
  m->cap = 0;
}

static int ef2__ensure_cap(ef2_theme_map* m, size_t need)
{
  if (need <= m->cap) return 1;
  size_t newcap = (m->cap == 0) ? 32 : (m->cap * 2);
  if (newcap < need) newcap = need;
  ef2_theme_entry* p = (ef2_theme_entry*)realloc(m->items, newcap * sizeof(ef2_theme_entry));
  if (!p) return 0;
  if (newcap > m->cap) {
    memset(p + m->cap, 0, (newcap - m->cap) * sizeof(ef2_theme_entry));
  }
  m->items = p;
  m->cap = newcap;
  return 1;
}

int ef2_theme_map_set(ef2_theme_map* m, const char* key, const ef2_theme_parameter* val)
{
  if (!m || !key || !val) return 0;

  {
    size_t i;
    for (i = 0; i < m->count; ++i) {
      if (m->items[i].key && strcmp(m->items[i].key, key) == 0) {
        m->items[i].value = *val;
        return 1;
      }
    }
  }

  if (!ef2__ensure_cap(m, m->count + 1)) return 0;

  ef2_theme_entry* e = &m->items[m->count++];
  e->key = ef2__strdup(key);
  if (!e->key) { m->count--; return 0; }
  e->value = *val;
  return 1;
}

int ef2_theme_map_get(const ef2_theme_map* m, const char* key, ef2_theme_parameter* out)
{
  if (!m || !key) return 0;
  {
    size_t i;
    for (i = 0; i < m->count; ++i) {
      if (m->items[i].key && strcmp(m->items[i].key, key) == 0) {
        if (out) *out = m->items[i].value;
        return 1;
      }
    }
  }
  return 0;
}

// ---- theme file parser -------------------------------------------------------

static int ef2__is_space(char c)
{
  return (c == ' ') || (c == '\t') || (c == '\r') || (c == '\n') || (c == '\v') || (c == '\f');
}

static int ef2__is_digit(char c)
{
  return (c >= '0' && c <= '9');
}

// tokenizes in-place; returns pointer to next token, or NULL.
static char* ef2__next_token(char** pcur)
{
  char* p = (pcur && *pcur) ? *pcur : NULL;
  if (!p) return NULL;

  while (*p && ef2__is_space(*p)) p++;
  if (!*p) { *pcur = p; return NULL; }

  char* tok = p;
  while (*p && !ef2__is_space(*p)) p++;

  if (*p) { *p = '\0'; p++; }
  *pcur = p;
  return tok;
}

// Minimal decimal parser (no locale). Supports: [+/-]digits[.digits][e[+/-]digits]
static int ef2__parse_double(const char* s, double* out)
{
  if (!s || !*s) return 0;
  const char* p = s;

  int sign = 1;
  if (*p == '+') { p++; }
  else if (*p == '-') { sign = -1; p++; }

  int saw_digit = 0;
  double ip = 0.0;
  while (ef2__is_digit(*p)) {
    saw_digit = 1;
    ip = ip * 10.0 + (double)(*p - '0');
    p++;
  }

  double fp = 0.0;
  double div = 1.0;
  if (*p == '.') {
    p++;
    while (ef2__is_digit(*p)) {
      saw_digit = 1;
      fp = fp * 10.0 + (double)(*p - '0');
      div *= 10.0;
      p++;
    }
  }

  if (!saw_digit) return 0;
  double v = (ip + (fp / div)) * (double)sign;

  // exponent
  if (*p == 'e' || *p == 'E') {
    p++;
    int esign = 1;
    if (*p == '+') { p++; }
    else if (*p == '-') { esign = -1; p++; }

    int exp = 0;
    int exp_digit = 0;
    while (ef2__is_digit(*p)) {
      exp_digit = 1;
      exp = exp * 10 + (*p - '0');
      p++;
    }
    if (exp_digit) {
      double pow10 = 1.0;
      while (exp-- > 0) pow10 *= 10.0;
      if (esign < 0) v /= pow10;
      else v *= pow10;
    }
  }

  if (out) *out = v;
  return 1;
}

static void ef2__append_cstr(char* dst, size_t* pos, size_t cap, const char* s)
{
  if (!dst || !pos || cap == 0) return;
  size_t p = *pos;
  while (*s && p + 1 < cap) {
    dst[p++] = *s++;
  }
  dst[p] = '\0';
  *pos = p;
}

static void ef2__append_int(char* dst, size_t* pos, size_t cap, int v)
{
  if (!dst || !pos || cap == 0) return;
  char tmp[16];
  size_t n = 0;

  unsigned int u;
  if (v < 0) {
    ef2__append_cstr(dst, pos, cap, "-");
    u = (unsigned int)(-v);
  } else {
    u = (unsigned int)v;
  }

  do {
    tmp[n++] = (char)('0' + (u % 10u));
    u /= 10u;
  } while (u && n < sizeof(tmp));

  // reverse
  {
    size_t i;
    for (i = 0; i < n; ++i) {
      if (*pos + 1 >= cap) break;
      dst[*pos] = tmp[n - 1 - i];
      (*pos)++;
    }
  }
  dst[*pos] = '\0';
}

static void ef2__format_theme_fname(int theme_id, char* out, size_t outsz)
{
  if (!out || outsz == 0) return;
  out[0] = '\0';
  size_t pos = 0;
  ef2__append_cstr(out, &pos, outsz, "lwp.");
  ef2__append_int(out, &pos, outsz, theme_id);
  ef2__append_cstr(out, &pos, outsz, ".theme");
}

static int ef2__load_file_to_cstr(ef2_AAssetManager* mgr, const char* name, char** out_buf, size_t* out_len)
{
  if (out_buf) *out_buf = NULL;
  if (out_len) *out_len = 0;
  if (!mgr || !name || !out_buf) return 0;

  ef2_AAsset* a = ef2_AAssetManager_open(mgr, name, 3);
  if (!a) return 0;

  const void* buf = ef2_AAsset_getBuffer(a);
  size_t len = ef2_AAsset_getLength(a);

  char* s = (char*)malloc(len + 1);
  if (!s) { ef2_AAsset_close(a); return 0; }
  if (len && buf) memcpy(s, buf, len);
  s[len] = '\0';

  ef2_AAsset_close(a);
  *out_buf = s;
  if (out_len) *out_len = len;
  return 1;
}

static int ef2__theme_load_one(ef2_theme_map* out, ef2_AAssetManager* mgr, int theme_id)
{
  if (!out) return 0;

  char fname[64];
  ef2__format_theme_fname(theme_id, fname, sizeof(fname));

  char* txt = NULL;
  size_t len = 0;
  if (!ef2__load_file_to_cstr(mgr, fname, &txt, &len)) {
    return 0;
  }

  char* cur = txt;
  for (;;) {
    char* key = ef2__next_token(&cur);
    if (!key) break;

    ef2_theme_parameter v;
    char* t0 = ef2__next_token(&cur);
    char* t1 = ef2__next_token(&cur);
    char* t2 = ef2__next_token(&cur);
    char* t3 = ef2__next_token(&cur);
    if (!t0 || !t1 || !t2 || !t3) break;

    if (!ef2__parse_double(t0, &v.v0) ||
        !ef2__parse_double(t1, &v.v1) ||
        !ef2__parse_double(t2, &v.v2) ||
        !ef2__parse_double(t3, &v.v3)) {
      break;
    }

    (void)ef2_theme_map_set(out, key, &v);
  }

  free(txt);
  return 1;
}

int ef2_theme_load(ef2_theme_map* out, ef2_AAssetManager* mgr, int theme_id)
{
  if (!out) return 1;
  ef2_theme_map_clear(out);

  if (!mgr) {
    return 0;
  }

  if (ef2__theme_load_one(out, mgr, theme_id)) return 0;

  if (theme_id != -1) {
    if (ef2__theme_load_one(out, mgr, -1)) return 0;
  }
  return 1;
}
