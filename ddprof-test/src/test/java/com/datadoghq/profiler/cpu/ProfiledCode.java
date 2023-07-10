package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.context.ContextExecutor;
import com.datadoghq.profiler.context.Tracing;

import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;

public class ProfiledCode implements AutoCloseable {

    private static volatile long sink;
    private final ContextExecutor executor;
    private final JavaProfiler profiler;

    private final Map<String, List<Long>> methodsToSpanIds = new ConcurrentHashMap<>();

    public ProfiledCode(JavaProfiler profiler) {
        this.profiler = profiler;
        this.executor = new ContextExecutor(1, profiler);
    }

    public void method1(int id) throws ExecutionException, InterruptedException {
        try (Tracing.Context context = Tracing.newContext(() -> id, profiler)) {
            method1Impl(id, context);
        }
    }

    public void method1Impl(int id, Tracing.Context context) throws ExecutionException, InterruptedException {
        burnCycles();
        Future<?> wait = executor.submit(() -> method3(id));
        method2(id);
        wait.get();
        record("method1Impl", context);
    }

    public void method2(long id) {
        try (Tracing.Context context = Tracing.newContext(() -> id + 1, profiler)) {
            method2Impl(context);
        }
    }

    public void method2Impl(Tracing.Context context) {
        burnCycles();
        record("method2Impl", context);
    }

    public void method3(long id) {
        try (Tracing.Context context = Tracing.newContext(() -> id + 2, profiler)) {
            method3Impl(context);
        }
    }

    public void method3Impl(Tracing.Context context) {
        burnCycles();
        record("method3Impl", context);
    }

    public Set<Long> spanIdsForMethod(String methodName) {
        return new HashSet<>(methodsToSpanIds.get(methodName));
    }

    public Set<Long> allSampledSpanIds() {
        Set<Long> all = new HashSet<>();
        methodsToSpanIds.values().forEach(all::addAll);
        return all;
    }


    private void record(String methodName, Tracing.Context context) {
        methodsToSpanIds.computeIfAbsent(methodName, k -> new CopyOnWriteArrayList<>())
                .add(context.getSpanId());
    }

    private void burnCycles() {
        long blackhole = sink;
        for (int i = 0; i < 1_000_000; i++) {
            blackhole ^= ThreadLocalRandom.current().nextLong();
        }
        sink = blackhole;
    }

    @Override
    public void close() throws Exception {
        executor.shutdownNow();
        executor.awaitTermination(30, TimeUnit.SECONDS);
    }
}
