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

import com.datadoghq.profiler.OTelContext;
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
import org.openjdk.jmh.annotations.Threads;
import org.openjdk.jmh.annotations.Warmup;
import org.openjdk.jmh.infra.Blackhole;


import java.io.IOException;
import java.util.concurrent.TimeUnit;

@State(Scope.Thread)
@BenchmarkMode(Mode.Throughput)
@Warmup(iterations = 3)
@Measurement(iterations = 5)
@OutputTimeUnit(TimeUnit.MICROSECONDS)
public class ProcessContextBenchmark {
    private static final String ENV = "Benchmark";
    private static final String HOST = "Benchmark-host";
    private static final String RUNTIME = "Benchmark-runtime";
    private static final String SERVICE = "Benchmark-service";
    private static final String VERSION = "1.0";
    private static final String TRACER_VERSION = "1.0";

    private OTelContext context;

    @Setup(Level.Trial)
    public void setup() throws IOException {
        context = OTelContext.getInstance();
    }

    @Benchmark
    public void setProcessContext() {
        context.setProcessContext(ENV, HOST, RUNTIME, SERVICE, VERSION, TRACER_VERSION);
    }

    @Benchmark
    public void readProcessContext(Blackhole bh) {
        OTelContext.ProcessContext readContext = context.readProcessContext();
        bh.consume(readContext);
    }
}
