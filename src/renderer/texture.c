#include "ef2/texture.h"
#include <stdlib.h>
#include <string.h>

// Thunk present in the original binary (see decompiled liblwplocal.so.c).
// It simply forwards to glTexParameteri.
extern void j_glTexParameteri(GLenum target, GLenum pname, GLint param);
extern void j_glBindTexture(GLenum target, GLuint texture);

void ef2_Texture_init(ef2_Texture* t, GLenum target, int keep_copy)
{
  if (!t) return;
  memset(t, 0, sizeof(*t));
  t->target = target;
  t->level = 0;
  t->internalformat = (GLint)GL_RGBA;
  t->format = (GLenum)GL_RGBA;
  t->type = (GLenum)GL_UNSIGNED_BYTE;
  t->keep_copy = keep_copy ? 1 : 0;
  glGenTextures(1, &t->id);
}

void ef2_Texture_deinit(ef2_Texture* t)
{
  if (!t) return;
  if (t->id) glDeleteTextures(1, &t->id);
  t->id = 0;
  free(t->pixels);
  t->pixels = NULL;
  t->size = 0;
  t->width = 0;
  t->height = 0;
}

int ef2_Texture_setRGBA8(ef2_Texture* t, int width, int height, const void* rgba, size_t size)
{
  if (!t || !rgba) return 0;
  if (width <= 0 || height <= 0) return 0;
  size_t expected = (size_t)width * (size_t)height * 4u;
  if (size != expected) return 0;

  t->width = width;
  t->height = height;
  t->size = size;

  glBindTexture(t->target, t->id);
  glTexImage2D(t->target, t->level, t->internalformat,
               (GLsizei)width, (GLsizei)height, 0,
               t->format, t->type, rgba);

  // Match decompiled texture::set behavior:
  // if pixels are provided, force nearest filtering.
  glTexParameteri(t->target, GL_TEXTURE_MAG_FILTER, (GLint)GL_NEAREST);
  j_glTexParameteri(t->target, GL_TEXTURE_MIN_FILTER, (GLint)GL_NEAREST);

  if (t->keep_copy) {
    void* copy = realloc(t->pixels, size);
    if (!copy) return 0;
    t->pixels = copy;
    memcpy(t->pixels, rgba, size);
  }
  return 1;
}

void ef2_Texture_bind(ef2_Texture* t, int unit)
{
  if (!t) return;
  // Decompiled texture::bind: glActiveTexture(unit + GL_TEXTURE0);
  if (unit < 0) unit = 0;
  glActiveTexture((GLenum)(GL_TEXTURE0 + (GLenum)unit));
  // Then bind GL_TEXTURE_2D using the thunk present in the original.
  j_glBindTexture(GL_TEXTURE_2D, t->id);
}
