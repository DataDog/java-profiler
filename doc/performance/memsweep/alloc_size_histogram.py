#!/usr/bin/env python3
"""Per-call-site allocation-size histogram, to decide which NM_* categories are
served by mmap (and therefore largely NON-RESIDENT) rather than from the arena.

WHY: `NativeMem` counts bytes *requested*. glibc serves allocations above the
mmap threshold with their own mmap, and those pages are only resident once
touched -- for a large calloc or an uninitialised array they may never be. So a
category whose allocations are mostly above the threshold over-states its RSS
cost. Measured residency of mmap-served chunks (`hblkhd`) is ~0, against ~0.96
for the arena, so the distinction is worth several MiB.

The threshold cannot be assumed to be 128 KiB: glibc's M_MMAP_THRESHOLD is
DYNAMIC, adapting upward to 32 MiB as mmap'd blocks are freed. This therefore
locates the threshold empirically. `ledger.txt` reports
`malloc_live_count_mmapped`, the number of live mmap-served allocations; ranking
call sites by allocation size and taking them until that count is reached
identifies which ones they are, without assuming any value.

`callers.txt` aggregates per call site (bytes, count), so per-site mean size is
`bytes / count`. That is exact for single-allocation sites -- which is what the
large ones are -- and a proxy where a site allocates many mixed sizes.

Usage: alloc_size_histogram.py <dump_dir> [<dump_dir> ...]
"""
import os
import re
import subprocess
import sys

KIB = 1024.0
MIB = 1048576.0

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
DEFAULT_DEBUG = os.path.join(
    REPO, "ddprof-lib/build/lib/main/release/linux/x64/debug/libjavaProfiler.so.debug")

# Source file -> the NM_* category its allocations are recorded under. Derived
# from the NativeMem::record call sites; a file absent here is uninstrumented.
FILE_TO_CAT = {
    "codeCache.cpp": "native_symbols", "codeCache.h": "native_symbols",
    "symbols_linux.cpp": "native_symbols", "libraries.cpp": "native_symbols",
    "dictionary.cpp": "dictionary", "dictionary.h": "dictionary",
    "flightRecorder.cpp": "jfr_buffers", "flightRecorder.h": "jfr_buffers",
    "livenessTracker.cpp": "liveness",
    "threadFilter.cpp": "thread_filter",
    "threadLocalData.cpp": "thread_local",
    "threadLocalDataPool.cpp": "thread_local",
    "threadInfo.cpp": "thread_info", "threadInfo.h": "thread_info",
    "callTraceHashTable.cpp": "calltrace", "callTraceStorage.cpp": "calltrace",
    "linearAllocator.cpp": "calltrace",
    "dwarf.cpp": "line_tables", "sframe.cpp": "line_tables",
    "perfEvents_linux.cpp": "perf", "wallClock.cpp": "wallclock",
    "ctimer_linux.cpp": "wallclock",
}


# addr2line resolves function names but usually returns NO file for this
# release build, so a file->category map alone silently drops almost everything
# into "(uninstrumented)". Fall back to the owning class in the function name,
# which is what actually identifies the recording site.
FUNC_TO_CAT = [
    ("CodeCache::", "native_symbols"), ("CodeCacheArray", "native_symbols"),
    ("ElfParser", "native_symbols"), ("Symbols", "native_symbols"),
    ("Libraries", "native_symbols"), ("findSymbol", "native_symbols"),
    ("Dictionary::", "dictionary"), ("DictTable", "dictionary"),
    ("FlightRecorder", "jfr_buffers"), ("Recording::", "jfr_buffers"),
    ("Buffer", "jfr_buffers"),
    ("LinearAllocator", "calltrace"), ("CallTrace", "calltrace"),
    ("LivenessTracker", "liveness"),
    ("ThreadFilter", "thread_filter"),
    ("ThreadLocalData", "thread_local"),
    ("ThreadInfo", "thread_info"),
    ("Dwarf", "line_tables"), ("SFrame", "line_tables"), ("sframe", "line_tables"),
    ("PerfEvents", "perf"),
    ("WallClock", "wallclock"), ("CTimer", "wallclock"),
    ("MethodMap", "method_map"),
]


def categorise(fn, src):
    if src in FILE_TO_CAT:
        return FILE_TO_CAT[src]
    for key, cat in FUNC_TO_CAT:
        if key in fn:
            return cat
    return "(unmapped: " + (fn.split("(")[0][:24] or "?") + ")"


def read_callers(path):
    out = []
    for line in open(path):
        if line.startswith("#"):
            continue
        p = line.split()
        if len(p) >= 3:
            try:
                out.append((int(p[0], 16), int(p[1]), int(p[2])))
            except ValueError:
                pass
    return out


def read_kv(path):
    d = {}
    for line in open(path):
        p = line.split()
        if len(p) >= 2:
            d[p[0]] = p[1]
    return d


