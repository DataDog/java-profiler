package com.datadoghq.profiler.context;

import one.profiler.JavaProfiler;

import java.util.concurrent.ThreadFactory;

final class RegisteringThreadFactory implements ThreadFactory {
    private final JavaProfiler profiler;

    RegisteringThreadFactory(JavaProfiler profiler) {
        this.profiler = profiler;
    }

    @Override
    public Thread newThread(Runnable task) {
        Thread thread = new Thread(() -> {
            // TODO simplify this, it has become apparent this API has a lot of downsides
            profiler.addThread(profiler.getNativeThreadId());
            task.run();
        });
        thread.setDaemon(true);
        return thread;
    }
}
