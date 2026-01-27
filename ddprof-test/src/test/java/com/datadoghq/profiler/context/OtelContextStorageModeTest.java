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
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Tests for OTEL-compatible context storage mode.
 *
 * <p>The profiler supports two context storage modes controlled by the {@code ctxstorage} option:
 * <ul>
 *   <li>{@code profiler} (default): Uses TLS-based storage with checksum validation</li>
 *   <li>{@code otel}: Uses OTEL-compatible ring buffer storage (Linux only)</li>
 * </ul>
 *
 * <p>The OTEL mode creates a named mmap region that can be discovered by external
 * profilers (like DDProf) via {@code /proc/<pid>/maps}.
 *
 * <p>Note: The Java API (getThreadContext) reads from TLS, not the OTEL buffer.
 * Full OTEL mode verification requires external profiler integration or a native
 * JNI method to read from the OTEL buffer.
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
    }

    /**
     * Tests that the default (profiler) mode works correctly.
     * Context values written should be readable back via TLS.
     */
    @Test
    public void testDefaultProfilerModeContext() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-default", ".jfr");

        profiler.execute(String.format("start,cpu=1ms,jfr,file=%s", jfrFile.toAbsolutePath()));
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
     * Tests that OTEL storage mode starts successfully and creates a discoverable buffer on Linux.
     * The OTEL mode creates a named mmap region that external profilers can find.
     */
    @Test
    public void testOtelStorageModeStartsOnLinux() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "OTEL storage mode only fully supported on Linux");

        Path jfrFile = Files.createTempFile("otel-ctx-otel", ".jfr");

        // Start profiler with OTEL context storage mode - should not throw
        profiler.execute(String.format("start,cpu=1ms,ctxstorage=otel,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        // Set context - this writes to the OTEL buffer
        long spanId = 0xAAAABBBBCCCCDDDDL;
        long rootSpanId = 0x1111222233334444L;
        profiler.setContext(spanId, rootSpanId);

        // Verify context can be read back via getThreadContext() (routes through JNI in OTEL mode)
        // This is the primary functional test - context must round-trip correctly
        ThreadContext ctx = profiler.getThreadContext();
        assertEquals(spanId, ctx.getSpanId(), "SpanId should match in OTEL mode");
        assertEquals(rootSpanId, ctx.getRootSpanId(), "RootSpanId should match in OTEL mode");

        // Verify mmap region naming in /proc/self/maps (informational)
        // Note: PR_SET_VMA_ANON_NAME requires kernel 5.17+ and may not work in all environments
        // The OTEL buffer still works for discovery via magic number scanning if naming fails
        boolean hasNamedRegion = checkMapsContains("DD_OTEL_CTX");
        if (!hasNamedRegion) {
            System.out.println("INFO: DD_OTEL_CTX mmap naming not available " +
                "(requires kernel 5.17+ with PR_SET_VMA_ANON_NAME support)");
        }
    }

    /**
     * Tests that OTEL mode can be requested on any platform without crashing.
     * On non-Linux systems, it falls back to profiler mode.
     */
    @Test
    public void testOtelModeStartsOnAnyPlatform() throws Exception {
        Path jfrFile = Files.createTempFile("otel-ctx-any", ".jfr");

        // Start profiler with OTEL context storage mode - should not throw on any platform
        profiler.execute(String.format("start,cpu=1ms,ctxstorage=otel,jfr,file=%s", jfrFile.toAbsolutePath()));
        profilerStarted = true;

        // Context operations should not crash
        profiler.setContext(0x123L, 0x456L);

        // On all platforms, the profiler should be running
        // (Context read verification is platform-specific due to TLS vs OTEL buffer)
    }

    /**
     * Checks if /proc/self/maps contains the specified string.
     * Java 8 compatible implementation.
     */
    private boolean checkMapsContains(String searchString) throws IOException {
        Path mapsFile = Paths.get("/proc/self/maps");
        if (!Files.exists(mapsFile)) {
            return false;
        }
        try (BufferedReader reader = Files.newBufferedReader(mapsFile, StandardCharsets.UTF_8)) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.contains(searchString)) {
                    return true;
                }
            }
        }
        return false;
    }
}
