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
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.IRange;
import org.openjdk.jmc.flightrecorder.JfrAttributes;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.CLASS;
import static org.openjdk.jmc.common.unit.UnitLookup.EPOCH_MS;
import static org.openjdk.jmc.common.unit.UnitLookup.EPOCH_NS;
import static org.openjdk.jmc.common.unit.UnitLookup.THREAD;
import static org.openjdk.jmc.common.unit.UnitLookup.TIMESTAMP;

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
            if (profiler.isThresholdExceeded(1, start, now)) {
                profiler.recordQueueTime(start, now, getClass(), QueueTimeTest.class, origin);
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

        IItemCollection events = verifyEvents("datadog.QueueTime");
        for (IItemIterable it : events) {
            for (IItem item : it) {
                assertTrue(startTimeAttr.getAccessor(it.getType()).getMember(item).longValueIn(EPOCH_NS) > 0);
                IRange<IQuantity> lifetime = JfrAttributes.LIFETIME.getAccessor(it.getType()).getMember(item);
                long duration = lifetime.getEnd().longValueIn(EPOCH_MS) - lifetime.getStart().longValueIn(EPOCH_MS);
                assertTrue(duration >= 1);
                assertEquals(task.getClass().getName(), taskAttr.getAccessor(it.getType()).getMember(item).getTypeName());
                assertEquals(getClass().getName(), schedulerAttr.getAccessor(it.getType()).getMember(item).getTypeName());
                assertEquals(1, SPAN_ID.getAccessor(it.getType()).getMember(item).longValue());
                assertEquals(2, LOCAL_ROOT_SPAN_ID.getAccessor(it.getType()).getMember(item).longValue());
                assertEquals("origin", originAttr.getAccessor(it.getType()).getMember(item).getThreadName());
            }
        }
    }
}
