#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include "ef2/platform.h"
#include <time.h>

#include <errno.h>

#if EF2_PLATFORM_ANDROID
  #include <android/log.h>
  #include <android/asset_manager.h>
  #include <time.h>
#endif

#if !EF2_PLATFORM_ANDROID
int ef2_log_print(int prio, const char* tag, const char* fmt, ...)
{
  if (!tag) tag = "lwplocal";

  va_list ap;
  va_start(ap, fmt);

  fprintf(stderr, "[%s] ", tag);
  int n = vfprintf(stderr, fmt, ap);
  fputc("\n"[0], stderr);

  va_end(ap);
  return n;
}
#endif

#if EF2_PLATFORM_ANDROID

ef2_AAsset* ef2_AAssetManager_open(ef2_AAssetManager* mgr, const char* filename, int mode)
{
  if (!mgr || !filename) return NULL;
  return (ef2_AAsset*)AAssetManager_open((AAssetManager*)mgr, filename, mode);
}

const void* ef2_AAsset_getBuffer(ef2_AAsset* asset)
{
  if (!asset) return NULL;
  return AAsset_getBuffer((AAsset*)asset);
}

size_t ef2_AAsset_getLength(ef2_AAsset* asset)
{
  if (!asset) return 0;
  return (size_t)AAsset_getLength((AAsset*)asset);
}

void ef2_AAsset_close(ef2_AAsset* asset)
{
  if (!asset) return;
  AAsset_close((AAsset*)asset);
}


#else // !EF2_PLATFORM_ANDROID

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

static char* ef2__path_join(const char* base, const char* rel) {
  if (!base || !rel) return NULL;
  const size_t bl = strlen(base);
  const size_t rl = strlen(rel);
  // +2 for '/' and '\0'
  char* out = (char*)malloc(bl + 1 + rl + 1);
  if (!out) return NULL;
  memcpy(out, base, bl);
  out[bl] = '/';
  memcpy(out + bl + 1, rel, rl);
  out[bl + 1 + rl] = '\0';
  return out;
}

ef2_AAsset* ef2_AAssetManager_open(ef2_AAssetManager* mgr, const char* filename, int mode) {
  (void)mode;
  if (!mgr || !mgr->base_path || !filename) return NULL;

  char* path = ef2__path_join(mgr->base_path, filename);
  if (!path) return NULL;

  int fd = open(path, O_RDONLY);
  free(path);
  if (fd < 0) {
    return NULL;
  }

  struct stat st;
  if (fstat(fd, &st) != 0 || st.st_size < 0) {
    close(fd);
    return NULL;
  }

  size_t size = (size_t)st.st_size;
  uint8_t* data = (uint8_t*)malloc(size ? size : 1);
  if (!data) {
    close(fd);
    return NULL;
  }

  size_t off = 0;
  while (off < size) {
    ssize_t r = read(fd, data + off, size - off);
    if (r < 0) {
      if (errno == EINTR) continue;
      free(data);
      close(fd);
      return NULL;
    }
    if (r == 0) break;
    off += (size_t)r;
  }
  close(fd);

  if (off != size) {
    free(data);
    return NULL;
  }

  // Avoid importing calloc (original binary does not reference it).
  ef2_AAsset* a = (ef2_AAsset*)malloc(sizeof(ef2_AAsset));
  if (!a) {
    free(data);
    return NULL;
  }
  memset(a, 0, sizeof(*a));
  a->data = data;
  a->size = size;
  return a;
}

const void* ef2_AAsset_getBuffer(ef2_AAsset* asset) {
  return asset ? (const void*)asset->data : NULL;
}

size_t ef2_AAsset_getLength(ef2_AAsset* asset) {
  return asset ? asset->size : 0;
}

void ef2_AAsset_close(ef2_AAsset* asset) {
  if (!asset) return;
  free(asset->data);
  free(asset);
}



#endif

int ef2_clock_gettime_monotonic(struct timespec* out)
{
  if (!out) return -1;
  return clock_gettime(CLOCK_MONOTONIC, out);
}