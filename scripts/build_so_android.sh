#!/usr/bin/env bash
set -euo pipefail

# Build liblwplocal.so using Android NDK + CMake (Ninja).
# Outputs: out/<abi>/liblwplocal.so

NDK="${ANDROID_NDK_HOME:-${ANDROID_NDK_ROOT:-}}"
if [[ -z "${NDK}" ]]; then
  if [[ -n "${ANDROID_SDK_ROOT:-}" && -d "${ANDROID_SDK_ROOT}/ndk" ]]; then
    # Pick last folder
    NDK="$(ls -1 "${ANDROID_SDK_ROOT}/ndk" | tail -n 1)"
    NDK="${ANDROID_SDK_ROOT}/ndk/${NDK}"
  fi
fi

if [[ -z "${NDK}" || ! -f "${NDK}/build/cmake/android.toolchain.cmake" ]]; then
  echo "[ERROR] Android NDK not found. Set ANDROID_NDK_HOME." >&2
  exit 1
fi

TOOLCHAIN="${NDK}/build/cmake/android.toolchain.cmake"
PLATFORM="android-21"

for ABI in armeabi-v7a arm64-v8a; do
  echo "=== Building ${ABI} ==="
  BDIR="build/${ABI}"
  cmake -S .. -B "${BDIR}" -G Ninja \
    -DANDROID_ABI="${ABI}" \
    -DANDROID_PLATFORM="${PLATFORM}" \
    -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DEF2_USE_REAL_GLES=ON
  cmake --build "${BDIR}" -j

  mkdir -p "out/${ABI}"
  # copy result
  SO_PATH="$(find "${BDIR}" -name 'liblwplocal.so' | head -n 1)"
  cp -f "${SO_PATH}" "out/${ABI}/liblwplocal.so"
  # Optional: bundle original libgnustl_shared.so next to liblwplocal.so for on-device comparison.
  if [[ -f "bundle/${ABI}/libgnustl_shared.so" ]]; then
    cp -f "bundle/${ABI}/libgnustl_shared.so" "out/${ABI}/libgnustl_shared.so"
    echo "[OK] out/${ABI}/libgnustl_shared.so"
  fi
  echo "[OK] out/${ABI}/liblwplocal.so"
done
