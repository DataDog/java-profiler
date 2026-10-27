/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.ContinuationStackChecks;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.chaos.VirtualThreadRemountAntagonist;
import com.datadoghq.profiler.junit.CStack;
import java.time.Duration;
import java.util.HashSet;
import java.util.Set;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.assertAll;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Checks CPU and wall-clock stack correctness while a shared chaos workload repeatedly remounts. */
public class VirtualThreadCarrierChaosTest extends CStackAwareAbstractProfilerTest {
    private final boolean carrierFrames;

    /** Selects carrier walking or the ordinary VM-mode control. */
    public VirtualThreadCarrierChaosTest(@CStack String cstack) {
        super(cstack);
        carrierFrames = "vmx".equals(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isJavaVersionAtLeast(21) && !Platform.isJ9() && !Platform.isZing()
                && !(isInCI() && Platform.isMusl() && !Platform.isAarch64());
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=2ms,wall=2ms,walltpt=64,filter=,jstackdepth=512";
    }

    /** Requires exercised return barriers and checks both layouts in each sampling engine. */
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void retainsCarrierAncestryDuringRepeatedRemounts() throws Exception {
        String seconds = System.getenv("DDPROF_VTHREAD_STRESS_SECONDS");
        long duration = seconds == null ? 6 : Long.parseLong(seconds);
        assertTrue(duration >= 2 && duration <= 3600, "Stress duration must be 2..3600 seconds");
        waitForProfilerReady(2_000);
        VirtualThreadRemountAntagonist workload = new VirtualThreadRemountAntagonist();
        try {
            workload.start();
            Thread.sleep(duration * 1000);
        } finally {
            try {
                workload.stopGracefully(Duration.ofSeconds(10));
            } finally {
                stopProfiler();
            }
        }
        assertTrue(workload.registerCycles() >= 10, "Register-argument workers made insufficient progress");
        assertTrue(workload.stackCycles() >= 10, "Stack-argument workers made insufficient progress");
        assertTrue(profiler.getDebugCounters().getOrDefault("walkvm_cont_barrier_hit", 0L) >= 20,
                "The stress run must sample continuation return barriers");
        verifyCStackSettings();
        Set<Long> carriers = reduceEvents("datadog.ExecutionSample", HashSet::new, ContinuationStackChecks::collectCarriers);
        carriers.addAll(reduceEvents("datadog.MethodSample", HashSet::new, ContinuationStackChecks::collectCarriers));
        assertAll(
                () -> assertStacks("datadog.ExecutionSample", carriers),
                () -> assertStacks("datadog.MethodSample", carriers));
    }

    /** Checks both engines against the same carriers without retaining every sampled stack. */
    private void assertStacks(String eventType, Set<Long> carriers) {
        ContinuationStackChecks counts = reduceEvents(eventType,
                () -> new ContinuationStackChecks(carrierFrames, carriers), ContinuationStackChecks::accept);
        System.out.println(eventType + " carrier=" + carrierFrames + " " + counts);
        counts.assertValid(eventType);
    }
}
