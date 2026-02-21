#pragma once

#include "ef2/platform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ef2_timespec32 {
  int32_t tv_sec;
  int32_t tv_nsec;
} ef2_timespec32;

EF2_STATIC_ASSERT(sizeof(ef2_timespec32) == 8, "ef2_timespec32 must be 8 bytes");

// Fill an ef2_timespec32 with current monotonic time.
int ef2_clock_gettime_monotonic32(ef2_timespec32* out);

// Decompiler-emitted helper (kept name for compatibility)
double timesince(const ef2_timespec32* start, int unused);

#ifdef __cplusplus
}
#endif
