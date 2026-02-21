#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Reorder DT_NEEDED entries in an ELF32 shared object by swapping d_val values.

This script does *not* change strings or add/remove dependencies.
It only reorders the DT_NEEDED tags as they appear in .dynamic so that
readelf -d shows the desired order.

Usage:
  python3 tools/fix_needed_order.py <path/to/lib.so>

You can customize DESIRED below.
"""

from __future__ import annotations

import os
import struct
import sys
from typing import List, Tuple

DT_NEEDED = 1

# Desired DT_NEEDED order for liblwplocal.so (armeabi-v7a)
DESIRED = [
    b"libgnustl_shared.so",
    b"libGLESv2.so",
    b"libandroid.so",
    b"liblog.so",
    b"libstdc++.so",
    b"libm.so",
    b"libc.so",
    b"libdl.so",
]


def read_cstr(blob: bytes, off: int) -> bytes:
    end = blob.find(b"\x00", off)
    if end < 0:
        return blob[off:]
    return blob[off:end]


def die(msg: str) -> None:
    print(f"[fix_needed_order] {msg}", file=sys.stderr)
    sys.exit(2)


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: fix_needed_order.py <elf.so>", file=sys.stderr)
        return 2

    path = sys.argv[1]
    data = bytearray(open(path, "rb").read())

    if data[0:4] != b"\x7fELF":
        die("not an ELF")
    ei_class = data[4]
    ei_data = data[5]
    if ei_class != 1:
        die("only ELFCLASS32 supported")
    if ei_data == 1:
        endian = "<"  # little
    elif ei_data == 2:
        endian = ">"  # big
    else:
        die("unknown endianness")

    # Elf32_Ehdr
    # e_shoff @ 0x20, e_shentsize @ 0x2E, e_shnum @ 0x30, e_shstrndx @ 0x32
    e_shoff, = struct.unpack_from(endian + "I", data, 0x20)
    e_shentsize, = struct.unpack_from(endian + "H", data, 0x2E)
    e_shnum, = struct.unpack_from(endian + "H", data, 0x30)
    e_shstrndx, = struct.unpack_from(endian + "H", data, 0x32)

    if e_shoff == 0 or e_shnum == 0:
        die("missing section headers")

    def shdr(i: int) -> Tuple[int, int, int, int, int, int, int, int, int, int]:
        off = e_shoff + i * e_shentsize
        # Elf32_Shdr: name,type,flags,addr,offset,size,link,info,addralign,entsize
        return struct.unpack_from(endian + "IIIIIIIIII", data, off)

    # Read section header string table
    sh_name, sh_type, sh_flags, sh_addr, sh_offset, sh_size, sh_link, sh_info, sh_addralign, sh_entsize = shdr(e_shstrndx)
    shstr = bytes(data[sh_offset: sh_offset + sh_size])

    dyn_sec = None
    dynstr_sec = None

    for i in range(e_shnum):
        name_off, stype, sflags, saddr, soff, ssize, slink, sinfo, salign, sentsize = shdr(i)
        name = read_cstr(shstr, name_off)
        if name == b".dynamic":
            dyn_sec = (soff, ssize, sentsize)
        elif name == b".dynstr":
            dynstr_sec = (soff, ssize)

    if dyn_sec is None or dynstr_sec is None:
        die(".dynamic or .dynstr not found")

    dyn_off, dyn_size, dyn_entsz = dyn_sec
    dynstr_off, dynstr_size = dynstr_sec
    if dyn_entsz == 0:
        dyn_entsz = 8

    dynstr = bytes(data[dynstr_off: dynstr_off + dynstr_size])

    # Parse dynamic entries
    needed_idx: List[int] = []
    needed_vals: List[int] = []
    needed_names: List[bytes] = []

    for n in range(0, dyn_size, dyn_entsz):
        tag, val = struct.unpack_from(endian + "II", data, dyn_off + n)
        if tag == DT_NEEDED:
            needed_idx.append(n)
            needed_vals.append(val)
            needed_names.append(read_cstr(dynstr, val))

    if not needed_idx:
        die("no DT_NEEDED found")

    # Validate content
    if set(needed_names) != set(DESIRED):
        die("DT_NEEDED set mismatch.\n" +
            f"  current: {needed_names}\n  desired: {DESIRED}")

    # Build map name -> val
    name_to_val = {name: val for name, val in zip(needed_names, needed_vals)}

    # Rewrite d_val in DT_NEEDED entries in-place
    for slot_i, name in enumerate(DESIRED):
        n_off = needed_idx[slot_i]
        new_val = name_to_val[name]
        struct.pack_into(endian + "I", data, dyn_off + n_off + 4, new_val)

    tmp = path + ".tmp"
    with open(tmp, "wb") as f:
        f.write(data)
    os.replace(tmp, path)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
