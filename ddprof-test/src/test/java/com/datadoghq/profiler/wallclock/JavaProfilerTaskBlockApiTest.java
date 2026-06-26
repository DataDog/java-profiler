package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class JavaProfilerTaskBlockApiTest extends AbstractProfilerTest {
    private static final int OSTHREAD_STATE_SLEEPING = 7;
    private static final long ROOT_SPAN_ID = 0L;
    private static final long SPAN_ID = 0L;
    private static final long BLOCKER = 0x7301L;
    private static final long UNBLOCKING_SPAN_ID = 0x7302L;

    @Test
    public void recordTaskBlockSameThreadEligibleEmission() throws Exception {
        assertTrue(runInsideCurrentThreadBlock(
                (tid, startTicks, endTicks, snapshot) ->
                        profiler.recordTaskBlock(startTicks, endTicks, BLOCKER, UNBLOCKING_SPAN_ID)));
        stopProfiler();

        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
        TaskBlockAssertions.assertContains(
                taskBlockEvents, ROOT_SPAN_ID, SPAN_ID, BLOCKER, UNBLOCKING_SPAN_ID);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "SLEEPING");
    }

    @Test
    public void recordTaskBlockTooShortSkipsAndCounts() throws Exception {
        assertFalse(runInsideRegisteredThread(() -> {
            long ticks = profiler.getCurrentTicks();
            return profiler.recordTaskBlock(ticks, ticks, BLOCKER, UNBLOCKING_SPAN_ID);
        }));
        stopProfiler();

        assertFalse(verifyEvents("datadog.TaskBlock", false).hasItems());
        assertTrue(getRecordedCounterValue("task_block_skipped_too_short") > 0);
    }

    @Test
    public void recordTaskBlockWithExplicitZeroContextEmitsExpectedFields() throws Exception {
        assertTrue(runInsideCurrentThreadBlock(
                (tid, startTicks, endTicks, snapshot) ->
                        profiler.recordTaskBlockWithContext(
                                startTicks, endTicks, BLOCKER, UNBLOCKING_SPAN_ID,
                                SPAN_ID, ROOT_SPAN_ID)));
        stopProfiler();

        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertContains(
                taskBlockEvents, ROOT_SPAN_ID, SPAN_ID, BLOCKER, UNBLOCKING_SPAN_ID);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "SLEEPING");
    }

    @Test
    public void recordTaskBlockWithNonZeroSpanContextSkipsAndCounts() throws Exception {
        assertFalse(runInsideCurrentThreadBlock(
                (tid, startTicks, endTicks, snapshot) ->
                        profiler.recordTaskBlockWithContext(
                                startTicks, endTicks, BLOCKER, UNBLOCKING_SPAN_ID,
                                0x7310L, 0x7311L)));
        stopProfiler();

        assertFalse(verifyEvents("datadog.TaskBlock", false).hasItems());
        assertTrue(getRecordedCounterValue("task_block_skipped_trace_context") > 0);
    }

    @Test
    public void recordTaskBlockFromContextWithoutStackReferenceSkipsAndCounts() throws Exception {
        CapturedBlock block = captureCurrentThreadBlock();

        assertFalse(profiler.recordTaskBlockFromContext(
                block.tid, block.startTicks, block.endTicks, BLOCKER, UNBLOCKING_SPAN_ID,
                SPAN_ID, ROOT_SPAN_ID));
        stopProfiler();

        assertFalse(verifyEvents("datadog.TaskBlock", false).hasItems());
        assertTrue(getRecordedCounterValue("task_block_skipped_no_stack_reference") > 0);
    }

    @Test
    public void recordTaskBlockFromContextWithExplicitStackReferencePreservesObservedState()
            throws Exception {
        CapturedBlock block = captureCurrentThreadBlock();

        assertTrue(profiler.recordTaskBlockFromContext(
                block.tid, block.startTicks, block.endTicks, BLOCKER, UNBLOCKING_SPAN_ID,
                SPAN_ID, ROOT_SPAN_ID, block.snapshot[0], block.snapshot[1],
                (int) block.snapshot[2]));
        stopProfiler();

        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertContains(
                taskBlockEvents, ROOT_SPAN_ID, SPAN_ID, BLOCKER, UNBLOCKING_SPAN_ID);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "SLEEPING");
    }

    @Test
    public void recordTaskBlockFromContextInvalidObservedStateStillEmitsWithFallbackState()
            throws Exception {
        CapturedBlock block = captureCurrentThreadBlock();

        assertTrue(profiler.recordTaskBlockFromContext(
                block.tid, block.startTicks, block.endTicks, BLOCKER, UNBLOCKING_SPAN_ID,
                SPAN_ID, ROOT_SPAN_ID, block.snapshot[0], block.snapshot[1], Integer.MAX_VALUE));
        stopProfiler();

        IItemCollection taskBlockEvents = verifyEvents("datadog.TaskBlock");
        TaskBlockAssertions.assertContains(
                taskBlockEvents, ROOT_SPAN_ID, SPAN_ID, BLOCKER, UNBLOCKING_SPAN_ID);
        TaskBlockAssertions.assertContainsAnyObservedState(taskBlockEvents);
    }

    @Test
    public void recordTaskBlockFromContextInvalidTidReturnsFalseAndEmitsNothing() {
        long ticks = profiler.getCurrentTicks();
        long endTicks = ticks + profiler.getTscFrequency();

        assertFalse(profiler.recordTaskBlockFromContext(
                -1, ticks, endTicks, BLOCKER, UNBLOCKING_SPAN_ID, SPAN_ID, ROOT_SPAN_ID));
        assertFalse(profiler.recordTaskBlockFromContext(
                -1, ticks, endTicks, BLOCKER, UNBLOCKING_SPAN_ID, SPAN_ID, ROOT_SPAN_ID,
                1L, 2L, OSTHREAD_STATE_SLEEPING));
        stopProfiler();

        assertFalse(verifyEvents("datadog.TaskBlock", false).hasItems());
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
    }

    private CapturedBlock captureCurrentThreadBlock() throws Exception {
        AtomicReference<CapturedBlock> captured = new AtomicReference<>();
        runInsideCurrentThreadBlock(
                (tid, startTicks, endTicks, snapshot) -> {
                    captured.set(new CapturedBlock(tid, startTicks, endTicks, snapshot.clone()));
                    return true;
                });
        CapturedBlock block = captured.get();
        if (block == null) {
            throw new AssertionError("capture thread did not publish block metadata");
        }
        return block;
    }

    private boolean runInsideCurrentThreadBlock(BlockAction action) throws Exception {
        AtomicReference<Throwable> error = new AtomicReference<>();
        AtomicReference<Boolean> result = new AtomicReference<>();
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
                long token2 = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
                if (token2 == 0) {
                    throw new AssertionError("Expected native blockEnter to re-arm SLEEPING state");
                }
                try {
                    Thread.sleep(200L);
                    result.set(action.run(profiler.getCurrentThreadId(), startTicks, endTicks, snapshot));
                } finally {
                    ProfilerOwnedBlockHooks.blockExit(profiler, token2);
                }
            } catch (Throwable t) {
                error.set(t);
            }
        }, "taskblock-direct-api-capture");

        thread.start();
        thread.join(5_000L);
        assertFalse(thread.isAlive(), "capture thread did not complete");
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
        Boolean recorded = result.get();
        if (recorded == null) {
            throw new AssertionError("capture thread did not publish TaskBlock record result");
        }
        return recorded;
    }

    private boolean runInsideRegisteredThread(RegisteredThreadAction action) throws Exception {
        AtomicReference<Throwable> error = new AtomicReference<>();
        AtomicReference<Boolean> result = new AtomicReference<>();
        Thread thread = new Thread(() -> {
            try {
                registerCurrentThreadForWallClockProfiling();
                result.set(action.run());
            } catch (Throwable t) {
                error.set(t);
            }
        }, "taskblock-direct-api-registered");

        thread.start();
        thread.join(5_000L);
        assertFalse(thread.isAlive(), "registered thread did not complete");
        if (error.get() != null) {
            throw new AssertionError(error.get());
        }
        Boolean recorded = result.get();
        if (recorded == null) {
            throw new AssertionError("registered thread did not publish TaskBlock record result");
        }
        return recorded;
    }

    private interface BlockAction {
        boolean run(int tid, long startTicks, long endTicks, long[] snapshot);
    }

    private interface RegisteredThreadAction {
        boolean run();
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
