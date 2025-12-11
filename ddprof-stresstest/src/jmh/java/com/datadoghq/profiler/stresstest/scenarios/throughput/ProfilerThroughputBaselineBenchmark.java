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
import java.util.concurrent.TimeUnit;
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
 * Baseline benchmark for profiler throughput with stable thread pools.
 *
 * <p>This benchmark measures end-to-end profiling overhead including:
 * - Signal handler interrupts (cpu=100us, wall=100us)
 * - Stack walking via ASGCT
 * - CallTraceStorage::put() operations with hazard pointer management
 * - Atomic operations in the hazard pointer lifecycle
 * - JFR background processing
 *
 * <p>Tests the complete profiling pipeline, not just isolated CallTraceStorage operations.
 */
@State(Scope.Benchmark)
public class ProfilerThroughputBaselineBenchmark {

    @Param({"cpu=100us,wall=100us"})
    public String command;

    @Param({"false"})
    public String skipResults;

    private JavaProfiler profiler;

    @Setup(Level.Trial)
    public void setup() throws IOException {
        profiler = JavaProfiler.getInstance();
    }

    /**
     * Performs computational work to generate stack samples.
     * The profiler will interrupt these threads and call CallTraceStorage::put().
     */
    private long doWork(long seed) {
        long result = seed;
        // Enough work to generate multiple samples
        for (int i = 0; i < 100_000; i++) {
            result = (result * 1103515245L + 12345L) & 0x7fffffffL;
        }
        return result;
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 2)
    @Measurement(iterations = 5, time = 5)
    @Threads(1)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void baseline01Thread(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 2)
    @Measurement(iterations = 5, time = 5)
    @Threads(2)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void baseline02Threads(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 2)
    @Measurement(iterations = 5, time = 5)
    @Threads(4)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void baseline04Threads(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 2)
    @Measurement(iterations = 5, time = 5)
    @Threads(8)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void baseline08Threads(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 2)
    @Measurement(iterations = 5, time = 5)
    @Threads(16)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void baseline16Threads(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 2)
    @Measurement(iterations = 5, time = 5)
    @Threads(32)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void baseline32Threads(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 2)
    @Measurement(iterations = 5, time = 5)
    @Threads(64)
    @OutputTimeUnit(TimeUnit.SECONDS)
    public void baseline64Threads(Blackhole bh) {
        bh.consume(doWork(System.nanoTime()));
    }
}
