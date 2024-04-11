package com.datadoghq.profiler.events;

import com.datadoghq.profiler.Pool;

public class QueueTime extends Origin {

    // do not rename these fields without changing the JNI access in javaApi.cpp
    private String task;
    private String scheduler;

    public QueueTime(Pool pool) {
        super(EventType.QUEUE, pool);
    }

    public void setTask(String task) {
        this.task = task;
    }

    public void setScheduler(String scheduler) {
        this.scheduler = scheduler;
    }
}
