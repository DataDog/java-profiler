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
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

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

            IItemCollection events = verifyEvents("datadog.ExecutionSample");
            int syntheticSamples = 0;
            int totalSamples = 0;
            for (IItemIterable cpuSamples : events) {
                IMemberAccessor<String, IItem> frameAccessor =
                        JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
                for (IItem sample : cpuSamples) {
                    totalSamples++;
                    String stackTrace = frameAccessor.getMember(sample);
                    if (stackTrace.contains(UNKNOWN_NATIVE_THREAD_FRAME)
                            || NO_JAVA_FRAME_ONLY.matcher(stackTrace).matches()) {
                        syntheticSamples++;
                    }
                }
            }

            assertTrue(syntheticSamples <= MAX_SYNTHETIC_NATIVE_THREAD_SAMPLES,
                    "Expected at most " + MAX_SYNTHETIC_NATIVE_THREAD_SAMPLES
                            + " samples with a synthetic native-thread frame, got "
                            + syntheticSamples + " of " + totalSamples);
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }
}
