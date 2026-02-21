#include "ef2/rendererdata.h"

#include "ef2/platform.h"

#include <stdint.h>
#include <string.h>

// The original binary exposes Curve::updateRenderer (mangled as a method but
// effectively called as (rendererdata*, Curve*)).
// For binary matching we keep the full implementation in the exported symbol
// (src/compat/compat_exports_armeabi_v7a.c) and forward the C helper here.
extern ef2_rendererdata* ef2_compat_Curve_updateRenderer(ef2_rendererdata* out, ef2_Curve* curve)
    __asm__("_ZN5Curve14updateRendererEv");

void ef2_rendererdata_init(rendererdata* out)
{
  if (!out) return;
  memset(out, 0, sizeof(*out));
  out->flt_0x44 = 0.0f;
  out->flt_0x64 = 0.0f;
}

void ef2_rendererdata_fillFromCurve(rendererdata* out, Curve* curve)
{
  (void)ef2_compat_Curve_updateRenderer((ef2_rendererdata*)out, (ef2_Curve*)curve);
}
