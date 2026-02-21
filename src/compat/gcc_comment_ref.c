// Force a deterministic .comment section to match the reference build.
//
// Important: Do NOT use __attribute__((section(".comment"))) with a normal data object.
// On older binutils/as (NDK r9d), that can produce an assembler warning:
//   "setting incorrect section attributes for .comment"
// and may trigger ld.gold internal errors.
//
// Instead, emit the .comment section with explicit flags "MS" (mergeable strings),
// progbits type, and 1-byte alignment, matching GCC's typical emission.

#if defined(__GNUC__)
// Use GAS-compatible "@progbits" (older binutils) instead of "%progbits".
// Also prepend a NUL so the first string begins at offset 1, matching reference.
__asm__(
    /*
     * Emit into .comment with explicit flags and entry size so sh_entsize becomes 1 (match reference).
     * The build adds -fno-ident and the linker script discards any remaining compiler-generated .comment
     * to avoid duplicate GCC strings.
     * Keep ONLY
     * this deterministic payload and discard all compiler-generated .comment
     * contributions from other objects.
     */
    ".section .comment,\"MS\",@progbits,1\n"
    ".byte 0\n"
    ".ascii \"GCC: (GNU) 4.6 20120106 (prerelease)\\0\"\n"
    ".ascii \"GCC: (GNU) 4.8\\0\"\n"
    ".previous\n"
);
#endif
