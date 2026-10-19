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
 * {@code fjmethodid=lazy} must find {@code Klass::_trace_id} even when a test JVM, or an
 * application, already created some of the array classes calibration probes.
 *
 * <p>Calibration makes the JVM create {@code Void} arrays of several dimensions back to back and
 * looks for the offset at which their JFR trace IDs are nearly consecutive. A child JVM first
 * creates {@code Void[]} and {@code Void[][]} with a few hundred class definitions in between, so
 * those two IDs are far apart and an attempt that includes them cannot succeed. Calibration must
 * still find the offset by probing dimensions it creates itself.
 */
public class LazyTraceIdCalibrationTest extends AbstractProcessProfilerTest {
    private static final String PREFIX = "[calibration] klass_trace_id_offset=";

    @Test
    @Timeout(60)
    public void calibratesWhenLowProbeDimensionsAlreadyExist() throws Exception {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal(), "HotSpot only");
        AtomicLong offset = new AtomicLong(Long.MIN_VALUE);
        AtomicReference<String> malformed = new AtomicReference<>();
        Path recording = Files.createTempFile("lazy-calibration-", ".jfr");
        LaunchResult result;
        try {
            result = launch("lazy-calibration-preexisting-arrays", Collections.emptyList(),
                "start,cpu=10ms,cstack=vm,fjmethodid=lazy,jfr,file=" + recording, line -> {
                    if (line.startsWith(PREFIX)) {
                        String value = line.substring(PREFIX.length()).split(" ")[0];
                        if (!"null".equals(value)) {
                            try {
                                offset.set(Long.parseLong(value));
                            } catch (NumberFormatException e) {
                                // Reported below; an unset offset would only skip the test.
                                malformed.compareAndSet(null, line);
                            }
                        }
                    }
                    return LineConsumerResult.CONTINUE;
                }, null);
        } finally {
            try { Files.deleteIfExists(recording); } catch (IOException ignored) {}
        }
        assertTrue(result.inTime, "child JVM did not finish in time");
        assertEquals(0, result.exitCode, "child JVM failed");
        assertNull(malformed.get(), "unparsable offset line from the child JVM");
        Assumptions.assumeTrue(offset.get() != Long.MIN_VALUE, "build without debug counters");
        // Without JFR (e.g. 8u before 8u262) there is no trace ID to find.
        Assumptions.assumeTrue(Platform.hasJfr(), "JDK without JFR");
        assertTrue(offset.get() > 0, "trace-ID calibration failed: klass_trace_id_offset=" + offset.get());
    }
}
