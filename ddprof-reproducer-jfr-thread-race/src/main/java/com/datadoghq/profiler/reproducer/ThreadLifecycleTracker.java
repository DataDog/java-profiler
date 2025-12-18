/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.reproducer;

import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Comparator;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Tracks thread lifecycle timing to identify race windows.
 *
 * This tracker captures precise nanosecond-level timing for:
 * - Thread creation
 * - First allocation on the thread
 * - Subsequent allocations
 *
 * The "init window" (time from thread start to first allocation) is critical
 * for identifying the race condition. Windows shorter than 20 microseconds
 * indicate threads that are in the critical race window where Thread::current()
 * might return nullptr during JFR allocation sampling.
 */
public class ThreadLifecycleTracker {
    private final ConcurrentHashMap<Long, ThreadState> states = new ConcurrentHashMap<>();
    private final AtomicInteger threadCounter = new AtomicInteger();

    static class ThreadState {
        final long threadId;
        final String threadName;
        final long createdAtNanos;
        volatile long firstAllocationAtNanos;
        volatile int allocationCount;

        ThreadState(long threadId, String threadName, long createdAtNanos) {
            this.threadId = threadId;
            this.threadName = threadName;
            this.createdAtNanos = createdAtNanos;
            this.firstAllocationAtNanos = 0;
            this.allocationCount = 0;
        }

        long getInitWindowNanos() {
            if (firstAllocationAtNanos == 0) {
                return -1;  // No allocation yet
            }
            return firstAllocationAtNanos - createdAtNanos;
        }

        double getInitWindowMicros() {
            long nanos = getInitWindowNanos();
            return nanos >= 0 ? nanos / 1000.0 : -1.0;
        }
    }

    /**
     * Called when a new thread starts executing a task.
     */
    public void onThreadStart(long threadId, String threadName) {
        states.computeIfAbsent(threadId, id -> {
            threadCounter.incrementAndGet();
            return new ThreadState(id, threadName, System.nanoTime());
        });
    }

    /**
     * Called on the first allocation performed by a thread.
     */
    public void onFirstAllocation(long threadId) {
        ThreadState state = states.get(threadId);
        if (state != null && state.firstAllocationAtNanos == 0) {
            state.firstAllocationAtNanos = System.nanoTime();
        }
    }

    /**
     * Called for each allocation (including the first one).
     */
    public void onAllocation(long threadId) {
        ThreadState state = states.get(threadId);
        if (state != null) {
            state.allocationCount++;
        }
    }

    /**
     * Returns the total number of unique threads tracked.
     */
    public int getThreadCount() {
        return threadCounter.get();
    }

    /**
     * Exports thread lifecycle statistics to a CSV file.
     *
     * The CSV includes:
     * - threadId: JVM thread ID
     * - threadName: Thread name
     * - createdAtNanos: Nanosecond timestamp when thread was created
     * - firstAllocationAtNanos: Nanosecond timestamp of first allocation
     * - initWindowNanos: Time between creation and first allocation (nanoseconds)
     * - initWindowMicros: Init window in microseconds (for easier reading)
     * - allocationCount: Total allocations performed by this thread
     *
     * Threads are sorted by init window (shortest first) to highlight
     * those most likely to have hit the race condition.
     */
    public void exportStatistics(Path output) throws IOException {
        try (PrintWriter writer = new PrintWriter(Files.newBufferedWriter(output))) {
            writer.println("threadId,threadName,createdAtNanos,firstAllocationAtNanos,initWindowNanos,initWindowMicros,allocationCount");

            states.values().stream()
                .filter(s -> s.firstAllocationAtNanos > 0)  // Only threads that performed allocations
                .sorted(Comparator.comparingLong(ThreadState::getInitWindowNanos))
                .forEach(s -> writer.printf("%d,%s,%d,%d,%d,%.3f,%d%n",
                    s.threadId,
                    s.threadName,
                    s.createdAtNanos,
                    s.firstAllocationAtNanos,
                    s.getInitWindowNanos(),
                    s.getInitWindowMicros(),
                    s.allocationCount));
        }

        // Print summary statistics to console
        long[] windows = states.values().stream()
            .filter(s -> s.firstAllocationAtNanos > 0)
            .mapToLong(ThreadState::getInitWindowNanos)
            .sorted()
            .toArray();

        if (windows.length > 0) {
            long min = windows[0];
            long max = windows[windows.length - 1];
            long median = windows[windows.length / 2];
            double avg = 0;
            for (long w : windows) {
                avg += w;
            }
            avg /= windows.length;

            long criticalCount = 0;
            for (long w : windows) {
                if (w < 20_000) {  // Less than 20 microseconds
                    criticalCount++;
                }
            }

            System.out.println("[TRACKER] Thread Init Window Analysis:");
            System.out.printf("[TRACKER]   Threads analyzed: %d%n", windows.length);
            System.out.printf("[TRACKER]   Min: %.3f μs%n", min / 1000.0);
            System.out.printf("[TRACKER]   Max: %.3f μs%n", max / 1000.0);
            System.out.printf("[TRACKER]   Median: %.3f μs%n", median / 1000.0);
            System.out.printf("[TRACKER]   Average: %.3f μs%n", avg / 1000.0);
            System.out.printf("[TRACKER]   Critical (<20μs): %d (%.1f%%)%n",
                criticalCount, 100.0 * criticalCount / windows.length);
        }
    }
}
