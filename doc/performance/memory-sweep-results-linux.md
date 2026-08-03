# Native Memory Sweep — Empirical Results (Linux x86_64)

This is the empirical calibration pass for the model in
[memory-usage-model.md](memory-usage-model.md), run on Linux x86_64
(OpenJDK 21.0.10) against `libjavaProfiler.so` built from this checkout. It
measures process RSS and the PR #669 `NativeMem` per-category counters
(surfaced as `datadog.ProfilerCounter` JFR events named `native_mem_*`)
across synthetic workloads that sweep four dimensions independently: thread
count, call-trace diversity, class/method diversity, and allocation
diversity. A companion pass on macOS arm64 exists in
[memory-sweep-results.md](memory-sweep-results.md); differences between the
two platforms are called out inline where they matter.

**Headline results:**
1. **Thread count has a real, measurable native-memory cost inside the
   profiler**, cleanly linear at ~824 bytes/thread (`sizeof(ProfiledThread)`)
   once measured correctly — see the methodology note below on *why*
   "correctly" matters here. JVM/OS-level thread overhead (stacks, kernel
   bookkeeping) dominates total RSS growth by roughly 3–4x on top of that.
2. **Call-trace shape diversity drives real, steppy growth** in the
   call-trace hash table, doubling in a single clean jump once ~49,152
   distinct shapes are recorded — confirmed both via direct method-call
   diversity (`traces` mode) and via class diversity under wall-clock
   sampling (`classes` mode), which produces distinct call-trace shapes as a
   side effect of sampling different callees.
3. **CORRECTED (see below): `NM_DICTIONARY`'s "flat" reading under wall-clock
   sampling throughout this document was a measurement artifact, not a real
   finding.** An earlier version of this document claimed
   `Lookup::resolveMethod` — the function that inserts class names during
   `writeStackTraces` — was dead code for wall-clock dumps on this build.
   That was wrong. It's confirmed (GDB breakpoint, an independent
   allocation-tracking tool, and the profiler's own source comment at
   `flightRecorder.cpp:819–826`) that this function **does** run, but the
   `NM_*` counters are snapshotted into the JFR chunk *before*
   `writeCpool()`/`writeStackTraces()` executes — so growth from a chunk's
   own dump-time symbolication is, by design, only visible in a *subsequent*
   chunk's reading. Every measurement in this document used single-chunk
   runs, which structurally cannot observe this. Two-chunk tests (forcing
   an intermediate dump mid-run, varying how much workload ran before the
   dump) confirm real, substantial growth: `NM_DICTIONARY` read ~143 MiB
   after a 90s pre-dump run and ~236 MiB after a 177s pre-dump run (both
   out of a 180s total), vs. the usual ~4.55 MiB baseline. The ~236 MiB
   reading reproduces tightly across two independent reps (236.5 MiB and
   235.3 MiB, a ~0.5% spread) — so the *difference between the two
   durations* is not run-to-run noise, it's a real, repeatable effect of
   how much sampled call-trace/method-resolution backlog has accumulated by
   the time of the forced dump (more pre-dump runtime → bigger backlog →
   bigger jump in the next chunk). **Treat "large, real, reproducible for a
   given test construction, and construction-dependent" as the confirmed
   finding** — the relationship between either specific number and a
   normal, unmodified single-chunk run's *actual* internal growth still
   isn't independently established, since both come from a methodology that
   deliberately perturbs the system (forcing an extra `dump()` call); see
   the dedicated section below for why. **This is a real, separate, additive
   cost — but it is *not* part of the "unattributed ~32–42 MB" steady-state
   gap reported elsewhere in this document; see point 8, which corrects an
   earlier version of this document that conflated the two.**
4. **The CPU-sampling engine (`cpu=`) works on Linux** (it doesn't
   initialize on this project's current macOS build) and produces real
   samples, but its associated `NM_PERF` counter requires a kernel-symbol
   capability (`kptr_restrict=0`) this test environment doesn't have — a
   documented, environment-specific gate rather than an open question.
5. **RSS, NMT, and the profiler's own counters each see a different slice of
   the picture, and none of them is complete on its own.** For thread-count
   growth specifically, only ~25–27% of the RSS delta per thread is
   explained by NMT's own accounting; the profiler's own tracked structures
   account for a small fraction of a percent (824 B against a ~400 KB/thread
   RSS delta); the rest is OS/kernel thread bookkeeping neither instruments.
6. **Running the identical thread-count workload with and without the agent
   attached shows the profiler's own RSS overhead is a small, roughly flat
   few-MB baseline cost (3.5–10 MB across 1–1000 threads), not a per-thread
   multiplier** — the ~400 KB/thread RSS growth analyzed under point 1 above
   happens almost identically with or without the agent, confirming it's
   JVM/OS thread machinery rather than something the profiler introduces.
   **This "small and flat" result is specific to thread count in a workload
   with no class/call-trace diversity — see point 7.**
7. **For class/call-trace diversity, the profiler's own RSS overhead is
   substantial and not flat at all.** A dedicated 80-run sweep (10 reps ×
   with/without-agent × 4 class-count values, needed because an initial
   2–3-rep attempt at N=150,000 gave estimates anywhere from 91–246 MB
   depending on which runs got paired) found profiler-attributable RSS
   overhead of essentially 0 at 2,000 classes, ~22 MB at 20,000, ~40 MB at
   60,000, and ~102 MB at 150,000 — growing roughly linearly with the number
   of classes *actually appearing in sampled stacks* (not raw class count),
   at a fairly consistent ~1–1.4 KB per sampled class. This is not the
   `NM_CALLTRACE` hash table's own step-function resize (confirmed a smaller,
   15–25 MB piece of the total) — most of the overhead scales continuously
   with call-graph/class diversity actually touched by sampling, and grows
   noisier at scale (±89 MB stdev at N=150,000, comparable to the mean
   itself). NMT category attribution explains 44% of it, and a toggle test
   confirmed jmethodID preloading (`JVMTI_EVENT_CLASS_PREPARE` →
   `GetClassMethods`, `jvmSupport.cpp:145`) as the driver of 79% of that
   NMT-visible share (Class/Internal/NMT's-own-overhead all collapse to
   noise when preloading is disabled) — "Java Heap" remains unexplained,
   its own measurement too noisy at practical rep counts to attribute
   either way. The remaining ~32–42 MB was, in an earlier version of this
   document, reported as invisible to both NMT and this profiler's own
   `NM_*` counters, with `MethodMap`/`MethodInfo` "ruled out" as a
   candidate. **The "ruled out" conclusion rested on a wrong premise (see
   point 3) and is superseded — `MethodMap`/`NM_DICTIONARY` growth is real
   and confirmed. But it does *not* explain this remaining ~32–42 MB.** A
   still more recent correction (point 8) shows that growth mechanism is
   gated behind `finishChunk()`, which — absent an explicit `dump()` call —
   fires exactly once, at process shutdown, strictly *after* this sweep's
   RSS sample is taken. The remaining ~32–42 MB stays unexplained; see
   point 8 for the full account and why the two lines of investigation
   don't connect the way an earlier version of this document claimed.
