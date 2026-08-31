#!/usr/bin/env python3
"""Derive a residency factor for every accounting term.

WHY THIS IS NEEDED: the accounting over-explains anon. NMT delta 30.00 +
profiler counters 24.81 = 54.81 against a stable measured anon term of
35.98 +/- 0.26. That is not a contradiction -- NMT reports committed address
space and the counters report allocated bytes, while cgroup anon counts
*resident pages*. Each term needs a residency factor before the two sides can
be compared.

NON-OVERLAPPING DECOMPOSITION. The subtle part is that NMT's per-category
`committed` mixes mmap'd regions with malloc'd bytes, and those malloc'd bytes
are served by glibc -- so they are already inside mallinfo's `arena`/`hblkhd`.
Summing NMT committed alongside mallinfo terms double-counts them. NMT reports
the split per category, so this uses:

    anon_Rss = f_heap  x NMT[Java Heap].mmap_committed
             + f_code  x NMT[Code].mmap_committed
             + f_stack x NMT[Thread].stack_committed    (NOT category committed:
                                                        that also carries a
                                                        malloc part already
                                                        inside the arena)
             + intercept                                (Metaspace/Class/GC:
                                                        near-constant across
                                                        runs, NOT identifiable)
             + f_arena x mallinfo.arena                 (ALL malloc, any origin)
             + f_hblk  x mallinfo.hblkhd                (mmap-served chunks)

CAVEAT: arena and hblkhd are collinear at r = +0.925, so their factors are not
separately identifiable -- only the combination f_arena + 0.274 x f_hblk ~ 0.911
is determined. Profiling f_hblk over [0,1] is monotone (residual SD 1.49 at 0,
5.36 at 1), so the data prefers f_hblk ~ 0.

`Shared class space` is deliberately excluded: it is the CDS archive, mapped
from a file, so it is file-backed and never counted in anon.

Three factors are measured directly from smaps rather than fitted, because
their mappings are unambiguously identifiable (huge anon / anon-executable /
guard+stack signature). The remaining terms are fitted by least squares on the
residual, over all run-snapshots in both arms.

Usage: derive_residency.py <dir> [<dir> ...]
"""
import math
import os
import re
import statistics as st
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from analyse_smaps import parse_smaps, classify  # noqa: E402

KB_MIB = 1024.0
B_MIB = 1048576.0


def nmt_terms(path):
    """Per-category committed, split into malloc and mmap parts."""
    try:
        s = open(path).read()
    except OSError:
        return None
    cats = {}
    cur = None
    for line in s.splitlines():
        m = re.match(r"^-\s+(.+?)\s+\(reserved=(\d+)KB, committed=(\d+)KB", line)
        if m:
            cur = m.group(1).strip()
            cats.setdefault(cur, {"committed": int(m.group(3)) / KB_MIB,
                                  "malloc": 0.0, "mmap": 0.0, "stack": 0.0})
            continue
        if cur is None:
            continue
        m = re.search(r"\(malloc=(\d+)KB", line)
        if m:
            cats[cur]["malloc"] = int(m.group(1)) / KB_MIB
        m = re.search(r"\(mmap: reserved=\d+KB, committed=(\d+)KB", line)
        if m:
            cats[cur]["mmap"] = int(m.group(1)) / KB_MIB
        # NMT reports thread stacks on their own `stack:` line rather than an
        # `mmap:` line. That, not the category total, is the right denominator
        # for stack residency: the category total also carries a small malloc
        # portion (~0.13 MiB) which is served by glibc and so already inside
        # mallinfo's arena -- counting it here would double-count it.
        m = re.search(r"\(stack: reserved=\d+KB, committed=(\d+)KB", line)
        if m:
            cats[cur]["stack"] = int(m.group(1)) / KB_MIB
    return cats


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
    n = min(best[0], key=lambda r: abs(r[0] - ts))
    return {"arena": n[1] / B_MIB, "uordblks": n[2] / B_MIB,
            "fordblks": n[3] / B_MIB, "hblkhd": n[5] / B_MIB}


def smaps_classes(path):
    out = {}
    for mp in classify(parse_smaps(path)):
        b = out.setdefault(mp["tag"], {"size": 0.0, "rss": 0.0})
        b["size"] += mp["size"] / KB_MIB
        b["rss"] += mp["rss"] / KB_MIB
    return out


