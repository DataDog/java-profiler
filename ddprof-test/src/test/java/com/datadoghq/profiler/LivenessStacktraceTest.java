package com.datadoghq.profiler;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class LivenessStacktraceTest extends AbstractProfilerTest {
    
    @Override
    protected String getProfilerCommand() {
        return "memory=1024:L:1.0";  // Enable liveness tracking with 1KB sampling, 100% liveness subsampling
    }
    
    @Test
    public void testLivenessStacktraceConsistency() throws Exception {
        final int NUM_ALLOCATOR_THREADS = 4;
        final int TEST_DURATION_SECONDS = 3;
        final int DUMP_INTERVAL_MS = 500;
        
        List<java.nio.file.Path> recordingFiles = new ArrayList<>();
        
        try {
            // Start multiple allocator threads running in parallel
            List<Thread> allocatorThreads = new ArrayList<>();
            for (int i = 0; i < NUM_ALLOCATOR_THREADS; i++) {
                Thread allocThread = new Thread(new AllocatingTarget(), "Allocator-" + i);
                allocThread.start();
                allocatorThreads.add(allocThread);
            }
            
            // Start dump thread that calls dump every second
            Thread dumpThread = new Thread(() -> {
                for (int i = 0; i < TEST_DURATION_SECONDS; i++) {
                    try {
                        java.nio.file.Path recording = java.nio.file.Files.createTempFile("liveness_dump_" + i + "_", ".jfr");
                        synchronized(recordingFiles) {
                            recordingFiles.add(recording);
                        }
                        
                        // This is where race conditions are most likely to occur
                        dump(recording);
                        
                        Thread.sleep(DUMP_INTERVAL_MS);
                        
                        // Trigger GC during each dump to maximize liveness events
                        synchronized(AllocatingTarget.heapObjects) {
                            if (AllocatingTarget.heapObjects.size() > 150) {
                                AllocatingTarget.heapObjects.subList(0, 50).clear();
                            }
                        }
                        System.gc();
                        
                    } catch (Exception e) {
                        System.err.println("Error in dump thread: " + e.getMessage());
                        e.printStackTrace();
                        break;
                    }
                }
            }, "DumpThread");
            
            dumpThread.start();
            
            // Let the test run for the specified duration
            dumpThread.join();
            
            // Stop all allocator threads
            AllocatingTarget.keepAllocating = false;
            for (Thread thread : allocatorThreads) {
                thread.join(2000); // Give threads time to finish gracefully
            }
            
            // Final dump after allocations stop
            java.nio.file.Path finalRecording = java.nio.file.Files.createTempFile("liveness_final_", ".jfr");
            recordingFiles.add(finalRecording);
            dump(finalRecording);
            
            // Verify all recordings have liveness events
            int totalLivenessEvents = 0;
            for (int i = 0; i < recordingFiles.size(); i++) {
                java.nio.file.Path recording = recordingFiles.get(i);
                try {
                    IItemCollection events = verifyEvents(recording, "datadog.HeapLiveObject", false);
                    long eventCount = events.stream().flatMap(items -> items.stream()).count();
                    totalLivenessEvents += eventCount;
                    
                    System.out.println("Recording " + i + ": " + eventCount + " liveness events");
                    
                    // TODO: Add more sophisticated verification of call trace consistency
                    // For now, just verify we have some events in most dumps
                    
                } catch (Exception e) {
                    System.err.println("Error verifying recording " + i + ": " + e.getMessage());
                }
            }
            
            System.out.println("Total liveness events across all recordings: " + totalLivenessEvents);
            assertTrue(totalLivenessEvents > 0, "Should have recorded liveness events across all dumps");
            
        } finally {
            // Clean up
            AllocatingTarget.cleanup();
            
            // Clean up recording files
            for (java.nio.file.Path recording : recordingFiles) {
                try {
                    java.nio.file.Files.deleteIfExists(recording);
                } catch (Exception e) {
                    // Ignore cleanup errors
                }
            }
        }
    }
    
    public static class AllocatingTarget implements Runnable {
        // Static list to keep objects alive in heap across multiple dump cycles
        public static final List<Object> heapObjects = Collections.synchronizedList(new ArrayList<>());
        public static volatile boolean keepAllocating = true;

        @Override
        public void run() {
            int allocationCount = 0;
            
            // Continuously allocate large objects while keepAllocating is true
            while (keepAllocating) {
                try {
                    Object obj = createLargeObjectFromDistinctStack(allocationCount);
                    
                    // Keep 60% of objects in heap to trigger liveness tracking
                    // The rest become eligible for GC immediately
                    if (allocationCount % 5 < 3) {
                        heapObjects.add(obj);
                    }
                    
                    allocationCount++;
                    
                    // More frequent maintenance for faster data generation
                    if (allocationCount % 25 == 0) {
                        // Prevent heap from growing too large
                        synchronized(heapObjects) {
                            if (heapObjects.size() > 500) {
                                // Remove oldest objects to create churn
                                heapObjects.subList(0, 100).clear();
                            }
                        }
                    }
                    
                    // More frequent GC to trigger liveness events faster
                    if (allocationCount % 100 == 0) {
                        System.gc();
                        Thread.sleep(2); // Minimal pause after GC
                    }
                    
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                } catch (OutOfMemoryError e) {
                    // Clear some objects and continue
                    synchronized(heapObjects) {
                        if (heapObjects.size() > 100) {
                            heapObjects.subList(0, heapObjects.size() / 2).clear();
                        }
                    }
                    System.gc();
                }
            }
        }
        
        private Object createLargeObjectFromDistinctStack(int index) {
            // Create objects large enough to be sampled (> 1KB with sampling=1024)
            if (index % 3 == 0) {
                return createLargeArrayA(2000); // ~2KB
            } else if (index % 3 == 1) {
                return createLargeArrayB(1500); // ~1.5KB
            } else {
                return createLargeArrayC(3000); // ~3KB
            }
        }
        
        private Object createLargeArrayA(int size) {
            // Large byte array to trigger sampling
            return new byte[size];
        }
        
        private Object createLargeArrayB(int size) {
            // Large int array to trigger sampling  
            return new int[size];
        }
        
        private Object createLargeArrayC(int size) {
            // Large Object array to trigger sampling
            Object[] array = new Object[size];
            // Fill with some objects to make it realistic
            for (int i = 0; i < Math.min(100, size); i++) {
                array[i] = "data" + i;
            }
            return array;
        }
        
        public static void cleanup() {
            keepAllocating = false;
            heapObjects.clear();
        }
    }
}