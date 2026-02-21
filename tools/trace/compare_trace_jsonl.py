#!/usr/bin/env python3
"""Compare two RPC traces (.jsonl) captured from the Curve RPC harness.

This tool focuses on *behavioral* equivalence signals that are stable across builds:
- Call sequence (req events): method names + params (optional)
- Memory dumps (dump events): tag + sha256 (order-sensitive per tag)

It intentionally ignores volatile fields such as pointers, base addresses, timestamps, paths.

Exit codes:
  0: match
  2: mismatch
  3: error
"""

import argparse
import json
import sys
from pathlib import Path
from collections import defaultdict

VOLATILE_KEYS = {
    "ts", "host", "port", "path", "handle", "ptr", "moduleBase", "mapAddr",
    "counterAddr", "rendererInterfacePtr", "rendererPtr", "curvePtr",
    "globalsSource", "data_b64", "size"
}

def load_jsonl(p: Path):
    out = []
    with p.open("r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            out.append(json.loads(line))
    return out

def normalize_req(req, drop_params=False):
    if not isinstance(req, dict):
        return req
    d = dict(req)
    # drop volatiles
    for k in list(d.keys()):
        if k in VOLATILE_KEYS:
            d.pop(k, None)
    if drop_params and "params" in d:
        d["params"] = "<dropped>"
    return d

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--gold", required=True, help="golden/original trace jsonl")
    ap.add_argument("--cand", required=True, help="candidate trace jsonl")
    ap.add_argument("--drop-params", action="store_true", help="ignore req.params")
    ap.add_argument("--max", type=int, default=200, help="max mismatches to print")
    args = ap.parse_args()

    gold = load_jsonl(Path(args.gold))
    cand = load_jsonl(Path(args.cand))

    # req sequence
    gold_req = [(e.get("name"), normalize_req(e.get("req"), args.drop_params))
                for e in gold if e.get("event") == "req"]
    cand_req = [(e.get("name"), normalize_req(e.get("req"), args.drop_params))
                for e in cand if e.get("event") == "req"]

    ok = True
    if gold_req != cand_req:
        ok = False
        print("REQ SEQUENCE MISMATCH")
        m = min(len(gold_req), len(cand_req))
        for i in range(m):
            if gold_req[i] != cand_req[i]:
                print(f"  at #{i}:")
                print(f"    gold: {gold_req[i]}")
                print(f"    cand: {cand_req[i]}")
                break
        if len(gold_req) != len(cand_req):
            print(f"  gold req count={len(gold_req)} cand req count={len(cand_req)}")

    # dump sha series by tag (order-sensitive)
    def dump_series(trace):
        d = defaultdict(list)
        for e in trace:
            if e.get("event") == "dump":
                tag = e.get("tag")
                sha = e.get("sha256")
                if tag and sha:
                    d[tag].append(sha)
        return d

    gds = dump_series(gold)
    cds = dump_series(cand)

    # compare tags union
    all_tags = sorted(set(gds.keys()) | set(cds.keys()))
    mism = 0
    for tag in all_tags:
        ga = gds.get(tag, [])
        ca = cds.get(tag, [])
        if ga != ca:
            ok = False
            mism += 1
            print(f"DUMP SERIES MISMATCH tag='{tag}': gold={len(ga)} cand={len(ca)}")
            # print first mismatch
            mm = min(len(ga), len(ca))
            for i in range(mm):
                if ga[i] != ca[i]:
                    print(f"  at #{i}: gold={ga[i]} cand={ca[i]}")
                    break
            if mism >= args.max:
                print("...too many mismatches, stopping.")
                break

    if ok:
        print("OK: traces match (req sequence + dump sha256 series)")
        return 0
    return 2

if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception as e:
        print("ERROR:", e, file=sys.stderr)
        raise SystemExit(3)
