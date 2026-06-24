package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class ParkTaskBlockTest extends AbstractProfilerTest {
    private static final long ROOT_SPAN_ID = 0L;
    private static final long SPAN_ID = 0L;
    private static final long BLOCKER = 0x3102L;
    private static final long UNBLOCKING_SPAN_ID = 0x3103L;

    @Test
    public void platformParkEmitsTaskBlockWithoutTraceContext() {
        registerCurrentThreadForWallClockProfiling();
        ProfilerOwnedBlockHooks.parkEnter(profiler);
        try {
            LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(200));
        } finally {
            ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
        }

        stopProfiler();

        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        assertTaskBlockStackReference(taskBlockEvents);
        TaskBlockAssertions.assertContains(
                taskBlockEvents, ROOT_SPAN_ID, SPAN_ID, BLOCKER, UNBLOCKING_SPAN_ID);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "PARKED");
        TaskBlockAssertions.assertWallClockEpochDoesNotExposeTaskBlockCounters(
                verifyEvents("datadog.WallClockSamplingEpoch"));
        assertTrue(
                getRecordedCounterValue("task_block_emitted") > 0,
                "task_block_emitted must be reported as a ProfilerCounter");
    }

    @Test
    public void tracedPlatformParkDoesNotEmitTaskBlock() {
        registerCurrentThreadForWallClockProfiling();
        profiler.setContext(0x3100L, 0x3101L, 0L, 0x3101L);
        try {
            ProfilerOwnedBlockHooks.parkEnter(profiler);
            try {
                LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(200));
            } finally {
                ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
            }
        } finally {
            profiler.clearContext();
        }

        stopProfiler();

        assertFalse(
                verifyEvents("datadog.TaskBlock", false).hasItems(),
                "Traced park interval must keep MethodSample wall-clock data instead of emitting TaskBlock");
        assertTrue(
                getRecordedCounterValue("task_block_skipped_trace_context") > 0,
                "task_block_skipped_trace_context must be reported as a ProfilerCounter");
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
    }

    protected void assertTaskBlockStackReference(IItemCollection taskBlockEvents) {
        TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
    }
}
