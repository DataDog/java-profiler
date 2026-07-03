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
import org.openjdk.jmh.annotations.OperationsPerInvocation;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Warmup;

/**
 * Measures the nested-scope propagation hot path — {@code ScopeStack.enter}/{@code exit}, which
 * call {@link ThreadContext#snapshot(byte[], int)} / {@link ThreadContext#restore(byte[], int)} on
 * every scope enter/exit — comparing the DirectByteBuffer bulk-memcpy against the Option B native
 * bulk-copy ({@code snapshotNative}/{@code restoreNative}).
 *
 * <p>One measured op = one snapshot+restore pair (i.e. one nested scope enter+exit round trip) over
 * the 688-byte record+sidecar region. Batched at {@value #BATCH} ops/invocation via
 * {@link OperationsPerInvocation} so the vthread create/join cost amortizes; JMH reports per-op ns.
 *
 * <p>The DBB variant uses a ThreadContext cached in setup — the best case for DBB (pure bulk copy,
 * no per-call lookup), which is the conservative comparison (adding a per-op lookup would only make
 * DBB slower). The native variant resolves the current carrier inside each JNI call. snapshot/restore
 * are dominated by the 688-byte bulk copy, so {@code mode} is expected to barely matter here; it is
 * kept for a fallback-confirmation and to verify native mode-independence.
 *
 * <p>Run: {@code ./gradlew :ddprof-stresstest:jmh -PjmhInclude="ContextScopeBenchmark"}
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 3, warmups = 0,
        jvmArgsAppend = {"--add-exports=java.base/jdk.internal.misc=ALL-UNNAMED"})
@Warmup(iterations = 3, time = 1)
@Measurement(iterations = 5, time = 2)
public class ContextScopeBenchmark {

    static final int BATCH = 20_000;
    static final int SNAPSHOT_SIZE = 688; // OTEL record(640) + tag_encodings(40) + LRS(8)

    // See ContextVThreadBenchmark: jmh compiles at the Java 8 baseline, so resolve the JDK 21
    // virtual-thread API reflectively; one invoke per invocation amortizes over BATCH ops.
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
            profiler.execute("start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());
            System.out.println("[bench] requested mode=" + mode
                    + " actual=" + profiler.contextStorageMode());
        }
    }

    @State(Scope.Thread)
    public static class ScopeState {
        ThreadContext ctx;
        byte[] scratch;

        @Setup(Level.Trial)
        public void setup(ProfilerState ps) {
            ctx = ps.profiler.getThreadContext();
            scratch = new byte[SNAPSHOT_SIZE];
            // Establish a live context (valid=1, real trace/span) so snapshot captures a valid
            // record and restore re-publishes it — the steady state ScopeStack operates on.
            long span = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            long lrs = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            long trLo = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            ctx.put(lrs, span, 0, trLo);
            ctx.snapshot(scratch, 0); // prime scratch with a valid snapshot for restore()
        }
    }

    private static void dbbScope(ScopeState ss) {
        for (int i = 0; i < BATCH; i++) {
            ss.ctx.snapshot(ss.scratch, 0);
            ss.ctx.restore(ss.scratch, 0);
        }
    }

    private static void nativeScope(JavaProfiler p, ScopeState ss) {
        for (int i = 0; i < BATCH; i++) {
            p.snapshotNative(ss.scratch, 0);
            p.restoreNative(ss.scratch, 0);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_dbb_scope(ScopeState ss) {
        dbbScope(ss);
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_dbb_scope(ScopeState ss) throws InterruptedException {
        runOnVirtualThread(() -> dbbScope(ss));
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_native_scope(ProfilerState ps, ScopeState ss) {
        nativeScope(ps.profiler, ss);
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_native_scope(ProfilerState ps, ScopeState ss) throws InterruptedException {
        runOnVirtualThread(() -> nativeScope(ps.profiler, ss));
    }
}
