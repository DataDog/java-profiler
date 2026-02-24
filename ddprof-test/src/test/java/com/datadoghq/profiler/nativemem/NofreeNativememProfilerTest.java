/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;
import org.openjdk.jmc.common.item.IItemCollection;

import java.nio.ByteBuffer;

import static org.junit.jupiter.api.Assertions.assertFalse;

/**
 * Verifies that the {@code nofree} option suppresses {@code profiler.Free} events.
 */
public class NofreeNativememProfilerTest extends CStackAwareAbstractProfilerTest {

    public NofreeNativememProfilerTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected String getProfilerCommand() {
        return "nativemem=0,nofree";
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isJ9() && !Platform.isZing();
    }

    @RetryTest(3)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void shouldNotRecordFreeEventsWithNofreeOption(@CStack String cstack) throws InterruptedException {
        Assumptions.assumeFalse(isAsan() || isTsan());

        // Trigger allocations and then release them via GC
        for (int i = 0; i < 1000; i++) {
            ByteBuffer.allocateDirect(1024);
        }
        for (int attempt = 0; attempt < 5; attempt++) {
            System.gc();
            Thread.sleep(200);
        }

        stopProfiler();

        verifyEvents("profiler.Malloc");

        IItemCollection freeEvents = verifyEvents("profiler.Free", false);
        assertFalse(freeEvents.hasItems(), "profiler.Free events must not be recorded when nofree is set");
    }
}
