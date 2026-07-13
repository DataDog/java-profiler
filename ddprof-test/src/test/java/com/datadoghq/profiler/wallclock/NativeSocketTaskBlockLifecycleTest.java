/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class NativeSocketTaskBlockLifecycleTest extends AbstractProfilerTest {
    private static final int BLOCK_HOLD_MILLIS = 250;
    private static final int NATIVE_BLOCK_ATTEMPTS = 5;

    @BeforeAll
    static void preloadNativeHelper() {
        if (Platform.isLinux()) {
            NativeIoBlockHelper.blockingPpoll(0);
        }
    }

    @Test
    public void restartWithWallPrecheckDisabledStopsNativeSocketTaskBlocks() throws Exception {
        long enabledBlocker = runNativeIoBlock();
        stopProfiler();
        assertIoWaitTaskBlockPresent(verifyEvents("datadog.TaskBlock", false), enabledBlocker);

        Path disabledRecording = Files.createTempFile(Paths.get("/tmp/recordings"),
                "NativeSocketTaskBlockLifecycleTest_disabled_", ".jfr");
        try {
            profiler.execute("start,wall=1ms,filter=0,wallprecheck=false,jfr,file="
                    + disabledRecording.toAbsolutePath());
            runNativeIoBlock();
            profiler.stop();

            IItemCollection disabledTaskBlocks =
                    verifyEvents(disabledRecording, "datadog.TaskBlock", false);
            assertFalse(disabledTaskBlocks.hasItems(),
                    "wallprecheck=false restart must disable native socket TaskBlock emission");
        } finally {
            Files.deleteIfExists(disabledRecording);
        }

        Path reenabledRecording = Files.createTempFile(Paths.get("/tmp/recordings"),
                "NativeSocketTaskBlockLifecycleTest_reenabled_", ".jfr");
        try {
            profiler.execute("start,wall=1ms,filter=0,wallprecheck=true,jfr,file="
                    + reenabledRecording.toAbsolutePath());
            long reenabledBlocker = runNativeIoBlock();
            profiler.stop();

            assertIoWaitTaskBlockPresent(verifyEvents(
                    reenabledRecording, "datadog.TaskBlock", false), reenabledBlocker);
        } finally {
            Files.deleteIfExists(reenabledRecording);
        }
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isJ9() && !Platform.isZing();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
    }

    private void assertIoWaitTaskBlockPresent(IItemCollection taskBlockEvents, long expectedBlocker) {
        assertTrue(expectedBlocker != 0L, "native lifecycle helper must report the expected blocker");
        if (!taskBlockEvents.hasItems()) {
            assertTrue(false, missingTaskBlockDiagnostic());
        }
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "IO_WAIT");
        TaskBlockAssertions.assertContainsBlocker(taskBlockEvents, expectedBlocker);
    }

    private long runNativeIoBlock() {
        registerCurrentThreadForWallClockProfiling();
        long blocker = 0L;
        for (int attempt = 0; attempt < NATIVE_BLOCK_ATTEMPTS; attempt++) {
            blocker = NativeIoBlockHelper.blockingPpoll(BLOCK_HOLD_MILLIS);
        }
        return blocker;
    }

    private String missingTaskBlockDiagnostic() {
        return "Expected lifecycle native TaskBlock after " + NATIVE_BLOCK_ATTEMPTS
                + " blocked interval(s); emitted=" + getRecordedCounterValue("task_block_emitted")
                + ", skipped_no_stack_reference="
                + getRecordedCounterValue("task_block_skipped_no_stack_reference")
                + ", skipped_too_short=" + getRecordedCounterValue("task_block_skipped_too_short")
                + ", skipped_trace_context="
                + getRecordedCounterValue("task_block_skipped_trace_context")
                + ", record_failed=" + getRecordedCounterValue("task_block_record_failed")
                + ", queue_dropped=" + getRecordedCounterValue("task_block_queue_dropped");
    }
}
