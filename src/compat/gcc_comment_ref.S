/*
 * Deterministic .comment payload to match the reference liblwplocal.so.
 *
 * Requirements (confirmed by fingerprint):
 *  - .comment size: 0x35 bytes
 *  - sh_entsize:    1
 *  - only ONE GCC string set (no duplicates)
 *
 * Note:
 *  We intentionally emit this from a standalone assembly file to avoid the
 *  assembler warning that can occur when mixing C compilation and .comment.
 */

    /*
     * Emit into a private input section to avoid GAS warnings about changing
     * attributes of the special .comment section.
     * The linker script maps this into the final output section named .comment.
     */
    .section .comment.ef2,"MS",@progbits,1
    .byte 0
    .ascii "GCC: (GNU) 4.6 20120106 (prerelease)\0"
    .ascii "GCC: (GNU) 4.8\0"
    .previous
