#include <stddef.h>
#include <stdio.h>
#include "ef2/curve.h"
#include "ef2/curve_offsets.h"

#define OFFSETOF(type, field) ((size_t)offsetof(type, field))

int main(void) {
#if defined(__arm__) || defined(__aarch64__) || defined(__i386__) || defined(__x86_64__)
  printf("sizeof(CurveClient)=0x%zx\n", sizeof(CurveClient));
  printf("sizeof(Curve)=0x%zx\n", sizeof(Curve));
#endif

  #if UINTPTR_MAX == 0xffffffffu
// Only fields that are explicitly named:
  printf("Curve.client_0x8 offset=0x%zx (expected 0x08)\n", OFFSETOF(Curve, client_0x8));
  printf("Curve.ptr_0xB0 offset=0x%zx (expected 0xB0)\n", OFFSETOF(Curve, ptr_0xB0));
  printf("Curve.field_0xB4 offset=0x%zx (expected 0xB4)\n", OFFSETOF(Curve, field_0xB4));
  printf("Curve._pad_0xB8 offset=0x%zx (expected 0xB8)\n", OFFSETOF(Curve, _pad_0xB8));

  printf("CurveClient.off_x_0x4 offset=0x%zx (expected 0x04)\n", OFFSETOF(CurveClient, off_x_0x4));
  printf("CurveClient.touch_x_0x28 offset=0x%zx (expected 0x28)\n", OFFSETOF(CurveClient, touch_x_0x28));
  printf("CurveClient.dx_0x38 offset=0x%zx (expected 0x38)\n", OFFSETOF(CurveClient, dx_0x38));
  printf("CurveClient.touch_active_0x50 offset=0x%zx (expected 0x50)\n", OFFSETOF(CurveClient, touch_active_0x50));

  // Also print decomp-anchored constants:
  printf("EF2_C_LAST_TIME=0x%X\n", EF2_C_LAST_TIME);
  printf("EF2_CC_DX=0x%X\n", EF2_CC_DX);
#else
  printf("host build is %zu-bit; offsetof() reflects host pointer size\n", (size_t)(8*sizeof(void*)) );
  printf("32-bit layout is validated at Android build-time via EF2_STATIC_ASSERT in include/ef2/curve.h\n");
#endif
  return 0;
}
