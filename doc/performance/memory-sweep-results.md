# Native Memory Sweep — Empirical Results (macOS arm64)

> This is a macOS-only first pass. See
> [memory-sweep-handoff.md](memory-sweep-handoff.md) for open questions and
> instructions to continue this investigation on Linux.

This is a first empirical calibration pass for the model in
[memory-usage-model.md](memory-usage-model.md), run locally on macOS
arm64 (Corretto 25) against `libjavaProfiler.dylib` built from this
checkout. It measures process RSS and the PR #669 `NativeMem` per-category
counters (surfaced as `datadog.ProfilerCounter` JFR events named
`native_mem_*`) across synthetic workloads that sweep thread count,
call-trace diversity, and class/method diversity independently.

**Headline result: the sweep did not behave as the static-analysis model
predicted.** Only thread count produced a measurable signal. Call-trace and
class/method diversity produced *no* measurable change in the `NM_CALLTRACE`
/ `NM_DICTIONARY` / `NM_NATIVE_SYMBOLS` counters, even at 2,000 distinct
classes with confirmed samples landing inside them. This section documents
the harness, the results, and — because the null result itself needed
verification — the debugging that ruled out harness bugs as the explanation.

## Harness

Standalone Java program (`MemSweepMain`), run per sweep point with
`-agentpath:libjavaProfiler.dylib=start,wall=~5ms,jfr,file=<out>,cstack=fp`.
Three modes, each isolating one dimension while holding the others near-constant:

- **`threads N`** — spawns N daemon threads, each busy-looping
  (`Math.sqrt`) for the run duration. Class/method diversity stays at 1.
- **`traces N`** — one thread, one precompiled class with N distinct static
  methods (`m0..mN-1`), invoked in a cycle via reflection. Isolates call-trace
  shape diversity from class-loading (still 1 class).
- **`classes N`** — one thread, N distinct precompiled classes each with one
  `compute()` method, invoked in a cycle via reflection. Isolates
  class/method diversity from call-trace shape variety (same call site).

Two methodology fixes were necessary to get a valid measurement, both worth
recording since they weren't obvious from reading the source:

1. **Classes/methods for the `traces`/`classes` sweeps are precompiled by an
   external, unprofiled `javac` process** before the profiled JVM starts.
   The first version of the harness used `javax.tools.JavaCompiler` in-process,
   which loads thousands of the JDK's own compiler classes into the profiled
   JVM — completely swamping the intended "N synthetic classes" signal.
2. **Every sampled thread must call `JavaProfiler.addThread()` explicitly.**
   With `-agentpath` alone (no in-process API calls), the wall-clock engine
   produced **zero** `datadog.MethodSample` events in every run on this
   build/platform, despite `datadog.WallClockSamplingEpoch` events showing the
   sampler was running on schedule. Threads created after profiler start are
   not auto-registered via a JVMTI callback in this configuration; the harness
   now calls `JavaProfiler.getInstance(...).addThread()` from both the main
   thread and every spawned worker. This is worth flagging on its own: the
   `datadog.MethodSample` event (not `datadog.ExecutionSample`, despite the
   `T_EXECUTION_SAMPLE` constant name in the source) is what wall-clock
   samples are written as; `ExecutionSample`/`ObjectSample` stayed at 0 in
   every run regardless.

RSS was sampled via `ps -o rss=` on the child JVM every 200ms and the max
recorded. `NM_*` counters were read from the JFR file's last
`datadog.ProfilerCounter` event of each name (the counters only refresh at
JFR chunk finish, so short runs produce exactly one snapshot, taken at
process exit).

## Results

