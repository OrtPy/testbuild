#pragma once

#include <stdint.h>
#include "ef2/theme.h"

#ifdef __cplusplus
extern "C" {
#endif

// Embedded theme RB-tree utilities.
//
// The original ARMv7 liblwplocal.so stores a std::map inside Curve at offset 0x20
// (std::_Rb_tree_impl) with the header node at offset 0x24 and node_count at 0x34.
//
// We only emulate this in-place layout on 32-bit builds.

typedef struct ef2_rb_node_base {
  // libstdc++ uses a color enum followed by pointers.
  // We keep color as a full 32-bit word so that parent is at +4 (matches decomp).
  uint32_t color;
  struct ef2_rb_node_base* parent;
  struct ef2_rb_node_base* left;
  struct ef2_rb_node_base* right;
} ef2_rb_node_base;

typedef struct ef2_theme_rb_node {
  ef2_rb_node_base base;
  char* key;                 // NUL-terminated key string (heap-owned)
  ef2_theme_parameter value; // parameter payload
} ef2_theme_rb_node;

// tree_base is the address of the embedded std::_Rb_tree_impl (Curve + 0x20 on ARMv7).
// These helpers assume 32-bit pointers and MUST NOT be used on 64-bit builds.
void ef2_theme_tree_init_inplace(void* tree_base);
void ef2_theme_tree_clear_inplace(void* tree_base);
int  ef2_theme_tree_build_from_map_inplace(void* tree_base, const ef2_theme_map* src);
int  ef2_theme_tree_find_inplace(void* tree_base, const char* key, ef2_theme_parameter* out);

#ifdef __cplusplus
}
#endif
