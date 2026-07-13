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
package com.datadoghq.profiler.context;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ThreadContext;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Tests for the all-native OTEL context write API (OTEP #4947): {@code setTraceContext},
 * {@code clearTraceContext}, {@code setContextValue}, {@code clearContextValue}.
 *
 * <p>These write the current carrier's native OtelThreadContextRecord directly (no cached
 * DirectByteBuffer). The DirectByteBuffer read methods on {@link ThreadContext}
 * ({@code getSpanId}/{@code getRootSpanId}/{@code readTraceId}/{@code readContextAttribute}) are a
 * view over that <em>same</em> record, so they serve as the read-back oracle here.
 *
 * <p>Ordering note: the first {@link JavaProfiler#getThreadContext()} on a thread runs the
 * {@code ThreadContext} constructor, which resets the record. So every test resolves the read
 * handle <em>before</em> writing, then reads through that handle after the native write.
 */
public class AllNativeContextTest {

    // Two named slots used as the activation attributes (like dd-trace-java's operation/resource).
    private static final int SLOT_OP = 0;
    private static final int SLOT_RES = 1;

    private static JavaProfiler profiler;
    private boolean profilerStarted = false;

    @BeforeAll
    public static void setup() throws IOException {
        profiler = JavaProfiler.getInstance();
    }

    @AfterEach
    public void cleanup() {
        if (profilerStarted) {
            profiler.clearTraceContext();
            profiler.stop();
            profiler.resetThreadContext();
            profilerStarted = false;
        }
    }

    private void start() throws IOException {
        Path jfr = Files.createTempFile("native-ctx", ".jfr");
        profiler.execute("start,cpu=1ms,attributes=op;res;k2;k3;k4,jfr,file=" + jfr.toAbsolutePath());
        profilerStarted = true;
    }

    /**
     * Invokes the private {@code setContextValue0} JNI primitive directly, bypassing the public
     * {@link JavaProfiler#setContextValue} wrapper. Needed to reach the native {@code arr == null}
     * guard in {@code otelReadUtf8}: the public path maps a null value to a slot clear, so it never
     * passes a null {@code byte[]} through to native with a live slot.
     */
    private static boolean setContextValue0(int slot, int encoding, byte[] utf8) throws Exception {
        Method m = JavaProfiler.class.getDeclaredMethod(
                "setContextValue0", int.class, int.class, byte[].class);
        m.setAccessible(true);
        return (boolean) m.invoke(null, slot, encoding, utf8);
    }

    /** Reads the record's {@code valid} byte through the ThreadContext buffer (test-only introspection). */
    private static int readValidByte(ThreadContext ctx) throws Exception {
        java.lang.reflect.Field bufField = ThreadContext.class.getDeclaredField("ctxBuffer");
        bufField.setAccessible(true);
        java.nio.ByteBuffer buf = (java.nio.ByteBuffer) bufField.get(ctx);
        java.lang.reflect.Field offField = ThreadContext.class.getDeclaredField("validOffset");
        offField.setAccessible(true);
        int off = (int) offField.get(ctx);
        return buf.get(off) & 0xFF;
    }

    /** {@code Thread.ofVirtual().start(task)} via reflection so this compiles with --release 8. */
    private static Thread startVirtualThread(Runnable task) throws Exception {
        Method ofVirtual = Thread.class.getMethod("ofVirtual");
        Object builder = ofVirtual.invoke(null);
        Class<?> builderInterface = Class.forName("java.lang.Thread$Builder");
        Method start = builderInterface.getMethod("start", Runnable.class);
        return (Thread) start.invoke(builder, task);
    }

    @Test
    public void setTraceContextRoundTrips() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();

        long lrs = 0x1111222233334444L;
        long span = 0xAAAABBBBCCCCDDDDL;
        long trHi = 0x5555666677778888L;
        long trLo = 0x9999AAAABBBBCCCCL;
        profiler.setTraceContext(lrs, span, trHi, trLo, SLOT_OP, "servlet.request", SLOT_RES, "GET /users");

        assertEquals(span, ctx.getSpanId());
        assertEquals(lrs, ctx.getRootSpanId());
        assertEquals("55556666777788889999aaaabbbbcccc", ctx.readTraceId());
        assertEquals("servlet.request", ctx.readContextAttribute(SLOT_OP));
        assertEquals("GET /users", ctx.readContextAttribute(SLOT_RES));
    }

    /** The native write must produce the same observable record state as the DirectByteBuffer path. */
    @Test
    public void nativeMatchesDirectByteBufferWrite() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();

        long lrs = 0x0102030405060708L;
        long span = 0x1122334455667788L;
        long trHi = 0xAABBCCDDEEFF0011L;
        long trLo = 0x2233445566778899L;

        // DirectByteBuffer path (deprecated).
        profiler.setContext(lrs, span, trHi, trLo);
        ctx.setContextAttribute(SLOT_OP, "servlet.request");
        ctx.setContextAttribute(SLOT_RES, "GET /users/{id}");
        long dbbSpan = ctx.getSpanId();
        long dbbRoot = ctx.getRootSpanId();
        String dbbTrace = ctx.readTraceId();
        String dbbOp = ctx.readContextAttribute(SLOT_OP);
        String dbbRes = ctx.readContextAttribute(SLOT_RES);

        profiler.clearTraceContext();
        assertEquals(0, ctx.getSpanId(), "precondition: cleared before native write");

        // All-native path — identical inputs.
        profiler.setTraceContext(lrs, span, trHi, trLo, SLOT_OP, "servlet.request", SLOT_RES, "GET /users/{id}");

        assertEquals(dbbSpan, ctx.getSpanId(), "spanId");
        assertEquals(dbbRoot, ctx.getRootSpanId(), "rootSpanId");
        assertEquals(dbbTrace, ctx.readTraceId(), "traceId");
        assertEquals(dbbOp, ctx.readContextAttribute(SLOT_OP), "op attribute");
        assertEquals(dbbRes, ctx.readContextAttribute(SLOT_RES), "resource attribute");
    }

    @Test
    public void clearTraceContextResetsRecord() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();

        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, SLOT_OP, "op", SLOT_RES, "res");
        assertEquals(0x1L, ctx.getSpanId());

        profiler.clearTraceContext();
        assertEquals(0, ctx.getSpanId(), "spanId cleared");
        assertEquals(0, ctx.getRootSpanId(), "rootSpanId cleared");
        // valid=0 after clear, so attributes are not observable.
        assertNull(ctx.readContextAttribute(SLOT_OP), "attributes cleared");
    }

    /** setTraceContext resets custom slots, so a span-to-span transition must not leak attributes. */
    @Test
    public void spanTransitionClearsAttributes() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();

        profiler.setTraceContext(0x1L, 0x1L, 0L, 0x1L, SLOT_OP, "/api/spanA", -1, null);
        assertEquals("/api/spanA", ctx.readContextAttribute(SLOT_OP));

        // Next span carries no activation attributes.
        profiler.setTraceContext(0x2L, 0x2L, 0L, 0x2L, -1, null, -1, null);
        assertEquals(0x2L, ctx.getSpanId());
        assertNull(ctx.readContextAttribute(SLOT_OP), "previous span's attribute must be cleared");
    }

    @Test
    public void singleAttributeSetAndClear() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null); // live span, no attrs

        assertTrue(profiler.setContextValue(SLOT_OP, "GET /api/users"));
        assertEquals("GET /api/users", ctx.readContextAttribute(SLOT_OP));

        profiler.clearContextValue(SLOT_OP);
        assertNull(ctx.readContextAttribute(SLOT_OP), "attribute cleared");
    }

    /** attrs_data overflow is reported (false), not crashed; unrelated slots keep working. */
    @Test
    public void attributeOverflowReturnsFalse() throws Exception {
        start();
        profiler.getThreadContext();
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x3L, -1, null, -1, null);

        StringBuilder sb = new StringBuilder(255);
        for (int i = 0; i < 255; i++) sb.append('x');
        String longValue = sb.toString(); // 255 bytes -> 257-byte entry

        // Two 257-byte entries fit in 594 available bytes; the third overflows.
        assertTrue(profiler.setContextValue(0, longValue), "first long attr fits");
        assertTrue(profiler.setContextValue(1, longValue), "second long attr fits");
        assertFalse(profiler.setContextValue(2, longValue), "third long attr overflows");
        assertTrue(profiler.setContextValue(3, "short"), "short attr after overflow still fits");
    }

    /** Rejected values (null / oversized) return false without corrupting the record. */
    @Test
    public void rejectedValuesReturnFalse() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null);

        assertFalse(profiler.setContextValue(SLOT_OP, null), "null value rejected");
        StringBuilder sb = new StringBuilder(256);
        for (int i = 0; i < 256; i++) sb.append('y');
        assertFalse(profiler.setContextValue(SLOT_OP, sb.toString()), "oversized (256B) value rejected");
        // A subsequent valid write still works.
        assertTrue(profiler.setContextValue(SLOT_OP, "ok"));
        assertEquals("ok", ctx.readContextAttribute(SLOT_OP));
    }

    /** The deprecated DBB path and the all-native path write the same record and interleave cleanly. */
    @Test
    public void coexistenceOfDbbAndNativePaths() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();

        profiler.setContext(0xA0L, 0xA1L, 0L, 0xA1L);           // DBB
        assertEquals(0xA1L, ctx.getSpanId());

        profiler.setTraceContext(0xB0L, 0xB1L, 0L, 0xB1L, -1, null, -1, null); // native
        assertEquals(0xB1L, ctx.getSpanId());

        ctx.setContextAttribute(SLOT_OP, "dbb-value");          // DBB attribute
        assertEquals("dbb-value", ctx.readContextAttribute(SLOT_OP));

        assertTrue(profiler.setContextValue(SLOT_RES, "native-value")); // native attribute
        assertEquals("native-value", ctx.readContextAttribute(SLOT_RES));
        assertEquals("dbb-value", ctx.readContextAttribute(SLOT_OP), "DBB-written attr still intact");
    }

    /**
     * setTraceContext is the activation path and rejects a zero span with IllegalArgumentException
     * (rather than silently clearing or publishing a span-less record). Clearing is clearTraceContext.
     * A rejected call must not mutate the record — a previously active span stays intact.
     */
    @Test
    public void setTraceContextRejectsZeroSpanId() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();

        profiler.setTraceContext(0x9L, 0x7L, 0L, 0x7L, -1, null, -1, null); // active span
        assertEquals(0x7L, ctx.getSpanId());

        assertThrows(IllegalArgumentException.class,
                () -> profiler.setTraceContext(0x2L, 0L, 0L, 0L, -1, null, -1, null),
                "spanId=0 must be rejected");

        // The rejected call is a no-op: it neither clears nor corrupts the still-active span.
        assertEquals(1, readValidByte(ctx), "record still valid after rejected call");
        assertEquals(0x7L, ctx.getSpanId(), "previously active span left intact");
    }

    /**
     * clearContextValue must not resurrect a record that clearTraceContext intentionally deactivated:
     * clearing a single attribute should preserve the record's prior {@code valid} flag rather than
     * unconditionally re-publishing it with {@code valid=1}.
     */
    @Test
    public void clearContextValuePreservesInvalidState() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();

        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, SLOT_OP, "op", -1, null); // active span
        assertEquals(1, readValidByte(ctx), "precondition: active record is valid");

        profiler.clearTraceContext();
        assertEquals(0, readValidByte(ctx), "clearTraceContext leaves the record deactivated");

        // Clearing an attribute on a deactivated record must not flip valid back to 1.
        profiler.clearContextValue(SLOT_OP);
        assertEquals(0, readValidByte(ctx),
                "clearContextValue must preserve valid=0; a deactivated record must stay deactivated");
    }

    /**
     * setContextValue publishes the record (valid=1) even with no active span: application-owned
     * attributes are visible independent of span activation (dd-trace-java's model — an attribute
     * like {@code http.route}, or app context reapplied after a span deactivates, must be observable
     * between spans). Contrast {@link #clearContextValuePreservesInvalidState()}: clearing must not
     * resurrect a deactivated record, but setting a value deliberately does.
     */
    @Test
    public void setContextValuePublishesAppContextWithoutSpan() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();

        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null); // active span
        assertEquals(1, readValidByte(ctx), "precondition: active record is valid");

        profiler.clearTraceContext();
        assertEquals(0, readValidByte(ctx), "clearTraceContext leaves the record deactivated");

        // Setting an attribute on a deactivated record republishes it so the attribute is visible
        // with no active span (span/trace stay zero, but the record is valid and carries the value).
        profiler.setContextValue(SLOT_OP, "late");
        assertEquals(1, readValidByte(ctx),
                "setContextValue must publish (valid=1) so app context is visible without a span");
        assertEquals(0, ctx.getSpanId(), "span stays zero — this is app context, not a span");
        assertEquals("late", ctx.readContextAttribute(SLOT_OP), "attribute observable without a span");
    }

    /**
     * copyContextTags reads the sidecar tag encodings written through the all-native path directly
     * from the record — without going through ThreadContext (which would reset the record). The test
     * never calls getThreadContext, proving the native read observes native writes.
     */
    @Test
    public void copyContextTagsReadsNativeEncodings() throws Exception {
        start();
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null); // active span
        assertTrue(profiler.setContextValue(SLOT_OP, "op-value"));
        assertTrue(profiler.setContextValue(SLOT_RES, "res-value"));

        int[] tags = new int[10];
        profiler.copyContextTags(tags);
        assertNotEquals(0, tags[SLOT_OP], "slot with a value has a non-zero encoding");
        assertNotEquals(0, tags[SLOT_RES], "slot with a value has a non-zero encoding");
        assertEquals(0, tags[5], "unset slot reads back zero");

        profiler.clearContextValue(SLOT_OP);
        profiler.copyContextTags(tags);
        assertEquals(0, tags[SLOT_OP], "cleared slot reads back zero");
        assertNotEquals(0, tags[SLOT_RES], "untouched slot still set");
    }

    /**
     * A null {@code byte[]} value at the JNI boundary must be treated as an empty value (the native
     * {@code arr == null} guard), not dereferenced. The public API can't produce this, so we call
     * the {@code setContextValue0} primitive directly with a live slot and a null array.
     */
    @Test
    public void nativeNullValueByteArrayIsTreatedAsEmpty() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null); // live span

        // encoding 0 is benign; the point is that a null byte[] does not crash and yields an empty
        // attribute rather than a dereference.
        assertTrue(setContextValue0(SLOT_OP, 0, null), "null value byte[] accepted as empty");
        assertEquals("", ctx.readContextAttribute(SLOT_OP), "null value stored as empty attribute");
    }

    /**
     * A zero-length value produces a bare 2-byte attrs_data entry (key + zero length). Overwriting
     * it exercises {@code otelCompactAttr}'s {@code readPos + 2 <= currentSize} guard at the exact
     * 2-byte boundary — the smallest possible entry.
     */
    @Test
    public void zeroLengthAttributeCompactsCleanly() throws Exception {
        start();
        ThreadContext ctx = profiler.getThreadContext();
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null); // live span

        assertTrue(profiler.setContextValue(SLOT_OP, ""), "empty value written");
        assertEquals("", ctx.readContextAttribute(SLOT_OP), "empty attribute observable");

        // Overwrite the zero-length entry: compaction must walk over the 2-byte entry correctly.
        assertTrue(profiler.setContextValue(SLOT_OP, "now-non-empty"));
        assertEquals("now-non-empty", ctx.readContextAttribute(SLOT_OP));

        // Clearing it back out also compacts across the (now larger) entry without corruption.
        profiler.clearContextValue(SLOT_OP);
        assertNull(ctx.readContextAttribute(SLOT_OP), "attribute cleared");
    }

    /**
     * An out-of-range slot is a caller programming error, not a data condition, so the slot methods
     * throw IllegalArgumentException (rather than silently swallowing it). The boundary is the native
     * DD_TAGS_CAPACITY of 10, guarded by {@code MaxContextSlotsTest}. {@code setContextValue}'s
     * {@code false} return is reserved for data conditions (null / oversized / Dictionary full).
     */
    @Test
    public void slotBoundaryIsRejected() throws Exception {
        start();
        profiler.getThreadContext();
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null); // live span

        final int capacity = 10; // native DD_TAGS_CAPACITY; drift caught by MaxContextSlotsTest
        assertTrue(profiler.setContextValue(capacity - 1, "last-slot"), "highest valid slot accepted");

        // setContextValue: out-of-range slots throw (programming error), not return false.
        assertThrows(IllegalArgumentException.class, () -> profiler.setContextValue(capacity, "oob"),
                "slot == capacity rejected");
        assertThrows(IllegalArgumentException.class, () -> profiler.setContextValue(capacity + 1, "oob"),
                "slot > capacity rejected");
        assertThrows(IllegalArgumentException.class, () -> profiler.setContextValue(-1, "oob"),
                "negative slot rejected");

        // clearContextValue: same contract.
        assertThrows(IllegalArgumentException.class, () -> profiler.clearContextValue(capacity),
                "clearContextValue out-of-range slot rejected");

        // setTraceContext: a non-negative out-of-range activation slot throws; negative is the
        // documented skip sentinel and must NOT throw.
        assertThrows(IllegalArgumentException.class,
                () -> profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, capacity, "oob", -1, null),
                "setTraceContext out-of-range slot0 rejected");
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -5, null, -1, null); // negative slots: skip, no throw
    }

    /**
     * Native writes issued from many mounted virtual threads land on a coherent per-carrier record.
     * Each vthread writes a unique span and reads it back with no blocking point in between, so it
     * stays mounted on one carrier for the write+read and must observe exactly its own value. This
     * is the migration-safe write path: it resolves the current carrier inside the JNI call rather
     * than caching a carrier-bound buffer.
     */
    @Test
    public void nativeWritesFromVirtualThreadsAreCoherent() throws Exception {
        assumeTrue(Platform.isJavaVersionAtLeast(21), "virtual threads require JDK 21+");
        start();

        final int nThreads = 512;
        final CountDownLatch done = new CountDownLatch(nThreads);
        final ConcurrentLinkedQueue<String> failures = new ConcurrentLinkedQueue<>();

        for (int i = 0; i < nThreads; i++) {
            final long span = 0x1000L + i;
            final long root = 0x900000L + i;
            startVirtualThread(() -> {
                try {
                    // Resolve the read handle first (may init/reset the carrier record), then write
                    // and read back with no yield point in between.
                    ThreadContext ctx = profiler.getThreadContext();
                    profiler.setTraceContext(root, span, 0L, span, SLOT_OP, "vt", -1, null);
                    long got = ctx.getSpanId();
                    if (got != span) {
                        failures.add("expected span " + span + " but read " + got);
                    }
                    if (!"vt".equals(ctx.readContextAttribute(SLOT_OP))) {
                        failures.add("attribute mismatch for span " + span);
                    }
                } catch (Throwable t) {
                    failures.add("exception: " + t);
                } finally {
                    done.countDown();
                }
            });
        }

        assertTrue(done.await(60, TimeUnit.SECONDS), "virtual threads did not finish in time");
        assertTrue(failures.isEmpty(), "native vthread writes were incoherent: " + failures);
    }
}
