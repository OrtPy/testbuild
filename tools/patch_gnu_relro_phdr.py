#!/usr/bin/env python3
"""ELF32 little-endian PHDR patcher.

What it does:
  - Normalizes PT_LOAD p_align to 0x1000 (reference uses 0x1000).
    (NDK r10c ld.gold has been observed to emit garbage here in some layouts.)
  - Optionally patches PT_GNU_RELRO (either with explicit values or auto-computed values).

Why auto mode exists:
  In EF2_LINK_LAYOUT=matchrelrohdr, we intentionally reserve a GNU_RELRO PHDR
  as a placeholder (no section mapping). ld.gold then emits it as 0/0/0.
  This breaks loaders/emulators that expect a sane GNU_RELRO range.

Usage:
  Explicit:
    patch_gnu_relro_phdr.py <so> <p_offset_hex> <p_vaddr_hex> <p_paddr_hex> <filesz_hex> <memsz_hex> <align_hex>

  Auto (recommended for CI/unidbg):
    patch_gnu_relro_phdr.py <so> --auto

Auto mode computes GNU_RELRO as:
  start = RW PT_LOAD start
  end   = max(.fini_array, .init_array, .data.rel.ro, .dynamic, .got, .got.plt end)
  size  = align_up(end-start, 0x8)
"""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

PT_GNU_RELRO = 0x6474e552
PT_LOAD = 1
PF_R = 4
PF_W = 2

PAGE = 0x1000


def die(msg: str, code: int = 1) -> None:
    print(msg, file=sys.stderr)
    sys.exit(code)


def align_up(x: int, a: int) -> int:
    return (x + (a - 1)) & ~(a - 1)


def parse_args() -> argparse.Namespace:
    ap = argparse.ArgumentParser(add_help=True)
    ap.add_argument("so", help="ELF32 LE shared object")
    ap.add_argument(
        "--auto",
        action="store_true",
        help="Auto-compute GNU_RELRO from RW LOAD + known RELRO sections",
    )
    ap.add_argument("vals", nargs="*", help="explicit hex values (offset vaddr paddr filesz memsz align)")
    return ap.parse_args()


def read_ehdr_fields(b: bytes) -> dict:
    # ELF32_Ehdr offsets
    return {
        "e_phoff": struct.unpack_from("<I", b, 28)[0],
        "e_phentsize": struct.unpack_from("<H", b, 42)[0],
        "e_phnum": struct.unpack_from("<H", b, 44)[0],
        "e_shoff": struct.unpack_from("<I", b, 32)[0],
        "e_shentsize": struct.unpack_from("<H", b, 46)[0],
        "e_shnum": struct.unpack_from("<H", b, 48)[0],
        "e_shstrndx": struct.unpack_from("<H", b, 50)[0],
    }


def parse_sections(b: bytes, eh: dict) -> dict[str, tuple[int, int, int]]:
    """Return name -> (sh_addr, sh_offset, sh_size)."""
    shoff = eh["e_shoff"]
    shentsz = eh["e_shentsize"]
    shnum = eh["e_shnum"]
    shstrndx = eh["e_shstrndx"]

    if shoff == 0 or shnum == 0:
        return {}
    if shentsz != 40:
        print(f"[WARN] unexpected e_shentsize={shentsz} (expected 40)", file=sys.stderr)

    shstr_off = shoff + shstrndx * shentsz
    (_, _, _, _, shstr_offset, shstr_size, _, _, _, _) = struct.unpack_from("<IIIIIIIIII", b, shstr_off)
    shstr = b[shstr_offset : shstr_offset + shstr_size]

    def get_name(noff: int) -> str:
        if noff >= len(shstr):
            return ""
        end = shstr.find(b"\x00", noff)
        if end < 0:
            end = len(shstr)
        return shstr[noff:end].decode("utf-8", errors="replace")

    out: dict[str, tuple[int, int, int]] = {}
    for i in range(shnum):
        off = shoff + i * shentsz
        (sh_name, sh_type, sh_flags, sh_addr, sh_offset, sh_size, sh_link, sh_info, sh_addralign, sh_entsize) = struct.unpack_from(
            "<IIIIIIIIII", b, off
        )
        name = get_name(sh_name)
        if name:
            out[name] = (int(sh_addr), int(sh_offset), int(sh_size))
    return out


