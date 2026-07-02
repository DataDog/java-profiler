package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class DeferredTaskBlockTest extends AbstractProfilerTest {
    private static final int OSTHREAD_STATE_SLEEPING = 7;
    private static final long ROOT_SPAN_ID = 0x7001L;
    private static final long SPAN_ID = 0L;
    private static final long BLOCKER_WITHOUT_STACK = 0x7101L;
    private static final long BLOCKER_WITH_STACK = 0x7102L;
    private static final long UNBLOCKING_SPAN_ID = 0L;

    @Test
    public void offThreadRecordWithoutStackReferenceIsDroppedAndCounted() throws Exception {
        CapturedBlock block = captureSleepingBlock();

        assertFalse(profiler.recordTaskBlockFromContext(
                block.tid,
                block.startTicks,
                block.endTicks,
                BLOCKER_WITHOUT_STACK,
                UNBLOCKING_SPAN_ID,
                SPAN_ID,
                ROOT_SPAN_ID));

        stopProfiler();

        assertFalse(
                verifyEvents("datadog.TaskBlock", false).hasItems(),
                "off-thread TaskBlock without stack-reference metadata must not be emitted");
        assertTrue(
                getRecordedCounterValue("task_block_skipped_no_stack_reference") > 0,
                "missing stack-reference drops must be reported as ProfilerCounter");
    }

    @Test
    public void offThreadRecordWithExplicitStackReferenceEmitsTaskBlock() throws Exception {
        CapturedBlock block = captureSleepingBlock();

        assertTrue(profiler.recordTaskBlockFromContext(
                block.tid,
                block.startTicks,
                block.endTicks,
                BLOCKER_WITH_STACK,
                UNBLOCKING_SPAN_ID,
                SPAN_ID,
                ROOT_SPAN_ID,
                block.snapshot[0],
                block.snapshot[1],
                (int) block.snapshot[2]));

        stopProfiler();

        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
        TaskBlockAssertions.assertContains(
                taskBlockEvents, ROOT_SPAN_ID, SPAN_ID, BLOCKER_WITH_STACK, UNBLOCKING_SPAN_ID);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "SLEEPING");
        assertTrue(
                getRecordedCounterValue("task_block_emitted") > 0,
                "explicit-stack off-thread TaskBlock must be reported as emitted");
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
    }

    private CapturedBlock captureSleepingBlock() throws Exception {
        AtomicReference<CapturedBlock> captured = new AtomicReference<>();
        AtomicReference<Throwable> error = new AtomicReference<>();
        Thread thread = new Thread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
                if (token == 0) {
                    throw new AssertionError("Expected native blockEnter to arm SLEEPING state");
                }
                long startTicks = profiler.getCurrentTicks();
                Thread.sleep(200L);
                long endTicks = profiler.getCurrentTicks();
                long[] snapshot = new long[3];
                profiler.blockExit(token, snapshot);
                if (snapshot[0] == 0 && snapshot[1] == 0) {
                    throw new AssertionError("Expected non-zero stack-reference metadata");
                }
                captured.set(new CapturedBlock(
                        profiler.getCurrentThreadId(), startTicks, endTicks, snapshot));
            } catch (Throwable t) {
                error.set(t);
            }
        }, "deferred-taskblock-capture");

        thread.start();
        thread.join(5_000L);
        assertFalse(thread.isAlive(), "capture thread did not complete");
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
        CapturedBlock block = captured.get();
        if (block == null) {
            throw new AssertionError("capture thread did not publish block metadata");
        }
        return block;
    }

    private static final class CapturedBlock {
        private final int tid;
        private final long startTicks;
        private final long endTicks;
        private final long[] snapshot;

        private CapturedBlock(int tid, long startTicks, long endTicks, long[] snapshot) {
            this.tid = tid;
            this.startTicks = startTicks;
            this.endTicks = endTicks;
            this.snapshot = snapshot;
        }
    }
}
