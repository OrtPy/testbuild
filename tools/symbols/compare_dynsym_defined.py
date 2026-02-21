#!/usr/bin/env python3
"""Compare defined dynsym symbols between a reference TSV and a candidate .so.

Reference TSV format (tab-separated):
  TYPE\tNAME\tBIND

Comparison is NAME-only.

Exit codes:
  0: OK
  2: Missing/extra symbols
  3: Error
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path


# Linker-provided section-boundary markers (sometimes present in the original build).
# For "perfect match" checks, keep them. For a more relaxed compatibility check, pass --ignore-linker-markers.
LINKER_MARKER_SYMBOLS = {"__bss_start", "_edata", "_end"}


def load_ref(path: Path):
    ref = {}
    for line in path.read_text(encoding="utf-8", errors="ignore").splitlines():
        line = line.strip()
        if not line:
            continue
        parts = line.split("\t")
        if len(parts) < 2:
            continue
        typ, name = parts[0], parts[1]
        bind = parts[2] if len(parts) > 2 else ""
        ref[name] = (typ, bind)
    return ref


def dynsym_defined(so_path: Path):
    """Return a set of defined dynsym names for the given .so.

    Backend order: readelf -> LIEF -> pyelftools (see dynsym_util.py).
    """
    # Local import without requiring a package install.
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from dynsym_util import dynsym_defined_names

    return dynsym_defined_names(so_path)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--ref", required=True)
    ap.add_argument("--so", required=True)
    ap.add_argument("--allow-extra", action="store_true")
    ap.add_argument("--ignore-linker-markers", action="store_true")
    args = ap.parse_args()

    ref_path = Path(args.ref)
    so_path = Path(args.so)

    if not ref_path.exists() or not so_path.exists():
        print("ref or so path does not exist", file=sys.stderr)
        return 3

    ref = load_ref(ref_path)
    got = dynsym_defined(so_path)

    if args.ignore_linker_markers:
        for _s in list(LINKER_MARKER_SYMBOLS):
            ref.pop(_s, None)
            got.discard(_s)

    missing = [n for n in sorted(ref.keys()) if n not in got]
    extra = [n for n in sorted(got) if n not in ref]

    if missing:
        print(f"MISSING: {len(missing)}")
        for n in missing[:200]:
            typ, bind = ref[n]
            print(f"  {typ}\t{bind}\t{n}")
        if len(missing) > 200:
            print("  ...")

    if extra and not args.allow_extra:
        print(f"EXTRA: {len(extra)}")
        for n in extra[:200]:
            print(f"  {n}")
        if len(extra) > 200:
            print("  ...")

    if missing:
        return 2
    if extra and not args.allow_extra:
        return 2

    print("OK")
    if extra:
        print(f"NOTE: {len(extra)} extra symbols (allowed).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
