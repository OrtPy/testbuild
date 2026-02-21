#include <stdint.h>

// NOTE:
// This translation unit is used to *shape* .rel.dyn (especially .got) ordering.
// We intentionally take addresses of specific extern symbols in a specific
// sequence and interleave “local” addresses so that gold allocates GOT slots
// (GLOB_DAT / RELATIVE) in the same pattern as the reference binary.
//
// The goal here is not runtime behavior. The anchor is forced in by
// -Wl,--undefined=ef2_reldyn_anchor_v7a.

extern "C" {

// Imported (GLOB_DAT) targets expected in reference order.
extern uintptr_t __stack_chk_guard;                // libc
extern void __cxa_call_unexpected(void);           // libstdc++/libsupc++
extern void* __gnu_Unwind_Find_exidx(void*, int*); // libgcc/unwind

// iostream/string symbols (libstdc++).
extern void _ZNSt8ios_base4InitD1Ev(void);
extern void* _ZSt4cout;
extern void* _ZSt4cerr;
extern char _ZNSs4_Rep20_S_empty_rep_storageE;

// Local “slot fillers” (RELATIVE) — default visibility so that PIC address-take
// goes through GOT and becomes R_ARM_RELATIVE after relaxation (-Bsymbolic).
__attribute__((visibility("default"))) uint32_t ef2_gotloc_00 = 0;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_01 = 0;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_02 = 0;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_03 = 0;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_04 = 0;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_05 = 0;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_06 = 0;
__attribute__((visibility("default"))) uint32_t ef2_gotloc_07 = 0;

// Compiler barrier helpers.
static inline void ef2_barrier_ptr(const void* p) {
  asm volatile("" : : "r"(p) : "memory");
}
static inline void ef2_barrier_u32(uint32_t v) {
  asm volatile("" : : "r"(v) : "memory");
}

// This anchor must be kept.
__attribute__((used, visibility("default"))) void ef2_reldyn_anchor_v7a(void) {
  // Guard to keep codegen from collapsing everything.
  volatile uint32_t sink = 0;

  // Reference wants GLOB_DAT order:
  //   empty_rep, __stack_chk_guard, ios_base::InitD1, cerr, cout,
  //   __gnu_Unwind_Find_exidx, __cxa_call_unexpected
  // and interleaved RELATIVE slots between them.

  // GLOB_DAT #1: empty_rep @ .got +0x04
  ef2_barrier_ptr(&_ZNSs4_Rep20_S_empty_rep_storageE);

  // RELATIVE: one slot before __stack_chk_guard
  ef2_barrier_ptr(&ef2_gotloc_00);

  // GLOB_DAT #2: __stack_chk_guard
  ef2_barrier_ptr((void*)&__stack_chk_guard);

  // RELATIVE x4 before ios_base::InitD1
  ef2_barrier_ptr(&ef2_gotloc_01);
  ef2_barrier_ptr(&ef2_gotloc_02);
  ef2_barrier_ptr(&ef2_gotloc_03);
  ef2_barrier_ptr(&ef2_gotloc_04);

  // GLOB_DAT #3: ios_base::InitD1
  ef2_barrier_ptr((void*)&_ZNSt8ios_base4InitD1Ev);

  // RELATIVE x1 before cerr
  ef2_barrier_ptr(&ef2_gotloc_05);

  // GLOB_DAT #4: cerr
  ef2_barrier_ptr(&_ZSt4cerr);

  // RELATIVE (trimmed in v59)
  ef2_barrier_ptr(&ef2_gotloc_06);
  ef2_barrier_ptr(&ef2_gotloc_07);

  // GLOB_DAT #5: cout
  ef2_barrier_ptr(&_ZSt4cout);

  // NOTE (v59):
  //   v58 では .got/.rel.dyn が +7 RELATIVE 過多となり、match 用 gold リンカスクリプトの
  //   `.data @ 0x18000` 固定境界に食い込んで `section '.data' moves backward` でリンク失敗していました。
  //   ここではローカル RELATIVE スロット(ef2_gotloc_*)の生成数を 15 -> 8 に減らし、
  //   `.got size 0x278` / `.rel.dyn entries 34` へ戻すことを狙います。

  // GLOB_DAT #6: __gnu_Unwind_Find_exidx
  ef2_barrier_ptr((void*)&__gnu_Unwind_Find_exidx);

  // GLOB_DAT #7: __cxa_call_unexpected
  ef2_barrier_ptr((void*)&__cxa_call_unexpected);

  // Consume a little so compiler won't treat this as empty.
  sink ^= (uint32_t)(uintptr_t)&ef2_gotloc_07;
  ef2_barrier_u32(sink);
}

} // extern "C"
