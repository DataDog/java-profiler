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
import org.openjdk.jmh.annotations.Threads;
import org.openjdk.jmh.annotations.Warmup;
import org.openjdk.jmh.infra.Blackhole;

/**
 * Quick smoke test for CallTraceStorage short-lived thread performance.
 *
 * <p>This benchmark provides fast feedback (~2 minutes) on key performance metrics:
 * - Baseline stable thread performance (1, 8, 32 threads)
 * - Short-lived thread churn overhead
 * - Moderate concurrency slot allocation
 *
 * <p>Use this for rapid iteration during development. For comprehensive analysis,
 * use the full benchmark suite (CallTraceStorageBaselineBenchmark, etc.).
 */
@State(Scope.Benchmark)
public class ProfilerThroughputQuickBenchmark {

    @Param({"cpu=100us,wall=100us"})
    public String command;

    @Param({"false"})
    public String skipResults;

    private JavaProfiler profiler;
    private final AtomicLong totalWork = new AtomicLong(0);

    @Setup(Level.Trial)
    public void setup() throws IOException {
        profiler = JavaProfiler.getInstance();
        totalWork.set(0);
    }

    private long doWork(long seed) {
        long result = seed;
        for (int i = 0; i < 100_000; i++) {
            result = (result * 1103515245L + 12345L) & 0x7fffffffL;
        }
        return result;
    }

    private long doShortWork(long seed, long durationMillis) {
        long result = seed;
        long endTime = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(durationMillis);
        while (System.nanoTime() < endTime) {
            for (int i = 0; i < 1000; i++) {
                result = (result * 1103515245L + 12345L) & 0x7fffffffL;
            }
        }
        return result;
    }

    // === Baseline Tests ===

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 1, warmups = 0)
    @Warmup(iterations = 1, time = 1)
    @Measurement(iterations = 2, time = 2)
    @Threads(1)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void baseline01Thread(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 1, warmups = 0)
    @Warmup(iterations = 1, time = 1)
    @Measurement(iterations = 2, time = 2)
    @Threads(8)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void baseline08Threads(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 1, warmups = 0)
    @Warmup(iterations = 1, time = 1)
    @Measurement(iterations = 2, time = 2)
    @Threads(32)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void baseline32Threads(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }

    // === Thread Churn Tests ===

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 1, warmups = 0)
    @Warmup(iterations = 1, time = 1)
    @Measurement(iterations = 2, time = 3)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void churn10ThreadsShort(Blackhole bh) throws InterruptedException {
        List<Thread> threads = new ArrayList<>(10);
        for (int i = 0; i < 10; i++) {
            final long seed = System.nanoTime() + i;
            Thread thread = new Thread(() -> {
                long result = doShortWork(seed, 5);
                totalWork.addAndGet(result);
            });
            thread.start();
            threads.add(thread);
        }
        for (Thread thread : threads) {
            thread.join();
        }
        bh.consume(totalWork.get());
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 1, warmups = 0)
    @Warmup(iterations = 1, time = 1)
    @Measurement(iterations = 2, time = 3)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void churn50ThreadsShort(Blackhole bh) throws InterruptedException {
        List<Thread> threads = new ArrayList<>(50);
        for (int i = 0; i < 50; i++) {
            final long seed = System.nanoTime() + i;
            Thread thread = new Thread(() -> {
                long result = doShortWork(seed, 5);
                totalWork.addAndGet(result);
            });
            thread.start();
            threads.add(thread);
        }
        for (Thread thread : threads) {
            thread.join();
        }
        bh.consume(totalWork.get());
    }

    // === Slot Allocation Test ===

    @Benchmark
    @BenchmarkMode(Mode.SingleShotTime)
    @Fork(value = 1, warmups = 0)
    @Warmup(iterations = 1)
    @Measurement(iterations = 3)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void burst500Threads(Blackhole bh) throws InterruptedException {
        List<Thread> threads = new ArrayList<>(500);
        for (int i = 0; i < 500; i++) {
            final long seed = System.nanoTime() + i;
            Thread thread = new Thread(() -> {
                long result = doShortWork(seed, 100);
                totalWork.addAndGet(result);
            });
            thread.start();
            threads.add(thread);
        }
        for (Thread thread : threads) {
            thread.join();
        }
        bh.consume(totalWork.get());
    }
}
