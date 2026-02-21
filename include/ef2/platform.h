#pragma once

#include "ef2/common.h"

// Platform abstraction (Android-first for liblwplocal.so builds).
//
// This project builds for Android NDK. Therefore, when EF2_PLATFORM_ANDROID=1,
// we include real NDK headers.

#ifndef EF2_PLATFORM_ANDROID
#define EF2_PLATFORM_ANDROID 0
#endif

#if EF2_PLATFORM_ANDROID
  #include <android/asset_manager.h>
  #include <android/log.h>
  typedef AAssetManager ef2_AAssetManager;
  typedef AAsset        ef2_AAsset;

  // Logging
  // NOTE: Avoid __android_log_vprint to match the original symbol set.
  //
  // Final/repro builds should not embed debug strings.
  #ifndef EF2_DEBUG_LOGS
    #define EF2_DEBUG_LOGS 0
  #endif

  #if EF2_DEBUG_LOGS
    #ifndef ef2_log_print
      #define ef2_log_print(prio, tag, fmt, ...) \
        __android_log_print((prio), ((tag) ? (tag) : "lwplocal"), (fmt), ##__VA_ARGS__)
    #endif
  #else
    #ifndef ef2_log_print
      #define ef2_log_print(...) ((void)0)
    #endif
  #endif
#else
  // Host stubs (not used by this project)
  typedef struct ef2_AAssetManager { const char* base_path; } ef2_AAssetManager;
  typedef struct ef2_AAsset { void* data; size_t size; } ef2_AAsset;

  // Logging (host)
  int ef2_log_print(int prio, const char* tag, const char* fmt, ...);
#endif

// Asset IO
ef2_AAsset* ef2_AAssetManager_open(ef2_AAssetManager* mgr, const char* filename, int mode);
const void*  ef2_AAsset_getBuffer(ef2_AAsset* asset);
size_t       ef2_AAsset_getLength(ef2_AAsset* asset);
void         ef2_AAsset_close(ef2_AAsset* asset);

// Time
int ef2_clock_gettime_monotonic(struct timespec* out);
