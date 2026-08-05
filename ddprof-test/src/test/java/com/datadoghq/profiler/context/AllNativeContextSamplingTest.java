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

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Regression test for the all-native context write path self-initializing OTEL TLS.
 *
 * <p>The wall-clock sampler reads context through {@code ContextApi::get}, which returns nothing
 * until the thread is context-initialized (and only then is the {@code otel_thread_ctx_v1} discovery
 * pointer published). {@code setTraceContext} must set that flag itself on first write — a thread
 * that only ever calls the all-native API must still be visible to the sampler.
 *
 * <p>If the native write does not initialize TLS, every sample carries spanId 0 and the assertion
 * fails.
 */
public class AllNativeContextSamplingTest extends AbstractProfilerTest {

    private static final long EXPECTED_LOCAL_ROOT_SPAN_ID = 0x00000000CAFEF00DL;
    private static final long EXPECTED_SPAN_ID = 0x00000000BADDCAFEL;

    @Override
    protected String getProfilerCommand() {
        // filter=0 samples every thread, so no extra registration is needed.
        return "wall=1ms,filter=0,loglevel=warn";
    }

    @RetryingTest(5)
    public void nativeOnlyContextIsVisibleToSampler() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9() && !Platform.isZing());

        // Register for wall-clock profiling (addThread()); the sampled thread never touches
        // anything but the all-native context API.
        registerCurrentThreadForWallClockProfiling();

        // Keep the context live for the whole sampling window; only the all-native path is used.
        long deadline = System.nanoTime() + 2_000_000_000L; // ~2s of wall-clock sampling
        while (System.nanoTime() < deadline) {
            profiler.setTraceContext(EXPECTED_LOCAL_ROOT_SPAN_ID, EXPECTED_SPAN_ID, 0L, EXPECTED_SPAN_ID,
                    -1, null, -1, null);
            Thread.sleep(5);
        }
        profiler.clearTraceContext();
        stopProfiler();

        JfrEvents events = verifyEvents("datadog.MethodSample");
        boolean found = false;
        for (JfrEvent sample : events) {
            if (sample.getLong(SPAN_ID, -1) == EXPECTED_SPAN_ID
                    && sample.getLong(LOCAL_ROOT_SPAN_ID, -1) == EXPECTED_LOCAL_ROOT_SPAN_ID) {
                found = true;
                break;
            }
        }
        assertTrue(found, "no wall-clock sample carried the natively-written context — "
                + "the all-native write path did not initialize OTEL TLS");
    }
}
