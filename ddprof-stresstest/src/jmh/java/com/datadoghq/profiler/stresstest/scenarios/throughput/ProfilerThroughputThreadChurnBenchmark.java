/*
 * Copyright 2025, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler.stresstest.scenarios.throughput;

import com.datadoghq.profiler.JavaProfiler;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Measurement;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.TearDown;
import org.openjdk.jmh.annotations.Warmup;
import org.openjdk.jmh.infra.Blackhole;

/**
 * Benchmark for profiler throughput under high thread churn.
 *
 * <p>This benchmark measures end-to-end profiling overhead with frequent
 * thread creation and destruction. Key components tested:
 *
 * <ul>
 *   <li>Signal handler interrupts (cpu/wall profiling)
 *   <li>Stack walking via ASGCT
 *   <li>HazardPointer slot allocation (prime probing with up to 32 attempts)
 *   <li>CallTraceStorage::put() operations (5 atomic ops per call)
 *   <li>JFR background processing
 *   <li>Slot cleanup and reuse efficiency
 * </ul>
 *
 * <p>Each short-lived thread:
 * 1. Acquires a HazardPointer slot via getThreadHazardSlot()
 * 2. Performs work that may be sampled by the profiler (full stack walking)
 * 3. Releases the slot in the destructor
 *
 * <p>High thread churn tests whether:
 * - Slots are efficiently reused
 * - Prime probing remains effective under contention
 * - The system avoids slot exhaustion (MAX_THREADS=8192)
 */
@State(Scope.Benchmark)
public class ProfilerThroughputThreadChurnBenchmark {

    @Param({"cpu=100us,wall=100us"})
    public String command;

    @Param({"false"})
    public String skipResults;

    @Param({"1", "5", "10"})
    private int threadLifetimeMillis;

    @Param({"10", "50", "100"})
    private int concurrentThreads;

    private JavaProfiler profiler;
    private final AtomicLong totalWork = new AtomicLong(0);

    @Setup(Level.Trial)
    public void setup() throws IOException {
        profiler = JavaProfiler.getInstance();
        totalWork.set(0);
    }

    /**
     * Work performed by each short-lived thread.
     * Designed to generate stack samples while avoiding excessive CPU time.
     */
    private long doShortLivedWork(long seed) {
        long result = seed;
        long endTime = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(threadLifetimeMillis);

        while (System.nanoTime() < endTime) {
            // Light work to keep thread alive and generate samples
            for (int i = 0; i < 1000; i++) {
                result = (result * 1103515245L + 12345L) & 0x7fffffffL;
            }
        }
        return result;
    }

    /**
     * Spawns a batch of short-lived threads and waits for them to complete.
     * Measures throughput in terms of thread batches processed per second.
     */
    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 3)
    @Measurement(iterations = 5, time = 10)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void threadChurn(Blackhole bh) throws InterruptedException {
        List<Thread> threads = new ArrayList<>(concurrentThreads);

        // Spawn concurrent short-lived threads
        for (int i = 0; i < concurrentThreads; i++) {
            final long seed = System.nanoTime() + i;
            Thread thread = new Thread(() -> {
                long result = doShortLivedWork(seed);
                totalWork.addAndGet(result);
            });
            thread.start();
            threads.add(thread);
        }

        // Wait for all threads to complete
        for (Thread thread : threads) {
            thread.join();
        }

        bh.consume(totalWork.get());
    }

    /**
     * Mixed workload: background long-lived threads plus continuous short-lived thread spawning.
     * Tests realistic scenario where stable workers coexist with transient threads.
     */
    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 3)
    @Measurement(iterations = 5, time = 10)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void mixedWorkload(Blackhole bh) throws InterruptedException {
        // Background work simulating long-lived threads
        long backgroundWork = 0;
        for (int i = 0; i < 10_000; i++) {
            backgroundWork = (backgroundWork * 1103515245L + 12345L) & 0x7fffffffL;
        }

        // Spawn short-lived threads concurrently with background work
        List<Thread> threads = new ArrayList<>(concurrentThreads / 2);
        for (int i = 0; i < concurrentThreads / 2; i++) {
            final long seed = System.nanoTime() + i;
            Thread thread = new Thread(() -> {
                long result = doShortLivedWork(seed);
                totalWork.addAndGet(result);
            });
            thread.start();
            threads.add(thread);
        }

        // More background work while short-lived threads execute
        for (int i = 0; i < 10_000; i++) {
            backgroundWork = (backgroundWork * 1103515245L + 12345L) & 0x7fffffffL;
        }

        // Wait for short-lived threads
        for (Thread thread : threads) {
            thread.join();
        }

        bh.consume(backgroundWork);
        bh.consume(totalWork.get());
    }
}
