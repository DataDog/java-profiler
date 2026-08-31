#!/usr/bin/env python3
"""Per-mapping residency breakdown, to decide whether glibc's free-but-held arena
space is resident.

Reports Rss against Size for every class of mapping, then puts the two competing
models side by side against the measured anon total:

  report's model: anon = uordblks + hblkhd + calltrace
  arena model:    anon = arena    + hblkhd + calltrace

The discriminating quantity is the Rss of the glibc arena regions: if it tracks
mallinfo's `arena`, free-held pages are resident; if it tracks `uordblks`, they
are not.

Arena identification, in order of reliability:
  - the main arena is `[heap]` (brk), named by the kernel;
  - secondary arenas are 64 MiB-aligned mmaps that glibc creates PROT_NONE and
    mprotects incrementally, so they appear as an rw-p head plus a ---p tail
    summing to exactly 65536 kB within one 64 MiB-aligned block.
Everything else anonymous is bucketed by size and permissions so nothing is
silently folded into the arena total.

Usage: analyse_smaps.py <snapshot_dir>
"""
import os
import re
import sys
import statistics as st

MIB = 1024.0  # smaps reports kB


def parse_smaps(path):
    maps = []
    cur = None
    hdr = re.compile(
        r"^([0-9a-f]+)-([0-9a-f]+)\s+(\S{4})\s+(\S+)\s+(\S+)\s+(\d+)\s*(.*)$")
    for line in open(path):
        m = hdr.match(line)
        if m:
            if cur:
                maps.append(cur)
            cur = {"start": int(m.group(1), 16), "end": int(m.group(2), 16),
                   "perms": m.group(3), "inode": m.group(6),
                   "path": m.group(7).strip(), "fields": {}}
            continue
        if cur:
            m2 = re.match(r"^(\w+):\s+(\d+) kB", line)
            if m2:
                cur["fields"][m2.group(1)] = int(m2.group(2))
    if cur:
        maps.append(cur)
    for mp in maps:
        mp["size"] = mp["fields"].get("Size", 0)
        mp["rss"] = mp["fields"].get("Rss", 0)
        mp["anon"] = mp["fields"].get("Anonymous", 0)
        mp["file_backed"] = bool(mp["path"]) and not mp["path"].startswith("[")
    return maps


ARENA_BLOCK = 64 * 1024  # kB


