#pragma once

#include "ef2/common.h"

#ifdef __cplusplus
extern "C" {
#endif

// No-op initializer for std::map/... red-black tree implementation.
void Rb_tree_impl(void* tree_impl);

// Erase tree nodes (stub)
void M_erase_3(int tree_or_theme_obj, void* node);

// Copy tree nodes (stub)
_DWORD* M_copy(int dst_base, int* src_root, int dst_sentinel);

#ifdef __cplusplus
}
#endif