def auto_relro_values(b: bytes, eh: dict) -> list[int] | None:
    """Compute GNU_RELRO values from RW LOAD + section ends."""
    e_phoff = eh["e_phoff"]
    e_phentsize = eh["e_phentsize"]
    e_phnum = eh["e_phnum"]
    if e_phentsize != 32:
        die(f"unexpected e_phentsize={e_phentsize}")

    rw_load: tuple[int, int, int, int, int] | None = None
    has_relro = False
    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align = struct.unpack_from("<IIIIIIII", b, off)
        if p_type == PT_GNU_RELRO:
            has_relro = True
        if p_type == PT_LOAD and (p_flags & PF_W):
            rw_load = (int(p_offset), int(p_vaddr), int(p_paddr), int(p_filesz), int(p_memsz))

    if not has_relro:
        return None
    if rw_load is None:
        die("RW PT_LOAD not found; cannot auto-compute GNU_RELRO")

    secmap = parse_sections(b, eh)
    relro_secs = [
        ".fini_array",
        ".init_array",
        ".data.rel.ro",
        ".dynamic",
        ".got",
        ".got.plt",
    ]

    start_off, start_va, start_pa, _, rw_memsz = rw_load
    delta = start_va - start_off

    end_va = start_va
    for s in relro_secs:
        if s in secmap:
            a, o, sz = secmap[s]
            end_va = max(end_va, a + sz)

    size = align_up(end_va - start_va, 0x8)
    if size <= 0:
        die("computed GNU_RELRO size <= 0; check sections")
    if size > rw_memsz:
        print(f"[WARN] computed GNU_RELRO size {size:#x} exceeds RW LOAD memsz {rw_memsz:#x}; clamping", file=sys.stderr)
        size = rw_memsz

    end_off = end_va - delta
    filesz = align_up(end_off - start_off, 0x8)
    if filesz <= 0:
        filesz = size

    return [start_off, start_va, start_pa, filesz, size, 0x8]


