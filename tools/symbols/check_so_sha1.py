#!/usr/bin/env python3
"""
check_so_sha1.py

Strictly verify that a given liblwplocal.so is the *reference* variant we accept.

Default expected SHA1 is loaded from:
  ref/reference/liblwplocal_armeabi-v7a.sha1

Exit codes:
  0: match
  2: mismatch
  3: error
"""

from __future__ import annotations

import argparse
import hashlib
import sys
from pathlib import Path


def sha1_of(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()


def elf_brief(path: Path) -> str:
    # Best-effort: show ELF class/machine if LIEF is available.
    try:
        import lief  # type: ignore
        bin = lief.parse(str(path))
        return f"ELF{bin.header.identity_class.name.replace('ELF', '')} {bin.header.machine_type.name}"
    except Exception:
        return "ELF(?)"


def default_expected_sha1_file() -> Path:
    # tools/symbols/check_so_sha1.py -> project root is parents[2]
    root = Path(__file__).resolve().parents[2]
    # The reference SHA1 is stored under ref/reference/ in this repo.
    return root / "ref" / "reference" / "liblwplocal_armeabi-v7a.sha1"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--so", required=True, type=Path, help="Path to liblwplocal.so")
    ap.add_argument("--expected", default=None, help="Expected SHA1 (hex)")
    ap.add_argument("--expected-file", default=None, type=Path, help="File containing expected SHA1")
    args = ap.parse_args()

    so = args.so
    if not so.exists():
        print(f"[err] not found: {so}", file=sys.stderr)
        return 3

    expected = args.expected
    if args.expected_file:
        expected = args.expected_file.read_text(encoding="utf-8", errors="ignore").strip()
    if not expected:
        expected = default_expected_sha1_file().read_text(encoding="utf-8", errors="ignore").strip()

    got = sha1_of(so)

    size = so.stat().st_size
    brief = elf_brief(so)
    print(f"[so] path={so}")
    print(f"[so] size={size} bytes")
    print(f"[so] type={brief}")
    print(f"[sha1] expected={expected}")
    print(f"[sha1] got     ={got}")

    if got.lower() == expected.lower():
        print("[ok] reference so matches (strict).")
        return 0

    print("[ng] reference so mismatch: DO NOT use this so for analysis/C-port.", file=sys.stderr)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
