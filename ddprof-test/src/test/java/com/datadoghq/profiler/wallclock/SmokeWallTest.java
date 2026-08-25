/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.cpu.ProfiledCode;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;
import com.datadoghq.profiler.JfrEvents;

import java.util.concurrent.ExecutionException;

import static org.junit.jupiter.api.Assumptions.assumeFalse;

public class SmokeWallTest extends CStackAwareAbstractProfilerTest {
    private ProfiledCode profiledCode;

    public SmokeWallTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected void before() {
        profiledCode = new ProfiledCode(profiler);
    }

    @RetryTest(10)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void test(@CStack String cstack) throws ExecutionException, InterruptedException {
        for (int i = 0, id = 1; i < 100; i++, id += 3) {
            profiledCode.method1(id);
        }
        stopProfiler();

        verifyCStackSettings();

        JfrEvents events = verifyEvents("datadog.MethodSample");
    }

    @Override
    protected void after() throws Exception {
        profiledCode.close();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms";
    }
}