8. **CORRECTED: the chunk-flush dictionary burst (point 3) and the ~32–42 MB
   steady-state gap (point 7) are two separate, real phenomena — the burst
   does not explain the gap.** Direct RSS instrumentation around the forced
   `dump()` call in the clean two-chunk test shows a real, physical RSS
   jump of ~213 MiB (VmRSS and Private_Dirty agree exactly) at the moment
   `dump()` is called, closely matching `NM_DICTIONARY`'s own ~230 MiB
   counter delta in the same run — conclusive confirmation the growth is
   real memory, not a counter-accounting artifact. But `finishChunk()` —
   the function that gates all of this growth — has exactly two call sites
   in the source: `Recording::~Recording()` (destructor, run at VM
   shutdown) and `Recording::switchChunk()`, called only from
   `FlightRecorder::dump()`. There is no periodic/automatic mid-run
   rotation. So in a standard run with no explicit `dump()` call,
   `finishChunk()` fires exactly once, at process shutdown — and the
   sweep's RSS sample (taken ~1 second *before* the workload loop even
   finishes, via `run_repeated_sweep.sh`'s `launch_epoch +
   (DURATION_MS - 1000)/1000` timing) is structurally taken *before* that
   single event ever occurs. The dictionary-growth mechanism therefore
   contributed nothing to the ~102 MB steady-state number or its ~32–42 MB
   unattributed remainder — not "a small piece," literally zero, because it
   hadn't happened yet at sample time. The same logic reattributes the
   LD_PRELOAD allocation shim's ~189 MB finding: its report is written via
   `atexit()`, which fires *after* VM shutdown (and thus after
   `~Recording()`'s `finishChunk()`) has already run, so it was also
   capturing the chunk-flush burst, not steady-state growth — corroboration
   of the burst's magnitude, not independent evidence about the gap. **Net
   result: there are two confirmed, real, additive overhead components at
   high class diversity — a ~102 MB steady-state cost (of which ~32–42 MB
   remains unattributed) paid continuously while the process runs, and a
   separate ~210–230 MB chunk-flush burst paid once per JFR chunk rotation
   (`dump()` or process exit) — and explaining one does not explain the
   other.** The steady-state gap needs a fresh hypothesis, untouched by
   anything found via the two-chunk-test/dump-burst line of investigation.
9. **The allocation shim, retimed to sample at steady state instead of
   `atexit()`, mostly re-discovered already-explained costs rather than
   explaining the ~32–42 MB gap.** Its steady-state total (~35.7 MB)
   dominant site (~24.6 MB) resolves to `JVMSupport::loadMethodIDsImpl` —
   verified, after ruling out a suspicious all-`nil` backtrace as an
   artifact, to be a real, multi-frame allocation chain through
   `jvmti->GetClassMethods()`. But that's the identical call disabled by
   the toggle test that already measured jmethodID preloading's ~35.9 MB
   NMT-visible share (`loadMethodIDsIfNeeded`, which the toggle patches,
   is what calls `loadMethodIDsImpl`) — since NMT tracks the same
   underlying `malloc` path this shim intercepts, these are most likely
   the same bytes measured twice, not additive. See the dedicated section
   above for the full account. The gap remains open; this rules out
   "additional profiler-`.so`-attributed allocation" as its likely source.
10. **Two more candidates for the ~32–42 MB gap ruled out: glibc allocator
    fragmentation, and JIT code-cache growth.** A 5-rep `mallinfo2()`
    comparison (steady-state timed, deliberately avoiding the earlier
    shim's own large static tables) shows the "invisible to allocation
    tracking" glibc overhead is consistently *smaller* with the agent
    attached, not larger (mean −15.7 MiB, tight across reps) — ruling out
    fragmentation. It did surface a clean, independent number though: total
    `malloc`-visible growth of ~82.0 MiB (±3.2 MiB), about 20 MB less than
    the established ~102 MB RSS delta. The obvious candidate for that 20 MB
    — HotSpot's `CodeCache`, `mmap`'d outside glibc's arenas entirely — is
    also ruled out: NMT's `Code` category grows by an essentially identical
    ~163 MB with and without the agent across all 10 existing sweep reps
    (mean delta −0.6 MiB), confirming it's workload-driven JIT warmup, not
    an agent cost. See the dedicated section above. The gap, and the
    smaller ~20 MB `malloc`-vs-RSS residual, both remain open.

## Harness

Standalone Java programs run per sweep point with
`-agentpath:libjavaProfiler.so=start,<engine>,jfr,file=<out>,cstack=fp`.
Everything needed is under `doc/performance/memsweep/` in this checkout:

```
memsweep/
├── src/
│   ├── MemSweepMain.java          # threads / traces / classes / allocs workloads
│   ├── GenSources.java            # writes .java sources for traces/classes/allocs,
│   │                              # compiled externally
│   └── LiveThreadLocalSweep.java  # dedicated thread-count-only program, see below
├── run_sweep.sh                   # one sweep point -> CSV line with RSS + NM_* counters
├── run_threadlocal_live.sh        # thread-count-only, reads NM_THREAD_LOCAL live
├── run_nmt.sh                     # one sweep point with JVM Native Memory Tracking
├── run_repeated_sweep.sh          # repeated-measures with/without-agent comparison, see below
└── extract.py                     # parses `jfr print --json` output for native_mem_* counters
```

Four independent workload modes, each isolating one dimension:

- **`threads N`** — spawns N daemon threads, each busy-looping
  (`Math.sqrt`) for the run duration. Driven by the wall-clock engine
  (`wall=<interval>`).
- **`traces N`** — one thread, one precompiled class with N distinct static
  methods, invoked in a cycle via reflection. Isolates call-trace shape
  diversity from class-loading (still 1 class). Wall-clock engine.
- **`classes N`** — one thread, N distinct precompiled classes each with one
  method, invoked in a cycle via reflection. Isolates class/method diversity
  from call-trace shape variety (same call site each time). Wall-clock
  engine.
- **`allocs N`** — one thread, N distinct precompiled short-lived object
  shapes (varying field count, so each is a genuinely different allocation
  size), allocated and discarded in a cycle. Driven by the allocation-
  sampling engine (`memory=<interval>:a`) instead of wall-clock, since none
  of the other three modes allocate any Java objects.

Classes/methods for `traces`/`classes`/`allocs` are precompiled by an
**external, unprofiled `javac` process** before the profiled JVM starts —
compiling in-process would load the JDK's own compiler classes into the
profiled JVM and swamp the intended N-classes signal.

**Every sampled thread must call `JavaProfiler.addThread()` explicitly** for
wall-clock sampling to produce any `datadog.MethodSample` events for it —
confirmed on Linux as well as macOS. A build/config with `-agentpath` alone,
no explicit registration, produces zero samples for any thread (including
the main thread) despite `datadog.WallClockSamplingEpoch` events showing the
sampler running on schedule. This is very likely intentional behavior for
this fork (every profiling consumer is expected to register its own
threads — check how dd-trace-java integrates this) rather than a platform-
specific auto-registration gap; the harness's `MemSweepMain` calls
`addThread()` from the main thread and every spawned worker.

**All `NM_*` counters share the same underlying mechanism (`nativeMem.h`,
PR #669), and reading them correctly means understanding it, not treating
them as simple monotonic high-water marks:** each category is a **live
gauge** — `NativeMem::record(category, delta)` does a relaxed atomic add on
every allocation (`delta > 0`) or free (`delta < 0`) — plus a precisely
tracked running peak (`_max`, updated at allocation time so a peak that
rises and falls between reads is still captured) and a moving-window average
over the last 64 `sample()` ticks. All three (`live`, `avg`, `max`) are
written per category into the JFR file as separate
`native_mem_{live,avg,max}_bytes.<category>` fields; this document's
`extract.py` only pulls the `live` field for brevity, which is a fine choice
for a category that never sees a `record()` with a negative delta during a
short single-chunk run (true for `NM_CALLTRACE`/`NM_THREAD_FILTER`/
`NM_NATIVE_SYMBOLS`/etc. here, since nothing in these workloads triggers a
chunk free or hash-table reset mid-run) — but it is the *wrong* field for a
category that does see frees during the run.

`NM_THREAD_LOCAL` is exactly that case: it's incremented when a thread's
`ProfiledThread` is allocated and decremented by a pthread TLS destructor as
soon as that thread exits (`threadLocalData.cpp`). A workload that spawns N
threads and joins all of them before the process exits — like `threads N`
above — has already freed nearly every one of those N `ProfiledThread`
structures by the time the JFR chunk (and its counter snapshot) is written
at exit. Reading the live field the same way as the other counters then
shows only whatever handful of long-lived JVM-internal threads happened to
still have one at that instant — not N, and not a value that means anything
about the workload. (The precise per-category `max` field would, in
principle, capture the true peak here too, since `_max` updates at
allocation time regardless of later frees — but rather than rely on reading
a different field correctly, `LiveThreadLocalSweep.java` /
`run_threadlocal_live.sh` sidestep the question entirely.)

`LiveThreadLocalSweep.java` / `run_threadlocal_live.sh` measure this
dimension correctly instead: they spawn N threads, wait for all of them to
register via `addThread()`, then call the public `JavaProfiler.dump(Path)`
API to force a JFR chunk write **while all N are still alive and
busy-looping**, and read the (still-live-at-that-instant) counter from that
snapshot. This is the measurement used in the thread-count results below.

## Results: thread count

| N threads | max RSS | `NM_THREAD_LOCAL` (live, all N alive) | `NM_THREAD_FILTER` |
|---|---|---|---|
| 1 | 70 MiB | 6,592 B | 40 KiB |
| 4 | 71 MiB | 9,064 B | 40 KiB |
| 16 | 76 MiB | 18,952 B | 40 KiB |
| 64 | 99 MiB | 68,392 B | 40 KiB |
| 256 | 172 MiB | 226,600 B | **72 KiB** |
| 1000 | 442 MiB | 839,656 B | **136 KiB** |

`NM_CALLTRACE` (24.5 MiB), `NM_DICTIONARY` (4.55 MiB), and
`NM_NATIVE_SYMBOLS` (11.9 MiB) are bit-for-bit flat across the entire sweep —
this workload has no call-trace or class-name diversity, so these structures
never leave their initial capacity. `NM_THREAD_FILTER`'s staircase (40→72→136
KiB, stepping at the 256-slot chunk boundaries) is the one high-water-mark
counter that does respond to thread count, independent of the
live/cumulative distinction discussed above.

**`NM_THREAD_LOCAL` scales cleanly and linearly**: the per-thread delta is
824.0 bytes/thread between every pair of sweep points except 16→64 (1,030
B/thread — plausibly a JVM-internal thread, e.g. a JIT compiler thread,
picking up a `ProfiledThread` of its own around that point, adding transient
noise on top of the linear term). 824 B/thread lines up well with
`sizeof(ProfiledThread)` — the struct's OTel context record alone is ~688
bytes per its own layout comment in `threadLocalData.h`, plus the preceding
scalar fields and vtable pointer — and is close to memory-usage-model.md's
independent ~650B/thread estimate from reading the struct layout directly.

**RSS scales far faster than the profiler's own accounting**: ~70 MiB at 1
thread to 442 MiB at 1000, or ~381 KB/thread average — about 460x the
profiler's own 824 B/thread contribution. The "reconciliation" section below
breaks down how much of that gap NMT can explain.

## Results: call-trace shape diversity (`traces`)

| N methods | duration / interval | max RSS | `NM_CALLTRACE` | `NM_DICTIONARY` |
|---|---|---|---|---|
| 2,000 | 10s / `wall=~5ms` | 426 MiB | 24.5 MiB (baseline) | 4.55 MiB (baseline) |
| 60,000 | 100s / `wall=~1ms` | 776 MiB | **40.5 MiB** | 4.55 MiB (baseline) |

The call-trace hash table (`callTraceHashTable.cpp`) starts at 65,536 slots
and doubles once load crosses 75% — i.e. once ≥49,152 distinct call-trace
shapes have actually been recorded (not just how many candidate methods
exist; coverage is bounded by how many of them a sample actually lands on).
2,000 methods stays well under that threshold and leaves the table flat; the
60,000-method run, sampled fast and long enough to generate ~93,000 samples
(duration/interval), crosses it and the table doubles to exactly
**42,469,888 bytes — matching the confirmed-growth value from the macOS pass
exactly**, byte for byte, which is expected: this is a machine-independent
struct-capacity jump, not something that should vary by platform. `NM_DICTIONARY`
stays flat in both rows, as expected — this workload has only 1 loaded class.

RSS is markedly higher here than in the `threads` sweep at comparable
duration (426–776 MiB vs. 70–442 MiB) — reflection-based invocation of many
distinct methods drives the JDK's own method-accessor bytecode generation
and JIT compilation harder than a plain busy loop, inflating Metaspace/code
cache usage. This is workload-shape overhead from the *test harness's* use
of reflection, not something attributable to the profiler.

## Results: class/method diversity (`classes`)

| N classes | duration / interval | max RSS | `NM_CALLTRACE` | `NM_DICTIONARY` |
|---|---|---|---|---|
| 2,000 | 10s / `wall=~5ms` | 417 MiB | 24.5 MiB (baseline) | 4.55 MiB (baseline) |
| 150,000 | 180s / `wall=~1ms` | 2.2 GiB | **48.5 MiB** | 4.55 MiB (baseline) |

`NM_CALLTRACE` doubles here too, for the same reason as the `traces` sweep:
each class's method appears as a distinct callee frame, so N distinct
classes produce (up to) N distinct call-trace shapes even though the call
*site* invoking them is the same one line of harness code each time.

**`NM_DICTIONARY` does not move at all in any single-chunk reading, even at
150,000 distinct classes over 180 seconds — but this is a measurement
artifact, not real profiler behavior, and the growth it's not showing is
large.**

An earlier version of this document concluded the opposite: that the code
path inserting class names (`Recording::writeStackTraces()` →
`Lookup::resolveMethod()` → `Lookup::fillJavaMethodInfo()` →
`_classes->lookupDuringDump()`, `flightRecorder.cpp`) was dead code for
wall-clock `MethodSample` dumps on this build, based on a temporary log line
at the top of `resolveMethod()` that fired zero times. That conclusion was
wrong, uncovered while investigating a related question (sizing `MethodMap`,
see below) and confirmed three independent ways:

1. **A GDB breakpoint on `Lookup::resolveMethod`** hit immediately on the
   very same kind of run that supposedly showed zero calls, with a full,
   sensible backtrace: `Recording::~Recording()` → `finishChunk()` →
   `writeCpool()` → `writeStackTraces()` → `Profiler::processCallTraces()` →
   `CallTraceStorage::processTraces()` → the `writeStackTraces` lambda →
   `Lookup::resolveMethod`.
2. **An independent LD_PRELOAD allocation-tracking tool** (built specifically
   for this investigation, see the RSS-reconciliation section below) showed
   real, substantial live memory attributed to exactly this call chain,
   ending in `StringDictionaryBuffer::insert_with_id` — the arena-allocating
   function that actually grows the dictionary.
3. **The profiler's own source comment explains why**, right above the code
   that snapshots `NM_*` counters into the JFR chunk (`flightRecorder.cpp:819–826`):

   > this will not report correct counts for any counters updated during
   > writing the constant pool... Some counters we verify to balance (e.g.
   > the anonymous dictionaries) will be reported as positive, others (e.g.
   > **the classes dictionary**) will reflect the previous serialization.

   `updateNativeMemStats()` / `writeCounters()` / `writeNativeMem()` run
   *before* `writeCpool()` (which calls `writeStackTraces` →
   `resolveMethod`) within `finishChunk()`. Growth from a chunk's own
   dump-time class-name insertions is written into the chunk, but the
   counter snapshot describing that growth was already taken and written
   moments earlier — it shows up only in a *subsequent* chunk's counter
   reading. **Every measurement in this document, and the entire premise of
   reading "the last `ProfilerCounter` event in a short single-chunk run,"
   is structurally blind to this** — not because of scale, sample count, or
   an instrumentation gap, but because a single-chunk run has no subsequent
   chunk to reveal it in.

**Two-chunk tests confirm real, large growth that depends on test
construction, not run-to-run noise.** Each forces an intermediate
`profiler.dump()` during a `classes 150000` run, then reads the *final*
chunk (written normally at process exit):

| Test | Workload before the forced dump | `NM_DICTIONARY` in the dump chunk | `NM_DICTIONARY` in the final chunk |
|---|---|---|---|
| Split evenly | 90s of 180s total | 4,774,032 B (baseline) | 149,876,928 B (~143 MiB) |
| Dump near the end, rep 1 | 177s of 180s total | 4,774,032 B (baseline) | 247,996,656 B (~236.5 MiB) |
| Dump near the end, rep 2 | 177s of 180s total | 4,774,032 B (baseline) | 246,798,576 B (~235.3 MiB) |

The two "dump near the end" reps agree to within ~0.5% (236.5 vs. 235.3
MiB) — including an *identical* dump-chunk baseline (4,774,032 B) across
all three runs, split-evenly included. That rules out ordinary run-to-run
noise as the explanation for the gap between the two test constructions:
the ~93 MiB difference between the 90s-pre-dump and 177s-pre-dump results
is a real, repeatable function of how much workload ran before the forced
dump, not measurement jitter. This confirms the same qualitative point
unambiguously: wall-clock sampling's class-name dictionary growth is real
and substantial — comparable to or larger than `NM_CALLTRACE`'s own growth,
not zero — and it scales with how much workload ran before the dump (177s
of accumulated class touches produced more growth than 90s), consistent
with the mechanism being real insertions rather than a fixed artifact of
forcing a dump at all. **But no single one of these numbers should be read
as "the size of the gap."** All three come from a methodology that itself
perturbs the system (an explicit `dump()` call the standard single-chunk
runs never make), and all are larger — in the "dump near the end" case,
over twice as large — than the entire ~102 MB RSS delta this whole
investigation has been trying to explain. Raw string content for 150,000
short class names is only on the order of ~2 MB, so something beyond
simple string storage is inflating this — plausibly per-thread or
per-shard `StringDictionaryBuffer` copies of the same names accumulating
before consolidation into the shared arena (mentioned as a hypothesis in
the very first version of this investigation, never confirmed), with the
accumulated *volume of unresolved stack-trace/method backlog at the moment
of the dump* — not elapsed time itself — the likely driver, since the
177s-pre-dump test showed more growth than the 90s one despite a much
shorter post-dump tail (3s vs. 90s) before the final chunk was written.
This wasn't traced further. Treat the *existence, substantial size, and
reproducibility-per-construction* of wall-clock dictionary growth as
solidly confirmed; treat its *precise magnitude under normal, unperturbed
conditions* as still an open question this specific methodology cannot
answer, since observing it at all requires the perturbation.

**A second, independent finding fell out of the same test: call-trace
storage resets across a chunk rotation; the dictionary's content persists
across it.** In the "dump near the end" test, `NM_CALLTRACE` was
50,858,496 B (grown/doubled) in the dump chunk, but read back down to
25,692,672 B — the *initial* baseline capacity — in the final chunk, just
3 seconds later, despite the workload continuing to sample the same 150,000
classes throughout. The dictionary shows the opposite pattern: its growth
from the dump chunk *carries forward* into the final chunk's reading (that
is precisely the "one chunk late" mechanism above). This is a genuinely
different lifetime for the two structures across chunk rotation, worth
knowing for any long-running production process with periodic JFR chunk
rotation: **call-trace memory is bounded per rotation window** (each
rotation effectively restarts the hash table), while **class-name
dictionary memory can accumulate across rotations**, up to its
`MAX_CLASS_MAP_SIZE` cap (`profiler.h`, 262,144 entries). This wasn't
independently verified beyond this one test and isn't otherwise documented
here — worth confirming with a dedicated, purpose-built test rather than
treating it as settled from a single observation.

The next section's `allocs`-vs-`classes` comparison remains a valid, separate finding (allocation sampling's dictionary
insertion is visible *immediately*, within the same chunk, while
wall-clock's is real but deferred by one chunk) — only the explanation for
*why* wall-clock's didn't show up immediately has changed, from "dead code"
to "correctly deferred, and this document's methodology never looked at a
second chunk."

## Results: allocation diversity (`allocs`)

Neither of the two modes above allocates a single Java object, so they say
nothing about the allocation-sampling engine (`memory=<interval>[:a]`) or
about how `NM_DICTIONARY` behaves when it's driven by that engine instead of
wall-clock sampling. The `allocs` mode fills that gap:

| N object shapes | duration / interval | max RSS | `NM_CALLTRACE` | `NM_DICTIONARY` | distinct shapes sampled |
|---|---|---|---|---|---|
| 2,000 | 15s / `memory=512:a` | 717 MiB | 24.5 MiB (baseline) | **6.04 MiB** | 1,115 / 2,000 |
| 20,000 | 60s / `memory=256:a` | 680 MiB | 24.5 MiB (baseline) | 6.03 MiB | — |

**Allocation sampling moves `NM_DICTIONARY` at 2,000 distinct shapes, and —
unlike wall-clock sampling — shows it in the *same* chunk it happened in.**
Confirmed with a same-machine, same-N, same-duration A/B against `classes`
mode (4.55 MiB flat there vs. 6.04 MiB here). Given the previous section's
finding, this isn't "allocation sampling grows the dictionary and wall-clock
sampling doesn't" — wall-clock sampling grows it too, substantially, per the
two-chunk test above. The real, narrower difference is *when* the growth
becomes externally visible: allocation sampling's `ObjectSample` path
apparently interns the sampled object's class at *sample* time (immediately
reflected in that same chunk's counter reading), while wall-clock's
`MethodSample` symbolication happens at *dump* time, one chunk later,
inside `writeCpool()`, after the counter snapshot for that chunk was
already taken. This wasn't traced to allocation sampling's specific
insertion call site to confirm the "sample time" half of that explanation
directly — it's inferred from the timing behavior being the opposite of
wall-clock's confirmed mechanism, not independently verified the way the
wall-clock side now is.

Growth here also matches the step-function model from the `traces` sweep:
the 2,000-shape and 20,000-shape runs land at essentially the same value
(6.04 vs. 6.03 MiB) — one arena-chunk threshold was crossed somewhere below
2,000 shapes, and neither run went far enough to cross the next one. This is
consistent with "hash-table/arena memory is a step function of
threshold-crossings, not a smooth function of unique-entry count," the same
pattern the `traces` sweep showed for `NM_CALLTRACE`.

`nativemem=<bytes>` (native `malloc` tracing, a distinct feature from the
always-on `NM_*` self-accounting) was smoke-tested against the
non-allocating `threads` workload and confirmed to initialize and produce
real `datadog.NativeMemoryAllocation` events from generic JVM-internal
`malloc` traffic, but no dedicated native-malloc-heavy workload (e.g. a
`DirectByteBuffer.allocateDirect()` loop) was built to characterize it the
way `allocs` characterizes `memory=` — left as further harness work.

## Results: CPU-sampling engine and `NM_PERF`

`cpu=10ms` initializes successfully here — worth noting since it fails
outright (`Agent_OnLoad` error) on the macOS build used for the companion
pass — and produces real samples: 158 `datadog.ExecutionSample` events over
an 8s/16-thread run. All `NM_*` counters other than `NM_PERF` behave
identically to the wall-clock runs above, as expected (they don't depend on
which sampling engine is active).

`NM_PERF` itself reads 0 here, and this environment doesn't allow verifying
whether it would move under load — but the reason is understood precisely,
from source, rather than left as an open question:

```
// perfEvents_linux.cpp:874 — silently downgrades if kernel symbols aren't readable
if ((_ring & RING_KERNEL) && !Symbols::haveKernelSymbols()) { _ring = RING_USER; }
// perfEvents_linux.cpp:885 — with cstack=fp and RING_USER, this evaluates false
_use_mmap_page = _cstack != CSTACK_NO &&
                 (_ring != RING_USER || _cstack == CSTACK_DEFAULT || _cstack == CSTACK_LBR);
