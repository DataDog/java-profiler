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

## Summary

**What drives memory overhead.** Thread count adds a small, linear,
well-understood cost (~824 bytes/thread inside the profiler itself); the
much larger ~400 KB/thread RSS growth alongside it is JVM/OS thread
machinery the profiler doesn't cause and can't see into. **Call-graph
diversity is the dimension that actually matters for customer-facing
sizing — specifically, the number of distinct *methods* (equivalently,
distinct call-trace shapes) actually appearing in sampled stacks, not the
number of distinct classes**: a workload whose sampled stacks touch few
distinct methods costs the profiler close to nothing regardless of scale;
a workload with a wide call graph (framework-heavy, generics/lambda-heavy,
microservice-style code) drives real, substantial, scaling overhead —
measured at ~0 MB at 2,000 sampled classes up to ~102 MB at 150,000
(one method per class in that sweep, so "classes touched" and "methods
touched" moved together and looked indistinguishable), growing at a
fairly consistent ~1-1.4 KB per touched method. A dedicated follow-up
disentangling the two (same 2,000 classes, but 100 methods each instead of
1) confirmed it's methods that matter: overhead jumped to ~74 MB — in the
same range as the 150,000-class result — purely from adding methods to
the *same* small set of classes.

**Where that ~102 MB (at N=150,000, default JVM heap ergonomics) comes
from.** About a third (~35 MB) is visible to the JVM's own Native Memory
Tracking and has a confirmed mechanism: this agent eagerly preallocates
jmethodIDs for every newly prepared class (`JVMTI_EVENT_CLASS_PREPARE` →
`GetClassMethods`, `jvmSupport.cpp:145`), which AsyncGetCallTrace's
signal-handler safety requires — confirmed by a toggle test that makes the
NMT-visible deltas collapse to noise when this is disabled. The remainder
is real, agent-attributable memory whose precise mechanism resists
attribution — five independent lines of investigation (dictionary/`MethodMap`
growth, direct allocation-site attribution, glibc fragmentation, JIT
code-cache growth, and a from-scratch recalibration of the NMT breakdown)
each ruled out or turned out to already be counted elsewhere.

That remainder was originally reported as "~42–57 MB", but that range came
from a 10-rep sweep with default (unfixed) JVM heap sizing, where each
condition's own RSS carried ±89 MB of run-to-run stdev — large enough that
the ~102 MB headline delta itself was only a ~2.5σ signal, and the
"42–57 MB" band inherited that same uncertainty without ever being stated
as a confidence interval. **A follow-up fixed-heap re-measurement
(`-Xms=-Xmx`, `-XX:+AlwaysPreTouch`, removing GC/heap-resize timing as a
noise source) at the same N, 12 reps, cut each condition's stdev by roughly
10x (to ~6–11 MB) and landed the residual at ~34.6 MB with a ±3.9 MB
standard error** — a real, non-noise, agent-attributable gap of roughly
30–40 MB, now with an actual confidence interval instead of an
unquantified range. See "Investigating the unattributed remainder" below,
specifically "Tightening the residual: a fixed-heap re-measurement", for
the full derivation.

**A separate, additive cost at JFR chunk boundaries.** Wall-clock sampling's
class-name dictionary growth happens at chunk-write time (an explicit
`dump()` call, chunk rotation, or process exit), not continuously — so the
profiler's own `NM_DICTIONARY` counter only reflects a chunk's growth in
the *next* chunk's reading, by design (this is documented in the source,
`flightRecorder.cpp:819–826`). The steady-state ~102 MB figure above is
sampled before that ever happens, so this cost is real but separate — a
one-time ~140–235 MB burst (magnitude depends on test construction; the
measurement methodology itself perturbs the system, so the true
unperturbed size isn't independently pinned down) paid once per JFR chunk
write. For the default single-continuous-recording mode, that's paid once,
at process exit, with no effect on the running process; for any
configuration that rotates JFR chunks periodically, it recurs.

**What we don't know.** The specific mechanism for the ~34.6 MB (±3.9 MB
SE) unattributed remainder — its magnitude is now precisely bounded, but
not its cause; the true (unperturbed) magnitude of the chunk-flush
burst; whether call-trace storage resetting across chunk rotations while
the dictionary's content persists (observed once) generalizes; `NM_PERF`'s
behavior under load (unverifiable in this sandboxed container); precise
characterization of the `allocs` and `nativemem=` engines (lightly
calibrated so far).

## Harness

Standalone Java programs run per sweep point with
`-agentpath:libjavaProfiler.so=start,<engine>,jfr,file=<out>,cstack=fp`.
Everything needed is under `doc/performance/memsweep/` in this checkout:

```
memsweep/
├── src/
│   ├── MemSweepMain.java          # threads / traces / classes / classesM / allocs workloads
│   ├── GenSources.java            # writes .java sources for traces/classes/classesM/allocs,
│   │                              # compiled externally
│   └── LiveThreadLocalSweep.java  # dedicated thread-count-only program, see below
├── run_sweep.sh                   # one sweep point -> CSV line with RSS + NM_* counters
├── run_threadlocal_live.sh        # thread-count-only, reads NM_THREAD_LOCAL live
├── run_nmt.sh                     # one sweep point with JVM Native Memory Tracking
├── run_repeated_sweep.sh          # repeated-measures with/without-agent comparison, see below
├── run_repeated_sweep_classesm.sh # same, for classesM mode (extra methods-per-class parameter)
└── extract.py                     # parses `jfr print --json` output for native_mem_* counters
```

Five independent workload modes, each isolating one dimension:

- **`threads N`** — spawns N daemon threads, each busy-looping
  (`Math.sqrt`) for the run duration. Driven by the wall-clock engine
  (`wall=<interval>`).
- **`traces N`** — one thread, one precompiled class with N distinct static
  methods, invoked in a cycle via reflection. Isolates call-trace shape
  diversity from class-loading (still 1 class). Wall-clock engine.
- **`classes N`** — one thread, N distinct precompiled classes each with one
  method, invoked in a cycle via reflection. Isolates class/method diversity
  from call-trace shape variety (same call site each time). Wall-clock
  engine. **Every class here has exactly one method, so this mode alone
  cannot distinguish "cost tracks classes touched" from "cost tracks
  methods touched" — see `classesM` below.**
- **`classesM N M`** — like `classes`, but N classes each with M methods,
  all M invoked every cycle. Lets classes-touched and methods-touched vary
  independently, specifically to test which one drives overhead (see
  "Isolating what the profiler itself adds: class diversity" below).
- **`allocs N`** — one thread, N distinct precompiled short-lived object
  shapes (varying field count, so each is a genuinely different allocation
  size), allocated and discarded in a cycle. Driven by the allocation-
  sampling engine (`memory=<interval>:a`) instead of wall-clock, since none
  of the other modes allocate any Java objects.

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

**`NM_DICTIONARY` does not move at all in a single-chunk reading, even at
150,000 distinct classes over 180 seconds — but real growth is happening
underneath it, deferred by design.** The insertion path
(`Recording::writeStackTraces()` → `Lookup::resolveMethod()` →
`Lookup::fillJavaMethodInfo()` → `_classes->lookupDuringDump()`,
`flightRecorder.cpp`) only runs from `writeCpool()`, which only runs from
`finishChunk()` — and `NM_*` counters are snapshotted into the JFR chunk
*before* `writeCpool()` executes within that same `finishChunk()` call. The
profiler's own source comment states this explicitly, right above the
counter-snapshot code (`flightRecorder.cpp:819–826`):

