.syntax unified
.text

.global ffi_call_words
.type ffi_call_words, %function

// uint64_t ffi_call_words(void* fn, const uint32_t* args, int argc_words);
// - argc_words words are passed.
// - First 4 words -> r0-r3
// - Remaining words -> stack [sp], [sp+4], ...
// - Returns r0/r1 packed as uint64_t
ffi_call_words:
    push {r4-r11, lr}

    mov r4, r0      @ fn
    mov r5, r1      @ args
    mov r6, r2      @ argc

    mov r0, #0
    mov r1, #0
    mov r2, #0
    mov r3, #0

    cmp r6, #1
    blt 1f
    ldr r0, [r5, #0]
    cmp r6, #2
    blt 1f
    ldr r1, [r5, #4]
    cmp r6, #3
    blt 1f
    ldr r2, [r5, #8]
    cmp r6, #4
    blt 1f
    ldr r3, [r5, #12]
1:
    subs r7, r6, #4
    movle r7, #0

    mov r8, r7, lsl #2      @ extra bytes
    add r8, r8, #7
    bic r8, r8, #7          @ align to 8

    sub sp, sp, r8

    cmp r7, #0
    beq 3f

    add r11, r5, #16        @ args + 4 words
    mov r10, #0
2:
    ldr r9, [r11], #4
    str r9, [sp, r10, lsl #2]
    add r10, r10, #1
    cmp r10, r7
    blt 2b

3:
    blx r4

    add sp, sp, r8
    pop {r4-r11, pc}
