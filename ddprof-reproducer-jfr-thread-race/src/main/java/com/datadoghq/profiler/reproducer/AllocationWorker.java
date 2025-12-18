/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.reproducer;

import java.util.concurrent.atomic.AtomicLong;

/**
 * Worker that performs allocations immediately upon thread start.
 *
 * The key design principle is to allocate as early as possible in the thread's
 * lifecycle to maximize the chance of hitting the race window where JVM's
 * Thread::current() might return nullptr during JFR ObjectAllocationSample recording.
 */
public class AllocationWorker implements Runnable {
    private final int allocationCount;
    private final int allocationSize;
    private final ThreadLifecycleTracker tracker;
    private final AtomicLong tasksCompleted;

    // Volatile sink to prevent JIT from optimizing away allocations
    private static volatile Object sink;

    public AllocationWorker(int allocationCount, int allocationSize,
                          ThreadLifecycleTracker tracker, AtomicLong tasksCompleted) {
        this.allocationCount = allocationCount;
        this.allocationSize = allocationSize;
        this.tracker = tracker;
        this.tasksCompleted = tasksCompleted;
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
                // Allocate large byte array to ensure JFR sampling
                byte[] allocation = new byte[allocationSize];

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
