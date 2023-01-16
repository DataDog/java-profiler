package com.datadoghq.profiler.context;

import com.datadoghq.profiler.JavaProfiler;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.RunnableFuture;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class ContextExecutor extends ThreadPoolExecutor {

    private final JavaProfiler profiler;
    public ContextExecutor(int corePoolSize, JavaProfiler profiler) {
        super(corePoolSize, corePoolSize, 30, TimeUnit.SECONDS,
                new ArrayBlockingQueue<>(128), new RegisteringThreadFactory(profiler));
        this.profiler = profiler;
    }

    @Override
    protected <T> RunnableFuture<T> newTaskFor(Runnable runnable, T value) {
        return ContextTask.wrap(runnable, value);
    }
}
