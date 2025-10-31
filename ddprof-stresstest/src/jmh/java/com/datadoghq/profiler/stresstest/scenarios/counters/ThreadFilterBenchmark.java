package com.datadoghq.profiler.stresstest.scenarios.counters;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.stresstest.Configuration;
import org.openjdk.jmh.annotations.*;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicIntegerArray;

@State(Scope.Benchmark)
public class ThreadFilterBenchmark extends Configuration {

    @Param({"true", "false"}) // Parameterize the filter usage
    public boolean useThreadFilters;

    private JavaProfiler profiler;
    private static final int ARRAY_SIZE = 1024; // Larger array to stress memory
    private static final int[] sharedArray = new int[ARRAY_SIZE];
    private static final AtomicIntegerArray atomicArray = new AtomicIntegerArray(ARRAY_SIZE);
    private static final int CACHE_LINE_SIZE = 64; // Typical cache line size
    private static final int STRIDE = CACHE_LINE_SIZE / Integer.BYTES; // Elements per cache line
    private static final AtomicInteger threadIds = new AtomicInteger(0);

    @Setup(Level.Trial)
    public void setup() throws IOException {
        profiler = JavaProfiler.getInstance();
    }

    @Benchmark
    @BenchmarkMode(Mode.Throughput)
    @Fork(value = 1, warmups = 1)
    @Warmup(iterations = 1, time = 1)
    @Measurement(iterations = 1, time = 2)
    @Threads(15)
    @OutputTimeUnit(TimeUnit.MILLISECONDS)
    public void threadFilterStress() throws InterruptedException {
       int threadId = threadIds.getAndAdd(1);
       // Memory-intensive operations that would be sensitive to false sharing
       for (int j = 0; j < ARRAY_SIZE; j += STRIDE) {
           if (useThreadFilters) {
               // Register thread at the start of each cache line operation
               profiler.addThread();
           }

           // Each thread writes to its own cache line
           int baseIndex = (threadId * STRIDE) % ARRAY_SIZE;
           for (int k = 0; k < STRIDE; k++) {
               int index = (baseIndex + k) % ARRAY_SIZE;
               // Write to shared array
               sharedArray[index] = threadId;
               // Read and modify
               int value = sharedArray[index] + 1;
               // Atomic operation
               atomicArray.set(index, value);
           }

           if (useThreadFilters) {
               // Remove thread after cache line operation
               profiler.removeThread();
           }
       }

       // More memory operations with thread registration
       for (int j = 0; j < ARRAY_SIZE; j += STRIDE) {
            if (useThreadFilters) {
                // Register thread at the start of each cache line operation
                profiler.addThread();
            }

            int baseIndex = (threadId * STRIDE) % ARRAY_SIZE;
            for (int k = 0; k < STRIDE; k++) {
                int index = (baseIndex + k) % ARRAY_SIZE;
                int value = atomicArray.get(index);
                sharedArray[index] = value * 2;
            }

            if (useThreadFilters) {
                // Remove thread after cache line operation
                profiler.removeThread();
            }
       }
    }
}