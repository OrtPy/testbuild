#pragma once
#include "ef2/platform.h"
#include "ef2/common.h"
#include "ef2/curve.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Renderer (0x60) ABI layout
 * -------------------------
 * Static analysis of the 95KB liblwplocal.so shows CurveRenderer JNI wrappers store
 * a pointer to a native renderer object that is 0x60 bytes, and the last field
 * (+0x5c) is a Curve* used by requestColors/updateScreenLayout/touch/activate/etc.
 *
 * We keep this public struct as raw bytes to preserve offsets, and keep richer
 * runtime state in a side-car registry keyed by ef2_Renderer* (similar to Curve).
 */

typedef struct ef2_Renderer {
  uint8_t raw[0x60];
} ef2_Renderer;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
_Static_assert(sizeof(ef2_Renderer) == 0x60, "ef2_Renderer must be 0x60 bytes");
#endif

// Offsets inside ef2_Renderer.raw (validated by disassembly of renderer() at 0xA310).
enum {
  EF2_R_PTR_0x4C = 0x4c, // internal resource pointers (original frees these)
  EF2_R_PTR_0x50 = 0x50,
  EF2_R_PTR_0x54 = 0x54,
  EF2_R_PTR_0x58 = 0x58,
  EF2_R_CURVE_PTR = 0x5c, // Curve* (used by many JNI entrypoints)
};

// Lifecycle (mirrors original behaviour at a high level)
void ef2_Renderer_init(ef2_Renderer* r, ef2_AAssetManager* mgr);
void ef2_Renderer_deinit(ef2_Renderer* r);

// Frame/update entrypoints
void ef2_Renderer_render(ef2_Renderer* r, ef2_AAssetManager* mgr);

void ef2_Renderer_requestColors(ef2_Renderer* r, ef2_AAssetManager* mgr, int theme_id);
void ef2_Renderer_updateScreenLayout(ef2_Renderer* r, int x, int y, int w, int h, int screenW, int screenH);
void ef2_Renderer_touchDown(ef2_Renderer* r, float x, float y);
void ef2_Renderer_touch(ef2_Renderer* r, float x, float y);
void ef2_Renderer_touchUp(ef2_Renderer* r, float x, float y);

void ef2_Renderer_activate(ef2_Renderer* r);
void ef2_Renderer_deactivate(ef2_Renderer* r);
int  ef2_Renderer_getSleepRecommendation(ef2_Renderer* r);

#ifdef __cplusplus
}
#endif
