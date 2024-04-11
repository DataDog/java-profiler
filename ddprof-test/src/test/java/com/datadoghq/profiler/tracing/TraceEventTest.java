package com.datadoghq.profiler.tracing;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.TraceEvent;
import com.datadoghq.profiler.events.CyclicBarrierTime;
import com.datadoghq.profiler.events.EventType;
import com.datadoghq.profiler.events.QueueTime;
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

import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.*;

public class TraceEventTest extends AbstractProfilerTest {
    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }

    private static final class Task implements Runnable {

        private final JavaProfiler profiler;
        private final TraceEvent traceEvent;

        private Task(JavaProfiler profiler) {
            this.profiler = profiler;
            this.traceEvent = profiler.startTrace(EventType.QUEUE);
            ((QueueTime) traceEvent).setTask(Task.class.getName());
            ((QueueTime) traceEvent).setScheduler("scheduler");
        }

        @Override
        public void run() {
            profiler.setContext(1, 2);
            if (traceEvent.shouldCommit(9, TimeUnit.MILLISECONDS)) {
                traceEvent.commit();
            }
            traceEvent.free();
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
        {
            profiler.setContext(10, 20);
            CyclicBarrierTime cbt = (CyclicBarrierTime) profiler.startTrace(EventType.CYCLIC_BARRIER);
            Thread.sleep(20);
            cbt.setTask(Task.class.getName());
            cbt.setBarrier(1, 0);
            if (cbt.shouldCommit(10, TimeUnit.MILLISECONDS)) {
                cbt.commit();
            }
            cbt.reset();
            cbt.setTask(Task.class.getName());
            cbt.setBarrier(1, 1);
            Thread.sleep(25);
            if (cbt.shouldCommit(20, TimeUnit.MILLISECONDS)) {
                cbt.commit();
            }
            cbt.free();
            profiler.clearContext();
        }

        stopProfiler();

        IAttribute<IQuantity> startTimeAttr = attr("startTime", "", "", TIMESTAMP);
        IAttribute<IMCThread> originAttr = attr("origin", "", "", THREAD);
        IAttribute<IMCType> taskAttr = attr("task", "", "", CLASS);
        IAttribute<IMCType> schedulerAttr = attr("scheduler", "", "", CLASS);
        IAttribute<IQuantity> barrierAttr = attr("barrier", "", "", NUMBER);
        IAttribute<IQuantity> generationAttr = attr("generation", "", "", NUMBER);

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

        IItemCollection queueTimeEvents = verifyEvents("datadog.QueueTime");
        for (IItemIterable it : queueTimeEvents) {
            for (IItem item : it) {
                assertTrue(startTimeAttr.getAccessor(it.getType()).getMember(item).longValueIn(EPOCH_NS) > 0);
                IRange<IQuantity> lifetime = JfrAttributes.LIFETIME.getAccessor(it.getType()).getMember(item);
                long duration = lifetime.getEnd().longValueIn(EPOCH_MS) - lifetime.getStart().longValueIn(EPOCH_MS);
                assertTrue(duration >= 10);
                assertEquals(task.getClass().getName(), taskAttr.getAccessor(it.getType()).getMember(item).getTypeName());
                assertEquals("scheduler", schedulerAttr.getAccessor(it.getType()).getMember(item).getTypeName());
                assertEquals(1, SPAN_ID.getAccessor(it.getType()).getMember(item).longValue());
                assertEquals(2, LOCAL_ROOT_SPAN_ID.getAccessor(it.getType()).getMember(item).longValue());
                assertEquals("origin", originAttr.getAccessor(it.getType()).getMember(item).getThreadName());
            }
        }

        IItemCollection barrierEvents = verifyEvents("datadog.CyclicBarrierTime");
        for (IItemIterable it : barrierEvents) {
            for (IItem item : it) {
                assertTrue(startTimeAttr.getAccessor(it.getType()).getMember(item).longValueIn(EPOCH_NS) > 0);
                IRange<IQuantity> lifetime = JfrAttributes.LIFETIME.getAccessor(it.getType()).getMember(item);
                long duration = lifetime.getEnd().longValueIn(EPOCH_MS) - lifetime.getStart().longValueIn(EPOCH_MS);
                assertTrue(duration >= 9);
                assertEquals(task.getClass().getName(), taskAttr.getAccessor(it.getType()).getMember(item).getTypeName());
                assertEquals(1, barrierAttr.getAccessor(it.getType()).getMember(item).longValue());
                assertEquals(10, SPAN_ID.getAccessor(it.getType()).getMember(item).longValue());
                assertEquals(20, LOCAL_ROOT_SPAN_ID.getAccessor(it.getType()).getMember(item).longValue());
                int generation = (int) generationAttr.getAccessor(it.getType()).getMember(item).longValue();
                assertTrue(generation == 0 || generation == 1);
            }
        }
    }
}