| mode | N | max RSS (MiB) | calltrace | dictionary | thread_filter | thread_local | native_symbols |
|---|---|---|---|---|---|---|---|
| threads | 1 | 357 | 24.5 MiB | 4.55 MiB | 40 KiB | 4.0 KiB | 294.6 MiB |
| threads | 4 | 359 | 24.5 MiB | 4.55 MiB | 40 KiB | 4.0 KiB | 294.6 MiB |
| threads | 16 | 363 | 24.5 MiB | 4.55 MiB | 40 KiB | 4.0 KiB | 294.6 MiB |
| threads | 64 | 385 | 24.5 MiB | 4.55 MiB | 40 KiB | 4.0 KiB | 294.6 MiB |
| threads | 256 | 462 | 24.5 MiB | 4.55 MiB | **72 KiB** | 4.0 KiB | 294.6 MiB |
| threads | 1000 | 749 | 24.5 MiB | 4.55 MiB | **136 KiB** | 4.0 KiB | 294.6 MiB |
| traces | 1 – 2000 | 854 – 958 | 24.5 MiB (flat) | 4.55 MiB (flat) | 40 KiB | 4.0 KiB | 294.6 MiB (flat) |
| classes | 1 – 2000 | 853 – 1041 | 24.5 MiB (flat) | 4.55 MiB (flat) | 40 KiB | 4.0 KiB | 294.6 MiB (flat) |

(Full raw CSV of all runs is not checked in; figures above are representative
of the sweep, reproducible with the harness described above.)

### What moved

- **RSS scales clearly with thread count**: ~357 MiB at 1 thread → ~749 MiB
  at 1000 threads, roughly **+400 KB per thread**. This is consistent with
  JVM-reserved/committed native thread stacks (typically several hundred KB
  to 1 MB per thread on the JVM side), not with the profiler's own `NM_*`
  accounting, which barely moved over the same range (see below). **For
  thread-count-driven memory growth, the JVM's own per-thread stacks — not
  the profiler — are the dominant cost.**
- **`NM_THREAD_FILTER` shows the predicted staircase**: flat at 40 KiB up to
  64 threads, steps to 72 KiB at 256, to 136 KiB at 1000 — consistent with
  the chunked (256-slots-at-a-time) allocation model identified by static
  analysis in memory-usage-model.md.

### What didn't move (and shouldn't be assumed away)

- **`NM_CALLTRACE`, `NM_DICTIONARY`, `NM_NATIVE_SYMBOLS`, `NM_THREAD_LOCAL`
  were bit-for-bit identical across every thread/trace/class sweep point**,
  including the 2,000-distinct-class run. This was verified *not* to be a
  harness artifact: the JFR file for that run contains 3,241
  `datadog.MethodSample` events, and grepping the printed stack traces
  confirms 887 of them land inside the synthetic `GenClassN.compute()`
  methods spread across many distinct classes. Real, diverse sampled
  activity reached the profiler — the counters simply didn't reflect it in
  this build/config.
- Two different explanations plausibly apply to different counters:
  - **`NM_DICTIONARY` and `NM_NATIVE_SYMBOLS` are very likely baseline-dominated.**
    `NM_NATIVE_SYMBOLS` sits at ~295 MiB even for a single idle thread —
    almost certainly the indexed symbol tables of the JVM's own large shared
    libraries (`libjvm.dylib` et al.), which dwarfs a few thousand synthetic
    class/method names by 3+ orders of magnitude. `NM_DICTIONARY` at ~4.55 MiB
    is plausibly dominated the same way by the JDK's own ~3,000+ bootstrap
    classes. A delta from 2,000 synthetic classes may simply be below the
    counters' effective resolution in a run this short.
  - **`NM_CALLTRACE` and `NM_THREAD_LOCAL` not moving at all is harder to
    explain by baseline dominance alone** and reads as a possible gap in the
    instrumentation rather than a true reflection of memory behavior:
    `NM_THREAD_LOCAL` stayed at exactly 4,120 bytes from 1 thread to 1,000
    threads, which contradicts the source-level model (`ProfiledThread` is a
    per-OS-thread structure) directly. This should be treated as an open
    question for the profiler team, not as evidence that per-thread native
    memory is actually free.
