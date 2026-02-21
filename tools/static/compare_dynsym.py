#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""compare_dynsym.py

ref (95KB) の dynsym と、生成物(あなたのC化lib)の dynsym を比較して
- ref にあるが out に無い (missing)
- out にあるが ref に無い (extra)
を列挙します。

例:
  python tools/static/compare_dynsym.py --ref ref/liblwplocal.so --out build/outputs/liblwplocal.so
"""

import argparse
import sys
from typing import Set

import lief


def dynsym_names(path: str) -> Set[str]:
    b = lief.parse(path)
    if not isinstance(b, lief.ELF.Binary):
        raise RuntimeError(f"not ELF: {path}")
    out: Set[str] = set()
    for s in b.dynamic_symbols:
        if s.name:
            out.add(s.name)
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--ref", required=True)
    ap.add_argument("--out", required=True)
    args = ap.parse_args()

    try:
        ref = dynsym_names(args.ref)
        out = dynsym_names(args.out)
    except Exception as e:
        print(f"ERROR: {e}", file=sys.stderr)
        return 2

    missing = sorted(ref - out)
    extra = sorted(out - ref)

    print(f"ref symbols : {len(ref)}")
    print(f"out symbols : {len(out)}")
    print(f"missing     : {len(missing)}")
    print(f"extra       : {len(extra)}\n")

    if missing:
        print("[missing]")
        for n in missing:
            print(n)
        print()
    if extra:
        print("[extra]")
        for n in extra:
            print(n)
        print()

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
