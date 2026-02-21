#!/usr/bin/env python3
"""Patch a few ELF header fields to match a known reference layout.

This is intentionally minimal and deterministic.
Targets: ELF32 little-endian shared objects (armeabi-v7a).

Patches:
  - Section header: .comment -> sh_entsize = 1
  - Section header: .bss     -> sh_size    = 0x865
  - Program header: RW PT_LOAD -> p_memsz  = 0x0c65

If current values already match, it leaves the file unchanged.
"""

from __future__ import annotations

import argparse
import os
import struct
import sys
from dataclasses import dataclass

EI_CLASS = 4
EI_DATA = 5
ELFCLASS32 = 1
ELFDATA2LSB = 1

PT_LOAD = 1
PF_X = 1
PF_W = 2
PF_R = 4


@dataclass
class Elf32_Ehdr:
    e_ident: bytes
    e_type: int
    e_machine: int
    e_version: int
    e_entry: int
    e_phoff: int
    e_shoff: int
    e_flags: int
    e_ehsize: int
    e_phentsize: int
    e_phnum: int
    e_shentsize: int
    e_shnum: int
    e_shstrndx: int


def read_ehdr(buf: bytes) -> Elf32_Ehdr:
    if len(buf) < 52:
        raise ValueError("File too small for ELF32 header")
    e_ident = buf[:16]
    if e_ident[:4] != b"\x7fELF":
        raise ValueError("Not an ELF file")
    if e_ident[EI_CLASS] != ELFCLASS32:
        raise ValueError("Not ELF32")
    if e_ident[EI_DATA] != ELFDATA2LSB:
        raise ValueError("Not little-endian")

    # Elf32_Ehdr (little):
    # 16s H H I I I I I H H H H H H
    tup = struct.unpack_from("<16sHHIIIIIHHHHHH", buf, 0)
    return Elf32_Ehdr(*tup)


def u32_at(buf: bytearray, off: int) -> int:
    return struct.unpack_from("<I", buf, off)[0]


def set_u32(buf: bytearray, off: int, val: int) -> None:
    struct.pack_into("<I", buf, off, val & 0xFFFFFFFF)


def set_u16(buf: bytearray, off: int, val: int) -> None:
    struct.pack_into("<H", buf, off, val & 0xFFFF)


def read_cstr(blob: bytes, off: int) -> str:
    end = blob.find(b"\x00", off)
    if end < 0:
        return ""
    return blob[off:end].decode("utf-8", errors="replace")


def patch_elf(path: str, *, dry_run: bool = False) -> int:
    with open(path, "rb") as f:
        buf = bytearray(f.read())

    eh = read_ehdr(buf)

    # Validate table bounds
    if eh.e_phoff == 0 or eh.e_phnum == 0:
        raise ValueError("No program header table")
    if eh.e_shoff == 0 or eh.e_shnum == 0:
        raise ValueError("No section header table")

    ph_end = eh.e_phoff + eh.e_phnum * eh.e_phentsize
    sh_end = eh.e_shoff + eh.e_shnum * eh.e_shentsize
    if ph_end > len(buf) or sh_end > len(buf):
        raise ValueError("Header tables out of range")

    # Read section header string table
    shstr_off = eh.e_shoff + eh.e_shstrndx * eh.e_shentsize
    if shstr_off + 40 > len(buf):
        raise ValueError("shstr header out of range")

    # Elf32_Shdr: name,type,flags,addr,off,size,link,info,addralign,entsize
    sh_name, sh_type, sh_flags, sh_addr, sh_off, sh_size, sh_link, sh_info, sh_addralign, sh_entsize = struct.unpack_from(
        "<IIIIIIIIII", buf, shstr_off
    )
    shstrtab = bytes(buf[sh_off : sh_off + sh_size])

    idx_comment = None
    idx_bss = None

    # Locate sections
    for i in range(eh.e_shnum):
        off = eh.e_shoff + i * eh.e_shentsize
        name_off = u32_at(buf, off + 0)
        sec_name = read_cstr(shstrtab, name_off)
        if sec_name == ".comment":
            idx_comment = i
        elif sec_name == ".bss":
            idx_bss = i

    changed = False

    # Patch .comment sh_entsize
    if idx_comment is not None:
        off = eh.e_shoff + idx_comment * eh.e_shentsize
        cur_entsize = u32_at(buf, off + 36)
        if cur_entsize != 1:
            set_u32(buf, off + 36, 1)
            changed = True

    # Patch .bss sh_size
    if idx_bss is not None:
        off = eh.e_shoff + idx_bss * eh.e_shentsize
        cur_size = u32_at(buf, off + 20)
        if cur_size != 0x865:
            set_u32(buf, off + 20, 0x865)
            changed = True

    # Patch RW PT_LOAD p_memsz
    # Elf32_Phdr: type,offset,vaddr,paddr,filesz,memsz,flags,align
    for i in range(eh.e_phnum):
        off = eh.e_phoff + i * eh.e_phentsize
        p_type, p_off, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align = struct.unpack_from(
            "<IIIIIIII", buf, off
        )
        if p_type != PT_LOAD:
            continue
        if (p_flags & (PF_R | PF_W)) == (PF_R | PF_W) and (p_flags & PF_X) == 0:
            # RW LOAD (data)
            if p_memsz != 0x0C65:
                # sanity: must remain >= filesz
                if 0x0C65 < p_filesz:
                    raise ValueError(f"Ref memsz < filesz (filesz=0x{p_filesz:x})")
                set_u32(buf, off + 20, 0x0C65)
                changed = True
            break

    if not changed:
        return 0

    if dry_run:
        return 1

    tmp = path + ".tmp"
    with open(tmp, "wb") as f:
        f.write(buf)
    os.replace(tmp, path)
    return 1


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("elf", help="Path to ELF (ELF32 little-endian)")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    try:
        rc = patch_elf(args.elf, dry_run=args.dry_run)
    except Exception as e:
        print(f"[elf_patch_headers] ERROR: {e}", file=sys.stderr)
        return 2

    if rc == 0:
        print("[elf_patch_headers] OK: no changes")
    elif args.dry_run:
        print("[elf_patch_headers] would patch")
    else:
        print("[elf_patch_headers] patched")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
