/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <jni.h>
#include <stdint.h>

/**
 * Recursive CPU-burning function that creates a distinct call stack.
 * This ensures native frames from this library appear in profiling samples.
 */
static uint64_t burn_cpu_recursive(uint64_t n, uint64_t depth) {
    if (depth == 0) {
        // Base case: perform actual computation
        uint64_t sum = 0;
        for (uint64_t i = 0; i < n; i++) {
            sum += i * i;
        }
        return sum;
    }

    // Recursive case: go deeper
    return burn_cpu_recursive(n, depth - 1) + depth;
}

/**
 * Entry point for CPU-burning work.
 * Called from Java to generate CPU samples with this library on the stack.
 */
JNIEXPORT jlong JNICALL
Java_com_datadoghq_profiler_RemoteSymHelper_burnCpu(JNIEnv *env, jclass clazz, jlong iterations, jint depth) {
    return (jlong)burn_cpu_recursive((uint64_t)iterations, (uint32_t)depth);
}

/**
 * Additional function to create more stack depth.
 */
static uint64_t compute_fibonacci(uint32_t n) {
    if (n <= 1) return n;

    uint64_t a = 0, b = 1;
    for (uint32_t i = 2; i <= n; i++) {
        uint64_t temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

/**
 * Another entry point with different stack signature.
 */
JNIEXPORT jlong JNICALL
Java_com_datadoghq_profiler_RemoteSymHelper_computeFibonacci(JNIEnv *env, jclass clazz, jint n) {
    // Call multiple times to increase likelihood of sampling
    uint64_t result = 0;
    for (int i = 0; i < 1000; i++) {
        result += compute_fibonacci((uint32_t)n);
    }
    return (jlong)result;
}
