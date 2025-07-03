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
import org.openjdk.jmh.annotations.Threads;
import org.openjdk.jmh.annotations.Warmup;
import org.openjdk.jmh.infra.Blackhole;

import java.io.IOException;
import java.util.concurrent.TimeUnit;

@State(Scope.Benchmark)
public class ThreadFilterBenchmark extends Configuration {
    private JavaProfiler profiler;

    @Param(BASE_COMMAND + ",filter=1")
    public String command;

    @Param("true")
    public String skipResults;

    @Param({"0", "7", "70000"})
    public String workload;

    private long workloadNum = 0;

    @Setup(Level.Trial)
    public void setup() throws IOException {
        profiler = JavaProfiler.getInstance();
        workloadNum = Long.parseLong(workload);
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 3)
    @Warmup(iterations = 5)
    @Measurement(iterations = 8)
    @Threads(1)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void threadFilterStress01() throws InterruptedException {
        profiler.addThread();
        // Simulate per-thread work
        Blackhole.consumeCPU(workloadNum);
        profiler.removeThread();
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 3)
    @Warmup(iterations = 5)
    @Measurement(iterations = 8)
    @Threads(2)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void threadFilterStress02() throws InterruptedException {
        profiler.addThread();
        // Simulate per-thread work
        Blackhole.consumeCPU(workloadNum);
        profiler.removeThread();
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 3)
    @Warmup(iterations = 5)
    @Measurement(iterations = 8)
    @Threads(4)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void threadFilterStress04() throws InterruptedException {
        profiler.addThread();
        // Simulate per-thread work
        Blackhole.consumeCPU(workloadNum);
        profiler.removeThread();
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 3)
    @Warmup(iterations = 5)
    @Measurement(iterations = 8)
    @Threads(8)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void threadFilterStress08() throws InterruptedException {
        profiler.addThread();
        // Simulate per-thread work
        Blackhole.consumeCPU(workloadNum);
        profiler.removeThread();
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 3, warmups = 3)
    @Warmup(iterations = 5)
    @Measurement(iterations = 8)
    @Threads(16)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void threadFilterStress16() throws InterruptedException {
        profiler.addThread();
        // Simulate per-thread work
        Blackhole.consumeCPU(workloadNum);
        profiler.removeThread();
    }
}
