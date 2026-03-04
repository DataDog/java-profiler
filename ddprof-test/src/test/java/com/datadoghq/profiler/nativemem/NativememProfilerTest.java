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
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.ADDRESS;

/**
 * Smoke tests for native memory (malloc/free) profiling.
 *
 * <p>Runs with {@code cstack=vm} and {@code cstack=vmx}. In {@code vmx} mode the
 * stack trace is expected to contain {@code allocateDirect} because the mixed-mode
 * walker captures the Java call chain that triggered the native allocation.
 */
public class NativememProfilerTest extends CStackAwareAbstractProfilerTest {

    private static final IAttribute<IQuantity> MALLOC_ADDRESS = attr("address", "address", "", ADDRESS);

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
    @ValueSource(strings = {"vm", "vmx"})
    public void shouldRecordMallocSamples() throws InterruptedException {
        Assumptions.assumeFalse(isAsan() || isTsan());

        List<ByteBuffer> buffers = new ArrayList<>();
        for (int i = 0; i < 1000; i++) {
            buffers.add(ByteBuffer.allocateDirect(1024));
        }

        stopProfiler();

        IItemCollection events = verifyEvents("profiler.Malloc");
        boolean foundMinSize = false;
        for (IItemIterable items : events) {
            IMemberAccessor<IQuantity, IItem> sizeAccessor = SIZE.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> addrAccessor = MALLOC_ADDRESS.getAccessor(items.getType());
            if (sizeAccessor == null) {
                continue;
            }
            for (IItem item : items) {
                IQuantity size = sizeAccessor.getMember(item);
                assertTrue(size == null || size.longValue() > 0, "allocation size must be positive");
                if (size != null && size.longValue() >= 1024) {
                    foundMinSize = true;
                }
                if (addrAccessor != null) {
                    IQuantity addr = addrAccessor.getMember(item);
                    assertTrue(addr == null || addr.longValue() != 0, "malloc address must not be zero");
                }
            }
        }
        assertTrue(foundMinSize, "expected at least one malloc event with size >= 1024 bytes");

        // Both vm and vmx capture the Java call chain; allocateDirect must appear in stack traces
        verifyStackTraces("profiler.Malloc", "allocateDirect");

        buffers.clear(); // keep alive until after stop
    }

    @RetryTest(3)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx"})
    public void shouldRecordFreeEvents() throws InterruptedException {
        Assumptions.assumeFalse(isAsan() || isTsan());

        // Allocate and immediately abandon so the GC Cleaner will call free()
        for (int i = 0; i < 1000; i++) {
            ByteBuffer.allocateDirect(1024);
        }
        for (int attempt = 0; attempt < 5; attempt++) {
            System.gc();
            Thread.sleep(200);
        }

        stopProfiler();

        IItemCollection mallocEvents = verifyEvents("profiler.Malloc");
        IItemCollection freeEvents = verifyEvents("profiler.Free");

        // Collect all recorded malloc addresses
        Set<Long> mallocAddresses = new HashSet<>();
        for (IItemIterable items : mallocEvents) {
            IMemberAccessor<IQuantity, IItem> addrAccessor = MALLOC_ADDRESS.getAccessor(items.getType());
            if (addrAccessor == null) {
                continue;
            }
            for (IItem item : items) {
                IQuantity addr = addrAccessor.getMember(item);
                if (addr != null) {
                    mallocAddresses.add(addr.longValue());
                }
            }
        }

        // At least one free event address must match a previously recorded malloc address
        boolean foundCorrelation = false;
        outer:
        for (IItemIterable items : freeEvents) {
            IMemberAccessor<IQuantity, IItem> addrAccessor = MALLOC_ADDRESS.getAccessor(items.getType());
            if (addrAccessor == null) {
                continue;
            }
            for (IItem item : items) {
                IQuantity addr = addrAccessor.getMember(item);
                if (addr != null && mallocAddresses.contains(addr.longValue())) {
                    foundCorrelation = true;
                    break outer;
                }
            }
        }
        assertTrue(foundCorrelation, "expected at least one free event whose address matches a recorded malloc");
    }
}
