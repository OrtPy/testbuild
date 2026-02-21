#!/usr/bin/env python3
import re
import struct
import subprocess
from pathlib import Path

DT_NEEDED = 1

def parse_section_offsets(so_path: Path, sec_name: str):
    out = subprocess.check_output(["readelf", "-SW", str(so_path)], text=True, errors="replace")
    for line in out.splitlines():
        # Example line (note that one-digit indices are formatted like "[ 3]"):
        #   [15] .dynamic          DYNAMIC         00017ee8 016ee8 000118 08  WA  3   0  4
        m = re.match(r"^\s*\[\s*\d+\]\s+(\S+)\s+\S+\s+\S+\s+(\S+)\s+(\S+)", line)
        if not m:
            continue
        name, off_hex, size_hex = m.group(1), m.group(2), m.group(3)
        if name != sec_name:
            continue
        off = int(off_hex, 16)
        size = int(size_hex, 16)
        return off, size
    raise SystemExit(f"section not found: {sec_name}")

def cstr(buf: bytes, off: int) -> str:
    end = buf.find(b"\x00", off)
    if end < 0:
        return ""
    return buf[off:end].decode("utf-8", errors="replace")

def main():
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("so", help="target .so to patch in place")
    ap.add_argument("--want", default="libm.so,libc.so,libdl.so",
                    help="comma-separated desired order inside DT_NEEDED group")
    args = ap.parse_args()

    so = Path(args.so)
    blob = bytearray(so.read_bytes())

    dyn_off, dyn_size = parse_section_offsets(so, ".dynamic")
    dynstr_off, dynstr_size = parse_section_offsets(so, ".dynstr")
    dynstr = blob[dynstr_off:dynstr_off + dynstr_size]

    entries = []
    for i in range(0, dyn_size, 8):
        tag, val = struct.unpack_from("<iI", blob, dyn_off + i)
        if tag == 0:
            break
        if tag == DT_NEEDED:
            name = cstr(dynstr, val)
            entries.append((dyn_off + i, val, name))

    want = [x.strip() for x in args.want.split(",") if x.strip()]
    target_set = set(want)

    slots = [e for e in entries if e[2] in target_set]
    slots.sort(key=lambda x: x[0])

    if len(slots) != len(want):
        raise SystemExit(f"DT_NEEDED missing/duplicated. found={[s[2] for s in slots]} want={want}")

    name2off = {name: off for (_, off, name) in slots}
    for name in want:
        if name not in name2off:
            raise SystemExit(f"missing DT_NEEDED: {name}")

    for (slot_off, _, _), name in zip(slots, want):
        struct.pack_into("<iI", blob, slot_off, DT_NEEDED, name2off[name])

    so.write_bytes(blob)
    print("patched DT_NEEDED order:", want)

if __name__ == "__main__":
    main()
