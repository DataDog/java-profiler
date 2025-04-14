package com.datadoghq.profiler.stresstest.scenarios;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.stresstest.Configuration;
import org.openjdk.jmh.annotations.*;
import org.openjdk.jmh.infra.Blackhole;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicIntegerArray;

@State(Scope.Benchmark)
public class ThreadFilterBenchmark extends Configuration {

    private static final int NUM_THREADS = 15;
    private ExecutorService executorService;
    private JavaProfiler profiler;
    private AtomicBoolean running;
    private CountDownLatch startLatch;
    private CountDownLatch stopLatch;
    private AtomicLong operationCount;
    private long startTime;
    private PrintWriter logWriter;
    private static final int ARRAY_SIZE = 1024; // Larger array to stress memory
    private static final int[] sharedArray = new int[ARRAY_SIZE];
    private static final AtomicIntegerArray atomicArray = new AtomicIntegerArray(ARRAY_SIZE);
    private static final int CACHE_LINE_SIZE = 64; // Typical cache line size
    private static final int STRIDE = CACHE_LINE_SIZE / Integer.BYTES; // Elements per cache line

    @Setup(Level.Trial)
    public void setup() throws IOException {
        System.out.println("Setting up benchmark...");
        System.out.println("Creating thread pool with " + NUM_THREADS + " threads");
        executorService = Executors.newFixedThreadPool(NUM_THREADS);
        System.out.println("Getting profiler instance");
        profiler = JavaProfiler.getInstance();
        
        // Try to stop any existing profiler session
        try {
            System.out.println("Stopping any existing profiler session...");
            profiler.execute("stop");
            // Give a small delay to ensure stop completes
            Thread.sleep(100);
        } catch (Exception e) {
            // Ignore exceptions if profiler wasn't started
            System.out.println("No existing profiler session to stop");
        }
        
        System.out.println("Starting profiler with wall=1ms,filter=0,file=/tmp/thread_filter_profile.jfr");
        profiler.execute("start,wall=1ms,filter=0,file=/tmp/thread_filter_profile.jfr");
        System.out.println("Started profiler with output file");
        running = new AtomicBoolean(true);
        operationCount = new AtomicLong(0);
        startTime = System.currentTimeMillis();
        System.out.println("Benchmark setup completed at " + startTime);
        
        try {
            String logFile = "/tmp/thread_filter_benchmark.log";
            System.out.println("Attempting to create log file at: " + logFile);
            logWriter = new PrintWriter(new FileWriter(logFile));
            logWriter.printf("Benchmark started at %d%n", startTime);
            logWriter.flush();
            System.out.println("Successfully created and wrote to log file");
        } catch (IOException e) {
            System.err.println("Failed to create log file: " + e.getMessage());
            e.printStackTrace();
            throw e;
        }
    }

