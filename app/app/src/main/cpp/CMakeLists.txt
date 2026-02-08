cmake_minimum_required(VERSION 3.10)
project(lwpbridge C CXX ASM)

# RPC + ARM32 word-call helpers
add_library(lwpbridge SHARED
        lwpbridge_jni.c
        elf_exports.c
        ffi_call_arm32.S
)

target_compile_features(lwpbridge PRIVATE c_std_11)

target_include_directories(lwpbridge PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lwpbridge
        android
        log
        dl
)

# Proxy liblwplocal_proxy.so
#  - Exposes the same JNI entrypoints as the Sony original (liblwplocal.so).
#  - Forwards to the original Sony library packaged as liblwplocal.so (jniLibs).
add_library(lwplocal_proxy SHARED
        lwplocal_proxy.cpp
)

target_compile_features(lwplocal_proxy PRIVATE cxx_std_17)

target_link_libraries(lwplocal_proxy
        log
        dl
)
