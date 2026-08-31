#!/usr/bin/env python3
"""Attribute the paired malloc delta -- and specifically the mmap-served
(`hblkhd`) part of it -- to owning libraries, on the dd-trace-doe workload.

The question: enabling the profiler adds +22.56 MiB of mmap-served malloc
address space whose residency is ~0, but only ~7.7 MiB of that is
profiler-instrumented allocation. Whose is the rest?

METHOD. `callers.txt` gives live requested bytes and a live count per call site,
so per-site mean size is bytes/count. The dump also contains the process's own
`smaps`, which carries a pathname per mapping -- so caller addresses join to
owning libraries with no debug info required. That answers "whose allocation"
(libjvm / libc / libjavaProfiler / tracer natives) but not "which JVM
subsystem", which would need HotSpot symbols the container image lacks.

The mmap threshold is located per dump rather than assumed: glibc's
M_MMAP_THRESHOLD is dynamic, and the doe workload's allocation pattern differs
from the memsweep one where it measured 256 KiB. Ranking call sites by size
until `malloc_live_count_mmapped` is covered identifies the mmap-served ones
without assuming a value.

Usage: analyse_ledger_doe.py <out_dir> [<out_dir> ...]
"""
import os
import re
import sys
import bisect
import statistics as st

KIB = 1024.0
MIB = 1048576.0


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


def read_modules(smaps_path):
    """Executable file-backed ranges -> library name, for caller attribution."""
    rows = []
    hdr = re.compile(r"^([0-9a-f]+)-([0-9a-f]+)\s+(\S{4})\s+\S+\s+\S+\s+(\d+)\s*(.*)$")
    for line in open(smaps_path):
        m = hdr.match(line)
        if not m:
            continue
        path = m.group(5).strip()
        if not path or path.startswith("["):
            continue
        rows.append((int(m.group(1), 16), int(m.group(2), 16),
                     os.path.basename(path)))
    rows.sort()
    return rows


def normalise(name):
    """dd-trace-java extracts the profiler .so to a fresh temp name every run
    (libjavaProfiler-dd-tmp<random>.so). Without folding those together the
    same library is treated as a different one per pair, so its mean across
    pairs is divided by the pair count and its SE is meaningless."""
    if "libjavaProfiler" in name:
        return "libjavaProfiler.so"
    return re.sub(r"-dd-tmp\d+", "", name)


def owner(mods, starts, addr):
    i = bisect.bisect_right(starts, addr) - 1
    if 0 <= i < len(mods) and mods[i][0] <= addr < mods[i][1]:
        return normalise(mods[i][2])
    return "(anon/JIT)"


def hblkhd_from_mallocinfo(path):
    """glibc's own mmap-served total, from the SAME run -- so the ledger's
    attribution is validated within-run rather than against a constant carried
    over from another batch. Its `count` also cross-checks the ledger's
    malloc_live_count_mmapped."""
    try:
        s = open(path).read()
    except OSError:
        return None
    m = re.findall(r'<total type="mmap" count="(\d+)" size="(\d+)"/>', s)
    return (int(m[-1][0]), int(m[-1][1]) / MIB) if m else None


def load_dump(d):
    cf = [f for f in os.listdir(d) if f.endswith(".callers.txt")]
    lf = [f for f in os.listdir(d) if f.endswith(".ledger.txt")]
    sf = [f for f in os.listdir(d) if f.endswith(".smaps.txt")]
    if not (cf and lf and sf):
        return None
    callers = read_callers(os.path.join(d, cf[0]))
    led = read_kv(os.path.join(d, lf[0]))
    mods = read_modules(os.path.join(d, sf[0]))
    starts = [m[0] for m in mods]
    n_mm = int(led.get("malloc_live_count_mmapped", 0))

    rows = [{"bytes": b, "count": c, "mean": b / max(1, c),
             "lib": owner(mods, starts, a)} for a, b, c in callers]
    rows.sort(key=lambda r: -r["mean"])

    acc, thr_idx = 0, len(rows)
    for i, r in enumerate(rows):
        if acc >= n_mm:
            thr_idx = i
            break
        acc += r["count"]
    for i, r in enumerate(rows):
        r["mmap"] = i < thr_idx
    thr = rows[thr_idx - 1]["mean"] if thr_idx else float("inf")
    xf = [f for f in os.listdir(d) if f.endswith(".mallocinfo.xml")]
    hb = hblkhd_from_mallocinfo(os.path.join(d, xf[0])) if xf else None
    return {"rows": rows, "led": led, "thr": thr, "n_mm": n_mm, "hblkhd": hb}


