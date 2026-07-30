# Native Memory Usage Model

This document estimates the native (off-heap) memory footprint of the java-profiler
agent itself — i.e. the memory the profiler's C++ library consumes in the target
JVM's process, separate from the JVM's own heap. It is intended as a starting point
for predicting agent memory usage from workload characteristics, based on reading
`ddprof-lib/src/main/cpp` and the memory-accounting instrumentation added in
[#669](https://github.com/DataDog/java-profiler/pull/669) (`nativeMem.h/.cpp`,
categories `NM_CALLTRACE`, `NM_DICTIONARY`, `NM_THREAD_FILTER`, `NM_NATIVE_SYMBOLS`,
`NM_LINE_TABLES`, `NM_PERF`, `NM_THREAD_LOCAL`, `NM_JFR_BUFFERS`, `NM_MISC`).

> An empirical calibration pass against this model — sweeping thread count,
> call-trace diversity, and class/method diversity and measuring actual RSS
> and `NM_*` counters — is in [memory-sweep-results.md](memory-sweep-results.md).
> It confirms the thread-count scaling below but found the call-trace and
> class/method terms are not currently visible in the `NM_*` counters at all;
> treat those two terms in the formula as unverified.

All byte figures are approximate (64-bit build, computed from struct layouts and
constants in the source, not measured with a profiler) and are meant to establish
orders of magnitude and scaling behavior, not exact numbers.

## Baseline (fixed) footprint

These allocations happen once, at agent load / profiler start, regardless of the
size or activity of the workload being profiled.

| Item | Constant(s) | Location | Approx. size |
|---|---|---|---|
| Per-shard spinlocks | `CONCURRENCY_LEVEL=16`, `SpinLock`=64B | `profiler.h` | ~1 KiB |
| Call-trace scratch buffers | 16 shards × 2058 frames × 16B | `profiler.cpp`, `profiler.h` | ~515 KiB |
| JFR recording buffers | 16 shards × (64 KiB + 8 KiB overflow) | `flightRecorder.h`, `buffers.h` | ~1.13 MiB |
| Thread-ID tables | 16 shards × 2 tables × 256 × 4B | `flightRecorder.h`, `threadIdTable.h` | 32 KiB |
| Call-trace hash table (initial) | `INITIAL_CAPACITY`=65,536 slots | `callTraceHashTable.cpp` | ~1.05 MiB |
| Native-lib pointer table | `MAX_NATIVE_LIBS`=2048 × 8B | `codeCache.h` | 16 KiB |
| Library-patcher static tables (Linux) | ~12,288 entries × 24B | `libraryPatcher.h` | ~288 KiB |
| Compiled agent binary (`.so`/`.dylib`) | — | build output | ~0.5 MiB |

**Rough baseline total: ~3–4 MiB**, present before a single thread is profiled or a
single class is loaded. This should be treated as a floor, not a precise constant —
a few structures (first `ThreadFilter` chunk, first `CodeCache` blob arrays) add a
further few hundred KiB that weren't fully quantifiable from static analysis alone,
and the real number should be validated empirically (e.g. RSS delta with agent
attached vs. not, on an otherwise idle JVM).

## Variable costs, by workload property

### 1. Thread count / thread churn — O(threads)
- `ProfiledThread` (thread-local, ~650B/thread: context record + tag encodings)
- `ThreadFilter::Slot` — capped hard at 2048 threads
- `ThreadInfo` name/id maps — grow with threads **ever seen**, not concurrently
  alive, so short-lived thread churn (thread-per-request styles, executor
  pools that get recreated) accumulates over the process lifetime

### 2. Unique call-trace shapes — O(unique stacks)
- `CallTraceHashTable` — doubles capacity at 75% fill
- `CallTraceStorage` triple-buffering roughly 2–3× that cost

Driven by call-graph *breadth* (distinct method-call sequences seen while
sampling), not by sample count or thread count directly — a workload with few hot
methods stays small even at high sampling frequency; one with deep/varied call
graphs (many distinct lambdas, generic instantiations, recursive paths) grows this
fast.

### 3. Loaded classes / methods / symbols — O(unique classes/methods/strings)
- `MethodMap`, `Dictionary`, `StringDictionary` — one entry per unique
  method/class/vtable/string seen since the last JFR chunk
- `CodeCache` — native library symbol tables, capped at 2048 native libs

Driven by classloading intensity (dynamic proxies, many microservice-style
classes, Groovy/Scala/Kotlin-generated synthetic classes), independent of thread
count or sampling rate.

### 4. Sampling / allocation event rate — mostly fixed buffers, variable churn
- JFR recording buffers are fixed in count and size; what scales is *flush
  frequency* (≈ sampling frequency × thread count × allocation rate), which
  affects transient memory churn between chunk rotations, not steady-state size
- `mallocTracer`'s PID controller self-tunes the sampling interval to hold event
  volume roughly constant regardless of raw allocation rate

### 5. Contexts / active spans — folded into thread cost
The former DirectByteBuffer-based per-span context storage was removed; context
data now lives inline in the fixed-size per-thread record, so this is `O(threads)`,
not `O(active spans)`.

## Rough formula

A simple additive model, deliberately ignoring interaction effects and buffer
doubling thresholds:

```
Memory(MiB) ≈ Baseline
            + Threads          × C_thread     (~1–2 KB/thread)
            + UniqueStackTraces × C_trace     (~50–150 B/trace, hash table + arena)
            + UniqueClasses     × C_class     (~200–500 B/class, incl. methods/symbols)
```

Where:
- **Baseline** ≈ 3–4 MiB (see above)
- **Threads** = distinct thread IDs seen over the profiling session (not peak
  concurrent threads), capped in practice at 2048 for the thread-filter component
- **UniqueStackTraces** = distinct call-trace shapes accumulated per JFR chunk
  before flush/reset
- **UniqueClasses** = distinct classes/methods touched by sampled stacks, not
  total classes loaded by the JVM

This is intentionally coarse: `C_trace` and `C_class` are estimates from struct
sizes, not measured constants, and real values should be calibrated by fitting
against RSS measurements from a small matrix of synthetic workloads (few threads
+ narrow call graph, many threads + narrow call graph, few threads + wide call
graph, etc.) before relying on it for capacity planning.

## Practical implications for workload characterization

To predict or explain agent memory usage for a given application, the most useful
signals to collect are, roughly in order of expected impact:
1. **Total distinct thread IDs** created over the profiling window (not just
   peak live thread count — churn matters)
2. **Call-graph breadth** — number of distinct stack-trace shapes, which
   correlates with code diversity more than throughput
3. **Class/method diversity** touched by hot paths — proxies, lambdas, and
   heavy framework use (Spring, reflection-based serialization) increase this
   independent of load
4. Sampling frequency and allocation rate are secondary — they mostly affect
   transient churn, not steady-state footprint, because of fixed buffer sizes
   and adaptive sampling
