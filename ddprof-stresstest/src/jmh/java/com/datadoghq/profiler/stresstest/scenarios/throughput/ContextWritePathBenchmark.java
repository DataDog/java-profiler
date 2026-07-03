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
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Warmup;

/**
 * Decomposes the per-call cost of the OTEP context write path to compare, on real hardware,
 * three shapes of the span-activation hot path (see the OTEL/Loom UAF investigation):
 *
 * <ol>
 *   <li><b>writeOnly_cachedCtx</b> — {@code ThreadContext.put(...)} on a ctx cached in setup.
 *       Isolates the pure DirectByteBuffer write (no per-call lookup).</li>
 *   <li><b>lookupOnly_getThreadContext</b> — {@code profiler.getThreadContext()} only.
 *       Isolates the storage lookup: {@code CarrierThreadLocal.get()} in {@code carrier} mode
 *       vs. plain {@code ThreadLocal.get()} in {@code thread} mode.</li>
 *   <li><b>fullPath_setContext</b> — {@code profiler.setContext(...)}: lookup + write, the real
 *       DirectByteBuffer path as production calls it.</li>
 *   <li><b>nativePath_setContextNative</b> — {@code profiler.setContextNative(...)}: the Option B
 *       all-native write (one JNI transition + resolve current carrier + write), no Java-side
 *       lookup and no cached buffer.</li>
 * </ol>
 *
 * <p>The {@code mode} param runs each storage mode in its own JMH fork; the mode is a
 * system property read once when {@code JavaProfiler} is first constructed, so it is set in
 * {@code @Setup} before {@link JavaProfiler#getInstance()}. Carrier mode needs
 * {@code --add-exports java.base/jdk.internal.misc=ALL-UNNAMED} at JVM launch (added via
 * {@code @Fork(jvmArgsAppend=...)}); it is a no-op for {@code thread} mode and requires JDK 21+.
 *
 * <p>Interpretation: {@code fullPath - writeOnly ≈ lookup cost}; comparing that against
 * {@code nativePath} answers whether the CarrierThreadLocal lookup already costs about as much
 * as a JNI transition. Threads here are platform threads, so {@code carrier} mode exercises the
 * CarrierThreadLocal code path but without the extra virtual→carrier resolution a mounted vthread
 * adds — treat it as a lower bound on the vthread lookup cost.
 *
 * <p>Run both modes:
 * {@code ./gradlew :ddprof-stresstest:jmh -PjmhInclude="ContextWritePathBenchmark"}
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 3, warmups = 0,
        jvmArgsAppend = {"--add-exports=java.base/jdk.internal.misc=ALL-UNNAMED"})
@Warmup(iterations = 3, time = 1)
@Measurement(iterations = 5, time = 2)
public class ContextWritePathBenchmark {

    @State(Scope.Benchmark)
    public static class ProfilerState {
        JavaProfiler profiler;

        @Param({"carrier", "thread"})
        String mode;

        @Setup(Level.Trial)
        public void setup() throws Exception {
            // Must be set before the JavaProfiler singleton is first constructed: the
            // storage mode is resolved once in the tlsContextStorage field initializer.
            // JMH runs each @Param value in its own fork, so getInstance() below is the
            // first construction in this JVM.
            System.setProperty("ddprof.debug.context.storage.mode", mode);
            profiler = JavaProfiler.getInstance();
            Path jfr = Files.createTempFile("bench", ".jfr");
            profiler.execute("start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());
            System.out.println("[bench] requested mode=" + mode
                    + " actual=" + profiler.contextStorageMode());
        }
    }

    @State(Scope.Thread)
    public static class ThreadState {
        ThreadContext ctx;
        long spanId;
        long localRootSpanId;
        long traceIdLow;

        @Setup(Level.Trial)
        public void setup(ProfilerState ps) {
            // Triggers native context-TLS init for this thread and caches the ctx for the
            // write-only baseline.
            ctx = ps.profiler.getThreadContext();
            spanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            localRootSpanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            traceIdLow = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
        }
    }

    /** Pure DirectByteBuffer write, no lookup (ctx cached in setup). */
    @Benchmark
    public void writeOnly_cachedCtx(ThreadState ts) {
        ts.ctx.put(ts.localRootSpanId, ts.spanId, 0, ts.traceIdLow);
    }

    /** Storage lookup only: CarrierThreadLocal.get() (carrier) vs ThreadLocal.get() (thread). */
    @Benchmark
    public ThreadContext lookupOnly_getThreadContext(ProfilerState ps) {
        return ps.profiler.getThreadContext();
    }

    /** Real DirectByteBuffer path as production calls it: lookup + write. */
    @Benchmark
    public void fullPath_setContext(ProfilerState ps, ThreadState ts) {
        ps.profiler.setContext(ts.localRootSpanId, ts.spanId, 0, ts.traceIdLow);
    }

    /** Option B: all-native write — one JNI transition, resolve current carrier, write. */
    @Benchmark
    public void nativePath_setContextNative(ProfilerState ps, ThreadState ts) {
        ps.profiler.setContextNative(ts.localRootSpanId, ts.spanId, 0, ts.traceIdLow);
    }
}