// perfEvents_linux.cpp:678 — NM_PERF is only recorded when a page was actually mapped
if (page != NULL) { NativeMem::record(NM_PERF, (long long)(2 * OS::page_size)); }
```

`NM_PERF` only increments when a kernel-ring mmap page is allocated per
registered thread, which requires both `RING_KERNEL` and working kernel
symbol resolution. This sandboxed test container has `kptr_restrict=1`
(`/proc/kallsyms` addresses read as zero for non-root), so the code falls
back to `RING_USER`, which combined with `cstack=fp` disables the mmap page
entirely — independent of sample rate or thread count. `perf_event_open`
itself still succeeds and real samples are recorded via the signal-delivery
path, which is why `ExecutionSample` events show up normally despite this.
**This is a host/container permission gate (would need root and
`kernel.kptr_restrict=0` to lift), not a profiler bug** — anyone re-running
this on a bare-metal or VM Linux host with relaxed kernel-symbol
restrictions should check `NM_PERF` again; the code path looks correct and
just isn't exercisable here.

## Results: reconciling RSS with NMT and the profiler's own counters

Three lenses, each blind to a different region of memory:

| | Tracks | Blind to |
|---|---|---|
| NMT (`jcmd VM.native_memory`) | HotSpot-internal: thread stacks, GC, class metadata, code cache, compiler arenas | The profiler agent's own allocations (`malloc`/`new`, which NMT doesn't instrument) |
| `NM_*` counters | The profiler's own tracked structures (call-trace storage, dictionaries, thread-filter, ...) | Everything on the JVM's side |
| Raw process RSS | Everything, as one number | Attribution — doesn't say *why* |

This profiler's JFR writer builds the chunk binary format entirely by hand
(`flightRecorder.cpp`) and does not call into, share memory with, or
coordinate with HotSpot's built-in `-XX:+FlightRecorder` engine at all — the
two recording systems are fully independent, so running this agent adds no
load to HotSpot's own JFR subsystem, and none of its own allocations are
visible to NMT.

`jcmd` attach was reliable here with the agent attached even at 1000
threads, so — unlike the macOS pass, which had to fall back to separate
agent-free control runs because `jcmd` attach became unreliable there at
256+ threads — NMT and RSS were sampled in the *same* process, mid-run, with
the agent active:

| N threads | NMT "Thread" committed | Process RSS | RSS Δ from N=1 | NMT Thread Δ/thread | RSS Δ/thread | % of RSS Δ explained |
|---|---|---|---|---|---|---|
| 1 | 966 KB | 72,248 KB | — | — | — | — |
| 256 | 28,512 KB | 177,000 KB | +104,752 KB | 108.1 KB | 410.8 KB | 26.3% |
| 1000 | 91,528 KB | 457,416 KB | +385,168 KB | 90.7 KB | 385.6 KB | 23.5% |

Total NMT `committed` across *all* categories (not just "Thread") explains
almost exactly the same fraction (26.9% at both N) — other categories barely
move with thread count, so nearly all of NMT's thread-scaling signal lives
in the Thread bucket alone. Combined with the profiler's own accounting
(824 B/thread, a rounding error against a ~400 KB/thread RSS delta): **roughly
three-quarters of the per-thread RSS growth here is invisible to both NMT
and the profiler's own instrumentation** — almost certainly OS/kernel-level
per-thread bookkeeping (pthread structures, stack guard pages, kernel task
scheduling structures) outside either's reach. The macOS pass found a
similar picture with a smaller explained fraction (~17–20%, vs. ~24–27%
here) — same conclusion, different exact split, plausibly reflecting
platform differences in kernel-level thread bookkeeping rather than
anything specific to this profiler.

### Isolating what the profiler itself adds: thread count

The table above shows how much of the *thread-count-driven* RSS growth NMT
can explain, but it doesn't by itself separate "cost of running N threads in
this JVM" from "cost the profiler adds on top of that same JVM." Those are
different questions — the agent's own JFR writer, its wall-clock sampler
thread, and its per-thread signal-handling setup are all overhead the JVM
wouldn't otherwise pay, and NMT can see *some* of that (e.g. if the agent's
activity perturbs HotSpot's own bookkeeping) even though it can't see the
agent's own `malloc`/`new` allocations directly. Isolating it means running
the *identical* workload twice, agent attached vs. not, and taking the
difference — which is what `run_nmt.sh`'s `--no-agent` flag is for:

| N threads | RSS, agent | RSS, no agent | RSS Δ (profiler cost) | NMT Thread, agent | NMT Thread, no agent | NMT Thread Δ | NMT total, agent | NMT total, no agent | NMT total Δ |
|---|---|---|---|---|---|---|---|---|---|
| 1 | 72,248 KB | 68,748 KB | +3,500 KB | 966 KB | 961 KB | +5 KB | 1,106,757 KB | 1,106,348 KB | +409 KB |
| 256 | 177,000 KB | 168,924 KB | +8,076 KB | 28,512 KB | 28,587 KB | −75 KB | 1,134,910 KB | 1,134,599 KB | +311 KB |
| 1000 | 457,416 KB | 447,288 KB | +10,128 KB | 91,528 KB | 90,431 KB | +1,097 KB | 1,210,526 KB | 1,208,958 KB | +1,568 KB |

**The profiler's RSS overhead here is a roughly flat few-MB baseline cost
(3.5–10 MB across this range), not a strong per-thread multiplier** — it
grows mildly with N (consistent with the agent's own housekeeping threads
and per-thread signal setup costing a little more as N grows) but nowhere
near proportionally; the bulk of the thread-count-driven RSS growth analyzed
above happens with or without the agent attached, confirming it's
overwhelmingly a JVM/OS cost rather than something the profiler introduces.
**NMT's own "Thread" bucket shows no consistent agent effect at all** — the
deltas (+5, −75, +1097 KB) are within run-to-run noise, meaning the agent
does not measurably inflate HotSpot's own thread-stack accounting (expected:
wall-clock sampling piggybacks on existing application threads rather than
spawning one dedicated OS thread per profiled thread). NMT's *total*
committed does show a small, mildly N-dependent increase attributable to the
agent (409 KB → 1,568 KB from N=1 to N=1000) — plausibly safepoint,
synchronization, or internal bookkeeping categories responding to the
additional signal traffic from wall-clock sampling, though this wasn't
broken down by category. **None of this changes the top-line conclusion**:
the profiler's own footprint (whether measured via `NM_*`, this with/without
delta, or NMT) is a small, mostly-fixed cost; the ~400 KB/thread RSS growth
analyzed above is JVM/OS thread machinery the profiler neither causes nor
can see into. **This conclusion is specific to thread count with no other
diversity in the workload** — the next section shows it does not extend to
class/call-trace diversity, where the profiler's own overhead is substantial
and scales with the workload rather than being a small fixed cost.

### Isolating what the profiler itself adds: class diversity

The thread-count result above invites a natural but wrong generalization —
"the profiler's RSS overhead is basically flat regardless of thread count,
classes, or stack shapes." It is **not**. The `classes` sweep already showed
`NM_CALLTRACE` growing by 15–25 MB once its ~49,152-shape resize threshold is
crossed (see above), which alone is larger than the entire thread-count
overhead range. To get an honest, statistically defensible answer for class
diversity specifically, `classes` mode was rerun with `run_repeated_sweep.sh`
(a repeated-measures variant of the with/without-agent methodology above,
added for this check — it compiles the N classes once and reuses them across
all reps, since recompiling per rep the way `run_nmt.sh` does would make
double-digit repetition counts at high N impractical), at **four N values
(2,000 / 20,000 / 60,000 / 150,000) with 10 repetitions per condition per N**
(80 runs total) instead of a single pair — an initial pass with only 2–3
reps at N=150,000 gave
estimates ranging from 91 MB to 246 MB depending on which two runs happened
to be paired, which is not something a customer-facing number should be
built on. Classes were generated and compiled once per N and reused across
all reps (recompiling 150,000 classes per rep, as the single-shot `run_nmt.sh`
does, would have made this scale of repetition impractical); with/without
runs were interleaved in same-size batches so both conditions saw comparable
concurrent system load.

| N classes | RSS, agent (mean ± stdev) | RSS, no agent (mean ± stdev) | **Δ (profiler cost)** |
|---|---|---|---|
| 2,000 | 284.4 ± 66.9 MB | 286.1 ± 71.0 MB | **-1.7 MB** (noise) |
| 20,000 | 467.2 ± 7.6 MB | 445.4 ± 7.8 MB | **+21.9 MB** |
| 60,000 | 962.3 ± 13.9 MB | 922.3 ± 20.9 MB | **+40.0 MB** |
| 150,000 | 1966.2 ± 89.0 MB | 1863.8 ± 89.9 MB | **+102.4 MB** |

(N=2,000's high per-condition stdev is a shared, environment-level effect —
reps 9–10 landed at ~400+ MB on *both* conditions equally, versus ~230–290 MB
for reps 1–8, most likely a batch-timing/system-cache effect rather than
anything agent-specific; it cancels out in the delta, which is why the delta
itself stays near zero despite the noisy per-condition numbers.)

**This is not a step function, and not flat — it's closer to roughly linear
in how many classes the workload actually samples.** Below ~2,000 classes
the profiler adds nothing measurable; above that, overhead grows
continuously with class diversity rather than jumping once at a single
threshold. Naively dividing the delta by N (raw class count) gives a
per-class rate that drifts across the range (1.12 KB/class at 20K, 0.68 at
60K and 150K — a 30% coefficient of variation). Normalizing instead by
**classes actually appearing in a sampled stack** — checked directly by
grepping distinct class names out of each N's JFR file — tightens this
considerably:

| N classes | distinct classes touched by a sample | coverage | Δ per touched class |
|---|---|---|---|
| 2,000 | 1,872 | 93.6% | (noise) |
| 20,000 | 16,311 | 81.6% | 1.38 KB |
| 60,000 | 43,772 | 73.0% | 0.94 KB |
| 150,000 | 84,640 | 56.4% | 1.24 KB |

The per-touched-class rate (mean 1.18 KB, 19% coefficient of variation) is
tighter than the per-raw-N rate (30%), consistent with the overhead tracking
*how much distinct code the workload's sampled stacks actually reference*
rather than how many classes merely exist. This lines up with the mechanism
already established for `NM_CALLTRACE`: a workload with a wide call graph
(many distinct classes/methods/lambdas actually appearing in stacks, as
generic/framework-heavy or microservice-style Java code often does) is what
drives this cost — raw class-loading volume with narrow, repetitive call
graphs would not. The calltrace hash table's own resize *is* a real step
function internally, but it is a small piece of a larger, smoother-scaling
total: most of the ~100 MB at N=150,000 is not the one-time doubling of
`NM_CALLTRACE` (15–25 MB) but something else that scales more continuously
with sampled-class count.

#### Where the rest of it goes

`run_repeated_sweep.sh` captures the full `jcmd VM.native_memory summary`
output per rep, not just the Thread/Total figures shown above, so this can
be broken down further. Averaging all 10 reps per condition at N=150,000 and
diffing category-by-category:

| NMT category | with-agent mean | without-agent mean | Δ |
|---|---|---|---|
| Class | 343.1 MB | 329.2 MB | **+13.6 MB** |
| Internal | 20.9 MB | 9.1 MB | **+11.6 MB** |
| Java Heap | 616.0 MB | 605.4 MB | **+10.4 MB** |
| Native Memory Tracking (NMT's own bookkeeping) | 54.0 MB | 43.4 MB | **+10.3 MB** |
| GC / Thread / Code / Metaspace / Symbol / others | — | — | ~0 (flat) |

NMT total explains 45.5 of the 102.4 MB delta (44%) — real, confirmed
JVM-side cost, not something the profiler allocates itself. **A strong
candidate mechanism for the "Class" line specifically (and plausibly part of
"Internal")**: this agent registers a `ClassPrepare` JVMTI callback only
when attached (`vmEntry.cpp:511,523`, `JVMTI_EVENT_CLASS_PREPARE`), which
calls `JVMSupport::loadMethodIDsImpl()` → `GetClassMethods()`
(`jvmSupport.cpp:160–178`) to eagerly preallocate every newly-prepared
class's jmethodIDs. The function's own comment explains why and flags
exactly this tradeoff:

> CRITICAL: GetClassMethods must be called to preallocate jmethodIDs for
> AsyncGetCallTrace. AGCT operates in signal handlers where lock acquisition
> is forbidden, so jmethodIDs must exist before profiling encounters them...
> JVM-internal allocation: This triggers JVM to allocate jmethodIDs
> internally, which persist until class unload. High class churn causes
> significant memory growth, but this is inherent to AGCT architecture and
> necessary for signal-safe profiling.

**This was confirmed with a toggle test**: a temporary one-line patch
(`return false;` at the top of `JVMSupport::loadMethodIDsIfNeeded`,
`jvmSupport.cpp:145` — reverted after the check, not part of the harness)
disables jmethodID preloading for both the per-class `ClassPrepare` path and
the bulk `loadAllMethodIDsIfNeeded` path in one place, since both call
through this single function. Rerunning the with/without-agent sweep at
N=150,000 (5 reps each) with preloading disabled:

| NMT category | Δ, preloading enabled (10 reps) | Δ, preloading disabled (5 reps) |
|---|---|---|
| Class | +13.6 MB | **+0.002 MB** (noise) |
| Internal | +11.6 MB | **+0.006 MB** (noise) |
| Native Memory Tracking (own bookkeeping) | +10.3 MB | **-0.1 MB** (noise) |
| Java Heap | +10.4 MB | +80.3 MB |

Disabling jmethodID preloading makes the "Class", "Internal", and NMT's own
tracking-overhead deltas **all collapse to noise** — with-agent's "Class"
value (329,164 KB) lands almost exactly on without-agent's (329,162 KB).
This confirms jmethodID preloading as the driver of all three, not just a
plausible guess: **~35.9 MB of the original ~45.5 MB NMT-visible delta (79%
of it) is directly attributable to this one mechanism.** The overall RSS
delta also dropped with preloading disabled (74.8 MB vs. 102.4 MB), a
smaller drop than the 35.9 MB category-level figure but only measured at 5
reps against high per-run variance (stdev 59–94 MB) — consistent in
direction, not precise enough to read the exact number from.

"Java Heap" moved the *other* way (delta more than doubled) when preloading
was disabled, which at first looks like a real effect but isn't: per-rep
Java Heap committed values swung by ~240 MB across just 5 reps of the
*same* condition (both with and without agent) — this metric is dominated
by GC/heap-resize timing noise at this sample size, unrelated to the patch.
**No conclusion can be drawn about "Java Heap" from this test in either
direction**; it would need many more reps than were practical here to
separate signal from this much noise. NMT's-own-overhead deltas have no
other candidate mechanism to test yet.

**The remaining ~57 MB (56% of the delta) is invisible to NMT entirely** —
this is the profiler's own `malloc`/`new` memory, which NMT structurally
cannot see. Of that, only 15–25 MB is explained by the profiler's own
`NM_CALLTRACE` counter (the confirmed hash-table resize). **That left
roughly 32–42 MB that neither NMT nor the profiler's own `NM_*`
self-accounting explained at the time** — real memory this agent is
genuinely allocating (RSS shows it), that PR #669's `NativeMem` categories
didn't attribute to anything.

**Sizing `MethodMap`/`MethodInfo` to test it as a candidate for this gap is
what uncovered the `resolveMethod` measurement artifact described in the
`NM_DICTIONARY` section above — the original "ruled out" conclusion from
that attempt does not hold.** A temporary instrumentation pass
(`flightRecorder.cpp:605`, reverted after this check) added a
`NativeMem::record(NM_MISC, ...)` call at the point where a genuinely new
`MethodMap` node gets inserted, reusing the otherwise-unused `NM_MISC`
category. It read exactly 0 in a single-chunk run — but per the correction
above, `NM_MISC` here is subject to the *exact same* "counters are
snapshotted before `writeCpool()`" ordering as `NM_DICTIONARY`, since
`MethodMap` insertion (`mi->_key = _method_map->allocId()`) happens one
line before the `_class_map` insertion, inside the *same*
`Lookup::resolveMethod()` call that's now confirmed (GDB, the allocation
shim, source comment) to run during `writeCpool()`. `MethodMap` is
therefore reopened as a real, confirmed-mechanism candidate for
*something* — given it's populated by the identical call path now
confirmed to insert real class names, it plausibly *does* grow alongside
`_class_map`.

**But "reopened as a candidate" turned out to mean "candidate for the
chunk-flush burst," not "candidate for the ~32–42 MB steady-state gap" —
these are not the same thing, and an earlier version of this document
conflated them.** `writeCpool()` (and everything it calls, including
`resolveMethod` and the `MethodMap`/`_class_map` insertions inside it) only
runs from `finishChunk()`, which — confirmed by reading every call site in
the source — fires from exactly two places: `Recording::~Recording()` at
VM shutdown, and `Recording::switchChunk()`, itself called only from the
explicit `FlightRecorder::dump()` API. There is no periodic/automatic
mid-run rotation. The steady-state RSS sweep that produced the ~32–42 MB
figure samples RSS ~1 second *before* the workload loop finishes — i.e.,
strictly before either of those two trigger points can fire. So this
growth mechanism contributed *nothing measurable* to that sweep's number;
it isn't a partial or imprecise explanation, it's temporally excluded from
that measurement altogether. Direct RSS instrumentation (see "Practical
implications" below) independently confirms this growth is real and large
(~213 MiB of physical RSS at the moment `dump()` is called) — it's just a
separate, additive cost from a different point in the process lifecycle,
not a hidden component of the steady-state number. **The ~32–42 MB
steady-state gap remains fully open** and needs a fresh hypothesis
untouched by anything in this `NM_DICTIONARY`/`MethodMap`/two-chunk-test
line of investigation. An LD_PRELOAD-based allocation-tracking tool built
for this investigation (below) independently corroborates that
`StringDictionaryBuffer::insert_with_id` — the function that actually
performs this growth — accounts for a large, multi-ten-MB share of the
profiler's total tracked allocations in a `classes 150000` run; but by the
same timing argument, its report is captured via `atexit()`, which fires
*after* VM shutdown's `finishChunk()` has already run, so it too reflects
the chunk-flush burst rather than steady-state growth, and isn't evidence
about the ~32–42 MB gap either.

### Ruling out OS-level causes, and an independent allocation-tracking tool

Before chasing `MethodMap` further, it's worth checking a different kind of
explanation entirely: is the ~32–42 MB gap even the *profiler's* memory, or
could it be an OS-level side effect of profiling (page cache from writing
the JFR file, some other kernel-level artifact)? `ps`-based RSS lumps all of
this together, so it can't distinguish them on its own.

**`/proc/<pid>/smaps_rollup` rules this out.** For a with-agent `classes
150000` run (RSS ≈ 1.96 GB), `Private_Dirty` = 1,936,752 KB and `Anonymous`
= 1,936,724 KB against a total `Rss` of 1,963,280 KB — **98.6% of RSS is
private, dirty, anonymous memory**, the standard signature of heap
allocation. Only ~14 MB is file-backed (`Pss_File`, almost certainly shared
library code/data, not something that scales with class diversity), and
`/proc/<pid>/maps` shows no mmap of the JFR output file at all (it's written
via plain `write()`, so any file-cache effect would land in system-wide page
cache, not this process's RSS). Whatever the gap is, it's genuine private
heap memory sitting in the process — OS-level caching effects are not a
plausible explanation.

**A purpose-built LD_PRELOAD allocation-tracking tool** was written to
attribute live heap bytes to call sites inside `libjavaProfiler.so`
specifically, since this profiler's own interception machinery
(`mallocTracer.cpp` + `libraryPatcher_linux.cpp`, backing the `nativemem=`
engine) deliberately excludes its own library from GOT/PLT patching to
avoid self-recursion (`libraryPatcher_linux.cpp:425`, `// Don't patch
self`) — it wasn't built for, and can't answer, "how much does the profiler
allocate." The standalone tool intercepts `malloc`/`calloc`/`realloc`/`free`
via `dlsym(RTLD_NEXT, ...)`, captures a short `backtrace()` per allocation,
attributes it to the profiler's library if any captured frame falls within
its mapped address range (found via `/proc/self/maps`), and tracks live
bytes per call site in fixed-size, statically-allocated tables (avoiding
any risk of the tracking code itself recursively calling the hooked
allocators). Validated incrementally (a trivial program, then a plain JVM,
then the profiler-attached JVM on a short workload) before running the full
`classes 150000` workload, which completed without incident.

The tool reported **~189 MB total live bytes attributed to profiler call
sites** for a `classes 150000` run — this is an *absolute* total (including
the profiler's full baseline footprint, most of which is already covered by
existing `NM_*` categories), not a with/without-agent delta, so it isn't
directly comparable to the ~32–42 MB gap figure without further work to
separate baseline from workload-driven growth; treat it as corroborating
signal, not a precise number. Resolving its top call sites via `addr2line`
against this build's debug symbols showed the two largest (**~78.6 MB
each**) both resolving to the exact chain confirmed above:
`CallTraceStorage::processTraces` → `writeStackTraces` → `resolveMethod` →
`fillJavaMethodInfo` → `StringDictionary::lookupDuringDump` →
`StringDictionaryBuffer::insert_with_id`. This is independent confirmation,
via a completely different method (live instruction-pointer attribution
rather than either source instrumentation or a debugger), that this
specific code path is both real and allocation-heavy — consistent with,
though not a precise cross-check against, the two-chunk tests'
~143–236 MiB `NM_DICTIONARY` readings.

### Retiming the allocation shim to steady state: re-discovers, doesn't explain, the gap

The shim above only ever reported via `atexit()`, which — per the
`finishChunk()` timing argument in "Practical implications" below — fires
*after* the chunk-flush burst, not during steady state. It was extended
with an optional background thread that takes a non-destructive snapshot
at a configurable elapsed time, matching `run_repeated_sweep.sh`'s own RSS
sample point (`launch_epoch + (DURATION_MS - 1000)/1000`) as closely as
possible, so the same run gives directly comparable steady-state and
post-exit attributions.

On a `classes 150000` run (180s total, snapshot at 179s): **steady-state
total was ~35.7 MB**, vs. ~197 MB at the post-exit snapshot from the same
run — consistent with the already-confirmed chunk-flush burst, and a
useful independent cross-check of its rough magnitude via a completely
different mechanism (allocation attribution vs. RSS/counter deltas).

Of that ~35.7 MB, **~24.6 MB (376,322 allocations, ~68.6 B average)
resolves to `JVMSupport::loadMethodIDsImpl`.** This looked promising at
first — close to the ~32–42 MB gap in magnitude — but needed verification
before trusting it: the top site's printed frames were suspiciously all
`nil` beyond the match point, unlike every other site (which showed full
16-24-frame chains). Rather than accept or dismiss this, `nm` was used to
get the function's exact address range (`[0x284b0, 0x28500)`, 80 bytes),
and the shim was retargeted to capture full-depth backtraces filtered to
exactly that range. A first attempt with too wide a filter window
accidentally caught a neighboring function (`loadAllMethodIDsIfNeeded`)
instead — caught before drawing any conclusion — and the corrected,
precise window then produced 50 consistent, coherent 18-21-frame chains
from `loadMethodIDsImpl` through several `libjvm.so`-internal frames down
to `malloc`. **Not a backtrace artifact**: this is real allocation, one
small object per method discovered (not per class) across the 150,000
touched classes, exactly matching the "JVM-internal allocation... persists
until class unload... significant memory growth" behavior the profiler's
own source comment already documents for this call.

**But this is not new evidence for the gap — it's the same mechanism
already confirmed, seen through a second instrument.** The toggle test
that measured jmethodID preloading's ~35.9 MB NMT-visible share patched
`JVMSupport::loadMethodIDsIfNeeded` (`jvmSupport.cpp:145`) to `return
false` — and `loadMethodIDsIfNeeded` is what calls `loadMethodIDsImpl`.
Disabling one disables the other; there is no daylight between them. Since
NMT's tracking wraps the same underlying `os::malloc` → glibc `malloc`
path this shim intercepts at the lowest level, the far more likely
explanation is that the shim's ~24.6 MB and the toggle test's ~35.9 MB
are, to a large extent, **the same bytes measured twice**, not two
quantities that add together. The same caution applies to the smaller
sites in this snapshot (`DwarfParser::addRecord`, JIT-code-cache callback
registration) — these plausibly already live under the profiler's own
`NM_LINE_TABLES`/`NM_NATIVE_SYMBOLS` categories rather than being new,
uncounted memory.

**Net result: this experiment mostly re-discovered already-explained
costs rather than accounting for the ~32–42 MB residual gap.** That's
still informative — it suggests the gap is unlikely to be sitting in
additional profiler-`.so`-attributed `malloc`/`new` calls at all (this
shim's entire steady-state total was already-known territory), pointing
instead toward something structurally invisible to this kind of
instrumentation: glibc allocator fragmentation/bookkeeping overhead,
JVM-side memory that doesn't route through `os::malloc`, or memory that's
NMT-tracked but was miscategorized/undercounted in the original NMT
category breakdown. The gap remains open.

### Checking glibc-level fragmentation and JIT code-cache growth

With profiler-`.so`-attributed allocation ruled out, two structurally
different candidates were checked next: memory glibc's allocator holds but
that no allocation-level tool (ours or NMT's) would ever attribute to a
specific structure, and memory the JVM manages entirely outside `malloc`.

**glibc allocator fragmentation/bookkeeping, via `mallinfo2()`.** A second,
minimal LD_PRELOAD probe (no malloc interception, no static tables — just
a background thread calling `mallinfo2()` at the same steady-state instant
`run_repeated_sweep.sh` samples RSS at, plus one at exit) was built
specifically to avoid the previous shim's own ~512 MB static table
potentially perturbing the very fragmentation signal being measured. A
first with/without pair was inconsistent (`hblkhd`, the mmap'd-large-block
figure, moved the *wrong* direction) — recognized immediately as the same
single-pair-unreliability trap this investigation already hit once at this
N, rather than trusted. Five reps each of with/without gave a materially
tighter picture (mallinfo2's own accounting is deterministic, unlike RSS,
which is subject to OS-level noise):

| Metric | Mean delta (with − without) | Stdev |
|---|---|---|
| `uordblks` (malloc's own "bytes in use") | +82.0 MiB | ±3.2 MiB |
| `hblkhd` (mmap'd large-block memory) | −28.6 MiB | ±1.5 MiB |
| `(arena+hblkhd) − uordblks` ("invisible" glibc overhead) | −15.7 MiB | tight, consistent |

**This rules out glibc fragmentation as the explanation**: the "invisible"
overhead delta is consistently *negative* with the agent attached — the
agent's allocation pattern produces *less* unaccounted glibc bookkeeping,
not more, across all 5 reps. But it produced a new, useful, independent
number: `uordblks` delta of **~82.0 MiB (±3.2 MiB)** — total
malloc/`new`-attributable growth, measured via glibc's own live-byte
accounting rather than any per-call-site interception or NMT category.
That's ~20 MB less than the established ~102 MB total RSS delta, meaning
~20 MB of the RSS delta is memory `malloc` itself never sees at all.

**JIT code-cache growth, via NMT's `Code` category.** The obvious
candidate for RSS growth invisible to `malloc` entirely is HotSpot's
`CodeCache`, which is `mmap`'d directly by the JVM outside glibc's arenas.
The existing 10-rep sweep's NMT diff files (`with_repN.diff.txt` /
`without_repN.diff.txt`, already captured, no new run needed) were
checked for the `Code` category's committed-memory growth across all 10
reps:

| | with-agent Δcommitted (mean) | without-agent Δcommitted (mean) | delta |
|---|---|---|---|
| `Code` category | +162.7 MiB | +163.3 MiB | **−0.6 MiB** |

**Ruled out too, and cleanly**: across all 10 reps, the delta is small and
consistently negative (range −54 KB to −1,236 KB) — Code cache grows by
essentially the same ~163 MB in both conditions, driven by the workload's
own JIT warmup compiling 150,000 distinct `compute` methods, not by the
agent. The ~20 MB gap between the new `malloc`-visible figure (~82 MB) and
total RSS (~102 MB) remains open; both of the two most obvious "memory
`malloc` can't see" candidates are now excluded.

**Practical takeaway for quantifying this to a customer**: "flat, a few MB"
is only correct for workloads with narrow call-graph/class diversity
(few distinct classes and methods actually appearing in sampled stacks,
regardless of how many exist or how many threads are running). For a
workload whose sampled stacks touch tens of thousands of distinct
classes/methods — plausible for a large, framework-heavy, or
microservice-style Java application — expect profiler-attributable RSS
overhead on the order of tens to ~100 MB, growing with sampled-class
diversity, and with substantial run-to-run variance at the high end (the
150,000-class point had almost as much spread, ±89 MB, as its own mean).

## Practical implications

Updating memory-usage-model.md's own "practical implications" list with what's
now confirmed empirically:

1. **Thread count (total distinct threads over the profiling session, not
   just peak concurrency) drives real profiler-side memory growth at a
   confirmed ~824 B/thread** — small in absolute terms, but linear and
   predictable. The much larger cost sitting alongside it (~400 KB/thread
   observed RSS growth) is JVM/OS thread overhead the profiler doesn't
   control and can't be optimized away from the profiler's side.
2. **Call-graph breadth (distinct stack-trace shapes) drives real, confirmed
   step-function growth** in the call-trace storage structure specifically,
   consistently at the documented ~49,152-shape hash-table resize threshold
   on both platforms tested. This applies whether the diversity comes from
   many distinct methods at one call site or many distinct classes sampled
   via reflection. **But this internal step function is only a small part of
   the externally-visible RSS cost** — see point 6.
3. **Class/method-name diversity genuinely grows the class-name dictionary
   under both sampling engines — but `NM_DICTIONARY` only shows it promptly
   for one of them.** Allocation sampling's growth is visible in the same
   chunk it happens in. Wall-clock sampling's growth is just as real (two
   independent two-chunk tests measured it directly, at ~143–236 MiB for
   `classes 150000` depending on test construction, and confirmed via
   direct RSS instrumentation to be genuine physical memory — a ~213 MiB
   real RSS jump was measured at the exact moment `dump()` was called,
   closely matching the counter's own ~230 MiB delta in the same run) but
   is only ever visible in a *subsequent* chunk's counter reading, by
   design (`flightRecorder.cpp:819–826`) — a single-chunk profiling session
   (the common case for short-lived diagnostic runs) will never see it in
   `NM_DICTIONARY` at all, regardless of how much real memory it consumed.
   Don't read a flat `NM_DICTIONARY` in a wall-clock-sampled, single-chunk
   session as "no class-name diversity cost" — it may just mean the cost
   hasn't been reported yet. **This growth is gated behind `finishChunk()`,
   which only fires at an explicit `dump()` call or at process shutdown —
   it is a separate, additive cost from the steady-state overhead in point
   6 below, not a hidden component of it** (see the dedicated section
   above for why the two don't overlap).
4. **Call-trace storage and the class-name dictionary appear to have
   different lifetimes across a JFR chunk rotation** — observed
   incidentally while investigating point 3, not independently verified
   beyond one test. `NM_CALLTRACE` reset to its initial baseline capacity
   in the chunk immediately after one that had grown it, while
   `NM_DICTIONARY`'s growth from that same prior chunk persisted into the
   next chunk's reading. If this holds up under further testing, it implies
   call-trace memory is bounded per rotation window in a long-running,
   periodically-rotating production process, while class-name dictionary
   memory can accumulate across rotations up to its capacity cap — a
   meaningfully different long-term memory profile for the two structures
   that this investigation otherwise treated as similar "hash table that
   grows with diversity" cases.
5. **Sampling frequency and allocation rate remain secondary** to the other
   points here for steady-state footprint, consistent with the original
   model's prediction — nothing in this pass found a counter-example.
6. **For quantifying total profiler-attributable RSS overhead to a customer,
   class/call-graph diversity is the dimension that matters, and it does not
   behave like a small fixed cost the way thread count does.** Measured via a
   dedicated with/without-agent sweep (not inferred from internal counters):
   effectively 0 MB overhead at 2,000 distinct classes sampled, growing
   roughly linearly with sampled-class count to ~102 MB at 150,000 — driven
   by how many distinct classes/methods actually appear in sampled stacks,
   not by thread count, raw class-loading volume, or the calltrace table's
   own one-time resize. A workload with a narrow call graph (few distinct
   hot methods) stays near the small-and-flat regime regardless of scale or
   thread count; a workload with a wide call graph (heavy framework/generics/
   lambda usage, microservice-style code diversity) does not, and this is the
   dimension worth asking a customer about before quoting a number. **This
   ~102 MB figure is steady-state only** — sampled while the process runs,
   strictly before any `dump()`/chunk-rotation/shutdown event — and does
   *not* include the separate chunk-flush burst from point 3; see point 7.
7. **A long-running process that rotates JFR chunks periodically (not just
   a single continuous recording to process exit) would pay the point-3
   chunk-flush burst on top of the point-6 steady-state number, once per
   rotation** — at `classes 150000`, that's roughly another ~210–230 MB,
   confirmed via direct RSS measurement. Since `NM_DICTIONARY` content
   persists across rotations (point 4) up to its capacity cap, later
   rotations may see a smaller incremental burst as the dictionary
   saturates — untested. For a process using this profiler's default
   single-continuous-file mode, this burst happens once, at process exit,
   and doesn't affect the process's own operation (it's paid right before
   the process would have exited anyway) — but for any configuration that
   rotates chunks periodically during normal operation, this is a real,
   recurring cost the steady-state number alone would not predict.

## Caveats

- **Single sandboxed Linux x86_64 container throughout.** Most sweep points
  in this document are a single run each — indicative, not statistically
  rigorous, no variance estimates. The class-diversity with/without-agent
  comparison is the exception (10 reps per condition per N, specifically
  because a smaller first attempt there was demonstrably too noisy to trust);
  treat single-run figures elsewhere in this document with more caution than
  that one.
- **`NM_PERF` remains unverified in practice**, though the reason is
  understood — see above. A root-accessible bare-metal or VM Linux host with
  relaxed `kptr_restrict` would be needed to close this out.
- **The `allocs` mode is new and lightly calibrated** — two data points
  (2,000 and 20,000 shapes) is enough to see the engine-difference and the
  plateau pattern, but not enough to pin down the exact threshold the way
  the `traces`/`classes` sweeps' ~49,152/~35–40K estimates are pinned down
  for wall-clock sampling.
- **`nativemem=` (native malloc tracing) was only smoke-tested**, not
  characterized against a dedicated native-allocation-heavy workload.
- **The `allocs` engine's insertion path for class names is inferred, not
  traced to a specific call site** — the *wall-clock* path is now fully
  identified and confirmed (`_class_map`/`resolveMethod`, see above); by
  contrast, allocation sampling's "grows the dictionary in the same chunk"
  behavior is only established by timing/outcome comparison against the
  wall-clock case, not independently traced to its own source location.
- **The thread-count with/without-agent overhead comparison is a single run
  per point on each side** (unlike the class-diversity one, which has 10) —
  some of the smaller deltas (e.g. the −75 KB NMT Thread delta at N=256) are
  plausibly within normal run-to-run noise rather than a real effect; treat
  the overall "small, roughly flat" conclusion as solid but the individual
  KB-level numbers as indicative only.
- **What causes the class-diversity RSS overhead to scale smoothly is now
  partially identified, not fully resolved.** NMT category breakdown
  explains 44% of it; a toggle test (disabling `JVMTI_EVENT_CLASS_PREPARE`
  → `GetClassMethods()` jmethodID preloading, `jvmSupport.cpp:145`)
  confirmed it as the driver of the "Class", "Internal", and NMT's-own-
  overhead lines (all three collapse to noise with it disabled — see
  above). "Java Heap" remains unexplained: it moved in the *opposite*
  direction under the toggle test, but per-rep values for that specific
  metric swung by ~240 MB across 5 reps of the same condition, so no
  conclusion could be drawn either way at a practical rep count.
  **Follow-up worth doing**: repeat the "Java Heap" comparison with many
  more reps (or find a less noisy way to attribute it) before treating it
  as either confirmed or ruled out.
- **CORRECTED: the ~32–42 MB steady-state gap is still fully open — the
  `NM_DICTIONARY`/`MethodMap` growth mechanism explains a different, separate
  cost, not this one.** Two two-chunk tests, one splitting the workload
  evenly and one running almost the full standard duration before forcing
  the dump (repeated twice for the latter), gave ~143 MiB and ~236 MiB
  (236.5 MiB and 235.3 MiB across the two reps, a ~0.5% spread — reproducible
  per construction, not run-to-run noise) respectively. Direct RSS
  instrumentation around the forced `dump()` call confirmed this is real
  physical memory (~213 MiB RSS jump at the moment of the call, closely
  matching the counter's own delta) — but source reading then showed
  `writeCpool()`/`resolveMethod` only ever runs from `finishChunk()`, which
  fires from exactly two places (`Recording::~Recording()` at VM shutdown,
  and `Recording::switchChunk()`, called only from `FlightRecorder::dump()`)
  — no periodic/automatic mid-run rotation exists. The steady-state RSS
  sweep that produced the ~32–42 MB figure samples RSS ~1 second *before*
  the workload loop finishes, strictly before either trigger point can
  fire. So this mechanism contributed nothing to that sweep's number — not
  approximately, exactly zero, because it hadn't happened yet. **The two
  findings don't connect**: there are two separate, real, additive overhead
  components (a ~102 MB steady-state cost with a ~32–42 MB unattributed
  remainder, and a ~210–230 MB chunk-flush burst paid once per JFR
  rotation), and resolving the burst's magnitude did not touch the
  steady-state gap at all. **Follow-up worth doing**: the steady-state gap
  needs a fresh hypothesis, independent of anything in this
  `NM_DICTIONARY`/`MethodMap`/two-chunk-test line of investigation — that
  entire line of work, however solid on its own terms, turned out to be
  answering a different question than the one it was originally chasing.
  Separately, tracing the per-thread/shard `StringDictionaryBuffer`
  buffering mechanism directly (source reading + targeted instrumentation)
  is still worth doing to understand why the chunk-flush burst is an order
  of magnitude larger than raw string content (~2 MB for 150,000 short
  names) would predict — that remains an open question about the burst
  itself, just no longer believed to bear on the steady-state gap. And
  this investigation's own initial conclusion (`resolveMethod` dead,
  `MethodMap` ruled out) turned out wrong, then a second conclusion
  (its growth explains the steady-state gap) also turned out wrong — worth
  remembering when reading any other claim in this document: getting the
  *mechanism* right doesn't automatically mean the *conclusion* drawn from
  it is right; check what's actually being measured and when, every time.
- **A follow-up attempt to close the ~32–42 MB gap with a steady-state-timed
  allocation shim also came up empty, but for an instructive reason.** The
  shim's ~35.7 MB steady-state total was dominated (~24.6 MB) by
  `JVMSupport::loadMethodIDsImpl` — verified as a real allocation chain, not
  a backtrace artifact, via `nm`-precise offset targeting and deep-backtrace
  capture. But that call is disabled by the exact same one-line patch
  (`loadMethodIDsIfNeeded` returning `false`) already used to measure
  jmethodID preloading's ~35.9 MB NMT-visible share — meaning the shim's
  number is most likely the same bytes NMT already counts, not additional
  ones. **Two independent attempts to explain this gap (dictionary/
  MethodMap growth, and now direct allocation attribution) have both landed
  on mechanisms that turned out to already be explained elsewhere.** That's
  a pattern worth taking seriously: whatever is causing the remaining
  ~32–42 MB is likely *not* sitting in additional profiler-`.so`-attributed
  `malloc`/`new` calls at all (this experiment's entire total was
  already-known territory) — worth looking at glibc allocator
  fragmentation/bookkeeping, JVM-side memory that bypasses `os::malloc`, or
  NMT categories that may be undercounting rather than missing entirely,
  before trying a third "new profiler-side allocation" hypothesis.
- **The two follow-up hypotheses from that hint (glibc fragmentation,
  JIT code-cache growth) are now both ruled out too — three attempts in a
  row have not explained the ~32–42 MB gap.** A 5-rep `mallinfo2()`
  comparison found the agent's allocation pattern produces *less*
  unaccounted glibc overhead, not more (mean −15.7 MiB), ruling out
  fragmentation; and NMT's `Code` category grows identically with and
  without the agent across all 10 existing sweep reps (mean delta
  −0.6 MiB), ruling out JIT code-cache growth. **First single-pair result
  for the `mallinfo2()` check was itself inconsistent** (`hblkhd` moved the
  wrong direction) and was not trusted on its own — correctly recognized as
  the same single-pair-unreliability pattern already documented for RSS at
  this N, resolved by running 5 reps instead of 1. The `mallinfo2()` check
  did produce one durable, reusable number: total `malloc`-visible growth
  of ~82.0 MiB (±3.2 MiB across 5 reps) — a clean, independent
  cross-check of the ~102 MB RSS figure, leaving a smaller ~20 MB
  "RSS but not `malloc`-visible" residual that is itself now unexplained
  (Code cache was the obvious candidate and is ruled out). **Follow-up
  worth doing**: the pattern of three ruled-out hypotheses in a row
  (dictionary/`MethodMap`, direct allocation attribution, and now
  fragmentation/code-cache) suggests the ~32–42 MB gap may not be a single
  mechanism at all, but several small contributors below the resolution of
  any one check so far — worth considering a finer-grained NMT
  malloc-vs-mmap breakdown per category (each category already reports
  this split, as seen for `Code`) rather than another single-hypothesis
  test.
- **Coverage (classes actually touched by a sample) fell from 93.6% at
  N=2,000 to 56.4% at N=150,000 for the same relative duration/interval
  scaling used across this sweep.** The per-touched-class normalization is
  more stable than per-raw-N, but wasn't tested against durations tuned to
  hold coverage constant across N, which would isolate the class-count
  effect from the duration/coverage confound more cleanly.
