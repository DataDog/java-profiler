/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.context.ContextExecutor;
import com.datadoghq.profiler.context.Tracing;
import org.junit.jupiter.api.Assumptions;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;

import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.*;

import static com.datadoghq.profiler.MoreAssertions.assertInRange;
import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class LightweightContextCpuTest extends AbstractProfilerTest {

    private ProfiledCode profiledCode;

    @Override
    protected void before() {
        profiledCode = new ProfiledCode(profiler);
    }

    public void test() throws ExecutionException, InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        for (int i = 0, id = 1; i < 100; i++, id += 3) {
            profiledCode.method1(id);
        }
        stopProfiler();
        Set<Long> sampledSpanIds = profiledCode.allSampledSpanIds();
        JfrEvents events = verifyEvents("datadog.ExecutionSample");

        int numNonZeroContexts = 0;
        for (JfrEvent sample : events) {
            String stackTrace = sample.getStackTraceString();
            assertNull(stackTrace);
            long spanId = sample.getLong(SPAN_ID, 0);
            long rootSpanId = sample.getLong(LOCAL_ROOT_SPAN_ID, 0);
            numNonZeroContexts += (spanId != 0 && rootSpanId != 0 ? 1 : 0);
            if (spanId > 0) {
                assertTrue(sampledSpanIds.contains(spanId));
            }
            String state = sample.getEnumName(THREAD_STATE);
            assertDoesNotThrow(() -> Thread.State.valueOf(state));
            assertEquals(Thread.State.RUNNABLE, Thread.State.valueOf(state));
        }
        assertTrue(numNonZeroContexts > 0, "no context");
        Map<String, Long> debugCounters = profiler.getDebugCounters();
        // these are here to verify these counters produce reasonable values so they can be used for memory leak detection
        assertInRange(debugCounters.get("calltrace_storage_traces"), 10, 10000);
        assertInRange(debugCounters.get("calltrace_storage_bytes"), 1024, 8 * 1024 * 1024);
        // this allocator is only used for calltrace storage and eagerly allocates chunks of 8MiB
        assertEquals(8 * 1024 * 1024, debugCounters.get("linear_allocator_bytes"));
        assertEquals(1, debugCounters.get("linear_allocator_chunks"));
    }

    @Override
    protected void after() throws Exception {
        profiledCode.close();
    }

    @Override
    protected String getProfilerCommand() {
        // cpu=100us signal-based sampling is much more expensive under ASAN (the signal
        // handler itself is ASAN-instrumented), which can inflate the sample count and,
        // via the per-sample accessor calls above, the test heap. Sample coarser under ASAN.
        return isAsan() ? "cpu=1ms,lightweight=yes" : "cpu=100us,lightweight=yes";
    }
}
