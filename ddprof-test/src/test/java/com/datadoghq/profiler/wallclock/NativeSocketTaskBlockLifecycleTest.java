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

public class NativeSocketTaskBlockLifecycleTest extends AbstractProfilerTest {
    private static final int NATIVE_WAKE_DELAY_MILLIS = 80;

    @BeforeAll
    static void preloadNativeHelper() {
        if (Platform.isLinux()) {
            NativeIoBlockHelper.blockingPpoll(0);
        }
    }

    @Test
    public void restartWithWallPrecheckDisabledStopsNativeSocketTaskBlocks() throws Exception {
        NativeIoBlockHelper.blockingPpoll(NATIVE_WAKE_DELAY_MILLIS);
        stopProfiler();
        assertIoWaitTaskBlockPresent(verifyEvents("datadog.TaskBlock"));

        Path disabledRecording = Files.createTempFile(Paths.get("/tmp/recordings"),
                "NativeSocketTaskBlockLifecycleTest_disabled_", ".jfr");
        try {
            profiler.execute("start,wall=1ms,filter=0,wallprecheck=false,jfr,file="
                    + disabledRecording.toAbsolutePath());
            NativeIoBlockHelper.blockingPpoll(NATIVE_WAKE_DELAY_MILLIS);
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
            NativeIoBlockHelper.blockingPpoll(NATIVE_WAKE_DELAY_MILLIS);
            profiler.stop();

            assertIoWaitTaskBlockPresent(verifyEvents(
                    reenabledRecording, "datadog.TaskBlock", true));
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

    private void assertIoWaitTaskBlockPresent(IItemCollection taskBlockEvents) {
        TaskBlockAssertions.assertNoAnchorFields(taskBlockEvents);
        TaskBlockAssertions.assertContainsStackTrace(taskBlockEvents);
        TaskBlockAssertions.assertContainsObservedState(taskBlockEvents, "IO_WAIT");
    }
}
