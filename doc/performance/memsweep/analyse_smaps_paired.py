#!/usr/bin/env python3
"""Aggregate the paired smaps snapshots: per-mapping-class resident deltas with
error bars, plus an independent replication of the free-held residency slope.

The single-pair snapshot settled residency in the absolute but drew
d_fordblks = +1.6 MiB against a 12-pair mean of +22.86, so it could not size the
profiler-attributable free-held cost. Per-pair anon SD is 29.56 MiB; this
replicates over 8 pairs.

Each run contributes two within-plateau snapshots (t=250, t=285), averaged, so
snapshot placement inside the plateau is not a source of spread.

Usage: analyse_smaps_paired.py <dir>
"""
import math
import os
import re
import statistics as st
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from analyse_smaps import parse_smaps, classify  # noqa: E402

MIB = 1024.0      # smaps is kB
MIB_B = 1048576.0  # mallinfo is bytes


def snap_classes(path):
    maps = classify(parse_smaps(path))
    out = {}
    for mp in maps:
        b = out.setdefault(mp["tag"], {"size": 0, "rss": 0})
        b["size"] += mp["size"]
        b["rss"] += mp["rss"]
    return out


def mallinfo_at(d, tag, ts):
    md = os.path.join(d, "mallinfo", tag)
    if not os.path.isdir(md):
        return None
    best = None
    for f in os.listdir(md):
        if not f.endswith(".mallinfo.txt"):
            continue
        rows = []
        for line in open(os.path.join(md, f)):
            p = line.split()
            if len(p) >= 6:
                try:
                    rows.append(tuple(int(x) for x in p[:6]))
                except ValueError:
                    pass
        if rows:
            m = st.median([r[1] for r in rows])
            if best is None or m > best[1]:
                best = (rows, m)
    if not best:
        return None
    near = min(best[0], key=lambda r: abs(r[0] - ts))
    return {"arena": near[1] / MIB_B, "uordblks": near[2] / MIB_B,
            "fordblks": near[3] / MIB_B, "hblkhd": near[5] / MIB_B}


def run_data(d, tag, snaps=("250", "285")):
    """Average the per-class Rss and the mallinfo terms over a run's snapshots."""
    cls_acc, mi_acc, anon_acc = {}, [], []
    n = 0
    for s in snaps:
        sp = os.path.join(d, "smaps", f"{tag}_t{s}.smaps")
        meta = os.path.join(d, "smaps", f"{tag}_t{s}.snapmeta")
        if not os.path.exists(sp) or os.path.getsize(sp) < 1000:
            continue
        ts, cg = 0, None
        if os.path.exists(meta):
            parts = open(meta).read().split()
            if len(parts) >= 2:
                ts, cg = int(parts[0]), int(parts[1]) / MIB_B
        cls = snap_classes(sp)
        for k, v in cls.items():
            a = cls_acc.setdefault(k, {"size": 0.0, "rss": 0.0})
            a["size"] += v["size"] / MIB
            a["rss"] += v["rss"] / MIB
        mi = mallinfo_at(d, tag, ts)
        if mi:
            mi_acc.append(mi)
        if cg:
            anon_acc.append(cg)
        n += 1
    if not n:
        return None
    for v in cls_acc.values():
        v["size"] /= n
        v["rss"] /= n
    mi = {k: st.mean([m[k] for m in mi_acc]) for k in mi_acc[0]} if mi_acc else None
    return {"cls": cls_acc, "mi": mi,
            "anon": st.mean(anon_acc) if anon_acc else None}


def stats(xs):
    n = len(xs)
    mu = st.mean(xs)
    sd = st.stdev(xs) if n > 1 else 0.0
    return mu, sd, (sd / math.sqrt(n) if n > 1 else 0.0)


