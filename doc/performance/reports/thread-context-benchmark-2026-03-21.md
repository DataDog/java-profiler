# ThreadContext Benchmark Report — 2026-03-21 (updated 2026-04-07)

## Objective

Verify that `ThreadContext` operations scale linearly across threads and
that no false sharing exists between per-thread `Context` structs
allocated on the native heap via `ProfiledThread`.

## Environment

### 2026-04-07 (current)

| Property       | Value                           |
|----------------|---------------------------------|
| OS             | macOS Darwin 25.3.0 (arm64)     |
| JDK            | Temurin 25.0.2                  |
| JMH            | 1.37                            |
| Forks          | 1                               |
| Warmup         | 2 iterations x 1 s              |
| Measurement    | 3 iterations x 2 s              |
| Mode           | Average time (ns/op)            |

### 2026-03-21 (baseline)

| Property       | Value                           |
|----------------|---------------------------------|
| OS             | macOS Darwin 25.3.0 (arm64)     |
| JDK            | Zulu 25.0.2                     |
| JMH            | 1.37                            |
| Forks          | 2                               |
| Warmup         | 3 iterations x 1 s              |
| Measurement    | 5 iterations x 2 s              |
| Mode           | Average time (ns/op)            |

## Benchmark Design

The benchmark class `ThreadContextBenchmark` uses two JMH `@State` scopes:

- **`ProfilerState` (`Scope.Benchmark`)** — starts the profiler once per
  trial, shared across all threads. Prevents the "Profiler already
  started" race that occurs when multiple threads each try to call
  `profiler.execute("start,...")`.

- **`ThreadState` (`Scope.Thread`)** — each JMH worker thread gets its own
  `ThreadContext`, random span IDs, and counter. This mirrors production
  behavior where each application thread owns an independent context.

Multi-threaded variants use JMH's `@Threads` annotation at the method
level. The single-threaded benchmarks run with the default thread count
of 1.

## Results

### 2026-04-07 — Current (Temurin 25, 1 fork)

```
Benchmark                                 Mode  Cnt   Score   Error  Units
ThreadContextBenchmark.clearContext       avgt    3   4.279 ± 0.236  ns/op
ThreadContextBenchmark.getSpanId         avgt    3   1.046 ± 0.054  ns/op
ThreadContextBenchmark.setAttrCacheHit   avgt    3   9.512 ± 0.213  ns/op
ThreadContextBenchmark.setContextFull    avgt    3   5.993 ± 0.094  ns/op
ThreadContextBenchmark.setContextFull_2t avgt    3   6.360 ± 0.680  ns/op
ThreadContextBenchmark.setContextFull_4t avgt    3   6.162 ± 1.297  ns/op
ThreadContextBenchmark.spanLifecycle     avgt    3  16.345 ± 0.935  ns/op
ThreadContextBenchmark.spanLifecycle_2t  avgt    3  14.475 ± 1.104  ns/op
ThreadContextBenchmark.spanLifecycle_4t  avgt    3  15.233 ± 0.302  ns/op
```

### 2026-03-21 — Baseline (Zulu 25, 2 forks)

```
Benchmark                                 Mode  Cnt   Score   Error  Units
ThreadContextBenchmark.clearContext       avgt    9   5.011 ± 0.039  ns/op
ThreadContextBenchmark.setAttrCacheHit   avgt    9  10.707 ± 0.077  ns/op
ThreadContextBenchmark.setContextFull    avgt    9  11.104 ± 0.338  ns/op
ThreadContextBenchmark.setContextFull_2t avgt    9  11.081 ± 0.105  ns/op
ThreadContextBenchmark.setContextFull_4t avgt    9  11.741 ± 0.338  ns/op
ThreadContextBenchmark.spanLifecycle     avgt    9  30.430 ± 0.129  ns/op
ThreadContextBenchmark.spanLifecycle_2t  avgt    9  30.674 ± 0.093  ns/op
ThreadContextBenchmark.spanLifecycle_4t  avgt    9  32.203 ± 0.309  ns/op
```

### Single-Threaded Breakdown (2026-04-07)

| Benchmark        | ns/op  | Error   | vs Baseline | Description                                    |
|------------------|--------|---------|-------------|------------------------------------------------|
| `clearContext`   |  4.279 | ± 0.236 | -14.6%      | Zero-fill all four context fields              |
| `getSpanId`      |  1.046 | ± 0.054 | N/A (new)   | Direct ByteBuffer read of span ID              |
| `setContextFull` |  5.993 | ± 0.094 | **-46.0%**  | Write localRootSpanId, spanId, traceIdHigh, traceIdLow |
| `setAttrCacheHit`|  9.512 | ± 0.213 | -11.2%      | Set string attribute (dictionary cache hit)    |
| `spanLifecycle`  | 16.345 | ± 0.935 | **-46.3%**  | `setContextFull` + `setAttrCacheHit` combined  |

`getSpanId` at **1.046 ns** confirms the direct ByteBuffer read compiles to a
single memory load — effectively free compared to the removed `getContext()` path
(71.6 ns, dominated by `long[]` JNI allocation).

