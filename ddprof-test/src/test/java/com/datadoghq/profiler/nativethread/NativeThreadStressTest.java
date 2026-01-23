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
package com.datadoghq.profiler.nativethread;

import com.datadoghq.profiler.AbstractProfilerTest;

import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Stress test for thread entry point detection under high concurrency.
 *
 * This test validates that thread entry detection works correctly when:
 * 1. Many threads are created and destroyed rapidly
 * 2. Thread lifecycles overlap significantly
 * 3. Profiling samples are captured during thread startup and teardown
 *
 * The stress test exercises race conditions that might not appear in
 * simpler tests with fewer threads.
 */
public class NativeThreadStressTest extends AbstractProfilerTest {

    private static final int THREADS_PER_WAVE = 16;
    private static final int NUM_WAVES = 5;
    private static final int WAVE_DELAY_MS = 50;

    @Override
    protected String getProfilerCommand() {
        // Fast sampling to catch thread lifecycle events
        return "cpu=1ms";
    }

    @RetryingTest(3)
    public void testHighConcurrencyThreads() throws Exception {
        System.out.println(String.format(
            "Starting stress test: %d waves of %d threads each",
            NUM_WAVES, THREADS_PER_WAVE));

        int totalThreadsCreated = 0;

        // Create waves of threads with overlapping lifecycles
        for (int wave = 0; wave < NUM_WAVES; wave++) {
            long[] threads = new long[THREADS_PER_WAVE];

            // Create all threads in this wave
            for (int i = 0; i < THREADS_PER_WAVE; i++) {
                threads[i] = NativeThreadCreator.createNativeThread();
                totalThreadsCreated++;
            }

            // Small delay before next wave to create overlap
            if (wave < NUM_WAVES - 1) {
                Thread.sleep(WAVE_DELAY_MS);
            }

            // Wait for this wave to complete
            for (long threadId : threads) {
                NativeThreadCreator.waitNativeThread(threadId);
            }

            System.out.println(String.format(
                "Wave %d/%d complete (%d threads total)",
                wave + 1, NUM_WAVES, totalThreadsCreated));
        }

        stopProfiler();

        // Verify no error frames across all samples
        IItemCollection events = verifyEvents("datadog.ExecutionSample");
        int samplesChecked = assertNoErrorFrames(events);

        System.out.println(String.format(
            "Stress test complete: created %d threads, verified %d samples",
            totalThreadsCreated, samplesChecked));

        // Verify we captured samples (profiling worked throughout)
        assertTrue(samplesChecked > 0,
            "Expected to capture samples during stress test");
    }

    /**
     * Verifies that no error frames are present in any stacktrace.
     * Returns the number of samples checked.
     */
    private int assertNoErrorFrames(IItemCollection events) {
        int samplesChecked = 0;
        int errorFramesFound = 0;
        StringBuilder errorDetails = new StringBuilder();

        for (IItemIterable samples : events) {
            IMemberAccessor<String, IItem> stackTraceAccessor =
                JdkAttributes.STACK_TRACE_STRING.getAccessor(samples.getType());

            for (IItem sample : samples) {
                String stackTrace = stackTraceAccessor.getMember(sample);
                samplesChecked++;

                // Check for all known error markers
                boolean hasError = false;
                String errorType = null;

                if (stackTrace.contains("break_no_anchor")) {
                    hasError = true;
                    errorType = "break_no_anchor";
                } else if (stackTrace.contains("no_Java_frame")) {
                    hasError = true;
                    errorType = "no_Java_frame";
                } else if (stackTrace.contains("BCI_ERROR")) {
                    hasError = true;
                    errorType = "BCI_ERROR";
                }

                if (hasError) {
                    errorFramesFound++;
                    errorDetails.append(String.format(
                        "\nSample %d: Found %s\n%s\n",
                        samplesChecked, errorType, stackTrace));
                }
            }
        }

        // Report all errors at once with detailed info
        if (errorFramesFound > 0) {
            String message = String.format(
                "Found %d error frames in %d samples checked:%s",
                errorFramesFound, samplesChecked, errorDetails.toString());
            assertFalse(true, message);
        }

        return samplesChecked;
    }
}
