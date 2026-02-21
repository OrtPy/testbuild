#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compare a dynamic log bundle against the golden bundle.

This is *not* about 'latest' logs. The golden bundle is a suite; this tool
finds the closest matching scenario using GL call-count vectors, then diffs
key text outputs.

Usage:
  python tools/compare_dynamic_logs.py \
    --golden-zip golden_logs/lwp_all_logs_gltrace_unidbg.zip \
    --golden-index golden_logs/golden_index.json \
    --run-zip path/to/your_dynamic_logs.zip \
    --out reports/dynamic_diff.md

It also supports --run-dir instead of --run-zip.

Outputs a Markdown report with:
  - scenario match (unidbg)
  - gles call-count deltas
  - unified diffs for key files (truncated)
"""

from __future__ import annotations

import argparse
import difflib
import io
import json
import os
import re
import zipfile
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple

KEY_GLES = [
    "glDrawElements",
    "glGetUniformLocation",
    "glGetActiveUniform",
    "glUniform1fv",
    "glUniform2fv",
    "glUniform4fv",
    "glUseProgram",
    "glBindTexture",
]


def parse_kv_text(txt: str) -> Dict[str, int]:
    out: Dict[str, int] = {}
    for line in txt.splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        m = re.match(r"([^\s:]+)[:\s]+(\d+)$", line)
        if m:
            out[m.group(1)] = int(m.group(2))
    return out


@dataclass
class BundleReader:
    """Read files from either a zip or a directory."""

    zip_path: Optional[Path] = None
    dir_path: Optional[Path] = None

    def __post_init__(self) -> None:
        if (self.zip_path is None) == (self.dir_path is None):
            raise ValueError("Provide exactly one of zip_path or dir_path")
        if self.zip_path is not None:
            self._zip = zipfile.ZipFile(self.zip_path)
        else:
            self._zip = None

    def namelist(self) -> List[str]:
        if self._zip is not None:
            return self._zip.namelist()
        assert self.dir_path is not None
        out: List[str] = []
        for p in self.dir_path.rglob("*"):
            if p.is_file():
                out.append(p.as_posix().replace(self.dir_path.as_posix() + "/", ""))
        return out

    def read_text(self, relpath: str, max_bytes: int = 5_000_000) -> str:
        if self._zip is not None:
            data = self._zip.read(relpath)
        else:
            assert self.dir_path is not None
            data = (self.dir_path / relpath).read_bytes()
        if len(data) > max_bytes:
            data = data[:max_bytes]
        return data.decode("utf-8", errors="replace")

    def has(self, relpath: str) -> bool:
        if self._zip is not None:
            try:
                self._zip.getinfo(relpath)
                return True
            except KeyError:
                return False
        assert self.dir_path is not None
        return (self.dir_path / relpath).is_file()


@dataclass
class UnidbgScenario:
    base: str
    gles_path: str
    gles: Dict[str, int]


def extract_unidbg_scenarios(reader: BundleReader) -> List[UnidbgScenario]:
    names = reader.namelist()
    gles_paths = [n for n in names if n.startswith("unidbg/") and n.endswith("gles_call_count.txt")]
    scenarios: List[UnidbgScenario] = []
    for p in sorted(gles_paths):
        base = p.rsplit("/", 1)[0]
        gles = parse_kv_text(reader.read_text(p))
        scenarios.append(UnidbgScenario(base=base, gles_path=p, gles=gles))
    return scenarios


def l1_distance(a: Dict[str, int], b: Dict[str, int], keys: List[str]) -> int:
    return sum(abs(a.get(k, 0) - b.get(k, 0)) for k in keys)


def unified_diff(a: str, b: str, fromfile: str, tofile: str, max_lines: int = 400) -> str:
    al = a.splitlines(keepends=False)
    bl = b.splitlines(keepends=False)
    diff = list(difflib.unified_diff(al, bl, fromfile=fromfile, tofile=tofile, lineterm=""))
    if len(diff) > max_lines:
        diff = diff[:max_lines] + [f"... (truncated, {len(diff)-max_lines} more lines)"]
    return "\n".join(diff)


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--golden-zip", required=True)
    ap.add_argument("--golden-index", required=True)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--run-zip")
    g.add_argument("--run-dir")
    ap.add_argument("--out", required=True)
    args = ap.parse_args()

    golden_zip = Path(args.golden_zip)
    golden_index = json.loads(Path(args.golden_index).read_text(encoding="utf-8"))

    golden_reader = BundleReader(zip_path=golden_zip)
    run_reader = BundleReader(zip_path=Path(args.run_zip)) if args.run_zip else BundleReader(dir_path=Path(args.run_dir))

    # Pick best unidbg scenario
    run_scenarios = extract_unidbg_scenarios(run_reader)
    if not run_scenarios:
        report = "# Dynamic diff report\n\nNo unidbg gles_call_count.txt found in run bundle.\n"
        Path(args.out).parent.mkdir(parents=True, exist_ok=True)
        Path(args.out).write_text(report, encoding="utf-8")
        return 0

    # Prefer canonical if present
    canonical = golden_index.get("canonical", {}).get("unidbg", "")
    golden_entries = golden_index.get("unidbg", [])

    # Build quick lookup: base -> entry
    gmap = {e["base"]: e for e in golden_entries if "base" in e}

    def find_golden_best(run_gles: Dict[str, int]) -> Tuple[str, Dict]:
        best_base = ""
        best_ent = {}
        best_d = 10**18
        for e in golden_entries:
            d = l1_distance(run_gles, e.get("gles", {}), KEY_GLES)
            if d < best_d:
                best_d = d
                best_base = e.get("base", "")
                best_ent = e
        return best_base, best_ent

    # choose run scenario with most evidence (prefer step11 trace_out_step11)
    run_pick = None
    for s in run_scenarios:
        if s.base.endswith("step11/logs/trace_out_step11"):
            run_pick = s
            break
    if run_pick is None:
        run_pick = max(run_scenarios, key=lambda s: s.gles.get("glDrawElements", 0))

    if canonical and canonical in gmap:
        golden_pick_base = canonical
        golden_pick_ent = gmap[canonical]
        dist = l1_distance(run_pick.gles, golden_pick_ent.get("gles", {}), KEY_GLES)
        # If canonical is wildly different, fall back to nearest
        if dist > 500:  # heuristic
            golden_pick_base, golden_pick_ent = find_golden_best(run_pick.gles)
    else:
        golden_pick_base, golden_pick_ent = find_golden_best(run_pick.gles)

    # Prepare report
    lines: List[str] = []
    lines.append("# Dynamic diff report")
    lines.append("")
    lines.append(f"Golden ZIP: `{golden_zip.name}`")
    lines.append("")
    lines.append("## Scenario match (unidbg)")
    lines.append(f"- Run scenario: `{run_pick.base}`")
    lines.append(f"- Golden scenario: `{golden_pick_base}`")
    lines.append("")

    # gles deltas
    lines.append("## GLES call-count deltas")
    g_gles = golden_pick_ent.get("gles", {})
    r_gles = run_pick.gles
    lines.append("```")
    for k in KEY_GLES:
        lines.append(f"{k:22s} run={r_gles.get(k,0):6d}  golden={g_gles.get(k,0):6d}  delta={r_gles.get(k,0)-g_gles.get(k,0):+6d}")
    lines.append("```")
    lines.append("")

    # Diff a few key files if present
    def diff_if_exists(rel: str, title: str) -> None:
        if run_reader.has(rel) and golden_reader.has(rel):
            a = golden_reader.read_text(rel)
            b = run_reader.read_text(rel)
            d = unified_diff(a, b, fromfile="golden/"+rel, tofile="run/"+rel)
            lines.append(f"## Diff: {title}")
            lines.append("```diff")
            lines.append(d if d.strip() else "(no diff)")
            lines.append("```")
            lines.append("")

    # Build relpaths for selected scenario
    base = golden_pick_base
    run_base = run_pick.base
    key_files = [
        ("gles_call_count.txt", "gles_call_count"),
        ("internal_func_count.demangled.txt", "internal_func_count.demangled"),
        ("internal_edge_count_top5000.demangled.txt", "internal_edge_count_top5000.demangled"),
        ("assets_open_count.txt", "assets_open_count"),
    ]
    for fn, title in key_files:
        gpath = f"{base}/{fn}"
        rpath = f"{run_base}/{fn}"
        if golden_reader.has(gpath) and run_reader.has(rpath):
            a = golden_reader.read_text(gpath)
            b = run_reader.read_text(rpath)
            d = unified_diff(a, b, fromfile="golden/"+gpath, tofile="run/"+rpath)
            lines.append(f"## Diff: {title}")
            lines.append("```diff")
            lines.append(d if d.strip() else "(no diff)")
            lines.append("```")
            lines.append("")

    # gltrace canonical compare (best effort)
    lines.append("## GLTrace quick check (best effort)")
    gl_canon = golden_index.get("canonical", {}).get("gltrace", "")
    if gl_canon:
        for fn in ("frame_signature_sha256.txt", "buffers_sha256.txt", "textures_sha256.txt"):
            gp = f"{gl_canon}/{fn}"
            # try to find a matching file in run bundle (same relpath if user uses same suite layout)
            if run_reader.has(gp) and golden_reader.has(gp):
                a = golden_reader.read_text(gp)
                b = run_reader.read_text(gp)
                d = unified_diff(a, b, fromfile="golden/"+gp, tofile="run/"+gp)
                lines.append(f"### Diff: {fn}")
                lines.append("```diff")
                lines.append(d if d.strip() else "(no diff)")
                lines.append("```")
            else:
                lines.append(f"- `{fn}`: skipped (run bundle missing `{gp}`)")
    else:
        lines.append("- gltrace canonical not found in golden index")

    Path(args.out).parent.mkdir(parents=True, exist_ok=True)
    Path(args.out).write_text("\n".join(lines) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
