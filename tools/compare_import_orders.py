#!/usr/bin/env python3
"""Compare import ordering between reference and candidate ELF.

Checks:
  1) .rel.plt (JUMP_SLOT) symbol order
  2) .rel.dyn (GLOB_DAT) symbol order

Usage:
  python3 tools/compare_import_orders.py reference/liblwplocal_ref.so artifacts/liblwplocal_match_gold.so

Exit code:
  0 if both orders match exactly
  2 if any mismatch
"""

from __future__ import annotations

import argparse
from pathlib import Path

from elftools.elf.elffile import ELFFile


def _rel_syms_in_order(elf: ELFFile, sec_name: str) -> list[tuple[str, str]]:
    """Return list of (type, sym_name) for relocations in section order."""
    relsec = elf.get_section_by_name(sec_name) or elf.get_section_by_name(sec_name.replace('.rel.', '.rela.'))
    if relsec is None:
        return []
    dynsym = elf.get_section_by_name('.dynsym')
    if dynsym is None:
        return []

    out: list[tuple[str, str]] = []
    for rel in relsec.iter_relocations():
        sym_idx = rel.entry.r_info_sym
        sym = dynsym.get_symbol(sym_idx)
        name = sym.name or f"<sym_{sym_idx}>"
        # For SHT_REL, r_info_type exists
        rtype = str(rel.entry.r_info_type)
        out.append((rtype, name))
    return out


def _relplt_syms(elf: ELFFile) -> list[str]:
    rels = _rel_syms_in_order(elf, '.rel.plt')
    if not rels:
        rels = _rel_syms_in_order(elf, '.rela.plt')
    return [name for _, name in rels]


def _reldyn_globdat_syms(elf: ELFFile) -> list[str]:
    rels = _rel_syms_in_order(elf, '.rel.dyn')
    if not rels:
        rels = _rel_syms_in_order(elf, '.rela.dyn')

    # ARM32: R_ARM_GLOB_DAT == 21
    out: list[str] = []
    for rtype, name in rels:
        if rtype == '21':
            out.append(name)
    return out


def _first_mismatch(a: list[str], b: list[str]) -> tuple[int, str, str] | None:
    n = min(len(a), len(b))
    for i in range(n):
        if a[i] != b[i]:
            return i, a[i], b[i]
    if len(a) != len(b):
        return n, f"<len={len(a)}>", f"<len={len(b)}>"
    return None


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument('ref', help='Reference .so')
    ap.add_argument('cand', help='Candidate .so')
    args = ap.parse_args()

    refp = Path(args.ref)
    candp = Path(args.cand)

    with refp.open('rb') as f:
        ref = ELFFile(f)
        ref_relplt = _relplt_syms(ref)
        ref_glob = _reldyn_globdat_syms(ref)

    with candp.open('rb') as f:
        cand = ELFFile(f)
        cand_relplt = _relplt_syms(cand)
        cand_glob = _reldyn_globdat_syms(cand)

    ok = True

    mm = _first_mismatch(ref_relplt, cand_relplt)
    print('== .rel.plt order ==')
    print(f'ref : {len(ref_relplt)}')
    print(f'cand: {len(cand_relplt)}')
    if mm is None:
        print('[OK] exact match')
    else:
        i, ra, ca = mm
        print(f'[NG] first mismatch @ index {i}:')
        print(f'  ref : {ra}')
        print(f'  cand: {ca}')
        ok = False

    mm2 = _first_mismatch(ref_glob, cand_glob)
    print('\n== .rel.dyn GLOB_DAT order ==')
    print(f'ref : {len(ref_glob)}')
    print(f'cand: {len(cand_glob)}')
    if mm2 is None:
        print('[OK] exact match')
    else:
        i, ra, ca = mm2
        print(f'[NG] first mismatch @ index {i}:')
        print(f'  ref : {ra}')
        print(f'  cand: {ca}')
        ok = False

    return 0 if ok else 2


if __name__ == '__main__':
    raise SystemExit(main())
