#include "ef2/decomp_compat.h"

void Rb_tree_impl(void* tree_impl)
{
  // In the original binary this likely initializes a std::_Rb_tree_impl.
  // For now we do nothing. This keeps the build green and lets you
  // progressively reimplement container semantics later.
  (void)tree_impl;
}

void M_erase_3(int tree_or_theme_obj, void* node)
{
  (void)tree_or_theme_obj;
  (void)node;
}

_DWORD* M_copy(int dst_base, int* src_root, int dst_sentinel)
{
  (void)dst_base;
  (void)src_root;
  (void)dst_sentinel;
  return NULL;
}
