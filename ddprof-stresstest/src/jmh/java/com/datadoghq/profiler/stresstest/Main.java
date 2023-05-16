package com.datadoghq.profiler.stresstest;

import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.results.RunResult;
import org.openjdk.jmh.runner.Runner;
import org.openjdk.jmh.runner.options.CommandLineOptions;
import org.openjdk.jmh.runner.options.Options;
import org.openjdk.jmh.runner.options.OptionsBuilder;
import org.openjdk.jmh.runner.options.TimeValue;

import java.util.Collection;
import java.util.concurrent.TimeUnit;

public class Main {

    public static final String SCENARIOS_PACKAGE = "com.datadoghq.profiler.stresstest.scenarios.";

    public static void main(String... args) throws Exception {
        CommandLineOptions commandLineOptions = new CommandLineOptions(args);
        Mode mode = Mode.AverageTime;
        Options options = new OptionsBuilder()
                .parent(new CommandLineOptions(args))
                .include(SCENARIOS_PACKAGE + "*")
                .addProfiler(WhiteboxProfiler.class)
                .forks(commandLineOptions.getForkCount().orElse(1))
                .warmupIterations(commandLineOptions.getWarmupIterations().orElse(0))
                .measurementIterations(commandLineOptions.getMeasurementIterations().orElse(1))
                .measurementTime(commandLineOptions.getMeasurementTime().orElse(TimeValue.seconds(5)))
                .timeUnit(commandLineOptions.getTimeUnit().orElse(TimeUnit.MICROSECONDS))
                .mode(mode)
                .build();
        Collection<RunResult> results = new Runner(options).run();
        CompositeFormatter.of(new HtmlCommentFormatter(results, mode), new HtmlFormatter(results, mode)).format();
    }
}