def fix_load_overlap(b: bytearray, eh: dict, page: int = PAGE) -> tuple[bool, str]:
    """Best-effort fix for strict loaders/emulators (unidbg+unicorn).

    Android's loader tolerates some PHDR layouts that unidbg struggles with.
    A common failure case is *page-level* overlap between the RX LOAD and RW LOAD.

    Example (bad for unidbg):
      RX p_memsz ends inside the same 0x1000 page that RW begins in.
      Even if rx_va_end < rw_va, the *rounded* RX mapping still covers rw_page_start.
      unidbg then fails to map the RW pages and crashes during PtLoadData.writeTo.

    Strategy (only for unidbgfix copies):
      1) If RW PT_LOAD is not page-aligned, first normalize it (handled separately).
      2) Ensure RX mapping does not cover RW's page start:
           align_up(rx_va + rx_memsz, page) <= align_down(rw_va, page)
         If violated, clamp RX p_filesz/p_memsz to rw_page_start.
      3) Also keep classic non-overlap guarantees:
           rx_off + rx_filesz <= rw_off
           rx_va  + rx_memsz  <= rw_va

    This does NOT move section contents; it only adjusts PHDR sizes.
    Intended for dynamic tracing (unidbgfix), not for final hash-perfect outputs.
    """

    e_phoff = eh["e_phoff"]
    e_phentsize = eh["e_phentsize"]
    e_phnum = eh["e_phnum"]

    rx_i = None
    rw_i = None
    rx = None
    rw = None

    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align = struct.unpack_from("<IIIIIIII", b, off)
        if p_type != PT_LOAD:
            continue
        if (p_flags & PF_W) and rw is None:
            rw_i = i
            rw = (int(p_offset), int(p_vaddr), int(p_filesz), int(p_memsz))
        elif (not (p_flags & PF_W)) and rx is None:
            rx_i = i
            rx = (int(p_offset), int(p_vaddr), int(p_filesz), int(p_memsz))

    if rx is None or rw is None or rx_i is None or rw_i is None:
        return (False, "[WARN] PT_LOAD RX/RW pair not found; overlap fix skipped")

    rx_off, rx_va, rx_filesz, rx_memsz = rx
    rw_off, rw_va, rw_filesz, rw_memsz = rw

    def align_down(x: int, a: int) -> int:
        return x & ~(a - 1)

    changed = False
    msgs = []

    # --- Page-level overlap check (critical for unidbg) ---
    rw_page_start = align_down(rw_va, page)
    rx_page_end = align_up(rx_va + rx_memsz, page)
    if rx_page_end > rw_page_start:
        new_memsz = max(0, rw_page_start - rx_va)
        new_filesz = min(rx_filesz, new_memsz)
        msgs.append(
            f"[FIX] PT_LOAD(RX) page-overlap: rx_page_end={rx_page_end:#x} > rw_page_start={rw_page_start:#x} -> filesz={new_filesz:#x} memsz={new_memsz:#x}"
        )
        off = e_phoff + rx_i * e_phentsize
        struct.pack_into("<I", b, off + 16, new_filesz)  # p_filesz
        struct.pack_into("<I", b, off + 20, new_memsz)   # p_memsz
        changed = True
        rx_filesz, rx_memsz = new_filesz, new_memsz

    # --- Classic file overlap check ---
    rx_file_end = rx_off + rx_filesz
    if rx_file_end > rw_off:
        new_filesz = max(0, rw_off - rx_off)
        msgs.append(f"[FIX] PT_LOAD(RX) file overlap: end={rx_file_end:#x} > rw_off={rw_off:#x} -> filesz={new_filesz:#x}")
        off = e_phoff + rx_i * e_phentsize
        struct.pack_into("<I", b, off + 16, new_filesz)
        if rx_memsz > new_filesz:
            struct.pack_into("<I", b, off + 20, new_filesz)
            msgs.append(f"[FIX] PT_LOAD(RX) memsz clamped to filesz: memsz={new_filesz:#x}")
        changed = True
        rx_filesz = new_filesz
        rx_memsz = min(rx_memsz, new_filesz)

    # --- Classic VA overlap check ---
    rx_va_end = rx_va + rx_memsz
    if rx_va_end > rw_va:
        new_memsz = max(0, rw_va - rx_va)
        msgs.append(f"[FIX] PT_LOAD(RX) VA overlap: end={rx_va_end:#x} > rw_va={rw_va:#x} -> memsz={new_memsz:#x}")
        off = e_phoff + rx_i * e_phentsize
        struct.pack_into("<I", b, off + 20, new_memsz)
        if rx_filesz > new_memsz:
            struct.pack_into("<I", b, off + 16, new_memsz)
            msgs.append(f"[FIX] PT_LOAD(RX) filesz clamped to memsz: filesz={new_memsz:#x}")
        changed = True

    if not msgs:
        msgs.append("[OK] PT_LOAD overlap check: no overlap")

    return (changed, "\n".join(msgs))


def normalize_rw_load_to_page(b: bytearray, eh: dict, page: int = 0x1000) -> tuple[bool, str]:
    """Make RW PT_LOAD friendlier to strict emulators.

    Some loaders/emulators fail when a PT_LOAD starts at a non-page-aligned
    address and its file span crosses into the next page. Real loaders map from
    align_down(vaddr) with a length that includes the page offset, but some
    emulators don't.

    For the first RW PT_LOAD, if (p_offset|p_vaddr) is not page-aligned, we:
      - shift p_offset/p_vaddr/p_paddr down to the page boundary
      - grow p_filesz/p_memsz by the same page offset

    This preserves the in-memory addresses of all original bytes.

    NOTE: This is intended only for "unidbgfix" copies used for tracing.
    """

    e_phoff = eh["e_phoff"]
    e_phentsize = eh["e_phentsize"]
    e_phnum = eh["e_phnum"]

    rw_i = None
    rw = None
    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align = struct.unpack_from("<IIIIIIII", b, off)
        if p_type == PT_LOAD and (p_flags & PF_W):
            rw_i = i
            rw = (int(p_offset), int(p_vaddr), int(p_paddr), int(p_filesz), int(p_memsz))
            break

    if rw_i is None or rw is None:
        return (False, "[WARN] RW PT_LOAD not found; page-align normalize skipped")

    p_offset, p_vaddr, p_paddr, p_filesz, p_memsz = rw
    page_mask = page - 1
    off_mod = p_offset & page_mask
    va_mod = p_vaddr & page_mask

    if off_mod == 0 and va_mod == 0:
        return (False, "[OK] RW PT_LOAD already page-aligned")

    # ELF congruence requirement.
    if off_mod != va_mod:
        return (False, f"[WARN] RW PT_LOAD offset/vaddr mod mismatch: off_mod={off_mod:#x} va_mod={va_mod:#x}; skipped")

    shift = off_mod
    new_offset = p_offset - shift
    new_vaddr = p_vaddr - shift
    new_paddr = p_paddr - shift
    new_filesz = p_filesz + shift
    new_memsz = p_memsz + shift

    off = e_phoff + rw_i * e_phentsize
    struct.pack_into("<I", b, off + 4, new_offset)
    struct.pack_into("<I", b, off + 8, new_vaddr)
    struct.pack_into("<I", b, off + 12, new_paddr)
    struct.pack_into("<I", b, off + 16, new_filesz)
    struct.pack_into("<I", b, off + 20, new_memsz)

    return (
        True,
        "\n".join(
            [
                f"[FIX] RW PT_LOAD page-align: shift={shift:#x}",
                f"      offset {p_offset:#x}->{new_offset:#x}",
                f"      vaddr  {p_vaddr:#x}->{new_vaddr:#x}",
                f"      filesz {p_filesz:#x}->{new_filesz:#x}",
                f"      memsz  {p_memsz:#x}->{new_memsz:#x}",
            ]
        ),
    )