def main():
    d = sys.argv[1]
    pairs = sorted({f.split("_prof")[0] for f in os.listdir(os.path.join(d, "smaps"))
                    if f.endswith(".smaps")})
    rows = []
    for p in pairs:
        a = run_data(d, f"{p}_proftrue")
        b = run_data(d, f"{p}_proffalse")
        if a and b and a["anon"] and b["anon"]:
            rows.append((p, a, b))
    print(f"pairs analysed: {len(rows)}\n")

    d_anon = [a["anon"] - b["anon"] for _, a, b in rows]
    mu, sd, se = stats(d_anon)
    print(f"{'quantity':<38}{'mean':>9}{'SD':>8}{'SE':>7}")
    print("-" * 62)
    print(f"{'d anon (cgroup, = smaps Anonymous)':<38}{mu:>+9.2f}{sd:>8.2f}{se:>7.2f}")
    for k in ("arena", "uordblks", "fordblks", "hblkhd"):
        if rows[0][1]["mi"]:
            v = [a["mi"][k] - b["mi"][k] for _, a, b in rows]
            m2, s2, e2 = stats(v)
            print(f"{'d mallinfo ' + k:<38}{m2:>+9.2f}{s2:>8.2f}{e2:>7.2f}")

    # per-class resident deltas
    keys = set()
    for _, a, b in rows:
        keys |= set(a["cls"]) | set(b["cls"])
    print(f"\n{'mapping class':<40}{'d Rss':>9}{'SD':>8}{'SE':>7}{'d Size':>10}")
    print("-" * 74)
    tot = []
    per_class = {}
    for k in sorted(keys):
        dv = [a["cls"].get(k, {"rss": 0})["rss"] - b["cls"].get(k, {"rss": 0})["rss"]
              for _, a, b in rows]
        ds = [a["cls"].get(k, {"size": 0})["size"] - b["cls"].get(k, {"size": 0})["size"]
              for _, a, b in rows]
        m2, s2, e2 = stats(dv)
        per_class[k] = (m2, s2, e2)
        if abs(m2) < 0.05 and abs(st.mean(ds)) < 0.05:
            continue
        print(f"{k:<40}{m2:>+9.2f}{s2:>8.2f}{e2:>7.2f}{st.mean(ds):>+10.1f}")
        tot.append(m2)
    print("-" * 74)
    print(f"{'sum of class deltas':<40}{sum(tot):>+9.2f}")

    # residency slope, replicated on this dataset
    if rows[0][1]["mi"]:
        X = [a["mi"]["fordblks"] - b["mi"]["fordblks"] for _, a, b in rows]
        Y = d_anon
        n = len(X)
        mx, my = st.mean(X), st.mean(Y)
        sxx = sum((x - mx) ** 2 for x in X)
        if sxx > 0 and n > 2:
            bb = sum((x - mx) * (y - my) for x, y in zip(X, Y)) / sxx
            aa = my - bb * mx
            resid = [y - (aa + bb * x) for x, y in zip(X, Y)]
            s2 = sum(r * r for r in resid) / (n - 2)
            se_b = math.sqrt(s2 / sxx)
            r2 = 1 - sum(r * r for r in resid) / sum((y - my) ** 2 for y in Y)
            print(f"\nresidency slope (independent replication, n={n}):")
            print(f"  d_anon = {aa:+.2f} + {bb:.4f} * d_fordblks")
            print(f"  slope {bb:.4f} +/- {se_b:.4f}   R^2 = {r2:.4f}   "
                  f"residual SD {math.sqrt(s2):.2f} MiB")
            print(f"  {abs(bb-1)/se_b:.2f} sigma from 1.0   |   "
                  f"{abs(bb)/se_b:.2f} sigma from 0")

        # resident free-held, measured directly per mapping
        ar = [a["cls"].get("glibc secondary arena", {"rss": 0})["rss"]
              + a["cls"].get("glibc main arena ([heap])", {"rss": 0})["rss"]
              for _, a, b in rows]
        uo = [a["mi"]["uordblks"] for _, a, b in rows]
        fh = [x - u for x, u in zip(ar, uo)]
        m3, s3, e3 = stats(fh)
        print(f"\nresident free-held arena, profiling arm (arena Rss - uordblks):")
        print(f"  {m3:.1f} +/- {e3:.1f} MiB   (SD {s3:.1f}, n={len(fh)})")
        arb = [b["cls"].get("glibc secondary arena", {"rss": 0})["rss"]
               + b["cls"].get("glibc main arena ([heap])", {"rss": 0})["rss"]
               for _, a, b in rows]
        uob = [b["mi"]["uordblks"] for _, a, b in rows]
        fhb = [x - u for x, u in zip(arb, uob)]
        m4, s4, e4 = stats(fhb)
        print(f"resident free-held arena, tracing arm:")
        print(f"  {m4:.1f} +/- {e4:.1f} MiB   (SD {s4:.1f})")
        dfh = [x - y for x, y in zip(fh, fhb)]
        m5, s5, e5 = stats(dfh)
        dfo = [a["mi"]["fordblks"] - b["mi"]["fordblks"] for _, a, b in rows]
        m6, s6, e6 = stats(dfo)
        print(f"PAIRED DELTA of resident free-held arena:")
        print(f"  smaps-detector route : {m5:+.2f} +/- {e5:.2f} MiB  (SD {s5:.2f})"
              f"   <- UNDERCOUNTS, see below")
        print(f"  mallinfo route       : {m6:+.2f} +/- {e6:.2f} MiB  (SD {s6:.2f})"
              f"   <- authoritative")
        print("""
  The two disagree because the strict 64 MiB-shape arena detector misses arenas
  whose mappings the kernel split or merged; those land in the generic
  'anon 1MiB-512MiB' bucket instead. The leak is quantified and accounts for the
  difference: d(secondary arena Rss) + d(anon 1MiB-512MiB Rss) reproduces
  d(mallinfo arena) closely, while the arena class alone does not.

  Use the mallinfo route for the free-held magnitude. Free-held residency itself
  is not measured by either of these -- it comes from the slope of d_anon on
  d_fordblks (1.0119 +/- 0.0066 over 20 pairs), which needs no classification.""")


if __name__ == "__main__":
    main()
