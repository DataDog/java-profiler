/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

/**
 * Helper class for remote symbolication testing.
 * Provides JNI methods that burn CPU to ensure native frames appear in profiling samples.
 * The native library is built with GNU build-id on Linux for remote symbolication testing.
 */
public class RemoteSymHelper {
    static {
        System.loadLibrary("ddproftest");
    }

    /**
     * Burns CPU cycles by performing recursive computation.
     * This creates a distinctive call stack that should appear in profiling samples.
     *
     * @param iterations Number of iterations for computation
     * @param depth Recursion depth
     * @return Computed result (to prevent optimization)
     */
    public static native long burnCpu(long iterations, int depth);

    /**
     * Computes Fibonacci numbers repeatedly to burn CPU.
     *
     * @param n Fibonacci number to compute
     * @return Computed result (to prevent optimization)
     */
    public static native long computeFibonacci(int n);
}
