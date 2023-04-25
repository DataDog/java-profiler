package com.datadoghq.profiler.stresstest;

import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.results.format.ResultFormatType;
import org.openjdk.jmh.runner.Runner;
import org.openjdk.jmh.runner.options.CommandLineOptions;
import org.openjdk.jmh.runner.options.Options;
import org.openjdk.jmh.runner.options.OptionsBuilder;
import org.openjdk.jmh.runner.options.TimeValue;

public class Main {
    public static void main(String... args) throws Exception {
        Options options = new OptionsBuilder()
                .parent(new CommandLineOptions(args))
                .include("com.datadoghq.profiler.stresstest.scenarios.*")
                .addProfiler(WhiteboxProfiler.class)
                .forks(1)
                .resultFormat(ResultFormatType.CSV)
                .warmupIterations(0)
                .measurementIterations(1)
                .measurementTime(TimeValue.seconds(5))
                .mode(Mode.AverageTime)
                .build();
        new Runner(options).run();
    }
}