def agg(dump):
    """{lib: (total MiB, mmap-served MiB)}"""
    out = {}
    for r in dump["rows"]:
        t, m = out.get(r["lib"], (0.0, 0.0))
        out[r["lib"]] = (t + r["bytes"] / MIB,
                         m + (r["bytes"] / MIB if r["mmap"] else 0.0))
    return out


def main():
    pairs = {}
    for root in sys.argv[1:]:
        ld = os.path.join(root, "ledger")
        if not os.path.isdir(ld):
            continue
        for tag in sorted(os.listdir(ld)):
            d = load_dump(os.path.join(ld, tag))
            if not d:
                print(f"  !! {tag}: no dump")
                continue
            # Key on (root, pair): separate batches both number from pair01, so
            # keying on the pair name alone would silently merge them.
            key = (os.path.basename(root.rstrip("/")), tag.split("_prof")[0])
            arm = "prof" if tag.endswith("proftrue") else "trace"
            pairs.setdefault(key, {})[arm] = d

    full = [k for k, v in pairs.items() if "prof" in v and "trace" in v]
    print(f"complete pairs: {len(full)}\n")
    if not full:
        return

    for k in full:
        for arm in ("prof", "trace"):
            d = pairs[k][arm]
            print(f"{k[0]}/{k[1]}/{arm:<6} live {int(d['led']['malloc_live_requested'])/MIB:8.1f} MiB "
                  f"in {int(d['led']['malloc_live_count']):>9,} allocs; "
                  f"{d['n_mm']:>3} mmap-served; threshold {d['thr']/KIB:>8,.0f} KiB")
    print()

    libs = set()
    for k in full:
        libs |= set(agg(pairs[k]["prof"])) | set(agg(pairs[k]["trace"]))

    print(f"{'library':<34}{'d total MiB':>13}{'d mmap-served':>15}{'SE':>8}")
    print("-" * 72)
    rows = []
    for lib in libs:
        dt, dm = [], []
        for k in full:
            a, b = agg(pairs[k]["prof"]), agg(pairs[k]["trace"])
            at, am = a.get(lib, (0.0, 0.0))
            bt, bm = b.get(lib, (0.0, 0.0))
            dt.append(at - bt)
            dm.append(am - bm)
        se = (st.stdev(dt) / len(dt) ** 0.5) if len(dt) > 1 else 0.0
        rows.append((lib, st.mean(dt), st.mean(dm), se))
    rows.sort(key=lambda r: -abs(r[2]))
    for lib, dt, dm, se in rows:
        if abs(dt) < 0.05 and abs(dm) < 0.05:
            continue
        print(f"{lib:<34}{dt:>+13.2f}{dm:>+15.2f}{se:>8.2f}")
    print("-" * 72)
    print(f"{'TOTAL':<34}{sum(r[1] for r in rows):>+13.2f}"
          f"{sum(r[2] for r in rows):>+15.2f}")
    hb = []
    for k in full:
        a, b = pairs[k]["prof"]["hblkhd"], pairs[k]["trace"]["hblkhd"]
        if a and b:
            hb.append(a[1] - b[1])
    if hb:
        mu = st.mean(hb)
        se = (st.stdev(hb) / len(hb) ** 0.5) if len(hb) > 1 else 0.0
        att = sum(r[2] for r in rows)
        print(f"\nWITHIN-RUN VALIDATION (glibc's own figure, same dumps):")
        print(f"  d_hblkhd from mallocinfo : {mu:+8.2f} +/- {se:.2f} MiB")
        print(f"  attributed by the ledger : {att:+8.2f} MiB"
              f"   ({100.0*att/mu if mu else 0:.0f} % of it)")
        print(f"  mmap counts also cross-check the ledger's "
              f"malloc_live_count_mmapped exactly.")


if __name__ == "__main__":
    main()
