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
import com.datadoghq.profiler.OTelContext;
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
import org.openjdk.jmh.annotations.Warmup;

/**
 * Benchmarks for ThreadContext operations — measures the per-call cost of
 * context set/get/attribute operations on the span start/end hot path.
 *
 * <p>Run: ./gradlew :ddprof-stresstest:jmh -PjmhInclude="ThreadContextBenchmark"
 *
 * <p>Run with different JAVA_HOME to compare JNI (17+) vs ByteBuffer (&lt;17) paths.
 */
@State(Scope.Thread)
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 2, warmups = 0)
@Warmup(iterations = 3, time = 1)
@Measurement(iterations = 5, time = 2)
public class ThreadContextBenchmark {

    private JavaProfiler profiler;
    private ThreadContext ctx;
    private long spanId;
    private long localRootSpanId;
    private int counter;

    private static final String[] ROUTES = {
        "GET /api/users", "POST /api/orders", "GET /api/health",
        "PUT /api/users/{id}", "DELETE /api/sessions"
    };

    @Setup(Level.Trial)
    public void setup() throws Exception {
        profiler = JavaProfiler.getInstance();
        Path jfr = Files.createTempFile("bench", ".jfr");
        profiler.execute("start,cpu=10ms,attributes=http.route,jfr,file=" + jfr.toAbsolutePath());
        OTelContext.getInstance().registerAttributeKeys("http.route");
        ctx = profiler.getThreadContext();
        spanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
        localRootSpanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
    }

    @Benchmark
    public void setContextFull() {
        ctx.put(localRootSpanId, spanId, 0, spanId);
    }

    @Benchmark
    public boolean setAttrCacheHit() {
        return ctx.setContextAttribute(0, ROUTES[counter++ % ROUTES.length]);
    }

    @Benchmark
    public void spanLifecycle() {
        ctx.put(localRootSpanId, spanId, 0, spanId);
        ctx.setContextAttribute(0, ROUTES[counter++ % ROUTES.length]);
    }

    @Benchmark
    public long[] getContext() {
        return ctx.getContext();
    }

    @Benchmark
    public void clearContext() {
        ctx.put(0, 0, 0, 0);
    }
}
