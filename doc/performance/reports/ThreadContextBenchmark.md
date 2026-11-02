# ThreadContext Benchmark Report

Current numbers: 2026-10-26, Linux x86_64. Historical numbers: 2026-03-21 and 2026-04-07,
macOS arm64.

## Objective

Measure the cost of each thread-context write on the span start and span end paths.
Verify that the cost stays flat as the thread count grows. A flat cost shows that the
per-thread OTEP records in `ProfiledThread` do not share cache lines.

## Implementation History

The context storage has three implementations. The first rewrite removed the JNI call from
each write to make writes faster. The second rewrite fixed a use-after-free risk under
virtual threads and moved the writes back into native code. The current numbers apply to
the all-native implementation only.

| Implementation | On `main` | Write mechanism |
|---|---|---|
| JNI (pre-2026-04-08) | Never. Branch `jb/otel_ctx`, before #347 merged on 2026-04-08. | One JNI call per write. Attribute values cross JNI as a `jstring`. |
| ByteBuffer | From 2026-04-08 (#347) to 2026-07-31 (#696). | Java writes the OTEP record through a cached `DirectByteBuffer` for each thread. Writes make no JNI call. |
| All-native (current) | Since 2026-07-10 (#631). The only implementation since 2026-07-31 (#696). | One JNI call per write. Attribute values cross JNI as a cached encoding and a UTF-8 `byte[]`. |

**Why the all-native implementation replaced the ByteBuffer implementation.** The ByteBuffer
implementation cached a `DirectByteBuffer` over the native record of each Java thread. When
a virtual thread migrated, the cached buffer could point at freed memory. The all-native
implementation caches no buffer. Each JNI call finds the record of the current carrier
thread. A native frame pins a mounted virtual thread to its carrier until the call returns.
Thus the record cannot change during the write (see the all-native context write API in
`javaApi.cpp`).

**Why the JNI implementation was slow.** For each call, `setContextAttribute0(int, String)`
converted the `jstring` to a C string (`JniString`). Then `ContextApi::setAttribute()` did a
`Dictionary::bounded_lookup()`. The all-native implementation finds the encoding in Java,
in `ContextValueCache`. This cache has 256 direct-mapped slots, keyed by
`String.hashCode()`. Only a cache miss calls `registerConstant0()` through JNI.

### All-Native Write Path

| Java API | Native entry point | Work per call |
|---|---|---|
| `JavaProfiler.setTraceContext(...)` | `setTraceContext0` | Find the `ProfiledThread`. Copy up to two attribute values from `byte[]`. Detach the record. Write the trace ID, the span ID and the local root span ID. Reset all custom slots. Write the activation attributes. Attach the record. |
| `JavaProfiler.setContextValue(slot, value)` | `setContextValue0` | Find the value in `ContextValueCache`. Find the `ProfiledThread`. Copy the value from `byte[]`. Detach the record. Replace one attribute. Attach the record. |
| `JavaProfiler.clearTraceContext()` | `clearTraceContext0` | Find the `ProfiledThread`. Detach the record. Set the trace ID, the span ID, the local root span ID and the custom slots to zero. Leave the record detached. |

To detach the record, the code stores `valid=0` and then issues a release fence. To attach
the record, the code issues a release fence and then stores `valid=1`. On x86, the release
fence is only a compiler barrier.

The all-native implementation has no span ID getter. Thus the `getSpanId` benchmark has no
all-native equivalent. The only Java read method is `JavaProfiler.copyContextTags(int[])`,
which copies the custom-slot encodings.

## Current Results — 2026-10-26 (Linux x86_64)

### Environment

| Property | Value |
|---|---|
| Host | AWS, Intel Xeon Platinum 8175M @ 2.50 GHz, 8 cores / 16 threads, 1 socket |
| OS | Ubuntu 22.04.5 LTS, kernel 6.8.0-1057-aws |
| JDK | Temurin 25.0.3+9 |
| JMH | 1.37, Blackhole mode `compiler` (auto-detected) |
| Forks | 2 |
| Warmup | 3 iterations x 1 s |
| Measurement | 5 iterations x 2 s |
| Mode | Average time (ns/op) |
| Native library | Release build |

All three implementations ran on the same host, with the same JDK and the same JMH
settings. For the procedure and the benchmark sources, see
[Reproducing the Numbers](#reproducing-the-numbers).

| Implementation | Implementation commit | Benchmark source |
|---|---|---|
| JNI (pre-2026-04-08) | [`8c44a91e7`](https://github.com/DataDog/java-profiler/commit/8c44a91e727dc906981d3a0237a99da7fe6e73ec) | [Historical benchmark](#historical-benchmark-jni-and-bytebuffer), run with `-Dtcb.extra=,ctxstorage=otel` |
| ByteBuffer | [`86367c704`](https://github.com/DataDog/java-profiler/commit/86367c7040a22175d9569c69cdbe92a2000b1de1) | [`ThreadContextBenchmark.java` at that commit][old-benchmark], without the `reapply*` benchmarks |
| All-native (current) | [`0ed46a634`](https://github.com/DataDog/java-profiler/commit/0ed46a634d585df3974b40b4207676a83bf0ff1f) | `ThreadContextBenchmark.java` in the current tree, not at `0ed46a634` (see the [call mapping](#current-benchmark-all-native)) |

[old-benchmark]: https://github.com/DataDog/java-profiler/blob/86367c7040a22175d9569c69cdbe92a2000b1de1/ddprof-stresstest/src/jmh/java/com/datadoghq/profiler/stresstest/scenarios/throughput/ThreadContextBenchmark.java

The JNI implementation ran in OTEL mode (`ctxstorage=otel`), because its default mode does
not write the OTEP record. The ByteBuffer and all-native implementations always write the
OTEP record.

### Three-Way Comparison (ns/op)

| Benchmark | JNI (pre-2026-04-08) | ByteBuffer | All-native (current) |
|---|---:|---:|---:|
| `setContextFull` | 37.485 ± 0.602 | 17.076 ± 0.164 | 31.284 ± 0.125 |
| `setContextFull_2t` | 39.113 ± 2.721 | 17.046 ± 0.098 | 31.531 ± 0.311 |
| `setContextFull_4t` | 37.255 ± 0.345 | 17.058 ± 0.066 | 31.686 ± 0.211 |
| `setAttrCacheHit` | 172.374 ± 0.615 | 28.097 ± 0.571 | 60.903 ± 0.321 † |
| `spanLifecycle` | 226.411 ± 4.547 | 43.848 ± 0.159 | 91.242 ± 0.639 |
| `spanLifecycle_2t` | 226.072 ± 2.023 | 44.045 ± 2.397 | 91.023 ± 0.593 |
| `spanLifecycle_4t` | 223.611 ± 3.550 | 43.944 ± 2.273 | 91.578 ± 0.695 |
| `clearContext` | 22.230 ± 0.080 | 15.643 ± 8.683 \* | 17.162 ± 0.247 |
| `getSpanId` | 80.147 ± 0.370 | 2.291 ± 0.004 | — |

\* The two forks disagree: fork 1 measured 21.1 ns and fork 2 measured 10.2 ns. Each fork
was stable, so the mean describes neither fork. Do not use this value for comparison.

† 6 forks. In the 2-fork run, one fork measured 73.9 ns and the other 61.0 ns
(67.434 ± 10.294). In the 6-fork run, all forks measured between 60.7 ns and 61.4 ns.

| Benchmark | All-native vs JNI | All-native vs ByteBuffer |
|---|---:|---:|
| `setContextFull` | 1.20x faster | 1.83x slower |
| `setAttrCacheHit` | 2.83x faster | 2.17x slower |
| `spanLifecycle` | 2.48x faster | 2.08x slower |

The JNI ratios compare different work. In the JNI implementation, `put()` keeps the
existing custom attributes, copies them through a buffer, and does not reset the custom
slots. `setTraceContext()` resets all custom slots.

The JNI and all-native implementations both make one JNI call per write. The attribute
write gains the most over the JNI implementation. The JNI implementation converts and
looks up a `jstring` on each call. The all-native implementation passes a cached encoding
and a `byte[]` instead.

Compared with the ByteBuffer implementation, each all-native call adds one JNI transition
and one `ProfiledThread` lookup. Each attribute write also adds one `byte[]` copy, and its
value cache is different. The ByteBuffer implementation kept plain arrays in each
`ThreadContext`. `ContextValueCache` is one `AtomicReferenceArray` for all threads, and each
cache hit does a volatile read. A profile is necessary to show how much of the 2x difference
each of these costs causes.

### False Sharing (all-native)

| Benchmark | 1 thread | 2 threads | 4 threads | 1t to 4t |
|---|---:|---:|---:|---:|
| `setContextFull` | 31.284 | 31.531 | 31.686 | +1.3% |
| `spanLifecycle` | 91.242 | 91.023 | 91.578 | +0.4% |

None of the three implementations shows false sharing on this host. Each multi-threaded
result is within 5% of the related single-threaded result.

### JNI (pre-2026-04-08) in Default Mode

Same host and settings, with the default `ctxstorage`. In this mode, the JNI
implementation does not write the OTEP record. Thus these numbers are not comparable to
the three-way comparison. They show how much of the JNI cost comes from the OTEP record
write.

| Benchmark | ns/op |
|---|---:|
| `setContextFull` | 18.337 ± 0.128 |
| `setContextFull_2t` | 20.812 ± 3.474 \* |
| `setContextFull_4t` | 18.348 ± 0.047 |
| `setAttrCacheHit` | 157.734 ± 0.302 |
| `spanLifecycle` | 175.971 ± 0.425 |
| `spanLifecycle_2t` | 178.703 ± 3.981 |
| `spanLifecycle_4t` | 177.848 ± 2.061 |
| `clearContext` | 18.023 ± 0.157 |
| `getSpanId` | 2.692 ± 0.022 |

\* The two forks disagree: 18.6 ns and 23.0 ns.

### Cost Model (Linux x86_64, 2026-10-26)

| Operation | JNI (pre-2026-04-08) | ByteBuffer | All-native (current) |
|---|---:|---:|---:|
| Span start (`setContextFull`) | ~37 ns | ~17 ns | ~31 ns |
| One attribute (`setAttrCacheHit`) | ~172 ns | ~28 ns | ~61 ns |
| Span start and one attribute (`spanLifecycle`) | ~226 ns | ~44 ns | ~91 ns |
| Span end (`clearContext`) | ~22 ns | 10–21 ns | ~17 ns |
| **Span start, one attribute and span end** | **~248 ns** | **~54–65 ns** | **~108 ns** |

The cost model adds results of separate benchmarks, and two of them do not run in a
production state. Each benchmark runs in its own fork. Thus `clearContext` clears a record
that is already clear, and `setAttrCacheHit` writes an attribute without a preceding
`setTraceContext()`. The span-end and attribute costs are estimates.

With the all-native implementation, one span start, one attribute and one span end cost
about 108 ns. With this estimate, one thread can do about 9 million such spans per second.
At 100,000 spans per second, the context writes use about 10.8 ms of CPU time per second,
or about 1.1% of one core. These are estimates, not production measurements.

## Historical Results — macOS arm64 (ByteBuffer)

These runs measured the ByteBuffer implementation on a laptop. Do not compare them with
the Linux numbers, because the CPU, the OS and the JDK build are different.

| Property | 2026-03-21 | 2026-04-07 |
|---|---|---|
| OS | macOS Darwin 25.3.0 (arm64) | macOS Darwin 25.3.0 (arm64) |
| JDK | Zulu 25.0.2 | Temurin 25.0.2 |
| JMH | 1.37 | 1.37 |
| Forks | 2 | 1 |
| Warmup | 3 iterations x 1 s | 2 iterations x 1 s |
| Measurement | 5 iterations x 2 s | 3 iterations x 2 s |

| Benchmark | 2026-03-21 (ns/op) | 2026-04-07 (ns/op) |
|---|---:|---:|
| `clearContext` | 5.011 ± 0.039 | 4.279 ± 0.236 |
| `getSpanId` | — | 1.046 ± 0.054 |
| `setAttrCacheHit` | 10.707 ± 0.077 | 9.512 ± 0.213 |
| `setContextFull` | 11.104 ± 0.338 | 5.993 ± 0.094 |
| `setContextFull_2t` | 11.081 ± 0.105 | 6.360 ± 0.680 |
| `setContextFull_4t` | 11.741 ± 0.338 | 6.162 ± 1.297 |
| `spanLifecycle` | 30.430 ± 0.129 | 16.345 ± 0.935 |
| `spanLifecycle_2t` | 30.674 ± 0.093 | 14.475 ± 1.104 |
| `spanLifecycle_4t` | 32.203 ± 0.309 | 15.233 ± 0.302 |

The 2026-04-07 run used 1 fork and 3 iterations. In that run, the multi-threaded
`spanLifecycle` results are lower than the single-threaded result. The difference is
within the noise of 1 fork and 3 iterations.

The JNI implementation on the same laptop, with Temurin 25.0.2:

| Benchmark | JNI (ns/op) |
|---|---:|
| `clearContext` | 6.5 |
| `setContextFull` | 20.0 |
| `setAttrCacheHit` | 114.8 |
| `spanLifecycle` | 146.3 |

## Recommendations

1. **Take no action on false sharing on Linux x86_64.** All three implementations stay
   flat from 1 to 4 threads.
2. **Profile the all-native implementation** if its 2x cost over the ByteBuffer
   implementation matters. Measure the JNI transition, the `ProfiledThread` lookup, the
   `byte[]` copy and the `ContextValueCache` lookup separately.
3. **Test more threads.** Add `@Threads(8)` and `@Threads(16)` variants. Run them on a
   host with enough physical cores.
4. **Measure cache misses on Linux.** Run
   `perf stat -e L1-dcache-load-misses,LLC-load-misses` and compare the miss rates across
   thread counts.

## Reproducing the Numbers

The current benchmark is in the tree at
`ddprof-stresstest/src/jmh/java/com/datadoghq/profiler/stresstest/scenarios/throughput/ThreadContextBenchmark.java`.
The historical benchmark uses the `ThreadContext` API, which #696 deleted. To see the
original file on GitHub, open [`ThreadContextBenchmark.java` at `86367c704`][old-benchmark].
This report contains the [modified source](#historical-benchmark-jni-and-bytebuffer) that
ran against both historical implementations.

### Procedure

1. Check out the commit of the implementation. For the all-native implementation, use the
   current tree. For `8c44a91e7`, replace `ThreadContextBenchmark.java` at the path above
   with the [historical benchmark](#historical-benchmark-jni-and-bytebuffer). For
   `86367c704`, use the file at that commit without changes.
2. Build the JMH jar. Set `JAVA_HOME` to JDK 21 and `JAVA_TEST_HOME` to the JDK under test.

   ```bash
   ./.claude/commands/build-and-summarize :ddprof-stresstest:jmhJar -Pskip-tests -Pskip-gtest
   ```
3. Make sure that the jar contains only the release build of the native library.
   `stresstests.jar` contains two `libjavaProfiler` entries with the same name: the debug
   build and the release build. Remove both entries, then add the release build:

   ```bash
   cp ddprof-stresstest/build/libs/stresstests.jar bench.jar
   zip -d bench.jar META-INF/native-libs/linux-x64/libjavaProfiler.so
   (cd ddprof-lib/build/native/release && \
    zip "$OLDPWD/bench.jar" META-INF/native-libs/linux-x64/libjavaProfiler.so)
   ```
4. Run the jar directly, and set all JMH options and the time unit explicitly. Put the
   benchmark regex in single quotes. In double quotes, interactive bash and zsh expand
   `!reapply` as a history reference. Do not run the benchmark through Gradle. The `jmh {}`
   block in `ddprof-stresstest/build.gradle.kts` sets `fork`, `iterations` and
   `timeOnIteration`, and these settings override the class annotations. The jar's `Main`
   also replaces each option that is not on the command line: 1 fork, 0 warmup iterations,
   1 measurement iteration of 5 s, and microseconds.

   ```bash
   # All-native and ByteBuffer
   java -jar bench.jar 'ThreadContextBenchmark\.(?!reapply)' \
     -f 2 -wi 3 -w 1s -i 5 -r 2s -tu ns -bm avgt -rf json -rff results.json

   # JNI (pre-2026-04-08), OTEL mode
   java -jar bench.jar "ThreadContextBenchmark" \
     -jvmArgsAppend "-Dtcb.extra=,ctxstorage=otel" \
     -f 2 -wi 3 -w 1s -i 5 -r 2s -tu ns -bm avgt -rf json -rff results-otel.json
   ```

### Current Benchmark (all-native)

The current benchmark is a port of the historical benchmark to the all-native API. It has
no `getSpanId` benchmark. The table shows how the measured calls map:

| Benchmark | Historical call | All-native call |
|---|---|---|
| `setContextFull` | `ThreadContext.put(lrs, span, 0, trLo)` | `setTraceContext(lrs, span, 0, trLo, -1, null, -1, null)` |
| `setAttrCacheHit` | `ThreadContext.setContextAttribute(0, route)` | `setContextValue(0, route)` |
| `clearContext` | `ThreadContext.put(0, 0, 0, 0)` | `clearTraceContext()` |

In the ByteBuffer implementation, `put()` resets all custom slots. `setTraceContext()` also
resets all custom slots. Thus `setContextFull` measures the same work in both
implementations.

Both benchmarks cycle through the same five routes. The historical benchmark uses
`ROUTES[counter++ % ROUTES.length]`. After 2^31 calls on one thread, the `int` counter
becomes negative, and the array access throws `ArrayIndexOutOfBoundsException`. The
current benchmark keeps the counter in the range 0 to 4. Runs with the settings in this
report stay far below 2^31 calls per thread.

### Historical Benchmark (JNI and ByteBuffer)

This source is [`ThreadContextBenchmark.java` from `86367c704`][old-benchmark], with these
changes:

- It has no `reapply*` benchmarks and no `ReapplyState` class. These benchmarks use API
  that `8c44a91e7` does not have.
- The start command appends the `tcb.extra` system property.
- This report leaves out the license header and the class javadoc. The
  `StandardCharsets` import is removed, because only `ReapplyState` used it.

When `tcb.extra` is not set, the start command and all measured methods are the same as in
`86367c704`.

```java
package com.datadoghq.profiler.stresstest.scenarios.throughput;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.ThreadContext;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Measurement;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Threads;
import org.openjdk.jmh.annotations.Warmup;

@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 2, warmups = 0)
@Warmup(iterations = 3, time = 1)
@Measurement(iterations = 5, time = 2)
public class ThreadContextBenchmark {

    private static final String[] ROUTES = {
        "GET /api/users", "POST /api/orders", "GET /api/health",
        "PUT /api/users/{id}", "DELETE /api/sessions"
    };

    @State(Scope.Benchmark)
    public static class ProfilerState {
        JavaProfiler profiler;

        @Setup(Level.Trial)
        public void setup() throws Exception {
            profiler = JavaProfiler.getInstance();
            Path jfr = Files.createTempFile("bench", ".jfr");
            profiler.execute("start,cpu=10ms,attributes=http.route" + System.getProperty("tcb.extra", "") + ",jfr,file=" + jfr.toAbsolutePath());
        }
    }

    @State(Scope.Thread)
    public static class ThreadState {
        ThreadContext ctx;
        long spanId;
        long localRootSpanId;
        long traceIdLow;
        int counter;

        @Setup(Level.Trial)
        public void setup(ProfilerState ps) {
            ctx = ps.profiler.getThreadContext();
            spanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            localRootSpanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            traceIdLow = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
        }
    }

    @Benchmark
    public void setContextFull(ThreadState ts) {
        ts.ctx.put(ts.localRootSpanId, ts.spanId, 0, ts.traceIdLow);
    }

    @Benchmark
    public boolean setAttrCacheHit(ThreadState ts) {
        return ts.ctx.setContextAttribute(0, ROUTES[ts.counter++ % ROUTES.length]);
    }

    @Benchmark
    public void spanLifecycle(ThreadState ts) {
        ts.ctx.put(ts.localRootSpanId, ts.spanId, 0, ts.traceIdLow);
        ts.ctx.setContextAttribute(0, ROUTES[ts.counter++ % ROUTES.length]);
    }

    @Benchmark
    @Threads(2)
    public void setContextFull_2t(ThreadState ts) {
        ts.ctx.put(ts.localRootSpanId, ts.spanId, 0, ts.traceIdLow);
    }

    @Benchmark
    @Threads(4)
    public void setContextFull_4t(ThreadState ts) {
        ts.ctx.put(ts.localRootSpanId, ts.spanId, 0, ts.traceIdLow);
    }

    @Benchmark
    @Threads(2)
    public void spanLifecycle_2t(ThreadState ts) {
        ts.ctx.put(ts.localRootSpanId, ts.spanId, 0, ts.traceIdLow);
        ts.ctx.setContextAttribute(0, ROUTES[ts.counter++ % ROUTES.length]);
    }

    @Benchmark
    @Threads(4)
    public void spanLifecycle_4t(ThreadState ts) {
        ts.ctx.put(ts.localRootSpanId, ts.spanId, 0, ts.traceIdLow);
        ts.ctx.setContextAttribute(0, ROUTES[ts.counter++ % ROUTES.length]);
    }

    @Benchmark
    public long getSpanId(ThreadState ts) {
        return ts.ctx.getSpanId();
    }

    @Benchmark
    public void clearContext(ThreadState ts) {
        ts.ctx.put(0, 0, 0, 0);
    }
}
```
