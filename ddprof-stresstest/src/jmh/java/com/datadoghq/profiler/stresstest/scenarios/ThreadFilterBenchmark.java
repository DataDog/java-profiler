package com.datadoghq.profiler.stresstest.scenarios;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.stresstest.Configuration;
import org.openjdk.jmh.annotations.*;
import org.openjdk.jmh.infra.Blackhole;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;

@State(Scope.Benchmark)
public class ThreadFilterBenchmark extends Configuration {

    private static final int NUM_THREADS = 15;
    private ExecutorService executorService;
    private JavaProfiler profiler;
    private AtomicBoolean running;
    private volatile CountDownLatch startLatch;
    private volatile CountDownLatch stopLatch;
    private AtomicLong operationCount;
    private long startTime;
    private PrintWriter logWriter;

    @Setup(Level.Trial)
    public void setup() throws IOException {
        System.out.println("Setting up benchmark...");
        executorService = Executors.newFixedThreadPool(NUM_THREADS);
        profiler = JavaProfiler.getInstance();
        // Enable thread filter and wall clock profiling to see the threads in profiles
        profiler.execute("start,wall=1ms,filter=0");
        running = new AtomicBoolean(true);
        operationCount = new AtomicLong(0);
        startTime = System.currentTimeMillis();
        
        // Setup logging to file
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
        running.set(false);
        executorService.shutdown();
        try {
            executorService.awaitTermination(5, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        profiler.stop();
        long endTime = System.currentTimeMillis();
        long totalOps = operationCount.get();
        double durationSecs = (endTime - startTime) / 1000.0;
        double opsPerSec = totalOps / durationSecs;
        
        // Log final stats to both console and file
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
    @Fork(1)
    @Warmup(iterations = 1, time = 1)
    @Measurement(iterations = 2, time = 2)
    @Threads(1)
    public long threadFilterStress() throws InterruptedException {
        System.out.println("Starting benchmark iteration...");
        startLatch = new CountDownLatch(NUM_THREADS);
        stopLatch = new CountDownLatch(NUM_THREADS);

        // Start all worker threads
        for (int i = 0; i < NUM_THREADS; i++) {
            final int threadId = i;
            executorService.submit(() -> {
                startLatch.countDown();
                try {
                    startLatch.await(); // Wait for all threads to be ready
                    String startMsg = String.format("Thread %d started%n", threadId);
                    System.out.print(startMsg);
                    if (logWriter != null) {
                        logWriter.print(startMsg);
                        logWriter.flush();
                    }
                    
                    while (running.get()) {
                        // Add and remove thread repeatedly as fast as possible
                        profiler.addThread();
                        operationCount.incrementAndGet();
                        profiler.removeThread();
                        operationCount.incrementAndGet();
                        
                        // Log progress every 1000 operations
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

        // Wait for all threads to finish
        stopLatch.await();
        return operationCount.get();
    }
} 