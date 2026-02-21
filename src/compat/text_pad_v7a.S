/*
 * Deterministic .text padding for layout tuning.
 *
 * Emits raw bytes into a dedicated subsection collected into the output
 * .text (via *(.text.*) in the linker script).
 *
 * Important:
 *  - Do NOT emit any functions (.fnstart/.type %function) here.
 *  - Keeping this as data-only avoids adding extra .ARM.exidx entries.
 */

    .section .text.ef2pad,"ax",%progbits
    .balign 4
    /* Initial guess: +0x2E0 bytes */
    .space 0x1bc, 0x00
