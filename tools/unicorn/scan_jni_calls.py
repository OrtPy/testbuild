#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""scan_jni_calls.py

95KB版 liblwplocal.so を対象に:
- dynsym から Java_*/JNI_OnLoad を抽出
- 関数先頭の命令列を Capstone で逆アセンブル
- 直接ターゲットを持つ bl / blx(#imm) を列挙

用途:
- 「JNIからどこへ飛ぶか」を静的に把握し、
  次のエミュレーション/差分実装の起点にする。

注意:
- Thumb関数はシンボルアドレスの bit0=1 を見て判定します。
"""

import argparse
import json
import sys
from typing import Dict, List, Any

import lief
import capstone
from capstone.arm import ARM_OP_IMM, ARM_OP_REG


def _get_dynsym_jni(binary: lief.ELF.Binary) -> List[lief.ELF.Symbol]:
    out = []
    for sym in binary.dynamic_symbols:
        if not sym.name:
            continue
        if sym.value == 0 or sym.size == 0:
            continue
        if sym.name.startswith("Java_") or sym.name == "JNI_OnLoad":
            out.append(sym)
    out.sort(key=lambda s: s.name)
    return out


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
    ap.add_argument("--max-bytes", type=lambda s: int(s, 0), default=0x400, help="Bytes to scan from function start (accepts 0x... as well)")
    ap.add_argument("--max-insn", type=lambda s: int(s, 0), default=200, help="Max instructions to disassemble (accepts 0x... as well)")
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

    syms = _get_dynsym_jni(binary)
    if not syms:
        print("WARN: no Java_*/JNI_OnLoad found in dynsym")
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