- **Confirmed via source inspection (see memory-usage-model.md): the JFR
  `MethodMap` / method-symbolication cache in `flightRecorder.h` has no
  `NativeMem::record` calls at all**, except for the line-number-table
  payload (`NM_LINE_TABLES`, which read 0 in every run here — plausibly
  because line-number tables weren't populated for these dynamically loaded
  classes, or because that path wasn't exercised). This is a real,
  independently-confirmed gap: **the "unique classes/methods" workload
  dimension is not currently visible in the `NM_*` counters at all**,
  regardless of the baseline-dominance question above.

## Caveats and follow-ups

- **macOS arm64 only.** `NM_PERF` is Linux-only and reads 0 here
  unconditionally; the CPU-time engine (`cpu=...`) failed to initialize on
  this platform at all (`Agent_OnLoad` error), so only the wall-clock engine
  was exercised. A Linux run would give a full picture and is the natural
  next step, especially for cross-checking whether `NM_CALLTRACE` /
  `NM_THREAD_LOCAL` behave differently there.
- **Short runs (3–20s).** Longer runs, and durations scaled to N (so each
  synthetic method/class gets several samples on average rather than a
  fraction of one), would better separate "genuinely flat" from
  "under-sampled." The 2,000-class/20s run was a step in that direction and
  still showed no movement in `NM_DICTIONARY`/`NM_CALLTRACE`.
- **Single machine, single run per point.** No repeated trials or variance
  estimates; treat the table as indicative, not statistically rigorous.
- **The rough formula in memory-usage-model.md is not yet validated by this
  data** for the trace/class terms — only the thread term (`C_thread`) has
  empirical support here (~400 KB/thread, dominated by JVM stack cost rather
  than the profiler's own accounting). The `C_trace`/`C_class` terms should
  be treated as unverified until the `NM_CALLTRACE`/`NM_DICTIONARY` gaps
  above are understood or fixed.

## Follow-up: separating JVM-internal cost from the profiler's own cost

The result above — RSS scales strongly with thread count while the
profiler's own `NM_*` counters barely move — raises an obvious question:
is that RSS growth actually inside the profiler at all, or is it JVM
machinery the profiler has nothing to do with? Two follow-up investigations
were done to answer this: (1) reading the source to determine whether this
profiler's JFR writer is its own code or piggybacks on HotSpot's internal
JFR engine, and (2) using the JVM's own Native Memory Tracking (NMT,
`-XX:NativeMemoryTracking=summary` + `jcmd VM.native_memory`) to see how
much of the RSS growth HotSpot itself accounts for.

### The profiler's JFR writer is fully self-contained

`flightRecorder.cpp`/`.h` builds the JFR chunk binary format by hand —
chunk header (`Recording::writeHeader`), metadata event
(`writeMetadata`, walking a schema compiled into `jfrMetadata.cpp`), and all
the `jdk.*`-looking bookkeeping events (`jdk.OSInformation`, `jdk.JVMInformation`,
`jdk.InitialSystemProperty`, `jdk.NativeLibrary`, `jdk.ActiveRecording`,
`jdk.ActiveSetting`) are constructed from this codebase's own OS calls,
JVMTI queries (`GetSystemProperty`, `GetSystemProperties` — the *external*
JVMTI API, not HotSpot internals), and internal bookkeeping, then serialized
with the codebase's own `Buffer` writer straight to the output file.
Grepping the whole source tree found **zero** references to HotSpot's
internal `jfr::` namespace, `JfrEvent`, or any HotSpot `jfr/*` header — this
agent does not call into, share memory with, or coordinate with the JVM's
built-in `-XX:+FlightRecorder`/`-XX:StartFlightRecording` engine at all. The
two are completely independent; running this agent produces zero additional
load on HotSpot's own JFR subsystem, and (this is the important part for the
memory question) **all of the profiler's own allocations are made through
plain `malloc`/`new`, which NMT does not track** — NMT only instruments
HotSpot's own internal allocation paths (`os::malloc`, arena allocators,
mmap wrappers). So NMT and the `NM_*` counters cover two genuinely disjoint
regions of memory, and neither one is a full picture on its own:

