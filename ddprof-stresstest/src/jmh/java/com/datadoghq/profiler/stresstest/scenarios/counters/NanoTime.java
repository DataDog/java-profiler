package com.datadoghq.profiler.stresstest.scenarios.counters;

import com.datadoghq.profiler.stresstest.Configuration;
import org.openjdk.jmh.annotations.Benchmark;

public class NanoTime {

    @Benchmark
    public long nanoTime(Configuration config) {
        return System.nanoTime();
    }
}
