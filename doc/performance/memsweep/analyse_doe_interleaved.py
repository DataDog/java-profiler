import re, os, glob, json, subprocess, statistics, sys
import zstandard as zstd

MIB = 1024*1024
PAIRS = list(range(1, 13))
WARMUP = 30.0

def load_trace(path):
    """Return (rel_times, values, marks) with container-TEARDOWN samples removed.

    The sampler runs until the cgroup file vanishes, so the tail of every trace
    contains the JVM exiting -- anon collapsing toward zero (observed: 1581 MiB
    -> 13 MiB). Those samples were previously inside the 'steady state' window,
    which inflated the within-run sd (140 MiB in one run) and dragged means
    down. Truncate the trailing collapse: walk back from the end while the
    value is below half the run's peak.
    """
    ts, vals, marks = [], [], {}
    for line in open(path):
        p = line.split()
        ts.append(int(p[0])); vals.append(int(p[1])/MIB)
        if len(p) > 2 and p[2].startswith("NMT"):
            marks[p[2]] = int(p[1])/MIB
    peak = max(vals)
    cut = len(vals)
    while cut > 1 and vals[cut-1] < 0.5*peak:
        cut -= 1
    t0 = ts[0]
    rel = [(t-t0)/1000.0 for t in ts[:cut]]
    return rel, vals[:cut], marks, len(vals)-cut

def st(xs):
    n = len(xs); mu = statistics.mean(xs)
    sd = statistics.stdev(xs) if n > 1 else 0.0
    return mu, sd, (sd/n**0.5 if n > 1 else 0.0)

