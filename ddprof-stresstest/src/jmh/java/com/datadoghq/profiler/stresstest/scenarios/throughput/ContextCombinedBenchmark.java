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
import org.openjdk.jmh.annotations.OperationsPerInvocation;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Warmup;

/**
 * Perf-guard for the all-native context write API: the full per-scope activate+deactivate cycle
 * as dd-trace-java drives it, comparing the production combined native calls
 * ({@code setTraceContext}/{@code clearTraceContext}) against the deprecated DirectByteBuffer
 * sequence ({@code setContext} + 2x {@code setContextAttribute}, then {@code clearContext} + 2x
 * {@code clearContextAttribute}).
 *
 * <p>One measured op = one full activate+deactivate cycle (@OperationsPerInvocation({@value #BATCH})).
 * The all-native cycle is expected to be at parity or a modest win over the fine-grained DBB cycle,
 * on both platform and mounted virtual threads and independent of storage mode (see the design
 * note, doc/plans/2026-07-02-all-native-context-storage-design.md). Guards against a regression in
 * the shipping API.
 *
 * <p>Run: {@code ./gradlew :ddprof-stresstest:jmh -PjmhInclude="ContextCombinedBenchmark"}
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 3, warmups = 0,
        jvmArgsAppend = {"--add-exports=java.base/jdk.internal.misc=ALL-UNNAMED"})
@Warmup(iterations = 3, time = 1)
@Measurement(iterations = 5, time = 2)
@SuppressWarnings("deprecation") // intentionally exercises the deprecated DirectByteBuffer path as the baseline
public class ContextCombinedBenchmark {

    static final int BATCH = 20_000;
    private static final String OP_NAME = "servlet.request";
    private static final String RES_NAME = "GET /api/users/{id}";
    private static final int SLOT_OP = 0;
    private static final int SLOT_RES = 1;

    // jmh compiles at the Java 8 baseline; resolve the JDK 21 vthread API reflectively.
    private static final java.lang.reflect.Method START_VIRTUAL_THREAD;
    static {
        java.lang.reflect.Method m;
        try {
            m = Thread.class.getMethod("startVirtualThread", Runnable.class);
        } catch (NoSuchMethodException e) {
            m = null;
        }
        START_VIRTUAL_THREAD = m;
    }

    private static void runOnVirtualThread(Runnable r) throws InterruptedException {
        try {
            Thread t = (Thread) START_VIRTUAL_THREAD.invoke(null, r);
            t.join();
        } catch (ReflectiveOperationException e) {
            throw new IllegalStateException("Thread.startVirtualThread unavailable; run on JDK 21+", e);
        }
    }

    @State(Scope.Benchmark)
    public static class ProfilerState {
        JavaProfiler profiler;

        @Param({"carrier", "thread"})
        String mode;

        @Setup(Level.Trial)
        public void setup() throws Exception {
            System.setProperty("ddprof.debug.context.storage.mode", mode);
            profiler = JavaProfiler.getInstance();
            Path jfr = Files.createTempFile("ctx-combined", ".jfr");
            profiler.execute("start,cpu=10ms,attributes=op;res,jfr,file=" + jfr.toAbsolutePath());
            System.out.println("[bench] requested mode=" + mode + " actual=" + profiler.contextStorageMode());
        }
    }

    @State(Scope.Thread)
    public static class CtxState {
        long span, lrs, trLo;

        @Setup(Level.Trial)
        public void setup() {
            span = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            lrs = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            trLo = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
        }
    }

    // ---- all-native combined cycle (2 JNI calls) ----

    private static void nativeCycle(JavaProfiler p, CtxState s) {
        p.setTraceContext(s.lrs, s.span, 0, s.trLo, SLOT_OP, OP_NAME, SLOT_RES, RES_NAME);
        p.clearTraceContext();
    }

    // ---- deprecated DirectByteBuffer cycle (6 calls; cache-hit attribute writes) ----

    private static void dbbCycle(JavaProfiler p, CtxState s) {
        p.setContext(s.lrs, s.span, 0, s.trLo);
        p.setContextAttribute(SLOT_OP, OP_NAME);
        p.setContextAttribute(SLOT_RES, RES_NAME);
        p.setContext(0, 0, 0, 0);
        p.clearContextAttribute(SLOT_OP);
        p.clearContextAttribute(SLOT_RES);
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_native_cycle(ProfilerState ps, CtxState s) {
        for (int i = 0; i < BATCH; i++) {
            nativeCycle(ps.profiler, s);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_dbb_cycle(ProfilerState ps, CtxState s) {
        for (int i = 0; i < BATCH; i++) {
            dbbCycle(ps.profiler, s);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_native_cycle(ProfilerState ps, CtxState s) throws InterruptedException {
        runOnVirtualThread(() -> {
            for (int i = 0; i < BATCH; i++) {
                nativeCycle(ps.profiler, s);
            }
        });
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_dbb_cycle(ProfilerState ps, CtxState s) throws InterruptedException {
        runOnVirtualThread(() -> {
            for (int i = 0; i < BATCH; i++) {
                dbbCycle(ps.profiler, s);
            }
        });
    }
}
