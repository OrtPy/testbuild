#pragma once

// Common C-compatible helpers for "cified" EF2 outputs.
// The goal is: compile cleanly as C11 on host platforms, while keeping
// decompiler-style pointer casts usable.

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

// Decompiler-style aliases
typedef uint8_t  _BYTE;
typedef uint16_t _WORD;
typedef uint32_t _DWORD;
typedef uint64_t _QWORD;

#ifndef __cplusplus
// Some decompilers refer to these in comments/annotations.
#define __usercall
#define __fastcall
#define __cdecl
#endif

#ifndef BYREF
#define BYREF
#endif

// Bit helpers often emitted by IDA-style pseudocode
#ifndef LODWORD
#define LODWORD(x) ((uint32_t)((uint64_t)(x) & 0xFFFFFFFFu))
#endif
#ifndef HIDWORD
#define HIDWORD(x) ((uint32_t)(((uint64_t)(x)) >> 32))
#endif
#ifndef SHIDWORD
#define SHIDWORD(x) ((int32_t)(((uint64_t)(x)) >> 32))
#endif

// Static assert (C11)
#define EF2_STATIC_ASSERT(cond, msg) _Static_assert((cond), msg)

// Safer min/max
#ifndef EF2_MIN
#define EF2_MIN(a,b) (( (a) < (b) ) ? (a) : (b))
#endif
#ifndef EF2_MAX
#define EF2_MAX(a,b) (( (a) > (b) ) ? (a) : (b))
#endif