> this will not report correct counts for any counters updated during
> writing the constant pool... Some counters we verify to balance (e.g.
> the anonymous dictionaries) will be reported as positive, others (e.g.
> **the classes dictionary**) will reflect the previous serialization.

So growth from a chunk's own dump-time class-name insertions is written
into that chunk, but the counter snapshot describing that growth was
already taken moments earlier — it only becomes visible in a *subsequent*
chunk's reading. A single-chunk run (the common case for short diagnostic
sessions, and every measurement elsewhere in this document) has no
subsequent chunk to reveal it in, and will show `NM_DICTIONARY` as flat
regardless of how much the dictionary actually grew.

This was confirmed three independent ways: a GDB breakpoint on
`Lookup::resolveMethod` hits immediately with a full, sensible backtrace
through `Recording::~Recording()` → `finishChunk()` → `writeCpool()` →
`writeStackTraces()` → `resolveMethod`; a purpose-built LD_PRELOAD
allocation-tracking tool (below) attributes real, substantial live memory
to exactly this call chain, ending in `StringDictionaryBuffer::insert_with_id`;
and the source comment above explains the mechanism directly.

**Two-chunk tests confirm the growth is real, large, and reproducible.**
Each forces an intermediate `profiler.dump()` during a `classes 150000`
run, then reads the *final* chunk (written normally at process exit):

| Test | Workload before the forced dump | `NM_DICTIONARY` in the dump chunk | `NM_DICTIONARY` in the final chunk |
|---|---|---|---|
| Split evenly | 90s of 180s total | 4,774,032 B (baseline) | 149,876,928 B (~143 MiB) |
| Dump near the end, rep 1 | 177s of 180s total | 4,774,032 B (baseline) | 247,996,656 B (~236.5 MiB) |
| Dump near the end, rep 2 | 177s of 180s total | 4,774,032 B (baseline) | 246,798,576 B (~235.3 MiB) |

The two "dump near the end" reps agree to within ~0.5%, including an
*identical* dump-chunk baseline across all three runs — the ~93 MiB gap
between the two test constructions is a real, repeatable function of how
much workload ran before the forced dump (more pre-dump runtime → bigger
resolution backlog → bigger growth in the next chunk), not measurement
noise. This confirms wall-clock dictionary growth is real and substantial —
comparable to or larger than `NM_CALLTRACE`'s own growth — and scales with
accumulated backlog at dump time rather than being a fixed artifact of
forcing a dump at all.

**No single one of these numbers should be read as "the true magnitude
under normal conditions."** All three come from a methodology that itself
perturbs the system (an explicit `dump()` call standard single-chunk runs
never make), and all are larger — in the "dump near the end" case, more
than twice as large — than the entire ~102 MB steady-state RSS delta this
document otherwise measures. Raw string content for 150,000 short class
names is only on the order of ~2 MB, so something beyond simple string
storage is inflating this — plausibly per-thread or per-shard
`StringDictionaryBuffer` copies of the same names accumulating before
consolidation into the shared arena, a hypothesis not traced further. The
existence, substantial size, and per-construction reproducibility of this
growth is solid; its precise magnitude under normal, unperturbed conditions
remains an open question this methodology can't answer, since observing it
at all requires the perturbation.

**A second finding fell out of the same test: call-trace storage and the
class-name dictionary have different lifetimes across a chunk rotation.**
`NM_CALLTRACE` was 50,858,496 B (grown) in the dump chunk but read back down
to 25,692,672 B — its initial baseline capacity — in the final chunk, just
3 seconds later, despite the workload continuing to sample the same 150,000
classes throughout. The dictionary's growth, by contrast, carries forward
into the next chunk's reading (that's the deferred-visibility mechanism
above). This means **call-trace memory is bounded per rotation window**
(each rotation effectively restarts the hash table) while **class-name
dictionary memory can accumulate across rotations**, up to its
`MAX_CLASS_MAP_SIZE` cap (`profiler.h`, 262,144 entries) — a materially
different long-term memory profile for two structures that otherwise look
like similar "hash table that grows with diversity" cases. This is from one
test and worth confirming with dedicated repetition before treating it as
fully settled.

The `allocs` section below shows allocation sampling's dictionary insertion
is visible immediately, in the same chunk — the two engines both grow the
dictionary for real, they just differ in *when* that growth is externally
visible.

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
mode (4.55 MiB flat there vs. 6.04 MiB here). The real difference between
the two engines isn't "one grows the dictionary and the other doesn't" —
both do, substantially — it's *when* that growth becomes externally
visible: allocation sampling's `ObjectSample` path apparently interns the
sampled object's class at *sample* time (immediately reflected in that
chunk's counter reading), while wall-clock's `MethodSample` symbolication
happens at *dump* time, one chunk later. The "sample time" half of that
explanation is inferred from timing behavior, not independently traced to
allocation sampling's own insertion call site the way the wall-clock path
is.

Growth here also matches the step-function pattern from the `traces` sweep:
the 2,000-shape and 20,000-shape runs land at essentially the same value
(6.04 vs. 6.03 MiB) — one arena-chunk threshold was crossed somewhere below
2,000 shapes, and neither run went far enough to cross the next one.

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
(824 B/thread, a rounding error against a ~400 KB/thread RSS delta): roughly
three-quarters of the per-thread RSS growth here is invisible to both NMT
and the profiler's own instrumentation — almost certainly OS/kernel-level
per-thread bookkeeping (pthread structures, stack guard pages, kernel task
scheduling structures) outside either's reach. The macOS pass found a
similar picture with a smaller explained fraction (~17–20%, vs. ~24–27%
here) — same conclusion, different exact split, plausibly reflecting
platform differences in kernel-level thread bookkeeping rather than
anything specific to this profiler.

### Isolating what the profiler itself adds: thread count

The table above shows how much of the *thread-count-driven* RSS growth NMT
can explain, but not how much of it is the profiler's own doing versus the
cost of running N threads in this JVM regardless. Isolating that means
running the identical workload twice, agent attached vs. not, and taking
the difference — `run_nmt.sh`'s `--no-agent` flag:

| N threads | RSS, agent | RSS, no agent | RSS Δ (profiler cost) | NMT Thread, agent | NMT Thread, no agent | NMT Thread Δ | NMT total, agent | NMT total, no agent | NMT total Δ |
|---|---|---|---|---|---|---|---|---|---|
| 1 | 72,248 KB | 68,748 KB | +3,500 KB | 966 KB | 961 KB | +5 KB | 1,106,757 KB | 1,106,348 KB | +409 KB |
| 256 | 177,000 KB | 168,924 KB | +8,076 KB | 28,512 KB | 28,587 KB | −75 KB | 1,134,910 KB | 1,134,599 KB | +311 KB |
| 1000 | 457,416 KB | 447,288 KB | +10,128 KB | 91,528 KB | 90,431 KB | +1,097 KB | 1,210,526 KB | 1,208,958 KB | +1,568 KB |

**The profiler's RSS overhead here is a roughly flat few-MB baseline cost
(3.5–10 MB across this range), not a strong per-thread multiplier** — it
grows mildly with N (consistent with the agent's own housekeeping threads
and per-thread signal setup costing a little more as N grows) but nowhere
near proportionally; the bulk of the thread-count-driven RSS growth above
happens with or without the agent attached, confirming it's overwhelmingly
a JVM/OS cost. NMT's own "Thread" bucket shows no consistent agent effect
at all (the deltas are within run-to-run noise), consistent with wall-clock
sampling piggybacking on existing application threads rather than spawning
dedicated OS threads per profiled thread. NMT's total committed does show a
small, mildly N-dependent increase attributable to the agent (409 KB →
1,568 KB from N=1 to N=1000), plausibly safepoint/synchronization/internal
bookkeeping responding to additional signal traffic, not broken down by
category. **This conclusion is specific to thread count in a workload with
no class/call-trace diversity** — it does not extend to class/call-trace
diversity, covered next, where the profiler's own overhead is substantial
and scales with the workload.