def analyse(base, label, work):
    os.makedirs(work, exist_ok=True)
    anon, dropped = {}, 0
    for p in PAIRS:
        for arm in ("true", "false"):
            rel, vals, marks, nd = load_trace(f"{base}/anon/pair{p:02d}_prof{arm}.txt")
            dropped += nd
            steady = [v for r, v in zip(rel, vals) if r >= WARMUP]
            # linear trend over the steady window, to separate ramp from noise
            n = len(steady)
            if n > 2:
                xs = list(range(n)); mx = sum(xs)/n; my = sum(steady)/n
                slope = sum((x-mx)*(y-my) for x, y in zip(xs, steady))/sum((x-mx)**2 for x in xs)
                resid = [y - (my + slope*(x-mx)) for x, y in zip(xs, steady)]
                detrended_sd = statistics.stdev(resid)
            else:
                slope, detrended_sd = 0.0, 0.0
            anon[(p, arm)] = {
                "max": max(vals),
                "steady_mean": statistics.mean(steady),
                "steady_median": statistics.median(steady),
                "steady_sd": statistics.stdev(steady) if n > 1 else 0.0,
                "detrended_sd": detrended_sd,
                "ramp_per_min": slope*n/(rel[-1]-WARMUP)*60 if rel[-1] > WARMUP else 0,
                "at30": marks.get("NMT30"), "at70": marks.get("NMT70"),
                "n": n,
            }

    nmt = {}
    for p in PAIRS:
        for arm in ("true", "false"):
            for d in ("30", "70"):
                txt = open(f"{base}/nmt/pair{p:02d}_prof{arm}_t{d}.txt").read()
                tot = re.search(r"committed=(\d+)KB", txt)
                ac = re.search(r"Arena Chunk \(reserved=\d+KB, committed=(\d+)KB", txt)
                nmt[(p, arm, d)] = {"total": int(tot.group(1))/1024 if tot else None,
                                    "arena": int(ac.group(1))/1024 if ac else 0.0}

    nm = {}
    for p in PAIRS:
        fs = glob.glob(f"{base}/jfr/pair{p:02d}_proftrue/*main.jfr")
        if not fs: continue
        latest = max(fs, key=lambda f: int(os.path.basename(f).split("-")[0]))
        out = f"{work}/pair{p:02d}.jfr"
        with open(latest, "rb") as fi, open(out, "wb") as fo:
            zstd.ZstdDecompressor().copy_stream(fi, fo)
        r = subprocess.run(["jfr", "print", "--json", "--events",
                            "datadog.ProfilerCounter", out], capture_output=True, text=True)
        if r.returncode != 0: continue
        live, mx = {}, {}
        for ev in json.loads(r.stdout).get("recording", {}).get("events", []):
            v = ev.get("values", {}); nme, c = v.get("name", ""), v.get("count")
            if c is None: continue
            if nme.startswith("native_mem_live_bytes."): live[nme.split(".",1)[1]] = c
            elif nme.startswith("native_mem_max_bytes."): mx[nme.split(".",1)[1]] = c
        nm[p] = {"live": live, "max": mx}

    print("=" * 76)
    print(f"{label}   (teardown samples removed: {dropped} total)")
    print("=" * 76)
    print("within-run steady-state variation, mean over runs:")
    for arm, lab in (("true","profiling"), ("false","tracing-only")):
        raw = statistics.mean([anon[(p,arm)]["steady_sd"] for p in PAIRS])
        det = statistics.mean([anon[(p,arm)]["detrended_sd"] for p in PAIRS])
        rmp = statistics.mean([anon[(p,arm)]["ramp_per_min"] for p in PAIRS])
        print(f"  {lab:<13} sd={raw:6.2f}  detrended sd={det:5.2f}  ramp={rmp:+6.2f} MiB/min")

    print(f"\n{'estimator':<24}{'delta':>8}{'sd':>8}{'SE':>8}")
    ests = [("max(anon)", "max"), ("steady mean", "steady_mean"),
            ("steady median", "steady_median"), ("sync t=30s", "at30"),
            ("sync t=70s", "at70")]
    out = {}
    for lab, key in ests:
        d = [anon[(p,"true")][key] - anon[(p,"false")][key] for p in PAIRS]
        mu, sd, se = st(d); out[lab] = (mu, sd, se)
        print(f"{lab:<24}{mu:>8.2f}{sd:>8.2f}{se:>8.3f}")
    spread = max(v[0] for v in out.values()) - min(v[0] for v in out.values())
    print(f"{'estimator spread':<24}{spread:>8.2f}")

    ct_live = st([nm[p]["live"].get("calltrace",0)/MIB for p in PAIRS])
    ct_max  = st([nm[p]["max"].get("calltrace",0)/MIB for p in PAIRS])
    other   = st([sum(v for k,v in nm[p]["live"].items() if k!="calltrace")/MIB for p in PAIRS])
    print(f"\nNativeMem: calltrace live {ct_live[0]:.3f} peak {ct_max[0]:.3f}, "
          f"malloc-backed {other[0]:.3f} (x1.17 = {other[0]*1.17:.3f})")

    print(f"\n{'anon basis':<16}{'NMT':>5}{'anon d':>9}{'NMT d':>8}{'resid(live)':>13}{'sigma':>7}{'resid(peak)':>13}{'sigma':>7}")
    for alab, akey, nd in (("steady mean","steady_mean","70"),
                           ("sync t=70s","at70","70"), ("sync t=30s","at30","30")):
        d_a = [anon[(p,"true")][akey] - anon[(p,"false")][akey] for p in PAIRS]
        d_n = [nmt[(p,"true",nd)]["total"] - nmt[(p,"false",nd)]["total"] for p in PAIRS]
        a_mu,_,a_se = st(d_a); n_mu,_,n_se = st(d_n)
        row = f"{alab:<16}{nd:>5}{a_mu:>9.2f}{n_mu:>8.2f}"
        for _, ctv in (("live", ct_live[0]), ("peak", ct_max[0])):
            expl = n_mu + ctv + other[0]*1.17
            e_se = (n_se**2 + other[2]**2)**0.5
            res = a_mu - expl; r_se = (a_se**2 + e_se**2)**0.5
            row += f"{res:>+13.2f}{abs(res)/r_se:>7.2f}"
        print(row + f"   (+/- {r_se:.2f})")
    return out

if __name__ == "__main__":
    a = analyse("/tmp/interleaved_v2", "NO PRETOUCH", "/tmp/jfr_fx_v2")
    print()
    b = analyse("/tmp/interleaved_pretouch", "WITH ALWAYSPRETOUCH", "/tmp/jfr_fx_pt")