def resolve(offsets, debug_lib):
    """addr2line in one batch -> {offset: (func, file)}."""
    if not offsets:
        return {}
    r = subprocess.run(["addr2line", "-f", "-C", "-e", debug_lib]
                       + [hex(o) for o in offsets],
                       capture_output=True, text=True)
    lines = r.stdout.splitlines()
    out = {}
    for i, off in enumerate(offsets):
        fn = lines[2 * i].strip() if 2 * i < len(lines) else "?"
        loc = lines[2 * i + 1].strip() if 2 * i + 1 < len(lines) else "?"
        src = os.path.basename(loc.split(":")[0]) if loc else "?"
        out[off] = (fn, src)
    return out


def main():
    debug_lib = DEFAULT_DEBUG
    for d in sys.argv[1:]:
        cf = [f for f in os.listdir(d) if f.endswith(".callers.txt")]
        nf = [f for f in os.listdir(d) if f.endswith(".nativemem.txt")]
        lf = [f for f in os.listdir(d) if f.endswith(".ledger.txt")]
        if not (cf and nf and lf):
            continue
        callers = read_callers(os.path.join(d, cf[0]))
        nm = read_kv(os.path.join(d, nf[0]))
        led = read_kv(os.path.join(d, lf[0]))
        base = int(nm["profiler_base"], 16)
        n_mmapped = int(led.get("malloc_live_count_mmapped", 0))

        print("=" * 96)
        print(os.path.basename(d))
        print("=" * 96)
        print(f"live requested {int(led['malloc_live_requested'])/MIB:.1f} MiB "
              f"in {int(led['malloc_live_count']):,} allocations; "
              f"{n_mmapped} of them are mmap-served")

        # profiler-attributable call sites only
        # The .so spans ~2 MiB of vaddr (readelf LOAD segments); anything
        # beyond that is another library and not profiler-attributable.
        mine = [(a, b, c) for a, b, c in callers if 0 <= a - base < 0x200000]
        syms = resolve([a - base for a, _b, _c in mine], debug_lib)

        rows = []
        for a, b, c in mine:
            fn, src = syms.get(a - base, ("?", "?"))
            rows.append({"bytes": b, "count": c, "mean": b / max(1, c),
                         "fn": fn, "src": src, "cat": categorise(fn, src)})
        rows.sort(key=lambda r: -r["mean"])

        # Locate the threshold empirically: walk sites by descending allocation
        # size until the live mmap-served count is accounted for.
        acc, thr_idx = 0, None
        for i, r in enumerate(rows):
            if acc >= n_mmapped:
                thr_idx = i
                break
            acc += r["count"]
        if thr_idx is None:
            thr_idx = len(rows)
        thr = rows[thr_idx - 1]["mean"] if thr_idx else float("inf")
        print(f"empirical mmap threshold: allocations >= {thr/KIB:,.0f} KiB "
              f"({thr/MIB:.2f} MiB) are mmap-served\n")

        print(f"{'largest call sites':<46}{'MiB':>8}{'n':>7}{'mean':>12}{'mmap?':>7}")
        print("-" * 96)
        for i, r in enumerate(rows[:14]):
            ms = (f"{r['mean']/MIB:.2f} MiB" if r["mean"] >= MIB
                  else f"{r['mean']/KIB:.1f} KiB")
            tag = "YES" if i < thr_idx else "no"
            label = f"{r['fn'][:30]} [{r['src']}]"
            print(f"{label:<46}{r['bytes']/MIB:>8.2f}{r['count']:>7}{ms:>12}{tag:>7}")

        print(f"\n{'category':<22}{'total MiB':>11}{'mmap-served':>13}"
              f"{'arena':>9}{'% mmap':>9}")
        print("-" * 96)
        agg = {}
        for i, r in enumerate(rows):
            a = agg.setdefault(r["cat"], {"tot": 0.0, "mm": 0.0})
            a["tot"] += r["bytes"] / MIB
            if i < thr_idx:
                a["mm"] += r["bytes"] / MIB
        for k in sorted(agg, key=lambda k: -agg[k]["tot"]):
            v = agg[k]
            pct = 100.0 * v["mm"] / v["tot"] if v["tot"] else 0.0
            print(f"{k:<22}{v['tot']:>11.2f}{v['mm']:>13.2f}"
                  f"{v['tot']-v['mm']:>9.2f}{pct:>8.0f}%")
        tot = sum(v["tot"] for v in agg.values())
        mm = sum(v["mm"] for v in agg.values())
        print("-" * 96)
        print(f"{'TOTAL':<22}{tot:>11.2f}{mm:>13.2f}{tot-mm:>9.2f}"
              f"{100.0*mm/tot if tot else 0:>8.0f}%")
        print()


if __name__ == "__main__":
    main()