def main() -> int:
    ns = parse_args()
    path = Path(ns.so)
    b = bytearray(path.read_bytes())

    if b[:4] != b"\x7fELF":
        die("not ELF")
    if b[4] != 1 or b[5] != 1:
        die("expected ELF32 little-endian")

    eh = read_ehdr_fields(b)
    e_phoff = eh["e_phoff"]
    e_phentsize = eh["e_phentsize"]
    e_phnum = eh["e_phnum"]
    if e_phentsize != 32:
        die(f"unexpected e_phentsize={e_phentsize}")

    explicit_mode = (not ns.auto)
    vals: list[int] | None

    if ns.auto:
        vals = auto_relro_values(b, eh)
    else:
        if len(ns.vals) != 6:
            die(
                "usage: patch_gnu_relro_phdr.py <so> <p_offset_hex> <p_vaddr_hex> <p_paddr_hex> <filesz_hex> <memsz_hex> <align_hex>\n"
                "   or: patch_gnu_relro_phdr.py <so> --auto"
            )
        vals = [int(x, 16) for x in ns.vals]

    found_relro = False
    load_patched = 0
    relro_patched = 0
    overlap_changed = False
    overlap_msg = ""
    rw_align_changed = False
    rw_align_msg = ""

    for i in range(e_phnum):
        off = e_phoff + i * e_phentsize
        p_type, p_offset, p_vaddr, p_paddr, p_filesz, p_memsz, p_flags, p_align = struct.unpack_from("<IIIIIIII", b, off)

        # Normalize LOAD align to 0x1000.
        if p_type == PT_LOAD and p_align != 0x1000:
            struct.pack_into("<I", b, off + 28, 0x1000)
            load_patched += 1

        if p_type == PT_GNU_RELRO:
            found_relro = True
            if vals is not None:
                n = (
                    PT_GNU_RELRO,
                    vals[0],
                    vals[1],
                    vals[2],
                    vals[3],
                    vals[4],
                    PF_R | PF_W,
                    vals[5],
                )
                struct.pack_into("<IIIIIIII", b, off, *n)
                relro_patched += 1

    # Finally, make the PT_LOAD ranges sane for strict loaders/emulators.
    # (This is best-effort and intended for unidbgfix copies.)
    rw_align_changed, rw_align_msg = normalize_rw_load_to_page(b, eh)
    overlap_changed, overlap_msg = fix_load_overlap(b, eh)

    if not found_relro:
        if explicit_mode:
            die("GNU_RELRO phdr not found")
        print("[WARN] GNU_RELRO phdr not found (auto mode): only normalized PT_LOAD p_align", file=sys.stderr)

    path.write_bytes(b)
    print("patched", path)
    if load_patched:
        print(f"normalized PT_LOAD p_align to 0x1000: {load_patched} entries")
    if relro_patched:
        print(f"patched GNU_RELRO: {relro_patched} entries")
    if rw_align_msg:
        print(rw_align_msg)
    if overlap_msg:
        print(overlap_msg)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
