#!/usr/bin/env python3
"""Report key section sizes against the v7a reference budget.

This is a *diagnostic* helper for CI logs. When the strict fixed-address
linker script (match layout) fails (ld.gold may crash), comparing section
sizes from a looser build helps identify what grew beyond the reserved
window.

Usage:
  python3 tools/section_budget_v7a.py path/to/liblwplocal.so [--label NAME]
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from typing import Dict, Tuple


# Reference sizes from ref/native liblwplocal.so (armeabi-v7a)
REF = {
    ".rel.dyn": 0x0110,
    ".rel.plt": 0x0420,
    ".plt": 0x0644,
    ".text": 0xC358,
    ".ARM.extab": 0x00B4,
    ".ARM.exidx": 0x08C8,
    ".rodata": 0x184C,
    ".fini_array": 0x0008,
    ".init_array": 0x001C,
    ".data.rel.ro": 0x0020,
    ".dynamic": 0x0118,
    ".got": 0x0278,
    ".data": 0x0028,
    ".bss": 0x0865,
}


def parse_readelf_sections(path: str) -> Dict[str, Tuple[int, int]]:
    """Return {name: (addr, size)} parsed from `readelf -SW`."""
    out = subprocess.check_output(["readelf", "-SW", path], text=True, errors="ignore")
    secs: Dict[str, Tuple[int, int]] = {}
    # Example line:
    # [ 7] .plt PROGBITS 000076d0 0076d0 000644 00  AX  0   0  4
    sec_re = re.compile(
        r"^\s*\[\s*\d+\]\s+(\S+)\s+\S+\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+"
    )
    for line in out.splitlines():
        m = sec_re.match(line)
        if not m:
            continue
        name = m.group(1)
        addr_hex = m.group(2)
        size_hex = m.group(4)
        try:
            addr = int(addr_hex, 16)
            size = int(size_hex, 16)
        except ValueError:
            continue
        secs[name] = (addr, size)
    return secs


def fmt_delta(delta: int) -> str:
    if delta == 0:
        return "0"
    sign = "+" if delta > 0 else "-"
    return f"{sign}0x{abs(delta):x} ({delta:+d})"


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("so", help="ELF shared object to inspect")
    ap.add_argument("--label", default="", help="label to print in header")
    args = ap.parse_args()

    secs = parse_readelf_sections(args.so)
    label = f" [{args.label}]" if args.label else ""
    print(f"== section budget report{label} ==")
    print(f"file: {args.so}")

    missing = [k for k in REF.keys() if k not in secs]
    if missing:
        print("[WARN] missing sections:", ", ".join(missing))

    for name, ref_sz in REF.items():
        cur_t = secs.get(name)
        if cur_t is None:
            continue
        cur = cur_t[1]
        delta = cur - ref_sz
        status = "OK" if delta == 0 else ("OVER" if delta > 0 else "UNDER")
        print(f"{name:12s} cur=0x{cur:06x} ref=0x{ref_sz:06x} delta={fmt_delta(delta):>14s} {status}")

    # Fixed-layout window diagnostics (armeabi-v7a reference layout)
    #   - Data PT_LOAD target start (VMA): 0x17c28
    #   - .data target start (VMA):       0x18000
    target_data_start = 0x17C28
    target_data_page = 0x18000
    ro = secs.get(".rodata")
    if ro:
        ro_end = ro[0] + ro[1]
        slack = target_data_start - ro_end
        print(f"RO end: 0x{ro_end:06x}  target data start: 0x{target_data_start:06x}  slack: {fmt_delta(slack)}")
    got = secs.get(".got")
    if got:
        got_end = got[0] + got[1]
        slack = target_data_page - got_end
        print(f".got end: 0x{got_end:06x} target .data page: 0x{target_data_page:06x} slack: {fmt_delta(slack)}")

    # Quick relocation count hints
    relplt_t = secs.get(".rel.plt")
    if relplt_t is not None:
        relplt = relplt_t[1]
        # Each REL entry is 8 bytes
        print(f".rel.plt entries: {relplt // 8}")
    reldyn_t = secs.get(".rel.dyn")
    if reldyn_t is not None:
        reldyn = reldyn_t[1]
        print(f".rel.dyn entries: {reldyn // 8}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
