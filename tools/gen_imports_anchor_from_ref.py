#!/usr/bin/env python3
"""Generate imports anchor include files from a reference ELF.

This project matches Sony's liblwplocal.so by stabilizing:
  - .rel.plt (JUMP_SLOT) order via a `bl` call list in inline asm
  - .rel.dyn (GLOB_DAT) order via ordered address-takes in C/C++

This script generates the .rel.plt call list include:
  src/compat/imports_anchor_relplt_v7a.inc

Usage:
  python3 tools/gen_imports_anchor_from_ref.py reference/liblwplocal_ref.so

Notes:
  - Requires pyelftools (see tools/requirements_tools.txt)
  - This script only generates the call list. The GLOB_DAT order is currently
    hard-coded in imports_anchor_v7a.cpp (7 entries) because it's short.
"""

from __future__ import annotations

import argparse
from pathlib import Path

from elftools.elf.elffile import ELFFile


def _find_section(elf: ELFFile, name: str):
    sec = elf.get_section_by_name(name)
    if sec is None:
        raise SystemExit(f"[ERR] section not found: {name}")
    return sec


def _relplt_symbols_in_order(elf: ELFFile) -> list[str]:
    # ARM32 SysV typically uses SHT_REL for .rel.plt
    relplt = elf.get_section_by_name('.rel.plt') or elf.get_section_by_name('.rela.plt')
    if relplt is None:
        raise SystemExit('[ERR] neither .rel.plt nor .rela.plt exists')

    dynsym = _find_section(elf, '.dynsym')

    out: list[str] = []
    for rel in relplt.iter_relocations():
        sym_idx = rel.entry.r_info_sym
        sym = dynsym.get_symbol(sym_idx)
        name = sym.name
        if not name:
            name = f"<sym_{sym_idx}>"
        out.append(name)
    return out


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument('ref_elf', help='Path to reference liblwplocal.so')
    ap.add_argument('--out', default='src/compat/imports_anchor_relplt_v7a.inc', help='Output include path')
    args = ap.parse_args()

    ref_path = Path(args.ref_elf)
    out_path = Path(args.out)

    with ref_path.open('rb') as f:
        elf = ELFFile(f)
        syms = _relplt_symbols_in_order(elf)

    out_path.parent.mkdir(parents=True, exist_ok=True)
    lines: list[str] = []
    lines.append('// Auto-generated from reference liblwplocal.so .rel.plt order')
    lines.append('// DO NOT EDIT BY HAND. Regenerate with tools/gen_imports_anchor_from_ref.py')
    for s in syms:
        # Each line is a string literal fragment for inline asm.
        lines.append(f'      "bl {s}\\n"')

    out_path.write_text('\n'.join(lines) + '\n', encoding='utf-8')

    print(f"[OK] wrote {out_path} ({len(syms)} entries)")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
