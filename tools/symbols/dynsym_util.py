#!/usr/bin/env python3
import subprocess
import re

# Perfect-match mode: keep linker markers by default.
# (Do NOT ignore __bss_start/_edata/_end. Existence matters; addresses will differ.)
IGNORED_SYMBOLS = set()

def dynsym_defined_names_readelf(so_path: str):
    out = subprocess.check_output(["readelf", "--dyn-syms", "-W", so_path], text=True, errors="replace")
    names = []
    for line in out.splitlines():
        m = re.match(r"\s*\d+:\s+[0-9a-fA-F]+\s+\d+\s+\S+\s+\S+\s+\S+\s+(\S+)\s+(\S+)\s*$", line)
        if not m:
            continue
        ndx = m.group(1)
        name = m.group(2)
        if ndx == "UND":
            continue
        if not name:
            continue
        if name in IGNORED_SYMBOLS:
            continue
        names.append(name)
    return names

def dynsym_defined_names_nm(so_path: str):
    out = subprocess.check_output(["nm", "-D", "--defined-only", so_path], text=True, errors="replace")
    names = []
    for line in out.splitlines():
        parts = line.split()
        if len(parts) < 3:
            continue
        name = parts[2]
        if not name:
            continue
        if name in IGNORED_SYMBOLS:
            continue
        names.append(name)
    return names

def dynsym_defined_names(so_path: str, prefer_readelf=True):
    if prefer_readelf:
        try:
            return dynsym_defined_names_readelf(so_path)
        except Exception:
            return dynsym_defined_names_nm(so_path)
    return dynsym_defined_names_nm(so_path)
