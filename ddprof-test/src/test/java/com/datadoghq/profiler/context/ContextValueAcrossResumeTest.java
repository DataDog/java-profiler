/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.context;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ContextSetter;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junitpioneer.jupiter.RetryingTest;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * A context value set before stop() and never rewritten must still resolve in the recording a
 * resume starts. The thread keeps sampling the encoding it cached when the value was set (the
 * ProfiledThread tag-encoding sidecar), so stop() must not free the context-value dictionary
 * that encoding points into.
 */
public class ContextValueAcrossResumeTest extends AbstractProfilerTest {

    private static final String COMMAND = "wall=1ms,filter=0,attributes=tag1;tag2;tag3";

    @BeforeEach
    void assumeNotJ9() {
        Assumptions.assumeTrue(!Platform.isJ9());
    }

    @Override
    protected String getProfilerCommand() {
        return COMMAND;
    }

    @RetryingTest(5)
    public void contextValueSetBeforeStopResolvesAfterResume() throws Exception {
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2", "tag3"));
        String value = "resume_" + Long.toHexString(System.nanoTime());
        assertTrue(profiler.setContextValue(contextSetter.offsetOf("tag1"), value));
        Thread.sleep(100);
        stopProfiler();

        Path resumed = Files.createTempFile("ContextValueAcrossResumeTest_", ".jfr");
        try {
            profiler.execute("resume," + COMMAND + ",jfr,file=" + resumed.toAbsolutePath());
            try {
                registerCurrentThreadForWallClockProfiling();
                // The context is deliberately not touched again.
                Thread.sleep(300);
            } finally {
                profiler.stop();
            }

            Set<String> tagValues = new HashSet<>();
            boolean found = false;
            JfrEvents samples = verifyEvents(resumed, "datadog.MethodSample", true);
            for (JfrEvent sample : samples) {
                String tag = sample.getString(TAG_1);
                if (tag != null) {
                    tagValues.add(tag);
                    found |= value.equals(tag);
                }
            }
            assertTrue(found, "no sample in the resumed recording carried tag1=" + value
                    + ". Found: " + tagValues);
        } finally {
            profiler.clearContextValue(contextSetter.offsetOf("tag1"));
            Files.deleteIfExists(resumed);
        }
    }
}