def lstsq(A, y):
    """Normal-equations least squares with Gaussian elimination. Returns
    (coeffs, residual SD, SEs)."""
    n, p = len(A), len(A[0])
    ata = [[sum(A[i][r] * A[i][c] for i in range(n)) for c in range(p)]
           for r in range(p)]
    aty = [sum(A[i][r] * y[i] for i in range(n)) for r in range(p)]
    M = [ata[r][:] + [aty[r]] for r in range(p)]
    for c in range(p):
        piv = max(range(c, p), key=lambda r: abs(M[r][c]))
        if abs(M[piv][c]) < 1e-12:
            return None
        M[c], M[piv] = M[piv], M[c]
        for r in range(p):
            if r == c:
                continue
            f = M[r][c] / M[c][c]
            for k in range(c, p + 1):
                M[r][k] -= f * M[c][k]
    beta = [M[r][p] / M[r][r] for r in range(p)]
    resid = [y[i] - sum(A[i][j] * beta[j] for j in range(p)) for i in range(n)]
    dof = max(1, n - p)
    s2 = sum(r * r for r in resid) / dof
    # SEs from the inverse of A'A (recomputed by elimination on the identity)
    inv = [[1.0 if r == c else 0.0 for c in range(p)] for r in range(p)]
    W = [ata[r][:] for r in range(p)]
    for c in range(p):
        piv = max(range(c, p), key=lambda r: abs(W[r][c]))
        W[c], W[piv] = W[piv], W[c]
        inv[c], inv[piv] = inv[piv], inv[c]
        d = W[c][c]
        W[c] = [v / d for v in W[c]]
        inv[c] = [v / d for v in inv[c]]
        for r in range(p):
            if r == c:
                continue
            f = W[r][c]
            W[r] = [W[r][k] - f * W[c][k] for k in range(p)]
            inv[r] = [inv[r][k] - f * inv[c][k] for k in range(p)]
    ses = [math.sqrt(max(0.0, s2 * inv[j][j])) for j in range(p)]
    return beta, math.sqrt(s2), ses, resid


