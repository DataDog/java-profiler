#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
# SPDX-License-Identifier: Apache-2.0
"""Summarizes Phase 0 runs: per-metric run-to-run noise, NMT profiler deltas.

Usage: analyze_phase0.py <OUT>   (reads OUT/runs/*.json, writes
OUT/phase0-report.md and OUT/phase0-stats.csv)

Noise classes, per (scenario, metric) in the counters / nmt arms:
  stable  SD <= max(1% of mean, 64 KiB)  -> gate with a tight threshold
  banded  SD <= 5% of mean               -> gate with a k*SD band
  noisy   otherwise                      -> report only
"""
import csv
import json
import statistics
import sys
from collections import defaultdict
from pathlib import Path

KIB = 1024
MIB = 1024 * 1024
SECTIONS = ("counters", "counters_middump", "nmt_kb", "proc_kb")
NMT_FOCUS = ("class", "internal", "thread", "symbol", "tracing", "code", "metaspace",
             "arena_chunk", "native_memory_tracking", "other", "total")


def load(out):
    runs = []
    for p in sorted((out / "runs").glob("*.json")):
        runs.append(json.loads(p.read_text()))
    return runs


def values_by_key(runs):
    """(scenario, arm, section, metric) -> [values in bytes]."""
    vals = defaultdict(list)
    for r in runs:
        for section in SECTIONS:
            scale = KIB if section.endswith("_kb") else 1
            for metric, v in r.get(section, {}).items():
                vals[(r["scenario"], r["arm"], section, metric)].append(v * scale)
    return vals


def stats(xs):
    mean = statistics.fmean(xs)
    sd = statistics.stdev(xs) if len(xs) > 1 else 0.0
    return {
        "n": len(xs), "mean": mean, "sd": sd,
        "cv": sd / mean if mean else 0.0,
        "min": min(xs), "max": max(xs),
    }


def noise_class(s):
    if s["sd"] <= max(0.01 * s["mean"], 64 * KIB):
        return "stable"
    if s["mean"] and s["sd"] <= 0.05 * s["mean"]:
        return "banded"
    return "noisy"


def mib(x):
    return f"{x / MIB:.3f}"


def is_focus_counter(metric):
    # avg_bytes is a moving average of live, and post_flush_max equals max;
    # both are in the CSV but would only repeat other rows in the report.
    return (metric.startswith("native_mem_")
            and not metric.startswith(("native_mem_avg_bytes", "native_mem_post_flush_max_bytes")))


def main():
    out = Path(sys.argv[1])
    runs = load(out)
    if not runs:
        sys.exit(f"no runs under {out / 'runs'}")
    vals = values_by_key(runs)
    table = {k: stats(v) for k, v in vals.items()}

    with open(out / "phase0-stats.csv", "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["scenario", "arm", "section", "metric", "n", "mean", "sd", "cv", "min", "max", "class"])
        for (sc, arm, sec, m), s in sorted(table.items()):
            w.writerow([sc, arm, sec, m, s["n"], round(s["mean"]), round(s["sd"]), f"{s['cv']:.5f}",
                        s["min"], s["max"], noise_class(s)])

    scenarios = sorted({r["scenario"] for r in runs})
    lines = ["# Phase 0: memcheck noise", ""]
    for name in ("profiler-commit.txt", "jdk.txt", "cpus.txt"):
        p = out / name
        if p.exists():
            lines.append(f"- {name.split('.')[0]}: `{p.read_text().strip()}`")
    counts = defaultdict(int)
    for r in runs:
        counts[r["arm"]] += 1
    lines.append("- runs: " + ", ".join(f"{a}={n}" for a, n in sorted(counts.items())))
    lines.append("")
    lines.append("Classes: **stable** SD <= max(1%, 64 KiB); **banded** SD <= 5%; **noisy** otherwise. "
                 "Values in MiB. Zero-valued metrics omitted.")

    for sc in scenarios:
        lines += ["", f"## {sc}", ""]

        lines += ["### Profiler counters (counters arm, final recording)", "",
                  "| metric | n | mean | SD | CV | min..max | class | mean in nmt arm |",
                  "|---|---|---|---|---|---|---|---|"]
        for (s2, arm, sec, m), s in sorted(table.items()):
            if s2 != sc or arm != "counters" or sec != "counters" or not is_focus_counter(m):
                continue
            if s["max"] == 0:
                continue
            other = table.get((sc, "nmt", "counters", m))
            lines.append(f"| `{m}` | {s['n']} | {mib(s['mean'])} | {mib(s['sd'])} | {s['cv']:.2%} | "
                         f"{mib(s['min'])}..{mib(s['max'])} | {noise_class(s)} | "
                         f"{mib(other['mean']) if other else '-'} |")

        lines += ["", "### NMT committed (nmt arm) vs no-profiler control", "",
                  "| category | n | mean | SD | CV | class | noprof mean | profiler delta |",
                  "|---|---|---|---|---|---|---|---|"]
        for cat in NMT_FOCUS:
            s = table.get((sc, "nmt", "nmt_kb", cat))
            if not s:
                continue
            ctl = table.get((sc, "noprof", "nmt_kb", cat))
            delta = mib(s["mean"] - ctl["mean"]) if ctl else "-"
            lines.append(f"| {cat} | {s['n']} | {mib(s['mean'])} | {mib(s['sd'])} | {s['cv']:.2%} | "
                         f"{noise_class(s)} | {mib(ctl['mean']) if ctl else '-'} | {delta} |")

        lines += ["", "### RSS at the sample point", "",
                  "| arm | metric | n | mean | SD |", "|---|---|---|---|---|"]
        for arm in ("counters", "nmt", "noprof"):
            for m in ("VmRSS", "RssAnon"):
                s = table.get((sc, arm, "proc_kb", m))
                if s:
                    lines.append(f"| {arm} | {m} | {s['n']} | {mib(s['mean'])} | {mib(s['sd'])} |")

    (out / "phase0-report.md").write_text("\n".join(lines) + "\n")
    print(f"wrote {out / 'phase0-report.md'} and {out / 'phase0-stats.csv'}")


if __name__ == "__main__":
    main()
