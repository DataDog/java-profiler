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
import org.openjdk.jmh.infra.Blackhole;

/**
 * Measures the OTEP context write path when the writer runs on a <em>mounted virtual thread</em>,
 * to quantify the extra cost the DirectByteBuffer path pays on a vthread that the all-native
 * (Option B) path does not.
 *
 * <p>On a mounted vthread, {@code CarrierThreadLocal.get()} must resolve
 * {@code currentCarrierThread()} (not just {@code currentThread()}), so the DBB-path lookup is
 * expected to be somewhat pricier than on a platform thread; the native path resolves the carrier
 * in C regardless of mount state, so it should be flat. Each measured method runs a batch of
 * {@value #BATCH} writes in one freshly-started virtual thread and joins it; with a large batch
 * the ~µs create/join cost amortizes to well under a nanosecond per op (verify against the
 * {@code platform_*} counterparts, which run the identical loop on the calling platform thread).
 *
 * <p>The vthread runs a tight CPU loop with no blocking, so under JDK 21 it stays mounted on one
 * carrier for the whole batch — exactly the "mounted, no migration" state whose per-call lookup
 * cost we want. Migration/UAF safety is a separate question (the native path is race-free by
 * construction); this benchmark is purely about per-call cost.
 *
 * <p>{@code mode} selects carrier vs thread storage per fork (native path is mode-independent).
 * Run: {@code ./gradlew :ddprof-stresstest:jmh -PjmhInclude="ContextVThreadBenchmark"}
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 3, warmups = 0,
        jvmArgsAppend = {"--add-exports=java.base/jdk.internal.misc=ALL-UNNAMED"})
@Warmup(iterations = 3, time = 1)
@Measurement(iterations = 5, time = 2)
public class ContextVThreadBenchmark {

    static final int BATCH = 20_000;

    // The jmh source set compiles at the Java 8 baseline (--release 8), so the JDK 21
    // virtual-thread API (Thread.ofVirtual / startVirtualThread) is not referenceable at
    // compile time. Resolve Thread.startVirtualThread(Runnable) reflectively once; a single
    // reflective invoke per benchmark invocation is amortized over BATCH writes.
    private static final java.lang.reflect.Method START_VIRTUAL_THREAD;
    static {
        java.lang.reflect.Method m;
        try {
            m = Thread.class.getMethod("startVirtualThread", Runnable.class);
        } catch (NoSuchMethodException e) {
            m = null; // JDK < 21 — vthread benchmarks will fail fast (this suite targets 21+).
        }
        START_VIRTUAL_THREAD = m;
    }

    private static void runOnVirtualThread(Runnable r) throws InterruptedException {
        try {
            Thread t = (Thread) START_VIRTUAL_THREAD.invoke(null, r);
            t.join();
        } catch (ReflectiveOperationException e) {
            throw new IllegalStateException(
                    "Thread.startVirtualThread unavailable; run this suite on JDK 21+", e);
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
            profiler.execute("start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());
            System.out.println("[bench] requested mode=" + mode
                    + " actual=" + profiler.contextStorageMode());
        }
    }

    @State(Scope.Thread)
    public static class Vals {
        long spanId;
        long localRootSpanId;
        long traceIdLow;

        @Setup(Level.Trial)
        public void setup() {
            spanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            localRootSpanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            traceIdLow = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
        }
    }

    // ---- fullPath (DirectByteBuffer): CarrierThreadLocal/ThreadLocal lookup + write ----

    private static void runFullPath(JavaProfiler p, Vals v) {
        long s = v.spanId, l = v.localRootSpanId, t = v.traceIdLow;
        // s + i keeps span non-zero (avoids the clear path) and varies the value so the loop
        // cannot be hoisted; the native-memory write is a side effect JIT cannot elide.
        for (int i = 0; i < BATCH; i++) {
            p.setContext(l, s + i, 0, t);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_fullPath(ProfilerState ps, Vals v) {
        runFullPath(ps.profiler, v);
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_fullPath(ProfilerState ps, Vals v) throws InterruptedException {
        runOnVirtualThread(() -> runFullPath(ps.profiler, v));
    }

    // ---- native (Option B): one JNI call per write, resolve carrier in C ----

    private static void runNative(JavaProfiler p, Vals v) {
        long s = v.spanId, l = v.localRootSpanId, t = v.traceIdLow;
        for (int i = 0; i < BATCH; i++) {
            p.setContextNative(l, s + i, 0, t);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_native(ProfilerState ps, Vals v) {
        runNative(ps.profiler, v);
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_native(ProfilerState ps, Vals v) throws InterruptedException {
        runOnVirtualThread(() -> runNative(ps.profiler, v));
    }

    // ---- lookup only: isolates the mounted-vthread carrier-resolution penalty ----

    private static void runLookup(JavaProfiler p, Blackhole bh) {
        for (int i = 0; i < BATCH; i++) {
            bh.consume(p.getThreadContext());
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_lookup(ProfilerState ps, Blackhole bh) {
        runLookup(ps.profiler, bh);
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_lookup(ProfilerState ps, Blackhole bh) throws InterruptedException {
        runOnVirtualThread(() -> runLookup(ps.profiler, bh));
    }
}
