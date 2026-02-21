#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""resolve_call_targets.py

scan_jni_calls.py の JSON 出力を入力にして、call target のアドレスを
ELF のシンボル名(主に dynsym / symtab)に可能な限り解決して一覧化します。

目的:
  - JNI 入口から呼ばれている「実体」(renderer/Curve 側)を正しく特定し、
    次の C 化(実装)対象を決めやすくする。

例:
  python tools/unicorn/scan_jni_calls.py --so ref/liblwplocal.so --json out/jni_calls.json
  python tools/static/resolve_call_targets.py --so ref/liblwplocal.so --calls out/jni_calls.json
"""

from __future__ import annotations

import argparse
import json
import sys
from dataclasses import dataclass
from typing import Dict, List, Optional, Tuple

import lief


@dataclass
class Sym:
    name: str
    value: int
    size: int


def load_syms(bin_path: str) -> List[Sym]:
    b = lief.parse(bin_path)
    if not isinstance(b, lief.ELF.Binary):
        raise RuntimeError(f"not ELF: {bin_path}")

    out: List[Sym] = []
    # Prefer dynamic symbols but also include symtab if present.
    for s in list(b.dynamic_symbols) + list(b.symbols):
        if not s.name:
            continue
        # value is virtual address.
        out.append(Sym(s.name, int(s.value), int(s.size)))

    # de-dup by (name,value)
    uniq: Dict[Tuple[str, int], Sym] = {}
    for s in out:
        uniq[(s.name, s.value)] = s

    return sorted(uniq.values(), key=lambda x: x.value)


def resolve_exact(syms: List[Sym], addr: int) -> Optional[str]:
    # exact match is safest.
    # Thumb ではシンボル値が (addr|1) で登録される場合があるため、addr と addr+1 の両方を確認します。
    cand = {addr, addr + 1}
    for s in syms:
        if s.value in cand and s.name:
            return s.name
    return None


def resolve_nearest(syms: List[Sym], addr: int) -> Optional[str]:
    # If no exact match, pick the closest preceding symbol within a reasonable range.
    # This is a heuristic; we still print it as "nearest".
    best: Optional[Sym] = None
    # Thumb bit を考慮して、比較用には value&~1 を使います。
    for s in syms:
        sval = s.value & ~1
        if sval <= addr:
            best = s
        else:
            break
    if not best:
        return None
    # Require addr within 0x400 bytes of the symbol start (avoid nonsense matches).
    if (addr - (best.value & ~1)) <= 0x400:
        return best.name
    return None


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--so", required=True, help="解析対象 ELF (.so)")
    ap.add_argument("--calls", required=True, help="scan_jni_calls.py の --json 出力")
    args = ap.parse_args()

    try:
        syms = load_syms(args.so)
        with open(args.calls, "r", encoding="utf-8") as f:
            calls = json.load(f)
    except Exception as e:
        print(f"ERROR: {e}", file=sys.stderr)
        return 2

    # scan_jni_calls.py の JSON は "list[dict]" (各JNI関数) です。
    # 旧形式などに備えて dict 形式も受け付けます。
    fns = []
    if isinstance(calls, list):
        fns = calls
    elif isinstance(calls, dict):
        fns = calls.get("functions", [])
    else:
        raise RuntimeError(f"unexpected JSON type: {type(calls).__name__}")

    # Collect unique targets across all JNI functions.
    targets: Dict[int, int] = {}
    for fn in fns:
        for c in fn.get("calls", []):
            t_raw = c.get("target", 0)
            t = int(t_raw, 0) if isinstance(t_raw, str) else int(t_raw)
            if t:
                targets[t] = targets.get(t, 0) + 1

    items = sorted(targets.items(), key=lambda x: x[0])

    print(f"so: {args.so}")
    print(f"unique targets: {len(items)}\n")

    for addr, nref in items:
        name = resolve_exact(syms, addr)
        if name:
            print(f"0x{addr:08x}  refs={nref:2d}  {name}")
            continue
        near = resolve_nearest(syms, addr)
        if near:
            print(f"0x{addr:08x}  refs={nref:2d}  {near}  (nearest)")
        else:
            print(f"0x{addr:08x}  refs={nref:2d}  (unresolved)")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
