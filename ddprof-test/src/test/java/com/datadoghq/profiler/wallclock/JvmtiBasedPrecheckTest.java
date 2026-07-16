/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;

import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Runs the wallprecheck regression suite through HotSpot's delegated
 * RequestStackTrace wall-clock engine.
 */
public class JvmtiBasedPrecheckTest extends PrecheckTest {
    private boolean jvmtiDelegationAvailable;
    private long requestedBefore;

    @Override
    protected void before() throws Exception {
        Map<String, Long> counters = profiler.getDebugCounters();
        Assumptions.assumeTrue(
                counters.getOrDefault("jvmti_stacks_init_ok", 0L) > 0,
                "HotSpot RequestStackTrace JVMTI extension is not available");
        jvmtiDelegationAvailable = true;
        requestedBefore = counters.getOrDefault("jvmti_stacks_requested", 0L);
    }

    @Override
    protected void after() throws Exception {
        if (!jvmtiDelegationAvailable) {
            return;
        }
        long requestedAfter = profiler.getDebugCounters()
                .getOrDefault("jvmti_stacks_requested", 0L);
        assertTrue(
                requestedAfter > requestedBefore,
                "Expected wallclock jvmtistacks path to request delegated stack traces");
    }

    @Override
    protected boolean isPlatformSupported() {
        return !Platform.isJ9();
    }

    @Override
    protected void withTestAssumptions() {
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,wallscope=all,wallprecheck=true,jvmtistacks=true";
    }

    @Override
    protected String getPrecheckDisabledProfilerCommand() {
        return "wall=1ms,wallscope=all,wallprecheck=false,jvmtistacks=true";
    }
}
