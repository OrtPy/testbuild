#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""scan_symbol_calls.py

95KB版 liblwplocal.so (armeabi-v7a) を対象に:
- dynsym から任意条件でシンボルを抽出
- Capstone で逆アセンブルし、bl / blx(#imm) を列挙

scan_jni_calls.py の「一般化版」です。

例:
  python tools/unicorn/scan_symbol_calls.py --so ref/liblwplocal_95k.so --prefix _ZN6buffer
  python tools/unicorn/scan_symbol_calls.py --so ref/liblwplocal_95k.so --regex '^Java_'
  python tools/unicorn/scan_symbol_calls.py --so ref/liblwplocal_95k.so --name _ZN6buffer5touchEv --name _ZN12bufferconfig3setEP6bufferii
"""

import argparse
import json
import re
import sys
from typing import List, Dict, Any

import lief
import capstone
from capstone.arm import ARM_OP_IMM, ARM_OP_REG


def _pick_symbols(binary: lief.ELF.Binary, names: List[str], prefix: str, regex: str) -> List[lief.ELF.Symbol]:
    picked: List[lief.ELF.Symbol] = []
    name_set = set(names or [])

    rx = re.compile(regex) if regex else None

    for sym in binary.dynamic_symbols:
        if not sym.name:
            continue
        if sym.value == 0 or sym.size == 0:
            continue

        ok = False
        if sym.name in name_set:
            ok = True
        if prefix and sym.name.startswith(prefix):
            ok = True
        if rx and rx.search(sym.name):
            ok = True

        if ok:
            picked.append(sym)

    # default: if nothing specified, behave like JNI picker
    if not (name_set or prefix or rx):
        for sym in binary.dynamic_symbols:
            if not sym.name:
                continue
            if sym.value == 0 or sym.size == 0:
                continue
            if sym.name.startswith("Java_") or sym.name == "JNI_OnLoad":
                picked.append(sym)

    picked.sort(key=lambda s: s.name)
    return picked


def _disasm_and_collect_calls(binary: lief.ELF.Binary, sym: lief.ELF.Symbol, max_bytes: int, max_insn: int) -> Dict[str, Any]:
    addr = int(sym.value)
    thumb = bool(addr & 1)
    start = addr & ~1

    mode = capstone.CS_MODE_THUMB if thumb else capstone.CS_MODE_ARM
    md = capstone.Cs(capstone.CS_ARCH_ARM, mode)
    md.detail = True

    try:
        code = bytes(binary.get_content_from_virtual_address(start, max_bytes))
    except Exception as e:
        return {
            "name": sym.name,
            "va": hex(addr),
            "thumb": thumb,
            "error": f"failed to read bytes at VA {hex(start)}: {e}",
        }

    calls = []
    insn_count = 0
    for insn in md.disasm(code, start):
        insn_count += 1
        mnem = insn.mnemonic.lower()

        if mnem in ("bl", "blx"):
            target = None
            kind = "unknown"

            if insn.operands and insn.operands[0].type == ARM_OP_IMM:
                target = int(insn.operands[0].imm)
                kind = "imm"
            elif insn.operands and insn.operands[0].type == ARM_OP_REG:
                kind = f"reg:{insn.op_str.strip()}"

            calls.append({
                "at": hex(insn.address),
                "insn": f"{insn.mnemonic} {insn.op_str}",
                "target": hex(target) if target is not None else None,
                "kind": kind,
            })

        if insn_count >= max_insn:
            break
        # return patterns
        if insn.mnemonic.lower() == "bx" and insn.op_str.strip().lower() == "lr":
            break
        if insn.mnemonic.lower() == "pop" and "pc" in insn.op_str.lower():
            break

    return {
        "name": sym.name,
        "va": hex(addr),
        "thumb": thumb,
        "start": hex(start),
        "bytes_scanned": max_bytes,
        "insn_scanned": insn_count,
        "calls": calls,
    }


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--so", required=True, help="Path to liblwplocal.so (95KB, armeabi-v7a)")
    ap.add_argument("--name", action="append", default=[], help="Exact symbol name (repeatable)")
    ap.add_argument("--prefix", default="", help="Prefix match (e.g. _ZN6buffer)")
    ap.add_argument("--regex", default="", help="Regex match on symbol name")
    ap.add_argument("--max-bytes", type=lambda s: int(s, 0), default=0x400, help="Bytes to scan from function start")
    ap.add_argument("--max-insn", type=lambda s: int(s, 0), default=250, help="Max instructions to disassemble")
    ap.add_argument("--json", dest="json_out", default="", help="Write JSON output to file")
    args = ap.parse_args()

    try:
        binary = lief.parse(args.so)
    except Exception as e:
        print(f"ERROR: lief.parse failed: {e}", file=sys.stderr)
        return 2

    if not isinstance(binary, lief.ELF.Binary):
        print("ERROR: not an ELF binary", file=sys.stderr)
        return 2

    syms = _pick_symbols(binary, args.name, args.prefix, args.regex)
    if not syms:
        print("WARN: no symbols matched")
        return 0

    results = []
    for sym in syms:
        results.append(_disasm_and_collect_calls(binary, sym, args.max_bytes, args.max_insn))

    for r in results:
        if "error" in r:
            print(f"{r['name']} @ {r['va']} thumb={r['thumb']} -> {r['error']}")
            continue
        print(f"{r['name']} @ {r['va']} thumb={r['thumb']} start={r['start']}")
        for c in r["calls"]:
            print(f"  {c['at']}: {c['insn']}  target={c['target']}  ({c['kind']})")
        print()

    if args.json_out:
        with open(args.json_out, "w", encoding="utf-8") as f:
            json.dump(results, f, indent=2, ensure_ascii=False)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
