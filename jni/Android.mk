LOCAL_PATH := $(call my-dir)

# ------------------------------
# Static: lodepng (C++ wrapper)
# ------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE := lodepng_cpp

LOCAL_SRC_FILES :=   ../src/lodepng/lodepng.cpp

LOCAL_C_INCLUDES +=   $(LOCAL_PATH)/../include

LOCAL_CFLAGS += -fPIC -fno-ident
LOCAL_CFLAGS += -fno-ident
LOCAL_CPPFLAGS += -fno-ident
LOCAL_CFLAGS += -fno-ident

# Build with the old GNU libstdc++ ABI (NDK r9d)
LOCAL_CPPFLAGS += -std=gnu++98 -fno-ident
# Export lodepng symbols (other exports are controlled via version-script on the shared lib)
LOCAL_CPPFLAGS += -fvisibility=default -fno-ident

include $(BUILD_STATIC_LIBRARY)


# ------------------------------
# Shared: liblwplocal.so
# ------------------------------
include $(CLEAR_VARS)

LOCAL_MODULE := lwplocal
LOCAL_MODULE_FILENAME := liblwplocal

###
### NOTE (perfect-match work):
###
### The stock Sony binary's dynsym / .rel.plt ordering indicates that many
### renderer/theme-related symbols are pulled in before the Android Asset
### Manager symbols.
###
### Because ld.gold largely finalizes dynsym and .rel.plt in the order it
### encounters undefined references while scanning input objects, the order of
### LOCAL_SRC_FILES has a direct impact on the resulting symbol/relocation
### ordering.
###
### To reduce early AAsset* pull-in (AAssetManager_open, AAsset_*), we link
### platform.c later than renderer/theme.
###
LOCAL_SRC_FILES := \
  ../src/compat/imports_anchor_v7a.cpp \
  ../src/compat/libgcc_anchor_v7a.c \
  ../src/compat/reldyn_anchor_v7a.cpp \
  ../src/util/timeutil.c \
  ../src/util/decomp_compat.c \
  ../src/curve/curve.c \
  ../src/curve/curveclient.c \
  ../src/renderer/renderer.c \
  ../src/gles/gles_stub.c \
  ../src/renderer/buffer.c \
  ../src/renderer/program.c \
  ../src/renderer/texture.c \
  ../src/renderer/shaderfile.c \
  ../src/renderer/meshgen.c \
  ../src/renderer/rendererdata.c \
  ../src/theme/theme.c \
  ../src/theme/theme_tree.c \
  ../src/platform/platform.c \
  ../src/jni/curve_renderer_jni.c \
  ../src/compat/cpp_shims_v7a.cpp \
  ../src/compat/bss_pad_v7a.c \
  ../src/compat/init_array_pad_v7a.c \
  ../src/compat/compat_exports_armeabi_v7a.c \
  ../src/compat/gcc_comment_ref.S \
  ../src/compat/text_pad_v7a.S \
  ../src/compat/data_ef2pad_v7a.c


LOCAL_C_INCLUDES +=   $(LOCAL_PATH)/../include

# NOTE:
# LOCAL_CFLAGS is used for both C and C++ compilation in ndk-build.
LOCAL_CFLAGS += -fvisibility=hidden -fPIC -fno-ident
LOCAL_CFLAGS += -fno-ident

# Build C++ sources with the old GNU libstdc++ ABI (NDK r9d)
LOCAL_CPPFLAGS += -std=gnu++98 -fno-ident

# Link whole lodepng objects so its exports are present
LOCAL_CFLAGS += -DEF2_DEBUG_LOGS=0
LOCAL_WHOLE_STATIC_LIBRARIES := lodepng_cpp

LOCAL_SHARED_LIBRARIES := gnustl_shared

LOCAL_LDFLAGS += -Wl,-soname,liblwplocal.so
LOCAL_LDFLAGS += -mthumb -mfloat-abi=softfp -mfpu=vfpv3-d16
LOCAL_LDFLAGS += -Wl,-Bsymbolic -Wl,-z,relro -Wl,-z,now
LOCAL_LDFLAGS += -Wl,--hash-style=sysv
LOCAL_LDFLAGS += -Wl,--build-id=none
LOCAL_LDFLAGS += -Wl,--no-as-needed
LOCAL_LDFLAGS += -Wl,--version-script=$(LOCAL_PATH)/exports_armeabi_v7a.map
LOCAL_LDFLAGS += -Wl,--undefined=ef2_imports_anchor_v7a
LOCAL_LDFLAGS += -Wl,--undefined=ef2_reldyn_anchor_v7a
LOCAL_LDFLAGS += -Wl,--undefined=ef2_libgcc_anchor_v7a

### Link layout modes
#
# The "compat" linker script hard-fixes output section addresses to match the
# stock Sony binary. This is required for perfect-match builds.
#
# During implementation work (filling internal functions), code/rodata size can
# temporarily exceed the fixed windows and ld.gold (binutils 2.24) may crash
# with an "internal error in set_offset" instead of producing a normal error.
#
# To keep CI usable, support a dev layout mode that omits the fixed-address
# script so the library can still be linked for functional testing.
#
# Usage:
#   ndk-build EF2_LINK_LAYOUT=dev       (no fixed script)
#   ndk-build EF2_LINK_LAYOUT=match     (default, strict fixed script; may crash gold while overshooting)
#   ndk-build EF2_LINK_LAYOUT=matchgold (fixed script tuned to keep gold 1.11 alive: no RELRO PHDR + no .bss dot forcing)
#   ndk-build EF2_LINK_LAYOUT=matchrelro (attempt GNU_RELRO PHDR + :relro mapping; may crash gold 1.11)
#   ndk-build EF2_LINK_LAYOUT=match_goldfix (more aggressive gold workaround; temporary)
#   ndk-build EF2_GOLD_DIAG=1 (add ld.gold debug flags to the link for dynamic tracing)
EF2_LINK_LAYOUT ?= match
EF2_BSS_PAD_BYTES ?= 0
EF2_GOLD_DIAG ?= 0

