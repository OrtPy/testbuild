#pragma once

#include "ef2/common.h"
#include "ef2/curve.h"
#include "ef2/timeutil.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rendererdata {
  unsigned char field_0x0[1];
  unsigned char _pad_0x1[7];
  /*
   * NOTE (v7a): keep this struct 0x9C bytes like the original.
   * Using 'double' here makes the struct 8-byte aligned on ARMv7, so the
   * compiler rounds sizeof(rendererdata) up to 0xA0 and breaks layout checks.
   * Store the 8-byte value as raw bytes and load/store via memcpy.
   */
  unsigned char time_0x8[8]; // raw bits of a double (seconds)
  unsigned char field_0x10[4];
  unsigned char _pad_0x14[4];
  unsigned char field_0x18[4];
  unsigned char field_0x1C[4];
  unsigned char field_0x20[4];
  unsigned char field_0x24[4];
  unsigned char field_0x28[4];
  unsigned char field_0x2C[4];
  unsigned char field_0x30[4];
  unsigned char field_0x34[4];
  unsigned char field_0x38[4];
  unsigned char field_0x3C[4];
  unsigned char field_0x40[4];
  float flt_0x44;
  unsigned char field_0x48[4];
  unsigned char field_0x4C[4];
  unsigned char field_0x50[4];
  unsigned char field_0x54[4];
  unsigned char field_0x58[4];
  unsigned char field_0x5C[4];
  unsigned char field_0x60[4];
  float flt_0x64;
  unsigned char field_0x68[1];
  unsigned char field_0x69[1];
  unsigned char _pad_0x6A[2];
  unsigned char field_0x6C[4];
  unsigned char field_0x70[4];
  unsigned char field_0x74[4];
  unsigned char field_0x78[4];
  unsigned char field_0x7C[4];
  unsigned char field_0x80[4];
  unsigned char field_0x84[4];
  unsigned char field_0x88[4];
  unsigned char field_0x8C[4];
  unsigned char field_0x90[4];
  unsigned char field_0x94[4];
  unsigned char field_0x98[4];
} rendererdata;

// Compatibility alias for generated compat shims.
typedef rendererdata ef2_rendererdata;


EF2_STATIC_ASSERT(sizeof(rendererdata) == 0x9C, "rendererdata size mismatch");

void ef2_rendererdata_init(rendererdata* out);
void ef2_rendererdata_fillFromCurve(rendererdata* out, Curve* curve);

#ifdef __cplusplus
}
#endif