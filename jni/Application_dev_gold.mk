# Dev build (ld.gold probe)
#
# - Same ABI/toolchain as the match build
# - Uses ld.gold but WITHOUT the fixed-address linker script (EF2_LINK_LAYOUT=dev)
# - Useful to inspect import set / section sizes when strict match link crashes

APP_ABI := armeabi-v7a
APP_PLATFORM := android-9
APP_STL := gnustl_shared
NDK_TOOLCHAIN_VERSION := 4.8
APP_OPTIM := release

APP_CFLAGS += -mthumb -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16
APP_CFLAGS += -fno-ident
APP_CPPFLAGS += -fno-ident
APP_CFLAGS += -DEF2_PLATFORM_ANDROID=1 -DEF2_USE_REAL_GLES=1

# Prefer gold here (probe only).
APP_LDFLAGS += -fuse-ld=gold
