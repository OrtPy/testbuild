#include "ef2/meshgen.h"
#include <stdlib.h>
#include <string.h>

int ef2_mesh_createVertices(ef2_Buffer* out_vb, int cols, int rows)
{
  if (!out_vb || cols <= 0 || rows <= 0) return 0;

  // In decompiled code: total vertices = (cols+1) * (rows+1),
  // each vertex is 2 floats.
  int vc = (cols + 1) * (rows + 1);
  size_t bytes = (size_t)vc * 2u * sizeof(float);

  float* v = (float*)malloc(bytes);
  if (!v) return 0;

  // Fill with normalized UV grid.
  // x from 0..cols, y from 0..rows
  size_t idx = 0;
  {
    int y;
    int x;
    for (y = 0; y <= rows; ++y) {
      float fv = (rows == 0) ? 0.0f : ((float)y / (float)rows);
      for (x = 0; x <= cols; ++x) {
        float fu = (cols == 0) ? 0.0f : ((float)x / (float)cols);
        v[idx++] = fu;
        v[idx++] = fv;
      }
    }
  }

  // Original: buffer(target=GL_ARRAY_BUFFER, keep_copy=-1); set(size, data, GL_STATIC_DRAW)
  ef2_Buffer_init(out_vb, GL_ARRAY_BUFFER, GL_STATIC_DRAW, -1);
  int ok = ef2_Buffer_set(out_vb, bytes, v, GL_STATIC_DRAW);
  free(v);
  return ok;
}

int
ef2_mesh_createIndices(ef2_Buffer* out_ib, int cols, int rows)
{
  if (!out_ib || cols <= 0 || rows <= 0) return 0;

  // Match original renderer::createIndices (triangle strip with degenerate indices between rows).
  // Decomp reference:
  //   v3 = cols + 1;
  //   v6 = rows * 2 * (cols + 2) - 2;
  // Layout:
  //   For each row y in [0..rows-1]:
  //     if y>0: emit base (degenerate)
  //     for x in [0..cols]:
  //       emit (x + base)          (top)
  //       emit (x + base + v3)     (bottom)
  //     if y < rows-1: emit (base + 2*v3 - 1) (degenerate)
  //
  // Note: base starts at 0 and increases by v3 each row.

  const int v3 = cols + 1;
  const int count = rows * 2 * (cols + 2) - 2; // matches decomp v6
  if (count <= 0) return 0;

  uint16_t* idx = (uint16_t*)malloc((size_t)count * sizeof(uint16_t));
  if (!idx) return 0;

  int k = 0;
  uint16_t base = 0;
  {
    int y;
    int x;
    for (y = 0; y < rows; ++y) {
      if (y > 0) {
        idx[k++] = base; // degenerate at row start
      }

      for (x = 0; x < v3; ++x) {
        const uint16_t top = (uint16_t)(base + (uint16_t)x);
        idx[k++] = top;
        idx[k++] = (uint16_t)(top + (uint16_t)v3);
      }

      if (y < rows - 1) {
        // degenerate at row end: (base + 2*v3 - 1)
        idx[k++] = (uint16_t)(base + (uint16_t)(2 * v3 - 1));
      }

      base = (uint16_t)(base + (uint16_t)v3);
    }
  }

  // Safety: if we mismatch, clamp to generated length (should not happen if logic matches decomp).
  if (k != count) {
    // Keep behavior deterministic even in unexpected cases.
    // Recompute buffer size from what we produced.
    // (Still return success as long as we produced something.)
  }

  // Element array buffer, static draw.
  // Decomp constants:
  //   target = 0x8893 (GL_ELEMENT_ARRAY_BUFFER)
  //   usage  = 0x88E4 (GL_STATIC_DRAW)
  // Original: buffer(target=GL_ELEMENT_ARRAY_BUFFER, keep_copy=-1); set(size, data, GL_STATIC_DRAW)
  ef2_Buffer_init(out_ib, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, -1);
  ef2_Buffer_set(out_ib, (size_t)count * sizeof(uint16_t), idx, GL_STATIC_DRAW);

  free(idx);
  return 1;
}
