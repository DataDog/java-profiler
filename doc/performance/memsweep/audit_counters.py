#!/usr/bin/env python3
"""Counter audit: does the profiler's NativeMem accounting match what it
actually allocates?

Two questions, both answered from a single same-instant dump produced by
alloc_ledger_probe.so:

  1. Are any allocation sites missed? Compare live *logical* bytes whose
     calling return address falls inside libjavaProfiler.so against the sum of
     the malloc-backed NativeMem::_live[] categories. Whatever is left over is
     a ranked list of uninstrumented call sites, resolved to function names.

  2. Do the instrumented sites count correctly? Per-site bytes can be read off
     the same list and compared against what the owning category claims.

Deliberately compares *within one condition*, not across the with/without
delta. The delta is a whole-process figure that includes JVM-side allocations
the agent merely causes (jmethodID tables, JVMTI buffers); no NativeMem counter
should ever cover those, so differencing would show a meaningless shortfall.

NM_CALLTRACE is excluded from the malloc-side sum: it is backed by
OS::safeAlloc's raw mmap, never by malloc. Its value is checked separately
against the probe's raw-syscall mmap total, which is what validates the whole
counter read.

Usage: audit_counters.py <dumpdir> [--lib <libjavaProfiler.so.debug>]
"""
import os
import re
import subprocess
import sys

MIB = 1024.0 * 1024.0
REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
DEFAULT_DEBUG = os.path.join(
    REPO, "ddprof-lib/build/lib/main/release/linux/x64/debug/libjavaProfiler.so.debug")
NM_HEADER = os.path.join(REPO, "ddprof-lib/src/main/cpp/nativeMem.h")


def category_names():
    src = open(NM_HEADER).read()
    return re.findall(r"^  X\((\w+),", src, re.M)


def read_kv(path):
    out = {}
    if not os.path.exists(path):
        return out
    for line in open(path):
        if line.startswith("#"):
            continue
        k, _, v = line.partition(" ")
        out[k.strip()] = v.strip()
    return out


def read_regions(path):
    regions = []
    hdr = re.compile(r"^([0-9a-f]+)-([0-9a-f]+)\s+\S+\s+\S+\s+\S+\s+\S+\s*(.*)$")
    for line in open(path):
        m = hdr.match(line)
        if m:
            regions.append((int(m.group(1), 16), int(m.group(2), 16),
                            m.group(3).strip()))
    return regions


def module_of(addr, regions):
    for s, e, p in regions:
        if s <= addr < e:
            return os.path.basename(p) if p else "[anon]"
    return "unknown"


def resolve_batch(offsets, debug_lib):
    """Resolve file offsets to function names in one addr2line invocation."""
    if not offsets or not os.path.exists(debug_lib):
        return {}
    proc = subprocess.run(
        ["addr2line", "-f", "-C", "-e", debug_lib] + [hex(o) for o in offsets],
        capture_output=True, text=True)
    lines = proc.stdout.splitlines()
    out = {}
    for i, off in enumerate(offsets):
        fn = lines[2 * i] if 2 * i < len(lines) else "??"
        loc = lines[2 * i + 1] if 2 * i + 1 < len(lines) else "??"
        out[off] = (fn, os.path.basename(loc))
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not args:
        raise SystemExit(__doc__)
    dumpdir = args[0]
    debug_lib = DEFAULT_DEBUG
    if "--lib" in sys.argv:
        debug_lib = sys.argv[sys.argv.index("--lib") + 1]

    pid = next(f.split(".")[0] for f in os.listdir(dumpdir)
               if f.endswith(".ledger.txt"))
    led = read_kv(os.path.join(dumpdir, f"{pid}.ledger.txt"))
    nm = read_kv(os.path.join(dumpdir, f"{pid}.nativemem.txt"))
    regions = read_regions(os.path.join(dumpdir, f"{pid}.smaps.txt"))

    base = int(nm.get("profiler_base", "0"), 16)
    names = category_names()
    live = [int(nm.get(f"nm_live[{i}]", 0)) for i in range(len(names))]
    cat = dict(zip(names, live))

    # Raw-syscall mmap total, which NM_CALLTRACE should track.
    raw_virtual = 0
    mm = os.path.join(dumpdir, f"{pid}.mmaps.txt")
    if os.path.exists(mm):
        alive = {}
        for line in open(mm):
            if line.startswith("#"):
                continue
            op, addr, ln, _caller, kind = line.split()
            addr, ln, kind, op = int(addr, 16), int(ln), int(kind), int(op)
            if op in (0, 3):
                alive[addr] = (ln, kind)
            else:
                alive.pop(addr, None)
        raw_virtual = sum(l for l, k in alive.values() if k == 1)

    # Live logical bytes per call site, split by owning module.
    by_mod = {}
    prof_sites = []
    callers = os.path.join(dumpdir, f"{pid}.callers.txt")
    for line in open(callers):
        if line.startswith("#"):
            continue
        a, b, c = line.split()
        addr, byt, cnt = int(a, 16), int(b), int(c)
        mod = module_of(addr, regions)
        by_mod[mod] = by_mod.get(mod, 0) + byt
        if "libjavaProfiler" in mod:
            prof_sites.append((byt, cnt, addr - base))

    prof_bytes = sum(s[0] for s in prof_sites)
    malloc_cats = {k: v for k, v in cat.items() if k != "CALLTRACE"}
    malloc_sum = sum(malloc_cats.values())

    print(f"=== counter audit: {os.path.basename(dumpdir)} (pid {pid}) ===\n")
    print("  live logical bytes by allocating module:")
    for mod, byt in sorted(by_mod.items(), key=lambda kv: -kv[1])[:8]:
        print(f"    {mod:38s} {byt/MIB:9.2f} MiB")
    total_req = int(led.get("malloc_live_requested", 0))
    print(f"    {'(total, all modules)':38s} {total_req/MIB:9.2f} MiB")

    print("\n  mmap-backed category, cross-checked against the probe:")
    print(f"    NM_CALLTRACE                           {cat.get('CALLTRACE',0)/MIB:9.2f} MiB")
    print(f"    raw syscall(SYS_mmap) live             {raw_virtual/MIB:9.2f} MiB")
    print(f"    difference                             "
          f"{(cat.get('CALLTRACE',0)-raw_virtual)/MIB:+9.2f} MiB"
          "   <- validates the counter read")

    print("\n  THE AUDIT: malloc-backed counters vs measured profiler allocations")
    for k, v in sorted(malloc_cats.items(), key=lambda kv: -kv[1]):
        if v:
            print(f"    NM_{k:36s} {v/MIB:9.2f} MiB")
    print(f"    {'sum of malloc-backed counters':39s} {malloc_sum/MIB:9.2f} MiB")
    print(f"    {'measured, attributed to libjavaProfiler':39s} {prof_bytes/MIB:9.2f} MiB")
    gap = prof_bytes - malloc_sum
    print(f"    {'UNACCOUNTED (measured - counted)':39s} {gap/MIB:+9.2f} MiB")

    print("\n  top allocating sites inside libjavaProfiler.so:")
    prof_sites.sort(reverse=True)
    top = prof_sites[:25]
    syms = resolve_batch([o for _b, _c, o in top], debug_lib)
    for byt, cnt, off in top:
        fn, loc = syms.get(off, ("??", "??"))
        print(f"    {byt/MIB:8.2f} MiB  {cnt:>9,} allocs  +0x{off:<8x} {fn}  ({loc})")


if __name__ == "__main__":
    main()
