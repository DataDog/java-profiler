package com.datadoghq.profiler.events;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Pool;
import com.datadoghq.profiler.TraceEvent;

import java.util.concurrent.TimeUnit;

abstract class Origin implements TraceEvent {
    protected final long timerHandle;
    private final EventType eventType;

    private final Pool pool;

    private long startMillis;

    private volatile boolean freed;

    protected Origin(EventType type, Pool pool) {
        JavaProfiler.ensureLoaded();
        this.timerHandle = createTimer0(type.ordinal());
        this.eventType = type;
        this.pool = pool;
    }

    @Override
    public void reset() {
        init0(timerHandle);
        startMillis = System.currentTimeMillis();
    }

    @Override
    public boolean shouldCommit(long threshold, TimeUnit timeUnit) {
        return System.currentTimeMillis() - startMillis >= timeUnit.toMillis(threshold);
    }

    @Override
    public void commit() {
        commit0(eventType.ordinal(), timerHandle);
    }

    @Override
    public void close() {
        pool.recycle(this);
    }

    @Override
    public void free() {
        if (!freed) {
            synchronized (this) {
                if (!freed) {
                    freed = true;
                    free0(timerHandle);
                }
            }
        }
    }

    private static native long createTimer0(int type);
    private static native void init0(long timerHandle);

    private static native void free0(long timerHandle);

    private native void commit0(int type, long timerHandle);
}
