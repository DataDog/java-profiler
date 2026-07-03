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
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Warmup;

/**
 * Compares the batched-attribute reapply hot path in two shapes:
 *
 * <ul>
 *   <li><b>dbb_reapply</b> — {@link ThreadContext#setContextAttributesByIdAndBytes(int[], byte[][])}:
 *       the DirectByteBuffer path (no JNI, in-Java attrs_data compaction).</li>
 *   <li><b>native_reapply</b> — {@code profiler.setContextAttributesNative(...)}: the Option B
 *       all-native equivalent, which pays the object-array JNI cost (GetObjectArrayElement +
 *       GetByteArrayRegion per active slot) but does the compaction in C.</li>
 * </ul>
 *
 * <p>This isolates the one transition the plain setContext benchmark does not cover: object-array
 * marshalling. Both variants reapply the same {@value #ACTIVE_SLOTS} pre-encoded attributes into a
 * record re-established to a live steady state (valid=1, slots populated) before every measurement
 * iteration — matching the ReapplyState discipline in {@code ThreadContextBenchmark}.
 *
 * <p>Run: {@code ./gradlew :ddprof-stresstest:jmh -PjmhInclude="ContextAttrBenchmark"}
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 3, warmups = 0,
        jvmArgsAppend = {"--add-exports=java.base/jdk.internal.misc=ALL-UNNAMED"})
@Warmup(iterations = 3, time = 1)
@Measurement(iterations = 5, time = 2)
public class ContextAttrBenchmark {

    private static final int ACTIVE_SLOTS = 5;
    // Mirrors MAX_CUSTOM_SLOTS (package-private, not visible here).
    private static final int MAX_CUSTOM_SLOTS = 10;
    private static final String[] ROUTES = {
        "GET /api/users", "POST /api/orders", "GET /api/health",
        "PUT /api/users/{id}", "DELETE /api/sessions"
    };

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
    public static class ReapplyState {
        ThreadContext ctx;
        long spanId;
        long localRootSpanId;
        long traceIdLow;
        int[] constantIds;
        byte[][] utf8;
        // Flattened custom-entry blob ([otepKey][len][bytes]...) for the flat-native path.
        byte[] attrsBlob;   // precomputed once (stable attribute set)
        int blobLen;
        byte[] scratchBlob; // reusable buffer for the build-each-call variant

        @Setup(Level.Trial)
        public void setup(ProfilerState ps) {
            ctx = ps.profiler.getThreadContext();
            spanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            localRootSpanId = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);
            traceIdLow = ThreadLocalRandom.current().nextLong(1, Long.MAX_VALUE);

            // Prime the normal path to obtain constant IDs, then snapshot for reapply.
            ctx.put(localRootSpanId, spanId, 0, traceIdLow);
            for (int i = 0; i < ACTIVE_SLOTS; i++) {
                ctx.setContextAttribute(i, ROUTES[i]);
            }
            constantIds = new int[MAX_CUSTOM_SLOTS];
            ctx.copyCustoms(constantIds);
            utf8 = new byte[MAX_CUSTOM_SLOTS][];
            for (int i = 0; i < ACTIVE_SLOTS; i++) {
                utf8[i] = ROUTES[i].getBytes(StandardCharsets.UTF_8);
            }
            // Fill inactive slots with empty arrays so the native path's GetObjectArrayElement
            // never hits null (constantIds<=0 slots are skipped, so bytes are unused there).
            for (int i = 0; i < utf8.length; i++) {
                if (utf8[i] == null) {
                    utf8[i] = new byte[0];
                }
            }
            // Precompute the flattened custom-entry blob once (the attribute set is stable
            // across mounts, so reapply-on-mount can reuse it). scratchBlob backs the
            // build-each-call variant that re-serializes on every call.
            scratchBlob = new byte[612];
            attrsBlob = new byte[612];
            blobLen = flatten(constantIds, utf8, attrsBlob);
        }

        /** Serialize active custom slots into dst as [otepKey][len][bytes]...; returns byte count. */
        static int flatten(int[] ids, byte[][] utf8, byte[] dst) {
            int p = 0;
            for (int i = 0; i < ids.length; i++) {
                if (ids[i] <= 0) {
                    continue;
                }
                byte[] v = utf8[i];
                dst[p++] = (byte) (i + 1); // otep key index (slot 0 reserved for LRS)
                dst[p++] = (byte) v.length;
                System.arraycopy(v, 0, dst, p, v.length);
                p += v.length;
            }
            return p;
        }

        @Setup(Level.Iteration)
        public void resetToSteadyState() {
            // Re-establish a live span (valid=1) with all attrs populated before each window,
            // so both variants see identical attrs_data state (avoids bimodal JIT divergence).
            ctx.put(localRootSpanId, spanId, 0, traceIdLow);
            if (!ctx.setContextAttributesByIdAndBytes(constantIds, utf8)) {
                throw new IllegalStateException("resetToSteadyState failed; benchmark state invalid");
            }
        }
    }

    /** DirectByteBuffer reapply (no JNI). */
    @Benchmark
    public boolean dbb_reapply(ReapplyState rs) {
        return rs.ctx.setContextAttributesByIdAndBytes(rs.constantIds, rs.utf8);
    }

    /** Option B all-native reapply (object-array JNI + native compaction). */
    @Benchmark
    public boolean native_reapply(ProfilerState ps, ReapplyState rs) {
        return ps.profiler.setContextAttributesNative(rs.constantIds, rs.utf8);
    }

    /**
     * Option B flattened native reapply with a PRECOMPUTED blob — the realistic reapply-on-mount
     * cost, since the attribute set is stable across mounts. Hot path is just the native call
     * (3 JNI array accesses + bulk copy), no per-call serialization.
     */
    @Benchmark
    public boolean native_flat_reapply(ProfilerState ps, ReapplyState rs) {
        return ps.profiler.setContextAttributesFlatNative(rs.constantIds, rs.attrsBlob, rs.blobLen);
    }

    /**
     * Option B flattened native reapply that RE-SERIALIZES the blob every call — the fair
     * per-call comparison against {@link #dbb_reapply} (which also does per-call work from the
     * raw constantIds/utf8 inputs).
     */
    @Benchmark
    public boolean native_flat_build_reapply(ProfilerState ps, ReapplyState rs) {
        int len = ReapplyState.flatten(rs.constantIds, rs.utf8, rs.scratchBlob);
        return ps.profiler.setContextAttributesFlatNative(rs.constantIds, rs.scratchBlob, len);
    }
}
