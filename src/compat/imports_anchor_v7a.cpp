#include <stdint.h>

// This translation unit is used to *stabilize* .rel.plt (JUMP_SLOT) ordering.
// It must be linked early (see jni/Android.mk).
//
// IMPORTANT:
//  - Keep this TU focused on PLT ordering only. GLOB_DAT stabilization is
//    handled by src/compat/reldyn_anchor_v7a.cpp which should be linked later,
//    to avoid shifting the start of .dynsym away from the stock Sony binary.

extern "C" {
// Guard: when 0, we should do nothing at runtime.
extern volatile unsigned char ef2_imports_guard;
}

static __attribute__((noinline)) void ef2_force_relplt_calls(void) {
  if (!ef2_imports_guard) return;

  __asm__ __volatile__(
      "mov r0, #0\n"
      "mov r1, #0\n"
      "mov r2, #0\n"
      "mov r3, #0\n"
      "\n"
      "@ ef2_force_relplt_calls begin\n"
#include "imports_anchor_relplt_v7a.inc"
      "@ ef2_force_relplt_calls end\n"
      :
      :
      : "r0", "r1", "r2", "r3", "lr", "memory");
}

extern "C" __attribute__((used, noinline)) void ef2_imports_anchor_v7a(void) {
  ef2_force_relplt_calls();
}
