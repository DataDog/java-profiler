/*
 * Copyright 2025, 2026 Datadog, Inc
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
import com.datadoghq.profiler.ThreadContext;
import java.nio.charset.StandardCharsets;
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

/**
 * Benchmarks for ThreadContext operations — measures the per-call cost of
 * context set/get/attribute operations on the span start/end hot path.
 *
 * <p>Run: ./gradlew :ddprof-stresstest:jmh -PjmhInclude="ThreadContextBenchmark"
 *
 * <p>Run with different JAVA_HOME to compare JNI (17+) vs ByteBuffer (&lt;17) paths.
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

        @Setup(Level.Trial)
        public void setup() throws Exception {
            profiler = JavaProfiler.getInstance();
            Path jfr = Files.createTempFile("bench", ".jfr");
            profiler.execute("start,cpu=10ms,attributes=http.route,jfr,file=" + jfr.toAbsolutePath());
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

    @State(Scope.Thread)
    public static class ReapplyState {
        ThreadContext ctx;
        long spanId;
        long localRootSpanId;
        long traceIdLow;
        int[] constantIds;
        byte[][] utf8;

        @Setup(Level.Trial)
        public void setup(ProfilerState ps) {
            ctx = ps.profiler.getThreadContext();
            spanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            localRootSpanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            traceIdLow = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);

            // Prime the normal path to obtain constant IDs, then snapshot for reapply.
            ctx.put(localRootSpanId, spanId, 0, traceIdLow);
            for (int i = 0; i < ROUTES.length; i++) {
                ctx.setContextAttribute(i, ROUTES[i]);
            }
            constantIds = new int[10];
            ctx.copyCustoms(constantIds);
            utf8 = new byte[10][];
            for (int i = 0; i < ROUTES.length; i++) {
                utf8[i] = ROUTES[i].getBytes(StandardCharsets.UTF_8);
            }
        }

        @Setup(Level.Iteration)
        public void resetToSteadyState() {
            // Re-establish a live span (valid=1) and pre-populate attrs_data with all slots
            // before each measurement window. Without this, reapplyByIdAndBytes sees a
            // different attrs_data state on the first invocation of each iteration (empty
            // after put() in the previous iteration or after the trial setup), causing a
            // bimodal distribution across forks due to JIT profile divergence.
            ctx.put(localRootSpanId, spanId, 0, traceIdLow);
            if (!ctx.setContextAttributesByIdAndBytes(constantIds, utf8)) {
                throw new IllegalStateException(
                        "resetToSteadyState: setContextAttributesByIdAndBytes failed; benchmark state invalid");
            }
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

    /** Bare reapply cost with constant IDs and bytes already in hand — no Dictionary lookup. */
    @Benchmark
    public boolean reapplyByIdAndBytes(ReapplyState rs) {
        return rs.ctx.setContextAttributesByIdAndBytes(rs.constantIds, rs.utf8);
    }

    /** Full reapply cycle: span activation wipes slots, then reapply restores them. */
    @Benchmark
    public boolean reapplyCycle(ReapplyState rs) {
        rs.ctx.put(rs.localRootSpanId, rs.spanId, 0, rs.spanId);
        return rs.ctx.setContextAttributesByIdAndBytes(rs.constantIds, rs.utf8);
    }

    @Benchmark
    @Threads(2)
    public boolean reapplyCycle_2t(ReapplyState rs) {
        rs.ctx.put(rs.localRootSpanId, rs.spanId, 0, rs.spanId);
        return rs.ctx.setContextAttributesByIdAndBytes(rs.constantIds, rs.utf8);
    }

    @Benchmark
    @Threads(4)
    public boolean reapplyCycle_4t(ReapplyState rs) {
        rs.ctx.put(rs.localRootSpanId, rs.spanId, 0, rs.spanId);
        return rs.ctx.setContextAttributesByIdAndBytes(rs.constantIds, rs.utf8);
    }
}
