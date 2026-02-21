#pragma once
#include "ef2/common.h"
#include "ef2/gles.h"
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ef2_Buffer {
  GLuint id;
  GLenum target;
  GLenum usage;
  size_t size;
  void*  data;     // heap-owned copy for host debugging (NULL if not kept)
  int    keep_copy;
} ef2_Buffer;

void ef2_Buffer_init(ef2_Buffer* b, GLenum target, GLenum usage, int keep_copy);
void ef2_Buffer_deinit(ef2_Buffer* b);
int  ef2_Buffer_setData(ef2_Buffer* b, const void* data, size_t size);

// Closer to the original binary's buffer::set(size, data, usage) API.
// This allows per-upload usage hints (e.g. GL_STATIC_DRAW / GL_DYNAMIC_DRAW).
int  ef2_Buffer_set(ef2_Buffer* b, size_t size, const void* data, GLenum usage);

// Bind helpers (match original draw flow).
void ef2_Buffer_bindArray(const ef2_Buffer* b);
void ef2_Buffer_bindElement(const ef2_Buffer* b);

#ifdef __cplusplus
}
#endif
