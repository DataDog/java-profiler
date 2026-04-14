package com.datadoghq.profiler.deadlock;

import com.datadoghq.profiler.AbstractProfilerTest;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.CountDownLatch;

import static org.junit.jupiter.api.Assertions.*;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.*;

public class DeadlockDetectionTest extends AbstractProfilerTest {

    private static final IAttribute<IQuantity> DEADLOCK_ID =
            attr("deadlockId", "deadlockId", "", NUMBER);
    private static final IAttribute<String> LOCK_NAME =
            attr("lockName", "lockName", "", PLAIN_TEXT);

    private volatile Thread deadlockThread1;
    private volatile Thread deadlockThread2;

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }

    @AfterEach
    public void cleanupDeadlockedThreads() {
        // Interrupt deadlocked threads so they don't leak
        Thread t1 = deadlockThread1;
        Thread t2 = deadlockThread2;
        if (t1 != null) {
            t1.interrupt();
        }
        if (t2 != null) {
            t2.interrupt();
        }
    }

    @Test
    public void testDeadlockDetectionEmitsEvents() throws Exception {
        Object lock1 = new Object();
        Object lock2 = new Object();
        CountDownLatch bothLocked = new CountDownLatch(2);

        deadlockThread1 = new Thread(() -> {
            synchronized (lock1) {
                bothLocked.countDown();
                try {
                    bothLocked.await();
                    Thread.sleep(50);
                } catch (InterruptedException e) {
                    return;
                }
                synchronized (lock2) {
                    // never reached
                }
            }
        }, "deadlock-test-thread-1");

        deadlockThread2 = new Thread(() -> {
            synchronized (lock2) {
                bothLocked.countDown();
                try {
                    bothLocked.await();
                    Thread.sleep(50);
                } catch (InterruptedException e) {
                    return;
                }
                synchronized (lock1) {
                    // never reached
                }
            }
        }, "deadlock-test-thread-2");

        deadlockThread1.setDaemon(true);
        deadlockThread2.setDaemon(true);
        deadlockThread1.start();
        deadlockThread2.start();

        // Wait for both threads to acquire their first lock
        bothLocked.await();
        Thread.sleep(200); // Let the deadlock form

        // Start deadlock detector with a short interval
        profiler.startDeadlockDetector(100);

        // Wait for detection
        Thread.sleep(1500);

        profiler.stopDeadlockDetector();
        stopProfiler();

        // Verify events
        IItemCollection events = verifyEvents("datadog.DeadlockedThread");
        assertTrue(events.hasItems(), "Expected deadlock events to be present");

        Set<Long> deadlockIds = new HashSet<>();
        boolean hasStackTraces = false;

        for (IItemIterable items : events) {
            IMemberAccessor<IQuantity, IItem> deadlockIdAccessor =
                    DEADLOCK_ID.getAccessor(items.getType());
            IMemberAccessor<String, IItem> lockNameAccessor =
                    LOCK_NAME.getAccessor(items.getType());
            IMemberAccessor<IMCStackTrace, IItem> stackTraceAccessor =
                    STACK_TRACE.getAccessor(items.getType());

            for (IItem item : items) {
                if (deadlockIdAccessor != null) {
                    IQuantity id = deadlockIdAccessor.getMember(item);
                    if (id != null) {
                        deadlockIds.add(id.longValue());
                    }
                }
                if (lockNameAccessor != null) {
                    String lockName = lockNameAccessor.getMember(item);
                    assertNotNull(lockName, "Lock name should not be null");
                    assertFalse(lockName.isEmpty(), "Lock name should not be empty");
                }
                if (stackTraceAccessor != null) {
                    IMCStackTrace st = stackTraceAccessor.getMember(item);
                    if (st != null && st.getFrames() != null && !st.getFrames().isEmpty()) {
                        hasStackTraces = true;
                    }
                }
            }
        }

        // All events should share the same deadlockId
        assertEquals(1, deadlockIds.size(),
                "Expected all events to share the same deadlock ID, got: " + deadlockIds);
        assertTrue(hasStackTraces, "Expected at least one event with a non-empty stack trace");
    }
}
