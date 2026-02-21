// SPDX-License-Identifier: MIT
// Optional .bss padding to reach the reference size without linker-script dot hacks.
//
// gold 1.11 (NDK r10c) crashes with internal errors when the linker script forces
// the location counter inside a NOLOAD .bss section (e.g. ". = __bss_start + 0x865").
//
// Instead, we provide an optional NOBITS input section that can be pulled in via
// KEEP(*(.bss.ef2pad)) from the linker script.
//
// Set EF2_BSS_PAD_BYTES (compile definition) to a positive value if you need padding.

#ifndef EF2_BSS_PAD_BYTES
#define EF2_BSS_PAD_BYTES 0
#endif

#if EF2_BSS_PAD_BYTES > 0
__attribute__((used, section(".bss.ef2pad")))
unsigned char ef2_bss_pad[EF2_BSS_PAD_BYTES];
#endif
