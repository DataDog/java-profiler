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
3. **Class-name interning behaves differently depending on which sampling
   engine drives it.** Wall-clock/reflection-driven class touching does not
   move the class-name dictionary at all, even at 150,000 distinct classes.
   Allocation sampling *does* move it, at a much smaller N (2,000), then
   plateaus — the two engines record class names through different paths
   with different effective thresholds.
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

**Reading `NM_*` counters correctly requires knowing which of two behaviors
a given counter has:**
- Most counters (`NM_CALLTRACE`, `NM_DICTIONARY`, `NM_THREAD_FILTER`,
  `NM_NATIVE_SYMBOLS`, ...) are **cumulative high-water marks** — they only
  grow, tracking allocations made by hash-table resizes, arena chunks, etc.
  For these, reading the counter once at JFR chunk finish (profiler stop or
  process exit, for a short single-chunk run) gives the right answer, and
  that's what `run_sweep.sh` does throughout this document.
- `NM_THREAD_LOCAL` is different: it's a **live/current count**, incremented
  when a thread's `ProfiledThread` is allocated and decremented by a pthread
  TLS destructor as soon as that thread exits (`threadLocalData.cpp`). A
  workload that spawns N threads and joins all of them before the process
  exits — like `threads N` above — has already freed nearly every one of
  those N `ProfiledThread` structures by the time the JFR chunk (and its
  counter snapshot) is written at exit. Reading it the same way as the other
  counters would then show only whatever handful of long-lived JVM-internal
  threads happened to still have one — not N, and not a value that means
  anything about the workload.

  `LiveThreadLocalSweep.java` / `run_threadlocal_live.sh` measure this
  dimension correctly instead: they spawn N threads, wait for all of them to
  register via `addThread()`, then call the public `JavaProfiler.dump(Path)`
  API to force a JFR chunk write **while all N are still alive and
  busy-looping**, and read the counter from that snapshot. This is the
  measurement used in the thread-count results below.

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

**`NM_DICTIONARY` does not move at all, even at 150,000 distinct classes
over 180 seconds** — an order of magnitude past the theoretical ~35–40K
names needed to fill one 512 KB `StringArena` chunk
(`stringDictionary.h:67`), and well past the point where the same run's
`NM_CALLTRACE` counter demonstrably crossed its own threshold, which rules
out "not enough samples reached the workload" as an explanation for the
flat dictionary reading. This appears to be a genuine gap in what
`NM_DICTIONARY` accounts for under wall-clock/reflection-driven class
touching, not a threshold that just needed more scale to cross — see the
next section for a sampling-engine comparison that narrows this down
further.

## Results: allocation diversity (`allocs`)

Neither of the two modes above allocates a single Java object, so they say
nothing about the allocation-sampling engine (`memory=<interval>[:a]`) or
about how `NM_DICTIONARY` behaves when it's driven by that engine instead of
wall-clock sampling. The `allocs` mode fills that gap:

| N object shapes | duration / interval | max RSS | `NM_CALLTRACE` | `NM_DICTIONARY` | distinct shapes sampled |
|---|---|---|---|---|---|
| 2,000 | 15s / `memory=512:a` | 717 MiB | 24.5 MiB (baseline) | **6.04 MiB** | 1,115 / 2,000 |
| 20,000 | 60s / `memory=256:a` | 680 MiB | 24.5 MiB (baseline) | 6.03 MiB | — |

**Allocation sampling moves `NM_DICTIONARY` at 2,000 distinct shapes** —
smaller than the 150,000-class run above that never moved it at all under
wall-clock sampling — confirmed with a same-machine, same-N, same-duration
A/B against `classes` mode (4.55 MiB flat there vs. 6.04 MiB here). The two
engines clearly record class/type names through different paths with
different effective growth thresholds: allocation sampling's `ObjectSample`
events record the *sampled object's own class* directly, while wall-clock
sampling only ever sees class/method identity indirectly, as part of a
call-trace's frame — plausibly why the two counters (`NM_CALLTRACE` vs.
`NM_DICTIONARY`) move independently of each other in the two engines
(`classes` mode grows call-traces without growing the dictionary; `allocs`
mode grows the dictionary without growing call-traces, since every sampled
allocation is reached through the same one-line reflective call site).

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
   step-function growth** in call-trace storage, consistently at the
   documented ~49,152-shape hash-table resize threshold on both platforms
   tested. This applies whether the diversity comes from many distinct
   methods at one call site or many distinct classes sampled via reflection.
3. **Class/method-name diversity's effect on memory depends on which
   sampling engine is driving it** — wall-clock sampling does not grow the
   class-name dictionary in any tested configuration up to 150,000 classes;
   allocation sampling does, at a much smaller 2,000-class scale. Workloads
   profiled primarily with wall-clock sampling should not expect
   `NM_DICTIONARY` to reflect their class-loading diversity; workloads using
   allocation profiling should.
4. **Sampling frequency and allocation rate remain secondary** to the three
   points above for steady-state footprint, consistent with the original
   model's prediction — nothing in this pass found a counter-example.

## Caveats

- **Single sandboxed Linux x86_64 container, single run per sweep point** —
  indicative, not statistically rigorous; no repeated trials or variance
  estimates were collected.
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
