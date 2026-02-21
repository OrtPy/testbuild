#pragma once

#include "ef2/common.h"
#include "ef2/gles.h"
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ef2_Texture {
  GLuint id;
  GLenum target;
  GLint  level;
  GLint  internalformat;
  GLenum format;
  GLenum type;
  int    width;
  int    height;
  size_t size;
  void*  pixels;     // heap-owned copy for host debugging (NULL if not kept)
  int    keep_copy;
} ef2_Texture;

void ef2_Texture_init(ef2_Texture* t, GLenum target, int keep_copy);
void ef2_Texture_deinit(ef2_Texture* t);

// Upload/replace texture content.
// Host: stores a copy if keep_copy.
int ef2_Texture_setRGBA8(ef2_Texture* t, int width, int height, const void* rgba, size_t size);

// Bind texture to texture unit index (0 == GL_TEXTURE0).
void ef2_Texture_bind(ef2_Texture* t, int unit);


#ifdef __cplusplus
}
#endif
