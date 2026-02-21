# Dev build (for CI usability while filling internal functions)
#
# - Uses the same ABI/toolchain as the match build
# - Uses ld.bfd to avoid ld.gold internal crashes when section layout is not fixed
# - Pair with: ndk-build EF2_LINK_LAYOUT=dev NDK_APPLICATION_MK=jni/Application_dev.mk

APP_ABI := armeabi-v7a
APP_PLATFORM := android-9
APP_STL := gnustl_shared
NDK_TOOLCHAIN_VERSION := 4.8
APP_OPTIM := release

APP_CFLAGS += -mthumb -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16
APP_CFLAGS += -fno-ident
APP_CPPFLAGS += -fno-ident
APP_CFLAGS += -DEF2_PLATFORM_ANDROID=1 -DEF2_USE_REAL_GLES=1

# Prefer bfd for stability in dev mode.
APP_LDFLAGS += -fuse-ld=bfd
