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
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

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

    private static final String MALLOC_ADDRESS = "address";

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

        JfrEvents events = verifyEvents("datadog.NativeMemoryAllocation");
        boolean foundMinSize = false;
        for (JfrEvent item : events) {
            if (!item.has(SIZE)) {
                continue;
            }
            assertTrue(item.has(MALLOC_ADDRESS), "datadog.NativeMemoryAllocation events must carry an address field");
            assertTrue(item.has(WEIGHT), "datadog.NativeMemoryAllocation events must carry a weight field");
            Long size = item.getLong(SIZE);
            assertNotNull(size, "datadog.NativeMemoryAllocation event must have a non-null size field");
            assertTrue(size > 0, "allocation size must be positive");
            if (size >= 1024) {
                foundMinSize = true;
            }
            Long addr = item.getLong(MALLOC_ADDRESS);
            assertTrue(addr == null || addr != 0, "malloc address must not be zero");
            // nativemem=0 samples every allocation; weight must be exactly 1.0.
            Double weight = item.getDouble(WEIGHT);
            assertNotNull(weight, "datadog.NativeMemoryAllocation event must have a non-null weight field");
            assertTrue(Math.abs(weight - 1.0) < 1e-6,
                "weight must be 1.0 for nativemem=0 (all allocations sampled), got " + weight);
        }
        assertTrue(foundMinSize, "expected at least one malloc event with size >= 1024 bytes");

        // triggerAllocations is a Java wrapper so it appears in all cstack modes, including fp/dwarf.
        verifyStackTraces("datadog.NativeMemoryAllocation", "triggerAllocations", "shouldRecordMallocSamples");
    }

    private static void triggerAllocations(int count) {
        NativeAllocHelper.nativeMalloc(1024, count);
    }

}
