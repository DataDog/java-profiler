package com.datadoghq.profiler.stresstest.scenarios;

import com.datadoghq.profiler.stresstest.BaseScenario;
import com.datadoghq.profiler.stresstest.Configuration;
import org.openjdk.jmh.annotations.Benchmark;

public class NanoTime extends BaseScenario {

    @Benchmark
    public long nanoTime(Configuration config) {
        return System.nanoTime();
    }
}
