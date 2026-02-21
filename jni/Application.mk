# NDK r9d / GCC+gold reproduction build (armeabi-v7a only)

APP_ABI := armeabi-v7a
APP_PLATFORM := android-9

# Match legacy STL used by original era builds.
APP_STL := gnustl_shared

# Force GCC toolchain (not clang) and pick the 4.8 toolchain.
NDK_TOOLCHAIN_VERSION := 4.8

APP_OPTIM := release

# Thumb-2 + VFPv3-D16 softfp is common for Xperia-era builds.
APP_CFLAGS += -mthumb -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16

# Avoid automatic .ident emission into .comment for every object.
# We provide a deterministic .comment via src/compat/gcc_comment_ref.c.
APP_CFLAGS += -fno-ident
APP_CPPFLAGS += -fno-ident

# Project-wide feature flags
APP_CFLAGS += -DEF2_PLATFORM_ANDROID=1 -DEF2_USE_REAL_GLES=1

# Use gold (for .note.gnu.gold-version).
APP_LDFLAGS += -fuse-ld=gold
