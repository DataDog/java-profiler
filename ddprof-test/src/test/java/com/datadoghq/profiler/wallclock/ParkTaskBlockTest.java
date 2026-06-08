package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;

import static org.junit.jupiter.api.Assertions.assertFalse;

public class ParkTaskBlockTest extends AbstractProfilerTest {
    private static final long ROOT_SPAN_ID = 0L;
    private static final long SPAN_ID = 0L;
    private static final long BLOCKER = 0x3102L;
    private static final long UNBLOCKING_SPAN_ID = 0x3103L;

    @Test
    public void platformParkEmitsTaskBlockWithoutTraceContext() {
        registerCurrentThreadForWallClockProfiling();
        profiler.parkEnter();
        try {
            LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(20));
        } finally {
            profiler.parkExit(BLOCKER, UNBLOCKING_SPAN_ID);
        }

        stopProfiler();

        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertAnchorResolvesToMethodSample(
                taskBlockEvents, verifyEvents("datadog.MethodSample"));
        TaskBlockAssertions.assertContains(
                taskBlockEvents, ROOT_SPAN_ID, SPAN_ID, BLOCKER, UNBLOCKING_SPAN_ID);
    }

    @Test
    public void tracedPlatformParkDoesNotEmitTaskBlock() {
        registerCurrentThreadForWallClockProfiling();
        profiler.setContext(0x3100L, 0x3101L, 0L, 0x3101L);
        try {
            profiler.parkEnter();
            try {
                LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(20));
            } finally {
                profiler.parkExit(BLOCKER, UNBLOCKING_SPAN_ID);
            }
        } finally {
            profiler.clearContext();
        }

        stopProfiler();

        assertFalse(
                verifyEvents("datadog.TaskBlock", false).hasItems(),
                "Traced park interval must keep MethodSample wall-clock data instead of emitting TaskBlock");
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
    }
}
