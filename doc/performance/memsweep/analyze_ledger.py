#!/usr/bin/env python3
"""Reconcile alloc_ledger_probe.so dumps for the Step 0 fork in
memory-sweep-results-linux.md.

For each condition it reports, from one same-instant dump:

  * malloc, three ways -- logical (requested), chunk footprint (what RSS
    actually pays for), and glibc's own independent view derived from
    malloc_info as `system.current - free` plus the mmap'd-chunk total. The
    last is a cross-check on the first two, not a third opinion to average in.
  * mmap, from the probe's append-only event log, attributed to the calling
    module by resolving each caller address against the same-instant smaps.
  * RSS, with the probe's own hash table and event log subtracted. Those are
    mmap'd by the probe itself and are resident in proportion to how many
    allocations the run made -- which is larger in the with-agent condition,
    so leaving them in would manufacture part of the delta being measured.

Usage: analyze_ledger.py <dumpdir_without> <dumpdir_with>
       analyze_ledger.py --dir <OUTDIR>        (auto-pairs dump_* subdirs)
"""
import os
import re
import sys
from collections import defaultdict

MIB = 1024.0 * 1024.0


def _one(d, pat):
    m = re.search(pat, d)
    return int(m.group(1)) if m else 0


def read_ledger(path):
    out = {}
    with open(path) as f:
        for line in f:
            k, _, v = line.partition(" ")
            out[k.strip()] = v.strip()
    return out


def read_mallocinfo(path):
    """glibc's own live-chunk view: sbrk/arena bytes minus what it considers
    free, plus mmap'd chunks (which are never on a free list)."""
    if not os.path.exists(path):
        return None
    x = open(path).read()
    tail = x[x.rfind("</heap>"):] if "</heap>" in x else x
    fast = _one(tail, r'<total type="fast" count="\d+" size="(\d+)"')
    rest = _one(tail, r'<total type="rest" count="\d+" size="(\d+)"')
    mmapd = _one(tail, r'<total type="mmap" count="\d+" size="(\d+)"')
    cur = _one(tail, r'<system type="current" size="(\d+)"')
    return {"live_chunks": cur - fast - rest + mmapd, "arena_current": cur,
            # Free chunks glibc holds but has not returned to the OS. These
            # stay resident when they are interleaved with live chunks, which
            # is why malloc_trim(0) cannot reclaim them -- trim only releases
            # the heap top and pages that are *entirely* free.
            "free_held": fast + rest, "mmapd_chunks": mmapd}


def read_smaps(path):
    """-> list of (start, end, path, rss_bytes) and total RSS."""
    regions = []
    if not os.path.exists(path):
        return regions, 0
    start = end = None
    pathname = ""
    rss = 0
    hdr = re.compile(r"^([0-9a-f]+)-([0-9a-f]+)\s+\S+\s+\S+\s+\S+\s+\S+\s*(.*)$")
    with open(path) as f:
        for line in f:
            m = hdr.match(line)
            if m:
                if start is not None:
                    regions.append((start, end, pathname, rss))
                start = int(m.group(1), 16)
                end = int(m.group(2), 16)
                pathname = m.group(3).strip()
                rss = 0
            elif line.startswith("Rss:"):
                rss = int(line.split()[1]) * 1024
    if start is not None:
        regions.append((start, end, pathname, rss))
    return regions, sum(r[3] for r in regions)


def resolve(addr, regions):
    for s, e, p, _ in regions:
        if s <= addr < e:
            return (os.path.basename(p) if p else "[anon]") + f"+0x{addr - s:x}"
    return f"0x{addr:x}(unmapped)"


def module_of(addr, regions):
    for s, e, p, _ in regions:
        if s <= addr < e:
            return os.path.basename(p) if p else "[anon]"
    return "unknown"


def replay_events(path):
    """Replay the append-only log into a live mapping set.

    Later events win at a given base address, which is what the reserve-then-
    MAP_FIXED-commit pattern means: HotSpot reserves a large range and then
    maps committed sub-ranges over it. This is an approximation of the true
    interval state and is used only for attribution, never for residency --
    residency always comes from smaps.
    """
    live = {}
    if not os.path.exists(path):
        return live
    with open(path) as f:
        for line in f:
            if line.startswith("#"):
                continue
            parts = line.split()
            if len(parts) != 5:
                continue
            op, addr, ln, caller, kind = (int(parts[0]), int(parts[1], 16),
                                          int(parts[2]), int(parts[3], 16),
                                          int(parts[4]))
            if op in (0, 3):
                live[addr] = (ln, caller, kind)
            elif op in (1, 2):
                live.pop(addr, None)
    return live


