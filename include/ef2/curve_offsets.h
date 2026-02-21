#pragma once

// Offsets used by the original liblwplocal.so implementation.
//
// The decompiled binary treats several C++ objects as raw blobs and accesses
// fields by fixed offsets (especially CurveClient and Curve). We keep these
// offsets centralized so Curve / Renderer / JNI can stay consistent.

// CurveClient offsets observed in liblwplocal.so decompilation.
enum {
  EF2_CC_OFF_X        = 4,    // int32
  EF2_CC_OFF_Y        = 8,    // int32
  EF2_CC_W            = 12,   // int32
  EF2_CC_H            = 16,   // int32

  EF2_CC_TIME0        = 24,   // double (timesince)
  EF2_CC_TIME1        = 32,   // double (timesince)

  EF2_CC_TOUCH_X      = 40,   // double
  EF2_CC_TOUCH_Y      = 48,   // double
  EF2_CC_DX           = 56,   // double
  EF2_CC_DY           = 64,   // double

  EF2_CC_TOUCH_ACTIVE = 80,   // uint8 (0/1)
};

// Curve offsets used by touch logic / layout in the decompilation.
enum {
  EF2_C_FLAGS         = 200,  // int32, used for divisor selection (flags & 1)
  EF2_C_ACC_X         = 208,  // double
  EF2_C_ACC_Y         = 216,  // double
  EF2_C_LAST_TIME     = 184,  // timespec32 (stored in _pad_0xB8)
  EF2_C_SLEEP_FACTOR  = 312,  // double
  EF2_C_TOUCH_COUNT   = 320,  // int32 (field_0x140)
  EF2_C_ROTATION      = 324,  // int32 (field_0x144)
  EF2_C_DENSITY       = 328,  // int32 (field_0x148)
};

// Additional Curve offsets used by render-time shader parameter updates.
enum { EF2_C_TIME100 = 304 };
