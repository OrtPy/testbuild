#!/usr/bin/env python3
"""Summarize Curve memory diffs from ef2_fix37 trace JSONL.

Usage:
  python tools/trace_analyze_curve.py trace.jsonl
"""

import base64
import json
import sys
from typing import List, Tuple


def diff_ranges(a: bytes, b: bytes) -> List[Tuple[int, int]]:
    """Return inclusive [start,end] ranges of differing bytes."""
    n = min(len(a), len(b))
    diffs = [i for i in range(n) if a[i] != b[i]]
    # if lengths differ, treat the tail as differing
    if len(a) != len(b):
        diffs.extend(range(n, max(len(a), len(b))))

    if not diffs:
        return []

    ranges: List[Tuple[int, int]] = []
    s = e = diffs[0]
    for i in diffs[1:]:
        if i == e + 1:
            e = i
        else:
            ranges.append((s, e))
            s = e = i
    ranges.append((s, e))
    return ranges


def fmt_ranges(ranges: List[Tuple[int, int]], limit: int = 12) -> str:
    parts = []
    for (s, e) in ranges[:limit]:
        if s == e:
            parts.append(f"0x{s:04X}")
        else:
            parts.append(f"0x{s:04X}-0x{e:04X}")
    if len(ranges) > limit:
        parts.append(f"...(+{len(ranges) - limit} more)")
    return ", ".join(parts)


def main() -> int:
    if len(sys.argv) != 2:
        print(__doc__.strip())
        return 2

    path = sys.argv[1]
    last_call = "(start)"
    dumps = []  # list of (call, sha256, bytes)

    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            e = json.loads(line)
            if e.get("event") == "req":
                last_call = e.get("name") or last_call
            elif e.get("event") == "dump" and e.get("tag") == "curve":
                data = base64.b64decode(e["data_b64"])
                dumps.append((last_call, e.get("sha256", ""), data))

    if len(dumps) < 2:
        print("No adjacent Curve dumps found.")
        return 1

    for i in range(1, len(dumps)):
        prev_call, prev_sha, prev = dumps[i - 1]
        cur_call, cur_sha, cur = dumps[i]
        ranges = diff_ranges(prev, cur)
        changed = sum((e - s + 1) for (s, e) in ranges)
        print(f"[{i:02d}] {prev_call} -> {cur_call}")
        print(f"     size={len(cur)} changed={changed} bytes ranges={len(ranges)}")
        if prev_sha and cur_sha:
            print(f"     sha256 {prev_sha[:8]}.. -> {cur_sha[:8]}..")
        if ranges:
            print(f"     {fmt_ranges(ranges)}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
