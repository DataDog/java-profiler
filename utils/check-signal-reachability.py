#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""Static async-signal-safety reachability check for the profiler's native code.

Builds a call graph from the relocations of ELF object files (`objdump -dr`),
walks it from the signal-handler / malloc-hook entry points in ROOTS and reports
every function that calls into an UNSAFE_SINKS symbol (heap allocation, locks,
stdio, dynamic-loader calls, dynamic TLS, logging, ...).

The graph only contains direct calls, so the objects must be built with
-ffunction-sections (every function gets its own section, so every call carries
a relocation) - the debug configuration (build/obj/main/debug) does that.
Indirect calls (function pointers, virtual dispatch) are not followed.

Exit codes:
  0  no findings outside the allowlist (or --self-test passed)
  1  one or more new findings, one line each:
       <object-file>:<caller symbol> -> <unsafe symbol> (via <path>)
  2  usage / environment error (missing or non-ELF objects, no GNU objdump,
     self-test fixture does not compile, malformed allowlist)
"""

import argparse
import bisect
import collections
import os
import re
import shutil
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor

# ---------------------------------------------------------------------------
# Entry points: mangled-symbol regexes (full match) of the functions that run
# in async-signal context or as a malloc interposer. Extend as needed.
#
# The NativeSocketSampler::{send,recv,write,read}_hook interposers are
# deliberately NOT listed: they run on the calling Java thread, not in a
# signal handler, and are allowed to allocate and lock
# (see ddprof-lib/src/main/cpp/nativeSocketSampler.h).
# ---------------------------------------------------------------------------
ROOTS = [
    # Signal handlers
    r"_ZN6CTimer13signalHandlerE\w+",
    r"_ZN11CTimerJvmti13signalHandlerE\w+",
    r"_ZN6ITimer13signalHandlerE\w+",
    r"_ZN11ITimerJvmti13signalHandlerE\w+",
    r"_ZN10PerfEvents13signalHandlerE\w+",
    r"_ZN14WallClockASGCT19sharedSignalHandlerE\w+",
    r"_ZN14WallClockASGCT13signalHandlerE\w+",
    r"_ZN14WallClockJvmti19sharedSignalHandlerE\w+",
    r"_ZN14WallClockJvmti13signalHandlerE\w+",
    r"_ZN8Profiler11segvHandlerE\w+",
    r"_ZN8Profiler10busHandlerE\w+",
    r"_ZL13wakeupHandleri",
    # malloc interposers (must not re-enter the allocator)
    r"malloc_hook",
    r"calloc_hook",
    r"realloc_hook",
    r"posix_memalign_hook",
    r"aligned_alloc_hook",
    r"_ZL18nested_malloc_hookm",
    r"_ZL25nested_aligned_alloc_hookmm",
]

# ---------------------------------------------------------------------------
# Unsafe sinks: mangled-symbol regexes (full match) that must not be reached
# from a root. "TLS_ACCESS:<var>" is the synthetic node for a thread_local
# access; the library is -fPIC, so every access is a TLS descriptor call that
# can allocate the DTV slot lazily.
# ---------------------------------------------------------------------------
UNSAFE_SINKS = [
    r"TLS_ACCESS:.*",
    r"__tls_get_addr",
    # heap
    r"malloc", r"calloc", r"realloc", r"free", r"aligned_alloc", r"posix_memalign", r"strdup",
    r"_Znwm", r"_Znam", r"_ZnwmRKSt9nothrow_t", r"_ZnamRKSt9nothrow_t",
    r"_ZdlPv", r"_ZdaPv", r"_ZdlPvm", r"_ZdaPvm",
    # locks and one-time initialization
    r"pthread_mutex_lock", r"__cxa_guard_acquire", r"__cxa_atexit",
    r"_ZN8SpinLock4lockEv", r"_ZN8SpinLock10lockSharedEv", r"_ZN5Mutex4lockEv",
    r"_ZN15SharedLockGuardC\dEP8SpinLock", r"_ZN18ExclusiveLockGuardC\dEP8SpinLock",
    r"_ZN13MutexLockerC\d\w*",
    # stdio
    r"vsnprintf", r"snprintf", r"fprintf", r"printf", r"fflush", r"fopen",
    # dynamic loader / unwinder
    r"dlsym", r"dladdr", r"dlopen", r"dl_iterate_phdr", r"backtrace",
    # profiler internals that allocate or lock
    r"_ZN3Log\w+",
    r"_ZN14ProfiledThread17initCurrentThreadEv",  # initCurrentThreadSignalSafe() is fine
]

# Functions whose callees are not followed. The singleton accessors guard a
# function-local static; the guard is initialized at startup, before any
# handler or hook is installed.
BARRIERS = [
    r"_ZN8Counters8instanceEv",
    r"_ZN9Libraries8instanceEv",
    r"_ZN8Profiler8instanceEv",
]

# ---------------------------------------------------------------------------
# Known findings: (caller symbol alternatives, unsafe symbol, tracking issue).
# Symbols are demangled names without parameter lists, exactly as printed in
# the report. --allowlist FILE replaces this list; the file holds one entry per
# line in the same shape:
#   <caller>[|<caller>...] -> <unsafe symbol>  # <JIRA-KEY> [note]
# ---------------------------------------------------------------------------
ALLOWLIST = [
    (("JitCodeCache::findRuntimeStub", "JitCodeCache::findRuntimeStubInfo"),
     "SpinLock::lockShared", "PROF-16313"),
    (("RefCountGuard::RefCountGuard",), "Log::warn", "PROF-16314"),
]

SELF_TEST_FIXTURE = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                 "tests", "signal-reachability-fixture.cpp")

# ---------------------------------------------------------------------------

_SYM_LINE = re.compile(r"^([0-9a-f]+) (.{7}) (\S+)\s+[0-9a-f]+ (?:\.hidden |\.protected |\.internal )?(\S+)$")
# Direct calls, plus PC-relative address materialization (clang -O0 on aarch64
# calls hidden functions via adrp+add+blr; on x86 PC32 covers lea/call alike).
# Taking a function's address is conservatively treated as calling it.
_CALL_RELOC = re.compile(r"^\s+([0-9a-f]+):\s+(R_AARCH64_(?:CALL26|JUMP26|ADR_PREL_PG_HI21|ADR_GOT_PAGE)|R_X86_64_(?:PLT32|PC32|GOTPCREL|GOTPCRELX|REX_GOTPCRELX))\s+(\S+?)([+-]0x[0-9a-f]+)?$")
_TLS_RELOC = re.compile(r"^\s+([0-9a-f]+):\s+(R_AARCH64_TLS\w*|R_X86_64_(?:TLSGD|TLSLD|GOTTPOFF|TPOFF32|GOTPC32_TLSDESC|TLSDESC_CALL))\s+(\S+?)([+-]0x[0-9a-f]+)?$")
_SECTION_HEADER = re.compile(r"^Disassembly of section (\S+):$")
_TLS_SECTION = re.compile(r"^\.(?:tbss|tdata)\.")


class EnvError(Exception):
    """Usage or environment problem: exit code 2."""


def _full(patterns):
    return re.compile("^(?:" + "|".join(patterns) + ")$")


ROOT_RE, SINK_RE, BARRIER_RE = _full(ROOTS), _full(UNSAFE_SINKS), _full(BARRIERS)


def _symbol(node):
    """Node id -> symbol name. Local symbols are qualified as 'sym@object'."""
    return node.rsplit("@", 1)[0] if "@" in node and not node.startswith("TLS_ACCESS:") else node


def _run(cmd, **kw):
    try:
        return subprocess.run(cmd, capture_output=True, text=True, **kw)
    except OSError as e:
        raise EnvError("cannot run %s: %s" % (cmd[0], e))


def check_tools():
    out = _run(["objdump", "--version"])
    if out.returncode != 0 or "GNU objdump" not in out.stdout:
        raise EnvError("GNU objdump is required (found: %s)" %
                       (out.stdout.splitlines()[0] if out.stdout else "none"))
    if not shutil.which("c++filt"):
        raise EnvError("c++filt is required")


def list_objects(obj_dir):
    if not os.path.isdir(obj_dir):
        raise EnvError("object directory not found: %s" % obj_dir)
    objs = sorted(os.path.join(obj_dir, f) for f in os.listdir(obj_dir) if f.endswith(".o"))
    if not objs:
        raise EnvError("no .o files in %s" % obj_dir)
    for o in objs:
        with open(o, "rb") as f:
            if f.read(4) != b"\x7fELF":
                raise EnvError("%s is not an ELF object; only Linux (ELF) objects are supported" % o)
    return objs


def _parse_object(obj):
    """Returns (defined: {node: obj}, edges: [(caller_node, callee_node)])."""
    name = os.path.basename(obj)
    syms = _run(["objdump", "-t", obj])
    dis = _run(["objdump", "-dr", "--no-show-raw-insn", obj])
    if syms.returncode != 0 or dis.returncode != 0:
        raise EnvError("objdump failed on %s: %s" % (obj, (syms.stderr or dis.stderr).strip()))

    local = set()
    by_section = collections.defaultdict(list)  # section -> [(offset, node)]
    for line in syms.stdout.splitlines():
        m = _SYM_LINE.match(line)
        if not m:
            continue
        flags, section, sym = m.group(2), m.group(3), m.group(4)
        if flags[0] == "l":
            local.add(sym)
        if flags[6] == "F" and section.startswith(".text"):
            node = sym + "@" + name if flags[0] == "l" else sym
            by_section[section].append((int(m.group(1), 16), node))
    for funcs in by_section.values():
        funcs.sort()

    def resolve(target, addend, x86):
        if target.startswith(".text"):
            # Call to a local function through its section symbol.
            funcs = by_section.get(target)
            if not funcs:
                return None
            off = addend + (4 if x86 else 0)
            best = funcs[0][1]
            for start, node in funcs:
                if start <= off:
                    best = node
            return best
        if target.startswith("."):
            return None  # data section (.bss, .rodata, ...)
        return target + "@" + name if target in local else target

    defined = {n: name for funcs in by_section.values() for _, n in funcs}
    edges = []
    funcs, starts = [], []
    for line in dis.stdout.splitlines():
        h = _SECTION_HEADER.match(line)
        if h:
            funcs = by_section.get(h.group(1), [])
            starts = [s for s, _ in funcs]
            continue
        if not funcs:
            continue
        m = _CALL_RELOC.match(line)
        tls = None if m else _TLS_RELOC.match(line)
        if not (m or tls):
            continue
        g = m or tls
        off = int(g.group(1), 16)
        # Owning function(s): the last start <= off, plus aliases at the same
        # address (e.g. C1/C2 constructor and D1/D2 destructor variants).
        i = bisect.bisect_right(starts, off) - 1
        if i < 0:
            continue
        addend = int(g.group(4), 16) if g.group(4) else 0
        if tls:
            callee = "TLS_ACCESS:" + _TLS_SECTION.sub("", g.group(3))
        else:
            callee = resolve(g.group(3), addend, g.group(2).startswith("R_X86_64"))
            if callee is None:
                continue
        j = i
        while j >= 0 and starts[j] == starts[i]:
            edges.append((funcs[j][1], callee))
            j -= 1
    return defined, edges


def build_graph(objs):
    defined, graph = {}, collections.defaultdict(set)
    with ThreadPoolExecutor(max_workers=min(16, (os.cpu_count() or 4))) as pool:
        for d, edges in pool.map(_parse_object, objs):
            for n, o in d.items():
                defined.setdefault(n, o)
            for caller, callee in edges:
                graph[caller].add(callee)
    return defined, graph


def demangle_all(nodes):
    nodes = sorted(nodes)
    raw = [_symbol(n).replace("TLS_ACCESS:", "") for n in nodes]
    out = _run(["c++filt"], input="\n".join(raw) + "\n")
    lines = out.stdout.splitlines()
    if out.returncode != 0 or len(lines) != len(nodes):
        raise EnvError("c++filt failed")
    return {n: ("TLS_ACCESS:" if n.startswith("TLS_ACCESS:") else "") + _strip_params(d)
            for n, d in zip(nodes, lines)}


def _strip_params(name):
    """'void ns::f<int>(int) const' -> 'void ns::f<int>'"""
    s = name.rstrip()
    for q in (" const", " volatile", " &&", " &"):
        if s.endswith(q):
            s = s[: -len(q)]
    if not s.endswith(")"):
        return s
    depth = 0
    for i in range(len(s) - 1, -1, -1):
        if s[i] == ")":
            depth += 1
        elif s[i] == "(":
            depth -= 1
            if depth == 0:
                return s[:i] if i else s
    return s


_LIBRARY_FRAME = re.compile(r"^(?:.*\s)?(?:std|__gnu_cxx|__cxxabiv1)::")


def find_violations(defined, graph):
    """BFS from ROOTS; returns [(object, caller, sink, path)] with demangled names."""
    roots = sorted(n for n in set(defined) | set(graph) if ROOT_RE.match(_symbol(n)))
    parent = {r: None for r in roots}
    queue = collections.deque(roots)
    while queue:
        u = queue.popleft()
        s = _symbol(u)
        if SINK_RE.match(s) or BARRIER_RE.match(s):
            continue
        for v in sorted(graph.get(u, ())):
            if v not in parent:
                parent[v] = u
                queue.append(v)

    names = demangle_all(parent)
    found, seen = [], set()
    for u in parent:  # BFS order: shortest path first
        s = _symbol(u)
        if SINK_RE.match(s) or BARRIER_RE.match(s):
            continue
        for v in sorted(graph.get(u, ())):
            if not SINK_RE.match(_symbol(v)):
                continue
            path, x = [], u
            while x is not None:
                path.append(x)
                x = parent[x]
            path.reverse()
            # Attribute calls made inside the C++ standard library to the
            # profiler function that called into it.
            caller = u
            for p in reversed(path):
                if not _LIBRARY_FRAME.match(names[p]):
                    caller = p
                    break
            key = (names[caller], names[v])
            if key in seen:
                continue
            seen.add(key)
            found.append((defined.get(caller, "?"), names[caller], names[v],
                          " -> ".join(names[p] for p in path)))
    return roots, found


_ALLOW_LINE = re.compile(r"^(?P<callers>.+?)\s+->\s+(?P<sink>.+?)\s+#\s*(?P<key>[A-Z][A-Z0-9]+-\d+)\b.*$")


def load_allowlist(path):
    entries = []
    with open(path) as f:
        for n, line in enumerate(f, 1):
            if not line.strip() or line.lstrip().startswith("#"):
                continue
            m = _ALLOW_LINE.match(line.strip())
            if not m:
                raise EnvError("%s:%d: expected '<caller>[|<caller>...] -> <unsafe symbol>  # <JIRA-KEY>'" % (path, n))
            entries.append((tuple(c.strip() for c in m.group("callers").split("|")),
                            m.group("sink").strip(), m.group("key")))
    return entries


def check(obj_dir, allowlist):
    objs = list_objects(obj_dir)
    check_tools()
    defined, graph = build_graph(objs)
    roots, found = find_violations(defined, graph)
    if not roots:
        raise EnvError("none of the ROOTS symbols is defined in %s" % obj_dir)

    new, used = [], set()
    for obj, caller, sink, path in found:
        hit = next((i for i, (callers, s, _) in enumerate(allowlist) if caller in callers and sink == s), None)
        if hit is None:
            new.append("%s:%s -> %s (via %s)" % (obj, caller, sink, path))
        else:
            used.add(hit)
            print("allowlisted [%s]: %s:%s -> %s" % (allowlist[hit][2], obj, caller, sink))
    for i, (callers, sink, key) in enumerate(allowlist):
        if i not in used:
            print("note: allowlist entry [%s] %s -> %s no longer matches; remove it"
                  % (key, "|".join(callers), sink), file=sys.stderr)
    print("%d objects, %d roots, %d findings (%d allowlisted, %d new)"
          % (len(objs), len(roots), len(found), len(found) - len(new), len(new)))
    for line in new:
        print(line)
    return new, found


def self_test():
    """Compile the planted-violation fixture and check its EXPECT* annotations."""
    with open(SELF_TEST_FIXTURE) as f:
        src = f.read()

    def expectations(tag):
        return set(re.findall(r"^// %s: (.+?) -> (.+?)\s*$" % tag, src, re.M))

    expected, allowed, forbidden = (expectations(t) for t in ("EXPECT", "EXPECT-ALLOWLISTED", "EXPECT-NOT"))
    if not expected or not allowed or not forbidden:
        raise EnvError("fixture %s lacks EXPECT / EXPECT-ALLOWLISTED / EXPECT-NOT lines" % SELF_TEST_FIXTURE)
    cxx = os.environ.get("CXX", "c++")
    with tempfile.TemporaryDirectory() as tmp:
        obj = os.path.join(tmp, "fixture.o")
        # Same codegen-relevant flags as the debug configuration.
        cc = _run([cxx, "-O0", "-g", "-fPIC", "-fvisibility=hidden", "-ffunction-sections",
                   "-fdata-sections", "-std=c++17", "-c", SELF_TEST_FIXTURE, "-o", obj])
        if cc.returncode != 0:
            raise EnvError("fixture compile failed:\n" + cc.stderr)
        allowlist = [((c,), s, "SELFTEST-1") for c, s in allowed]
        new, found = check(tmp, allowlist)
    got = {(c, s) for _, c, s, _ in found}
    reported = {(c, s) for c, s in got if (c, s) not in allowed}
    errors = (["MISSED %s -> %s" % e for e in sorted(expected - reported)] +
              ["NOT FOUND (allowlisted) %s -> %s" % e for e in sorted(allowed - got)] +
              ["FALSE POSITIVE %s -> %s" % e for e in sorted(forbidden & got)])
    if len(new) != len(reported):
        errors.append("allowlist did not suppress exactly the EXPECT-ALLOWLISTED findings")
    for e in errors:
        print("self-test: " + e)
    print("self-test %s: %d/%d planted violations reported, %d/%d allowlisted suppressed, %d/%d negative controls clean"
          % ("FAILED" if errors else "PASSED", len(expected & reported), len(expected),
             len(allowed & got), len(allowed), len(forbidden - got), len(forbidden)))
    return 1 if errors else 0


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                 formatter_class=argparse.RawDescriptionHelpFormatter,
                                 epilog=__doc__.split("\n\n", 1)[1])
    ap.add_argument("--obj-dir", help="directory with the ELF .o files to check (e.g. ddprof-lib/build/obj/main/debug)")
    ap.add_argument("--allowlist", help="known-findings file replacing the built-in ALLOWLIST")
    ap.add_argument("--self-test", action="store_true", help="check the planted-violation fixture instead")
    args = ap.parse_args(argv)
    try:
        if args.self_test:
            return self_test()
        if not args.obj_dir:
            ap.print_usage(sys.stderr)
            print("error: --obj-dir is required", file=sys.stderr)
            return 2
        allowlist = load_allowlist(args.allowlist) if args.allowlist else ALLOWLIST
        new, _ = check(args.obj_dir, allowlist)
        return 1 if new else 0
    except (EnvError, OSError) as e:
        print("error: %s" % e, file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