def probe_self_rss(led, regions):
    """Resident bytes of the probe's own hash table and event log.

    Identified by the VMA names the probe sets via prctl(PR_SET_VMA_ANON_NAME),
    which smaps reports as "[anon:probe_mtab]" / "[anon:probe_evlog]". An
    earlier version matched by address overlap and credited the probe with any
    region that merely touched its range -- which absorbed a merged neighbour
    and reported more probe RSS than the tables can possibly occupy.
    """
    if any("probe_" in path for _s, _e, path, _r in regions):
        return sum(rss for _s, _e, path, rss in regions if "probe_" in path)
    print("  !! dump predates PR_SET_VMA naming -- probe RSS is a strict-containment\n"
          "     estimate and may read 0 if the kernel merged the probe's VMAs.\n"
          "     It largely cancels in the delta, but do not quote the per-condition\n"
          "     'RSS net of probe' from such a dump.", file=sys.stderr)
    # Fall back to strict containment for kernels without anon-VMA naming.
    total = 0
    for a_key, b_key in (("probe_mtab_addr", "probe_mtab_bytes"),
                         ("probe_evlog_addr", "probe_evlog_bytes")):
        raw = led.get(a_key, "0")
        try:
            base = int(raw, 16) if raw.startswith("0x") else int(raw)
            size = int(led.get(b_key, "0"))
        except ValueError:
            continue
        if not base or not size:
            continue
        for s, e, _p, rss in regions:
            if s >= base and e <= base + size:
                total += rss
    return total


def load(dumpdir):
    files = os.listdir(dumpdir)
    led_f = next((f for f in files if f.endswith(".ledger.txt")), None)
    if not led_f:
        raise SystemExit(f"no ledger dump in {dumpdir}")
    pid = led_f.split(".")[0]
    led = read_ledger(os.path.join(dumpdir, led_f))
    regions, rss_total = read_smaps(os.path.join(dumpdir, f"{pid}.smaps.txt"))
    return {
        "pid": pid,
        "led": led,
        "regions": regions,
        "rss_total": rss_total,
        "rss_probe": probe_self_rss(led, regions),
        "mi": read_mallocinfo(os.path.join(dumpdir, f"{pid}.mallocinfo.xml")),
        "events": replay_events(os.path.join(dumpdir, f"{pid}.mmaps.txt")),
        "dir": dumpdir,
    }


def summarize(c, label):
    led, mi = c["led"], c["mi"]
    req = int(led.get("malloc_live_requested", 0))
    use = int(led.get("malloc_live_usable", 0))
    cnt = int(led.get("malloc_live_count", 0))
    chunk = int(led.get("malloc_live_chunk_est", 0))
    rss_net = c["rss_total"] - c["rss_probe"]

    print(f"\n=== {label}  (pid {c['pid']}) ===")
    print(f"  RSS total                    {c['rss_total']/MIB:10.2f} MiB")
    print(f"  RSS attributable to probe    {c['rss_probe']/MIB:10.2f} MiB")
    print(f"  RSS net of probe             {rss_net/MIB:10.2f} MiB")
    print(f"  malloc live requested        {req/MIB:10.2f} MiB   ({cnt:,} allocations)")
    print(f"  malloc live chunk footprint  {chunk/MIB:10.2f} MiB")
    print(f"  malloc chunk inflation       {(chunk-req)/MIB:10.2f} MiB"
          f"   ({100.0*(chunk-req)/req if req else 0:+.1f}%)")
    if mi:
        d = mi["live_chunks"] - chunk
        print(f"  glibc live chunks (crosscheck){mi['live_chunks']/MIB:10.2f} MiB"
              f"   (probe differs by {d/MIB:+.2f} MiB)")
    if cnt:
        print(f"  mean allocation size         {req/cnt:10.0f} B")

    for k in ("malloc_insert_fail", "malloc_free_untracked", "ev_overflow"):
        v = int(led.get(k, 0))
        flag = "   <-- INVALIDATES requested leg" if v and k != "ev_overflow" else \
               ("   <-- event log truncated" if v else "")
        if v:
            print(f"  !! {k} = {v}{flag}")

    raw = sum(ln for ln, _, kind in c["events"].values() if kind == 1)
    wrap = sum(ln for ln, _, kind in c["events"].values() if kind == 0)
    print(f"  mmap live (libc wrapper)     {wrap/MIB:10.2f} MiB virtual")
    print(f"  mmap live (raw syscall)      {raw/MIB:10.2f} MiB virtual"
          f"   <- OS::safeAlloc path")
    return {"req": req, "chunk": chunk, "cnt": cnt, "rss_net": rss_net,
            "raw": raw, "wrap": wrap,
            "glibc": mi["live_chunks"] if mi else 0,
            "free_held": mi["free_held"] if mi else 0}


