/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.reproducer;

import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Worker that performs allocations immediately upon thread start.
 *
 * The key design principle is to allocate as early as possible in the thread's
 * lifecycle to maximize the chance of hitting the race window where JVM's
 * Thread::current() might return nullptr during JFR ObjectAllocationSample recording.
 *
 * Allocation sizes are randomized around the target average to create realistic
 * allocation patterns and increase chances of hitting various code paths.
 */
public class AllocationWorker implements Runnable {
    // Sensible bounds for allocation sizes
    private static final int MIN_ALLOCATION_SIZE = 1024;        // 1KB minimum
    private static final int MAX_ALLOCATION_SIZE = 10_000_000;  // 10MB maximum

    private final int allocationCount;
    private final int averageAllocationSize;
    private final ThreadLifecycleTracker tracker;
    private final AtomicLong tasksCompleted;

    // Volatile sink to prevent JIT from optimizing away allocations
    private static volatile Object sink;

    public AllocationWorker(int allocationCount, int allocationSize,
                          ThreadLifecycleTracker tracker, AtomicLong tasksCompleted) {
        this.allocationCount = allocationCount;
        // Cap the average to sensible bounds
        this.averageAllocationSize = Math.max(MIN_ALLOCATION_SIZE,
                                             Math.min(MAX_ALLOCATION_SIZE, allocationSize));
        this.tracker = tracker;
        this.tasksCompleted = tasksCompleted;
    }

    /**
     * Generates a random allocation size around the average.
     *
     * Uses a triangular-like distribution:
     * - 50% of values within ±25% of average
     * - 25% of values between average and 2x average
     * - 25% of values between average/2 and average
     *
     * Always capped to sensible min/max bounds.
     */
    private int getRandomAllocationSize() {
        ThreadLocalRandom random = ThreadLocalRandom.current();

        // Generate size with variance around average (±50% typical range)
        // Using exponential-like distribution for more realistic patterns
        double variance = random.nextDouble(0.5, 1.5);
        int size = (int) (averageAllocationSize * variance);

        // Occasionally generate very small or very large allocations
        if (random.nextInt(100) < 5) {  // 5% chance
            if (random.nextBoolean()) {
                // Very small allocation
                size = random.nextInt(MIN_ALLOCATION_SIZE, averageAllocationSize / 4);
            } else {
                // Very large allocation (up to 3x average)
                size = random.nextInt(averageAllocationSize,
                                    Math.min(averageAllocationSize * 3, MAX_ALLOCATION_SIZE));
            }
        }

        // Ensure within bounds
        return Math.max(MIN_ALLOCATION_SIZE, Math.min(MAX_ALLOCATION_SIZE, size));
    }

    @Override
    public void run() {
        long threadId = Thread.currentThread().getId();
        String threadName = Thread.currentThread().getName();

        // Track thread start
        tracker.onThreadStart(threadId, threadName);

        try {
            // CRITICAL: Allocate IMMEDIATELY before any other operations
            // This maximizes the chance of hitting the narrow race window
            // during thread initialization where Thread::current() might be nullptr
            for (int i = 0; i < allocationCount; i++) {
                // Get randomized allocation size around average
                int size = getRandomAllocationSize();

                // Allocate byte array with random size
                byte[] allocation = new byte[size];

                // Track first allocation timing
                if (i == 0) {
                    tracker.onFirstAllocation(threadId);
                }

                // Prevent JIT optimization
                sink = allocation;

                // Increment allocation counter
                tracker.onAllocation(threadId);
            }

            tasksCompleted.incrementAndGet();

        } catch (Throwable t) {
            System.err.println("[WORKER] Error in thread " + threadId + ": " + t.getMessage());
            t.printStackTrace();
        }
    }
}
