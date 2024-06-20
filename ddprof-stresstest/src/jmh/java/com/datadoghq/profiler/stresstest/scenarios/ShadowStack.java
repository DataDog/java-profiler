package com.datadoghq.profiler.stresstest.scenarios;

import com.datadoghq.profiler.JavaProfiler;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.infra.Blackhole;

import java.io.IOException;

@State(Scope.Benchmark)
public class ShadowStack {
    @org.openjdk.jmh.annotations.State(Scope.Benchmark)
    public static class State {
        JavaProfiler profiler;
        @Setup(Level.Trial)
        public void setUp() {
            try {
                profiler = JavaProfiler.getInstance();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    @Benchmark
    public boolean shadowStackPopPush(State state, Blackhole bh) throws IOException  {
        JavaProfiler profiler = state.profiler;
        boolean ret = profiler.pushFrame(1) && profiler.popFrame(1);
        bh.consume(ret);
        return ret;
    }

    @Benchmark
    public boolean shadowStackPush(State state, Blackhole bh) throws IOException  {
        JavaProfiler profiler = state.profiler;
        boolean ret = profiler.pushFrame(1);
        bh.consume(ret);
        return ret;
    }
}