def mmap_by_module(c):
    """Resident bytes grouped by the module that mapped the region.

    Driven from the smaps side, not the event side, because the kernel merges
    and splits mappings, so most event addresses are not region starts and
    several events can land inside one region.

    Unattributed bytes go to "[unattributed]" -- that bucket is the interesting
    one: memory the process is resident in that neither the libc wrappers nor
    raw syscall(SYS_mmap) produced, i.e. brk/malloc arenas, the loader, thread
    stacks, or the JVM's own mappings made before the probe initialised.

    Attribution is by *overlapped bytes*, prorating each region's Rss across
    every mapping that intersects it. Matching only "the mapping containing the
    region's start" is wrong because the kernel merges adjacent anonymous VMAs:
    in one observed run an 8 MiB OS::safeAlloc chunk sat at the head of a
    71.94 MiB merged region, and all-or-nothing attribution charged the whole
    63.94 MiB of its Rss to the profiler -- reporting more resident bytes than
    the mapping's entire virtual size.

    Prorating assumes residency is uniform within a region, which it is not.
    That makes these per-module figures good to roughly a MiB, not exact. The
    virtual totals and the malloc legs carry no such assumption.
    """
    by_mod = defaultdict(lambda: [0, 0])  # tag -> [resident, virtual]
    live = sorted(c["events"].items())  # (addr, (len, caller, kind))
    starts = [a for a, _ in live]

    import bisect
    for s, e, path, rss in c["regions"]:
        if rss == 0 or e <= s:
            continue
        span = e - s
        # Walk back far enough to catch a long mapping that starts well before
        # this region, then forward over everything beginning before its end.
        i = bisect.bisect_left(starts, s)
        j = i
        while j > 0 and starts[j - 1] + live[j - 1][1][0] > s:
            j -= 1
        covered = 0
        while j < len(live) and starts[j] < e:
            addr, (ln, caller, kind) = live[j]
            ov = min(e, addr + ln) - max(s, addr)
            if ov > 0:
                tag = module_of(caller, c["regions"]) + (" [raw]" if kind == 1 else "")
                by_mod[tag][0] += rss * ov // span
                by_mod[tag][1] += ov
                covered += ov
            j += 1
        if covered < span:
            tag = "[unattributed] " + (os.path.basename(path) if path else "anon")
            by_mod[tag][0] += rss * (span - covered) // span
            by_mod[tag][1] += span - covered
    return by_mod


