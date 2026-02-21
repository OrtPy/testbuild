#pragma once

#include "ef2/platform.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Theme parameter as seen in lwp.<id>.theme assets: 4 floating-point values.
// In the original binary these are stored in a std::map<std::string, themeparameter>.
typedef struct ef2_theme_parameter {
  double v0;
  double v1;
  double v2;
  double v3;
} ef2_theme_parameter;

// A very small C replacement for std::map<std::string, themeparameter>.
// Theme files are small (dozens of entries), so a linear container is fine.
typedef struct ef2_theme_entry {
  char* key;                 // heap-owned, NUL-terminated
  ef2_theme_parameter value;
} ef2_theme_entry;

typedef struct ef2_theme_map {
  ef2_theme_entry* items;
  size_t count;
  size_t cap;
} ef2_theme_map;

void ef2_theme_map_init(ef2_theme_map* m);
void ef2_theme_map_clear(ef2_theme_map* m);
void ef2_theme_map_deinit(ef2_theme_map* m);

// Set or replace key/value (key is copied).
int  ef2_theme_map_set(ef2_theme_map* m, const char* key, const ef2_theme_parameter* val);

// Find key; returns 1 if found.
int  ef2_theme_map_get(const ef2_theme_map* m, const char* key, ef2_theme_parameter* out);

// Load lwp.<theme_id>.theme from assets into out.
// If the file is missing and theme_id != -1, this falls back to -1.
// Returns 0 on success.
int  ef2_theme_load(ef2_theme_map* out, ef2_AAssetManager* mgr, int theme_id);

#ifdef __cplusplus
}
#endif
