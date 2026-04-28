package com.datadoghq.profiler.queue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCThread;
import org.openjdk.jmc.common.IMCType;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.IRange;
import org.openjdk.jmc.flightrecorder.JfrAttributes;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.concurrent.ArrayBlockingQueue;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.*;

public class QueueTimeTest extends AbstractProfilerTest {
    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }

    private static final class Task implements Runnable {

        private final JavaProfiler profiler;
        private final long start;
        private final Thread origin;

        private Task(JavaProfiler profiler) {
            this.profiler = profiler;
            this.start = profiler.getCurrentTicks();
            this.origin = Thread.currentThread();
        }

        @Override
        public void run() {
            profiler.setContext(1, 2);
            long now = profiler.getCurrentTicks();
            if (profiler.isThresholdExceeded(9, start, now)) {
                profiler.recordQueueTime(start, now, getClass(), QueueTimeTest.class, ArrayBlockingQueue.class, 10, origin, 0L);
            }
            profiler.clearContext();
        }
    }

    /**
     * Regression test for the QueueTime field serialization order bug: submittingSpanId was
     * written before writeContext(), placing it at field position 9 (where the schema expects
     * the consuming spanId). This caused the backend to read completely wrong span IDs.
     * <p>
     * Verifies that all three span-ID fields (spanId, localRootSpanId, submittingSpanId) round-trip
     * correctly when they are all distinct and non-zero.
     */
    @Test
    public void testQueueTimeFieldOrder() throws Exception {
        IAttribute<IQuantity> submittingSpanIdAttr = attr("submittingSpanId", "", "", NUMBER);

        Thread origin = Thread.currentThread();
        origin.setName("origin-field-order");
        // Use distinct, non-zero values so any field-order swap is detectable:
        //   consuming spanId=7, rootSpanId=42 (set via setContext), submittingSpanId=99.
        long start = profiler.getCurrentTicks();
        Runnable worker = () -> {
            profiler.setContext(7, 42);
            long now = profiler.getCurrentTicks();
            profiler.recordQueueTime(start, now, QueueTimeTest.class, QueueTimeTest.class,
                    ArrayBlockingQueue.class, 1, origin, 99L);
            profiler.clearContext();
        };
        Thread thread = new Thread(worker, "destination-field-order");
        Thread.sleep(10);
        thread.start();
        thread.join();
        stopProfiler();

        IItemCollection events = verifyEvents("datadog.QueueTime");
        boolean found = false;
        for (IItemIterable it : events) {
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> submittingAccessor = submittingSpanIdAttr.getAccessor(it.getType());
            for (IItem item : it) {
                if (spanIdAccessor.getMember(item).longValue() == 7) {
                    found = true;
                    assertEquals(7, spanIdAccessor.getMember(item).longValue(), "spanId must be the consuming span (not the submitting span)");
                    assertEquals(42, rootSpanIdAccessor.getMember(item).longValue(), "localRootSpanId must be the root");
                    assertEquals(99, submittingAccessor.getMember(item).longValue(), "submittingSpanId must be the submitting span (not the root)");
                }
            }
        }
        assertTrue(found, "Expected at least one QueueTime event with spanId=7");
    }

    /**
     * When {@code consumingSpanIdOverride} is non-zero, native code must use it for JFR
     * {@code spanId} instead of the active {@code Contexts} span.
     */
    @Test
    public void testQueueTimeConsumingSpanIdOverride() throws Exception {
        Thread origin = Thread.currentThread();
        origin.setName("origin-override");
        long start = profiler.getCurrentTicks();
        Runnable worker = () -> {
            profiler.setContext(1, 2);
            long now = profiler.getCurrentTicks();
            long override = 88L;
            profiler.recordQueueTime(
                    start,
                    now,
                    QueueTimeTest.class,
                    QueueTimeTest.class,
                    ArrayBlockingQueue.class,
                    1,
                    origin,
                    99L,
                    override);
            profiler.clearContext();
        };
        Thread thread = new Thread(worker, "destination-override");
        Thread.sleep(10);
        thread.start();
        thread.join();
        stopProfiler();

        IItemCollection events = verifyEvents("datadog.QueueTime");
        boolean found = false;
        for (IItemIterable it : events) {
            IMemberAccessor<IQuantity, IItem> acc = SPAN_ID.getAccessor(it.getType());
            for (IItem item : it) {
                if (acc.getMember(item).longValue() == 88) {
                    found = true;
                    break;
                }
            }
        }
        assertTrue(found, "Expected QueueTime with spanId=88 from override");
    }

    @Test
    public void testRecordQueueTime() throws Exception {
        Thread origin = Thread.currentThread();
        origin.setName("origin");
        Task task = new Task(profiler);
        Thread thread = new Thread(task, "destination");
        Thread.sleep(10);
        thread.start();
        thread.join();
        stopProfiler();

        IAttribute<IQuantity> startTimeAttr = attr("startTime", "", "", TIMESTAMP);
        IAttribute<IMCThread> originAttr = attr("origin", "", "", THREAD);
        IAttribute<IMCType> taskAttr = attr("task", "", "", CLASS);
        IAttribute<IMCType> schedulerAttr = attr("scheduler", "", "", CLASS);
        IAttribute<IMCType> queueTypeAttr = attr("queueType", "", "", CLASS);
        IAttribute<IQuantity> queueLengthAttr = attr("queueLength", "", "", NUMBER);

        IItemCollection activeSettings = verifyEvents("jdk.ActiveSetting");
        for (IItemIterable activeSetting : activeSettings) {
            IMemberAccessor<String, IItem> nameAccessor = JdkAttributes.REC_SETTING_NAME.getAccessor(activeSetting.getType());
            IMemberAccessor<String, IItem> valueAccessor = JdkAttributes.REC_SETTING_VALUE.getAccessor(activeSetting.getType());
            for (IItem item : activeSetting) {
                String name = nameAccessor.getMember(item);
                if ("tscfrequency".equals(name)) {
                    String frequency = valueAccessor.getMember(item);
                    assertTrue(Long.valueOf(frequency) > 0, frequency);
                }
            }
        }

        IItemCollection events = verifyEvents("datadog.QueueTime");
        for (IItemIterable it : events) {
            for (IItem item : it) {
                assertTrue(startTimeAttr.getAccessor(it.getType()).getMember(item).longValueIn(EPOCH_NS) > 0);
                IRange<IQuantity> lifetime = JfrAttributes.LIFETIME.getAccessor(it.getType()).getMember(item);
                long duration = lifetime.getEnd().longValueIn(EPOCH_MS) - lifetime.getStart().longValueIn(EPOCH_MS);
                assertTrue(duration >= 9);
                assertEquals(task.getClass().getName(), taskAttr.getAccessor(it.getType()).getMember(item).getTypeName());
                assertEquals(getClass().getName(), schedulerAttr.getAccessor(it.getType()).getMember(item).getTypeName());
                assertEquals(1, SPAN_ID.getAccessor(it.getType()).getMember(item).longValue());
                assertEquals(2, LOCAL_ROOT_SPAN_ID.getAccessor(it.getType()).getMember(item).longValue());
                assertEquals("origin", originAttr.getAccessor(it.getType()).getMember(item).getThreadName());
                assertEquals(ArrayBlockingQueue.class.getName(), queueTypeAttr.getAccessor(it.getType()).getMember(item).getTypeName());
                assertEquals(10, queueLengthAttr.getAccessor(it.getType()).getMember(item).longValue());
            }
        }
    }
}
