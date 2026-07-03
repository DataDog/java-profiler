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
 * The decisive all-native benchmark: the SINGLE-attribute write path that dd-trace-java actually
 * uses in production ({@code setContextValue} → {@link ThreadContext#setContextAttribute(int, String)},
 * ~2x per scope activation), plus {@code clearContextAttribute} (on deactivation).
 *
 * <p>This is the one path where the DBB has its strongest advantage: on a cache hit the DBB write
 * is <b>zero-JNI</b> (the per-thread value→encoding cache means no native call at all), whereas the
 * all-native path pays a mandatory JNI transition. So this is where native's fixed per-call
 * transition cost is least likely to be amortized — the true make-or-break for Option B on the
 * real production surface (snapshot/restore is unused by the tracer; the batch setter is unused).
 *
 * <ul>
 *   <li><b>setAttr_dbb</b> — {@code ctx.setContextAttribute(0, VALUE)} with a primed cache (hit → zero-JNI).</li>
 *   <li><b>setAttr_native</b> — {@code profiler.setContextAttributeNative(0, encoding, utf8)} with the
 *       encoding+bytes pre-resolved. NOTE: this omits the ~2-4 ns Java cache lookup that the DBB
 *       call includes, so native is given a small artificial edge on the set path; the clear path
 *       below is fully symmetric/fair.</li>
 *   <li><b>clearAttr_dbb / clearAttr_native</b> — {@code clearContextAttribute(0)}, no marshalling on
 *       either side (fair head-to-head of the write mechanism).</li>
 * </ul>
 *
 * <p>Run: {@code ./gradlew :ddprof-stresstest:jmh -PjmhInclude="ContextSingleAttrBenchmark"}
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 3, warmups = 0,
        jvmArgsAppend = {"--add-exports=java.base/jdk.internal.misc=ALL-UNNAMED"})
@Warmup(iterations = 3, time = 1)
@Measurement(iterations = 5, time = 2)
public class ContextSingleAttrBenchmark {

    static final int BATCH = 20_000;
    private static final String VALUE = "GET /api/users/{id}";

    // See ContextVThreadBenchmark: jmh compiles at the Java 8 baseline; resolve the JDK 21
    // virtual-thread API reflectively (one invoke per invocation, amortized over BATCH ops).
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
            profiler.execute("start,cpu=10ms,attributes=http.route,jfr,file=" + jfr.toAbsolutePath());
            System.out.println("[bench] requested mode=" + mode
                    + " actual=" + profiler.contextStorageMode());
        }
    }

    @State(Scope.Thread)
    public static class AttrState {
        ThreadContext ctx;
        int encoding;
        byte[] utf8;

        @Setup(Level.Trial)
        public void setup(ProfilerState ps) {
            ctx = ps.profiler.getThreadContext();
            // Establish a live span and prime the per-thread value cache so setContextAttribute
            // hits (zero-JNI) in the measured loop.
            long span = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            ctx.put(span, span, 0, span);
            ctx.setContextAttribute(0, VALUE); // primes cache + registers the encoding
            // Resolve the encoding the cache assigned, for the pre-resolved native path.
            int[] enc = new int[10];
            ctx.copyCustoms(enc);
            encoding = enc[0];
            utf8 = VALUE.getBytes(StandardCharsets.UTF_8);
        }
    }

    // ---- set single attribute (cache hit) ----

    private static void dbbSet(AttrState as) {
        for (int i = 0; i < BATCH; i++) {
            as.ctx.setContextAttribute(0, VALUE);
        }
    }

    private static void nativeSet(JavaProfiler p, AttrState as) {
        for (int i = 0; i < BATCH; i++) {
            p.setContextAttributeNative(0, as.encoding, as.utf8);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_setAttr_dbb(AttrState as) {
        dbbSet(as);
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_setAttr_dbb(AttrState as) throws InterruptedException {
        runOnVirtualThread(() -> dbbSet(as));
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_setAttr_native(ProfilerState ps, AttrState as) {
        nativeSet(ps.profiler, as);
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void vthread_setAttr_native(ProfilerState ps, AttrState as) throws InterruptedException {
        runOnVirtualThread(() -> nativeSet(ps.profiler, as));
    }

    // ---- clear single attribute (symmetric, no marshalling either side) ----

    private static void dbbClear(AttrState as) {
        for (int i = 0; i < BATCH; i++) {
            as.ctx.clearContextAttribute(0);
        }
    }

    private static void nativeClear(JavaProfiler p, AttrState as) {
        for (int i = 0; i < BATCH; i++) {
            p.clearContextAttributeNative(0);
        }
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_clearAttr_dbb(AttrState as) {
        dbbClear(as);
    }

    @Benchmark
    @OperationsPerInvocation(BATCH)
    public void platform_clearAttr_native(ProfilerState ps, AttrState as) {
        nativeClear(ps.profiler, as);
    }
}
