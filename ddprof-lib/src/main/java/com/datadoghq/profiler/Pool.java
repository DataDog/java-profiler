package com.datadoghq.profiler;

import com.datadoghq.profiler.events.EventType;

import java.util.function.BiFunction;
import java.util.function.Function;

public interface Pool {
    <T extends TraceEvent> T get(Function<Pool, T> create);

    <T extends TraceEvent> void recycle(T event);
}
