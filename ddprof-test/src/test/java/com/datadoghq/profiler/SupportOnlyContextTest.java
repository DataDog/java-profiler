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
package com.datadoghq.profiler;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Support-only context propagation tests (ContextExtractionToSupportPlan, Phase E: E.1/E.2).
 *
 * <p>These tests bypass {@link JavaProfiler} entirely and drive the package-private
 * {@link ContextStorage} / public {@link ThreadContext} / {@link OTelContext} surface directly,
 * so only {@code libJavaSupport.so} is ever loaded. This exercises the support-owned
 * {@code ThreadContext} base (native {@code support/threadContext.{h,cpp}}) with no profiler
 * factory registered — the default {@code g_thread_context_factory} yields a plain
 * {@code ThreadContext}, not a {@code ProfiledThread}.
 *
 * <p>Because these run in a shared JVM alongside profiler-loading tests, every test first
 * asserts (via {@link org.junit.jupiter.api.Assumptions}) that the profiler library has not
 * already been loaded by an earlier test in the same JVM — mirroring the isolation-check
 * pattern in {@link SupportOnlyLoadTest}. If the profiler is already mapped, the support-only
 * guarantees this test verifies cannot be attributed to this test's own actions, so the test
 * is skipped rather than made to fail spuriously.
 */
class SupportOnlyContextTest {

    private static boolean profilerLibraryMapped() throws IOException {
        try (Stream<String> lines = Files.lines(Paths.get("/proc/self/maps"))) {
            return lines.anyMatch(line -> line.contains("libjavaProfiler"));
        }
    }

    /**
     * E.1: with only libJavaSupport.so loaded, write span/trace/local-root-span-id through
     * {@link ContextStorage#initializeContextTLS0} + {@link ThreadContext}, and read them back.
     * On Linux, also assert {@code /proc/self/maps} shows no {@code libjavaProfiler} mapping —
     * the support-only load path never pulls in the profiler library. That assertion is
     * Linux-only tooling (design §2.1, §8); on other platforms only the round-trip is checked.
     */
    @Test
    void supportOnlyPropagatesSpanTraceAndRootSpanId() throws Exception {
        boolean linux = Platform.isLinux();
        if (linux) {
            Assumptions.assumeFalse(profilerLibraryMapped(),
                "libjavaProfiler.so already mapped in this JVM — cannot attribute isolation to this test");
        }
        Assumptions.assumeFalse(LibraryLoader.isLoaded(LibraryLoader.Library.PROFILER),
            "profiler library already loaded in this JVM — support-only guarantees not verifiable");

        long[] metadata = new long[6];
        ByteBuffer buffer = ContextStorage.initializeContextTLS0(metadata);
        assertNotNull(buffer, "support-only initializeContextTLS0 must succeed without the profiler");

        ThreadContext ctx = new ThreadContext(buffer, metadata);

        long traceIdHigh = 0x1122334455667788L;
        long traceIdLow = 0x99aabbccddeeff00L;
        long spanId = 0xdeadbeefL;
        long rootSpanId = 424242L;
        ctx.put(rootSpanId, spanId, traceIdHigh, traceIdLow);

        assertEquals(spanId, ctx.getSpanId(), "span id must round-trip support-only");
        assertEquals(rootSpanId, ctx.getRootSpanId(), "local root span id must round-trip support-only");
        String expectedTraceId = String.format("%016x%016x", traceIdHigh, traceIdLow);
        assertEquals(expectedTraceId, ctx.readTraceId(), "trace id must round-trip support-only");

        if (linux) {
            assertFalse(profilerLibraryMapped(),
                "libjavaProfiler.so must NOT be mapped after support-only context propagation");
        }
    }

