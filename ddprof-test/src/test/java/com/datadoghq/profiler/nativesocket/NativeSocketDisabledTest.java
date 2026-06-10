package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItemCollection;

import static org.junit.jupiter.api.Assertions.assertFalse;

/**
 * Verifies that NativeSocketEvent events are absent when the 'nativesocket'
 * profiler argument is not specified.
 */
public class NativeSocketDisabledTest extends NativeSocketTestBase {

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux();
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }

    @RetryingTest(3)
    public void noSocketEventsWithoutFeatureEnabled() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        doTcpTransfer(64 * 1024, 8);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent", false);
        assertFalse(events.hasItems(),
                "NativeSocketEvent events must not appear when nativesocket argument is absent");
    }
}
