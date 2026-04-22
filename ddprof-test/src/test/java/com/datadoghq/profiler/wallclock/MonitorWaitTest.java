package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.context.Tracing;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Attribute;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicLong;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;

/**
 * Verifies the JVMTI MonitorWait/MonitorWaited callback implementation for JDK 8-20.
 *
 * These callbacks emit datadog.TaskBlock JFR events when a thread with an active span
 * calls Object.wait() for longer than 1 ms. On JDK 21+, the BCI instrumentation handles
 * this instead, so the JVMTI path is skipped on those versions.
 *
 * Addendum C: when a notifier thread still holds the monitor when the waiting thread
 * re-acquires it (MonitorContendedEnter fires), the notifier's span ID is captured
 * as unblockingSpanId in the TaskBlock event.
 */
public class MonitorWaitTest extends AbstractProfilerTest {

    private static final IAttribute<IQuantity> UNBLOCKING_SPAN_ID =
            Attribute.attr("unblockingSpanId", "unblockingSpanId", "Unblocking Span ID", NUMBER);

    private static final long WAIT_DURATION_MS = 100;

    // -------------------------------------------------------------------------
    // Test 1: basic emission — waiting thread with active span emits TaskBlock
    // -------------------------------------------------------------------------

    @Test
    public void testWaitWithSpanEmitsTaskBlock() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());

        final Object monitor = new Object();
        final AtomicLong capturedSpanId = new AtomicLong();
        final AtomicLong capturedRootSpanId = new AtomicLong();
        final CountDownLatch waitStarted = new CountDownLatch(1);
        final CountDownLatch notified = new CountDownLatch(1);

        // Thread A: waits on the monitor with an active span.
        Thread waiter = new Thread(() -> {
            try (Tracing.Context ctx = Tracing.newContext(() -> 0xAAAABBBBL, profiler)) {
                capturedSpanId.set(ctx.getSpanId());
                capturedRootSpanId.set(ctx.getRootSpanId());
                synchronized (monitor) {
                    waitStarted.countDown();
                    monitor.wait(WAIT_DURATION_MS * 3);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        // Thread B: notifies after waiting thread is parked.
        Thread notifier = new Thread(() -> {
            try {
                waitStarted.await();
                Thread.sleep(WAIT_DURATION_MS);
                synchronized (monitor) {
                    monitor.notifyAll();
                }
                notified.countDown();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        waiter.start();
        notifier.start();
        waiter.join(5_000);
        notifier.join(5_000);
        stopProfiler();

        long spanId = capturedSpanId.get();
        long rootSpanId = capturedRootSpanId.get();

        IItemCollection blocks = verifyEvents("datadog.TaskBlock");
        assertTrue(blocks.hasItems(), "Expected at least one datadog.TaskBlock event");

        boolean foundMatchingBlock = false;
        for (IItemIterable items : blocks) {
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(items.getType());
            if (spanIdAccessor == null) continue;
            for (IItem item : items) {
                if (spanIdAccessor.getMember(item).longValue() == spanId
                        && rootSpanIdAccessor.getMember(item).longValue() == rootSpanId) {
                    foundMatchingBlock = true;
                }
            }
        }
        assertTrue(foundMatchingBlock,
                "No TaskBlock event matched spanId=" + spanId + " rootSpanId=" + rootSpanId);
    }

    // -------------------------------------------------------------------------
    // Test 2: duration filter — wait below 1 ms threshold emits no TaskBlock
    // -------------------------------------------------------------------------

    @Test
    public void testWaitBelowThresholdEmitsNoTaskBlock() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());

        final Object monitor = new Object();

        try (Tracing.Context ctx = Tracing.newContext(() -> 0xCCCCDDDDL, profiler)) {
            synchronized (monitor) {
                // wait(1) — 1 ms timeout, well below the 1 ms minimum duration filter
                // (the actual wait will be even shorter than 1 ms in practice).
                monitor.wait(1);
            }
        }

        stopProfiler();

        IItemCollection blocks = verifyEvents("datadog.TaskBlock", false);
        assertFalse(blocks.hasItems(),
                "Expected no TaskBlock event for a sub-threshold Object.wait()");
    }

    // -------------------------------------------------------------------------
    // Test 3: no span — wait without active span emits no TaskBlock
    // -------------------------------------------------------------------------

    @Test
    public void testWaitWithoutSpanEmitsNoTaskBlock() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());

        final Object monitor = new Object();
        final CountDownLatch waitStarted = new CountDownLatch(1);

        Thread waiter = new Thread(() -> {
            // No Tracing.Context — spanId is 0; callback must be a no-op.
            synchronized (monitor) {
                try {
                    waitStarted.countDown();
                    monitor.wait(WAIT_DURATION_MS * 2);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        });

        Thread notifier = new Thread(() -> {
            try {
                waitStarted.await();
                Thread.sleep(WAIT_DURATION_MS);
                synchronized (monitor) {
                    monitor.notifyAll();
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        waiter.start();
        notifier.start();
        waiter.join(5_000);
        notifier.join(5_000);
        stopProfiler();

        IItemCollection blocks = verifyEvents("datadog.TaskBlock", false);
        assertFalse(blocks.hasItems(),
                "Expected no TaskBlock event when Object.wait() is called without an active span");
    }

    // -------------------------------------------------------------------------
    // Test 4 (Addendum C): notifier holds lock after notify — unblockingSpanId captured
    // -------------------------------------------------------------------------

    @Test
    public void testUnblockingSpanIdCapturedWhenNotifierHoldsLock() throws InterruptedException {
        // Addendum C uses MonitorContendedEnter, which is only wired on JDK < 21 (JVMTI path).
        // On JDK 21+ the BCI path always emits unblockingSpanId = 0 (notify is native).
        Assumptions.assumeTrue(!Platform.isJ9() && !Platform.isJavaVersionAtLeast(21));

        final Object monitor = new Object();
        final AtomicLong waiterSpanId = new AtomicLong();
        final AtomicLong notifierSpanId = new AtomicLong();
        final CountDownLatch waitStarted = new CountDownLatch(1);

        Thread waiter = new Thread(() -> {
            try (Tracing.Context ctx = Tracing.newContext(() -> 0x1111_2222L, profiler)) {
                waiterSpanId.set(ctx.getSpanId());
                synchronized (monitor) {
                    waitStarted.countDown();
                    monitor.wait(WAIT_DURATION_MS * 5);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        Thread notifier = new Thread(() -> {
            try {
                waitStarted.await();
                Thread.sleep(WAIT_DURATION_MS);
                // Notifier holds the lock for 50 ms after notify() so that when the waiter
                // tries to re-acquire (MonitorContendedEnter fires), the notifier is still
                // the owner — Addendum C can then capture notifierSpanId as unblockingSpanId.
                try (Tracing.Context ctx = Tracing.newContext(() -> 0x3333_4444L, profiler)) {
                    notifierSpanId.set(ctx.getSpanId());
                    synchronized (monitor) {
                        monitor.notifyAll();
                        Thread.sleep(50); // keep holding the lock after notify
                    }
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        waiter.start();
        notifier.start();
        waiter.join(5_000);
        notifier.join(5_000);
        stopProfiler();

        long spanId = waiterSpanId.get();
        long expectedUnblocking = notifierSpanId.get();

        IItemCollection blocks = verifyEvents("datadog.TaskBlock");
        assertTrue(blocks.hasItems(), "Expected at least one datadog.TaskBlock event");

        boolean foundWithUnblocking = false;
        for (IItemIterable items : blocks) {
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> unblockingAccessor = UNBLOCKING_SPAN_ID.getAccessor(items.getType());
            if (spanIdAccessor == null || unblockingAccessor == null) continue;
            for (IItem item : items) {
                if (spanIdAccessor.getMember(item).longValue() == spanId) {
                    long unblocking = unblockingAccessor.getMember(item).longValue();
                    if (unblocking == expectedUnblocking) {
                        foundWithUnblocking = true;
                    }
                }
            }
        }
        assertTrue(foundWithUnblocking,
                "Expected a TaskBlock event for waiter span " + spanId
                        + " with unblockingSpanId=" + expectedUnblocking
                        + " (notifier held lock after notify — Addendum C capture)");
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms";
    }
}
