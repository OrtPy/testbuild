#!/usr/bin/env bash
set -euo pipefail

ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
DIST="$ROOT/dist"
APK_SRC="$ROOT/app/app/build/outputs/apk/debug/app-debug.apk"
APK_DST="$DIST/LwpLocalRpcHarness_debug.apk"

if [[ ! -f "$APK_SRC" ]]; then
  echo "[ERROR] APK not found: $APK_SRC" >&2
  exit 1
fi

mkdir -p "$DIST"
cp -f "$APK_SRC" "$APK_DST"

# Preferred: copy libs from Gradle intermediates
LIBSRC=""
CANDS=(
  "$ROOT/app/app/build/intermediates/merged_native_libs/debug/out/lib"
  "$ROOT/app/app/build/intermediates/merged_jni_libs/debug/out/lib"
  "$ROOT/app/app/build/intermediates/stripped_native_libs/debug/out/lib"
)
for c in "${CANDS[@]}"; do
  if [[ -d "$c" ]]; then
    LIBSRC="$c"
    break
  fi
done

if [[ -n "$LIBSRC" ]]; then
  rm -rf "$DIST/lib"
  mkdir -p "$DIST/lib"
  cp -a "$LIBSRC/." "$DIST/lib/"
  echo "[OK] Collected APK + libs (from intermediates) -> $DIST"
  exit 0
fi

# Fallback: unzip APK and copy lib/
rm -rf "$DIST/apk_unpacked"
mkdir -p "$DIST/apk_unpacked"
(
  cd "$DIST/apk_unpacked"
  unzip -q "$APK_DST"
)
if [[ -d "$DIST/apk_unpacked/lib" ]]; then
  rm -rf "$DIST/lib"
  cp -a "$DIST/apk_unpacked/lib" "$DIST/lib"
  echo "[OK] Collected APK + libs (from APK unzip) -> $DIST"
else
  echo "[WARN] No lib/ folder found in APK. APK only: $APK_DST" >&2
fi
