#!/usr/bin/env python3
"""Compare reference dynsym export list against what the C port declares.

This does NOT require building the .so.
It extracts:
  - all `__asm__("...")` symbol names from src/compat/compat_exports_*.c
  - all JNI exported function names from src/jni/*.c (Java_...)

Then compares them to ref/reference/exports_armeabi-v7a_dynsym_defined.tsv.

Usage:
  python scripts/check_exports_against_reference.py

Optional:
  --ref <path-to-tsv>
  --root <repo-root>
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path


ASM_RE = re.compile(r'__asm__\(\s*"([^"]+)"\s*\)')
JNI_RE = re.compile(r'\b(Java_[A-Za-z0-9_]+)\b')


def load_reference(tsv_path: Path) -> set[str]:
    names: set[str] = set()
    for line in tsv_path.read_text(encoding='utf-8', errors='replace').splitlines():
        line = line.strip()
        if not line or line.startswith('#'):
            continue
        parts = line.split('\t')
        if len(parts) < 2:
            continue
        names.add(parts[1])
    return names


def load_declared(repo_root: Path) -> set[str]:
    names: set[str] = set()

    # __asm__ exports
    for c in repo_root.glob('src/compat/compat_exports_*.c'):
        txt = c.read_text(encoding='utf-8', errors='replace')
        for m in ASM_RE.finditer(txt):
            names.add(m.group(1))

    # JNI exports: Java_... symbols will be exported by name
    for c in repo_root.glob('src/jni/*.c'):
        txt = c.read_text(encoding='utf-8', errors='replace')
        # keep only Java_* that appear in code
        for m in JNI_RE.finditer(txt):
            if m.group(1).startswith('Java_'):
                names.add(m.group(1))

    # Commonly expected loader hooks
    for name in ('JNI_OnLoad', 'JNI_OnUnload'):
        if (repo_root / 'src').joinpath('jni').exists():
            # Only add if present in code, but check quickly
            pass

    return names


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument('--ref', default='ref/reference/exports_armeabi-v7a_dynsym_defined.tsv')
    ap.add_argument('--root', default='.')
    args = ap.parse_args()

    root = Path(args.root).resolve()
    ref = (root / args.ref).resolve()

    if not ref.exists():
        print(f'[ERR] reference file not found: {ref}')
        return 2

    ref_names = load_reference(ref)
    declared = load_declared(root)

    missing = sorted(ref_names - declared)
    extra = sorted(declared - ref_names)

    print(f'[INFO] reference exports: {len(ref_names)}')
    print(f'[INFO] declared exports:  {len(declared)}')

    if missing:
        print('\n[MISSING] present in reference but not declared in code:')
        for n in missing:
            print('  ' + n)
    else:
        print('\n[OK] no missing exports vs reference list.')

    # "extra" can be fine (we may export more than the original), so keep it short.
    if extra:
        print(f'\n[NOTE] {len(extra)} names declared by code but not in reference (usually OK).')
        for n in extra[:50]:
            print('  ' + n)
        if len(extra) > 50:
            print('  ...')

    return 0 if not missing else 1


if __name__ == '__main__':
    raise SystemExit(main())
