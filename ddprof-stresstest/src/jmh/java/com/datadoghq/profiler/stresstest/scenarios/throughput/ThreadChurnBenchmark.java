/*
 * Copyright 2025, Datadog, Inc.
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
import com.datadoghq.profiler.stresstest.Configuration;
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

import java.io.IOException;
import java.util.concurrent.TimeUnit;

/**
 * Benchmark to measure throughput impact of TLS priming overhead during high thread churn
 * scenarios. This helps identify performance regressions in the thread directory watcher
 * introduced for native thread TLS priming.
 */
@State(Scope.Benchmark)
@BenchmarkMode(Mode.Throughput)
@OutputTimeUnit(TimeUnit.MILLISECONDS)
public class ThreadChurnBenchmark extends Configuration {

    @Param({BASE_COMMAND})
    public String command;

    @Param({"true", "false"})
    public boolean profilingEnabled;

    @Param({"0", "1000", "10000"})
    public int workPerThread;

    private JavaProfiler profiler;

    @Setup(Level.Trial)
    public void setup() throws IOException {
        profiler = JavaProfiler.getInstance();
        if (profilingEnabled) {
            profiler.execute("start," + command + ",jfr,file=/tmp/thread-churn-benchmark.jfr");
        }
    }

    @TearDown(Level.Trial)
    public void tearDown() throws IOException {
        if (profilingEnabled && profiler != null) {
            profiler.execute("stop");
        }
    }

    @Benchmark
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 5)
    @Measurement(iterations = 5, time = 10)
    @Threads(4)
    public void threadChurn04(Blackhole bh) throws InterruptedException {
        Thread t = new Thread(() -> {
            long sum = 0;
            for (int i = 0; i < workPerThread; i++) {
                sum += i;
            }
            Blackhole.consumeCPU(sum);
        });
        t.start();
        t.join();
    }

    @Benchmark
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 5)
    @Measurement(iterations = 5, time = 10)
    @Threads(8)
    public void threadChurn08(Blackhole bh) throws InterruptedException {
        Thread t = new Thread(() -> {
            long sum = 0;
            for (int i = 0; i < workPerThread; i++) {
                sum += i;
            }
            Blackhole.consumeCPU(sum);
        });
        t.start();
        t.join();
    }

    @Benchmark
    @Fork(value = 3, warmups = 1)
    @Warmup(iterations = 3, time = 5)
    @Measurement(iterations = 5, time = 10)
    @Threads(16)
    public void threadChurn16(Blackhole bh) throws InterruptedException {
        Thread t = new Thread(() -> {
            long sum = 0;
            for (int i = 0; i < workPerThread; i++) {
                sum += i;
            }
            Blackhole.consumeCPU(sum);
        });
        t.start();
        t.join();
    }
}
