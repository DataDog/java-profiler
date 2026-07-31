package com.datadoghq.profiler.stresstest.scenarios.counters;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.context.ContextExecutor;
import com.datadoghq.profiler.context.Tracing;
import com.datadoghq.profiler.stresstest.Configuration;
import org.openjdk.jmh.annotations.*;
import org.openjdk.jmh.infra.Blackhole;

import java.io.IOException;
import java.util.UUID;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.ThreadLocalRandom;
import java.util.stream.IntStream;

public class TracedParallelWork {

    private static final int SLOT_TAG0 = 0;
    private static final int SLOT_TAG1 = 1;

    @State(Scope.Benchmark)
    public static class BenchmarkState extends Configuration {

        public static final String COMMAND = BASE_COMMAND + ",attributes=tag0;tag1";

        @Param(COMMAND)
        String command;
        @Param({"10", "100", "1000"})
        int tagCardinality;
        ContextExecutor executor;
        JavaProfiler profiler;

        String[] tagValues;

        public long newTraceId() {
            return ThreadLocalRandom.current().nextLong();
        }

        public String getTag(long id) {
            int offset = (int) (Math.abs(id) % tagCardinality);
            return tagValues[offset];
        }

        @Setup(Level.Trial)
        public void setup() throws IOException {
            profiler = JavaProfiler.getInstance();
            executor = new ContextExecutor(200, profiler);
            tagValues = IntStream.range(0, tagCardinality).mapToObj(i -> UUID.randomUUID().toString())
                    .toArray(String[]::new);
        }
    }

    @Benchmark
    @Threads(8)
    public Object work(BenchmarkState state, Blackhole bh) throws ExecutionException, InterruptedException {
        try (Tracing.Context context = Tracing.newContext(state::newTraceId, state.profiler)) {
            state.profiler.setContextValue(SLOT_TAG0, state.getTag(context.getSpanId()));
            state.profiler.setContextValue(SLOT_TAG1, state.getTag(context.getSpanId() + 1));
            Future<?> f = state.executor.submit(() -> compute(state));
            bh.consume(compute(state));
            return f.get();
        }
    }

    public long compute(BenchmarkState state) {
        long x = ThreadLocalRandom.current().nextLong();
        for (int i = 0; i < 10_000; i++) {
            state.profiler.setContextValue(SLOT_TAG0, state.getTag(x));
            x ^= ThreadLocalRandom.current().nextLong();
            state.profiler.setContextValue(SLOT_TAG1, state.getTag(x));
        }
        return x;
    }

}
