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
import java.util.concurrent.CountDownLatch;
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
 * Benchmark testing RefCountGuard slot allocation under extreme concurrency.
 *
 * <p>This benchmark stress-tests the slot allocation mechanism by creating
 * large numbers of concurrent threads, approaching or exceeding typical usage
 * patterns. Key metrics:
 *
 * <ul>
 *   <li>Slot allocation latency as occupancy increases
 *   <li>Prime probing efficiency under high contention
 *   <li>Risk of slot exhaustion (MAX_THREADS=8192 limit)
 *   <li>Cache line contention effects
 * </ul>
 *
 * <p>The RefCountGuard::getThreadRefCountSlot() function uses prime probing with
 * MAX_PROBE_DISTANCE=32 attempts. Under high concurrency, probing distance
 * increases and may reach the limit, causing allocation failures.
 *
 * <p>Test scenarios:
 * - Burst thread creation: Spawn many threads simultaneously
 * - Wave pattern: Create threads in successive waves
 * - Sustained high concurrency: Maintain high thread count
 */
@State(Scope.Benchmark)
public class ProfilerThroughputSlotExhaustionBenchmark {

    @Param({"cpu=100us,wall=100us"})
    public String command;

    @Param({"false"})
    public String skipResults;

    @Param({"500", "1000", "2000", "4000"})
    private int burstThreadCount;

    @Param({"50", "100", "200"})
    private int threadLifetimeMillis;

    private JavaProfiler profiler;
    private final AtomicLong totalWork = new AtomicLong(0);
    private final AtomicLong successfulSlots = new AtomicLong(0);

    @Setup(Level.Trial)
    public void setup() throws IOException {
        profiler = JavaProfiler.getInstance();
        totalWork.set(0);
        successfulSlots.set(0);
    }

    /**
     * Work performed by each thread during slot exhaustion test.
     * Simulates real application work that would trigger profiling samples.
     */
    private long doWork(long seed, long durationMillis) {
        long result = seed;
        long endTime = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(durationMillis);

        while (System.nanoTime() < endTime) {
            for (int i = 0; i < 5000; i++) {
                result = (result * 1103515245L + 12345L) & 0x7fffffffL;
            }
        }
        return result;
    }

    /**
     * Burst test: Creates many threads simultaneously to stress slot allocation.
     * All threads start together and run for the specified lifetime.
     *
     * <p>This tests the worst-case scenario where slot allocation happens
     * under maximum contention. High probe distances and potential allocation
     * failures may occur if burstThreadCount approaches MAX_THREADS.
     */
    @Benchmark
    @BenchmarkMode(Mode.SingleShotTime)
    @Fork(value = 3, warmups = 0)
    @Warmup(iterations = 2)
    @Measurement(iterations = 5)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void burstThreadCreation(Blackhole bh) throws InterruptedException {
        CountDownLatch startLatch = new CountDownLatch(1);
        CountDownLatch completionLatch = new CountDownLatch(burstThreadCount);
        List<Thread> threads = new ArrayList<>(burstThreadCount);

        // Create all threads first
        for (int i = 0; i < burstThreadCount; i++) {
            final long seed = System.nanoTime() + i;
            Thread thread = new Thread(() -> {
                try {
                    // Wait for signal to start all threads simultaneously
                    startLatch.await();

                    long result = doWork(seed, threadLifetimeMillis);
                    totalWork.addAndGet(result);
                    successfulSlots.incrementAndGet();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                } finally {
                    completionLatch.countDown();
                }
            });
            threads.add(thread);
            thread.start();
        }

        // Start all threads simultaneously
        long startTime = System.nanoTime();
        startLatch.countDown();

        // Wait for all threads to complete
        completionLatch.await();
        long duration = System.nanoTime() - startTime;

        bh.consume(totalWork.get());
        bh.consume(successfulSlots.get());
        bh.consume(duration);
    }

    /**
     * Wave test: Creates threads in successive waves to test slot reuse.
     * Tests whether slots from completed threads are efficiently reclaimed
     * and reused by subsequent threads.
     */
    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 2, time = 2)
    @Measurement(iterations = 5, time = 5)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void waveThreadCreation(Blackhole bh) throws InterruptedException {
        int threadsPerWave = burstThreadCount / 4;
        int waves = 4;

        for (int wave = 0; wave < waves; wave++) {
            List<Thread> threads = new ArrayList<>(threadsPerWave);

            for (int i = 0; i < threadsPerWave; i++) {
                final long seed = System.nanoTime() + i;
                Thread thread = new Thread(() -> {
                    long result = doWork(seed, threadLifetimeMillis / 4);
                    totalWork.addAndGet(result);
                });
                thread.start();
                threads.add(thread);
            }

            // Wait for this wave to complete before starting next
            for (Thread thread : threads) {
                thread.join();
            }
        }

        bh.consume(totalWork.get());
    }

    /**
     * Sustained concurrency test: Maintains high thread count continuously.
     * Tests long-term stability under sustained high slot occupancy.
     */
    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 2, time = 2)
    @Measurement(iterations = 5, time = 5)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void sustainedHighConcurrency(Blackhole bh) throws InterruptedException {
        // Maintain constant high thread count by spawning replacement threads
        int activeThreads = burstThreadCount / 2;
        List<Thread> threads = new ArrayList<>(activeThreads);

        // Initial thread pool
        for (int i = 0; i < activeThreads; i++) {
            Thread thread = createWorkThread(System.nanoTime() + i);
            thread.start();
            threads.add(thread);
        }

        // Replace completed threads to maintain high occupancy
        for (int i = 0; i < activeThreads; i++) {
            threads.get(i).join();
            Thread replacement = createWorkThread(System.nanoTime() + activeThreads + i);
            replacement.start();
            threads.set(i, replacement);
        }

        // Wait for final batch
        for (Thread thread : threads) {
            thread.join();
        }

        bh.consume(totalWork.get());
    }

    private Thread createWorkThread(long seed) {
        return new Thread(() -> {
            long result = doWork(seed, threadLifetimeMillis);
            totalWork.addAndGet(result);
        });
    }
}
