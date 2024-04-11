package com.datadoghq.profiler;

import java.util.Queue;
import java.util.function.Function;

public class QueuePool implements Pool {

    private final Queue<TraceEvent> queue;

    public QueuePool(Queue<TraceEvent> queue) {
        this.queue = queue;
    }

    @Override
    @SuppressWarnings("unchecked")
    public <T extends TraceEvent> T get(Function<Pool, T> create) {
        TraceEvent event = queue.poll();
        if (event == null) {
            event = create.apply(this);
        }
        return (T) event;
    }

    @Override
    public <T extends TraceEvent> void recycle(T event) {
        if (!queue.offer(event)) {
            // we have nowhere to put the event, so we need to free the underlying
            event.free();
        }
    }
}