def classify(maps):
    """Tag each mapping. Secondary-arena detection needs the neighbour context,
    so it runs over the address-sorted list rather than per mapping."""
    maps = sorted(maps, key=lambda m: m["start"])
    for mp in maps:
        mp["tag"] = None

    for mp in maps:
        if mp["path"] == "[heap]":
            mp["tag"] = "glibc main arena ([heap])"
        elif mp["path"] == "[stack]":
            mp["tag"] = "main thread stack"
        elif mp["path"].startswith("["):
            mp["tag"] = "kernel (" + mp["path"] + ")"
        elif mp["file_backed"]:
            mp["tag"] = "file-backed"

    # Secondary arenas: glibc's new_heap() mmaps exactly HEAP_MAX_SIZE (64 MiB)
    # aligned to 64 MiB as PROT_NONE, then mprotects the used prefix RW and
    # extends it as the arena grows. The resulting shape is therefore EXACTLY two
    # mappings -- one rw-p prefix followed by one ---p remainder -- spanning one
    # 64 MiB-aligned block.
    #
    # The strict two-mapping requirement matters. A looser "any run summing to
    # 64 MiB containing a ---p" rule also matches a contiguous run of pthread
    # stacks, which are [---p guard][rw-p stack] repeated and can sum to 64 MiB
    # from an aligned start. That leak is what made the first single-pair run
    # report 146 arena mappings in one arm against 169 in the other, with a
    # spurious -52.8 MiB arena Rss delta offset by +80.4 MiB in the generic
    # bucket. A fully-grown arena (one rw-p spanning the whole block, no ---p
    # remainder) is accepted as the degenerate case.
    i = 0
    while i < len(maps):
        mp = maps[i]
        if mp["tag"] is None and mp["perms"].startswith("rw") \
           and mp["start"] % (ARENA_BLOCK * 1024) == 0:
            nxt = maps[i + 1] if i + 1 < len(maps) else None
            # degenerate: whole 64 MiB block grown
            if mp["size"] == ARENA_BLOCK:
                mp["tag"] = "glibc secondary arena"
                i += 1
                continue
            if nxt is not None and nxt["tag"] is None \
               and nxt["perms"].startswith("---") \
               and nxt["start"] == mp["end"] \
               and mp["size"] + nxt["size"] == ARENA_BLOCK:
                mp["tag"] = "glibc secondary arena"
                nxt["tag"] = "glibc secondary arena (reserve)"
                i += 2
                continue
        i += 1

    # pthread stacks: [---p guard][rw-p stack]. Tagged before the generic size
    # buckets so they are not counted as mmap-served malloc.
    for k, mp in enumerate(maps):
        if mp["tag"] is not None or not mp["perms"].startswith("rw"):
            continue
        prv = maps[k - 1] if k > 0 else None
        if prv is not None and prv["tag"] is None \
           and prv["perms"].startswith("---") \
           and prv["end"] == mp["start"] and prv["size"] <= 64 \
           and 256 <= mp["size"] <= 8192:
            mp["tag"] = "pthread stack"
            prv["tag"] = "pthread stack guard"

    for mp in maps:
        if mp["tag"] is not None:
            continue
        if "x" in mp["perms"]:
            mp["tag"] = "anon executable (JIT code cache)"
        elif mp["size"] >= 512 * 1024:
            mp["tag"] = "anon huge >=512MiB (JVM heap)"
        elif mp["size"] == 8192:
            mp["tag"] = "anon 8MiB (calltrace chunk candidate)"
        elif mp["size"] >= 1024:
            mp["tag"] = "anon 1MiB-512MiB"
        elif mp["size"] >= 128:
            mp["tag"] = "anon 128kB-1MiB (mmap-served malloc)"
        else:
            mp["tag"] = "anon <128kB"
    return maps


def read_mallinfo(d, tag, snap_ts):
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
        if not rows:
            continue
        med = st.median([r[1] for r in rows])
        if best is None or med > best[1]:
            best = (rows, med)
    if not best:
        return None
    rows = best[0]
    near = min(rows, key=lambda r: abs(r[0] - snap_ts))
    return {"arena": near[1] / 1048576.0, "uordblks": near[2] / 1048576.0,
            "fordblks": near[3] / 1048576.0, "keepcost": near[4] / 1048576.0,
            "hblkhd": near[5] / 1048576.0}


