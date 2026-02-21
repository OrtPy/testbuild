// .bss sizing notes (armeabi-v7a)
//
// The perfect-match layout is enforced by the linker script
//   jni/ldscripts/armelf_linux_eabi_gold_compat.xsw
// which pins the final .bss size to the reference value (0x865) by advancing the
// location counter to __bss_start + 0x865.
//
// IMPORTANT:
// Because the script hard-pins the final size, any *real* .bss/COMMON content that
// grows beyond 0x865 will force the linker script to move the location counter
// backwards, and ld.gold 2.24 (NDK r10c) may crash with an internal error
// (output.cc:set_offset) instead of producing a friendly message.
//
// Therefore, keep this file's contribution intentionally tiny. If you need to
// grow/shrink .bss for matching, do it in the linker script (safe expansion only)
// rather than via a large pad symbol here.

#include <stdint.h>

// 1-byte volatile guard so the compiler cannot assume constant and so .bss can
// end at an odd size (reference is 0x865).
__attribute__((used, aligned(1)))
volatile uint8_t ef2_imports_guard;

// Keep the historical symbol name, but do not attempt to size-match using it.
// The linker script will expand .bss to the exact size when needed.
__attribute__((used, aligned(1)))
volatile unsigned char ef2_bss_pad[1];
