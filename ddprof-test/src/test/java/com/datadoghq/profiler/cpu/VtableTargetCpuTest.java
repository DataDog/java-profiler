/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies vtable-target pre-registration: when vtable_target is enabled,
 * CPU samples taken at vtable/itable dispatch stubs should carry a synthetic
 * BCI_ALLOC frame whose class name matches the polymorphic receiver type.
 *
 * TODO (PROF-14618 follow-up): two blockers prevent enabling this test:
 *   1. vtable_target has no command-line argument; needs a "features=vtable_target"
 *      (or equivalent) toggle wired through Arguments::parse().
 *   2. The current STACK_TRACE_STRING-based assertion is wrong: vtable_target
 *      emits the receiver class as a synthetic BCI_ALLOC frame whose label is
 *      stored as the class-id, not as text in the stack trace string. When
 *      enabling, replace the trace.contains(...) check with a scan over each
 *      ExecutionSample's stack-frame items looking for a BCI_ALLOC frame whose
 *      class label matches the receiver type.
 */
@Disabled("PROF-14618 follow-up: nail down assertion shape — vtable_target has no CLI toggle yet")
public class VtableTargetCpuTest extends AbstractProfilerTest {

    // Two concrete receiver types to force polymorphic vtable dispatch.
    interface Workload {
        long compute(long seed);
    }

    static final class WorkloadA implements Workload {
        @Override
        public long compute(long seed) {
            long x = seed;
            for (int i = 0; i < 1_000; i++) {
                x = x * 6364136223846793005L + 1442695040888963407L;
            }
            return x;
        }
    }

    static final class WorkloadB implements Workload {
        @Override
        public long compute(long seed) {
            long x = seed;
            for (int i = 0; i < 1_000; i++) {
                x = x * 2862933555777941757L + 3037000493L;
            }
            return x;
        }
    }

    @Test
    public void vtableStubReceiverClassAppearsInSamples() throws Exception {
        Workload a = new WorkloadA();
        Workload b = new WorkloadB();

        // Drive polymorphic dispatch for ~3 s so the JIT compiles the call site
        // as a vtable stub and the profiler collects CPU samples inside it.
        long result = 0;
        long deadline = System.currentTimeMillis() + 3_000;
        while (System.currentTimeMillis() < deadline) {
            result += a.compute(result);
            result += b.compute(result);
        }
        // Prevent dead-code elimination.
        if (result == 0) {
            throw new AssertionError("unreachable");
        }

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.ExecutionSample");

        // At least one sample must contain a synthetic frame whose label
        // includes the receiver class simple name.  The label is recorded as
        // the "allocated class" name (BCI_ALLOC frame) for vtable-stub samples.
        boolean foundVtableFrame = false;
        for (IItemIterable cpuSamples : events) {
            IMemberAccessor<String, IItem> frameAccessor =
                    JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
            for (IItem sample : cpuSamples) {
                String trace = frameAccessor.getMember(sample);
                if (trace != null && (trace.contains("WorkloadA") || trace.contains("WorkloadB"))) {
                    foundVtableFrame = true;
                    break;
                }
            }
            if (foundVtableFrame) break;
        }

        assertTrue(foundVtableFrame,
                "Expected at least one CPU sample with a vtable-stub receiver frame " +
                "(WorkloadA or WorkloadB) but none were found");
    }

    @Override
    protected String getProfilerCommand() {
        // TODO (PROF-14618): replace with "cpu=10ms,features=vtable_target" once
        // Arguments::parse() supports the vtable_target flag.
        return "cpu=10ms";
    }
}
