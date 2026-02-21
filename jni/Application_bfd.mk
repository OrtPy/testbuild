# Match-layout diagnostic build (bfd)
#
# When ld.gold crashes with "internal error in set_offset" under the fixed
# address linker script, switching to ld.bfd usually produces a human-readable
# overlap/overflow error message. This file is used only for CI diagnostics.

APP_ABI := armeabi-v7a
APP_PLATFORM := android-9
APP_STL := gnustl_shared
NDK_TOOLCHAIN_VERSION := 4.8
APP_OPTIM := release

APP_CFLAGS += -mthumb -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16
APP_CFLAGS += -fno-ident
APP_CPPFLAGS += -fno-ident
APP_CFLAGS += -DEF2_PLATFORM_ANDROID=1 -DEF2_USE_REAL_GLES=1

# Use bfd instead of gold (diagnostic only).
APP_LDFLAGS += -fuse-ld=bfd

# Try to keep generating an output/map even if there are overlaps.
# This often makes the error actionable (shows which section grows past its slot).
APP_LDFLAGS += -Wl,--noinhibit-exec
