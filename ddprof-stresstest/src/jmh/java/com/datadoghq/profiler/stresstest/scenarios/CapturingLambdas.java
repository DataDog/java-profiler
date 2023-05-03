package com.datadoghq.profiler.stresstest.scenarios;

import com.datadoghq.profiler.stresstest.Configuration;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.CompilerControl;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.State;

import java.util.UUID;
import java.util.concurrent.ThreadLocalRandom;
import java.util.function.Supplier;

@State(Scope.Benchmark)
public class CapturingLambdas extends Configuration {

    @Param(BASE_COMMAND + ",memory=1048576:a")
    public String command;

    @Benchmark
    public Object capturingLambda() {
        return lambda(UUID.randomUUID()).get();
    }


    @CompilerControl(CompilerControl.Mode.DONT_INLINE)
    public Supplier<Object> lambda(UUID state) {
        return () -> state.getLeastSignificantBits() * ThreadLocalRandom.current().nextLong();
    }
}
