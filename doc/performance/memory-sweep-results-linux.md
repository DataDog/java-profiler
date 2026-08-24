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

## Summary

**What drives memory overhead.** Thread count adds a small, linear cost
(~824 B/thread inside the profiler); the much larger ~400 KB/thread RSS
growth beside it is JVM/OS thread machinery the profiler neither causes nor
can see into. The dimension that actually matters for customer-facing sizing
is **the number of distinct *methods* appearing in sampled stacks** — not
classes, not threads. A narrow call graph costs close to nothing at any
scale; a wide one (framework-heavy, generics/lambda-heavy, microservice-style
code) costs ~0.8–1.4 KB per touched method, reaching ~102 MB at 150,000
touched methods.

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

| N threads | max RSS | `NM_THREAD_LOCAL` (all N alive) | `NM_THREAD_FILTER` |
|---|---|---|---|
| 1 | 70 MiB | 6,592 B | 40 KiB |
| 16 | 76 MiB | 18,952 B | 40 KiB |
| 64 | 99 MiB | 68,392 B | 40 KiB |
| 256 | 172 MiB | 226,600 B | 72 KiB |
| 1000 | 442 MiB | 839,656 B | 136 KiB |

`NM_THREAD_LOCAL` scales linearly at **824.0 B/thread**, matching
`sizeof(ProfiledThread)` (its OTel context record alone is ~688 B per the
layout comment in `threadLocalData.h`). `NM_THREAD_FILTER` steps at 256-slot
chunk boundaries. `NM_CALLTRACE`/`NM_DICTIONARY`/`NM_NATIVE_SYMBOLS` are flat
across the whole sweep — no call-trace or class-name diversity here.

RSS grows ~381 KB/thread, about 460× the profiler's own contribution. That
gap is JVM/OS thread machinery.

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
   and predictable. The ~400 KB/thread beside it is JVM/OS overhead that
   cannot be optimized from the profiler's side.
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
- **The free-but-held arena term needs more reps** before its magnitude is
  quoted; its existence is established, its ~7.6 MiB mean is ~2.5σ.
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
