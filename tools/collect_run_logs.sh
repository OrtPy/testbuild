#!/usr/bin/env bash
set -euo pipefail

# Collect build outputs + diagnostics into a single folder.
# Intended for GitHub Actions.

if [ $# -lt 3 ]; then
  echo "Usage: collect_run_logs.sh <out_dir> <ndk_dir> <abi>" >&2
  exit 2
fi

OUT_DIR="$1"; NDK_DIR="$2"; ABI="$3"

mkdir -p "$OUT_DIR" "$OUT_DIR/out" "$OUT_DIR/text" "$OUT_DIR/meta"

# Metadata
(date -u +"%Y-%m-%dT%H:%M:%SZ" || true) > "$OUT_DIR/meta/timestamp_utc.txt"
(git rev-parse HEAD || true) > "$OUT_DIR/meta/source_sha.txt"

# Build products (stripped + unstripped)
if [ -f "libs/$ABI/liblwplocal.so" ]; then
  cp -av "libs/$ABI/liblwplocal.so" "$OUT_DIR/out/liblwplocal.so"
fi
if [ -f "libs/$ABI/liblwplocal_unidbgfix.so" ]; then
  cp -av "libs/$ABI/liblwplocal_unidbgfix.so" "$OUT_DIR/out/liblwplocal_unidbgfix.so"
fi
if [ -f "obj/local/$ABI/liblwplocal.so" ]; then
  cp -av "obj/local/$ABI/liblwplocal.so" "$OUT_DIR/out/liblwplocal_unstripped.so"
fi
if [ -f "obj/local/$ABI/liblwplocal_unstripped_unidbgfix.so" ]; then
  cp -av "obj/local/$ABI/liblwplocal_unstripped_unidbgfix.so" "$OUT_DIR/out/liblwplocal_unstripped_unidbgfix.so"
fi
if [ -f "obj/local/$ABI/liblwplocal.map" ]; then
  cp -av "obj/local/$ABI/liblwplocal.map" "$OUT_DIR/out/liblwplocal.map"
fi

# Convenience aliases for tracing tools:
# - unidbg internal-trace often relies on rich symbols; use unstripped+fix by default.
#   (Keep original names for backwards compatibility.)
if [ -f "$OUT_DIR/out/liblwplocal_unstripped_unidbgfix.so" ]; then
  cp -av "$OUT_DIR/out/liblwplocal_unstripped_unidbgfix.so" "$OUT_DIR/out/liblwplocal_unidbgfix2.so"
fi
if [ -f "$OUT_DIR/out/liblwplocal_unidbgfix.so" ]; then
  cp -av "$OUT_DIR/out/liblwplocal_unidbgfix.so" "$OUT_DIR/out/liblwplocal_unidbgfix2_stripped.so"
fi

# libgnustl_shared.so (runtime)
GNUSRC="$NDK_DIR/sources/cxx-stl/gnu-libstdc++/4.8/libs/$ABI/libgnustl_shared.so"
if [ -f "$GNUSRC" ]; then
  cp -av "$GNUSRC" "$OUT_DIR/out/libgnustl_shared.so"
fi

# Toolchain fingerprints
{
  echo "NDK_DIR=$NDK_DIR"
  "$NDK_DIR/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86_64/bin/arm-linux-androideabi-gcc" -v 2>&1 | tail -n 50 || true
  "$NDK_DIR/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86_64/bin/arm-linux-androideabi-ld.gold" --version 2>&1 | head -n 5 || true
} > "$OUT_DIR/text/fingerprint_toolchain.txt" 2>&1 || true

# ELF dumps (only if we have the file)
SO="$OUT_DIR/out/liblwplocal.so"
if [ -f "$SO" ]; then
  file "$SO" > "$OUT_DIR/text/file.txt" || true
  readelf -hW "$SO" > "$OUT_DIR/text/readelf_h.txt" || true
  readelf -lW "$SO" > "$OUT_DIR/text/readelf_l.txt" || true
  readelf -SW "$SO" > "$OUT_DIR/text/readelf_s.txt" || true
  readelf -dW "$SO" > "$OUT_DIR/text/readelf_d.txt" || true
  readelf -rW "$SO" > "$OUT_DIR/text/readelf_r.txt" || true
  readelf -Ws "$SO" > "$OUT_DIR/text/readelf_Ws.txt" || true
  readelf -p .comment "$SO" > "$OUT_DIR/text/readelf_comment.txt" || true
  readelf -A "$SO" > "$OUT_DIR/text/readelf_A.txt" || true
fi

# Extra dumps for unidbg-fixed variant (if present)
SO_FIX="$OUT_DIR/out/liblwplocal_unidbgfix.so"
if [ -f "$SO_FIX" ]; then
  file "$SO_FIX" > "$OUT_DIR/text/file_fix.txt" || true
  readelf -hW "$SO_FIX" > "$OUT_DIR/text/readelf_h_fix.txt" || true
  readelf -lW "$SO_FIX" > "$OUT_DIR/text/readelf_l_fix.txt" || true
  readelf -SW "$SO_FIX" > "$OUT_DIR/text/readelf_s_fix.txt" || true
  readelf -dW "$SO_FIX" > "$OUT_DIR/text/readelf_d_fix.txt" || true
  readelf -rW "$SO_FIX" > "$OUT_DIR/text/readelf_r_fix.txt" || true
  readelf -Ws "$SO_FIX" > "$OUT_DIR/text/readelf_Ws_fix.txt" || true
  readelf -p .comment "$SO_FIX" > "$OUT_DIR/text/readelf_comment_fix.txt" || true
  readelf -A "$SO_FIX" > "$OUT_DIR/text/readelf_A_fix.txt" || true
fi

# Zip
ZIP_PATH="$OUT_DIR/run_logs_$(basename "$OUT_DIR").zip"
( cd "$OUT_DIR" && zip -qr "$(basename "$ZIP_PATH")" . )

# Print where it is
echo "[ok] collected logs: $OUT_DIR"
echo "[ok] zip: $ZIP_PATH"
