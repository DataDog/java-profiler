/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler.stresstest.scenarios.throughput;

import com.datadoghq.profiler.JavaProfiler;
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
import org.openjdk.jmh.annotations.TearDown;
import org.openjdk.jmh.annotations.Threads;
import org.openjdk.jmh.annotations.Warmup;

/**
 * Per-call cost of the all-native context write API on the span start/end hot path, single- and
 * multi-threaded (false-sharing check between per-thread OTEP records).
 *
 * <p>{@code setContextFull} calls {@link JavaProfiler#setTraceContext} with both attribute slots
 * skipped; that call also resets the custom slots. {@code clearContext} calls
 * {@link JavaProfiler#clearTraceContext}. {@code setAttrCacheHit} calls
 * {@link JavaProfiler#setContextValue} with values that hit the Java-side value cache.
 *
 * <p>The annotation settings do not apply by default. The Gradle {@code jmh} block overrides
 * them, and the jar's {@code Main} replaces every option that is not on the command line with
 * its own default. Pass all JMH options explicitly (see the report in
 * {@code doc/performance/reports/ThreadContextBenchmark.md}).
 */
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
        Path jfr;

        @Setup(Level.Trial)
        public void setup() throws Exception {
            profiler = JavaProfiler.getInstance();
            jfr = Files.createTempFile("bench", ".jfr");
            profiler.execute("start,cpu=10ms,attributes=http.route,jfr,file=" + jfr.toAbsolutePath());
        }

        // With -f 0 all trials share one JVM; a still-running profiler makes the next start fail.
        @TearDown(Level.Trial)
        public void tearDown() throws Exception {
            profiler.execute("stop");
            Files.deleteIfExists(jfr);
        }
    }

    @State(Scope.Thread)
    public static class ThreadState {
        JavaProfiler profiler;
        long spanId;
        long localRootSpanId;
        long traceIdLow;
        int counter;

        @Setup(Level.Trial)
        public void setup(ProfilerState ps) {
            profiler = ps.profiler;
            spanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            localRootSpanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            traceIdLow = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
        }
    }

    // Wraps instead of incrementing without bound: an int counter goes negative after 2^31 calls
    // and the array index would throw.
    private static String nextRoute(ThreadState ts) {
        ts.counter = (ts.counter + 1) % ROUTES.length;
        return ROUTES[ts.counter];
    }

    private static void setIds(ThreadState ts) {
        ts.profiler.setTraceContext(ts.localRootSpanId, ts.spanId, 0, ts.traceIdLow, -1, null, -1, null);
    }

    @Benchmark
    public void setContextFull(ThreadState ts) {
        setIds(ts);
    }

    @Benchmark
    public boolean setAttrCacheHit(ThreadState ts) {
        return ts.profiler.setContextValue(0, nextRoute(ts));
    }

    @Benchmark
    public void spanLifecycle(ThreadState ts) {
        setIds(ts);
        ts.profiler.setContextValue(0, nextRoute(ts));
    }

    @Benchmark
    @Threads(2)
    public void setContextFull_2t(ThreadState ts) {
        setIds(ts);
    }

    @Benchmark
    @Threads(4)
    public void setContextFull_4t(ThreadState ts) {
        setIds(ts);
    }

    @Benchmark
    @Threads(2)
    public void spanLifecycle_2t(ThreadState ts) {
        setIds(ts);
        ts.profiler.setContextValue(0, nextRoute(ts));
    }

    @Benchmark
    @Threads(4)
    public void spanLifecycle_4t(ThreadState ts) {
        setIds(ts);
        ts.profiler.setContextValue(0, nextRoute(ts));
    }

    @Benchmark
    public void clearContext(ThreadState ts) {
        ts.profiler.clearTraceContext();
    }
}
