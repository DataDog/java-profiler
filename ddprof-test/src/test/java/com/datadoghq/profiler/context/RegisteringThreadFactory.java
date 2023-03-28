package com.datadoghq.profiler.context;

import com.datadoghq.profiler.JavaProfiler;

import java.util.concurrent.ThreadFactory;

final class RegisteringThreadFactory implements ThreadFactory {
    private final JavaProfiler profiler;

    RegisteringThreadFactory(JavaProfiler profiler) {
        this.profiler = profiler;
    }

    @Override
    public Thread newThread(Runnable task) {
        Thread thread = new Thread(() -> {
            profiler.addThread();
            task.run();
        });
        thread.setDaemon(true);
        return thread;
    }
}
