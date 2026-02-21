#include "ef2/gles.h"

#if !(EF2_USE_REAL_GLES && EF2_PLATFORM_ANDROID)

static GLuint g_next_id = 1;

static GLuint alloc_id(void) {
  if (g_next_id == 0) g_next_id = 1;
  return g_next_id++;
}

void glGenBuffers(GLsizei n, GLuint* buffers)
{
  if (!buffers || n <= 0) return;
  for (GLsizei i = 0; i < n; ++i) buffers[i] = alloc_id();
}

void glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
  (void)n; (void)buffers;
}

void glBindBuffer(GLenum target, GLuint buffer)
{
  (void)target; (void)buffer;
}

void glBufferData(GLenum target, ptrdiff_t size, const void* data, GLenum usage)
{
  (void)target; (void)size; (void)data; (void)usage;
}

void glBufferSubData(GLenum target, ptrdiff_t offset, ptrdiff_t size, const void* data)
{
  (void)target; (void)offset; (void)size; (void)data;
}

void glGenTextures(GLsizei n, GLuint* textures)
{
  if (!textures || n <= 0) return;
  for (GLsizei i = 0; i < n; ++i) textures[i] = alloc_id();
}

void glDeleteTextures(GLsizei n, const GLuint* textures)
{
  (void)n; (void)textures;
}

void glBindTexture(GLenum target, GLuint texture)
{
  (void)target; (void)texture;
}

void glActiveTexture(GLenum texture)
{
  (void)texture;
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat,
                  GLsizei width, GLsizei height, GLint border,
                  GLenum format, GLenum type, const void* pixels)
{
  (void)target; (void)level; (void)internalformat;
  (void)width; (void)height; (void)border;
  (void)format; (void)type; (void)pixels;
}

void glTexParameteri(GLenum target, GLenum pname, GLint param)
{
  (void)target; (void)pname; (void)param;
}
#endif

// The original binary contains many "j_gl*" thunks; add the ones we can
// confirm from the decompiled output. These should exist regardless of
// whether we link against real GLES or a stub implementation.
void j_glTexParameteri(GLenum target, GLenum pname, GLint param)
{
  glTexParameteri(target, pname, param);
}

void j_glBindTexture(GLenum target, GLuint texture)
{
  glBindTexture(target, texture);
}

void j_glActiveTexture(GLenum texture)
{
  glActiveTexture(texture);
}
