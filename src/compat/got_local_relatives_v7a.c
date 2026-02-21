// Force additional RELATIVE relocations in the *non-PLT* GOT area.
// Goal: shift/shape .got layout toward the Sony reference, where many R_ARM_RELATIVE
// entries appear before the PLT resolver table.
//
// Notes:
// - Build uses -fvisibility=hidden, so we explicitly set DEFAULT visibility here.
// - Link uses -Bsymbolic; we want the linker to be able to relax GOT entries for
//   locally-defined (but default-vis) symbols into R_ARM_RELATIVE when possible.
// - The anchor is kept via -Wl,--undefined=ef2_got_local_relatives_anchor_v7a.

#include <stdint.h>

__attribute__((visibility("default"))) uint32_t ef2_gotloc_0;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_1;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_2;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_3;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_4;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_5;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_6;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_7;

static volatile uintptr_t ef2_gotloc_sink;

__attribute__((used))
void ef2_got_local_relatives_anchor_v7a(void) {
    // Take addresses in a way that discourages constant-folding.
    ef2_gotloc_sink ^= (uintptr_t)&ef2_gotloc_0;
    ef2_gotloc_sink ^= (uintptr_t)&ef2_gotloc_1;
    ef2_gotloc_sink ^= (uintptr_t)&ef2_gotloc_2;
    ef2_gotloc_sink ^= (uintptr_t)&ef2_gotloc_3;
    ef2_gotloc_sink ^= (uintptr_t)&ef2_gotloc_4;
    ef2_gotloc_sink ^= (uintptr_t)&ef2_gotloc_5;
    ef2_gotloc_sink ^= (uintptr_t)&ef2_gotloc_6;
    ef2_gotloc_sink ^= (uintptr_t)&ef2_gotloc_7;
}
