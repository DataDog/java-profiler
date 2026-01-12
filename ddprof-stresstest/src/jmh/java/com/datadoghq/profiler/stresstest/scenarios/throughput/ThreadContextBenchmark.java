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
import com.datadoghq.profiler.ThreadContext;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.concurrent.TimeUnit;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Measurement;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.TearDown;
import org.openjdk.jmh.annotations.Threads;
import org.openjdk.jmh.annotations.Warmup;
import org.openjdk.jmh.infra.Blackhole;

/**
 * Benchmark comparing ThreadContext implementations:
 * - JNI-based native implementation (putContextNative)
 * - DirectByteBuffer-based Java implementation (putContextJava)
 *
 * <p>Tests various thread counts to measure both single-threaded overhead
 * and multi-threaded contention characteristics.
 */
@State(Scope.Benchmark)
public class ThreadContextBenchmark {
    private JavaProfiler profiler;

    @Setup(Level.Trial)
    public void setup() throws IOException {
        // Initialize profiler to set up native context
        profiler = JavaProfiler.getInstance();
    }

    // Single-threaded benchmark
    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 1)
    @Measurement(iterations = 5, time = 3)
    @Threads(1)
    @OutputTimeUnit(TimeUnit.MICROSECONDS)
    public void setContext01() {
        ThreadContext ctx = profiler.getThreadContext();
        ctx.put(0x123456789ABCDEFL, 0xFEDCBA987654321L);
    }

    // Multi-threaded benchmark: 2 threads
    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 1)
    @Measurement(iterations = 5, time = 3)
    @Threads(2)
    @OutputTimeUnit(TimeUnit.MICROSECONDS)
    public void setContext02() {
        ThreadContext ctx = profiler.getThreadContext();
        ctx.put(0x123456789ABCDEFL, 0xFEDCBA987654321L);
    }
}
