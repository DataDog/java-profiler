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
 * per-thread buffer). The read-back oracle is {@link JavaProfiler}'s package-private
 * {@code test*} accessors ({@code testGetSpanId}/{@code testGetRootSpanId}/
 * {@code testReadTraceId}/{@code testReadContextAttribute}/{@code testIsContextValid}), which
 * read the same record directly and are invoked here via reflection (this test lives in a
 * different package than {@link JavaProfiler}).
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
            profiler.stop();
            profilerStarted = false;
        }
        profiler.clearTraceContext();
        profiler.resetThreadContext();
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

    private static long testGetSpanId() throws Exception {
        Method m = JavaProfiler.class.getDeclaredMethod("testGetSpanId");
        m.setAccessible(true);
        return (long) m.invoke(profiler);
    }

    private static long testGetRootSpanId() throws Exception {
        Method m = JavaProfiler.class.getDeclaredMethod("testGetRootSpanId");
        m.setAccessible(true);
        return (long) m.invoke(profiler);
    }

    private static String testReadTraceId() throws Exception {
        Method m = JavaProfiler.class.getDeclaredMethod("testReadTraceId");
        m.setAccessible(true);
        return (String) m.invoke(profiler);
    }

    private static String testReadContextAttribute(int slot) throws Exception {
        Method m = JavaProfiler.class.getDeclaredMethod("testReadContextAttribute", int.class);
        m.setAccessible(true);
        return (String) m.invoke(profiler, slot);
    }

    private static boolean testIsContextValid() throws Exception {
        Method m = JavaProfiler.class.getDeclaredMethod("testIsContextValid");
        m.setAccessible(true);
        return (boolean) m.invoke(profiler);
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

        long lrs = 0x1111222233334444L;
        long span = 0xAAAABBBBCCCCDDDDL;
        long trHi = 0x5555666677778888L;
        long trLo = 0x9999AAAABBBBCCCCL;
        profiler.setTraceContext(lrs, span, trHi, trLo, SLOT_OP, "servlet.request", SLOT_RES, "GET /users");

        assertEquals(span, testGetSpanId());
        assertEquals(lrs, testGetRootSpanId());
        assertEquals("55556666777788889999aaaabbbbcccc", testReadTraceId());
        assertEquals("servlet.request", testReadContextAttribute(SLOT_OP));
        assertEquals("GET /users", testReadContextAttribute(SLOT_RES));
    }

    @Test
    public void clearTraceContextResetsRecord() throws Exception {
        start();

        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, SLOT_OP, "op", SLOT_RES, "res");
        assertEquals(0x1L, testGetSpanId());

        profiler.clearTraceContext();
        assertEquals(0, testGetSpanId(), "spanId cleared");
        assertEquals(0, testGetRootSpanId(), "rootSpanId cleared");
        // valid=0 after clear, so attributes are not observable.
        assertNull(testReadContextAttribute(SLOT_OP), "attributes cleared");
    }

    /** setTraceContext resets custom slots, so a span-to-span transition must not leak attributes. */
    @Test
    public void spanTransitionClearsAttributes() throws Exception {
        start();

        profiler.setTraceContext(0x1L, 0x1L, 0L, 0x1L, SLOT_OP, "/api/spanA", -1, null);
        assertEquals("/api/spanA", testReadContextAttribute(SLOT_OP));

        // Next span carries no activation attributes.
        profiler.setTraceContext(0x2L, 0x2L, 0L, 0x2L, -1, null, -1, null);
        assertEquals(0x2L, testGetSpanId());
        assertNull(testReadContextAttribute(SLOT_OP), "previous span's attribute must be cleared");
    }

    @Test
    public void singleAttributeSetAndClear() throws Exception {
        start();
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null); // live span, no attrs

        assertTrue(profiler.setContextValue(SLOT_OP, "GET /api/users"));
        assertEquals("GET /api/users", testReadContextAttribute(SLOT_OP));

        profiler.clearContextValue(SLOT_OP);
        assertNull(testReadContextAttribute(SLOT_OP), "attribute cleared");
    }

    /** attrs_data overflow is reported (false), not crashed; unrelated slots keep working. */
    @Test
    public void attributeOverflowReturnsFalse() throws Exception {
        start();
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
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null);

        assertFalse(profiler.setContextValue(SLOT_OP, null), "null value rejected");
        StringBuilder sb = new StringBuilder(256);
        for (int i = 0; i < 256; i++) sb.append('y');
        assertFalse(profiler.setContextValue(SLOT_OP, sb.toString()), "oversized (256B) value rejected");
        // A subsequent valid write still works.
        assertTrue(profiler.setContextValue(SLOT_OP, "ok"));
        assertEquals("ok", testReadContextAttribute(SLOT_OP));
    }

    /**
     * setTraceContext is the activation path and rejects a zero span with IllegalArgumentException
     * (rather than silently clearing or publishing a span-less record). Clearing is clearTraceContext.
     * A rejected call must not mutate the record — a previously active span stays intact.
     */
    @Test
    public void setTraceContextRejectsZeroSpanId() throws Exception {
        start();

        profiler.setTraceContext(0x9L, 0x7L, 0L, 0x7L, -1, null, -1, null); // active span
        assertEquals(0x7L, testGetSpanId());

        assertThrows(IllegalArgumentException.class,
                () -> profiler.setTraceContext(0x2L, 0L, 0L, 0L, -1, null, -1, null),
                "spanId=0 must be rejected");

        // The rejected call is a no-op: it neither clears nor corrupts the still-active span.
        assertTrue(testIsContextValid(), "record still valid after rejected call");
        assertEquals(0x7L, testGetSpanId(), "previously active span left intact");
    }

    /**
     * clearContextValue must not resurrect a record that clearTraceContext intentionally deactivated:
     * clearing a single attribute should preserve the record's prior {@code valid} flag rather than
     * unconditionally re-publishing it with {@code valid=1}.
     */
    @Test
    public void clearContextValuePreservesInvalidState() throws Exception {
        start();

        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, SLOT_OP, "op", -1, null); // active span
        assertTrue(testIsContextValid(), "precondition: active record is valid");

        profiler.clearTraceContext();
        assertFalse(testIsContextValid(), "clearTraceContext leaves the record deactivated");

        // Clearing an attribute on a deactivated record must not flip valid back to 1.
        profiler.clearContextValue(SLOT_OP);
        assertFalse(testIsContextValid(),
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

        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null); // active span
        assertTrue(testIsContextValid(), "precondition: active record is valid");

        profiler.clearTraceContext();
        assertFalse(testIsContextValid(), "clearTraceContext leaves the record deactivated");

        // Setting an attribute on a deactivated record republishes it so the attribute is visible
        // with no active span (span/trace stay zero, but the record is valid and carries the value).
        profiler.setContextValue(SLOT_OP, "late");
        assertTrue(testIsContextValid(),
                "setContextValue must publish (valid=1) so app context is visible without a span");
        assertEquals(0, testGetSpanId(), "span stays zero — this is app context, not a span");
        assertEquals("late", testReadContextAttribute(SLOT_OP), "attribute observable without a span");
    }

    /**
     * copyContextTags reads the sidecar tag encodings written through the all-native path directly
     * from the record.
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
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null); // live span

        // encoding 0 is benign; the point is that a null byte[] does not crash and yields an empty
        // attribute rather than a dereference.
        assertTrue(setContextValue0(SLOT_OP, 0, null), "null value byte[] accepted as empty");
        assertEquals("", testReadContextAttribute(SLOT_OP), "null value stored as empty attribute");
    }

    /**
     * A zero-length value produces a bare 2-byte attrs_data entry (key + zero length). Overwriting
     * it exercises {@code otelCompactAttr}'s {@code readPos + 2 <= currentSize} guard at the exact
     * 2-byte boundary — the smallest possible entry.
     */
    @Test
    public void zeroLengthAttributeCompactsCleanly() throws Exception {
        start();
        profiler.setTraceContext(0x2L, 0x1L, 0L, 0x1L, -1, null, -1, null); // live span

        assertTrue(profiler.setContextValue(SLOT_OP, ""), "empty value written");
        assertEquals("", testReadContextAttribute(SLOT_OP), "empty attribute observable");

        // Overwrite the zero-length entry: compaction must walk over the 2-byte entry correctly.
        assertTrue(profiler.setContextValue(SLOT_OP, "now-non-empty"));
        assertEquals("now-non-empty", testReadContextAttribute(SLOT_OP));

        // Clearing it back out also compacts across the (now larger) entry without corruption.
        profiler.clearContextValue(SLOT_OP);
        assertNull(testReadContextAttribute(SLOT_OP), "attribute cleared");
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
                    // Write and read back with no yield point in between, so this vthread stays
                    // mounted on one carrier for the whole write+read.
                    profiler.setTraceContext(root, span, 0L, span, SLOT_OP, "vt", -1, null);
                    long got = testGetSpanId();
                    if (got != span) {
                        failures.add("expected span " + span + " but read " + got);
                    }
                    if (!"vt".equals(testReadContextAttribute(SLOT_OP))) {
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
