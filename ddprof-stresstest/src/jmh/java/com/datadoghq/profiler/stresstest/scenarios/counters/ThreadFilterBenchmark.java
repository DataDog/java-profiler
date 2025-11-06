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
import java.util.concurrent.atomic.AtomicLongArray;

@State(Scope.Benchmark)
public class ThreadFilterBenchmark extends Configuration {

    @Param({"true", "false"}) // Parameterize the filter usage
    public boolean useThreadFilters;

    private JavaProfiler profiler;
    private static final int ARRAY_SIZE = 1024; // Larger array to stress memory
    private static final long[] sharedArray = new long[ARRAY_SIZE];
    private static final AtomicLongArray atomicArray = new AtomicLongArray(ARRAY_SIZE);
    private static final int CACHE_LINE_SIZE = 64; // Typical cache line size
    private static final int STRIDE = CACHE_LINE_SIZE / Integer.BYTES; // Elements per cache line

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
       long threadId = Thread.currentThread().getId();
       // Memory-intensive operations that would be sensitive to false sharing
       for (int j = 0; j < ARRAY_SIZE; j += STRIDE) {
           if (useThreadFilters) {
               // Register thread at the start of each cache line operation
               profiler.addThread();
           }

           // Each thread writes to its own cache line
           long baseIndex = (threadId * STRIDE) % ARRAY_SIZE;
           for (int k = 0; k < STRIDE; k++) {
               int index = (int)(baseIndex + k) % ARRAY_SIZE;
               // Write to shared array
               sharedArray[index] = threadId;
               // Read and modify
               long value = sharedArray[index] + 1;
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

            long baseIndex = (threadId * STRIDE) % ARRAY_SIZE;
            for (int k = 0; k < STRIDE; k++) {
                int index = (int)(baseIndex + k) % ARRAY_SIZE;
                long value = atomicArray.get(index);
                sharedArray[index] = value * 2;
            }

            if (useThreadFilters) {
                // Remove thread after cache line operation
                profiler.removeThread();
            }
       }
    }
}