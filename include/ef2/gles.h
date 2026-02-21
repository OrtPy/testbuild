#pragma once
#include "ef2/platform.h"
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EF2_USE_REAL_GLES
#define EF2_USE_REAL_GLES 0
#endif

#if EF2_USE_REAL_GLES && EF2_PLATFORM_ANDROID
  #include <GLES2/gl2.h>
#else
  // Minimal GLES2-compatible types/constants for host builds.
  typedef uint32_t GLenum;
  typedef uint8_t  GLboolean;
  typedef uint32_t GLbitfield;
  typedef int8_t   GLbyte;
  typedef int16_t  GLshort;
  typedef int32_t  GLint;
  typedef int32_t  GLsizei;
  typedef uint8_t  GLubyte;
  typedef uint16_t GLushort;
  typedef uint32_t GLuint;
  typedef float    GLfloat;

  // A very small subset of enums used by the decompiled renderer.
  enum {
    GL_ARRAY_BUFFER         = 0x8892,
    GL_ELEMENT_ARRAY_BUFFER = 0x8893,
    GL_STATIC_DRAW          = 0x88E4,
    GL_DYNAMIC_DRAW         = 0x88E8,

    GL_TEXTURE_2D           = 0x0DE1,

    GL_TEXTURE0            = 0x84C0,
    GL_RGBA                 = 0x1908,
    GL_UNSIGNED_BYTE        = 0x1401,

    // Texture parameters (used by the decompiled texture::set)
    GL_TEXTURE_MAG_FILTER   = 0x2800,
    GL_TEXTURE_MIN_FILTER   = 0x2801,
    GL_NEAREST              = 0x2600,
    GL_LINEAR               = 0x2601,
  };

  void glGenBuffers(GLsizei n, GLuint* buffers);
  void glDeleteBuffers(GLsizei n, const GLuint* buffers);
  void glBindBuffer(GLenum target, GLuint buffer);
  void glBufferData(GLenum target, ptrdiff_t size, const void* data, GLenum usage);
  void glBufferSubData(GLenum target, ptrdiff_t offset, ptrdiff_t size, const void* data);

  void glGenTextures(GLsizei n, GLuint* textures);
  void glDeleteTextures(GLsizei n, const GLuint* textures);
  void glBindTexture(GLenum target, GLuint texture);
  void glActiveTexture(GLenum texture);
  void glTexImage2D(GLenum target, GLint level, GLint internalformat,
                    GLsizei width, GLsizei height, GLint border,
                    GLenum format, GLenum type, const void* pixels);

  void glTexParameteri(GLenum target, GLenum pname, GLint param);
#endif

  // --- j_gl* thunks ---
  // The original binary contains small wrapper functions (named j_gl*) that
  // forward to the corresponding GLES entry points. Some of our decompiled
  // code paths still call these names directly, so we provide prototypes here
  // to avoid implicit declarations and keep call sites close to the decomp.
  void j_glTexParameteri(GLenum target, GLenum pname, GLint param);
  void j_glBindTexture(GLenum target, GLuint texture);
  void j_glActiveTexture(GLenum texture);

#ifdef __cplusplus
}
#endif
