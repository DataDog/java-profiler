package com.datadoghq.profiler.nativesocket;

import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItemCollection;

import com.datadoghq.profiler.Platform;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies that the 'nativesocket' profiler argument enables socket I/O tracking
 * and that NativeSocketEvent JFR events are produced.
 */
public class NativeSocketEnabledTest extends NativeSocketTestBase {

    @RetryingTest(3)
    public void socketEventsProducedWhenFeatureEnabled() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        doTcpTransfer(4096, 128);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        assertTrue(events.hasItems(), "Expected NativeSocketEvent events to be present in JFR recording");
    }
}
