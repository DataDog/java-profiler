/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

/**
 * CPU-bound workload for {@link ContextClassLoaderUnloadTest}.
 *
 * <p>This class is never run from the application class loader: each test thread's own
 * context class loader defines a private copy from this class's bytes, so its frames
 * belong to a class that is unloaded once that thread and its loader become unreachable.
 * Do not reference it from the test by type -- only by name.
 */
public class LoaderLocalWorker implements Runnable {
    // Written after each round so the JIT cannot drop the work as dead code.
    public static volatile long sink;

    private final long durationNanos;

    public LoaderLocalWorker(long durationNanos) {
        this.durationNanos = durationNanos;
    }

    @Override
    public void run() {
        long deadline = System.nanoTime() + durationNanos;
        long checksum = 0;
        int limit = 50_000;
        while (System.nanoTime() < deadline) {
            checksum = mix(checksum, countPrimes(limit));
            // Vary the input so every round does fresh work.
            limit = 50_000 + (int) (checksum & 0x3fff);
        }
        sink = checksum;
    }

    // Sieve of Eratosthenes: the bulk of the CPU time, so most samples land here.
    static int countPrimes(int limit) {
        boolean[] composite = new boolean[limit + 1];
        int count = 0;
        for (int i = 2; i <= limit; i++) {
            if (!composite[i]) {
                count++;
                for (long j = (long) i * i; j <= limit; j += i) {
                    composite[(int) j] = true;
                }
            }
        }
        return count;
    }

    // FNV-1a style fold of each round's result into a running checksum.
    static long mix(long checksum, int value) {
        long h = checksum ^ 0xcbf29ce484222325L;
        for (int shift = 0; shift < 32; shift += 8) {
            h ^= (value >>> shift) & 0xff;
            h *= 0x100000001b3L;
        }
        return h;
    }
}
