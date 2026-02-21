#include "ef2/buffer.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void ef2_Buffer_init(ef2_Buffer* b, GLenum target, GLenum usage, int keep_copy)
{
  if (!b) return;
  memset(b, 0, sizeof(*b));
  b->target = target;
  b->usage  = usage;
  // Preserve caller value (the original binary sometimes uses -1 as a sentinel).
  b->keep_copy = keep_copy;
  glGenBuffers(1, &b->id);
}

void ef2_Buffer_deinit(ef2_Buffer* b)
{
  if (!b) return;
  if (b->id) glDeleteBuffers(1, &b->id);
  b->id = 0;
  free(b->data);
  b->data = NULL;
  b->size = 0;
}

int ef2_Buffer_setData(ef2_Buffer* b, const void* data, size_t size)
{
  // Backwards-compatible helper. The original binary uses a per-upload usage
  // hint (buffer::set(size, data, usage)). Keep this existing signature and
  // forward to ef2_Buffer_set() using the currently configured b->usage.
  return ef2_Buffer_set(b, size, data, b->usage);
}

int ef2_Buffer_set(ef2_Buffer* b, size_t size, const void* data, GLenum usage)
{
  if (!b || !data || size == 0) return 0;
  b->size = size;
  b->usage = usage;

  glBindBuffer(b->target, b->id);
  glBufferData(b->target, (ptrdiff_t)size, data, usage);

  if (b->keep_copy) {
    void* copy = realloc(b->data, size);
    if (!copy) return 0;
    b->data = copy;
    memcpy(b->data, data, size);
  }
  return 1;
}

void ef2_Buffer_bindArray(const ef2_Buffer* b)
{
#if defined(EF2_PLATFORM_ANDROID) && EF2_PLATFORM_ANDROID && defined(EF2_USE_REAL_GLES) && EF2_USE_REAL_GLES
  if (!b || !b->id) return;
  glBindBuffer(GL_ARRAY_BUFFER, b->id);
#else
  (void)b;
#endif
}

void ef2_Buffer_bindElement(const ef2_Buffer* b)
{
#if defined(EF2_PLATFORM_ANDROID) && EF2_PLATFORM_ANDROID && defined(EF2_USE_REAL_GLES) && EF2_USE_REAL_GLES
  if (!b || !b->id) return;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b->id);
#else
  (void)b;
#endif
}

