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
                profiler.recordQueueTime(start, now, getClass(), QueueTimeTest.class, ArrayBlockingQueue.class, 10, origin);
            }
            profiler.clearContext();
        }
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
