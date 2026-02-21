#!/usr/bin/env python3
"""Generate a C-only compatibility exports file for armeabi-v7a.

We keep a reference list of *defined* dynsym exports from the original
Xperia Live Wallpaper liblwplocal.so (armeabi-v7a) in:

  ref/reference/exports_armeabi-v7a_dynsym_defined.tsv

This script turns that list into a C file that defines every symbol (except
the real JNI entry points which are implemented elsewhere) as a lightweight
stub. This preserves the exported symbol surface while we progressively
replace stubs with real cified implementations.
"""

from __future__ import annotations


# --- Hotfix3: do not generate stubs for libgcc runtime (these must come from libgcc objects) ---
SKIP_ASM_PREFIXES = (
    "_Unwind_", "___Unwind_", "__gnu_Unwind_", "__gnu_unwind_",
    "__restore_core_regs", "restore_core_regs", "__udivsi3",
    "__aeabi_uidiv", "__aeabi_uidivmod", "__aeabi_idivmod",
    "__aeabi_unwind_cpp_pr0", "__aeabi_unwind_cpp_pr1",
)

import argparse
from pathlib import Path


IGNORED = {"__bss_start", "_edata", "_end"}


def parse_tsv(path: Path):
    out = []
    for line in path.read_text(encoding="utf-8", errors="ignore").splitlines():
        line = line.strip()
        if not line:
            continue
        parts = line.split("\t")
        if len(parts) < 2:
            continue
        typ = parts[0]
        name = parts[1]
        bind = parts[2] if len(parts) > 2 else ""
        out.append((typ, name, bind))
    return out


def generate(entries) -> str:
    funcs = [e for e in entries if e[0] == "FUNC" and not e[1].startswith("Java_") and e[1] not in IGNORED]
    objs = [e for e in entries if e[0] == "OBJECT" and e[1] not in IGNORED]

    out = []
    out.append(
        "#include <stdint.h>\n"
        "#include <stddef.h>\n"
        "#include \"ef2/platform.h\"\n\n"
        "#if defined(__arm__) && !defined(__aarch64__)\n\n"
        "/* Auto-generated. See tools/symbols/gen_compat_exports_c.py */\n\n"
        "#define EF2_COMPAT_EXPORT __attribute__((visibility(\\\"default\\\"), used))\n\n"
        "static inline uintptr_t ef2_compat_ret0(const char* who) {\n  ef2_log_print(5 /* WARN */, \"EF2\", \"[STUB] %s called (returns 0)\", who ? who : \"(null)\");\n  return 0;\n}\n\n"
    )

    out.append("/* ---- OBJECT symbols ---- */\n")
    for i, (_typ, name, _bind) in enumerate(objs, start=1):
        if name.startswith("_ZTV"):
            out.append(f"EF2_COMPAT_EXPORT void* ef2_compat_obj_{i:04d}[64] __asm__(\"{name}\");\n")
        elif name.startswith("lodepng_default_"):
            out.append(f"EF2_COMPAT_EXPORT uint8_t ef2_compat_obj_{i:04d}[64] __asm__(\"{name}\");\n")
        else:
            out.append(f"EF2_COMPAT_EXPORT uintptr_t ef2_compat_obj_{i:04d} __asm__(\"{name}\");\n")

    out.append("\n/* ---- FUNC symbols ---- */\n")
    for i, (_typ, name, _bind) in enumerate(funcs, start=1):
        out.append(f"EF2_COMPAT_EXPORT uintptr_t ef2_compat_fn_{i:04d}(void) __asm__(\"{name}\");\n")
        out.append(f"uintptr_t ef2_compat_fn_{i:04d}(void) {{ return ef2_compat_ret0(); }}\n")

    out.append("\n#endif\n")
    return "".join(out)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--ref", required=True, help="reference TSV")
    ap.add_argument("--out", required=True, help="output C file")
    args = ap.parse_args()

    ref = Path(args.ref)
    out_path = Path(args.out)

    text = generate(parse_tsv(ref))
    out_path.write_text(text, encoding="utf-8")
    print(f"Wrote {out_path} ({len(text.splitlines())} lines)")


if __name__ == "__main__":
    main()
