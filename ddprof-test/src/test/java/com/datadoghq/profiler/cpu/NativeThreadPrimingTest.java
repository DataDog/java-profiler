/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.junit.CStack;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.regex.Pattern;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Regression coverage for JVM threads that existed before the profiler initialized. Thread
 * priming must create a {@code ProfiledThread} for those compiler and GC threads before this test
 * can be enabled again.
 */
@Disabled("Re-enable when thread priming is reintroduced")
public class NativeThreadPrimingTest extends CStackAwareAbstractProfilerTest {
    private static final String UNKNOWN_NATIVE_THREAD_FRAME =
            "UNKNOWN_PACKAGE.Unknown Native Thread";
    private static final Pattern NO_JAVA_FRAME_ONLY =
            Pattern.compile("^\\s*\\.?no_Java_frame\\(\\)(?:\\s+line:\\s+0)?\\s*$");
    private static final int MAX_SYNTHETIC_NATIVE_THREAD_SAMPLES = 10;

    public NativeThreadPrimingTest(@CStack String cstack) {
        super(cstack);
    }

    @TestTemplate
    @ValueSource(strings = {"vm"})
    public void testPreExistingNativeThreadsHaveUsableFrames() throws Exception {
        try (ProfiledCode profiledCode = new ProfiledCode(profiler)) {
            for (int i = 0, id = 1; i < 100; i++, id += 3) {
                profiledCode.method1(id);
            }
            stopProfiler();

            AtomicInteger syntheticSamples = new AtomicInteger();
            long totalSamples = streamEvents("datadog.ExecutionSample", item -> {
                String stackTrace = item.getStackTraceString();
                if (stackTrace.contains(UNKNOWN_NATIVE_THREAD_FRAME)
                        || NO_JAVA_FRAME_ONLY.matcher(stackTrace).matches()) {
                    syntheticSamples.incrementAndGet();
                }
            });

            assertTrue(syntheticSamples.get() <= MAX_SYNTHETIC_NATIVE_THREAD_SAMPLES,
                    "Expected at most " + MAX_SYNTHETIC_NATIVE_THREAD_SAMPLES
                            + " samples with a synthetic native-thread frame, got "
                            + syntheticSamples.get() + " of " + totalSamples);
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }
}
