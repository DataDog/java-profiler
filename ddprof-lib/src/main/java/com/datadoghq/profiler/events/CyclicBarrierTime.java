package com.datadoghq.profiler.events;

import com.datadoghq.profiler.Pool;

public class CyclicBarrierTime extends Origin {

    // do not rename these fields without changing the JNI access in javaApi.cpp
    private String task;

    private int barrier;
    private int generation;

    public CyclicBarrierTime(Pool pool) {
        super(EventType.CYCLIC_BARRIER, pool);
    }

    public void setTask(String task) {
        this.task = task;
    }

    public void setBarrier(int barrier, int generation) {
        this.barrier = barrier;
        this.generation = generation;
    }
}
