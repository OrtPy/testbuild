cmake_minimum_required(VERSION 3.16)
project(lwplocal_so_only LANGUAGES C)

# v7a: try to match original DT_NEEDED list for drop-in replacement
option(EF2_V7A_FORCE_ORIGINAL_NEEDED \"Force original DT_NEEDED (armeabi-v7a)\" ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


## Keep exports under control (match original dynsym gradually)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# This project is intended to build ONLY liblwplocal.so (JNI) for Android/NDK.
# Build scripts in ./scripts set the Android toolchain and ABI(s).

option(EF2_USE_REAL_GLES "Use real GLES2 symbols (link GLESv2). OFF = keep lightweight stub implementation." ON)

add_library(ef2core STATIC
  src/platform/platform.c
  src/lodepng/lodepng.c
  src/util/timeutil.c
  src/util/decomp_compat.c
  src/curve/curve.c
  src/curve/curveclient.c
  src/renderer/renderer.c
  src/gles/gles_stub.c
  src/renderer/buffer.c
  src/renderer/program.c
  src/renderer/texture.c
  src/renderer/shaderfile.c
  src/renderer/meshgen.c
  src/renderer/rendererdata.c
  src/theme/theme.c
  src/theme/theme_tree.c
)

# lodepng (20131115) is compiled as C++ in the original binary (mangled C symbol names),
# but we intentionally disable the optional C++ std::vector API to avoid pulling the
# modern libc++ ABI into exports/NEEDED deps. The legacy std::vector-based symbols are
# still provided via compat_exports_armeabi_v7a.c (as stubs for now).
set_source_files_properties(src/lodepng/lodepng.c PROPERTIES
  COMPILE_DEFINITIONS "LODEPNG_NO_COMPILE_CPP"
  COMPILE_FLAGS "-fvisibility=hidden -fno-exceptions -fno-rtti"
)

target_include_directories(ef2core PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(ef2core PUBLIC
  EF2_PLATFORM_ANDROID=1
  EF2_USE_REAL_GLES=$<BOOL:${EF2_USE_REAL_GLES}>
)

add_library(lwplocal SHARED
  src/jni/curve_renderer_jni.c
)

# Add compatibility exports for 32-bit (armeabi-v7a) to match original liblwplocal.so
if (ANDROID_ABI STREQUAL "armeabi-v7a")
  target_sources(lwplocal PRIVATE src/compat/compat_exports_armeabi_v7a.c)
  target_sources(lwplocal PRIVATE src/compat/compat_lodepng_mangled_v7a.c)
endif()


# BEGIN v7a needed match
# The original (Sony) armeabi-v7a liblwplocal.so has DT_NEEDED entries for:
#   libc.so, libstdc++.so, libm.so, liblog.so, libGLESv2.so, libdl.so, libgnustl_shared.so
# Our toolchain/linker can accidentally pull extra deps (e.g., libatomic) when --as-needed is off.
# Here we: (1) enable --as-needed by default, (2) force-keep the legacy deps we want.
if(ANDROID AND ANDROID_ABI STREQUAL "armeabi-v7a")
  # Drop unused libs from DT_NEEDED (e.g., libatomic if not actually referenced)
  target_link_options(lwplocal PRIVATE "-Wl,--as-needed")

  if(EF2_V7A_FORCE_ORIGINAL_NEEDED)
    # libgnustl_shared.so (prebuilt from the original environment)
    set(_EF2_GNUSTL "${CMAKE_CURRENT_SOURCE_DIR}/prebuilts/armeabi-v7a/libgnustl_shared.so")
    if(EXISTS "${_EF2_GNUSTL}")
      add_library(ef2_gnustl_shared SHARED IMPORTED GLOBAL)
      set_target_properties(ef2_gnustl_shared PROPERTIES IMPORTED_LOCATION "${_EF2_GNUSTL}")
    else()
      message(WARNING "EF2_V7A_FORCE_ORIGINAL_NEEDED=ON but missing: ${_EF2_GNUSTL}")
    endif()

    # libstdc++.so (try to locate inside the NDK sysroot)
    set(_EF2_STDCPP "")
    if(DEFINED CMAKE_SYSROOT)
      file(GLOB _EF2_STDCPP_CANDS "${CMAKE_SYSROOT}/usr/lib/*/libstdc++.so")
      list(LENGTH _EF2_STDCPP_CANDS _EF2_STDCPP_CNT)
      if(_EF2_STDCPP_CNT GREATER 0)
        list(GET _EF2_STDCPP_CANDS 0 _EF2_STDCPP)
      endif()
    endif()
    if(_EF2_STDCPP STREQUAL "")
      # Fallback to find_library (cross sysroot aware)
      find_library(_EF2_STDCPP NAMES stdc++ )
    endif()

    # Force-keep these deps even if no symbols are referenced (to match original DT_NEEDED).
    # We temporarily disable --as-needed, add libs, then re-enable it.
    if(TARGET ef2_gnustl_shared)
      target_link_libraries(lwplocal PRIVATE "-Wl,--no-as-needed" ef2_gnustl_shared)
    endif()
    if(NOT _EF2_STDCPP STREQUAL "")
      target_link_libraries(lwplocal PRIVATE "-Wl,--no-as-needed" "${_EF2_STDCPP}")
    else()
      message(WARNING "Could not locate libstdc++.so in sysroot; DT_NEEDED may differ from original")
    endif()
    target_link_libraries(lwplocal PRIVATE "-Wl,--no-as-needed" dl "-Wl,--as-needed")
  endif()
endif()
# END v7a needed match


# Android system libs used by JNI + logging + AAssetManager_fromJava.
# (If you set EF2_USE_REAL_GLES=ON, you can additionally link GLESv2.)
if (ANDROID)
  target_link_libraries(lwplocal PRIVATE android log)
  target_link_libraries(lwplocal PRIVATE m)

  if (EF2_USE_REAL_GLES)
    target_link_libraries(lwplocal PRIVATE GLESv2)
  endif()
else()
  message(FATAL_ERROR "This project is for Android NDK builds only. Use scripts/ to build liblwplocal.so.")
endif()

set_target_properties(lwplocal PROPERTIES OUTPUT_NAME "lwplocal")

# CI-friendly diagnostics: show all lld errors, generate a link map, and add section-boundary symbols.
if (ANDROID)
  # Avoid lld truncating duplicate-symbol output, etc.
  target_link_options(lwplocal PRIVATE "-Wl,--error-limit=0")

  # Link map (per-ABI build dir).
  target_link_options(lwplocal PRIVATE "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/lwplocal_${ANDROID_ABI}.map")

  # Add __bss_start, _edata, _end (original dynsym has them).
  target_link_options(lwplocal PRIVATE "-Wl,-T,${CMAKE_CURRENT_SOURCE_DIR}/src/compat/section_boundary_syms.ld")
endif()
