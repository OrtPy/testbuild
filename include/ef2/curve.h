#pragma once

#include "ef2/platform.h"
#include "ef2/common.h"

#ifdef __cplusplus
extern "C" {
#endif

// forward decl (defined in ef2/theme.h)
typedef struct ef2_theme_parameter ef2_theme_parameter;
typedef struct ef2_theme_map ef2_theme_map;

// ---- C versions of decompiled "classes" ----

typedef struct CurveClient {
  // NOTE: Layout is derived from the original liblwplocal.so decompilation:
  // - operator new(0x60) for CurveClient
  // - Curve::touchDown uses offsets: +4,+8,+0x28,+0x30,+0x38,+0x40,+0x50
  //
  // We keep unknown fields but preserve byte-accurate offsets.
  uint32_t unk0_0x0;          // [0x00] unknown (likely vptr in C++)
  int32_t  off_x_0x4;         // [0x04]
  int32_t  off_y_0x8;         // [0x08]
  int32_t  w_0xC;             // [0x0C]
  int32_t  h_0x10;            // [0x10]
  uint32_t unk_0x14;          // [0x14]
  double   t0_0x18;           // [0x18]
  double   t1_0x20;           // [0x20]
  double   touch_x_0x28;      // [0x28]
  double   touch_y_0x30;      // [0x30]
  double   dx_0x38;           // [0x38]
  double   dy_0x40;           // [0x40]
  uint8_t  _pad_0x48[8];      // [0x48..0x4F]
  uint8_t  touch_active_0x50; // [0x50]
  uint8_t  _pad_0x51[0x0F];   // [0x51..0x5F]
} CurveClient;

typedef struct Curve {
  // NOTE: Layout is derived from the original liblwplocal.so decompilation:
  // - renderer::init uses operator new(0x178u) for Curve
  // - CurveClient* stored at offset 0x08
  // - std::_Rb_tree_impl starts at offset 0x20
  // - clock_gettime stores timespec at offset 0xB8
  //
  // IMPORTANT:
  //  - RPC harness "hint size" for dumps is 0x180, but the original allocation
  //    for Curve is 0x178. We keep sizeof(Curve)=0x178 here.
  uint8_t     _pad_0x0[8];              // [0x00..0x07]
  CurveClient* client_0x8;              // [0x08..0x0B]
  uint8_t     _pad_0xC[0x14];           // [0x0C..0x1F]

  // std::_Rb_tree_impl base (starts at 0x20)
  uint8_t     rb_tree_impl_0x20[0x18];  // [0x20..0x37]

  uint8_t     _pad_0x38[0x78];          // [0x38..0xAF]
  void*       ptr_0xB0;                 // [0xB0..0xB3]
  uint8_t     field_0xB4[4];            // [0xB4..0xB7]
  uint8_t     _pad_0xB8[8];             // [0xB8..0xBF] struct timespec (32-bit)

  uint8_t field_0xC0[4];                // [0xC0..0xC3]
  uint8_t field_0xC4[4];                // [0xC4..0xC7]
  uint8_t field_0xC8[4];                // [0xC8..0xCB]
  uint8_t field_0xCC[4];                // [0xCC..0xCF]
  uint8_t field_0xD0[4];                // [0xD0..0xD3]
  uint8_t field_0xD4[4];                // [0xD4..0xD7]
  uint8_t field_0xD8[4];                // [0xD8..0xDB]
  uint8_t field_0xDC[4];                // [0xDC..0xDF]
  uint8_t _pad_0xE0[12];                // [0xE0..0xEB]
  uint8_t field_0xEC[4];                // [0xEC..0xEF]
  uint8_t field_0xF0[4];                // [0xF0..0xF3]
  uint8_t _pad_0xF4[4];                 // [0xF4..0xF7]
  uint8_t field_0xF8[4];                // [0xF8..0xFB]
  uint8_t _pad_0xFC[4];                 // [0xFC..0xFF]
  uint8_t field_0x100[4];               // [0x100..0x103]
  uint8_t field_0x104[4];               // [0x104..0x107]
  uint8_t field_0x108[4];               // [0x108..0x10B]
  uint8_t field_0x10C[4];               // [0x10C..0x10F]
  uint8_t _pad_0x110[48];               // [0x110..0x13F]
  uint8_t field_0x140[4];               // [0x140..0x143]
  uint8_t field_0x144[4];               // [0x144..0x147]
  uint8_t field_0x148[4];               // [0x148..0x14B]
  uint8_t field_0x14C[4];               // [0x14C..0x14F]
  uint8_t field_0x150[4];               // [0x150..0x153]
  uint8_t field_0x154[4];               // [0x154..0x157]
  uint8_t field_0x158[4];               // [0x158..0x15B]

  uint8_t field_0x15C[0x0C];            // [0x15C..0x167]
  uint8_t field_0x168[4];               // [0x168..0x16B]
  uint8_t field_0x16C[4];               // [0x16C..0x16F]
  uint8_t field_0x170[4];               // [0x170..0x173]
  uint8_t _pad_0x174[4];                // [0x174..0x177]
} Curve;

// Size sanity checks (from localtypes output).
// The original binary is ARM32, so these are only enforced on 32-bit builds.
#if UINTPTR_MAX == 0xFFFFFFFFu
EF2_STATIC_ASSERT(sizeof(CurveClient) == 0x60, "CurveClient size mismatch");
EF2_STATIC_ASSERT(sizeof(Curve) == 0x178, "Curve size mismatch");
#endif

// ---- Compatibility typedefs ----
// Some generated compat export shims refer to ef2_Curve / ef2_CurveClient names.
// Keep these aliases to avoid build breaks without changing ABI/layout.
typedef Curve       ef2_Curve;
typedef CurveClient ef2_CurveClient;


// ---- API ----
void ef2_CurveClient_init(CurveClient* self);
void ef2_Curve_init(Curve* self, ef2_AAssetManager* mgr);
void ef2_Curve_deinit(Curve* self);

// "virtual"/methods converted to free functions.
void ef2_Curve_requestColors(Curve* self, ef2_AAssetManager* mgr, int theme_id);

// Screen/layout + lifecycle
void ef2_Curve_updateScreenLayout(Curve* self, int x, int y, int w, int h, int screenW, int screenH);
void ef2_Curve_activate(Curve* self);
void ef2_Curve_deactivate(Curve* self);
int  ef2_Curve_getSleepRecommendation(Curve* self);

// Theme accessors (loaded by requestColors)
int  ef2_Curve_themeGet(Curve* self, const char* key, ef2_theme_parameter* out);
// Returns a non-owning pointer to the internal theme map (valid until deinit).
int  ef2_Curve_themeMap(const Curve* self, const ef2_theme_map** out_map);

// Noise buffer accessors (pre-decoded RGBA8, when available)
int  ef2_Curve_getNoiseRGBA(const Curve* self, const uint8_t** out_rgba,
                            int* out_w, int* out_h, int* out_len);

// Touch input
void ef2_Curve_touchDown(Curve* self, float x, float y);
void ef2_Curve_touch(Curve* self, float x, float y);
void ef2_Curve_touchUp(Curve* self, float x, float y);

#ifdef __cplusplus
}
#endif