def main():
    dirs = sys.argv[1:]
    obs = []
    for d in dirs:
        sd = os.path.join(d, "smaps")
        if not os.path.isdir(sd):
            continue
        for f in sorted(os.listdir(sd)):
            if not f.endswith(".smaps"):
                continue
            base = f[:-6]
            m = re.match(r"(.+?)_t(\d+)$", base)
            if m:
                tag, t = m.group(1), m.group(2)
                nmtp = os.path.join(d, "nmt", f"{tag}_t{t}.txt")
            else:
                tag, t = base, None
                nmtp = os.path.join(d, "smaps", f"{tag}.nmt")
            sp = os.path.join(sd, f)
            if os.path.getsize(sp) < 1000:
                continue
            meta = os.path.join(sd, base + ".snapmeta")
            ts = 0
            if os.path.exists(meta):
                pp = open(meta).read().split()
                if pp:
                    ts = int(pp[0])
            nmt = nmt_terms(nmtp)
            mi = mallinfo_at(d, tag, ts)
            if not nmt or not mi:
                continue
            cls = smaps_classes(sp)
            obs.append({"d": d, "tag": tag, "nmt": nmt, "mi": mi, "cls": cls,
                        "arm": "prof" if "proftrue" in tag else "trace"})
    print(f"observations (run-snapshots): {len(obs)}\n")
    if not obs:
        return

    def g(o, cat, key="mmap"):
        return o["nmt"].get(cat, {}).get(key, 0.0)

    def rss(o, k):
        return o["cls"].get(k, {"rss": 0.0})["rss"]

    # ---- directly measured factors (unambiguous mappings) ----
    print("DIRECTLY MEASURED residency factors (Rss / committed):")
    print(f"{'term':<34}{'Rss':>9}{'committed':>11}{'factor':>9}{'SD':>7}")
    print("-" * 70)
    direct = {}
    specs = [
        ("Java heap", "anon huge >=512MiB (JVM heap)", lambda o: g(o, "Java Heap")),
        ("JIT code cache", "anon executable (JIT code cache)", lambda o: g(o, "Code")),
        ("thread stacks", "pthread stack", lambda o: g(o, "Thread", "stack")),
    ]
    for label, clskey, term in specs:
        fs, rs, cs = [], [], []
        for o in obs:
            c = term(o)
            if c > 0.5:
                fs.append(rss(o, clskey) / c)
                rs.append(rss(o, clskey))
                cs.append(c)
        if fs:
            direct[label] = st.mean(fs)
            print(f"{label:<34}{st.mean(rs):>9.1f}{st.mean(cs):>11.1f}"
                  f"{st.mean(fs):>9.3f}{(st.stdev(fs) if len(fs)>1 else 0):>7.3f}")

    # ---- fit the rest on the residual ----
    #
    # Metaspace/Class/GC are NOT separately identifiable here and must not be
    # fitted as free terms. NMT GC mmap is byte-identical across arms
    # (d = +0.00) and metaspace barely moves, so their columns are effectively
    # constant; least squares then splits them arbitrarily. A first attempt
    # returned metaspace = -7.55 and GC = +7.25, both physically impossible,
    # with the pair cancelling to something plausible. They are folded into an
    # intercept representing the near-constant JVM mmap baseline, leaving only
    # the two terms that actually vary across runs to carry factors.
    A, y = [], []
    names = ["intercept (constant JVM mmap baseline)", "glibc arena",
             "hblkhd (mmap-served malloc)"]
    for o in obs:
        tot = sum(v["rss"] for k, v in o["cls"].items() if k != "file-backed")
        known = (rss(o, "anon huge >=512MiB (JVM heap)")
                 + rss(o, "anon executable (JIT code cache)")
                 + rss(o, "pthread stack"))
        y.append(tot - known)
        A.append([1.0, o["mi"]["arena"], o["mi"]["hblkhd"]])
    out = lstsq(A, y)
    if not out:
        print("\nfit failed (singular)")
        return
    beta, rsd, ses, resid = out
    print(f"\nFITTED residency factors (least squares on the remainder, n={len(y)}):")
    print(f"{'term':<38}{'mean':>9}{'factor':>9}{'+/-':>8}")
    print("-" * 70)
    for j, nm in enumerate(names):
        unit = "MiB" if j == 0 else ""
        print(f"{nm:<38}{st.mean([a[j] for a in A]):>9.1f}"
              f"{beta[j]:>9.3f}{ses[j]:>8.3f} {unit}")
    print(f"\nresidual SD of the model: {rsd:.2f} MiB")

    # ---- honest out-of-sample check: leave-one-pair-out on the DELTA ----
    bykey = {}
    for o in obs:
        bykey.setdefault((o["d"], o["tag"].split("_prof")[0]), []).append(o)
    keys = sorted(bykey)
    errs = []
    for hold in keys:
        tr = [o for k in keys if k != hold for o in bykey[k]]
        At = [[1.0, o["mi"]["arena"], o["mi"]["hblkhd"]] for o in tr]
        yt = [sum(v["rss"] for kk, v in o["cls"].items() if kk != "file-backed")
              - (rss(o, "anon huge >=512MiB (JVM heap)")
                 + rss(o, "anon executable (JIT code cache)")
                 + rss(o, "pthread stack")) for o in tr]
        r = lstsq(At, yt)
        if not r:
            continue
        bt = r[0]
        held = bykey[hold]
        pr = [o for o in held if o["arm"] == "prof"]
        tc = [o for o in held if o["arm"] == "trace"]
        if not pr or not tc:
            continue

        def pred(o):
            return (bt[0] + bt[1] * o["mi"]["arena"] + bt[2] * o["mi"]["hblkhd"]
                    + rss(o, "anon huge >=512MiB (JVM heap)")
                    + rss(o, "anon executable (JIT code cache)")
                    + rss(o, "pthread stack"))

        def meas(o):
            return sum(v["rss"] for k, v in o["cls"].items() if k != "file-backed")
        dp = st.mean([pred(o) for o in pr]) - st.mean([pred(o) for o in tc])
        dm = st.mean([meas(o) for o in pr]) - st.mean([meas(o) for o in tc])
        errs.append(dp - dm)
    if errs:
        print(f"\nleave-one-pair-out prediction of d_anon (out of sample, n={len(errs)}):")
        print(f"  mean error {st.mean(errs):+.2f} MiB, "
              f"SD {st.stdev(errs) if len(errs)>1 else 0:.2f}, "
              f"max |error| {max(abs(e) for e in errs):.2f}")

    # ---- apply to the paired delta ----
    print("\n" + "=" * 70)
    print("APPLYING THE FACTORS TO THE PAIRED DELTA")
    print("=" * 70)
    pairs = {}
    for o in obs:
        key = (o["d"], o["tag"].split("_prof")[0])
        pairs.setdefault(key, {})[o["arm"]] = o
    rows = [v for v in pairs.values() if "prof" in v and "trace" in v]
    print(f"complete pairs: {len(rows)}")
    comp = []
    for label, f, term in [
        ("JIT code cache", direct.get("JIT code cache", 1.0), lambda o: g(o, "Code")),
        ("thread stacks", direct.get("thread stacks", 0.85), lambda o: g(o, "Thread", "stack")),
        ("glibc arena", beta[1], lambda o: o["mi"]["arena"]),
        ("hblkhd", beta[2], lambda o: o["mi"]["hblkhd"]),
        ("metaspace+class+GC", 1.0, lambda o: 0.0),  # constant across arms
    ]:
        dv = [term(v["prof"]) - term(v["trace"]) for v in rows]
        mu, sd = st.mean(dv), (st.stdev(dv) if len(dv) > 1 else 0)
        comp.append((label, f, mu, f * mu, sd / math.sqrt(len(dv)) * abs(f)))
    print(f"\n{'term':<24}{'factor':>8}{'d term':>10}{'d resident':>12}{'SE':>8}")
    print("-" * 66)
    for label, f, mu, contrib, se in comp:
        print(f"{label:<24}{f:>8.3f}{mu:>+10.2f}{contrib:>+12.2f}{se:>8.2f}")
    print("-" * 66)
    print(f"{'PREDICTED d anon':<24}{'':>8}{'':>10}{sum(c[3] for c in comp):>+12.2f}")
    danon = [sum(v["prof"]["cls"][k]["rss"] for k in v["prof"]["cls"] if k != "file-backed")
             - sum(v["trace"]["cls"][k]["rss"] for k in v["trace"]["cls"] if k != "file-backed")
             for v in rows]
    print(f"{'MEASURED d anon':<24}{'':>8}{'':>10}{st.mean(danon):>+12.2f}"
          f"{st.stdev(danon)/math.sqrt(len(danon)):>8.2f}")
    print(f"{'difference':<24}{'':>8}{'':>10}"
          f"{sum(c[3] for c in comp)-st.mean(danon):>+12.2f}")


if __name__ == "__main__":
    main()
