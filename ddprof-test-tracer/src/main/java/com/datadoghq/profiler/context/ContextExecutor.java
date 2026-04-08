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

    @Override
    protected void beforeExecute(Thread t, Runnable r) {
        super.beforeExecute(t, r);
        profiler.addThread();
        // Prime OTEL context TLS to avoid race condition with wall clock signals.
        // TLS is lazily initialized on first setContext() call, which happens in
        // ContextTask.run() after this method returns. If a wall clock signal
        // arrives between now and then, the context would be uninitialized.
        profiler.setContext(0, 0);
    }

    @Override
    protected void afterExecute(Runnable r, Throwable t) {
        profiler.removeThread();
        super.afterExecute(r, t);
    }
}
