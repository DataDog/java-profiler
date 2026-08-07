/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;

import java.util.concurrent.locks.LockSupport;

public class CollapsingSleepTest extends AbstractProfilerTest {

    @Test
    public void testSleep() {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        long ts = System.nanoTime();
        long waitTime = 1_000_000_000L; // 1mil ns == 1s
        do {
            LockSupport.parkNanos(waitTime);
            waitTime -= (System.nanoTime() - ts);
            ts = System.nanoTime();
        } while (waitTime > 1_000);
        stopProfiler();
        JfrEvents events = verifyEvents("datadog.MethodSample");
        assertTrue(events.hasItems());
        long totalWeight = 0;
        for (JfrEvent item : events) {
            totalWeight += item.getLong(WEIGHT, 0);
        }
        assertTrue(totalWeight > 700);
        assertTrue(events.count() > 9);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms";
    }
}
