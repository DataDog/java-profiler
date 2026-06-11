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
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Covers the sampled path of the native memory profiler (interval &gt; 1), which
 * exercises the Poisson interval generator, PID controller update, and the
 * {@code 1 / (1 - exp(-size/interval))} weight formula. The smoke test class
 * {@link NativememProfilerTest} only covers {@code nativemem=0}, which bypasses
 * these code paths via the {@code _interval <= 1} fast path.
 */
public class NativememSampledProfilerTest extends CStackAwareAbstractProfilerTest {

    @BeforeAll
    static void preloadNativeLib() {
        // Same as NativememProfilerTest: load libddproftest.so before the profiler starts
        // so patchLibraries() finds it in native_libs and patches its malloc GOT entry.
        NativeAllocHelper.nativeMalloc(0, 0);
    }

    public NativememSampledProfilerTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected String getProfilerCommand() {
        return "nativemem=512";
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isJ9() && !Platform.isZing();
    }

    @RetryTest(3)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "dwarf", "fp"})
    public void shouldEmitWeightedMallocSamples() throws InterruptedException {
        // GOT patching conflicts with ASan/TSan interceptors.
        Assumptions.assumeFalse(isAsan() || isTsan());

        // Drive enough allocation volume through malloc to yield several Poisson samples.
        triggerAllocations(20_000);

        stopProfiler();

        IItemCollection events = verifyEvents("profiler.Malloc");
        int sampleCount = 0;
        for (IItemIterable items : events) {
            IMemberAccessor<IQuantity, IItem> sizeAccessor = SIZE.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> weightAccessor = WEIGHT.getAccessor(items.getType());
            assertNotNull(sizeAccessor, "profiler.Malloc events must carry a size field");
            assertNotNull(weightAccessor, "profiler.Malloc events must carry a weight field");
            for (IItem item : items) {
                IQuantity size = sizeAccessor.getMember(item);
                IQuantity weight = weightAccessor.getMember(item);
                assertNotNull(size, "profiler.Malloc event must have a non-null size field");
                assertNotNull(weight, "profiler.Malloc event must have a non-null weight field");
                // Weight is 1 / (1 - exp(-size/interval)); that function is strictly > 1
                // for all positive sizes, so any Poisson-sampled event must carry weight >= 1.
                assertTrue(weight.doubleValue() >= 1.0,
                    "weight must be >= 1.0 on the sampled path, got " + weight.doubleValue()
                    + " (size=" + size.longValue() + ")");
                sampleCount++;
            }
        }

        // With ~20M bytes allocated and a 512-byte interval we expect plenty of samples.
        // The assertion is loose to tolerate CI variance but tight enough to catch
        // regressions where the sampling path silently produces zero events.
        assertTrue(sampleCount >= 8,
            "expected at least 8 sampled malloc events, got " + sampleCount);
    }

    private static void triggerAllocations(int count) {
        NativeAllocHelper.nativeMalloc(1024, count);
    }
}