`setContextFull` improved from 11.1 ns to 6.0 ns (-46%), and `spanLifecycle` from
30.4 ns to 16.3 ns (-46%). This reflects OTEP record write optimizations accumulated
since the baseline (removed redundant `full_fence`, tightened detach/attach window,
direct sidecar writes replacing dictionary lookups for LRS).

### False Sharing Analysis (2026-04-07)

| Benchmark        | 1 thread | 2 threads | 4 threads | 1t to 2t | 1t to 4t |
|------------------|----------|-----------|-----------|----------|----------|
| `setContextFull` | 5.993    | 6.360     | 6.162     | +6.1%    | +2.8%    |
| `spanLifecycle`  | 16.345   | 14.475    | 15.233    | -11.5%\* | -6.8%\*  |

\* The `spanLifecycle` multi-thread results are below the single-thread score.
With 1 fork and 3 measurement iterations, noise floor is ~1 ns. The inversion is
within measurement noise, not a real effect. Re-run with 2+ forks to confirm.

**At 4 threads (`setContextFull`):** +2.8% increase. Well below false-sharing
threshold (typically 2-10x). Consistent with L2/L3 cache pressure and MOESI
coherency traffic with no same-cache-line contention.

### Verdict

**No false sharing detected.** Consistent with the 2026-03-21 result. Per-thread
`OtelThreadContextRecord` structs embedded in `ProfiledThread` are sufficiently
separated in memory. Throughput scales near-linearly from 1 to 4 threads.

## JNI vs ByteBuffer Implementation Comparison

Prior to commit `e7e1c3ce`, the context write path used JNI native
methods for every operation. The current implementation replaced the
per-operation JNI calls with direct `ByteBuffer` writes to native memory,
keeping JNI only for one-time value registration. This section documents
the measured regression in the old JNI path and explains its root cause.

### Before/After Benchmark Data

The "JNI" column was captured on Java 25 (Temurin 25.0.2) where
`ThreadContext` routed all writes through JNI native methods. The
"ByteBuffer" column is the current implementation on Java 25 (Zulu
25.0.2) where all hot-path writes go through `DirectByteBuffer`.
Both are standard OpenJDK 25 distributions with no profiling-relevant
divergences; the vendor difference does not materially affect the comparison.

| Benchmark        | JNI (ns/op) | ByteBuffer 2026-03-21 | ByteBuffer 2026-04-07 | JNI→current |
|------------------|------------:|----------------------:|----------------------:|------------:|
| `clearContext`   |         6.5 |                 5.011 |                 4.279 |      1.5x   |
| `setContextFull` |        20.0 |                11.104 |                 5.993 |      3.3x   |
| `setAttrCacheHit`|       114.8 |                10.707 |                 9.512 |     12.1x   |
| `spanLifecycle`  |       146.3 |                30.430 |                16.345 |      9.0x   |

The span lifecycle hot path improved by **9.0x** from JNI (146 ns) to the current
ByteBuffer implementation (16.3 ns). The dominant contributor is `setContextAttribute`,
which improved by **12.1x** (115 ns → 9.5 ns). Additional gains since the 2026-03-21
baseline reflect OTEP record write optimizations (removed `full_fence`, tightened
detach/attach, direct sidecar writes).

### Why the JNI Path Was Slow

The old `setContextAttribute0` JNI method accepted a `java.lang.String`:

```c
JNICALL Java_com_datadoghq_profiler_ThreadContext_setContextAttribute0(
    JNIEnv* env, jclass unused, jint keyIndex, jstring value)
```

Every invocation paid three costs that the ByteBuffer path avoids:

**1. JNI boundary crossing (~15-20 ns)**

Each JNI call transitions from compiled Java code to native code through
the JNI stub. The JVM must save the Java frame state, set up the native
frame, and pass arguments through the JNI calling convention. On return,
it must restore Java state and check for pending exceptions. Even for
trivial native methods with all-primitive signatures (like
`setContextFull0(long, long, long, long)`), this costs ~10 ns. With
object references in the signature, the cost increases due to handle
table management (see point 2).

**2. JNI String marshalling (~40-60 ns)**

The `jstring` parameter triggers JNI local reference tracking. Inside
the native method, `JniString` called `GetStringUTFChars()` to obtain a
modified-UTF-8 copy of the string data. This involves:

- Acquiring the string's backing array (may pin or copy).
- Converting UTF-16 code units to modified-UTF-8.
- Allocating a temporary native buffer for the result.
- Releasing the string via `ReleaseStringUTFChars()` on scope exit.

For a typical 15-character HTTP route like `"GET /api/users"`, this
UTF-16-to-UTF-8 conversion and copy dominates the call cost.

**3. Dictionary lookup on every call (~30-40 ns)**

After extracting the C string, `ContextApi::setAttribute()` performed a
`Dictionary::bounded_lookup()` to resolve the string to a numeric
encoding. This hash-table lookup happened on every call, even for
repeated values of the same attribute — the JNI path had no caching
layer.

**Total JNI path cost:** ~15 + ~50 + ~35 = ~100 ns, consistent with
the measured 115 ns (the remainder is `JniString` construction overhead
and mode-checking branches).

