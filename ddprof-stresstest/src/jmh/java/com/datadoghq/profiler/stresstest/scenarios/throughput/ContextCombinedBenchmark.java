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
import org.openjdk.jmh.annotations.OperationsPerInvocation;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Warmup;

/**
 * The settling benchmark: models dd-trace-java's real per-scope work and compares the current
 * fine-grained DBB call sequence against a BATCHED all-native call.
 *
 * <p>Production activation = {@code setContext(4 longs)} + {@code setContextValue(spanName)} +
 * {@code setContextValue(resourceName)} (3 DBB calls, each zero-JNI on cache hit but each with its
 * own detach/attach + carrier lookup). Deactivation = {@code setContext(0,0,0,0)} + 2x
 * {@code clearContextValue} (3 more). The all-native alternative does activation in ONE
 * {@code setFullContextNative} call and deactivation in ONE {@code clearFullContextNative} call, so
 * the JNI transition is amortized over the whole activation instead of paid per sub-op.
 *
 * <ul>
 *   <li><b>*_activate</b> — activation half only (DBB: 3 calls; native: 1 call).</li>
 *   <li><b>*_cycle</b> — full activate + deactivate (DBB: 6 calls; native: 2 calls).</li>
 * </ul>
 * One measured op = one activate (or one full cycle). @OperationsPerInvocation({@value #BATCH}).
 *
 * <p>Run: {@code ./gradlew :ddprof-stresstest:jmh -PjmhInclude="ContextCombinedBenchmark"}
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 3, warmups = 0,
        jvmArgsAppend = {"--add-exports=java.base/jdk.internal.misc=ALL-UNNAMED"})
@Warmup(iterations = 3, time = 1)
@Measurement(iterations = 5, time = 2)
public class ContextCombinedBenchmark {

    static final int BATCH = 20_000;
    private static final String SPAN_NAME = "servlet.request";
    private static final String RESOURCE_NAME = "GET /api/users/{id}";
    private static final int SPAN_NAME_SLOT = 0;
    private static final int RESOURCE_NAME_SLOT = 1;

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
            Path jfr = Files.createTempFile("bench", ".jfr");
            profiler.execute("start,cpu=10ms,attributes=span.name;resource.name,jfr,file="
                    + jfr.toAbsolutePath());
            System.out.println("[bench] requested mode=" + mode
                    + " actual=" + profiler.contextStorageMode());
        }
    }

    @State(Scope.Thread)
    public static class CtxState {
        ThreadContext ctx;
        long span, lrs, trLo;
        int enc0, enc1;
        byte[] utf0, utf1;

        @Setup(Level.Trial)
        public void setup(ProfilerState ps) {
            ctx = ps.profiler.getThreadContext();
            span = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            lrs = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            trLo = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            // Prime the per-thread value cache and resolve encodings for the two named attrs.
            ctx.put(span, span, 0, span);
            ctx.setContextAttribute(SPAN_NAME_SLOT, SPAN_NAME);
            ctx.setContextAttribute(RESOURCE_NAME_SLOT, RESOURCE_NAME);
            int[] enc = new int[10];
            ctx.copyCustoms(enc);
            enc0 = enc[SPAN_NAME_SLOT];
            enc1 = enc[RESOURCE_NAME_SLOT];
            utf0 = SPAN_NAME.getBytes(StandardCharsets.UTF_8);
            utf1 = RESOURCE_NAME.getBytes(StandardCharsets.UTF_8);
        }
    }

    // ---- DBB: the current fine-grained sequence (cache hits → zero-JNI writes) ----

    private static void dbbActivate(CtxState s) {
        s.ctx.put(s.lrs, s.span, 0, s.trLo);
        s.ctx.setContextAttribute(SPAN_NAME_SLOT, SPAN_NAME);
        s.ctx.setContextAttribute(RESOURCE_NAME_SLOT, RESOURCE_NAME);
    }

    private static void dbbDeactivate(CtxState s) {
        s.ctx.put(0, 0, 0, 0);
        s.ctx.clearContextAttribute(SPAN_NAME_SLOT);
        s.ctx.clearContextAttribute(RESOURCE_NAME_SLOT);
    }

    // ---- native: one combined call per half ----

    private static void nativeActivate(JavaProfiler p, CtxState s) {
        p.setFullContextNative(s.lrs, s.span, 0, s.trLo, s.enc0, s.utf0, s.enc1, s.utf1);
    }

    private static void nativeDeactivate(JavaProfiler p, CtxState s) {
        p.clearFullContextNative();
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_dbb_activate(CtxState s) {
        for (int i = 0; i < BATCH; i++) {
            dbbActivate(s);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_native_activate(ProfilerState ps, CtxState s) {
        for (int i = 0; i < BATCH; i++) {
            nativeActivate(ps.profiler, s);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_dbb_cycle(CtxState s) {
        for (int i = 0; i < BATCH; i++) {
            dbbActivate(s);
            dbbDeactivate(s);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_native_cycle(ProfilerState ps, CtxState s) {
        for (int i = 0; i < BATCH; i++) {
            nativeActivate(ps.profiler, s);
            nativeDeactivate(ps.profiler, s);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_dbb_cycle(CtxState s) throws InterruptedException {
        runOnVirtualThread(() -> {
            for (int i = 0; i < BATCH; i++) {
                dbbActivate(s);
                dbbDeactivate(s);
            }
        });
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_native_cycle(ProfilerState ps, CtxState s) throws InterruptedException {
        runOnVirtualThread(() -> {
            for (int i = 0; i < BATCH; i++) {
                nativeActivate(ps.profiler, s);
                nativeDeactivate(ps.profiler, s);
            }
        });
    }
}