    @TearDown(Level.Trial)
    public void tearDown() {
        System.out.println("Tearing down benchmark...");
        
        // First stop all threads
        running.set(false);
        
        // Wait for all threads to finish with a timeout
        try {
            if (stopLatch != null) {
                if (!stopLatch.await(30, TimeUnit.SECONDS)) {
                    System.err.println("Warning: Some threads did not finish within timeout");
                }
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        // Shutdown executor with timeout
        if (executorService != null) {
            executorService.shutdown();
            try {
                if (!executorService.awaitTermination(30, TimeUnit.SECONDS)) {
                    executorService.shutdownNow();
                    if (!executorService.awaitTermination(30, TimeUnit.SECONDS)) {
                        System.err.println("Warning: Executor did not terminate");
                    }
                }
            } catch (InterruptedException e) {
                executorService.shutdownNow();
                Thread.currentThread().interrupt();
            }
        }

        // Stop profiler with timeout
        if (profiler != null) {
            try {
                System.out.println("Stopping profiler...");
                profiler.execute("stop");
                // Give a small delay to ensure stop completes
                Thread.sleep(100);
            } catch (Exception e) {
                System.err.println("Warning: Error stopping profiler: " + e.getMessage());
                e.printStackTrace();
            }
        }

        // Calculate and log statistics
        long endTime = System.currentTimeMillis();
        long totalOps = operationCount != null ? operationCount.get() : 0;
        double durationSecs = (endTime - startTime) / 1000.0;
        double opsPerSec = totalOps / durationSecs;
        
        String stats = String.format("Thread Filter Stats:%n" +
                "Total operations: %,d%n" +
                "Duration: %.2f seconds%n" +
                "Operations/second: %,.0f%n" +
                "Operations/second/thread: %,.0f%n",
                totalOps, durationSecs, opsPerSec, opsPerSec / NUM_THREADS);
        
        System.out.print(stats);
        if (logWriter != null) {
            try {
                logWriter.print(stats);
                logWriter.flush();
                logWriter.close();
                System.out.println("Successfully closed log file");
            } catch (Exception e) {
                System.err.println("Error closing log file: " + e.getMessage());
                e.printStackTrace();
            }
        }
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 1, warmups = 0)
    @Warmup(iterations = 1, time = 1)
    @Measurement(iterations = 1, time = 2)
    @Threads(Threads.MAX)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public long threadFilterStress() throws InterruptedException {
        System.out.println("Starting benchmark iteration...");
        startLatch = new CountDownLatch(NUM_THREADS);
        stopLatch = new CountDownLatch(NUM_THREADS);

        // Start all worker threads
        for (int i = 0; i < NUM_THREADS; i++) {
            final int threadId = i;
            executorService.submit(() -> {
                try {
                    startLatch.countDown();
                    startLatch.await(30, TimeUnit.SECONDS);
                    
                    String startMsg = String.format("Thread %d started%n", threadId);
                    System.out.print(startMsg);
                    if (logWriter != null) {
                        logWriter.print(startMsg);
                        logWriter.flush();
                    }
                    
                    while (running.get()) {
                        // Memory-intensive operations that would be sensitive to false sharing
                        for (int j = 0; j < ARRAY_SIZE; j += STRIDE) {
                            // Register thread at the start of each cache line operation
                            profiler.addThread();
                            
                            // Each thread writes to its own cache line
                            int baseIndex = (threadId * STRIDE) % ARRAY_SIZE;
                            for (int k = 0; k < STRIDE; k++) {
                                int index = (baseIndex + k) % ARRAY_SIZE;
                                // Write to shared array
                                sharedArray[index] = threadId;
                                // Read and modify
                                int value = sharedArray[index] + 1;
                                // Atomic operation
                                atomicArray.set(index, value);
                            }
                            
                            // Remove thread after cache line operation
                            profiler.removeThread();
                            operationCount.incrementAndGet();
                        }
                        
                        // More memory operations with thread registration
                        for (int j = 0; j < ARRAY_SIZE; j += STRIDE) {
                            // Register thread at the start of each cache line operation
                            profiler.addThread();
                            
                            int baseIndex = (threadId * STRIDE) % ARRAY_SIZE;
                            for (int k = 0; k < STRIDE; k++) {
                                int index = (baseIndex + k) % ARRAY_SIZE;
                                int value = atomicArray.get(index);
                                sharedArray[index] = value * 2;
                            }
                            
                            // Remove thread after cache line operation
                            profiler.removeThread();
                            operationCount.incrementAndGet();
                        }
                        
                        if (operationCount.get() % 1000 == 0) {
                            String progressMsg = String.format("Thread %d completed %d operations%n", threadId, operationCount.get());
                            System.out.print(progressMsg);
                            if (logWriter != null) {
                                logWriter.print(progressMsg);
                                logWriter.flush();
                            }
                        }
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                } finally {
                    stopLatch.countDown();
                    String finishMsg = String.format("Thread %d finished%n", threadId);
                    System.out.print(finishMsg);
                    if (logWriter != null) {
                        logWriter.print(finishMsg);
                        logWriter.flush();
                    }
                }
            });
        }

        // Wait for all threads to finish with timeout
        if (!stopLatch.await(30, TimeUnit.SECONDS)) {
            System.err.println("Warning: Benchmark did not complete within timeout");
        }
        
        return operationCount.get();
    }
}