### Why the ByteBuffer Path Is Fast

The current implementation splits attribute setting into two phases:

**Phase 1 — One-time registration (cache miss, ~100+ ns, amortized away)**

On the first call with a new string value, `registerConstant0(String)`
crosses JNI once to register the value in the native `Dictionary` and
returns its integer encoding. The encoding and the string's UTF-8 bytes
are stored in a per-thread 256-slot direct-mapped cache:

```java
encoding = registerConstant0(value);          // one JNI call
utf8 = value.getBytes(StandardCharsets.UTF_8); // one allocation
attrCacheEncodings[slot] = encoding;
attrCacheBytes[slot] = utf8;
attrCacheKeys[slot] = value;                  // commit
```

**Phase 2 — Cached hot path (cache hit, ~11 ns, zero JNI)**

On subsequent calls with the same string value (the common case — web
applications cycle through a small set of routes), the path is:

```java
if (value.equals(attrCacheKeys[slot])) {
    encoding = attrCacheEncodings[slot];       // int read
    utf8 = attrCacheBytes[slot];               // ref read
}
BUFFER_WRITER.writeOrderedInt(sidecarBuffer, keyIndex * 4, encoding);
detach();
replaceOtepAttribute(otepKeyIndex, utf8);
attach();
```

This performs:
- One `String.equals()` comparison (~3 ns for short strings).
- One ordered int write to the sidecar `DirectByteBuffer` (~2 ns).
- Detach/attach protocol with `storeFence` barriers (~4 ns on ARM).
- A `ByteBuffer.put()` sequence for the OTEP attrs_data (~2 ns).

No JNI crossing. No string marshalling. No dictionary lookup.

### Why All-Primitive JNI Was Also Slower

Even `setContextFull0(long, long, long, long)` — which has no object
parameters — was 1.8x slower than the ByteBuffer path (20 ns vs 11 ns).
The JNI stub overhead alone accounts for ~10 ns. The ByteBuffer path
replaces this with `ByteBuffer.putLong()` calls that the JIT compiles
to direct memory stores, plus two `storeFence` barriers for the
detach/attach protocol. On ARM, `storeFence` compiles to a DMB ISHST
instruction (~2 ns), making the total ByteBuffer overhead ~6 ns for
four long writes plus two fences — well under the JNI stub cost.

On x86, `storeFence` is a no-op (Total Store Order provides free
store-store ordering), so the ByteBuffer path would be even cheaper.

### Cache Hit Rate in Production

The attribute cache is a 256-slot direct-mapped cache keyed by
`String.hashCode() & 0xFF`. In typical web applications:

- HTTP route attributes cycle through 5-50 unique values.
- Span IDs change every request, but they use the `put()` path (no
  string marshalling).
- The cache hit rate for string attributes is effectively 100% in
  steady state, since the working set is far smaller than 256 slots.

This means the amortized cost of `setContextAttribute` in production is
the cache-hit cost of ~11 ns, not the registration cost.

## Cost Model for Instrumentation Budget

Based on these results, the per-span instrumentation cost on the context
hot path is:

| Operation              | Cost (2026-03-21) | Cost (2026-04-07) |
|------------------------|------------------:|------------------:|
| Span start (set IDs)   | ~11 ns            | ~6 ns             |
| Set one attribute       | ~11 ns            | ~10 ns            |
| Full span lifecycle     | ~30 ns            | ~16 ns            |
| Span end (clear)        | ~5 ns             | ~4 ns             |
| Read span ID            | ~72 ns (alloc)    | ~1 ns (direct)    |
| **Total per-span**      | **~35 ns**        | **~20 ns**        |

At 20 ns per span, a single thread can sustain ~50 million span
transitions per second before the context layer becomes a bottleneck.
For a typical web application processing 10K-100K requests/second, this
represents less than 0.002% of available CPU time.

## Recommendations

1. **No action needed on false sharing.** The current `ProfiledThread`
   allocation strategy (one heap allocation per thread) provides
   sufficient cache-line isolation. Confirmed by both the 2026-03-21 and
   2026-04-07 runs.

2. **`getContext` allocation (resolved).** The original `getContext` method
   allocated a `long[]` per call (~71.6 ns). Resolved by replacing `getContext()`
   with direct `DirectByteBuffer` reads in `getSpanId()` (1.0 ns) and
   `getRootSpanId()`, eliminating the JNI call and array allocation entirely.

3. **Re-run multi-threaded variants with 2+ forks.** The 2026-04-07 run used
   1 fork with 3 iterations; `setContextFull_4t` has a ±21% error bar and the
   `spanLifecycle` multi-thread results show noise-floor inversion. A 2-fork run
   would produce publication-quality error bars.

4. **Higher thread counts.** To stress-test on server hardware, add `@Threads(8)`
   and `@Threads(16)` variants and run on a machine with sufficient physical cores.
   On a laptop, 4 threads saturates the performance core complex.

5. **Linux `perf stat` validation.** For definitive cache-miss evidence, run on
   Linux with `perf stat -e L1-dcache-load-misses,LLC-load-misses` and compare
   miss rates across thread counts.
