# Native Memory Usage Model

This document predicts the native (off-heap) memory footprint of the
java-profiler agent itself — the memory its C++ library consumes in the target
JVM's process, separate from the JVM's own heap. It is a *model*: structure
sizes and scaling terms derived from reading `ddprof-lib/src/main/cpp`, with
constants calibrated against measurement.

> **Calibrated against measurement.** The empirical pass is in
> [memory-sweep-results-linux.md](memory-sweep-results-linux.md) (Linux x86_64,
> JDK 21 — the current and more complete one); an earlier macOS arm64 pass is in
> [memory-sweep-results.md](memory-sweep-results.md). Constants below marked
> **(measured)** come from that work; ones marked *(from source)* are still
> struct-layout arithmetic. An earlier revision of this document warned that the
> call-trace and class/method terms were "not visible in the `NM_*` counters at
> all" — that is no longer true, and both terms are now calibrated.

The accounting instrumentation is `nativeMem.h/.cpp` (originally
[#669](https://github.com/DataDog/java-profiler/pull/669)), with eleven
categories: `NM_CALLTRACE`, `NM_DICTIONARY`, `NM_THREAD_FILTER`,
`NM_NATIVE_SYMBOLS`, `NM_LINE_TABLES`, `NM_PERF`, `NM_THREAD_LOCAL`,
`NM_JFR_BUFFERS`, `NM_METHOD_MAP`, `NM_LIVENESS`, `NM_MISC`.

## Baseline (fixed) footprint

Allocated once, at agent load / profiler start, regardless of workload size or
activity.

| Item | Constant(s) | Location | Size |
|---|---|---|---|
| **Call-trace arena** | 3 × `CALL_TRACE_CHUNK` (8 MiB), triple-buffered | `callTraceHashTable.cpp:18` | **24.5 MiB** (measured) |
| **Native-symbol tables** | one `CodeCache` per loaded native library | `codeCache.cpp` | **13.03 MiB** (measured) |
| **Class-name dictionary** | 3 × `StringDictionary` initial arena | `stringDictionary.h` | **4.55 MiB** (measured) |
| **JFR recording buffers** | 16 shards × (64 KiB + 8 KiB overflow) | `flightRecorder.h` | **1.16 MiB** (measured) |
| Thread filter, first chunk | `kChunkSize`=256 slots | `threadFilter.h:42` | 40 KiB (measured) |
| Library-patcher static tables (Linux) | ~12,288 entries × 24 B | `libraryPatcher.h` | ~288 KiB *(from source)* |
| Call-trace scratch buffers | 16 shards × 2058 frames × 16 B | `profiler.h` | ~515 KiB *(from source)* |
| Thread-ID tables | 16 shards × 2 × 256 × 4 B | `threadIdTable.h` | 32 KiB *(from source)* |
| Native-lib pointer table | `MAX_NATIVE_LIBS`=2048 × 8 B | `codeCache.h:27` | 16 KiB *(from source)* |
| Per-shard spinlocks | `CONCURRENCY_LEVEL`=16 × 64 B | `flightRecorder.h:47` | ~1 KiB *(from source)* |
| Compiled agent binary | — | build output | 1.31 MiB |

**Baseline total: ~43 MiB**, present before a single application thread is
profiled.

Two things this corrects. The call-trace line is not the 65,536-slot hash
table (~1.05 MiB) but the **8 MiB arena chunks backing it**, triple-buffered —
a ~24× difference, and the single largest fixed cost. And the native-symbol
tables are ~13 MiB that an earlier revision of this model omitted entirely.

**`NM_NATIVE_SYMBOLS` is environment-dependent, not a universal constant.** It
scales with how many native libraries the process has loaded and how many
symbols they export, so 13.03 MiB is this container's figure, not a portable
one. Everything else in the table is genuinely fixed.

**24 MiB of the baseline is `mmap`, not `malloc`.** The call-trace arena comes
from `OS::safeAlloc`, a raw `mmap` syscall, and it is **sparsely resident** —
of the 48.5 MiB the counter reports at high diversity, only ~19.9 MiB is
actually resident. Treat `NM_CALLTRACE` as a virtual-capacity figure and halve
it for RSS purposes.

## Variable costs, by workload property

### 1. Thread count / thread churn — O(threads ever seen)

- `ProfiledThread` (thread-local): **824 B/thread** (measured; ~650 B was the
  earlier struct-layout estimate). Linear and highly predictable.
- `ThreadFilter::Slot` — allocated in 256-slot chunks (`kChunkSize`), capped
  hard at `kMaxThreads` = 2048 (`threadFilter.h:42-45`). Observed stepping
  40 → 72 → 136 KiB.
- `ThreadInfo` name/id maps grow with threads **ever seen**, not concurrently
  alive — so thread-per-request styles and recreated executor pools accumulate
  over process lifetime.

Note that observed RSS grows ~400 KB/thread, roughly 460× the profiler's own
824 B. That difference is JVM/OS thread machinery, not agent cost.

### 2. Distinct methods in sampled stacks — the dominant term

This is the dimension that matters, and it is **methods, not classes**. A
workload's cost tracks the number of distinct methods actually appearing in
sampled stacks; raw class-loading volume with a narrow call graph costs
essentially nothing.

- `CallTraceHashTable` doubles capacity at 75 % fill — i.e. once ≥49,152
  distinct call-trace shapes are recorded — taking `NM_CALLTRACE` from 24.5 to
  48.5 MiB.
- `MethodMap`, `Dictionary`, `StringDictionary` grow with unique
  methods/classes/strings.

**Measured rate: ~0.8–1.4 KB per touched method** (0.78 KB at 96,953 methods,
1.24 KB at 84,640, 1.38 KB at 16,311). Effectively zero below ~2,000 touched
methods.

### 3. Loaded classes / native libraries — O(unique symbols)

- `CodeCache` native-library symbol tables, capped at `MAX_NATIVE_LIBS` = 2048.
  This is the 13 MiB baseline item; it grows only when new native libraries are
  loaded, not with Java class loading.

### 4. Sampling / allocation event rate — mostly fixed buffers

JFR recording buffers are fixed in count and size; what scales is *flush
frequency*, which affects churn rather than steady-state size.
`mallocTracer`'s PID controller self-tunes to hold event volume roughly
constant regardless of raw allocation rate.

### 5. Contexts / active spans — folded into thread cost

The former DirectByteBuffer-based per-span context storage was removed; context
data lives inline in the fixed-size per-thread record, so this is O(threads),
not O(active spans).

## Costs this model does not express

Two effects are large and are not additive terms in the formula below.

**JFR chunk-flush burst.** Serialization is expensive and transient-plus-sticky:
one flush at 150,000 classes takes `NM_DICTIONARY` from 4.55 MiB to a
**216.62 MiB peak, settling at 162.46 MiB that it keeps**, and builds
`NM_METHOD_MAP` from nothing to 13.32 MiB. This is *not* included in any
steady-state number here. For the default single-continuous-recording mode it
is paid once, at process exit, with no effect on the running process; any
configuration that rotates chunks periodically pays it per rotation. Note the
asymmetry across a rotation: call-trace memory is bounded per rotation window,
while dictionary content **accumulates** across rotations up to
`MAX_CLASS_MAP_SIZE`.

**Counters undercount RSS, structurally.** The `NM_*` categories record
*logical* bytes; RSS pays for malloc chunks. At the profiler's allocation
profile (~83 B mean, hundreds of thousands of live allocations) that is ~17 %
inflation, plus unreclaimable free arena pages glibc holds. Budget roughly
**+15–20 % on top of the counter sum**, and separately remember that
`NM_CALLTRACE` runs the other way, overstating residency by ~2×.

## Rough formula

Additive, ignoring interaction effects and doubling thresholds:

```
Memory(MiB) ≈ Baseline
            + Threads        × C_thread    (824 B/thread, measured)
            + TouchedMethods × C_method    (~0.8-1.4 KB/method, measured)
```

Where:

- **Baseline** ≈ 43 MiB, of which ~24 MiB is sparsely-resident `mmap`
- **Threads** = distinct thread IDs seen over the session, not peak concurrency
  (the `ThreadFilter` component alone caps at 2048)
- **TouchedMethods** = distinct methods actually appearing in *sampled stacks* —
  not methods loaded, and not classes. Below ~2,000 this term is ~0.

Then add the chunk-flush burst if the deployment rotates JFR chunks, and the
~15–20 % counter-to-RSS gap if you are predicting RSS rather than counter
totals.

Worked example at the calibration point: 43 (baseline) + 84,640 × 1.24 KB
(≈105 MB) ≈ 148 MB predicted against ~102 MB of measured *delta* — the model
over-predicts here because the 43 MiB baseline is present in both the with- and
without-agent conditions of that comparison and so cancels out of the delta.
**Use the baseline term when sizing absolute footprint; drop it when comparing
against a with/without-agent measurement.**

## Practical implications for workload characterization

In rough order of impact:

1. **Call-graph breadth — the number of distinct methods appearing in sampled
   stacks.** This dominates. Proxies, lambdas, generic instantiations and
   heavy framework use (Spring, reflection-based serialization) raise it
   independently of load; a high-throughput service with a narrow hot path
   does not.
2. **Total distinct thread IDs** created over the profiling window, including
   churn — small per thread, but linear and unbounded in churn-heavy designs.
3. **Whether the deployment rotates JFR chunks**, which decides whether the
   flush burst is a one-off at exit or a recurring cost.
4. **How many native libraries the process loads**, which sets the
   `NM_NATIVE_SYMBOLS` baseline.
5. Sampling frequency and allocation rate are secondary — they mostly affect
   transient churn, not steady-state footprint, because of fixed buffer sizes
   and adaptive sampling.
