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
import com.datadoghq.profiler.OTelContext;
import com.datadoghq.profiler.ThreadContext;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Tests for OTEL-compatible context storage (OTEP #4947).
 */
public class OtelContextStorageModeTest {

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
            profiler.resetThreadContext();
            profilerStarted = false;
        }
    }

    /**
     * Tests that context round-trips correctly.
     */
    @Test
    public void testOtelStorageModeContext() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-otel", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,attributes=tag1;tag2;tag3,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        long localRootSpanId = 0x1111222233334444L;
        long spanId = 0xAAAABBBBCCCCDDDDL;
        long traceIdHigh = 0x5555666677778888L;
        long traceIdLow = 0x9999AAAABBBBCCCCL;
        profiler.setContext(localRootSpanId, spanId, traceIdHigh, traceIdLow);

        ThreadContext ctx = profiler.getThreadContext();
        assertEquals(spanId, ctx.getSpanId(), "SpanId should match");
        assertEquals(localRootSpanId, ctx.getRootSpanId(), "LocalRootSpanId should match");
        // Verify the 128-bit trace ID round-trips through the OTEP record (big-endian)
        assertEquals("55556666777788889999aaaabbbbcccc", ctx.readTraceId(), "TraceId should match");
    }


    /**
     * Tests that custom attributes are correctly written to and read back from
     * the OTEP record's attrs_data (via DirectByteBuffer). Verifies the
     * sidecar encoding is set and the UTF-8 value appears in attrs_data.
     */
    @Test
    public void testOtelModeCustomAttributes() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-attrs", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,attributes=http.route;db.system,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        // Register attribute keys
        OTelContext.getInstance().registerAttributeKeys("http.route", "db.system");

        long localRootSpanId = 0x1111222233334444L;
        long spanId = 0xAAAABBBBCCCCDDDDL;
        profiler.setContext(localRootSpanId, spanId, 0L, 0x9999L);

        ThreadContext ctx = profiler.getThreadContext();
        boolean result = ctx.setContextAttribute(0, "GET /api/users");
        assertTrue(result, "setContextAttribute should succeed");

        result = ctx.setContextAttribute(1, "postgresql");
        assertTrue(result, "setContextAttribute for second key should succeed");

        // Verify attribute values round-trip correctly through attrs_data
        assertEquals("GET /api/users", ctx.readContextAttribute(0), "http.route should round-trip");
        assertEquals("postgresql", ctx.readContextAttribute(1), "db.system should round-trip");

        // Verify trace context is still intact after attribute writes
        assertEquals(spanId, ctx.getSpanId(), "SpanId should match after setAttribute");
        assertEquals(localRootSpanId, ctx.getRootSpanId(), "LocalRootSpanId should match after setAttribute");
    }

    /**
     * Tests that attrs_data overflow is handled gracefully (returns false, no crash).
     */
    @Test
    public void testOtelModeAttributeOverflow() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-overflow", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,attributes=k0;k1;k2;k3;k4,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        OTelContext.getInstance().registerAttributeKeys("k0", "k1", "k2", "k3", "k4");

        profiler.setContext(0x2L, 0x1L, 0L, 0x3L);

        ThreadContext ctx = profiler.getThreadContext();

        // LRS is a fixed 18-byte entry (key=0, len=16, 16 hex value bytes).
        // Available for custom attrs: 612 - 18 = 594 bytes.
        // Each 255-char attr = 257 bytes. Two fit (514 ≤ 594); third overflows (771 > 594).
        StringBuilder sb = new StringBuilder(255);
        for (int i = 0; i < 255; i++) sb.append('x');
        String longValue = sb.toString();
        assertTrue(ctx.setContextAttribute(0, longValue), "First long attr should fit");
        assertTrue(ctx.setContextAttribute(1, longValue), "Second long attr should fit");
        assertFalse(ctx.setContextAttribute(2, longValue), "Third long attr should overflow");

        // Short values should still work for remaining slots
        assertTrue(ctx.setContextAttribute(3, "short"), "Short attr after overflow should work");
    }

    /**
     * Tests sequential context updates including boundary values and clearing.
     * Verifies that each setContext overwrites the previous values, that MAX_VALUE
     * round-trips correctly, and that clearContext resets both IDs to zero.
     */
    @Test
    public void testSequentialContextUpdates() {
        profiler.setContext(2L, 1L, 0, 1L);
        assertEquals(1L, profiler.getThreadContext().getSpanId());
        assertEquals(2L, profiler.getThreadContext().getRootSpanId());

        profiler.setContext(20L, 10L, 0, 10L);
        assertEquals(10L, profiler.getThreadContext().getSpanId());
        assertEquals(20L, profiler.getThreadContext().getRootSpanId());

        profiler.setContext(200L, 100L, 0, 100L);
        assertEquals(100L, profiler.getThreadContext().getSpanId());
        assertEquals(200L, profiler.getThreadContext().getRootSpanId());

        long maxValue = Long.MAX_VALUE;
        profiler.setContext(maxValue, maxValue, 0, maxValue);
        assertEquals(maxValue, profiler.getThreadContext().getSpanId(), "SpanId should be MAX_VALUE");
        assertEquals(maxValue, profiler.getThreadContext().getRootSpanId(), "RootSpanId should be MAX_VALUE");

        profiler.clearContext();
        assertEquals(0, profiler.getThreadContext().getSpanId(), "SpanId should be zero after clear");
        assertEquals(0, profiler.getThreadContext().getRootSpanId(), "RootSpanId should be zero after clear");
    }

    @Test
    public void testThreadIsolation() throws InterruptedException {
        long threadASpanId = 1000L;
        long threadARootSpanId = 1001L;
        profiler.setContext(threadARootSpanId, threadASpanId, 0, threadASpanId);
        assertEquals(threadASpanId, profiler.getThreadContext().getSpanId());
        assertEquals(threadARootSpanId, profiler.getThreadContext().getRootSpanId());

        final long threadBSpanId = 2000L;
        final long threadBRootSpanId = 2001L;
        final AssertionError[] threadBError = {null};

        Thread threadB = new Thread(() -> {
            try {
                profiler.setContext(threadBRootSpanId, threadBSpanId, 0, threadBSpanId);
                assertEquals(threadBSpanId, profiler.getThreadContext().getSpanId());
                assertEquals(threadBRootSpanId, profiler.getThreadContext().getRootSpanId());
            } catch (AssertionError e) {
                threadBError[0] = e;
            }
        }, "TestThread-B");

        threadB.start();
        threadB.join();

        if (threadBError[0] != null) throw threadBError[0];

        // Thread A's context must be unaffected
        assertEquals(threadASpanId, profiler.getThreadContext().getSpanId());
        assertEquals(threadARootSpanId, profiler.getThreadContext().getRootSpanId());
    }

    /**
     * Tests that a direct span-to-span transition (no clearContext in between)
     * does not leak custom attributes from the previous span.
     */
    @Test
    public void testSpanTransitionClearsAttributes() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-transition", ".jfr");
        profiler.execute(String.format("start,cpu=1ms,attributes=http.route,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        OTelContext.getInstance().registerAttributeKeys("http.route");

        // Span A: set a custom attribute
        profiler.setContext(0x1L, 0x1L, 0L, 0x1L);
        ThreadContext ctx = profiler.getThreadContext();
        ctx.setContextAttribute(0, "/api/spanA");

        // Transition directly to span B without clearing
        profiler.setContext(0x2L, 0x2L, 0L, 0x2L);

        // Span A's attribute must not be visible in span B's context
        assertNull(ctx.readContextAttribute(0), "Custom attribute must be cleared on span transition");
    }

    /**
     * Tests that the per-thread attribute cache isolates threads correctly.
     * "FB" and "Ea" have equal hashCode() (both 2236), so they map to the same
     * cache slot. With per-thread caches each thread owns its slot independently.
     */
    @Test
    public void testAttributeCacheIsolation() throws Exception {
        Path jfrFile = Files.createTempFile("otel-attr-cache-iso", ".jfr");
        profiler.execute(String.format("start,cpu=1ms,attributes=attr0,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;
        OTelContext.getInstance().registerAttributeKeys("attr0");

        final String valueA = "FB"; // hashCode = 2236, slot 188
        final String valueB = "Ea"; // hashCode = 2236, same slot
        final AssertionError[] errors = {null, null};
        final CountDownLatch bothWritten = new CountDownLatch(2);

        Thread threadA = new Thread(() -> {
            try {
                profiler.setContext(1L, 1L, 0L, 1L);
                ThreadContext ctx = profiler.getThreadContext();
                assertTrue(ctx.setContextAttribute(0, valueA));
                bothWritten.countDown();
                bothWritten.await(5, TimeUnit.SECONDS);
                // After thread B has written "Ea" to its own slot, A must still read "FB"
                assertEquals(valueA, ctx.readContextAttribute(0));
            } catch (AssertionError e) {
                errors[0] = e;
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }, "TestThread-CacheA");

        Thread threadB = new Thread(() -> {
            try {
                profiler.setContext(2L, 2L, 0L, 2L);
                ThreadContext ctx = profiler.getThreadContext();
                assertTrue(ctx.setContextAttribute(0, valueB));
                bothWritten.countDown();
                bothWritten.await(5, TimeUnit.SECONDS);
                assertEquals(valueB, ctx.readContextAttribute(0));
            } catch (AssertionError e) {
                errors[1] = e;
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }, "TestThread-CacheB");

        threadA.start();
        threadB.start();
        threadA.join(10_000);
        threadB.join(10_000);

        if (errors[0] != null) throw errors[0];
        if (errors[1] != null) throw errors[1];
    }
}
