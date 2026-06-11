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
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.ADDRESS;

/**
 * Smoke tests for native memory (malloc) profiling.
 *
 * <p>Runs with {@code cstack=vm}, {@code cstack=vmx}, {@code cstack=dwarf}, and
 * {@code cstack=fp}. All modes produce usable Java stacks for malloc events:
 * vm/vmx seed from {@code callerPC()}/{@code JavaFrameAnchor} via
 * {@code HotspotSupport::walkVM}; dwarf/fp hand a {@code NULL ucontext} to
 * {@code AsyncGetCallTrace}, which falls back to the JavaFrameAnchor populated
 * by the Java → native transition.
 */
public class NativememProfilerTest extends CStackAwareAbstractProfilerTest {

    private static final IAttribute<IQuantity> MALLOC_ADDRESS = attr("address", "address", "", ADDRESS);

    @BeforeAll
    static void preloadNativeLib() {
        // Ensure libddproftest.so is loaded before the profiler starts in @BeforeEach.
        // patchLibraries() only patches libraries already in native_libs at call time;
        // if the library loads after start() via dlopen_hook, glibc JVMs may not forward
        // the System.loadLibrary dlopen through the patched GOT entry.
        NativeAllocHelper.nativeMalloc(0, 0);
    }

    public NativememProfilerTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected String getProfilerCommand() {
        return "nativemem=0"; // sample every allocation
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isJ9() && !Platform.isZing();
    }

    @RetryTest(3)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "dwarf", "fp"})
    public void shouldRecordMallocSamples() throws InterruptedException {
        // GOT patching conflicts with ASan/TSan interceptors: both replace malloc/free
        // symbols, causing undefined behavior or crashes when hooks chain into each other.
        Assumptions.assumeFalse(isAsan() || isTsan());

        triggerAllocations(1000);

        stopProfiler();

        IItemCollection events = verifyEvents("profiler.Malloc");
        boolean foundMinSize = false;
        for (IItemIterable items : events) {
            IMemberAccessor<IQuantity, IItem> sizeAccessor = SIZE.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> weightAccessor = WEIGHT.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> addrAccessor = MALLOC_ADDRESS.getAccessor(items.getType());
            if (sizeAccessor == null) {
                continue;
            }
            assertNotNull(addrAccessor, "profiler.Malloc events must carry an address field");
            assertNotNull(weightAccessor, "profiler.Malloc events must carry a weight field");
            for (IItem item : items) {
                IQuantity size = sizeAccessor.getMember(item);
                assertNotNull(size, "profiler.Malloc event must have a non-null size field");
                assertTrue(size.longValue() > 0, "allocation size must be positive");
                if (size.longValue() >= 1024) {
                    foundMinSize = true;
                }
                IQuantity addr = addrAccessor.getMember(item);
                assertTrue(addr == null || addr.longValue() != 0, "malloc address must not be zero");
                // nativemem=0 samples every allocation; weight must be exactly 1.0.
                IQuantity weight = weightAccessor.getMember(item);
                assertNotNull(weight, "profiler.Malloc event must have a non-null weight field");
                assertTrue(Math.abs(weight.doubleValue() - 1.0) < 1e-6,
                    "weight must be 1.0 for nativemem=0 (all allocations sampled), got " + weight.doubleValue());
            }
        }
        assertTrue(foundMinSize, "expected at least one malloc event with size >= 1024 bytes");

        // triggerAllocations is a Java wrapper so it appears in all cstack modes, including fp/dwarf.
        verifyStackTraces("profiler.Malloc", "triggerAllocations", "shouldRecordMallocSamples");
    }

    private static void triggerAllocations(int count) {
        NativeAllocHelper.nativeMalloc(1024, count);
    }

}
