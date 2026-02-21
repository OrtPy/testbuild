#!/usr/bin/env python3
"""Extract a *curated* list of symbols we want to keep compatible with the
original liblwplocal.so.

We intentionally do NOT try to mirror every template/stdlib symbol, because
those depend on the STL implementation and toolchain.

This script extracts:
- JNI entrypoints (Java_com_sonymobile_experienceflow_renderer_CurveRenderer_*)
- Core engine classes used directly by the original library (Curve, CurveClient)
- A small set of renderer helper classes (buffer/varray/program/texture/bufferconfig)

Usage:
  python3 tools/symbols/extract_required_symbols.py \
      --input-so ref/external/armeabi-v7a/liblwplocal.so \
      --out tools/symbols/required_symbols.txt
"""

import argparse
import re
import subprocess
from pathlib import Path

PATTERNS = [
    re.compile(r"^Java_com_sonymobile_experienceflow_renderer_CurveRenderer_"),
    re.compile(r"^_ZN5Curve"),
    re.compile(r"^_ZN11CurveClient"),
    re.compile(r"^_ZN6varray"),
    re.compile(r"^_ZN6buffer"),
    re.compile(r"^_ZN12bufferconfig"),
    re.compile(r"^_ZN7program"),
    re.compile(r"^_ZN7texture"),
    re.compile(r"^_ZN12rendererdata"),
]

# A few important global objects used by the original program implementation.
EXTRA_OBJECTS = {
    "_ZN7program7attribsE",
    "_ZN7program5boundE",
    "_ZN7program8uniformsE",
    "_ZN7program11attribindexE",
}


def run_readelf(so_path: Path) -> str:
    try:
        out = subprocess.check_output(["readelf", "-Ws", str(so_path)], text=True)
    except FileNotFoundError as e:
        raise SystemExit("readelf not found. Install binutils (or run inside CI on ubuntu-latest).") from e
    return out


def parse_symbols(readelf_out: str):
    # readelf output columns are variable width; we grab the final column (Name)
    # but only for dynsym entries.
    symbols = []
    for line in readelf_out.splitlines():
        line = line.strip()
        if not line or line.startswith("Symbol table") or line.startswith("Num:"):
            continue
        # Example:
        #  119: 00012201   308 FUNC    GLOBAL DEFAULT    8 _ZN5CurveC1EP13AAssetManager
        parts = line.split()
        if len(parts) < 8:
            continue
        ndx = parts[6]
        name = parts[7]
        if ndx == "UND":
            continue
        symbols.append(name)
    return symbols


def is_required(name: str) -> bool:
    if name in EXTRA_OBJECTS:
        return True
    return any(p.match(name) for p in PATTERNS)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--input-so", required=True)
    ap.add_argument("--out", required=True)
    args = ap.parse_args()

    so_path = Path(args.input_so)
    if not so_path.exists():
        raise SystemExit(f"input .so not found: {so_path}")

    out = run_readelf(so_path)
    syms = parse_symbols(out)

    required = sorted({s for s in syms if is_required(s)})

    out_path = Path(args.out)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text("\n".join(required) + "\n", encoding="utf-8")

    print(f"Wrote {len(required)} symbols -> {out_path}")


if __name__ == "__main__":
    main()
