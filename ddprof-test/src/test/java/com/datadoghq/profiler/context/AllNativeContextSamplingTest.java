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
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Regression test for the all-native context write path self-initializing OTEL TLS.
 *
 * <p>The wall-clock sampler reads context through {@code ContextApi::get}, which returns nothing
 * until the thread is context-initialized (and only then is the {@code otel_thread_ctx_v1} discovery
 * pointer published). Before the fix, that flag was set only by the deprecated DirectByteBuffer path
 * ({@code getThreadContext()} / {@code initializeContextTLS0}); a thread that used only the
 * all-native API ({@code setTraceContext}) wrote a record the sampler silently ignored.
 *
 * <p>This test deliberately <em>never</em> calls {@code getThreadContext()} on the sampled thread.
 * If the native write does not initialize TLS, every sample carries spanId 0 and the assertion fails.
 */
public class AllNativeContextSamplingTest extends AbstractProfilerTest {

    private static final long EXPECTED_LOCAL_ROOT_SPAN_ID = 0x00000000CAFEF00DL;
    private static final long EXPECTED_SPAN_ID = 0x00000000BADDCAFEL;

    @Override
    protected String getProfilerCommand() {
        // filter=0 samples every thread, so no getThreadContext()/registration is needed.
        return "wall=1ms,filter=0,loglevel=warn";
    }

    @RetryingTest(5)
    public void nativeOnlyContextIsVisibleToSampler() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9() && !Platform.isZing());

        // Register for wall-clock profiling (addThread(); does NOT touch getThreadContext, so the
        // all-native-only nature of the test is preserved).
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

        IItemCollection events = verifyEvents("datadog.MethodSample");
        boolean found = false;
        for (IItemIterable samples : events) {
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(samples.getType());
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(samples.getType());
            if (spanIdAccessor == null || rootSpanIdAccessor == null) {
                continue;
            }
            for (IItem sample : samples) {
                if (spanIdAccessor.getMember(sample).longValue() == EXPECTED_SPAN_ID
                        && rootSpanIdAccessor.getMember(sample).longValue() == EXPECTED_LOCAL_ROOT_SPAN_ID) {
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        assertTrue(found, "no wall-clock sample carried the natively-written context — "
                + "the all-native write path did not initialize OTEL TLS");
    }
}
