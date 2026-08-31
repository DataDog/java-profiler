# Native Memory Sweep — Empirical Results (Linux x86_64)

Empirical calibration of the model in
[memory-usage-model.md](memory-usage-model.md), on Linux x86_64
(OpenJDK 21.0.10) against `libjavaProfiler.so` built from this checkout. It
measures process RSS, the JVM's Native Memory Tracking categories, and the
profiler's own `NativeMem` counters (surfaced as `datadog.ProfilerCounter`
JFR events named `native_mem_*`) across synthetic workloads sweeping four
dimensions independently: thread count, call-trace diversity, class/method
diversity, and allocation diversity. A companion macOS arm64 pass is in
[memory-sweep-results.md](memory-sweep-results.md).

This document reports the **current state**. It deliberately does not
chronicle the sequence of investigations that produced it — `git log` on this
file has that. What it does keep are the measurement traps that produced wrong
answers along the way, because anyone re-running this work will hit them too.

## Re-verification after the `origin/main` merge

This branch merged 51 upstream commits (see the branch's own history around
that merge commit). Every measurement below was re-run against the merged
tree to check for drift; results are folded into the relevant sections
in-place rather than kept as a separate report. Summary:

| Check | Result |
|---|---|
| Counter audit (coverage, new uninstrumented sites) | Unchanged: ~95.5% coverage (was ~96%), +0.89 MiB unaccounted (was 0.88 MiB). One new tiny site (`ThreadLocalDataPool::initialize()`, 0.05 MiB), already inside the known residual. |
| Baseline footprint | 41.70 MiB (was 42.49 MiB) — `UnwindFailures` removal (−0.8 MiB) plus a new fixed `ThreadLocalDataPool` cost (+50.7 KB); see "Thread count" and `memory-usage-model.md`. Every other category unchanged. |
| Thread-count marginal cost | Confirmed ~792 B/thread (`sizeof(ProfiledThread)`, post-`UnwindFailures`-fix), matching prediction exactly. |
| Call-trace diversity | Unchanged: 24.53→40.53 MiB at N=2,000→60,000 traces (was 24.5→40.5 MiB). |
| Touched-methods RSS delta | 74.38 ± 10.37 MB (n=3) at N=150,000, fixed-heap — matches the historical ~79 MiB within noise. |
| Allocation diversity | Unchanged: `NM_DICTIONARY` 6.04→6.04 MiB and 6.03→6.05 MiB at the two calibration points; RSS 717→696.5 MiB and 680→681.7 MiB. |
| Chunk-flush burst mechanism | Confirmed still present and still "settles high, doesn't fall back": one forced rotation at N=150,000 took `NM_DICTIONARY` to a 115.25 MiB post-flush peak, settling live at 86.22 MiB, growing further to 127.06 MiB by the next (final) flush. Magnitude isn't directly comparable to the historical 216.62/162.46 MiB figures — that measurement's exact timing parameters (how long before the forced dump) aren't recorded, and this driver is inherently duration/coverage-sensitive (see the open question on that below) — but the *mechanism* (spike shows in `max`, persists in `live`, doesn't revert) is unchanged. |
| `parseDwarfInfo()` gating | Investigated and closed, not fixed — see below. |

The one genuinely new mechanism the merge introduced — the `ThreadLocalDataPool`
fixed baseline cost — is detailed in `memory-usage-model.md`'s baseline table,
not duplicated here.

### `parseDwarfInfo()`: investigated, fixed, and closed without merging

The `ElfParser::parseDwarfInfo()` low-hanging-fruit item from the original
investigation (SFrame/DWARF unwind tables built unconditionally for every
parsed native library, even though they're read only by
`StackWalker::walkDwarf()` under `CSTACK_DWARF` — measured at 4.52 MiB across
22 allocations at 150,000 loaded classes) was implemented, and turned out to
need more care than expected. `Profiler::_cstack`'s constructor default is
`CSTACK_NO` — a real, user-selectable mode, not a distinguishable "not yet
resolved" sentinel — so a naive `cstackMode() != CSTACK_DWARF` gate would
have **permanently and silently skipped building the table for the handful of
libraries parsed at JVMTI `Agent_OnLoad`** (before the later
`VM::VMInit()`-triggered `Profiler::start()` resolves cstack mode), including
`libjvm.so` itself — degrading native-frame unwind quality in an actual
`CSTACK_DWARF` session with no visible error, since libraries are parsed
exactly once and never re-parsed. The correct fix needs a dedicated
`Profiler::_cstack_resolved` flag to disambiguate "not yet decided" from
"decided, and it's `CSTACK_NO`".

After fixing that, re-measuring turned up a second finding: on this
investigation's `classes` benchmark, the *real* savings are only **~0.07 MiB**
(13.03 → 12.96 MiB), not the original 4.52 MiB — because almost the entire
native-library set for that workload loads before `Profiler::start()` runs,
where the gate must conservatively always build. Only a handful of
JDK-internal libraries that load lazily after start (`libmanagement.so`,
`libnet.so`, `libnio.so`, etc.) actually benefit. The fix should have more
value for workloads that `dlopen` native libraries *while actively profiling*
in a non-DWARF mode (JNI-heavy applications, dynamically-attached native
agents) — but no workload measured in this investigation exercises that, so
the benefit there is unquantified, not just small.

