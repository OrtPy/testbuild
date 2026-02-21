#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
split_liblwplocal.py

Decompile output (IDA/Ghidra-like) often arrives as a single gigantic .c file.
This helper splits it into multiple .c chunks by "class" prefix (e.g., Curve::*, Program::*),
and also groups JNI exports (Java_*) into a separate file.

Usage:
  python tools/split_liblwplocal.py ref/native/liblwplocal.so.c --out generated/liblwplocal_split

Notes:
- This script keeps the original text blocks as-is (no semantic rewriting).
- Output is intended for readability / navigation, not guaranteed to compile.
"""
from __future__ import annotations

import argparse
import os
import re
from pathlib import Path
from collections import defaultdict

MARK_RE = re.compile(r"^//-----\s+\([0-9A-Fa-f]{8}\)")

def guess_group(sig_line: str) -> str:
    # Extract function name from a signature-like line
    # Examples:
    #   void __fastcall Curve::requestColors(Curve *this)
    #   int __fastcall Java_com_sonymobile_experienceflow_renderer_CurveRenderer_init(...)
    #   unsigned int __fastcall lodepng::decode(...)
    m = re.search(r"\b([A-Za-z_][A-Za-z0-9_:]*)\s*\(", sig_line)
    name = m.group(1) if m else "unknown"

    if name.startswith("Java_") or name.startswith("JNI"):
        return "jni"
    if "::" in name:
        cls = name.split("::", 1)[0]
        # normalize a few very common ones
        cls = cls.replace("std::", "std_")
        cls = cls.replace("lodepng::", "lodepng_")
        return cls
    # fall back
    if name.startswith("sub_") or name.startswith("loc_"):
        return "subroutines"
    return "globals"

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("input", help="path to liblwplocal.so.c (decompile output)")
    ap.add_argument("--out", default="generated/liblwplocal_split", help="output directory")
    args = ap.parse_args()

    inp = Path(args.input)
    out_dir = Path(args.out)
    out_dir.mkdir(parents=True, exist_ok=True)

    text = inp.read_text(errors="ignore").splitlines(True)

    blocks = []
    i = 0
    while i < len(text):
        if MARK_RE.match(text[i]):
            start = i
            i += 1
            # find signature line (skip blank/comment-only lines)
            sig = ""
            while i < len(text) and sig.strip() == "":
                sig = text[i]
                i += 1
            # now capture until next marker or EOF
            while i < len(text) and not MARK_RE.match(text[i]):
                i += 1
            blocks.append((sig.strip(), "".join(text[start:i])))
        else:
            i += 1

    grouped = defaultdict(list)
    for sig, blk in blocks:
        grouped[guess_group(sig)].append((sig, blk))

    # Write out per-group files
    for group, items in sorted(grouped.items(), key=lambda kv: kv[0].lower()):
        out_path = out_dir / f"{group}.c"
        with out_path.open("w", encoding="utf-8", newline="") as f:
            f.write(f"// Auto-split from: {inp.as_posix()}\n")
            f.write(f"// Group: {group}  Functions: {len(items)}\n\n")
            for sig, blk in items:
                f.write(blk)
                if not blk.endswith("\n"):
                    f.write("\n")
                f.write("\n")

    # summary
    summary_path = out_dir / "_summary.txt"
    with summary_path.open("w", encoding="utf-8") as f:
        total = sum(len(v) for v in grouped.values())
        f.write(f"input: {inp}\n")
        f.write(f"total functions (by markers): {total}\n\n")
        for group, items in sorted(grouped.items(), key=lambda kv: (-len(kv[1]), kv[0].lower())):
            f.write(f"{group:20s} {len(items)}\n")

    print(f"[ok] split {len(blocks)} blocks into {len(grouped)} files: {out_dir}")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
