package com.datadoghq.profiler.wallclock;

import java.util.concurrent.FutureTask;

public class ContextTask<T> extends FutureTask<T> {

    public static <T> FutureTask<T> wrap(Runnable task, T value) {
        return new ContextTask<>(Tracing.capture(), task, value);
    }

    public ContextTask(Tracing.MigratingContext context, Runnable task, T value) {
        super(task, value);
        this.context = context;
    }

    @Override
    public void run() {
        try (Tracing.Context activation = this.context.activate()) {
            super.run();
        }
    }

    private final Tracing.MigratingContext context;
}
