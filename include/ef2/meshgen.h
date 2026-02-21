#pragma once
#include "ef2/buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

// Matches decompiled renderer::createVertices / createIndices behavior.
// a2 = columns, a3 = rows (both >= 1).
// Vertices are (u,v) float pairs.
int ef2_mesh_createVertices(ef2_Buffer* out_vb, int cols, int rows);
int ef2_mesh_createIndices(ef2_Buffer* out_ib, int cols, int rows);

#ifdef __cplusplus
}
#endif