| | Tracks | Blind to |
|---|---|---|
| NMT (`jcmd VM.native_memory`) | HotSpot-internal: thread stacks, GC, class metadata, code cache, compiler arenas, symbol tables | Anything the profiler agent allocates itself |
| `NM_*` counters (this agent) | The profiler's own tracked structures — calltrace storage, dictionaries, thread-filter, JFR-format write buffers (with the gaps noted above) | Everything on the JVM's side of the fence |
| Raw process RSS | Everything, but as one number | Attribution — doesn't say *why* |

### What NMT showed for the thread-count sweep

Because attaching `jcmd` to a process that also has this profiler agent
attached turned out to be unreliable at higher thread counts (`jcmd`
intermittently failed the attach handshake at 256+ threads with the agent
running — a friction point worth knowing about, not something this
investigation root-caused), NMT was measured on **agent-free** control runs
of the same `MemSweepMain threads N` workload, isolating the JVM's own
thread-scaling cost:

| N threads | NMT "Thread" committed | Process RSS | RSS − 1-thread RSS | NMT Thread Δ /thread | RSS Δ /thread |
|---|---|---|---|---|---|
| 1 | 649 KB (19 threads incl. JVM-internal) | 363 MiB | — | — | — |
| 256 | 21,970 KB (286 threads) | 458 MiB | +95 MiB | ~84 KB | ~415 KB |
| 1000 | 68,538 KB (1030 threads) | 747 MiB | +384 MiB | ~68 KB | ~405 KB |

**NMT's own "Thread" bucket explains only ~17–20% of the actual RSS growth
per thread; total NMT `committed` across *all* categories explains about the
same fraction of total RSS growth (~77 KB of the ~405 KB/thread delta at
n=1000).** The remaining ~80% is invisible to NMT entirely — most likely
OS/kernel-level per-thread cost (pthread structures, stack guard pages,
macOS thread port bookkeeping) that HotSpot's own memory tracker doesn't
instrument. This was measured **without the profiler agent attached at
all**, so it isn't the agent's cost either — it's pure JVM/OS thread
overhead. Combined with the earlier finding that this profiler's own
`NM_THREAD_LOCAL` counter didn't move at all across the same thread-count
range, the practical conclusion is:

- **Thread-count-driven RSS growth on this platform is overwhelmingly a JVM/OS
  cost, not a profiler cost** — of the ~400 KB/thread observed, NMT accounts
  for under a fifth, the profiler's own counters account for effectively
  none of it (whether because it's genuinely near-zero, or because
  `NM_THREAD_LOCAL` has a measurement gap — this data can't distinguish the
  two), and the rest is OS-level thread bookkeeping outside anyone's
  instrumentation.
- **A full RSS accounting needs all three lenses together**: NMT for
  JVM-internal cost, `NM_*` for the profiler's tracked structures, and raw
  RSS as ground truth — with whatever's left over after subtracting the
  first two being the honest "unaccounted" bucket, not attributable to
  either side without further instrumentation (e.g. OS-level tools, or
  `-XX:NativeMemoryTracking=detail` broken down by call site, which wasn't
  attempted here).

### Enabling the right samplers (the second half of this question)

The profiler has several independent sampling engines, each requiring its
own enable flag, and getting *any* signal into the profiler's own structures
depends on picking ones that actually work on the platform under test:

| Engine | Flag | Works on macOS here? |
|---|---|---|
| Wall clock | `wall=<interval>` | Yes, but **only for threads that call `JavaProfiler.addThread()`** — no auto-registration observed in this build |
| CPU (execution sampling) | `cpu=<interval>` | **No** — `Agent_OnLoad` fails outright on this macOS arm64 build (consistent with `cpuEngine=None` being the default here) |
| Allocation profiling | `memory=<interval>[:a][:l\|L]` | Not tested in this sweep — worth adding to future runs to exercise `ObjectSampler`/allocation-path call-trace storage specifically |
| Native malloc tracing | `nativemem=<bytes>` | Not tested here — separate from the always-on `NM_*` self-accounting; this is the *application*-allocation-sampling feature documented in `doc/architecture/NativeMemoryProfiling.md` |
| Native socket tracing | `natsock[=<interval>]` | Not tested |
| Lock contention | — | Not available in this fork (no `lock=` engine) |

