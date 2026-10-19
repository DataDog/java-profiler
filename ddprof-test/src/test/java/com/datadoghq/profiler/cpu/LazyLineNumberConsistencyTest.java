/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Checks the line number tables {@code fjmethodid=lazy} decodes from HotSpot's compressed
 * {@code ConstMethod} tables against the ones JVMTI {@code GetLineNumberTable} returns.
 *
 * <p>A fresh child JVM, in which nothing has allocated jmethodIDs for most classes yet, runs the
 * same JDK-heavy workload twice: first in lazy mode, where frames without a jmethodID are
 * resolved from VM metadata, then with {@code fjmethodid=true}, where every frame is resolved
 * through JVMTI. Every (method, bytecode index) that both recordings contain must map to the
 * same line in both.
 */
public class LazyLineNumberConsistencyTest extends AbstractProcessProfilerTest {
    private static final String LAZY = "cpu=1ms,cstack=vm,fjmethodid=lazy";
    private static final String JVMTI = "cpu=1ms,cstack=vm,fjmethodid=true";
    // Enough frames for the comparison to cover many methods and both encodings of the
    // compressed table, without depending on how much the scheduler lets the workload run.
    private static final int MIN_COMMON_FRAMES = 20;

    @Test
    @Timeout(120)
    public void lazyLineNumbersMatchJvmti() throws Exception {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal(), "HotSpot only");

        Path lazyRecording = Files.createTempFile("lazy-lines-vm-", ".jfr");
        Path jvmtiRecording = Files.createTempFile("lazy-lines-jvmti-", ".jfr");
        try {
            AtomicLong lazyResolved = new AtomicLong(-1);
            AtomicReference<String> malformed = new AtomicReference<>();
            LaunchResult result = launch("line-numbers", Collections.emptyList(),
                    "start," + LAZY + ",jfr,file=" + lazyRecording + ";start," + JVMTI + ",jfr,file=" + jvmtiRecording,
                    line -> {
                        String prefix = "[line-numbers] method_resolve_lazy_resolved=";
                        // The first line is the lazy session's.
                        if (line.startsWith(prefix) && lazyResolved.get() < 0) {
                            String value = line.substring(prefix.length());
                            try {
                                lazyResolved.set("null".equals(value) ? 0 : Long.parseLong(value));
                            } catch (NumberFormatException e) {
                                // Reported below; an unset count would only skip the test.
                                malformed.compareAndSet(null, line);
                            }
                        }
                        return LineConsumerResult.CONTINUE;
                    }, null);
            assertTrue(result.inTime, "child JVM did not finish in time");
            assertEquals(0, result.exitCode, "child JVM failed");
            assertNull(malformed.get(), "unparsable counter line from the child JVM");
            // Lazy mode falls back to partial mode where it cannot run (e.g. no JFR trace IDs);
            // its frames still come from VM metadata, but the counter stays 0.
            Assumptions.assumeTrue(lazyResolved.get() > 0, "lazy mode resolved no raw frames");

            Map<String, Integer> lazyLines = linesByFrame(lazyRecording);
            Map<String, Integer> jvmtiLines = linesByFrame(jvmtiRecording);
            List<String> mismatches = new ArrayList<>();
            int common = 0;
            for (Map.Entry<String, Integer> e : lazyLines.entrySet()) {
                Integer jvmtiLine = jvmtiLines.get(e.getKey());
                if (jvmtiLine == null) {
                    continue;
                }
                common++;
                if (!jvmtiLine.equals(e.getValue())) {
                    mismatches.add(e.getKey() + ": lazy " + e.getValue() + ", JVMTI " + jvmtiLine);
                }
            }
            System.out.println("raw frames resolved=" + lazyResolved.get() + ", frames in both recordings=" + common
                    + ", mismatches=" + mismatches.size());
            assertTrue(common >= MIN_COMMON_FRAMES, "only " + common + " frames in both recordings");
            assertTrue(mismatches.isEmpty(), "line numbers differ: " + mismatches);
        } finally {
            try { Files.deleteIfExists(lazyRecording); } catch (IOException ignored) {}
            try { Files.deleteIfExists(jvmtiRecording); } catch (IOException ignored) {}
        }
    }

    /**
     * Maps "class.method descriptor @bci" to the line the recording gives that frame, for every
     * frame of {@code datadog.ExecutionSample}. Frames without a line are kept, so that a table
     * one side failed to decode shows up as a mismatch.
     */
    private static Map<String, Integer> linesByFrame(Path recording) throws Exception {
        Map<String, Integer> lines = new HashMap<>();
        JfrEvents.forEach(recording, "datadog.ExecutionSample"::equals, event -> {
            if (!event.has("stackTrace")) {
                return;
            }
            for (JfrFrame frame : event.getStackTrace().frames()) {
                if (frame.className() == null || frame.bytecodeIndex() < 0) {
                    continue;
                }
                lines.put(frame.className() + "." + frame.methodName() + frame.methodDescriptor()
                        + " @" + frame.bytecodeIndex(), frame.lineNumber());
            }
        });
        return lines;
    }
}