Given the added complexity (a new `Profiler` field threaded through a
lifecycle-ordering invariant) isn't clearly justified by a measured benefit,
the fix was implemented, tested, and submitted as
[DataDog/java-profiler#755](https://github.com/DataDog/java-profiler/pull/755),
then **closed without merging** — left as a complete, tested reference for
anyone with a workload where this actually matters.

## Summary

**What drives memory overhead.** Thread count costs the profiler itself
~824 B/thread. This branch briefly shipped a ~296 KB/thread cost instead —
an unconditional `UnwindFailures` allocation that `bff61c47c` instrumented
into `NM_THREAD_LOCAL` but did not remove, discovered when a stale doc figure
was re-checked (see "Thread count" below) — now fixed by porting
`origin/main`'s `e1de4cf08`. The dimension that actually matters for
customer-facing sizing is **the number of distinct *methods* appearing in
sampled stacks** — not classes, not threads. A narrow call graph costs close
to nothing at any scale; a wide one (framework-heavy, generics/lambda-heavy,
microservice-style code) costs ~0.8–1.4 KB per touched method, reaching
~102 MB at 150,000 touched methods.

**Where the profiler's RSS delta goes.** Measured with a whole-process
allocation ledger, the delta decomposes with no meaningful remainder:

| component | Δ (MiB) | SE |
| --- | --- | --- |
| RSS delta, net of the measuring probe | **+60.2** | 3.2 |
| — glibc arena residency | +41.1 | 3.2 |
| — `OS::safeAlloc` arena, resident | +19.9 | 1.5 |
| and the arena side, from independent instruments: | | |
| — live malloc chunk bytes | +33.6 | 2.4 |
| — free-but-held arena pages | +7.6 | 3.0 |
| — **disagreement between the two** | **−0.06** | 0.16 |

Three mechanisms account for it, none of them a missing allocation site:
chunk overhead invisible to logical counters (**+6.44 MiB, SE 0.10** — the
most reproducible figure in this document), free-but-held glibc arena pages
(**+7.6 MiB, but SE 3.0 and a range of −7.2 to +17.2 — existence
established, magnitude not**), and `NM_CALLTRACE` reporting virtual capacity
(48.5 MiB) rather than residency (~19.9 MiB).

> **Confirmed 31 Aug 2026 — and this document had it right.** Counting
> free-but-held arena pages on the *resident* side of that reconciliation was
> correct. Their residency is now measured directly: regressing the paired anon
> delta on Δ`fordblks` over 20 pairs gives a slope of **1.0119 ± 0.0066**
> (R² = 0.9992), i.e. ~100 % resident, confirmed independently by per-mapping
> `smaps` Rss. The magnitude question flagged above is also answered — the term
> is +22.86 ± 8.47 MiB (12 pairs) and +36.90 ± 7.72 (8 pairs) on the dd-trace-doe
> workload, and its run-to-run variation is the sole source of the variance in
> the paired anon delta.
>
> Note for anyone reconciling the two documents:
> `dd-trace-doe-reconciliation-2026-08-27.md` briefly concluded the opposite —
> that arena waste was non-resident and "costs no RSS" — on a mean-matching
> argument. That was a regression against this document's finding and has been
> retracted there.

**Counter accuracy.** The profiler's own counters accounted for 37 % of what
it actually allocated, because `NM_NATIVE_SYMBOLS` was a gauge that never ran
during a recording. Fixed; coverage is now **96 %** (99 % with the library
loaded but idle), leaving 0.88 MiB uncounted.

**A separate, additive cost at JFR chunk boundaries.** Serialization is
expensive and is not part of the steady-state number: one flush takes
`NM_DICTIONARY` from 4.55 MiB to a **216.62 MiB peak, settling at 162.46 MiB
it then keeps**, and builds `NM_METHOD_MAP` from nothing to 13.32 MiB. For
the default single-continuous-recording mode this is paid once, at exit; any
configuration rotating chunks periodically pays it per rotation.

**What we don't know**, in full: ~0.88 MiB of the profiler's malloc is still
unattributed; the final chunk's own serialization cost is emitted nowhere;
`NM_PERF` is unverifiable in this container; the `allocs` and `nativemem=`
engines are lightly calibrated.

## How to read these instruments

Every item here produced a confidently wrong answer at some point. They are
properties of the measurement tools, not of the profiler.

**`NM_*` counters are live gauges, not high-water marks.**
`NativeMem::record(category, delta)` is a relaxed atomic add on every
allocation and free, plus a precisely tracked peak (`_max`, raised at
allocation time) and a 64-tick moving average. All three are emitted per
category as `native_mem_{live,avg,max}_bytes.<category>`. Reading `live` is
wrong for any category that sees frees during the run — `NM_THREAD_LOCAL` is
exactly that case, decremented by a pthread TLS destructor as each thread
exits, so a workload that joins its threads before exit shows a `live` value
that means nothing. `_max` is never reset in production
(`NativeMem::reset()` has no callers), so it is a **lifetime** maximum.

**A counter reading zero may be correct.** `NM_METHOD_MAP` reads 0 at steady
state because the method map is built during serialization and genuinely does
not exist yet — confirmed by the allocation ledger, which finds only 0.88 MiB
total unattributed. Contrast `NM_NATIVE_SYMBOLS`, which read 0 for memory
that *was* allocated and resident; that was a real bug. "The instrument says
zero" and "the instrument is broken" are different claims.

**A doc's "measured" number goes stale the moment the instrumentation it read
changes, silently.** The "824 B/thread" figure this document carried for
`NM_THREAD_LOCAL` was correct when captured — but a later commit
(`bff61c47c`) added `NativeMem::record` calls to `UnwindFailures`'s
constructor, adding ~296 KB/thread to that same category, and the thread-count
sweep was never re-run. The stale number survived three more rounds of doc
consolidation because nothing about it looked wrong in isolation. There is no
tooling fix for this — only re-running the sweep whenever an instrumented
site's allocation behavior changes, not just when its doc prose changes.

**`malloc_trim(0)` reclaiming nothing does not mean there is no free arena
memory.** Trim releases only the heap top and pages that are *entirely* free;
free chunks interleaved with live ones are unreclaimable by construction, and
`malloc_info` shows 61–74 MiB of exactly that. Per-chunk headers and
alignment padding sit on *live* chunks, so trim can never move those either.

**`malloc_info` arena totals are chunk-inclusive; `NativeMem` counters are
logical bytes.** Comparing them directly is a category error, and one such
comparison landed close enough to the right magnitude to look like a
confirmation.

**glibc chunk footprint** (measured on glibc 2.35, not assumed): a normal
chunk costs `malloc_usable_size + 8`; an mmap'd chunk (request ≳128 KB) costs
`usable + 16`, and `usable + 16 == align4096(req + 16)` exactly — page
rounding is **already inside** `malloc_usable_size`, so adding a separate
page-rounding term double counts.

**The "without agent" baseline is not agent-free.** `MemSweepMain` calls
`JavaProfiler.getInstance()` unconditionally — it needs a handle for
`addThread()` — which `System.load()`s the library and runs its constructors in
*both* conditions; `-agentpath` only adds `start,...`. Measured, the library
loaded but not profiling already holds **42.49 MiB** (`NM_CALLTRACE` 24.03,
`NM_NATIVE_SYMBOLS` 13.03, `NM_DICTIONARY` 4.55, `NM_THREAD_LOCAL` 0.85)
against 69.86 MiB while profiling; only `NM_JFR_BUFFERS` and the call-trace
table's resize actually arrive with `start`. **Every RSS delta in this document
therefore understates the total cost of attaching the profiler by roughly
42 MiB**; what they measure is the cost of profiling *activity*.

**NMT is an asymmetric bias.** Its per-allocation header scales with JVM
allocation count, which the agent inflates, so `-XX:NativeMemoryTracking`
enabled in both conditions is symmetric in intent but not in effect: the
logical malloc delta reads +27.1 MiB with NMT off and +33.3 MiB with it on,
and measured chunk inflation roughly doubles (+6.44 → +12.39 MiB).

**Sample relative to steady state, not to launch.** Class loading is
completion-bounded while the measured loop is time-bounded, and the agent
loads measurably slower, so a launch-relative sample can catch the two
conditions at different lifecycle stages. The harness prints
`MEMSWEEP_LOADED`; sample relative to that.

**Run conditions sequentially.** CPU contention between concurrently running
conditions once produced a physically impossible negative delta.

## Harness

Standalone Java programs per sweep point, run with
`-agentpath:libjavaProfiler.so=start,<engine>,jfr,file=<out>,cstack=fp`.
Everything is under `doc/performance/memsweep/`:

```
memsweep/
├── src/
│   ├── MemSweepMain.java          # threads / traces / classes / classesM / allocs
│   ├── GenSources.java            # writes .java sources, compiled externally
│   └── LiveThreadLocalSweep.java  # thread-count-only, dumps while threads are alive
├── run_sweep.sh                   # one sweep point -> CSV with RSS + NM_* counters
├── run_repeated_sweep.sh          # repeated-measures with/without-agent comparison
├── run_repeated_sweep_fixedheap.sh# same, with -Xms=-Xmx -XX:+AlwaysPreTouch
├── run_repeated_sweep_classesm.sh # classesM mode (methods-per-class parameter)
├── run_nmt.sh                     # one sweep point with JVM Native Memory Tracking
├── run_threadlocal_live.sh        # thread-count-only, reads NM_THREAD_LOCAL live
├── run_ledger_capture.sh          # paired capture with the allocation ledger probe
├── alloc_ledger_probe.c           # LD_PRELOAD whole-process allocation ledger
├── alloc_ledger_newops.cpp        # replaceable global operator new/delete
├── analyze_ledger.py              # RSS/malloc/mmap reconciliation
├── audit_counters.py              # NativeMem counters vs measured allocations
├── malloc_info_probe.c            # malloc_info + malloc_trim probe
├── alloc_size_histogram.py        # per-call-site alloc sizes vs the *observed*
│                                  #   mmap threshold -> which categories are
│                                  #   mmap-served (and so non-resident)
├── run_doe_interleaved.sh         # interleaved counterbalanced paired doe runs
├── analyse_doe_interleaved.py     # plateau estimators + reconciliation
├── mallinfo_sampler.c             # allocation-free LD_PRELOAD arena sampler,
│                                  #   works in BOTH arms (the profiler's own
│                                  #   mallinfo counters ride its JFR, so the
│                                  #   tracing-only arm would emit nothing)
├── run_smaps_snapshot.sh          # single-pair per-mapping residency snapshot
├── run_smaps_paired.sh            # 8-pair version, two snapshots per run
├── analyse_smaps.py               # classifies mappings, Rss vs Size per class
├── analyse_smaps_paired.py        # per-class resident deltas + residency slope
├── derive_residency.py            # residency factor per accounting term
└── extract.py                     # parses `jfr print --json` for native_mem_*
```

Workload modes, each isolating one dimension:

- **`threads N`** — N daemon threads busy-looping. Wall-clock engine.
- **`traces N`** — one class, N distinct static methods invoked in a cycle.
  Isolates call-trace shape diversity from class loading.
- **`classes N`** — N classes with one method each. **Every class has exactly
  one method, so this mode alone cannot distinguish "cost tracks classes" from
  "cost tracks methods".**
- **`classesM N M`** — N classes, M methods each, all invoked every cycle.
  Lets classes-touched and methods-touched vary independently.
- **`allocs N`** — N distinct short-lived object shapes. Allocation-sampling
  engine, since no other mode allocates Java objects.

Two harness requirements worth knowing. Classes are precompiled by an
**external, unprofiled `javac`** — compiling in-process would load the JDK
compiler into the profiled JVM and swamp the signal. And **every sampled
thread must call `JavaProfiler.addThread()`**: wall-clock sampling produces
zero `datadog.MethodSample` events for unregistered threads, including main,
despite the sampler running on schedule. That is very likely intentional for
this fork rather than a platform gap.

Optional: `-Dmemsweep.dumpAfterMs=N` forces a mid-run `dump()`, which is the
only way to observe a chunk flush while the process is still alive.

## Results by dimension

### Thread count

**Correction (re-measured after `bff61c47c`).** The table and conclusion
below this paragraph are stale: they were captured before that commit added
`NativeMem::record` calls to `UnwindFailures`'s constructor/destructor
(`unwindStats.h`), and were never re-run afterward — an instance of exactly
the "did we measure wrong" risk this document's audit was meant to catch.
`ProfiledThread` (`threadLocalData.h`) embeds a `UnwindFailures` member whose
constructor unconditionally allocates two buffers totaling
`1024 × 256 + 1024 × 4 × 8` = **294,912 bytes (288 KiB)**, regardless of
whether that thread ever has an unwind failure to record. Re-measured
directly (current tree, `run_threadlocal_live.sh` / a standalone
`forTid()` harness, three independent methods agreeing to 0.04%):

| N threads | `NM_THREAD_LOCAL` (all N alive) | VmRSS |
|---|---|---|
| 1 | 2,662,720 B | 71,864 kB |
| 8 | 4,733,712 B | — |
| 32 | 11,834,256 B | 84,452 kB |
| 64 | 24,851,344 B (reproducible at 5 s and 15 s hold) | 101,524 kB |

`NM_THREAD_LOCAL` scales at **~295,856 B/thread** (N=1→32), matching
`sizeof(ProfiledThread)` + the `UnwindFailures` buffers (824 + 294,912 =
295,736) almost exactly. N=32→64 comes in higher, at ~406,784 B/thread —
reproducible, not a dump-timing artifact (unchanged across hold durations),
but not explained; treat the ~296 KB/thread figure as the reliable one and
this super-linearity above N≈32 as an open question. `NM_THREAD_FILTER`
still steps at 256-slot chunk boundaries and is unaffected.

RSS grows **~406 KB/thread** (N=1→32) — meaning the profiler's own
`NM_THREAD_LOCAL` growth (~296 KB/thread) now accounts for roughly
**70–75 %** of that, not "1/460th, all JVM/OS machinery" as the original
table claimed. That original conclusion is inverted: most of the per-thread
RSS growth *is* the profiler's own allocation, driven by the `UnwindFailures`
table every profiled thread carries.

**Fixed.** `origin/main`'s `e1de4cf08` ("Make ProfiledThread's UnwindFailures
field debug only", #734) gates the entire `UnwindFailures` class and the
`ThreadLocalData` member behind `#ifdef DEBUG` — release builds allocate
nothing at all for it, rather than allocating it and merely accounting for
it (which is all `bff61c47c` did on this branch). Ported to this branch
directly (`git cherry-pick e1de4cf08`, zero conflicts). It also wires up the
actual failure-recording call sites in `HotspotSupport::walkVM` for the first
time — this branch had the allocation and the JFR-serialization code but
nothing populating the table, so the feature was silently dead — and fixes an
unrelated latent bug in the same function: an unwindable-stub-frame case that
previously fell through into an infinite loop is now terminated explicitly.
Confirmed post-fix: `sizeof(ProfiledThread)` 824 → 792 B (the `UnwindFailures`
member is compiled out, shrinking the struct slightly), and a rebuilt release
`.so` shows `NM_THREAD_LOCAL` scaling back down to roughly 800-900 B/thread
in a live sweep, matching the release-build prediction of ~296 KB/thread
eliminated. Release/debug gtest suites (`stress_threadLifecycle_ut`,
`thread_teardown_safety_ut`, and the newly-debug-gated `ddprof_ut`
`UnwindFailures` unit test) all pass on both configs post-port.

Measured with `LiveThreadLocalSweep.java`, which forces a JFR chunk write
while all N threads are still alive — necessary because `NM_THREAD_LOCAL` is
decremented as threads exit.

### Call-trace shape diversity (`traces`)

| N methods | duration / interval | max RSS | `NM_CALLTRACE` |
|---|---|---|---|
| 2,000 | 10s / `wall=~5ms` | 426 MiB | 24.5 MiB (baseline) |
| 60,000 | 100s / `wall=~1ms` | 776 MiB | **40.5 MiB** |

The call-trace hash table starts at 65,536 slots and doubles once load
crosses 75 % — i.e. once ≥49,152 distinct shapes have actually been recorded.
The 60,000-method run crosses it and lands at exactly **42,469,888 bytes**,
byte-identical to the macOS pass, as expected for a machine-independent
capacity jump.

The high RSS here is the harness's reflection-based invocation driving
method-accessor generation and JIT, not profiler cost.

### Class/method diversity (`classes`)

| N classes | duration / interval | max RSS | `NM_CALLTRACE` |
|---|---|---|---|
| 2,000 | 10s / `wall=~5ms` | 417 MiB | 24.5 MiB (baseline) |
| 150,000 | 180s / `wall=~1ms` | 2.2 GiB | **48.5 MiB** |

`NM_CALLTRACE` doubles for the same reason as `traces`: each class's method is
a distinct callee frame, so N classes yield up to N distinct shapes even
though the call *site* is one line of harness code.

`NM_DICTIONARY` stays at its 4.55 MiB baseline in a single-chunk run. That is
correct, not a measurement failure — wall-clock dictionary growth happens
during serialization (see "Chunk-flush cost").

### Allocation diversity (`allocs`)

| N shapes | duration / interval | max RSS | `NM_DICTIONARY` | shapes sampled |
|---|---|---|---|---|
| 2,000 | 15s / `memory=512:a` | 717 MiB | **6.04 MiB** | 1,115 / 2,000 |
| 20,000 | 60s / `memory=256:a` | 680 MiB | 6.03 MiB | — |

**Allocation sampling shows dictionary growth in the same chunk**, unlike
wall-clock sampling — confirmed by a same-machine, same-N A/B against
`classes` (4.55 MiB flat there vs 6.04 MiB here). Both engines grow the
dictionary; they differ in *when* it becomes visible. The `ObjectSample` path
appears to intern the class at sample time, but that half is inferred from
timing, not traced to a call site.

The two rows landing at the same value is the same arena-chunk step function
seen in `traces`.

`nativemem=` (native malloc tracing, distinct from the always-on `NM_*`
self-accounting) was smoke-tested only: it initializes and produces real
`datadog.NativeMemoryAllocation` events, but no allocation-heavy workload was
built to characterize it.

### CPU engine and `NM_PERF`

`cpu=10ms` initializes and samples correctly here (it fails outright on the
macOS build). `NM_PERF` reads 0, for an understood reason rather than an open
question:

```
// perfEvents_linux.cpp:874 — downgrades if kernel symbols aren't readable
if ((_ring & RING_KERNEL) && !Symbols::haveKernelSymbols()) { _ring = RING_USER; }
// perfEvents_linux.cpp:885 — with cstack=fp and RING_USER, this is false
_use_mmap_page = _cstack != CSTACK_NO &&
                 (_ring != RING_USER || _cstack == CSTACK_DEFAULT || _cstack == CSTACK_LBR);
// perfEvents_linux.cpp:678 — NM_PERF only counts a page that was mapped
if (page != NULL) { NativeMem::record(NM_PERF, (long long)(2 * OS::page_size)); }
```

This container has `kptr_restrict=1`, so kernel symbols are unreadable, the
ring downgrades to `RING_USER`, and with `cstack=fp` the mmap page is never
allocated. **A host permission gate, not a profiler bug** — re-check on a host
with relaxed `kptr_restrict`.

## What the profiler actually adds

With/without-agent comparison, `classes` mode, 10 reps per condition per N,
interleaved in same-size batches:

| N classes | RSS, agent | RSS, no agent | **Δ** |
|---|---|---|---|
| 2,000 | 284.4 ± 66.9 MB | 286.1 ± 71.0 MB | **−1.7 MB** (noise) |
| 20,000 | 467.2 ± 7.6 MB | 445.4 ± 7.8 MB | **+21.9 MB** |
| 60,000 | 962.3 ± 13.9 MB | 922.3 ± 20.9 MB | **+40.0 MB** |
| 150,000 | 1966.2 ± 89.0 MB | 1863.8 ± 89.9 MB | **+102.4 MB** |

The N=150,000 row's ±89 MB per-condition stdev makes its point estimate
imprecise. A fixed-heap redo (`-Xms=-Xmx`, `-XX:+AlwaysPreTouch`, 12 reps) cut
per-condition stdev roughly 10× to ~6–11 MB and put the delta at ~79 MiB.

### The driver is touched methods, not touched classes

Every class in the `classes` sweep has exactly one method, so
classes-touched and methods-touched move together by construction. `classesM`
separates them:

| Configuration | Classes touched | Methods touched | RSS Δ | per touched method |
|---|---|---|---|---|
| N=2,000, 1 method/class | 1,872 | 1,872 | ~0 (noise) | — |
| N=20,000, 1 method/class | 16,311 | 16,311 | +21.9 MB | 1.38 KB |
| N=150,000, 1 method/class | 84,640 | 84,640 | +102.4 MB | 1.24 KB |
| **N=2,000, 100 methods/class** | **2,000** | **96,953** | **+74.3 MB** | **0.78 KB** |

The last row costs nearly as much as the 150,000-class row using **75× fewer
classes**. `NM_CALLTRACE` confirms it without any RSS noise: both land on the
identical 48.5 MiB capacity, because the structure counts call-trace shapes
and never counted classes.

A smaller-contrast attempt (N=20,000 × 5 methods) was inconclusive — that
configuration is unexpectedly noisy run to run, for reasons not identified —
which is why the 100× design was chosen.

### NMT breakdown, and the one confirmed mechanism

Averaging 10 reps per condition at N=150,000 and diffing by category:

| NMT category | with agent | without | Δ |
|---|---|---|---|
| Class | 343.1 MB | 329.2 MB | **+13.6 MB** |
| Internal | 20.9 MB | 9.1 MB | **+11.6 MB** |
| Java Heap | 616.0 MB | 605.4 MB | +10.4 MB |
| NMT's own bookkeeping | 54.0 MB | 43.4 MB | +10.3 MB |
| GC / Thread / Code / Metaspace / Symbol | — | — | ~0 |

NMT explains 45.5 of the 102.4 MB (44 %). **The Class/Internal lines have a
confirmed mechanism:** the agent registers a `ClassPrepare` callback only when
attached (`vmEntry.cpp:511,523`) and calls
`JVMSupport::loadMethodIDsImpl()` → `GetClassMethods()`
(`jvmSupport.cpp:160–178`) to eagerly preallocate every newly prepared class's
jmethodIDs, which AsyncGetCallTrace's signal-handler safety requires. A toggle
test disabling this collapses the NMT-visible deltas to noise, confirming
~35 MB of the total.

Note the NMT-bookkeeping row is the asymmetric bias described earlier — it is
NMT measuring itself, not profiler cost.

## Where the RSS delta goes

Rather than guessing which call site to instrument next, `alloc_ledger_probe.c`
measures every allocation the process makes and reports what the RSS delta
consists of. It tracks live malloc bytes three ways (requested, usable, count)
plus an append-only log of every mapping event with its caller.

Three things it must do that a naive shim does not, each of which silently
loses most of the signal:

- interpose **`mmap64`**, which is what `libjvm.so` actually imports — an
  `mmap`-only shim sees exactly one JVM mapping;
- interpose **`syscall()`**, because `OS::safeAlloc`/`safeFree`
  (`os_linux.cpp:658-670`) use a naked syscall *specifically* to be
  uninterceptable, and that is where `NM_CALLTRACE`'s arena comes from;
- **name its own mappings** via `prctl(PR_SET_VMA_ANON_NAME)` so its side
  tables can be subtracted exactly — they are resident in proportion to
  allocation count, hence larger in the with-agent condition, and would
  otherwise manufacture part of the delta being measured.

Validated against ground truth (a known population of allocations reproduces
every quantity exactly) and against glibc's own view — `system.current −
(fast + rest) + mmap` from `malloc_info` — agreeing to 0.26 % absolute and
0.01 MiB on the delta. `malloc_insert_fail`, `free_untracked` and
`ev_overflow` are zero in every run.

**Protocol:** N=150,000 `classes`, fixed heap, JDK 21, conditions run
sequentially, sampled 165 s after `MEMSWEEP_LOADED`, NMT off. 7 paired runs.

The per-module resident deltas partition the RSS delta exactly by
construction. The real test is whether the anonymous (arena) bucket, measured
from smaps, matches what the malloc instruments say independently:

| | Δ (MiB) | SE |
| --- | --- | --- |
| RSS delta, net of the probe's own footprint | +60.2 | 3.2 |
| anonymous (glibc arena) residency | +41.1 | 3.2 |
| `OS::safeAlloc` arena residency (+24.0 virtual, exactly, every run) | +19.9 | 1.5 |
| **anon, from the other side:** live malloc chunk bytes | +33.6 | 2.4 |
| **anon, from the other side:** free-but-held arena pages | +7.6 | 3.0 |
| **disagreement** | **−0.06** | **0.16** |

Across all 9 pairs (both NMT settings) that disagreement never exceeds
0.66 MiB, on deltas of 50–77 MiB. Two instruments sharing no code and no data
source agree to well under a megabyte.

**Three mechanisms, none a missing allocation site:**

1. **Chunk overhead the counters cannot see: +6.44 MiB (SE 0.10, sd 0.27).**
   `NativeMem` records logical bytes; RSS pays for chunks. At a mean
   allocation size of ~83 B the agent's ~650,000 extra live allocations carry
   ~17 % inflation. The most reproducible figure in this document.
2. **Free-but-held arena pages: +7.6 MiB, SE 3.0, range −7.2 to +17.2.** Real
   rather than an artifact — the smaps anon bucket independently requires it,
   tracking it even into the runs where it went negative — but a genuinely
   variable quantity depending on arena fragmentation at the sampling instant.
   **Do not quote its mean as a fixed cost.**
3. **`NM_CALLTRACE` reports capacity, not residency.** Its deterministic
   48.5 MiB is virtual; measured resident delta is +19.9 MiB against a virtual
   delta of exactly +24.0 MiB in all 9 runs. This error runs *opposite* to the
   other two.

Caveat: per-module residency is prorated across merged VMAs, so the split
between the anon and `safeAlloc` buckets is good to a few MiB, not exact — in
one run the kernel merged an 8 MiB `safeAlloc` chunk into a 71.9 MiB anonymous
region. The malloc-vs-smaps check above carries the argument precisely because
it is unaffected by that.

### `NM_CALLTRACE`: counting residency at source instead of correcting for it

Mechanism 3 above (`NM_CALLTRACE` reports capacity, not residency) was a
*counter* bug, not a memory bug, and it is now fixed at source rather than
corrected after the fact.

`LinearAllocator::allocateChunk()` recorded the whole `CALL_TRACE_CHUNK`
(8 MiB, `callTraceHashTable.cpp`) into `NM_CALLTRACE` the instant the chunk was
`mmap`'d — before any byte in it was touched. Chunks are then filled
incrementally by `alloc()`'s bump pointer, and `reserveChunk()` eagerly
reserves the *next* chunk once the current one crosses 50 % fill, so at any
snapshot at least one fully-counted chunk was mostly or entirely untouched.
The counter therefore moved in 8 MiB steps regardless of real use.

The fix moves the accounting into `alloc()`, recording exactly the bytes handed
out. Because the bump pointer advances monotonically and every returned pointer
is written into immediately by its caller, cumulative bump-allocated bytes
track touched bytes directly — no separate residency measurement, and no
correction factor. `freeChunk()`/`freeChunks()` decrement each chunk's consumed
extent (captured *before* `safeFree` unmaps it), and `clear()` un-records the
retained `_tail`'s extent explicitly, since no `freeChunk()` runs for it.

**Measured, `classes` 150,000 / 60 s, same build, only the accounting differing:**

| | `NM_CALLTRACE` | `live_total` |
| --- | --- | --- |
| capacity accounting (before) | 25,725,744 B = 24.53 MiB | 42.23 MiB |
| residency accounting (after) | 5,642,032 B = 5.38 MiB | 23.07 MiB |

Every other category was byte-identical across the pair (`dictionary`
4,774,032; `native_symbols` 12,453,944), so the entire 19.15 MiB difference is
this one counter. `linearAllocator_nativemem_ut.cpp` pins the new behaviour and
fails against the old code, reporting a whole 1 MiB chunk where 12,800 B had
been handed out.

**Cost.** `alloc()` is reached only from the `key_value == 0` branch of
`CallTraceHashTable::put()` — i.e. only for a call trace not already in the
table; repeat samples of a known stack take `findCallTrace()` and never
allocate. So this is a per-*distinct*-trace cost, not a per-sample one.
Microbenchmarked on the isolated allocator (3 runs each, sd < 1 ns):

| | before | after | after, peak already established |
| --- | --- | --- | --- |
| single-thread | 12.62 ns | 25.66 ns | 18.15 ns |
| 8 threads, contended | 64.87 ns | 116.3 ns | ~78.3 ns |

Roughly 7.4 ns of the single-thread increase is `record()`'s peak high-water
CAS, whose comment notes it fires rarely "since `_max` is monotonic" — true for
the old once-per-chunk call site, but during a pure-growth phase at a per-alloc
call site every allocation sets a new high-water and the CAS fires every time.
Real rotation makes live oscillate below an established peak, which is the
third column. In absolute terms the per-run cost is milliseconds.

**Why this beats the ×0.829 correction.** That factor was legitimately derived
(a resident delta of +19.9 MiB against a virtual delta of exactly +24.0 MiB,
all 9 runs) but it is a *ratio measured in one workload*. The fill ratio here
is 5.38/24.53 ≈ 0.22, nothing like 0.83 — the fraction of reserved capacity
actually touched depends on where in the fill/rotation cycle the chunk is
emitted and on how many distinct traces the workload produces. A constant
cannot carry that. Counting at source removes the need for one.

**~~Open, and the reason this is not yet called closed:~~ RETRACTED.** This
paragraph previously named `LinearAllocator::clear()` as the remaining gap
between "counts touched bytes" and "equals RSS": `clear()` resets `offs` and
un-records but does not `munmap` the retained `_tail`, so pages it already
touched stay resident while the counter forgets them, and a chunk re-filled
after `clear()` re-counts pages that were never released.

Every clause of that is an accurate description of what `clear()` does. The
error was treating it as a code path. **`clear()` is reachable only from
`~LinearAllocator()`**, so it never runs in a live profiler; the production
reset is `detachChunks()` + `freeChunks()`, and `freeChunks()` calls
`OS::safeFree` (`munmap`) on every chunk while decrementing exactly the byte
count `alloc()` recorded for it. Pages are genuinely returned to the kernel and
cgroup `anon` drops with them. The "bounded by roughly one chunk" framing implied
a production path that does not exist, and the proposed fix — tracking a
per-chunk touched high-water kept across `clear()` — is therefore **not needed
and should not be built.**

The real under-counts in this path are the 64-byte chunk header, page rounding
of the bump pointer, and the reserve chunk's touched first page: together well
under 0.1 MiB, not one chunk. What *does* remain is a sampling-phase artefact
rather than an accounting one — `live` is read after serialization has already
rotated the arena, so it reports the trough of the cycle. See **Remaining named
biases** in `dd-trace-doe-reconciliation-2026-08-27.md`.

## Counter accuracy

`audit_counters.py` attributes every live allocation to its call site and
compares against the counters read at the same instant. Two prerequisites,
both non-obvious:

- The probe defines the replaceable global **`operator new`/`delete`** family
  (`alloc_ledger_newops.cpp`). libstdc++'s `operator new` reaches `malloc`
  through its own PLT, so without this every `new`, STL container and
  `CountingAllocator` byte is attributed to libstdc++ rather than the profiler.
- **`libjavaProfiler.so` statically links libstdc++ and does not export
  `operator new`** (`nm -D` shows no `_Znwm`), so its internal `new` binds to
  a private copy the override never sees. The probe is given that copy's
  address range and unwinds out of it via libgcc's `.eh_frame` unwinder.

Counters are read directly from the running process — `NativeMem::_live[]` is
a file-local static, so its offset comes from `nm` on the debug object plus
the load base from `dl_iterate_phdr`. That bypasses the JFR path. The read is
validated against a known quantity: `NM_CALLTRACE` reads 48.53 MiB against
48.00 MiB of independently measured live raw `syscall(SYS_mmap)`. It is
excluded from the malloc comparison for that same reason — it is mmap-backed.

**Result** (both reps byte-identical; these are structural allocations):

| | profiling active | library loaded, idle |
| --- | --- | --- |
| measured malloc from `libjavaProfiler.so` | 22.21 MiB | 18.74 MiB |
| malloc-backed counters, **before** the fix | 8.30 MiB | 5.44 MiB |
| malloc-backed counters, **after** the fix | **21.32 MiB** | **18.46 MiB** |
| uncounted, before → after | 13.91 → **0.88** MiB | 13.30 → **0.27** MiB |

**The cause was one broken category.** `NM_NATIVE_SYMBOLS` is a `setLive()`
gauge that was written only by `Profiler::updateNativeLibMemStats()`, called
solely from `Profiler::stop()` and `Profiler::dump()`. Neither fires during a
recording, so it held 0 for the entire life of a profiled process while
`CodeCache` really held 13.03 MiB — split across `CodeCache::setDwarfTable`
(4.52 MiB), `CodeCache::add` (5.09 MiB over 92,747 allocations), the
`CodeCache` constructor (0.30 MiB), and `new CodeBlob[_capacity]` arrays. `CodeCache::memoryUsage()` itself was correct
and simply never evaluated.

**The fix** recomputes the gauge at the end of `Libraries::updateSymbols()`,
which is the only function that grows `_native_libs`; a published `CodeCache`
is immutable (`add()`, `expand()` and `setDwarfTable()` each assert they run
pre-publication), so recomputing where the tables change makes the gauge
accurate at any later instant, with no polling. Counter-only change: it
allocates nothing, and class-load time and RSS are unchanged.

**Every instrumented site counts correctly.** `StringDictionary` 4.50 MiB
against `NM_DICTIONARY` 4.55; `FlightRecorder::start` 1.16 against
`NM_JFR_BUFFERS` 1.16; `ProfiledThread::forTid` 2.25 against
`NM_THREAD_LOCAL` 2.54. The `NM_MISC` gauge (`wallClock.h:83`) refreshes every
sampling iteration and correctly uses `capacity()`, and `LivenessTracker`'s
realloc records a capacity *difference* rather than a usable-size one. No
miscounting was found anywhere.

## Chunk-flush cost

Serialization is a large, separate cost that the steady-state numbers above
deliberately exclude. Measured by forcing a mid-run `dump()` and reading
`NativeMem::_live[]`/`_max[]` directly either side of it:

| category | live before | live after | max before | max after |
| --- | --- | --- | --- | --- |
| `NM_DICTIONARY` | 4.55 | **162.46** | 4.55 | **216.62** |
| `NM_METHOD_MAP` | 0.00 | 13.32 | 0.00 | 13.32 |
| `NM_CALLTRACE` | 40.53 | 27.95 | 40.53 | 59.96 |
| `NM_LINE_TABLES` | 0.00 | 4.16 | 0.00 | 4.16 |

One flush peaks the dictionary at 216.62 MiB and leaves 162.46 MiB behind.
Raw string content for 150,000 short class names is only ~2 MB. Both the 80×
amplification and the fact that it does not fall back are now explained.

**The growth is overflow tables, not strings.** Caller attribution during a
flush is unambiguous: **154.98 MiB across 26,450 allocations from
`StringDictionaryBuffer::insert_with_id`**, which is 6,144 bytes each —
exactly `sizeof(SBTable)` (`ROWS`=128 rows × 48 B per `SBRow`: `keys[3]` +
`ids[3]` + `next`). Essentially all of the growth is hash-table structure.

The dictionary resolves collisions by chaining **a whole 6 KB table off a
single overflowing row**. A row holds `CELLS`=3 keys; the fourth key hashing
there allocates a full 128-row `SBTable` of which that key occupies one cell.
The per-level rehash is a 32-bit rotate-right by `ROW_BITS`=7 with the row
picked as `h % ROWS`, so there are only ⌈32/7⌉ ≈ 5 non-overlapping 7-bit
slices before bit ranges start repeating (full repetition at 32 levels) —
keys that collide once tend to keep colliding down the chain, and each link
buys about 3 usable slots for 6 KB. Net: 26,450 tables × 384 slots ≈ 10.2 M
slots allocated for a few hundred thousand interned strings, low single-digit
percent occupancy.

**It does not fall back because the grown buffer is the live dictionary, not
garbage.** `rotate()` performs a two-phase ID-preserving copy (active →
clearTarget, then old_active → new_active) so IDs stay stable across chunks,
and during serialization `lookupDuringDump(key)` inserts each newly resolved
name into *both* the dump buffer and the new active. When the flush completes,
the new active holds the full cumulative interned set by design. Only the old
generation is released by `clearStandby()` — which is what the 216.62 → 162.46
MiB step is: one buffer of the triple-buffered set (active / dump /
clearTarget) being freed, not the structure shrinking.

**Implication for optimization:** growing by rehashing into a larger table, or
simply raising `CELLS`, would cut this dramatically. The current design pays
6 KB per collision cluster regardless of how few keys land in it.

Note `NM_CALLTRACE`'s live value *falls* across the rotation while the
dictionary's persists: **call-trace memory is bounded per rotation window,
class-name dictionary memory accumulates across rotations** up to
`MAX_CLASS_MAP_SIZE` (262,144 entries). Materially different long-term
profiles for two structures that otherwise look alike.

### `MethodMap`: a node-per-method `std::map`, sized against a flat alternative

`MethodMap` (`flightRecorder.h`) is `std::map<unsigned long, MethodInfo, ...>` —
one red-black-tree node individually `malloc`'d per distinct method, the same
shape of cost as `SBTable` chaining above but at a much smaller constant per
entry. Measured, not assumed:

- `sizeof(MethodInfo)` = 56 B, `sizeof(pair<const u64, MethodInfo>)` = 64 B.
- Actual `operator new` request per node = **96 B** (64 B pair + 32 B
  libstdc++ `_Rb_tree_node` bookkeeping — parent/left/right pointers + color).
  Confirmed via a standalone harness reading `NativeMem`'s own recorded byte
  count, then independently confirmed live: a debug-build mid-run dump logged
  `MethodMap: 54,762 methods after cleanup` via the pre-existing `TEST_LOG`
  (`flightRecorder.cpp:898`), and that exact chunk's
  `native_mem_live_bytes.method_map` was 5,257,152 B — **5,257,152 ÷ 54,762 =
  exactly 96.0**.
- Real glibc chunk footprint per node: 96 B usable-requested → glibc rounds to
  104 B usable → **112 B** including the chunk header. (An earlier internal
  note quoted "~165 B/entry" from dividing the 13.32 MiB chunk-flush figure
  above by 84,640 — a *different* experiment's touched-method count. At the
  confirmed 96 B/entry, that run must have held ~145,500 live methods, not
  84,640; the two numbers were never meant to be paired.)

**Flat/open-addressing alternative.** The keys (`jmethodID`/native addresses,
high 2 bits used for type tagging) aren't dense, so "flat" means a hash table,
not a literal indexed array — the same family as `StringDictionary`'s own
row/cell design. Per-slot cost would be `sizeof(u64) + sizeof(MethodInfo)` =
**64 B**, no per-entry allocation; with load-factor headroom (~65% target)
that's an effective **~98.5 B/entry** — barely different from the current
96 B *logical* figure. The case for doing it isn't the per-entry byte count;
it's structural:

1. **Chunk-header overhead paid once for the table, not once per node** —
   directly attacks the same "~650,000 extra live allocations, ~17% chunk
   inflation" mechanism as the RSS-delta reconciliation above.
2. **No fragmentation for this structure.** `MethodMap` survives across chunk
   rotations with continuous age-based pruning (`cleanupUnreferencedMethods`),
   so individually-freed rb-tree nodes scatter unreclaimable holes that
   compound across rotations — the same "free-but-held" mechanism from the
   RSS-delta reconciliation, but specific to this structure and specific to
   long-running, many-rotation deployments (a single-flush test like the one
   above can't show the compounding).
3. Fewer pointer-chases per lookup, and ~54,000+ fewer individual
   malloc/free calls — a secondary CPU benefit, not the memory story.

**Sizing it needs a growth strategy, not an upfront estimate.** Touched-method
count is workload-dependent and not predictable from loaded-class count (the
central finding of this whole document), so there's no reliable a-priori
size. Two precedents already exist in this codebase for the same class of
problem, pointing in opposite directions:

- **Follow:** `CallTraceHashTable` — fixed initial capacity, doubles at 75%
  fill. The right model for unknown-in-advance-count hash tables.
- **Avoid:** `SBTable`'s overflow chaining (above) — "grow by chaining a
  whole new large block" is the exact mechanism behind the 200 MB chunk-flush
  burst. A flat `MethodMap` must rehash-and-grow, not chain.

The one wrinkle `CallTraceHashTable` doesn't have: `MethodMap` deletes
continuously (age-based pruning), and plain open-addressing deletion is
broken (clearing a slot can sever another entry's probe chain). Two ways to
handle it: tombstones with a periodic full-rehash to reclaim them (new
complexity), or reuse `Profiler::rotateDictsAndRun()`'s existing
triple-buffer pattern (`profiler.h`) — rebuild the live table from the
currently-referenced set each cycle instead of erasing in place, avoiding the
tombstone problem by reusing an already-proven mechanism. That rebuild
cadence would also give a free, already-computed sizing signal for the next
cycle's table (size to ~1.3-1.5× the previous cycle's peak) even though no
upfront guess is possible for a session's first chunk.

Not yet implemented or measured end-to-end; this is a sized, honest
candidate, not a quick fix.

### Why a chunk cannot report its own serialization

`cpool_offset` is recorded in the chunk header as the boundary between the
event section and the constant pool, so no event may be appended once
`writeCpool()` has run — and `writeCpool()` is what builds the method map and
grows the dictionary. The counters are therefore necessarily sampled before
it. `native_mem_max_bytes` does eventually reflect the spike, since `record()`
raises the peak at allocation time and nothing resets it, but only one chunk
late and only as a lifetime maximum — after several flushes it can no longer
say which one was responsible.

`Recording::capturePostFlushNativeMem()` therefore snapshots per-category
`live` and `max` immediately after `writeCpool()`, and the following chunk
emits them as `native_mem_post_flush_live_bytes.<category>` and
`native_mem_post_flush_max_bytes.<category>` (absent from the first chunk).
The same point refreshes the JNI-visible `Counters::` mirrors, so a live
process reading `getDebugCounters0()` after a `dump()` sees post-serialization
values. Verified end to end and cross-checked against the direct memory read:

| category | in-chunk live | in-chunk max | post-flush live | post-flush max |
| --- | --- | --- | --- | --- |
| dictionary | 240.02 | 240.02 | **161.53** | **215.27** |
| calltrace | 27.95 | 59.96 | 27.95 | 59.96 |

Without these, the following chunk reports dictionary live and max both at
240.02 with no way to attribute the preceding spike.

`NativeMem::sample()` must **not** be called a second time per chunk to paper
over this: it advances a 64-tick moving-average window, so calling it twice
silently redefines `avg()` as a 32-chunk mean.

## Practical implications

1. **Thread count** (total distinct threads over the session, not peak
   concurrency) costs a confirmed ~824 B/thread inside the profiler — linear
   and predictable. This branch briefly cost ~296 KB/thread instead, via an
   unconditional `UnwindFailures` allocation in `ProfiledThread` that
   accounted for most of the observed ~400 KB/thread RSS growth; fixed by
   porting `origin/main`'s `e1de4cf08` (#734), which gates the class behind
   `#ifdef DEBUG` (see "Thread count" above for the before/after).
2. **Call-graph breadth drives the cost that matters, and the variable is
   distinct *methods* appearing in sampled stacks.** ~0 MB at 2,000 touched
   methods, ~102 MB at 150,000, at ~0.8–1.4 KB each. A workload with a narrow
   call graph stays cheap regardless of class count or thread count; a wide
   one does not. **This is the question to ask a customer before quoting a
   number.**
3. **Steady-state and flush costs are additive, not overlapping.** The
   per-touched-method number is sampled while the process runs, before any
   chunk write. A configuration that rotates JFR chunks pays the flush cost
   (~200 MB peak at N=150,000) *per rotation* on top. For the default
   single-continuous-recording mode it is paid once, at exit, with no effect
   on the running process.
4. **Don't read a flat `NM_DICTIONARY` in a single-chunk wall-clock session as
   "no class-name cost"** — the cost may simply not have been incurred yet.
   The new `native_mem_post_flush_*` counters make it visible from the second
   chunk onward.
5. **Roughly a fifth of the profiler's steady-state RSS cost is not
   attributable to any allocation site.** Chunk overhead on many small
   allocations (~17 % inflation at ~83 B mean) and unreclaimable arena slack
   are properties of using glibc malloc at this allocation profile, not bugs.
   Reducing allocation *count* would attack the first directly.
6. **`NM_CALLTRACE` overstates real memory by roughly 2×** — it reports
   virtual capacity, and its arena is sparsely resident. Sizing decisions
   using it should use residency.

## Open questions

- **~0.88 MiB of the profiler's own malloc is still unattributed**, of which
  3.64 MiB in 34 large allocations resolves only to the private `operator new`
  (the unwinder recovers most callers but not those). The two figures overlap;
  the residual is small and bounded either way.
- **The final chunk's own serialization is emitted nowhere** — there is no
  following chunk to carry the post-flush counters, so only the refreshed
  `Counters::` mirrors hold it, readable only before JVM teardown completes.
- ~~**The free-but-held arena term needs more reps** before its magnitude is
  quoted; its existence is established, its ~7.6 MiB mean is ~2.5σ.~~
  **Resolved 31 Aug 2026.** Magnitude on the dd-trace-doe workload is
  +22.86 ± 8.47 MiB (12 pairs) / +36.90 ± 7.72 (8 pairs), and residency measures
  1.0119 ± 0.0066 — the pages are resident. More reps will *not* tighten it: the
  term is intrinsically variable and is the sole source of the paired delta's
  variance, so reaching SE = 1 MiB would take ~873 pairs. Report it as a separate
  term rather than averaging it down.
- **`NM_CALLTRACE` is counted accurately but may not be sized appropriately** —
  48.5 MiB of capacity for ~19.9 MiB of resident use is a sizing question this
  document does not answer.
- **`StringDictionary`'s overflow chaining is the flush burst's mechanism and
  looks improvable** (6 KB per collision cluster; see "Chunk-flush cost"). Not
  an open *question* any more, but an open *opportunity*.
- **`NM_PERF` remains unverified in practice** (understood reason above); needs
  a host with relaxed `kptr_restrict`.
- **`allocs` is lightly calibrated** (two points — enough for the
  engine-difference and the plateau, not for its resize threshold), and
  **`nativemem=` was only smoke-tested**.
- **The `allocs` dictionary-insertion path is inferred from timing**, not
  traced to a call site, unlike the wall-clock path.
- **Java Heap's behavior under the jmethodID-preloading toggle is unresolved** —
  it moved *opposite* to expectation but swung ~240 MB across 5 reps of the
  same condition, too noisy to attribute.
- **How jmethodID preloading scales with methods-per-class is unresolved.** It
  fires per `ClassPrepare`, once per class, regardless of sampling, so on its
  own terms it should track total methods across all *loaded* classes rather
  than touched ones. A direct NMT check at 1 vs 5 methods per class was too
  noisy to answer.
- **Coverage fell from 93.6 % at N=2,000 to 56.4 % at N=150,000**, so
  duration/coverage is confounded with class count; durations tuned to hold
  coverage constant would separate them.
- **Single sandboxed Linux x86_64 container throughout.** Single-run figures
  should be treated more cautiously than the repeated-measures ones.