This sweep only exercised the wall-clock engine (with explicit
registration). The `NM_CALLTRACE`/`NM_DICTIONARY` flatness noted above was
against real, confirmed wall-clock samples — so it isn't simply "no engine
was active" — but a fuller picture would also drive the allocation
(`memory=`) and native-malloc (`nativemem=`) engines, since those populate
different call-trace/dictionary entries than wall-clock sampling does and
were not exercised at all in this pass.

## Follow-up: was 2,000 just too small to trigger growth?

Yes. The flat `NM_CALLTRACE`/`NM_DICTIONARY` readings above were within the
structures' pre-allocated initial capacity the whole time — not evidence of
a growth-independent baseline. The relevant thresholds, read from source:

- **Call-trace hash table** (`callTraceHashTable.cpp:17,57`):
  `INITIAL_CAPACITY = 65536` slots, `LOAD_RATIO = 0.75` → grows only once
  **≥49,152 distinct call-trace shapes** have actually been recorded. 2,000
  is ~4% of that.
- **Class-name dictionary** (`flightRecorder.h:347`, `stringDictionary.h:67`):
  class names are interned into a `StringDictionary` whose arena
  (`StringArena::CHUNK_SIZE`) allocates in **512 KB chunks** — growth is
  chunk-boundary-triggered, not per-entry. At ~13 bytes/name for names like
  `GenClass1999`, one chunk holds roughly 35,000–40,000 distinct short
  class names before a new chunk (and an `NM_DICTIONARY` counter bump) is
  needed. 2,000 names is under 1 KB of that.

Critically, the threshold is against **distinct shapes/classes that actually
appear in a recorded sample**, not against N. A larger N with too few
samples still produces zero growth, because coverage is bounded by sample
count (birthday/coupon-collector-style), not by how many methods/classes
exist. The original sweep used `wall=~5ms`, so a 60s run only produced
~13,000 samples regardless of N — nowhere near 49,152 distinct shapes even
with 60,000 candidate methods to choose from.

Re-running with `wall=~1ms` and longer durations confirmed real growth once
the threshold was actually crossed:

| Test | Samples captured | `calltrace` before | `calltrace` after |
|---|---|---|---|
| 60,000 methods, 90s, wall=~1ms | 76,400 | 25,692,672 B (~24.5 MiB) | **42,469,888 B (~40.5 MiB)** |

A genuine ~16 MB jump, matching the resize-at-threshold model exactly.

The class-name dictionary, however, **still did not move** even at 40,000
distinct classes with 97,661 samples (coupon-collector estimate: ~36,500 of
the 40,000 classes actually touched by a sample, close to but maybe just
under the ~35–40K threshold estimate above). This wasn't root-caused further
— plausible explanations are (a) the per-name threshold is somewhat higher
than the back-of-envelope estimate, or (b) the per-thread
`StringDictionaryBuffer` (a local buffer that batches entries before merging
into the shared global arena) hadn't flushed enough of them into the
structure this counter actually tracks within the run. Left as an open
question rather than a confirmed dead end.

One more observation from the confirmed calltrace jump: the post-growth byte
value was identical (down to the last digit) across two runs with different
N and different sample counts. That's consistent with **hash-table memory
being a step function of capacity-doubling events, not a smooth function of
unique-entry count** — flat below a resize threshold, a fixed jump at the
threshold, flat again until the next one. For memory modeling purposes,
"how many resize thresholds has this workload crossed" is a better mental
model than "bytes per unique trace."
