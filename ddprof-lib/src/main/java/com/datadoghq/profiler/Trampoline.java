package com.datadoghq.profiler;

import java.lang.management.ManagementFactory;
import java.lang.management.MemoryMXBean;

public final class Trampoline {
    private static final MemoryMXBean memoryBean = ManagementFactory.getMemoryMXBean();
    public static long getMaxHeap() {
        return memoryBean != null ? memoryBean.getHeapMemoryUsage().getMax() : -1;
    }

    public static long getUsedHeap() {
        return memoryBean != null ? memoryBean.getHeapMemoryUsage().getUsed() : -1;
    }
}
