// Force undefined references to specific GNU libstdc++ ABI objects that exist in
// the original liblwplocal.so dynamic relocation table.
//
// IMPORTANT:
// - Do NOT materialize these addresses as static data pointers. That tends to
//   produce R_ARM_ABS32 data relocations.
// - The original binary uses GOT-based references (R_ARM_GLOB_DAT).
//
// Therefore we reference the addresses in code (PIC), which forces GOT entries.

#include <iostream>
#include <stdint.h>

extern "C" {
  // std::string empty rep storage symbol in GNU libstdc++ (arm, old ABI).
  extern char _ZNSs4_Rep20_S_empty_rep_storageE;
}

extern "C" __attribute__((used, noinline)) void ef2_force_libstdcpp_refs(void) {
  void* volatile p = 0;

  p = (void*)&std::cout;
  p = (void*)&std::cerr;
  p = (void*)&_ZNSs4_Rep20_S_empty_rep_storageE;

  __asm__ __volatile__("" : : "r"(p) : "memory");
}
