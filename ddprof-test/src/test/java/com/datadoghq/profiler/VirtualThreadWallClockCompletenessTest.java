// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler;

import com.datadoghq.profiler.wallclock.VirtualThreadWallClockTest;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

/** Deterministic checks of the blocking recording oracle, without starting the profiler. */
public class VirtualThreadWallClockCompletenessTest {
    private static final String WORKLOAD_CLASS = "com.datadoghq.profiler.wallclock.VirtualThreadWallClockTest";
    private static final String BLOCKING_LAMBDA = "lambda$samplesCarrierFramesFromBlockingVT$1";

    @Test
    void rejectsBadSampleAfterGoodCarrier() {
        assertThrows(AssertionError.class, () -> VirtualThreadWallClockTest.assertBlockingSamplesComplete(
                Arrays.asList(sample(WORKLOAD_CLASS, BLOCKING_LAMBDA, true, false),
                        sample(WORKLOAD_CLASS, BLOCKING_LAMBDA, false, false))));
    }

    @Test
    void rejectsBadSampleBeforeGoodCarrier() {
        assertThrows(AssertionError.class, () -> VirtualThreadWallClockTest.assertBlockingSamplesComplete(
                Arrays.asList(sample(WORKLOAD_CLASS, BLOCKING_LAMBDA, false, false),
                        sample(WORKLOAD_CLASS, BLOCKING_LAMBDA, true, false))));
    }

    @Test
    void acceptsCarrierAndTruthfullyTruncatedSample() {
        assertDoesNotThrow(() -> VirtualThreadWallClockTest.assertBlockingSamplesComplete(
                Arrays.asList(sample(WORKLOAD_CLASS, BLOCKING_LAMBDA, true, false),
                        sample(WORKLOAD_CLASS, BLOCKING_LAMBDA, false, true))));
    }

    @Test
    void rejectsCpuOnlyRecordingWithCarrier() {
        assertThrows(AssertionError.class, () -> VirtualThreadWallClockTest.assertBlockingSamplesComplete(
                Arrays.asList(sample(WORKLOAD_CLASS, "lambda$samplesCarrierFramesFromCpuBoundVT$0", true, false))));
    }

    @Test
    void retainsPositiveCarrierRequirement() {
        assertThrows(AssertionError.class, () -> VirtualThreadWallClockTest.assertBlockingSamplesComplete(
                Arrays.asList(sample(WORKLOAD_CLASS, BLOCKING_LAMBDA, false, true))));
    }

    @Test
    void excludesWrongClassAndNearPrefixFromWorkload() {
        assertDoesNotThrow(() -> VirtualThreadWallClockTest.assertBlockingSamplesComplete(
                Arrays.asList(sample(WORKLOAD_CLASS, BLOCKING_LAMBDA, true, false),
                        sample(WORKLOAD_CLASS + "Other", BLOCKING_LAMBDA, false, false),
                        sample(WORKLOAD_CLASS, "lambda$samplesCarrierFramesFromBlockingVTOther$1", false, false))));
    }

    @Test
    void rejectsMissingStackFieldAlongsideGoodSample() {
        JfrEvent missingStack = new JfrEvent("datadog.MethodSample", new HashMap<>());
        assertFalse(missingStack.has("stackTrace"));
        assertThrows(AssertionError.class, () -> VirtualThreadWallClockTest.assertBlockingSamplesComplete(
                Arrays.asList(sample(WORKLOAD_CLASS, BLOCKING_LAMBDA, true, false), missingStack)));
    }

    private static JfrEvent sample(String className, String methodName, boolean carrier, boolean truncated) {
        Object[] frames = carrier
                ? new Object[] {frame(className, methodName), frame("java.util.concurrent.ForkJoinWorkerThread", "run")}
                : new Object[] {frame(className, methodName)};
        Map<String, Object> stack = new HashMap<>();
        stack.put("frames", frames);
        stack.put("truncated", truncated);
        JfrEvent event = new JfrEvent("datadog.MethodSample", map("stackTrace", stack));
        assertNotNull(event.get("stackTrace"));
        assertEquals(Boolean.valueOf(truncated), stack.get("truncated"));
        JfrStackTrace trace = event.getStackTrace();
        assertEquals(frames.length, trace.frames().size());
        assertEquals(className, trace.frames().get(0).className());
        assertEquals(methodName, trace.frames().get(0).methodName());
        assertEquals(truncated, trace.isTruncated());
        if (carrier) {
            assertEquals("java.util.concurrent.ForkJoinWorkerThread", trace.frames().get(1).className());
            assertEquals("run", trace.frames().get(1).methodName());
        }
        return event;
    }

    private static Map<String, Object> frame(String className, String methodName) {
        Map<String, Object> method = map("type", map("name", className));
        method.put("name", methodName);
        return map("method", method);
    }

    private static Map<String, Object> map(String key, Object value) {
        Map<String, Object> map = new HashMap<>();
        map.put(key, value);
        return map;
    }
}
