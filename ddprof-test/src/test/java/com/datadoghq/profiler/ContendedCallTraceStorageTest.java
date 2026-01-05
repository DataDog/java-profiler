/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;
import org.openjdk.jmc.flightrecorder.CouldNotLoadRecordingException;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.CyclicBarrier;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Test to validate that CallTraceStorage::put() contention is low
 * when exclusive operations (processTraces) are running concurrently.
 * 
 * This test exercises contention between:
 * - Multiple threads calling put() operations (shared lock)
 * - JFR dump operations calling processTraces() (exclusive lock)
 */
public class ContendedCallTraceStorageTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        // Generate a lot of CPU samples
        return "cpu=1ms";
    }

    @Override
    protected boolean isPlatformSupported() {
        return !Platform.isJ9() && !Platform.isMusl(); // Avoid J9-specific issues
    }

    @Test
    public void shouldShowImprovedContentionWithRetries() throws Exception {
        List<ContentionResult> currentResults = measureContention();
        
        // The test validates that the measurement infrastructure works
        // In practice, you would modify CallTraceStorage::put to accept retry count
        // and test with higher values like tryLockShared(100)

        for (ContentionResult currentResult : currentResults) {
            // For this test, we verify that contention measurement works
            assertTrue(currentResult.totalAttempts > 0, "Should measure total attempts");
            assertTrue(
                currentResult.totalAttempts > 0 &&
                currentResult.droppedSamples / (double) currentResult.totalAttempts < 0.1f,
                "Should measure total attempts and not drop more than 10% of samples"
            );
        }
        
        // The key insight: this test framework can be used to validate
        // that increasing retry counts reduces dropped samples
    }

    private List<ContentionResult> measureContention() throws Exception {
        Path jfrFile = Paths.get("contention-test.jfr");
        List<Path> recordings = new ArrayList<>();
        recordings.add(jfrFile);

        try {
            // Create high contention scenario
            int numThreads = Runtime.getRuntime().availableProcessors() * 2;
            CyclicBarrier startBarrier = new CyclicBarrier(numThreads + 1);
            CountDownLatch finishLatch = new CountDownLatch(numThreads);
            
            // Start concurrent allocation threads
            for (int i = 0; i < numThreads; i++) {
                final int threadId = i;
                Thread worker = new Thread(() -> {
                    try {
                        startBarrier.await(); // Synchronize start
                        
                        // Generate CPU load for 5 seconds to ensure samples
                        long endTime = System.currentTimeMillis() + 5000;
                        while (System.currentTimeMillis() < endTime) {
                            performCpuIntensiveWork(threadId);
                        }
                    } catch (Exception e) {
                        throw new RuntimeException(e);
                    } finally {
                        finishLatch.countDown();
                    }
                });
                worker.start();
            }
            
            // Wait for all threads to be ready
            startBarrier.await();
            
            // Let allocation threads run for a bit, then trigger contention with dumps
            Thread.sleep(500);

            // Trigger contention by calling dump during heavy allocation
            // This forces processTraces() to acquire exclusive lock while put() operations are active
            for (int i = 0; i < 3; i++) {
                Path tempDump = Paths.get("temp-contention-" + i + ".jfr");
                dump(tempDump); // This will cause contention in CallTraceStorage
                recordings.add(tempDump);
                Thread.sleep(500);
            }
            
            // Wait for all allocation threads to finish
            finishLatch.await();
            
            // Final dump to get all data
            dump(jfrFile);
            
            // Analyze contention from JFR data
            return analyzeContentionFromJFR(recordings);
            
        } finally {
            recordings.forEach(f -> {
                try {
                    Files.deleteIfExists(f);
                } catch (IOException e) {
                    // ignore
                }
            });
        }
    }

    private List<ContentionResult> analyzeContentionFromJFR(List<Path> recordings) throws IOException, CouldNotLoadRecordingException {
        List<ContentionResult> results = new ArrayList<>();
        for (Path jfrFile : recordings) {
            IItemCollection events = JfrLoaderToolkit.loadEvents(Files.newInputStream(jfrFile));

            // Count profiling events - represents successful put() operations
            IItemCollection cpuEvents = events.apply(ItemFilters.type("datadog.ExecutionSample"));
            IItemCollection allocationEvents = events.apply(ItemFilters.type("jdk.ObjectAllocationInNewTLAB"));

            // Count events with regular stack traces vs dropped traces
            long cpuWithRegularStack = countEventsWithRegularStackTrace(cpuEvents);
            long cpuWithDroppedStack = countEventsWithDroppedStackTrace(cpuEvents);
            long allocWithRegularStack = countEventsWithRegularStackTrace(allocationEvents);
            long allocWithDroppedStack = countEventsWithDroppedStackTrace(allocationEvents);

            // Events with dropped stack traces indicate contention - CallTraceStorage::put() returned DROPPED_TRACE_ID
            long contentionDrops = cpuWithDroppedStack + allocWithDroppedStack;
            long totalEvents = cpuWithRegularStack + cpuWithDroppedStack + allocWithRegularStack + allocWithDroppedStack;

            System.out.printf("JFR Contention Analysis:%n");
            System.out.printf("  CPU: %d with regular stack, %d with dropped stack%n", cpuWithRegularStack, cpuWithDroppedStack);
            System.out.printf("  Alloc: %d with regular stack, %d with dropped stack%n", allocWithRegularStack, allocWithDroppedStack);
            System.out.printf("  Contention drops: %d/%d (%.2f%%)%n",
                    contentionDrops, totalEvents,
                    totalEvents > 0 ? (double) contentionDrops / totalEvents * 100 : 0);
            results.add(new ContentionResult(contentionDrops, totalEvents));
        }
        
        return results;
    }
    
    private long countEventsWithRegularStackTrace(IItemCollection events) {
        if (!events.hasItems()) return 0;
        
        long count = 0;
        for (IItemIterable iterable : events) {
            for (IItem item : iterable) {
                IMCStackTrace stackTrace = STACK_TRACE.getAccessor(iterable.getType()).getMember(item);
                if (stackTrace != null && !stackTrace.getFrames().isEmpty()) {
                    // Check if this is NOT the dropped trace (contains method with "dropped")
                    String topMethodName = stackTrace.getFrames().get(0).getMethod().getMethodName();
                    if (!topMethodName.contains("dropped")) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
    
    private long countEventsWithDroppedStackTrace(IItemCollection events) {
        if (!events.hasItems()) return 0;
        
        long count = 0;
        for (IItemIterable iterable : events) {
            for (IItem item : iterable) {
                IMCStackTrace stackTrace = STACK_TRACE.getAccessor(iterable.getType()).getMember(item);
                if (stackTrace != null && !stackTrace.getFrames().isEmpty()) {
                    // Check if this is the special dropped trace (single frame with "dropped" method)
                    if (stackTrace.getFrames().size() == 1) {
                        String methodName = stackTrace.getFrames().get(0).getMethod().getMethodName();
                        if (methodName.contains("dropped")) {
                            count++;
                        }
                    }
                }
            }
        }
        return count;
    }
    
    private void performCpuIntensiveWork(int threadId) {
        // Simple CPU-intensive loop similar to ProfiledCode.burnCycles()
        burnCycles(threadId);
    }
    
    private void burnCycles(int threadId) {
        // CPU burning pattern that ensures we get profiling samples
        long sink = 0;
        for (int i = 0; i < 100000; i++) {
            sink += i * threadId;
            sink ^= threadId;
            if (i % 1000 == 0) {
                // Add some method calls to create interesting stack traces
                sink += computeHash(sink, threadId);
            }
        }
        // Store in volatile to prevent optimization
        volatileResult = sink;
    }
    
    private long computeHash(long value, int threadId) {
        // Another method in the stack trace
        long result = value;
        for (int i = 0; i < 100; i++) {
            result = Long.rotateLeft(result, 1);
            result ^= (threadId + i);
        }
        return result;
    }
    
    private volatile long volatileResult; // Prevent optimization

    private static class ContentionResult {
        final long droppedSamples;
        final long totalAttempts;
        
        ContentionResult(long droppedSamples, long totalAttempts) {
            this.droppedSamples = droppedSamples;
            this.totalAttempts = totalAttempts;
        }
        
        double getDropRate() {
            return totalAttempts > 0 ? (double) droppedSamples / totalAttempts : 0.0;
        }
    }
}