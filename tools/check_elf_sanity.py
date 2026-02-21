#!/usr/bin/env python3
"""Sanity checks for liblwplocal.so fingerprints.

This script is intentionally dependency-free and uses readelf output.
It is meant to be run in CI to prevent accidental introduction of new
PLT imports / relocation count drift that breaks "perfect match" goals.

Checks:
  - DT_RELCOUNT equals expected (default 27)
  - R_ARM_JUMP_SLOT count equals expected (default 132)
  - banned symbols are NOT present in dynsym / relocations

Usage:
  python3 tools/check_elf_sanity.py <path/to/liblwplocal.so> [--relcount 27] [--jumps 132]

Exit code:
  0 = OK
  2 = mismatch
  3 = tool/readelf failure
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

DEFAULT_BANNED = [
    "_ZNSs7_M_leakEv",  # std::string::_M_leak (COW detach) must not be imported
]


def run(cmd: list[str]) -> str:
    try:
        return subprocess.check_output(cmd, stderr=subprocess.STDOUT, text=True)
    except subprocess.CalledProcessError as e:
        sys.stderr.write(e.output)
        raise


def parse_relcount(readelf_d: str) -> int | None:
    # Example: 0x6ffffffa (RELCOUNT)                   27
    m = re.search(r"\(RELCOUNT\)\s+(\d+)", readelf_d)
    return int(m.group(1)) if m else None


def count_jump_slots(readelf_r: str) -> int:
    return sum(1 for ln in readelf_r.splitlines() if "R_ARM_JUMP_SLOT" in ln)


def find_banned(readelf_ws: str, readelf_r: str, banned: list[str]) -> list[str]:
    hits: set[str] = set()
    for sym in banned:
        if sym in readelf_ws or sym in readelf_r:
            hits.add(sym)
    return sorted(hits)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("so", type=Path)
    ap.add_argument("--relcount", type=int, default=27)
    ap.add_argument("--jumps", type=int, default=132)
    ap.add_argument("--ban", action="append", default=[])
    args = ap.parse_args()

    so = args.so
    if not so.is_file():
        sys.stderr.write(f"[NG] missing: {so}\n")
        return 3

    banned = list(DEFAULT_BANNED)
    banned.extend(args.ban)

    try:
        out_d = run(["readelf", "-dW", str(so)])
        out_r = run(["readelf", "-rW", str(so)])
        out_ws = run(["readelf", "-Ws", str(so)])
    except Exception:
        sys.stderr.write("[NG] readelf failed\n")
        return 3

    relcount = parse_relcount(out_d)
    jumps = count_jump_slots(out_r)
    banned_hits = find_banned(out_ws, out_r, banned)

    ok = True

    if relcount is None:
        sys.stderr.write("[NG] RELCOUNT not found in DT_DYNAMIC\n")
        ok = False
    elif relcount != args.relcount:
        sys.stderr.write(f"[NG] RELCOUNT expected={args.relcount} actual={relcount}\n")
        ok = False
    else:
        print(f"[OK] RELCOUNT={relcount}")

    if jumps != args.jumps:
        sys.stderr.write(f"[NG] JUMP_SLOT expected={args.jumps} actual={jumps}\n")
        ok = False
    else:
        print(f"[OK] JUMP_SLOT={jumps}")

    if banned_hits:
        sys.stderr.write("[NG] banned symbols present: " + ", ".join(banned_hits) + "\n")
        ok = False
    else:
        print("[OK] banned symbols: none")

    return 0 if ok else 2


if __name__ == "__main__":
    raise SystemExit(main())