# Always write a link map (useful when gold crashes).
# Use a stable path so CI can collect it even when the final .so is missing.
EF2_ABI := $(if $(TARGET_ARCH_ABI),$(TARGET_ARCH_ABI),armeabi-v7a)
LOCAL_LDFLAGS += -Wl,-Map,$(LOCAL_PATH)/../obj/local/$(EF2_ABI)/liblwplocal.map

ifeq ($(EF2_GOLD_DIAG),1)
  # Increase ld.gold verbosity for dynamic diagnosis of set_offset/internal errors
  LOCAL_LDFLAGS += -Wl,--debug=script
  # NOTE: -Wl, uses comma as an argument separator. Use separate flags if you need more.
  # LOCAL_LDFLAGS += -Wl,--debug=files
  # LOCAL_LDFLAGS += -Wl,--debug=task
  LOCAL_LDFLAGS += -Wl,--trace
  LOCAL_LDFLAGS += -Wl,--stats
  LOCAL_LDFLAGS += -Wl,--thread-count=1
endif

ifeq ($(EF2_LINK_LAYOUT),match)
  # Force section layout to better match the original binary:
  #   - .got before .data
  #   - RELRO window ends at 0x18000
  # This script is intentionally minimal for gold 1.11 compatibility.
  LOCAL_LDFLAGS += -Wl,-T,$(LOCAL_PATH)/ldscripts/armelf_linux_eabi_gold_compat.xsw
else ifeq ($(EF2_LINK_LAYOUT),matchgold)
  # "Match + gold" recovery mode: keep the fixed-address layout constraints but
  # avoid known ld.gold 1.11 crashes by removing the explicit RELRO PHDR assignment
  # and avoiding dot-forcing inside NOLOAD .bss.
  #
  # Optional: set EF2_BSS_PAD_BYTES to match reference .bss size via .bss.ef2pad input.
  LOCAL_SRC_FILES += ../src/compat/bss_ef2pad_v7a.c
  LOCAL_CFLAGS += -DEF2_BSS_PAD_BYTES=$(EF2_BSS_PAD_BYTES)
  LOCAL_LDFLAGS += -Wl,-T,$(LOCAL_PATH)/ldscripts/armelf_linux_eabi_gold_compat_matchgold.xsw
else ifeq ($(EF2_LINK_LAYOUT),matchrelrohdr)
  # Experimental: reserve GNU_RELRO PHDR (8 PHDRs) without :relro mapping; intended for post-link PHDR patching.
  # Force page sizes so PT_LOAD p_align becomes 0x1000 (stock).
  LOCAL_LDFLAGS += -Wl,-z,max-page-size=0x1000 -Wl,-z,common-page-size=0x1000
  LOCAL_SRC_FILES += ../src/compat/bss_ef2pad_v7a.c
  LOCAL_CFLAGS += -DEF2_BSS_PAD_BYTES=$(EF2_BSS_PAD_BYTES)
  LOCAL_LDFLAGS += -Wl,-T,$(LOCAL_PATH)/ldscripts/armelf_linux_eabi_gold_compat_relrohdr.xsw

else ifeq ($(EF2_LINK_LAYOUT),matchrelro)
  # Experimental: try to match stock PHDR count (8) and GNU_RELRO segment using explicit relro PHDR + :relro mapping.
  # gold 1.11 can be fragile here; keep this as an opt-in layout for data collection.
  # Force page sizes so PT_LOAD p_align becomes 0x1000 (stock).
  LOCAL_LDFLAGS += -Wl,-z,max-page-size=0x1000 -Wl,-z,common-page-size=0x1000
  LOCAL_LDFLAGS += -Wl,-T,$(LOCAL_PATH)/ldscripts/armelf_linux_eabi_gold_compat_relro.xsw

else ifeq ($(EF2_LINK_LAYOUT),match_goldfix)
  # Workaround for ld.gold 1.11 internal errors (set_offset) while the section windows
  # are still in flux. Uses an alternative linker script that avoids RELRO PHDR
  # assignment and avoids dot-forcing inside NOLOAD .bss.
  #
  # Optional: set EF2_BSS_PAD_BYTES to a positive value to match reference .bss size
  # without linker-script dot hacks.
  LOCAL_SRC_FILES += ../src/compat/bss_ef2pad_v7a.c
  LOCAL_CFLAGS += -DEF2_BSS_PAD_BYTES=$(EF2_BSS_PAD_BYTES)
  LOCAL_LDFLAGS += -Wl,-T,$(LOCAL_PATH)/ldscripts/armelf_linux_eabi_gold_compat_goldfix.xsw
else
  $(info [EF2] EF2_LINK_LAYOUT=$(EF2_LINK_LAYOUT) -> no fixed-address linker script)
endif

# Hotfix3: force-link libgcc unwind/div helpers into liblwplocal to match stock dynsym


LOCAL_LDLIBS := -llog -landroid -lstdc++ -lGLESv2 -lm -lc -ldl -lgcc

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/gnu-libstdc++)
