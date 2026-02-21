#!/usr/bin/env bash
set -euo pipefail

# Repair missing toolchain symlinks in Android NDK r10c if the extractor
# ignored them (common on newer 7-Zip due to "dangerous symlink" checks).
#
# Usage:
#   fix_ndk_r10c_symlinks.sh /path/to/android-ndk-r10c

NDK_DIR="${1:-}"
if [ -z "$NDK_DIR" ] || [ ! -d "$NDK_DIR" ]; then
  echo "Usage: $0 /path/to/android-ndk-r10c" >&2
  exit 2
fi

# Create symlinks like:
#   toolchains/.../prebuilt/linux-x86_64/<triple>/bin/gcc -> ../../bin/<triple>-gcc
# when they are missing.

for bin_dir in "$NDK_DIR"/toolchains/*/prebuilt/linux-x86_64/*/bin; do
  [ -d "$bin_dir" ] || continue
  triple="$(basename "$(dirname "$bin_dir")")"
  prebuilt_root="$(dirname "$(dirname "$bin_dir")")"  # .../prebuilt/linux-x86_64
  shared_bin="$prebuilt_root/bin"
  [ -d "$shared_bin" ] || continue

  # Common tool names present in the NDK as <triple>-<tool> in shared_bin.
  for t in ar as c++ g++ gcc ld nm objcopy objdump ranlib strip ld.bfd ld.gold; do
    if [ ! -e "$bin_dir/$t" ] && [ -e "$shared_bin/${triple}-$t" ]; then
      ln -sf "../../bin/${triple}-$t" "$bin_dir/$t"
    fi
  done

  # ld.mcld is special in r10c: some toolchains link to llvm-3.5's ld.mcld.
  if [ ! -e "$bin_dir/ld.mcld" ] && [ -x "$NDK_DIR/toolchains/llvm-3.5/prebuilt/linux-x86_64/bin/ld.mcld" ]; then
    ln -sf "../../../../../../toolchains/llvm-3.5/prebuilt/linux-x86_64/bin/ld.mcld" "$bin_dir/ld.mcld"
  fi
done

echo "[ok] fixed toolchain symlinks (best-effort)"
