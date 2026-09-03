#!/usr/bin/env python3
"""Compare APM memory overhead across scopes and estimators.

Reads either harness:
  run_doe_original_method.sh  -- old estimator only (doe's `memory=` max)
  run_doe_full_apm.sh         -- both estimators from identical runs

Reports three deltas per estimator:
    full APM = both   - baseline      (the customer-facing figure)
    tracer   = tracer - baseline
    profiler = both   - tracer        (comparable to the historical ~104 MB)

Because run_doe_full_apm.sh captures doe's maximum and a plateau median from the
SAME runs, the difference between the two columns isolates the estimator alone --
scope, workload and build all held constant.

Usage: analyse_apm_scopes.py <out_dir> [<out_dir> ...]
"""
import os
import statistics as st
import sys

MB = 1048576.0
CONDS = ("baseline", "tracer", "both")


def plateau_median(path, from_s=240):
    """Median cgroup anon over the plateau, in MB.

    Median rather than mean, and outliers dropped, because every trace ends with
    the container tearing down and anon collapsing toward zero. A handful of such
    samples is enough to wreck a mean; partial collapses have previously survived
    a naive filter, so the cut is taken against the median itself.
    """
    try:
        rows = []
        for line in open(path):
            p = line.split()
            if len(p) >= 2:
                rows.append((int(p[0]), int(p[1])))
    except OSError:
        return None
    if not rows:
        return None
    t0 = rows[0][0]
    med = st.median([v for _, v in rows])
    vals = [v / MB for t, v in rows
            if v > 0.9 * med and (t - t0) / 1000.0 >= from_s]
    return st.median(vals) if len(vals) >= 10 else None


def load(root):
    """{round: {cond: {'max': MB, 'plateau': MB|None}}}"""
    res = os.path.join(root, "results.txt")
    if not os.path.exists(res):
        return {}
    out = {}
    for line in open(res):
        p = line.split()
        if len(p) < 3:
            continue
        rnd, cond, mem = p[0], p[1], int(p[2])
        rec = {"max": mem / MB if mem else None, "plateau": None}
        if len(p) >= 4:
            rec["plateau"] = plateau_median(p[3])
        out.setdefault(rnd, {})[cond] = rec
    return out


def deltas(rounds, key):
    """Per-round deltas for one estimator; only rounds with all three arms."""
    out = {"full APM": [], "tracer": [], "profiler": []}
    for r, c in rounds.items():
        if not all(k in c and c[k][key] is not None for k in CONDS):
            continue
        b, t, x = c["baseline"][key], c["tracer"][key], c["both"][key]
        out["full APM"].append(x - b)
        out["tracer"].append(t - b)
        out["profiler"].append(x - t)
    return out


def stat(xs):
    n = len(xs)
    if not n:
        return None
    mu = st.mean(xs)
    sd = st.stdev(xs) if n > 1 else 0.0
    return mu, sd, (sd / n ** 0.5 if n > 1 else 0.0), n


def report(root):
    rounds = load(root)
    if not rounds:
        print(f"  !! {root}: no results")
        return
    has_plateau = any(c[k]["plateau"] is not None
                      for c in rounds.values() for k in c)

    print("=" * 78)
    print(os.path.basename(root.rstrip("/")))
    print("=" * 78)

    print(f"\n{'absolute (MB)':<14}" + "".join(f"{c:>16}" for c in CONDS))
    print("-" * 78)
    for key, lbl in (("max", "doe max"), ("plateau", "plateau median")):
        if key == "plateau" and not has_plateau:
            continue
        row = f"{lbl:<14}"
        for c in CONDS:
            vals = [r[c][key] for r in rounds.values()
                    if c in r and r[c][key] is not None]
            row += f"{st.mean(vals):>16.1f}" if vals else f"{'-':>16}"
        print(row)

    for key, lbl in (("max", "doe max (the ORIGINAL estimator)"),
                     ("plateau", "plateau median (this investigation's)")):
        if key == "plateau" and not has_plateau:
            continue
        d = deltas(rounds, key)
        print(f"\n{lbl}")
        print(f"  {'delta':<12}{'mean MB':>10}{'SD':>8}{'SE':>8}{'n':>4}")
        print("  " + "-" * 42)
        for k in ("full APM", "tracer", "profiler"):
            s = stat(d[k])
            if s:
                print(f"  {k:<12}{s[0]:>+10.1f}{s[1]:>8.1f}{s[2]:>8.1f}{s[3]:>4}")
    print()


def main():
    for root in sys.argv[1:]:
        report(root)
    print("Reference points")
    print("  Aug 2026 reproduction, old method: tracer +136.1 MB, profiler +104.3 MB,")
    print("                                     total ~240 MB on a 1514 MB baseline.")
    print("  This investigation, profiler-only, plateau anon: 59-74 MiB (62-78 MB).")
    print()
    print("  If the profiler's share under the OLD estimator still lands near 104 MB,")
    print("  the whole gap is measurement and no footprint improvement can be claimed.")


if __name__ == "__main__":
    main()
