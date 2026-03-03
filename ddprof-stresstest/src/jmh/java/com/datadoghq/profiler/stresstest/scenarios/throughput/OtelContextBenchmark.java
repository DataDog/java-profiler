/*
 * Copyright 2026, Datadog, Inc
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
import com.datadoghq.profiler.OTelContext;
import com.datadoghq.profiler.ThreadContext;

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


import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.io.IOException;
import java.util.concurrent.TimeUnit;

@State(Scope.Benchmark)
@BenchmarkMode(Mode.Throughput)
@Warmup(iterations = 3)
@Measurement(iterations = 5)
@OutputTimeUnit(TimeUnit.MICROSECONDS)
public class OtelContextBenchmark {

    @Param({"profiler", "otel"})
    String mode;

    private static volatile JavaProfiler profiler;
    private static Object lock = new Object();

    @Setup(Level.Iteration)
    public void setup() throws IOException {
        synchronized(lock) {
            if (profiler == null) {
                profiler = JavaProfiler.getInstance();
                Path jfrFile = Files.createTempFile("otel-ctx-profiler", ".jfr");        
                profiler.execute(String.format("start,cpu=1ms,ctxstorage=%s,jfr,file=%s", mode, jfrFile.toAbsolutePath()));
            }
        }
    }

    @TearDown(Level.Iteration)
    public void tearDown() throws IOException {
        synchronized(lock) {
            if (profiler != null) {
                profiler.stop();
                profiler = null;
            }
        }
    }

    @Benchmark
    public void setThreadContext() {
        long spanId = 0xbababa;
        long rootSpanId = 0xdedede;
        profiler.setContext(spanId, rootSpanId);
    }

    @Benchmark
    public void getThreadContext(Blackhole bh) {
        ThreadContext context = profiler.getThreadContext();
        bh.consume(context);
    }

    @Benchmark
    @Threads(8)
    public void setThreadContexts() {
        long spanId = 0xbababa;
        long rootSpanId = 0xdedede;
        profiler.setContext(spanId, rootSpanId);
    }

    @Benchmark
    @Threads(8)
    public void getThreadContexts(Blackhole bh) {
        ThreadContext context = profiler.getThreadContext();
        bh.consume(context);
    }
}