### Isolating what the profiler itself adds: class diversity

`NM_CALLTRACE` growing by 15–25 MB once its ~49,152-shape resize threshold
is crossed (see above) is already larger than the entire thread-count
overhead range, so class diversity needed the same rigor. `classes` mode
was rerun with `run_repeated_sweep.sh` (compiles the N classes once and
reuses them across reps, since recompiling per rep the way `run_nmt.sh`
does would make double-digit repetition impractical at high N) at **four N
values (2,000 / 20,000 / 60,000 / 150,000) with 10 repetitions per
condition per N** (80 runs total) — an initial pass with only 2–3 reps at
N=150,000 gave estimates ranging from 91 MB to 246 MB depending on which
two runs happened to be paired, not something a customer-facing number
should be built on. With/without runs were interleaved in same-size
batches so both conditions saw comparable concurrent system load.

| N classes | RSS, agent (mean ± stdev) | RSS, no agent (mean ± stdev) | **Δ (profiler cost)** |
|---|---|---|---|
| 2,000 | 284.4 ± 66.9 MB | 286.1 ± 71.0 MB | **-1.7 MB** (noise) |
| 20,000 | 467.2 ± 7.6 MB | 445.4 ± 7.8 MB | **+21.9 MB** |
| 60,000 | 962.3 ± 13.9 MB | 922.3 ± 20.9 MB | **+40.0 MB** |
| 150,000 | 1966.2 ± 89.0 MB | 1863.8 ± 89.9 MB | **+102.4 MB** |

**This N=150,000 row's own stdev (±89 MB per condition) is large enough
that its point estimate shouldn't be read as precise** — see "Tightening
the residual: a fixed-heap re-measurement" (under "Investigating the
unattributed remainder") for a 12-rep fixed-heap redo at the same N that
cuts per-condition stdev roughly 10x. The *qualitative* conclusion this
table exists to support — touched-method count, not raw class count,
drives the cost, confirmed by comparing across N and against the
`classesM` follow-up below — holds regardless of heap methodology; only
this row's absolute precision is superseded.

(N=2,000's high per-condition stdev is a shared, environment-level effect —
reps 9–10 landed at ~400+ MB on *both* conditions equally, versus ~230–290
MB for reps 1–8, most likely a batch-timing/system-cache effect rather than
anything agent-specific; it cancels out in the delta.)

