#!/usr/bin/env python3
import argparse
import re
from pathlib import Path

TARGETS = [
    r"^\s*\.comment\s+0\s*:\s*\{",
    r"^\s*\.note\.gnu\.gold-version\s+0\s*:\s*\{",
    r"^\s*\.ARM\.attributes\s+0\s*:\s*\{",
]

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("ldscript", type=Path)
    ap.add_argument("--mode", choices=["remove0", "discard"], default="remove0")
    ap.add_argument("--backup", action="store_true", default=True)
    args = ap.parse_args()

    p = args.ldscript
    txt = p.read_text(errors="ignore")

    bak = p.with_suffix(p.suffix + ".bak")
    if args.backup and not bak.exists():
        bak.write_text(txt)

    if args.mode == "remove0":
        # Replace only the section header "<name> 0 :" -> "<name> :"
        txt2 = re.sub(r"^(\s*\.(?:comment|note\.gnu\.gold-version|ARM\.attributes))\s+0\s*:\s*\{",
                     r"\1 : {", txt, flags=re.M)
        p.write_text(txt2)
        print(f"[+] patched (remove0): {p}")
        return

    # discard mode: append /DISCARD/ block (idempotent-ish)
    if "/DISCARD/" in txt:
        print("[!] /DISCARD/ already present; not modifying")
        return

    block = "\n\n/* gold crash triage */\n/DISCARD/ : {\n  *(.comment*)\n  *(.note.gnu.gold-version)\n  *(.ARM.attributes)\n}\n"
    p.write_text(txt + block)
    print(f"[+] patched (discard): {p}")

if __name__ == "__main__":
    main()
