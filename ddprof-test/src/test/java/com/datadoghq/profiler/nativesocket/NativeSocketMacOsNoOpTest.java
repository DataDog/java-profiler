/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * On macOS the nativesocket feature is a no-op stub.
 * Verifies that the profiler starts without error when 'nativesocket' is specified
 * and that no NativeSocketEvent events appear in the recording.
 */
public class NativeSocketMacOsNoOpTest extends NativeSocketTestBase {

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isMac();
    }

    @Override
    protected String getProfilerCommand() {
        return "natsock";
    }

    @RetryingTest(3)
    public void noEventsOnMacOS() throws Exception {
        Assumptions.assumeTrue(Platform.isMac(), "This test targets macOS no-op behaviour");

        String status = profiler.getStatus();
        assertTrue(status.contains("Running          : true"),
                "Profiler should be running after start with nativesocket on macOS; status: " + status);

        doTcpTransfer(32 * 1024, 8);

        stopProfiler();

        JfrEvents events = verifyEvents("datadog.NativeSocketEvent", false);
        assertNotNull(events);
        assertFalse(events.hasItems(),
                "NativeSocketEvent must not be emitted on macOS (no-op stub)");
    }
}
