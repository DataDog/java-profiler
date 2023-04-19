package com.datadoghq.profiler.stresstest;

import org.openjdk.jmh.runner.Runner;
import org.openjdk.jmh.runner.options.CommandLineOptions;
import org.openjdk.jmh.runner.options.Options;
import org.openjdk.jmh.runner.options.OptionsBuilder;

public class Main {
    public static void main(String... args) throws Exception {
        Options options = new OptionsBuilder()
                .parent(new CommandLineOptions(args))
                .include("com.datadoghq.profiler.stresstest.scenarios.*")
                .addProfiler(WhiteboxProfiler.class)
                .build();
        new Runner(options).run();
    }
}