def report(d, tag):
    sp = os.path.join(d, "smaps", tag + ".smaps")
    if not os.path.exists(sp) or os.path.getsize(sp) < 1000:
        print(f"  !! {tag}: smaps missing or empty")
        return None
    maps = classify(parse_smaps(sp))

    snap_ts = 0
    meta = os.path.join(d, "smaps", tag + ".snapmeta")
    cg_anon = None
    if os.path.exists(meta):
        parts = open(meta).read().split()
        if len(parts) >= 2:
            snap_ts = int(parts[0])
            cg_anon = int(parts[1]) / 1048576.0

    mi = read_mallinfo(d, tag, snap_ts)

    buckets = {}
    for mp in maps:
        b = buckets.setdefault(mp["tag"], {"n": 0, "size": 0, "rss": 0, "anon": 0})
        b["n"] += 1
        b["size"] += mp["size"]
        b["rss"] += mp["rss"]
        b["anon"] += mp["anon"]

    print(f"\n{'='*94}\n{tag}\n{'='*94}")
    print(f"{'class':<42}{'n':>5}{'Size MiB':>11}{'Rss MiB':>10}{'Anon MiB':>10}{'Rss/Size':>10}")
    print("-" * 94)
    for k in sorted(buckets, key=lambda k: -buckets[k]["rss"]):
        b = buckets[k]
        ratio = b["rss"] / b["size"] if b["size"] else 0
        print(f"{k:<42}{b['n']:>5}{b['size']/MIB:>11.1f}{b['rss']/MIB:>10.1f}"
              f"{b['anon']/MIB:>10.1f}{ratio:>10.2f}")
    tot_rss = sum(b["rss"] for b in buckets.values())
    tot_anon = sum(b["anon"] for b in buckets.values())
    print("-" * 94)
    print(f"{'TOTAL':<42}{len(maps):>5}"
          f"{sum(b['size'] for b in buckets.values())/MIB:>11.1f}"
          f"{tot_rss/MIB:>10.1f}{tot_anon/MIB:>10.1f}")
    if cg_anon is not None:
        print(f"\ncgroup anon at snapshot instant : {cg_anon:9.1f} MiB")
        print(f"smaps Anonymous total           : {tot_anon/MIB:9.1f} MiB"
              f"   (diff {tot_anon/MIB - cg_anon:+.1f})")

    arena_rss = sum(b["rss"] for k, b in buckets.items() if "arena" in k) / MIB
    arena_size = sum(b["size"] for k, b in buckets.items() if "arena" in k) / MIB
    if mi:
        print(f"\nmallinfo at the same instant:")
        for k in ("arena", "uordblks", "fordblks", "keepcost", "hblkhd"):
            print(f"  {k:<10} {mi[k]:9.1f} MiB")
        print(f"\n>>> DISCRIMINATOR")
        print(f"  glibc arena regions: Size {arena_size:.1f}  Rss {arena_rss:.1f} MiB")
        print(f"    vs mallinfo arena    {mi['arena']:9.1f}  (diff {arena_rss-mi['arena']:+.1f})"
              f"   <- free-held IS resident")
        print(f"    vs mallinfo uordblks {mi['uordblks']:9.1f}  (diff {arena_rss-mi['uordblks']:+.1f})"
              f"   <- free-held NOT resident")
    return {"buckets": buckets, "tot_rss": tot_rss, "tot_anon": tot_anon,
            "cg_anon": cg_anon, "mi": mi, "arena_rss": arena_rss,
            "arena_size": arena_size}


def main():
    d = sys.argv[1]
    r = {}
    for tag in ("proftrue", "proffalse"):
        out = report(d, tag)
        if out:
            r[tag] = out
    if len(r) == 2:
        a, b = r["proftrue"], r["proffalse"]
        print(f"\n{'='*94}\nPAIRED DELTA (profiling - tracing only)\n{'='*94}")
        keys = sorted(set(a["buckets"]) | set(b["buckets"]))
        print(f"{'class':<42}{'d Size':>11}{'d Rss':>10}{'d Anon':>10}")
        print("-" * 94)
        for k in keys:
            ab = a["buckets"].get(k, {"size": 0, "rss": 0, "anon": 0})
            bb = b["buckets"].get(k, {"size": 0, "rss": 0, "anon": 0})
            ds = (ab["size"] - bb["size"]) / MIB
            dr = (ab["rss"] - bb["rss"]) / MIB
            da = (ab["anon"] - bb["anon"]) / MIB
            if abs(dr) < 0.05 and abs(ds) < 0.05:
                continue
            print(f"{k:<42}{ds:>+11.1f}{dr:>+10.1f}{da:>+10.1f}")
        print("-" * 94)
        print(f"{'TOTAL':<42}{'':>11}{(a['tot_rss']-b['tot_rss'])/MIB:>+10.1f}"
              f"{(a['tot_anon']-b['tot_anon'])/MIB:>+10.1f}")
        if a["cg_anon"] and b["cg_anon"]:
            print(f"\ncgroup anon delta        : {a['cg_anon']-b['cg_anon']:+8.1f} MiB")
        print(f"glibc arena Rss delta    : {a['arena_rss']-b['arena_rss']:+8.1f} MiB")
        if a["mi"] and b["mi"]:
            for k in ("arena", "uordblks", "fordblks", "hblkhd"):
                print(f"mallinfo d {k:<12}  : {a['mi'][k]-b['mi'][k]:+8.1f} MiB")


if __name__ == "__main__":
    main()
