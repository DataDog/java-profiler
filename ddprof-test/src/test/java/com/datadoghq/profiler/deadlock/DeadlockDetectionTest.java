package com.datadoghq.profiler.deadlock;

import com.datadoghq.profiler.AbstractProfilerTest;

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

    private Thread deadlockThread1;
    private Thread deadlockThread2;
    private DeadlockDetector detector;

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }

    @Override
    protected void before() throws Exception {
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

        bothLocked.await();
        Thread.sleep(200); // Let the deadlock form

        detector = new DeadlockDetector(profiler);
        detector.start(100);
    }

    @Override
    protected void after() throws Exception {
        if (detector != null) {
            detector.stop();
            detector = null;
        }
        if (deadlockThread1 != null) {
            deadlockThread1.interrupt();
        }
        if (deadlockThread2 != null) {
            deadlockThread2.interrupt();
        }
    }

    @Test
    public void testDeadlockDetectionEmitsEvents() throws Exception {
        // Wait for detection
        Thread.sleep(1500);

        detector.stop();
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

        assertEquals(1, deadlockIds.size(),
                "Expected all events to share the same deadlock ID, got: " + deadlockIds);
        assertTrue(hasStackTraces, "Expected at least one event with a non-empty stack trace");
    }
}
