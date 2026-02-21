#!/usr/bin/env python3
"""
dump_dynsym_defined.py

Dump defined dynsym symbol names from an ELF shared object.
This is used to generate or inspect exports_*.tsv.

Output:
  one symbol name per line, sorted.
"""

from __future__ import annotations

import argparse
from pathlib import Path

from dynsym_util import dynsym_defined_names


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--so", required=True, type=Path)
    args = ap.parse_args()

    names = sorted(dynsym_defined_names(args.so))
    for n in names:
        print(n)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
