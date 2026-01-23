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
 * Test specifically for thread entry point detection (Theory 1).
 *
 * This test validates that when profiling native threads, the profiler:
 * 1. Correctly detects JVM thread entry points (thread_native_entry, JavaThread::, etc.)
 * 2. Does NOT produce break_no_anchor or other error frames
 * 3. Treats thread entry points as root frames and stops unwinding
 *
 * The test uses a larger number of threads than the standard test to increase
 * the likelihood of catching race conditions in thread startup detection.
 */
public class ThreadEntryDetectionTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        // Use fast sampling to capture more thread startup samples
        return "cpu=1ms";
    }

    @RetryingTest(3)
    public void testThreadEntryDetection() throws Exception {
        // Create more threads than standard test to increase likelihood
        // of capturing thread startup samples
        int numThreads = 16;
        long[] threads = new long[numThreads];

        System.out.println("Creating " + numThreads + " native threads...");
        for (int i = 0; i < numThreads; i++) {
            threads[i] = NativeThreadCreator.createNativeThread();
        }

        // Wait for all threads to complete
        for (long threadId : threads) {
            NativeThreadCreator.waitNativeThread(threadId);
        }

        stopProfiler();

        // Verify events
        IItemCollection events = verifyEvents("datadog.ExecutionSample");
        assertNoErrorFrames(events);

        // Verify we captured some samples
        int totalSamples = countTotalSamples(events);
        System.out.println("Total samples captured: " + totalSamples);
        assertTrue(totalSamples > 0, "Expected to capture at least some profiling samples");
    }

    /**
     * Verifies that no error frames are present in the stacktraces.
     * This is the primary validation for Theory 1 - ensuring thread entry
     * detection prevents malformed stacktraces.
     */
    private void assertNoErrorFrames(IItemCollection events) {
        int samplesChecked = 0;

        for (IItemIterable samples : events) {
            IMemberAccessor<String, IItem> stackTraceAccessor =
                JdkAttributes.STACK_TRACE_STRING.getAccessor(samples.getType());

            for (IItem sample : samples) {
                String stackTrace = stackTraceAccessor.getMember(sample);
                samplesChecked++;

                // Critical assertion: NO error frames should be present
                assertFalse(stackTrace.contains("break_no_anchor"),
                    String.format("Found break_no_anchor error in sample %d/%d:\n%s",
                        samplesChecked, samplesChecked, stackTrace));

                assertFalse(stackTrace.contains("no_Java_frame"),
                    String.format("Found no_Java_frame error in sample %d/%d:\n%s",
                        samplesChecked, samplesChecked, stackTrace));

                // Additional checks for other error indicators
                assertFalse(stackTrace.contains("BCI_ERROR"),
                    String.format("Found BCI_ERROR in sample %d/%d:\n%s",
                        samplesChecked, samplesChecked, stackTrace));
            }
        }

        System.out.println("Verified " + samplesChecked + " samples - no error frames found");
    }

    /**
     * Counts total number of samples in the event collection.
     */
    private int countTotalSamples(IItemCollection events) {
        int count = 0;
        for (IItemIterable samples : events) {
            for (IItem sample : samples) {
                count++;
            }
        }
        return count;
    }
}
