/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Collections;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * {@code fjmethodid=lazy} must find {@code Klass::_trace_id} whatever array classes the application
 * has created.
 *
 * <p>Calibration looks for the offset at which a few freshly created array klasses hold nearly
 * consecutive JFR trace IDs. If its probes were classes that already existed, created far apart,
 * the real field would fail that check while another one could pass it: the mirrors' heap
 * addresses, shifted right by 16, can be distinct and close together. A child JVM therefore creates
 * {@code Void} arrays of many dimensions, far apart, before the profiler starts, and must
 * calibrate to the same offset as a child JVM that creates none.
 */
public class LazyTraceIdCalibrationTest extends AbstractProcessProfilerTest {
    private static final String PREFIX = "[calibration] klass_trace_id_offset=";

    @Test
    @Timeout(90)
    public void calibratesRegardlessOfPreexistingArrayClasses() throws Exception {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal(), "HotSpot only");
        // Without JFR (e.g. 8u before 8u262) there is no trace ID to find.
        Assumptions.assumeTrue(Platform.hasJfr(), "JDK without JFR");
        long reference = calibratedOffset(0);
        Assumptions.assumeTrue(reference != Long.MIN_VALUE, "build without debug counters");
        assertTrue(reference > 0, "trace-ID calibration failed: klass_trace_id_offset=" + reference);
        assertEquals(reference, calibratedOffset(24),
                "calibration with pre-created Void arrays found a different offset");
    }

    /**
     * The offset a child JVM calibrates to after creating {@code Void} arrays of dimensions 1 to
     * {@code dims}, or {@link Long#MIN_VALUE} if the build has no debug counters.
     */
    private long calibratedOffset(int dims) throws Exception {
        AtomicLong offset = new AtomicLong(Long.MIN_VALUE);
        AtomicReference<String> malformed = new AtomicReference<>();
        Path recording = Files.createTempFile("lazy-calibration-", ".jfr");
        LaunchResult result;
        try {
            result = launch("lazy-calibration-preexisting-arrays",
                Collections.singletonList("-Dddprof_test.calibration_dims=" + dims),
                "start,cpu=10ms,cstack=vm,fjmethodid=lazy,jfr,file=" + recording, line -> {
                    if (line.startsWith(PREFIX)) {
                        String value = line.substring(PREFIX.length()).split(" ")[0];
                        if (!"null".equals(value)) {
                            try {
                                offset.set(Long.parseLong(value));
                            } catch (NumberFormatException e) {
                                malformed.compareAndSet(null, line);
                            }
                        }
                    }
                    return LineConsumerResult.CONTINUE;
                }, null);
        } finally {
            try { Files.deleteIfExists(recording); } catch (IOException ignored) {}
        }
        assertTrue(result.inTime, "child JVM did not finish in time (dims=" + dims + ")");
        assertEquals(0, result.exitCode, "child JVM failed (dims=" + dims + ")");
        assertNull(malformed.get(), "unparsable offset line from the child JVM");
        return offset.get();
    }
}
