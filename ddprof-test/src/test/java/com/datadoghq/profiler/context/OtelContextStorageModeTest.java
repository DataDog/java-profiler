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
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ThreadContext;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Tests for OTEL-compatible context storage mode (OTEP #4947).
 *
 * <p>The profiler supports two context storage modes controlled by the {@code ctxstorage} option:
 * <ul>
 *   <li>{@code profiler} (default): Uses TLS-based storage with checksum validation</li>
 *   <li>{@code otel}: Uses OTEP #4947 TLS pointer (custom_labels_current_set_v2)</li>
 * </ul>
 *
 * <p>The OTEL mode publishes a {@code __thread} pointer discoverable via ELF dynsym
 * that external profilers (like the OTel eBPF profiler) can resolve per-thread.
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
            profilerStarted = false;
        }
        // Reset cached ThreadContext after profiler stops (no active sampling).
        // The next test's profiler.execute() will start fresh, and the ThreadContext
        // created afterward will pick up the correct otelMode.
        profiler.resetThreadContext();
    }

    /**
     * Tests that the default (profiler) mode works correctly.
     * Context values written should be readable back via TLS.
     */
    @Test
    public void testDefaultProfilerModeContext() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-default", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,ctxstorage=profiler,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        // Clear any previous context
        profiler.setContext(0, 0);

        // Write context
        long spanId = 0x1234567890ABCDEFL;
        long rootSpanId = 0xFEDCBA0987654321L;
        profiler.setContext(spanId, rootSpanId);

        // Verify context is readable from TLS
        ThreadContext ctx = profiler.getThreadContext();
        assertEquals(spanId, ctx.getSpanId(), "SpanId should match");
        assertEquals(rootSpanId, ctx.getRootSpanId(), "RootSpanId should match");
    }

    /**
     * Tests that OTEL storage mode starts successfully and context round-trips correctly.
     * On Linux, the custom_labels_current_set_v2 TLS symbol is discoverable via ELF dynsym.
     */
    @Test
    public void testOtelStorageModeContext() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-otel", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,ctxstorage=otel,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        // Reset cached ThreadContext so it picks up the current OTEL mode
        profiler.resetThreadContext();

        long localRootSpanId = 0x1111222233334444L;
        long spanId = 0xAAAABBBBCCCCDDDDL;
        long traceIdHigh = 0x5555666677778888L;
        long traceIdLow = 0x9999AAAABBBBCCCCL;
        profiler.setContext(localRootSpanId, spanId, traceIdHigh, traceIdLow);

        ThreadContext ctx = profiler.getThreadContext();
        assertEquals(spanId, ctx.getSpanId(), "SpanId should match in OTEL mode");
        assertEquals(localRootSpanId, ctx.getRootSpanId(), "LocalRootSpanId should match in OTEL mode");
    }

    /**
     * Tests that OTEL mode can be requested on any platform without crashing.
     */
    @Test
    public void testOtelModeStartsOnAnyPlatform() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-any", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,ctxstorage=otel,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        profiler.resetThreadContext();

        // Context operations should not crash
        profiler.setContext(0x456L, 0x123L, 0L, 0x789L);
    }

    /**
     * Tests that clearing context in OTEL mode sets values back to zero.
     */
    @Test
    public void testOtelModeClearContext() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-clear", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,ctxstorage=otel,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        profiler.resetThreadContext();

        profiler.setContext(0xCAFEBABEL, 0xDEADBEEFL, 0L, 0x12345678L);
        profiler.clearContext();

        ThreadContext ctx = profiler.getThreadContext();
        assertEquals(0, ctx.getSpanId(), "SpanId should be zero after clear");
        assertEquals(0, ctx.getRootSpanId(), "RootSpanId should be zero after clear");
    }

    /**
     * Tests that custom attributes round-trip correctly in OTEL mode.
     * Registers attribute keys, sets values via setContextAttribute.
     */
    @Test
    public void testOtelModeCustomAttributes() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-attrs", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,ctxstorage=otel,contextattribute=http.route;db.system,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        // Register attribute keys
        OTelContext.getInstance().registerAttributeKeys("http.route", "db.system");

        profiler.resetThreadContext();

        long localRootSpanId = 0x1111222233334444L;
        long spanId = 0xAAAABBBBCCCCDDDDL;
        profiler.setContext(localRootSpanId, spanId, 0L, 0x9999L);

        ThreadContext ctx = profiler.getThreadContext();
        boolean result = ctx.setContextAttribute(0, "GET /api/users");
        assertTrue(result, "setContextAttribute should succeed");

        result = ctx.setContextAttribute(1, "postgresql");
        assertTrue(result, "setContextAttribute for second key should succeed");

        // Verify trace context is still intact
        assertEquals(spanId, ctx.getSpanId(), "SpanId should match after setAttribute");
        assertEquals(localRootSpanId, ctx.getRootSpanId(), "LocalRootSpanId should match after setAttribute");
    }

    /**
     * Tests that setContextAttribute works in profiler mode as fallback
     * (registers constant + writes to Context.tags[]).
     */
    @Test
    public void testProfilerModeSetContextAttribute() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-prof-attr", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,contextattribute=http.route,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        profiler.setContext(0x123L, 0x456L);

        ThreadContext ctx = profiler.getThreadContext();
        boolean result = ctx.setContextAttribute(0, "POST /api/orders");
        assertTrue(result, "setContextAttribute should work in profiler mode");
    }

    /**
     * Tests that attrs_data overflow is handled gracefully (returns false, no crash).
     */
    @Test
    public void testOtelModeAttributeOverflow() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-overflow", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,ctxstorage=otel,contextattribute=k0;k1;k2;k3;k4,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        OTelContext.getInstance().registerAttributeKeys("k0", "k1", "k2", "k3", "k4");

        profiler.resetThreadContext();

        profiler.setContext(0x2L, 0x1L, 0L, 0x3L);

        ThreadContext ctx = profiler.getThreadContext();

        // Fill up attrs_data with long values (255 bytes each = 257 bytes per entry)
        // 612 / 257 = 2 full entries, third should fail
        StringBuilder sb = new StringBuilder(255);
        for (int i = 0; i < 255; i++) sb.append('x');
        String longValue = sb.toString();
        assertTrue(ctx.setContextAttribute(0, longValue), "First long attr should fit");
        assertTrue(ctx.setContextAttribute(1, longValue), "Second long attr should fit");
        assertFalse(ctx.setContextAttribute(2, longValue), "Third long attr should overflow");

        // Short values should still work for remaining slots
        assertTrue(ctx.setContextAttribute(3, "short"), "Short attr after overflow should work");
    }
}