    /**
     * E.2: publish the OTEP process {@code attribute_key_map} via {@code OTelContext.setProcessCtx0}
     * (support-only), then set a custom attribute support-only and verify the {@code attrs_data}
     * bytes are correct via the external-reader-equivalent read path
     * ({@link ThreadContext#readContextAttribute}). Also asserts the DD JFR interning sidecar slot
     * stays 0 (there is no {@code Profiler}/Dictionary to intern into in support-only mode), and
     * that repeated writes to the same slot keep succeeding and keep the OTEP value intact — i.e.
     * the mandatory {@code attrs_data} write never depends on (and is never undone by) the DD
     * sidecar path, which is the Task C.3 fix this test exercises from the support-only side.
     */
    @Test
    void supportOnlyOtepCustomAttributeRoundTripDoesNotTouchSidecar() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "OTelContext process-context publish is Linux-only");
        Assumptions.assumeFalse(profilerLibraryMapped(),
            "libjavaProfiler.so already mapped in this JVM — cannot attribute isolation to this test");
        Assumptions.assumeFalse(LibraryLoader.isLoaded(LibraryLoader.Library.PROFILER),
            "profiler library already loaded in this JVM — support-only guarantees not verifiable");

        OTelContext otel = OTelContext.getInstance();
        otel.initializeAllContext("test-env", "test-host", "rt-support-only", "test-svc", "1.0.0", "1.0.0",
            new String[] {"custom.tag"});
        OTelContext.ProcessContext published = otel.readProcessContext();
        assertNotNull(published, "process context must publish successfully support-only");
        assertArrayEquals("custom.tag key map", published.attributeKeyMap);

        long[] metadata = new long[6];
        ByteBuffer buffer = ContextStorage.initializeContextTLS0(metadata);
        assertNotNull(buffer);
        ThreadContext ctx = new ThreadContext(buffer, metadata);

        // A live (valid=1) record is required before attrs_data writes are externally observable —
        // readContextAttribute() gates on valid, matching the OTEP external-reader contract.
        ctx.put(1L, 2L, 0L, 3L);

        assertTrue(ctx.setContextAttribute(0, "checkout"),
            "setContextAttribute must succeed support-only — it never depends on the DD Dictionary");
        assertEquals("checkout", ctx.readContextAttribute(0));

        int[] sidecar = new int[1];
        ctx.copyCustoms(sidecar);
        assertEquals(0, sidecar[0], "DD sidecar slot must stay 0 support-only — no Dictionary to register into");

        // Repeat with a different value: this is the support-only equivalent of the "dictionary
        // full" fix (Task C.3.2) — in support-only mode registerConstant0 is never even called
        // (profilerPresent == false), so nothing can clear the OTEP attribute out from under a
        // sidecar-registration failure. The OTEP write always lands regardless.
        assertTrue(ctx.setContextAttribute(0, "checkout-2"));
        assertEquals("checkout-2", ctx.readContextAttribute(0),
            "OTEP attrs_data must reflect the latest value; a sidecar-side failure must never clear it");
        ctx.copyCustoms(sidecar);
        assertEquals(0, sidecar[0], "DD sidecar slot must remain 0 support-only after a second write");
    }

    /**
     * s-2 / g-6 regression: a {@link ThreadContext} constructed support-only (before the
     * profiler attaches) must start reporting the DD JFR sidecar encoding once the profiler
     * is later loaded into the same JVM — {@code setContextAttributeDirect} must re-read
     * {@link LibraryLoader#isLoaded(LibraryLoader.Library)} at the point of use rather than
     * latching {@code profilerPresent} once at construction time.
     *
     * <p>This deliberately loads {@code libjavaProfiler.so} as a side effect, which consumes
     * the "profiler not yet loaded" isolation window this test class relies on — any test in
     * this JVM that runs afterwards will correctly skip via its own {@code Assumptions} check
     * (see the class-level javadoc) rather than fail.
     */
    @Test
    void threadContextReportsSidecarEncodingAfterLateProfilerLoad() throws Exception {
        Assumptions.assumeFalse(profilerLibraryMapped(),
            "libjavaProfiler.so already mapped in this JVM — cannot attribute isolation to this test");
        Assumptions.assumeFalse(LibraryLoader.isLoaded(LibraryLoader.Library.PROFILER),
            "profiler library already loaded in this JVM — support-only guarantees not verifiable");

        long[] metadata = new long[6];
        ByteBuffer buffer = ContextStorage.initializeContextTLS0(metadata);
        assertNotNull(buffer, "support-only initializeContextTLS0 must succeed without the profiler");
        ThreadContext ctx = new ThreadContext(buffer, metadata);

        // A live (valid=1) record is required before attrs_data/sidecar writes are observable.
        ctx.put(1L, 2L, 0L, 3L);

        assertTrue(ctx.setContextAttribute(0, "before-profiler"),
            "setContextAttribute must succeed support-only");
        int[] sidecar = new int[1];
        ctx.copyCustoms(sidecar);
        assertEquals(0, sidecar[0], "DD sidecar slot must be 0 before the profiler is loaded");

        LibraryLoader.Result result = LibraryLoader.builder().library(LibraryLoader.Library.PROFILER).load();
        Assumptions.assumeTrue(result.succeeded, "profiler library failed to load: " + result.error);
        assertTrue(LibraryLoader.isLoaded(LibraryLoader.Library.PROFILER),
            "LibraryLoader must report the profiler as loaded after a successful load");

        // Same ThreadContext instance, constructed support-only: the DD sidecar encoding
        // must now be populated on the next setContextAttribute call.
        assertTrue(ctx.setContextAttribute(0, "after-profiler"));
        ctx.copyCustoms(sidecar);
        assertTrue(sidecar[0] > 0,
            "DD sidecar slot must be populated once the profiler is loaded (was latched false pre-fix)");
        assertEquals("after-profiler", ctx.readContextAttribute(0));
    }

    private static void assertArrayEquals(String message, String[] attributeKeyMap) {
        assertNotNull(attributeKeyMap, message);
        assertEquals(2, attributeKeyMap.length, message);
        assertEquals("datadog.local_root_span_id", attributeKeyMap[0], message);
        assertEquals("custom.tag", attributeKeyMap[1], message);
    }
}
