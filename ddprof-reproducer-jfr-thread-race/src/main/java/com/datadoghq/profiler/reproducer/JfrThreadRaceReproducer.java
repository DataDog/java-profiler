/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.reproducer;

import com.datadoghq.profiler.JavaProfiler;
import org.eclipse.jetty.util.thread.QueuedThreadPool;
import picocli.CommandLine;
import picocli.CommandLine.Command;
import picocli.CommandLine.Option;

import java.nio.file.Paths;
import java.util.concurrent.Callable;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Reproducer application for JFR Thread Race SIGSEGV.
 *
 * This application creates a high thread churn scenario with Jetty QueuedThreadPool
 * and performs immediate allocations on thread start to trigger the race condition
 * where Thread::current() returns nullptr during JFR ObjectAllocationSample recording.
 */
@Command(name = "jfr-thread-race", mixinStandardHelpOptions = true, version = "1.0",
         description = "Reproduces JFR thread race SIGSEGV on Java 25.0.1")
public class JfrThreadRaceReproducer implements Callable<Integer> {

    @Option(names = "--threads", description = "Maximum threads in pool (default: ${DEFAULT-VALUE})")
    private int maxThreads = 200;

    @Option(names = "--min-threads", description = "Minimum threads in pool (default: ${DEFAULT-VALUE})")
    private int minThreads = 5;

    @Option(names = "--churn-ms", description = "Task submission interval in ms (default: ${DEFAULT-VALUE})")
    private long taskSubmissionIntervalMs = 1;

    @Option(names = "--idle-ms", description = "Thread idle timeout in ms (default: ${DEFAULT-VALUE})")
    private long threadIdleTimeoutMs = 50;

    @Option(names = "--allocations", description = "Allocations per task (default: ${DEFAULT-VALUE})")
    private int allocationsPerTask = 10;

    @Option(names = "--alloc-size", description = "Allocation size in bytes (default: ${DEFAULT-VALUE})")
    private int allocationSize = 100_000;

    @Option(names = "--duration-sec", description = "Run duration in seconds (default: ${DEFAULT-VALUE})")
    private long durationSeconds = 60;

    @Option(names = "--profiler-config", description = "Datadog profiler configuration (default: ${DEFAULT-VALUE})")
    private String profilerConfig = "start,event=cpu,alloc,memory=256k:a";

    private QueuedThreadPool threadPool;
    private ThreadLifecycleTracker tracker;
    private JavaProfiler profiler;
    private final AtomicLong tasksSubmitted = new AtomicLong();
    private final AtomicLong tasksCompleted = new AtomicLong();

    public static void main(String[] args) {
        int exitCode = new CommandLine(new JfrThreadRaceReproducer()).execute(args);
        System.exit(exitCode);
    }

    @Override
    public Integer call() throws Exception {
        System.out.println("[REPRODUCER] JFR Thread Race Reproducer Starting");
        System.out.println("[REPRODUCER] Java Version: " + System.getProperty("java.version"));
        System.out.println("[REPRODUCER] OS: " + System.getProperty("os.name") + " " + System.getProperty("os.arch"));
        System.out.println("[REPRODUCER] Configuration:");
        System.out.println("[REPRODUCER]   Thread Pool: " + minThreads + "-" + maxThreads + " threads");
        System.out.println("[REPRODUCER]   Thread Idle Timeout: " + threadIdleTimeoutMs + "ms");
        System.out.println("[REPRODUCER]   Task Submission Rate: " + (1000.0 / taskSubmissionIntervalMs) + "/sec");
        System.out.println("[REPRODUCER]   Allocations per Task: " + allocationsPerTask + " x " + allocationSize + " bytes");
        System.out.println("[REPRODUCER]   Duration: " + durationSeconds + " seconds");
        System.out.println("[REPRODUCER]   Profiler Config: " + profilerConfig);

        try {
            // Initialize tracker
            tracker = new ThreadLifecycleTracker();

            // Initialize Datadog profiler
            System.out.println("[REPRODUCER] Initializing Datadog profiler...");
            profiler = JavaProfiler.getInstance();
            String result = profiler.execute(profilerConfig);
            System.out.println("[REPRODUCER] Profiler started: " + result);

            // Configure Jetty thread pool for aggressive churn
            System.out.println("[REPRODUCER] Initializing thread pool...");
            threadPool = new QueuedThreadPool(maxThreads, minThreads);
            threadPool.setIdleTimeout((int) threadIdleTimeoutMs);
            threadPool.setStopTimeout(0);  // Immediate shutdown - maximize race window
            threadPool.setName("reproducer");
            threadPool.start();
            System.out.println("[REPRODUCER] Thread pool started");

            // Submit continuous workload
            System.out.println("[REPRODUCER] Starting workload submission...");
            ScheduledExecutorService submitter = Executors.newSingleThreadScheduledExecutor();
            submitter.scheduleAtFixedRate(() -> {
                try {
                    threadPool.execute(new AllocationWorker(
                        allocationsPerTask,
                        allocationSize,
                        tracker,
                        tasksCompleted
                    ));
                    tasksSubmitted.incrementAndGet();
                } catch (Exception e) {
                    System.err.println("[REPRODUCER] Error submitting task: " + e.getMessage());
                }
            }, 0, taskSubmissionIntervalMs, TimeUnit.MILLISECONDS);

            // Monitor statistics
            long startTime = System.currentTimeMillis();
            long lastReportTime = startTime;
            long lastTaskCount = 0;

            while ((System.currentTimeMillis() - startTime) < (durationSeconds * 1000)) {
                Thread.sleep(10_000);  // Report every 10 seconds

                long currentTime = System.currentTimeMillis();
                long elapsedSeconds = (currentTime - startTime) / 1000;
                long submitted = tasksSubmitted.get();
                long completed = tasksCompleted.get();

                long intervalTasks = completed - lastTaskCount;
                long intervalSeconds = (currentTime - lastReportTime) / 1000;
                double tasksPerSecond = intervalSeconds > 0 ? (double) intervalTasks / intervalSeconds : 0;

                System.out.printf("[REPRODUCER] Statistics (%ds): submitted=%d, completed=%d, rate=%.1f tasks/sec, threads=%d%n",
                    elapsedSeconds, submitted, completed, tasksPerSecond, threadPool.getThreads());

                lastReportTime = currentTime;
                lastTaskCount = completed;
            }

            // Shutdown
            System.out.println("[REPRODUCER] Shutting down...");
            submitter.shutdown();
            submitter.awaitTermination(5, TimeUnit.SECONDS);

            threadPool.stop();
            threadPool.join();

            profiler.stop();

            // Export statistics
            System.out.println("[REPRODUCER] Exporting thread statistics...");
            tracker.exportStatistics(Paths.get("build/thread-stats.csv"));

            // Summary
            System.out.println("[REPRODUCER] Final Statistics:");
            System.out.println("[REPRODUCER]   Total Tasks Submitted: " + tasksSubmitted.get());
            System.out.println("[REPRODUCER]   Total Tasks Completed: " + tasksCompleted.get());
            System.out.println("[REPRODUCER]   Total Threads Created: " + tracker.getThreadCount());
            System.out.println("[REPRODUCER]   Thread Stats: build/thread-stats.csv");
            System.out.println("[REPRODUCER] Reproducer completed successfully");

            return 0;

        } catch (Exception e) {
            System.err.println("[REPRODUCER] Error: " + e.getMessage());
            e.printStackTrace();
            return 1;
        }
    }
}
