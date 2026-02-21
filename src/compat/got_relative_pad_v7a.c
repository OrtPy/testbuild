// Create additional R_ARM_RELATIVE entries *inside .got* to match the original.
//
// We place a used pointer table into a ".got.*" input section so it lands
// in the final output section ".got".
// functions. For local addresses stored in .got, the dynamic loader applies
// R_ARM_RELATIVE relocations.

#include <stdint.h>

// NOTE (v58):
//   v57 以降は reldyn_anchor_v7a が .got 内の R_ARM_RELATIVE スロットを十分に生成できるため、
//   ここでの .got 追加パディングは **過剰** になりました。
//   run 22212331020 では `.got` 内の R_ARM_RELATIVE が +7 スロット過多となり、
//   gold の match リンカスクリプト（`.data @ 0x18000` 固定）で
//   "section '.data' moves backward" によりリンク失敗しています。
//
//   そのため v58 では GOT パディングを無効化します。

#if 0
static void ef2_got_pad_00(void) {}
static void ef2_got_pad_01(void) {}
static void ef2_got_pad_02(void) {}
static void ef2_got_pad_03(void) {}
static void ef2_got_pad_04(void) {}
static void ef2_got_pad_05(void) {}
static void ef2_got_pad_06(void) {}
static void ef2_got_pad_07(void) {}

__attribute__((used, section(".got.ef2pad")))
static void* ef2_got_relative_pad[8] = {
  (void*)(uintptr_t)&ef2_got_pad_00,
  (void*)(uintptr_t)&ef2_got_pad_01,
  (void*)(uintptr_t)&ef2_got_pad_02,
  (void*)(uintptr_t)&ef2_got_pad_03,
  (void*)(uintptr_t)&ef2_got_pad_04,
  (void*)(uintptr_t)&ef2_got_pad_05,
  (void*)(uintptr_t)&ef2_got_pad_06,
  (void*)(uintptr_t)&ef2_got_pad_07,
};
#endif