def main():
    args = sys.argv[1:]
    if args and args[0] == "--dir":
        base = args[1]
        subs = sorted(d for d in os.listdir(base) if d.startswith("dump_"))
        without = [os.path.join(base, d) for d in subs if d.startswith("dump_without")]
        with_ = [os.path.join(base, d) for d in subs if d.startswith("dump_with_")]
        pairs = list(zip(without, with_))
    elif len(args) == 2:
        pairs = [(args[0], args[1])]
    else:
        raise SystemExit(__doc__)

    agg = defaultdict(list)
    for wo_dir, wi_dir in pairs:
        wo = summarize(load(wo_dir), f"WITHOUT agent [{os.path.basename(wo_dir)}]")
        wi = summarize(load(wi_dir), f"WITH agent    [{os.path.basename(wi_dir)}]")
        print("\n  --- delta (with - without) ---")
        for key, name in (("rss_net", "RSS (net of probe)"),
                          ("req", "malloc requested (logical)"),
                          ("chunk", "malloc chunk footprint"),
                          ("glibc", "glibc live chunks"),
                          ("raw", "raw-syscall mmap virtual"),
                          ("wrap", "wrapper mmap virtual")):
            d = wi[key] - wo[key]
            agg[key].append(d)
            print(f"    {name:32s} {d/MIB:+10.2f} MiB")
        d_free = wi["free_held"] - wo["free_held"]
        agg["free_held"].append(d_free)
        print(f"    {'free-but-held arena bytes':32s} {d_free/MIB:+10.2f} MiB")
        d_inf = (wi["chunk"] - wi["req"]) - (wo["chunk"] - wo["req"])
        agg["inflation"].append(d_inf)
        print(f"    {'of which chunk inflation':32s} {d_inf/MIB:+10.2f} MiB")
        print(f"    {'extra live allocations':32s} {wi['cnt']-wo['cnt']:+10,}")

        # The delta table is what closes the accounting: it says which resident
        # regions the agent actually adds, attributed to the module that mapped
        # them. Per-condition tables are dominated by the JVM and hide it.
        a = mmap_by_module(load(wo_dir))
        b = mmap_by_module(load(wi_dir))
        print("\n  --- resident by mapping module: with - without ---")
        rows = []
        for mod in set(a) | set(b):
            wo_r = a.get(mod, [0, 0])[0]
            wi_r = b.get(mod, [0, 0])[0]
            rows.append((wi_r - wo_r, mod, wo_r, wi_r))
        tot = 0
        for d, mod, wo_r, wi_r in sorted(rows, key=lambda r: -abs(r[0]))[:14]:
            tot += d
            print(f"    {mod:34s} {wo_r/MIB:9.2f} -> {wi_r/MIB:9.2f}  "
                  f"delta {d/MIB:+9.2f} MiB")
        print(f"    {'(sum of rows shown)':34s} {'':9s}    {'':9s}  "
              f"delta {tot/MIB:+9.2f} MiB")
        agg["mmap_resident_delta"].append(sum(r[0] for r in rows))

        # Closure, stated so that each step is either exact by construction
        # or a comparison between genuinely independent instruments.
        #
        # Step 1 is exact: the per-module resident deltas partition the RSS
        # delta, because every region's Rss is prorated across the mappings
        # overlapping it and the remainder goes to [unattributed].
        #
        # Step 2 is the real test: the anonymous bucket's residency (from
        # smaps) against live malloc chunks + free-but-held arena bytes (from
        # the probe's counters and malloc_info). Nothing is shared between
        # those two sides.
        #
        # An earlier version subtracted chunk + free_held + raw_resident from
        # total RSS. That flattered the result, because raw_resident is
        # prorated out of the same smaps whose anon bucket already covers the
        # arena pages -- when the kernel merges a safeAlloc chunk into a large
        # anonymous region, proration error moves bytes between the two and
        # the two errors partly cancel.
        def bucket(t, pred):
            return sum(v[0] for k, v in t.items() if pred(k))
        is_anon = lambda k: "unattributed" in k and "anon" in k and "probe_" not in k
        is_raw = lambda k: "[raw]" in k
        anon_d = bucket(b, is_anon) - bucket(a, is_anon)
        raw_d = bucket(b, is_raw) - bucket(a, is_raw)
        rss_d = wi["rss_net"] - wo["rss_net"]
        chunk_d = wi["chunk"] - wo["chunk"]
        other_d = rss_d - anon_d - raw_d
        malloc_side = chunk_d + d_free
        resid = anon_d - malloc_side
        agg["closure_residual"].append(resid)
        agg["anon_resident"].append(anon_d)
        agg["raw_resident"].append(raw_d)
        print("\n  --- closure ---")
        print(f"    {'RSS delta (net of probe)':40s} {rss_d/MIB:+10.2f} MiB")
        print(f"    {'  = anonymous (arena) residency':40s} {anon_d/MIB:+10.2f} MiB")
        print(f"    {'  + OS::safeAlloc arena residency':40s} {raw_d/MIB:+10.2f} MiB")
        print(f"    {'  + everything else':40s} {other_d/MIB:+10.2f} MiB   (exact by construction)")
        print(f"    {'anon residency, independently:':40s}")
        print(f"    {'    live malloc chunks':40s} {chunk_d/MIB:+10.2f} MiB")
        print(f"    {'  + free-but-held arena pages':40s} {d_free/MIB:+10.2f} MiB")
        print(f"    {'  = total':40s} {malloc_side/MIB:+10.2f} MiB")
        print(f"    {'DISAGREEMENT (independent check)':40s} {resid/MIB:+10.2f} MiB")
        if wi["raw"] - wo["raw"] and abs(raw_d) > abs(wi["raw"] - wo["raw"]):
            print(f"    !! raw residency {raw_d/MIB:+.2f} exceeds its virtual delta "
                  f"{(wi['raw']-wo['raw'])/MIB:+.2f} -- VMA-merge proration error")

    if len(pairs) > 1:
        print("\n=== mean across %d pairs ===" % len(pairs))
        for k, v in agg.items():
            mean = sum(v) / len(v)
            spread = (max(v) - min(v)) / MIB
            print(f"  {k:28s} {mean/MIB:+10.2f} MiB   (range {spread:.2f} MiB, n={len(v)})")


if __name__ == "__main__":
    main()
