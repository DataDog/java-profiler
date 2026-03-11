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
 * Test for thread entry point detection on native threads.
 *
 * Validates that when profiling native threads the profiler produces usable
 * samples and that non-Java thread samples are not misclassified as
 * break_no_anchor (which implies a missing JavaFrameAnchor, inapplicable
 * for pure pthreads).  break_no_symbol is acceptable — it indicates the
 * DWARF unwind could not resolve the next frame, which is expected when
 * the test library or libc lacks complete CFI.
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
     * Verifies that native thread samples do not contain break_no_anchor.
     * break_no_anchor implies a missing JavaFrameAnchor which is inapplicable
     * for pure pthreads.  break_no_symbol is acceptable — it means the DWARF
     * unwind hit an unresolvable PC, expected when CFI is incomplete.
     */
    private void assertNoErrorFrames(IItemCollection events) {
        int samplesChecked = 0;

        for (IItemIterable samples : events) {
            IMemberAccessor<String, IItem> stackTraceAccessor =
                JdkAttributes.STACK_TRACE_STRING.getAccessor(samples.getType());

            for (IItem sample : samples) {
                String stackTrace = stackTraceAccessor.getMember(sample);
                samplesChecked++;

                if (stackTrace.contains("do_primes()")) {
                    // Native thread sample: must not be misclassified as break_no_anchor
                    assertFalse(stackTrace.contains("break_no_anchor"),
                        String.format("Found break_no_anchor in native thread sample %d:\n%s",
                            samplesChecked, stackTrace));
                }
            }
        }

        System.out.println("Verified " + samplesChecked + " samples");
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
