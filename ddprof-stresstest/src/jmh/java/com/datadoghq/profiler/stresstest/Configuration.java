package com.datadoghq.profiler.stresstest;

import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.State;

@State(Scope.Benchmark)
public class Configuration {

    @Param({"cpu=1us,wall=1us"})
    public String command;
}