**This is not a step function, and not flat — it's closer to roughly linear
in how much of the workload's call graph the sampler actually records.**
Below ~2,000 classes the profiler adds nothing measurable; above that,
overhead grows continuously. Naively dividing by raw class count gives a
per-class rate that drifts (1.12 KB/class at 20K, 0.68 at 60K/150K — 30%
coefficient of variation). Normalizing instead by **classes actually
appearing in a sampled stack** (checked directly by grepping distinct
class names out of each N's JFR file) tightens this considerably:

| N classes | distinct classes touched by a sample | coverage | Δ per touched class |
|---|---|---|---|
| 2,000 | 1,872 | 93.6% | (noise) |
| 20,000 | 16,311 | 81.6% | 1.38 KB |
| 60,000 | 43,772 | 73.0% | 0.94 KB |
| 150,000 | 84,640 | 56.4% | 1.24 KB |

But every class in this sweep's workload has exactly one method, so
"classes touched" and "methods touched" are the same number here by
construction — this table alone can't tell whether classes or methods are
the real driver. A dedicated follow-up disentangles them: `classesM` mode
generates N classes with a configurable M methods each, all invoked every
cycle, so classes-touched and methods-touched can move independently. At
**N=2,000 classes with 100 methods each** (200,000 total methods, still
only 2,000 total classes), the run touched all 2,000 classes but only
96,953 of the 200,000 methods (48.5% method coverage) — and cost **+74.3
MB (±19.2 MB SE, 10 reps)**, in the same range as the 150,000-class,
one-method-each result (+102.4 MB, 84,640 touched), despite using **75x
fewer classes**. `NM_CALLTRACE` confirms this without any RSS-level noise
at all: both runs land on the identical 48.5 MiB hash-table capacity,
since both touch a comparable number of distinct call-trace shapes — the
structure never counted classes, only shapes, to begin with.

| Configuration | Classes touched | Methods touched | RSS Δ | Rate per touched method |
|---|---|---|---|---|
| N=2,000, 1 method/class | 1,872 | 1,872 | ~0 (noise) | — |
| N=20,000, 1 method/class | 16,311 | 16,311 | +21.9 MB | 1.38 KB |
| N=150,000, 1 method/class | 84,640 | 84,640 | +102.4 MB | 1.24 KB |
| N=2,000, 100 methods/class | 2,000 | 96,953 | +74.3 MB | 0.78 KB |

**The driver is the number of distinct methods (equivalently, distinct
call-trace shapes) actually appearing in sampled stacks, not the number of
distinct classes.** The ~1.2 KB/touched-*class* rate from the single-
method sweep and the ~0.78 KB/touched-*method* rate from the multi-method
follow-up are the same underlying quantity, not two separate findings — a
workload with a wide call graph (many distinct methods/lambdas actually
appearing in stacks, as generic/framework-heavy or microservice-style Java
code often does) drives this cost regardless of how many classes those
methods happen to be spread across; raw class-loading volume with narrow,
repetitive call graphs does not. (A smaller-contrast attempt at this same
question — N=20,000 classes with 5 methods each — was inconclusive: the
5x-methods condition turned out far noisier, run to run, than the
1-method baseline at the same N, for reasons not yet identified, and the
modest predicted separation didn't clear that noise. The 100x-methods
design above was chosen specifically to produce a large enough contrast to
be decisive despite that.) `NM_CALLTRACE`'s own resize is a real step
function internally, but it's a small piece (15–25 MB) of a much larger,
smoother-scaling total tied to this same touched-method-count variable.

#### NMT category breakdown

`run_repeated_sweep.sh` captures the full `jcmd VM.native_memory summary`
output per rep, so the ~102 MB at N=150,000 can be broken down further.
Averaging all 10 reps per condition and diffing category-by-category:

| NMT category | with-agent mean | without-agent mean | Δ |
|---|---|---|---|
| Class | 343.1 MB | 329.2 MB | **+13.6 MB** |
| Internal | 20.9 MB | 9.1 MB | **+11.6 MB** |
| Java Heap | 616.0 MB | 605.4 MB | **+10.4 MB** |
| Native Memory Tracking (NMT's own bookkeeping) | 54.0 MB | 43.4 MB | **+10.3 MB** |
| GC / Thread / Code / Metaspace / Symbol / others | — | — | ~0 (flat) |

NMT total explains 45.5 of the 102.4 MB delta (44%). **The Class/Internal
lines have a confirmed mechanism**: this agent registers a `ClassPrepare`
JVMTI callback only when attached (`vmEntry.cpp:511,523`,
`JVMTI_EVENT_CLASS_PREPARE`), calling `JVMSupport::loadMethodIDsImpl()` →
`GetClassMethods()` (`jvmSupport.cpp:160–178`) to eagerly preallocate every
newly-prepared class's jmethodIDs. The function's own comment explains why:

> CRITICAL: GetClassMethods must be called to preallocate jmethodIDs for
> AsyncGetCallTrace. AGCT operates in signal handlers where lock acquisition
> is forbidden, so jmethodIDs must exist before profiling encounters them...
> JVM-internal allocation: This triggers JVM to allocate jmethodIDs
> internally, which persist until class unload. High class churn causes
> significant memory growth, but this is inherent to AGCT architecture and
> necessary for signal-safe profiling.

**Confirmed with a toggle test**: a temporary one-line patch (`return
false;` at the top of `JVMSupport::loadMethodIDsIfNeeded`,
`jvmSupport.cpp:145` — reverted after the check, not part of the harness)
disables jmethodID preloading for both the per-class `ClassPrepare` path
and the bulk `loadAllMethodIDsIfNeeded` path in one place (both call
through this single function). Rerunning the with/without-agent sweep at
N=150,000 (5 reps each) with preloading disabled:

| NMT category | Δ, preloading enabled (10 reps) | Δ, preloading disabled (5 reps) |
|---|---|---|
| Class | +13.6 MB | **+0.002 MB** (noise) |
| Internal | +11.6 MB | **+0.006 MB** (noise) |
| Native Memory Tracking (own bookkeeping) | +10.3 MB | **-0.1 MB** (noise) |
| Java Heap | +10.4 MB | +80.3 MB |

Disabling jmethodID preloading makes the Class, Internal, and NMT's own
tracking-overhead deltas all collapse to noise — with-agent's "Class" value
(329,164 KB) lands almost exactly on without-agent's (329,162 KB). **~35.9
MB of the original ~45.5 MB NMT-visible delta (79% of it) is directly
attributable to jmethodID preloading.** The overall RSS delta also dropped
with preloading disabled (74.8 MB vs. 102.4 MB) — consistent in direction,
though only measured at 5 reps against high per-run variance (stdev
59–94 MB), not precise enough to read an exact number from.

"Java Heap" moved the *other* way (delta more than doubled) when preloading
was disabled — not a real effect: per-rep Java Heap committed values swung
by ~240 MB across just 5 reps of the *same* condition, dominated by
GC/heap-resize timing noise at this sample size. **This is noise, not a
signal in either direction**; it would need many more reps to attribute at
all.

**One nuance the `classesM` finding above raises but doesn't resolve**:
jmethodID preloading fires on `ClassPrepare`, once per *class*, regardless
of whether that class's methods ever get sampled — so on its own terms
this specific mechanism should scale with total classes loaded (and their
method counts), not with touched-method count the way the overall RSS
delta does. An attempt to check this directly (comparing NMT category
deltas between 1-method and 5-method classes at the same N) didn't give a
clean answer — the category-level deltas were as noisy as the overall RSS
figure at that configuration, in some cases flipping sign entirely. How
jmethodID preloading's own contribution interacts with the
touched-vs-loaded distinction remains open; the touched-method-count
finding above is solid at the aggregate RSS/`NM_CALLTRACE` level, not yet
decomposed back down to this specific mechanism.

## Investigating the unattributed remainder

The category breakdown above accounts for the ~35 MB that's visible to
NMT. The remaining ~57 MB of the 102.4 MB delta is invisible to NMT
entirely — this is memory the agent allocates through paths NMT
structurally doesn't instrument (its own `malloc`/`new`, or direct `mmap`
calls). `NM_CALLTRACE`'s own resize (15–25 MB) accounts for part of that,
leaving a residual this section tries to pin down. Five independent checks
were run against it; none found the mechanism, but each ruled something
out and narrowed what's left.

**OS-level effects are not the explanation.** `/proc/<pid>/smaps_rollup`
for a with-agent `classes 150000` run (RSS ≈ 1.96 GB) shows `Private_Dirty`
= 1,936,752 KB and `Anonymous` = 1,936,724 KB against a total `Rss` of
1,963,280 KB — 98.6% of RSS is private, dirty, anonymous memory, the
standard signature of heap allocation, not page cache or another kernel-
level artifact. `/proc/<pid>/maps` shows no mmap of the JFR output file at
all (it's written via plain `write()`). Whatever this memory is, it's
genuine private heap memory the process itself is holding.

**A purpose-built LD_PRELOAD allocation-tracking tool**, built because this
profiler's own native-malloc-tracing machinery (`mallocTracer.cpp` +
`libraryPatcher_linux.cpp`) deliberately excludes its own library from
GOT/PLT patching to avoid self-recursion (`libraryPatcher_linux.cpp:425`)
and so can't answer "how much does the profiler itself allocate."
Intercepts `malloc`/`calloc`/`realloc`/`free` via `dlsym(RTLD_NEXT, ...)`,
attributes each call to the profiler's library if any captured backtrace
frame falls within its mapped address range, and tracks live bytes per
call site in fixed-size static tables. Reported ~189 MB total live bytes
attributed to profiler call sites for a `classes 150000` run (an absolute
total, not a with/without delta, so not directly comparable to the residual
figure) — its two largest sites (~78.6 MB each) both resolve to
`CallTraceStorage::processTraces` → `writeStackTraces` → `resolveMethod` →
`StringDictionaryBuffer::insert_with_id`, independently confirming that
call chain is real and allocation-heavy via a completely different method
(live instruction-pointer attribution) than the GDB/source-comment
confirmation above.

**Retiming the same shim to sample at steady state instead of `atexit()`**
(via a background thread taking a non-destructive snapshot at the same
elapsed time `run_repeated_sweep.sh` samples RSS) isolates what the
profiler allocates *before* any chunk write, as opposed to the dictionary
growth above which only happens at chunk-write time. Steady-state total on
a `classes 150000` run: ~35.7 MB, dominated (~24.6 MB, 376,322 allocations
averaging 68.6 B) by `JVMSupport::loadMethodIDsImpl` — verified via
`nm`-precise address-range targeting and deep-backtrace capture to be a
real, coherent allocation chain through `jvmti->GetClassMethods()`, not a
backtrace artifact. But this is the *same* call disabled by the toggle test
above (`loadMethodIDsIfNeeded`, which the toggle patches, is what calls
`loadMethodIDsImpl`) — since NMT tracks the same underlying `malloc` path
this shim intercepts, this is most likely the same bytes measured twice,
not new evidence. The smaller sites in this snapshot (`DwarfParser::addRecord`,
JIT-code-cache callback registration) plausibly already live under the
profiler's own `NM_LINE_TABLES`/`NM_NATIVE_SYMBOLS` categories too. This
experiment's entire steady-state total turned out to be already-known
territory, suggesting the residual isn't additional profiler-`.so`-attributed
allocation at all.

**glibc allocator fragmentation**, checked via a second, minimal LD_PRELOAD
probe (no malloc interception, just a background thread calling
`mallinfo2()` at the same steady-state instant, avoiding the previous
shim's own large static tables as a potential confound). A first
with/without pair was inconsistent (`hblkhd` moved the wrong direction) and
wasn't trusted — the same single-pair-unreliability pattern the RSS
comparison above required 10 reps to escape — so this was run 5 reps per
condition instead:

| Metric | Mean delta (with − without) | Stdev |
|---|---|---|
| `uordblks` (malloc's own "bytes in use") | +82.0 MiB | ±3.2 MiB |
| `hblkhd` (mmap'd large-block memory) | −28.6 MiB | ±1.5 MiB |
| `(arena+hblkhd) − uordblks` ("invisible" glibc overhead) | −15.7 MiB | tight, consistent |

**Fragmentation is ruled out**: the "invisible" glibc overhead delta is
consistently *negative* with the agent attached, not positive. This did
produce a useful, independent number: total `malloc`-visible growth of
~82.0 MiB, about 20 MB less than the ~102 MB total RSS delta — meaning
~20 MB of that delta is memory `malloc` itself never sees at all.

**JIT code-cache growth**, the obvious candidate for RSS growth invisible
to `malloc` (HotSpot's `CodeCache` is `mmap`'d directly, outside glibc's
arenas). Checked against the already-captured NMT diff files from the
10-rep sweep (no new runs needed) for the `Code` category specifically:

| | with-agent Δcommitted (mean) | without-agent Δcommitted (mean) | delta |
|---|---|---|---|
| `Code` category | +162.7 MiB | +163.3 MiB | **−0.6 MiB** |

**Ruled out too, cleanly**: consistently small and negative across all 10
reps (range −54 KB to −1,236 KB) — Code cache grows by essentially the same
~163 MB in both conditions, driven by the workload's own JIT warmup
compiling 150,000 distinct methods, not by the agent.

**Recalibrating from scratch**, mining the already-captured NMT diff files
for a full category-by-category malloc-vs-mmap breakdown:

| Category | Total Δ | malloc Δ | mmap Δ |
|---|---|---|---|
| Class | +13.9 MB | +13.2 MB | +0.7 MB |
| Internal | +11.3 MB | +11.3 MB | 0 |
| Java Heap | +10.4 MB | 0 | +10.4 MB |
| Native Memory Tracking (own) | +10.2 MB | ~0 | +10.2 MB, as "tracking overhead" (ambiguous) |
| Compiler | −3.6 MB | ~0 | — |
| Arena Chunk | −1.8 MB | −1.8 MB | 0 |
| everything else | ~+1.5 MB combined | small | small |

This closely reproduces the toggle-test figures (Class +13.6 MB, Internal
+11.6 MB), a sanity check on the mining. Excluding Java Heap's already-known
noise, the confirmed NMT-visible total is Class+Internal+NMT-own ≈ 35.5 MB,
matching jmethodID's confirmed 35.9 MB almost exactly. Cross-checking with
the mallinfo2 figures (which sidesteps the Java Heap ambiguity entirely,
since Java Heap is 100% mmap): `82.0 MiB total malloc − 23.1 MiB NMT-tracked
malloc = 58.9 MiB NMT-invisible malloc growth`, within ~2 MiB of the
original derivation's ~56.9 MB NMT-invisible total — two independent
methods agreeing closely.

`NM_CALLTRACE`'s own counter needed the same scrutiny. Reading it directly
from the 10 already-existing with-agent JFR files gives 50,858,496 bytes
(48.5 MiB) at N=150,000, deterministic across all 10 reps, and it scales in
exact +8.0 MiB steps (`CALL_TRACE_CHUNK`, `callTraceHashTable.cpp:18`)
across N — 24.5 / 32.5 / 40.5 / 48.5 MiB at N=2,000/20,000/60,000/150,000.
This is `NM_CALLTRACE`'s full size, not the 15–25 MB one-time resize
increment cited above. But it's backed by a raw `mmap()` syscall
(`LinearAllocator::allocateChunk` → `OS::safeAlloc`, confirmed in source —
the comments explicitly describe "a raw mmap syscall"), not `malloc` —
invisible to NMT, the allocation shim, and `mallinfo2` simultaneously, so
its logical size can't be subtracted directly from the malloc-based figures
above (doing so produces an impossible total that exceeds the entire RSS
delta).

Checking `/proc/<pid>/smaps` directly (readable without `ptrace`, unlike a
GDB struct-inspection attempt which failed on this release build's
member-layout debug info) resolves this: `CallTraceStorage` is
triple-buffered (`_active_storage`/`_standby_storage`/`_scratch_storage`),
each with its own chunk-based allocator. Four distinct 8 MiB
(`CALL_TRACE_CHUNK`-sized) anonymous regions were found with dramatically
different residency:

| Chunk | Size | Resident (Rss) | % resident |
|---|---|---|---|
| A | 8.0 MiB | 8,192 KB | **100%** |
| B | 8.0 MiB | 1,028 KB | 12.5% |
| C | 8.0 MiB | 32 KB | 0.4% |
| D | 8.0 MiB | 12 KB | **0.15%** |

One chunk (the actively-written buffer) is fully resident; the other three
(older, rotated-out generations kept alive for in-flight sample continuity)
sit mostly on untouched anonymous zero-pages. **`NM_CALLTRACE`'s counter
tracks allocated capacity, not resident memory** — worth remembering for
capacity planning with this or any counter backed by `OS::safeAlloc`.
Extrapolating the ~28% residency ratio from these 4 chunks (9.06 MiB
resident of 32 MiB logical) gives a rough estimate of ~10–15 MiB true RSS
contribution — not an exhaustive measurement (only 4 of an estimated ~6
chunks were positively identified).

**Net result at this point**: redoing the original derivation with this —
56.9–66.9 MiB NMT-invisible total (depending on whether Java Heap's noise
is included) minus ~10–15 MiB true `NM_CALLTRACE` cost — landed the
residual around ~42–57 MiB. That range itself was never a real confidence
interval, though — it was built from a 10-rep sweep whose own per-condition
stdev (±89 MB) was large relative to the effect being measured. The
following re-measurement addresses that directly.

### Tightening the residual: a fixed-heap re-measurement

Every recalibration pass up to this point re-mined the *same* 10-rep
default-heap dataset rather than collecting new, less noisy data — so the
~42–57 MiB range inherited whatever imprecision was baked into that
original sweep, without ever being checked. That sweep's own numbers make
the concern concrete: at N=150,000, RSS was 1966.2 ± 89.0 MB (agent) vs.
1863.8 ± 89.9 MB (no agent) over 10 reps — if the two conditions varied
independently, the delta's own standard error would be ~40 MB, making the
"102.4 MB" headline only a ~2.5σ signal, not the precise number the prose
elsewhere implies. None of the five ruling-out checks above re-measured
the residual itself at tighter precision; they measured other quantities
(`mallinfo2`, Code cache, `CallTraceStorage` residency) and subtracted
estimates, so the noise in the original RSS delta flows straight through
into the residual's uncertainty.

The likely dominant noise source was identifiable directly from the
original sweep's own NMT breakdown: "Java Heap" swung ~240 MB across 5 reps
of the *same* condition in the jmethodID toggle test (already flagged as
noise there), and the class-diversity sweep never set `-Xms`/`-Xmx` at all
— every rep ran under default ergonomic heap sizing, with GC/heap-resize
timing free to vary rep to rep. Re-running the same N=150,000 with/without
comparison with `-Xms512m -Xmx512m -XX:+AlwaysPreTouch` added (forcing both
conditions to commit and fully touch an identical, fixed-size heap up
front, removing that timing variable entirely), 12 reps, interleaved
batches as before, using
`doc/performance/memsweep/run_repeated_sweep_fixedheap.sh` (same structure as
`run_repeated_sweep.sh`, plus a `HEAP_FLAGS` env var):

| | RSS mean | RSS stdev | vs. original stdev |
|---|---|---|---|
| with-agent | 1867.7 MiB | **6.3 MiB** | was ±89.0 MiB |
| without-agent | 1788.9 MiB | **11.3 MiB** | was ±89.9 MiB |

Roughly a 10x reduction in per-condition noise from one change. The
**paired** per-rep delta (with − without, same rep) — the statistic that
actually matters, and one the original sweep never explicitly reported —
came out to **78.77 MiB, stdev 13.4 MiB, standard error 3.86 MiB** (12
reps). Dropping the single lowest rep (47.0 MiB, the one visible outlier)
barely moves the mean (78.8 → 80.8 MiB), confirming it's not distorting
the result.

The absolute magnitude (78.77 MiB) differs from the original 102.4 MiB
headline, which is expected, not contradictory: fixing the heap
mechanically zeroes out Java Heap's category delta (previously +10.4 MiB,
already flagged as noise), and the original 102.4 MiB point estimate
carried enough of its own sampling noise (~±40 MiB SE) that a ~24 MiB
difference from a much tighter re-measurement isn't a surprising
discrepancy.

Redoing the NMT category breakdown on this same fixed-heap data (paired
per-rep, not just per-condition):

| NMT category | Original (10 reps, unfixed heap) | Fixed-heap (12 reps, paired) | Fixed-heap stdev |
|---|---|---|---|
| Class | +13.6 MB | **+13.50 MiB** | ±0.46 MiB |
| Internal | +11.6 MB | **+11.36 MiB** | ±0.06 MiB |
| NMT (own bookkeeping) | +10.3 MB | **+10.20 MiB** | ±0.16 MiB |
| Java Heap | +10.4 MB (flagged as noise) | **0.00 MiB** | — (mechanically zero) |

The three jmethodID-driven categories reproduce almost exactly, but now
with sub-MiB stdevs instead of implied tens-of-MB noise — strong
confirmation that this ~35 MiB piece is a real, heap-size-independent
effect. Java Heap going to exactly zero (rather than just "closer to
zero") confirms its old +10.4 MiB contribution really was pure GC/heap-
resize timing noise, as suspected but never proven. NMT-visible total:
Class + Internal + NMT-own = **35.06 MiB**.

`NM_CALLTRACE`'s logical size, read directly from this run's JFR file, is
50,858,496 bytes (48.5 MiB) — bit-for-bit identical to the original sweep,
confirming it's driven by touched call-trace shapes, not heap size, as
expected. Its *residency* was previously only extrapolated (4 of an
estimated ~6 `CALL_TRACE_CHUNK`s positively identified, ~28% average
residency assumed to generalize). Re-checking `/proc/<pid>/smaps` directly
on a fresh live fixed-heap run instead of extrapolating: the same 4-chunk
pattern reproduced to within 10 KB of the original measurement (100% /
12.5% / 0.4% / 0.15% resident, 9.05 MiB total resident of 32 MiB logical).
A further 32 MiB anonymous region was found at 0.1% residency (24 KB
resident) — its size is consistent with covering the remaining ~2
unidentified chunks, and its residency is low enough that even
attributing it entirely to `CallTraceStorage` adds only ~24 KB. This
replaces the previous **10–15 MiB extrapolated estimate** with a directly
measured **~9.05–9.1 MiB** — tighter, and no longer dependent on assuming
the unidentified chunks behave like the identified ones.

**Result**:

```
Residual = Total RSS delta − NMT-visible − CallTraceStorage resident
         = 78.77 MiB − 35.06 MiB − 9.07 MiB
         ≈ 34.6 MiB, SE ≈ 3.9 MiB (dominated by the RSS-delta term)
```

**~34.6 MiB ± ~3.9 MiB**, versus the original **~42–57 MiB with no stated
confidence interval**. The new figure sits inside the old range, so this
isn't a reversal — it's the same effect, now with an actual error bar
instead of a band inherited from an unexamined noisy dataset. The
practical conclusion: there is a real, non-noise, agent-attributable
residual of roughly 30–40 MiB at N=150,000 — not a measurement artifact,
and not as uncertain as "42–57 MiB" made it sound, but its *mechanism*
remains exactly as unknown as before. Tightening precision was the goal of
this pass, not localization; see "Caveats and open questions" for what a
follow-up mechanism hunt (e.g. a full smaps region inventory, with vs.
without) would need to do next.

### Instrumenting the remaining allocation sites directly (negative result)

The five techniques above each ruled something out by inference — none
directly instrumented the allocation sites they suspected. This pass adds
real `NativeMem` counters at the eight sites identified as plausible
contributors (a `CountingAllocator<T, Category>` wrapping `::operator
new`/`delete` for STL containers, plus direct `record()`/`setLive()` calls
for raw-`malloc` structures), giving two new categories —
`NM_METHOD_MAP` (`Recording::_method_map`) and `NM_LIVENESS`
(`LivenessTracker::_table`) — alongside additions to the existing
`NM_THREAD_LOCAL` (`UnwindFailures`, `ThreadInfo`'s two maps),
`NM_JFR_BUFFERS` (`Lookup::_vtable_receiver_cache`), `NM_CALLTRACE`
(`CallTraceStorage`'s two working buffers), and `NM_MISC` (wall-clock's
thread-reservoir vector, `setLive`-gauged rather than allocator-wrapped).
A `CodeCache::setDwarfTable()` fix trims the DWARF/SFrame `FrameDesc` table
to its exact length via `realloc`, eliminating the capacity-doubling slack
that previously lingered in real RSS undetected.

Re-running the same `classes 150000`, `wall=~1ms` workload with this
instrumentation and reading the counters directly, instead of estimating:

| Category | Value | Note |
|---|---|---|
| `NM_THREAD_LOCAL` | 5.92 MB | includes `UnwindFailures`'s fixed +294,912 B, previously invisible |
| `NM_MISC` | 8,192 B | wall-clock reservoir vector capacity, previously always 0 (no call sites) |
| `NM_CALLTRACE` | 50.89 MB | ~33 KB above the pre-instrumentation baseline (50,858,496 B) — `CallTraceStorage`'s two working buffers are real but tiny |
| `NM_JFR_BUFFERS` | 1.21 MB | unchanged from baseline — `_vtable_receiver_cache` stays empty for this workload (no `BCI_ALLOC` frames) |
| `NM_LIVENESS` | 0 | expected: `LivenessTracker` is an allocation-profiling feature, inactive for this wall-clock-only workload |
| `NM_METHOD_MAP` | 0 in a single-chunk read; **13.15 MB** with a forced mid-run `dump()` | see below |

**The newly-instrumented sites add at most ~340 KB to steady-state
accounting** (dominated by `UnwindFailures`'s fixed 288 KiB table) — about
1% of the ~34.6 MiB residual. This is a genuine negative result: the plan's
premise — that these eight sites were plausible hiding places for the
residual — turns out to be wrong for seven of the eight. They're real,
newly-visible allocations, just not big ones.

**`NM_METHOD_MAP` is the one site large enough to matter, and it doesn't
count either — but for a timing reason, not a magnitude reason.**
`Recording::_method_map` is only populated by `Lookup::resolveMethod()`
during `writeCpool()`, which runs *after* that same chunk's `NM_*` counter
snapshot (`flightRecorder.cpp`'s `finishChunk()`: `updateNativeMemStats()`/
`writeNativeMem()` at lines ~820/822, `writeCpool()` at line ~835) — the
exact same deferred-write pattern already documented above for
`NM_DICTIONARY`. A single continuous recording (this profiler's default)
only ever runs that path once, at process exit, so `_method_map` is
essentially empty at the moment the fixed-heap protocol's RSS/NMT snapshot
is taken (~1 second before the workload's own deadline, well before
process exit). Forcing an intermediate `dump()` at 177s of a 180s run (the
same technique already validated for `NM_DICTIONARY`, reproducing its
prior ~236 MB reading to within ~0.6%) makes the growth visible in the
final chunk: **13.15 MB**, in the same neighborhood as the earlier
`mallinfo2()` probe's ~16.02 MB estimate (the gap is plausibly the same
~56% stack-trace coverage at N=150,000 already documented above — not
every generated method necessarily gets resolved into a stack trace
that survives to the forced dump). Either way, **this memory is real, but
it materializes at JFR chunk-flush time, not during steady-state
execution** — it's temporally disjoint from the residual being measured,
not a hidden contributor to it.

**The `CodeCache` fix doesn't show up in `NM_NATIVE_SYMBOLS` either, for a
related reason: `memoryUsage()`'s formula is `length * sizeof(FrameDesc)`
regardless of whether the underlying buffer was shrunk to match.** Reverting
the `realloc`-shrink and rebuilding confirmed this directly — `NM_NATIVE_SYMBOLS`
read 12,481,568 B without the fix vs. 12,481,616 B with it, a 48-byte
difference that's clearly noise, not the ~30-50% overallocation the fix
targets. The fix's real effect is on the actual malloc'd block size, which
this gauge was never computing from in the first place. A single unpaired
comparison of total process RSS between the two builds (2,132,604 KB
without the fix vs. 2,116,940 KB with it, same workload, default
unfixed-heap ergonomics) suggested ~15 MB lower RSS with the fix applied —
directionally consistent with removing doubling slack — but this wasn't run
under the fixed-heap protocol that cut per-condition noise from ~89 MB to
~6-11 MB elsewhere in this document, so it isn't strong evidence on its
own. The fix is real and correct (it makes the accounting formula and the
actual allocation agree, and can only reduce real RSS, never increase it),
but this pass doesn't produce a rigorously confirmed magnitude for it.

**Net conclusion: the ~34.6 MiB (±3.9 MiB) residual remains unexplained.**
This pass closes out the plan's premise rather than confirming it — all
eight identified sites are now instrumented with real, byte-exact counters,
and none of them turn out to be sitting in the residual's steady-state
window. The residual's mechanism is still open; per the "Caveats" section
below, a full `smaps` region inventory (with vs. without the agent) remains
the most direct next step, since it doesn't depend on guessing which
category to instrument next.

### Ruling out arena-level fragmentation as the residual's mechanism (malloc_info + malloc_trim)

The eight-site instrumentation pass above closed out every allocation site
anyone had a concrete hypothesis for, but left the ~34.6 MiB residual's
mechanism unknown. A remaining possibility: maybe it isn't a missing
*counter* at all, but a mismatch between what any byte-counting
instrumentation can see (logical requested bytes, which is all
`CountingAllocator` or any `malloc`-request-counting shim can ever measure)
and what glibc actually holds resident — chunk headers, 16-byte alignment,
per-thread arena reservation, fragmentation. Three techniques tested this,
all under the fixed-heap `classes 150000` protocol:

1. **`MALLOC_ARENA_MAX=1` differential (8 clean paired reps).** Forcing
   glibc to a single process-wide arena eliminates any per-thread-arena
   proliferation effect. Paired RSS delta: 70.61 MiB (±2.73 MiB SE, n=8) vs.
   the established unrestricted-arena baseline of 78.77 MiB (±3.86 MiB SE,
   n=12) — an ~8 MiB (~10%) reduction, only ~1.7σ given the combined SE, so
   suggestive but not conclusive on its own. (A follow-up batch of 4 more
   reps was accidentally run concurrently with an unrelated background job
   and was discarded: one rep showed a physically impossible negative
   with-vs-without delta — proof of CPU-contention corruption — so the
   whole batch was untrustworthy by association and not merged in.)

2. **`/proc/<pid>/smaps` region inventory (single with/without pair, default
   arenas).** Java heap (510 MiB), metaspace/class-space (220.75 MiB), and
   CodeCache (116.31 MiB) regions were byte-identical between conditions,
   confirming the fixed-heap protocol controls what it should. The entire
   RSS delta for this pair (65.9 MiB) lived in additional/larger anonymous
   mmap regions. The count of large (~60-64 MiB, glibc-arena-sized)
   committed regions was similar between conditions (~11 vs. ~9-10) —
   arguing against simple arena-*count* proliferation. One ~91 MiB
   fully-resident anonymous region was unique to the "with" condition, but
   `smaps` can't name anonymous regions, so it couldn't be attributed to
   anything specific from this alone.

3. **`malloc_info()` + `malloc_trim(0)` direct probe (single with/without
   pair, default arenas) — decisive.** Built a small LD_PRELOAD shim
   (`doc/performance/memsweep/malloc_info_probe.c`) that, on receiving
   `SIGRTMIN+10`, dumps `malloc_info()` to a file, calls `malloc_trim(0)`,
   then dumps `malloc_info()` again. (`SIGRTMIN+10` was chosen after
   `SIGUSR2` silently failed — HotSpot claims `SIGUSR2` as its own
   suspend/resume signal on Linux and intercepted it before the LD_PRELOAD
   handler ever ran, confirmed via the JVM's own "stray SR signal"
   warning.) Findings:
   - Arena count: 44 (with) vs. 42 (without) — not a meaningful
     proliferation.
   - Total committed arena memory (`system` bytes): 441.65 MiB (with) vs.
     373.54 MiB (without), a 68.11 MiB delta, concentrated almost entirely
     in one arena (344.9 MiB vs. 274.83 MiB, a 70.07 MiB difference by
     itself) — plausibly the main arena.
   - Free bytes sitting in bins (`fast`+`rest` totals) were nearly
     identical between conditions (~65.7 MiB vs. ~71.4 MiB), both before
     and after the trim.
   - **`malloc_trim(0)` changed `system_current` by ~0.01 MiB in both
     conditions.** Since `malloc_trim` can only release memory the
     allocator has already determined is unused (unconsolidated top-chunk
     tail, some free-list consolidation), a near-zero effect means the
     ~68-70 MiB gap is **live, in-use allocated memory — not reclaimable
     slack or fragmentation waste.**

**Conclusion: the RSS-vs-counters alignment/fragmentation/arena-waste
hypothesis is ruled out.** The gap between conditions is real, live,
currently-allocated memory that glibc itself considers in use, not a
phantom accounting artifact. This is consistent with (not contradictory
to) everything measured earlier: HotSpot's own NMT-tracked categories
(Internal, Class, etc. — the already-explained ~35 MiB portion of the total
delta) also allocate via `os::malloc`, which routes through the same glibc
arenas, so this arena-level delta plausibly represents "already-known
NMT-visible allocations (~35 MiB) + the still-unexplained residual
(~34.6 MiB)" landing in the same arena — not a new, separate ~70 MiB
mystery on top of everything else measured so far.

**Where this leaves the investigation:** the residual is a real, live,
currently-unidentified allocation (or set of allocations) that goes through
plain `malloc`/`new` without being wrapped by any of the `NativeMem`
counters checked so far (the eight sites from the prior pass are all
confirmed <1 MB combined at steady state). `malloc_info()` cannot identify
*which* call site is responsible — it only histograms free (not in-use)
chunks, by construction. The next tool that could actually attribute live
bytes to a call site would be a `malloc`/`free` LD_PRELOAD shim keyed by
captured backtrace (heavier than anything tried so far, since it has to
survive being invoked from inside libc's own allocator), or an external
tool like `heaptrack`/`valgrind --tool=massif` if available in the
environment — neither has been tried yet.

## Practical implications

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
   via reflection. This internal step function is only a small part of the
   externally-visible RSS cost — see point 5.
3. **Class/method-name diversity genuinely grows the class-name dictionary
   under both sampling engines — but `NM_DICTIONARY` only shows it promptly
   for one of them.** Allocation sampling's growth is visible in the same
   chunk it happens in; wall-clock sampling's is just as real (~140–235 MiB
   for `classes 150000` depending on test construction, confirmed as
   genuine physical memory via direct RSS instrumentation) but is only ever
   visible in a subsequent chunk's counter reading, by design. Don't read a
   flat `NM_DICTIONARY` in a wall-clock-sampled, single-chunk session as "no
   class-name diversity cost" — the cost may simply not have been reported
   yet. This growth is gated behind chunk writes and is a separate,
   additive cost from the steady-state overhead in point 5, not a hidden
   component of it.
4. **Call-trace storage and the class-name dictionary have different
   lifetimes across a JFR chunk rotation** (observed once, not
   independently re-verified). Call-trace memory is bounded per rotation
   window; class-name dictionary memory can accumulate across rotations up
   to its capacity cap — a meaningfully different long-term profile for two
   structures that otherwise look similar.
5. **For quantifying total profiler-attributable RSS overhead to a
   customer, call-graph diversity is the dimension that matters — and
   specifically, the number of distinct *methods* actually appearing in
   sampled stacks, not the number of distinct classes.** A dedicated
   with/without-agent sweep at fixed methods-per-class found: effectively
   0 MB overhead at 2,000 distinct classes sampled, growing roughly
   linearly with sampled-class count to ~102 MB at 150,000. A follow-up
   holding class count fixed at 2,000 while adding methods (100 instead of
   1) reached ~74 MB — confirming it's touched-method count, not class
   count, doing the work; the first sweep's "classes" and "methods" moved
   together only because that benchmark gave every class exactly one
   method. A workload with a narrow call graph stays near the small-and-
   flat regime regardless of how many classes or threads exist; a workload
   with a wide call graph (many distinct methods actually invoked, whether
   spread across few classes or many) does not, and this is the dimension
   worth asking a customer about before quoting a number. **This ~102 MB
   figure is steady-state only** — sampled while the process runs, before
   any chunk write — and does not include the chunk-flush burst from
   point 3. (This specific N=150,000 point was measured under default,
   unfixed JVM heap sizing and carries a wide confidence interval as a
   result — see "Tightening the residual: a fixed-heap re-measurement"
   under "Investigating the unattributed remainder" for a 12-rep
   fixed-heap redo landing at ~79 MiB with a ±3.9 MiB standard error. The
   qualitative touched-method-count conclusion here doesn't depend on
   which heap methodology was used.)
6. **A long-running process that rotates JFR chunks periodically (not just
   a single continuous recording to process exit) pays the point-3
   chunk-flush burst on top of the point-5 steady-state number, once per
   rotation** — at `classes 150000`, roughly another ~140–235 MB. Since
   dictionary content persists across rotations (point 4) up to its
   capacity cap, later rotations may see a smaller incremental burst as it
   saturates — untested. For this profiler's default single-continuous-file
   mode, this burst happens once, at process exit, with no effect on the
   running process; for any configuration that rotates chunks periodically
   during normal operation, it's a real, recurring cost the steady-state
   number alone would not predict.

## Caveats and open questions

- **Single sandboxed Linux x86_64 container throughout.** Most sweep points
  in this document are a single run each — indicative, not statistically
  rigorous. The class-diversity with/without-agent comparison is the
  exception (10 reps per condition per N, default heap; 12 reps at
  N=150,000 under a fixed-heap redo — see "Tightening the residual" above);
  treat single-run figures elsewhere with more caution than those.
- **`NM_PERF` remains unverified in practice**, though the reason is
  understood (see above) — a root-accessible bare-metal or VM Linux host
  with relaxed `kptr_restrict` would be needed to close this out.
- **The `allocs` mode is new and lightly calibrated** — two data points is
  enough to see the engine-difference and the plateau pattern, but not
  enough to pin down its resize threshold the way `traces`/`classes` are
  pinned down for wall-clock sampling.
- **`nativemem=` (native malloc tracing) was only smoke-tested**, not
  characterized against a dedicated native-allocation-heavy workload.
- **The `allocs` engine's dictionary-insertion path is inferred from timing
  behavior, not traced to a specific call site** — unlike the wall-clock
  path, which is fully identified and confirmed.
- **The thread-count with/without-agent comparison is a single run per
  point** (unlike the class-diversity one, which has 10) — treat the
  overall "small, roughly flat" conclusion as solid but individual
  KB-level numbers as indicative only.
- **"Java Heap"'s behavior under the jmethodID-preloading toggle is
  unresolved** — it moved in the *opposite* direction when preloading was
  disabled, but swung ~240 MB across 5 reps of the *same* condition, too
  noisy to attribute in either direction at practical rep counts. Worth
  repeating with many more reps, or a less noisy measurement approach.
- **The exact mechanism for the ~34.6 MB (±3.9 MB SE) unattributed
  remainder is still unknown**, despite five independent lines of
  investigation (all detailed under "Investigating the unattributed
  remainder" above), a sixth pass that tightened the magnitude's precision
  without localizing it further, and a seventh pass ("Instrumenting the
  remaining allocation sites directly") that added real byte-exact counters
  at all eight previously-uninstrumented allocation sites identified as
  plausible contributors — all eight are now ruled out (seven contribute
  well under 1 MB combined at steady state; the eighth, `NM_METHOD_MAP`, is
  real but only materializes at JFR chunk-flush time, outside the residual's
  measurement window). The pattern across all these checks — each either
  ruled out or shown to already be counted elsewhere — suggests the residual
  is unlikely to be additional profiler-`.so`-attributed `malloc`/`new`
  activity from any currently-known allocation site, glibc fragmentation, or
  JIT code-cache growth. An eighth/ninth/tenth pass ("Ruling out arena-level
  fragmentation" above) then directly tested the RSS-vs-counters angle via
  `MALLOC_ARENA_MAX=1`, a `/proc/<pid>/smaps` region inventory, and an
  in-process `malloc_info()`/`malloc_trim(0)` probe — the last one decisive:
  the with/without gap is real, live, in-use memory (`malloc_trim` reclaimed
  ~0 of it), not fragmentation or arena-count proliferation. So the residual
  is a genuine, currently-unattributed live allocation, and the remaining
  open question is purely "which call site" — `malloc_info()` can't answer
  that (it only histograms *free* chunks). Worth checking next: a
  `malloc`/`free` LD_PRELOAD shim keyed by captured backtrace (heavier than
  anything tried so far), or `heaptrack`/`valgrind --tool=massif` if
  available in the environment; whether other profiler structures use
  `OS::safeAlloc` (raw `mmap`, sparse-residency-prone) the way
  `CallTraceStorage` does, since their counters would have the same
  logical-vs-resident gap that complicated the `NM_CALLTRACE` analysis;
  and/or tracing the per-thread/shard `StringDictionaryBuffer` buffering
  mechanism directly to understand why the chunk-flush burst is an order of
  magnitude larger than raw string content (~2 MB for 150,000 short names)
  would predict.
- **Coverage (classes actually touched by a sample) fell from 93.6% at
  N=2,000 to 56.4% at N=150,000** for the same relative duration/interval
  scaling used across this sweep. The per-touched-class normalization is
  more stable than per-raw-N, but wasn't tested against durations tuned to
  hold coverage constant across N, which would isolate the class-count
  effect from the duration/coverage confound more cleanly.
- **How jmethodID preloading's own NMT-visible contribution (the confirmed
  ~35 MB piece) responds to methods-per-class specifically is still
  unresolved**, even though the *aggregate* driver is now confirmed to be
  touched methods rather than touched classes (see "Isolating what the
  profiler itself adds: class diversity" above). This mechanism fires per
  `ClassPrepare`, once per class, regardless of sampling — so on its own
  terms it should scale with total methods across all *loaded* classes,
  not just touched ones. A direct check (NMT category deltas at 1 vs. 5
  methods per class, same N) didn't give a clean answer — the category-
  level deltas were noisier than the aggregate RSS figure at that specific
  configuration, in some cases flipping sign. Worth revisiting with a
  larger methods-per-class contrast (the same fix that resolved the
  aggregate question) rather than treating the noisy 5x attempt as
  conclusive either way.
