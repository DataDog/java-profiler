package com.datadoghq.profiler;

import java.util.concurrent.TimeUnit;

public interface TraceEvent extends AutoCloseable {

    boolean shouldCommit(long threshold, TimeUnit timeUnit);

    void commit();

    void reset();

    void free();

    default void close() {
        commit();
    }

}
