package com.datadoghq.profiler.context;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ContextSetter;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.IntStream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class TagContextTest extends AbstractProfilerTest {

    @Test
    public void test() throws InterruptedException {
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2", "tag1"));

        String[] strings = IntStream.range(0, 10).mapToObj(String::valueOf).toArray(String[]::new);
        for (int i = 0; i < strings.length * 10; i++) {
            work(contextSetter, "tag1", strings[i % strings.length]);
        }
        stopProfiler();
        IItemCollection events = verifyEvents("datadog.MethodSample");
        Map<String, AtomicLong> weightsByTagValue = new HashMap<>();
        for (IItemIterable wallclockSamples : events) {
            IMemberAccessor<IQuantity, IItem> weightAccessor = WEIGHT.getAccessor(wallclockSamples.getType());
            // this will become more generic in the future
            IMemberAccessor<String, IItem> tag1Accessor = TAG_1.getAccessor(wallclockSamples.getType());
            assertNotNull(tag1Accessor);
            IMemberAccessor<String, IItem> tag2Accessor = TAG_2.getAccessor(wallclockSamples.getType());
            assertNotNull(tag2Accessor);
            IMemberAccessor<String, IItem> stacktraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(wallclockSamples.getType());
            for (IItem sample : wallclockSamples) {
                String stacktrace = stacktraceAccessor.getMember(sample);
                if (!stacktrace.contains("sleep")) {
                    // we don't know the context has been set for sure until the sleep has started
                    continue;
                }
                long weight = weightAccessor.getMember(sample).longValue();
                String tag = tag1Accessor.getMember(sample);
                weightsByTagValue.computeIfAbsent(tag, v -> new AtomicLong())
                        .addAndGet(weight);
                assertNull(tag2Accessor.getMember(sample));
            }
        }
        long sum = 0;
        long[] weights = new long[strings.length];
        for (int i = 0; i < strings.length; i++) {
            weights[i] = weightsByTagValue.get(strings[i]).get();
            sum += weights[i];
        }
        double avg = (double) sum / weights.length;
        for (int i = 0; i < weights.length; i++) {
            assertTrue(Math.abs(weights[i] - avg) < 0.1 * weights[i], strings[i]
                    + " more than 10% from mean");
        }
        // now check we have settings to unbundle the dynamic columns
        IItemCollection activeSettings = verifyEvents("jdk.ActiveSetting");
        Set<String> recordedContextAttributes = new HashSet<>();
        for (IItemIterable activeSetting : activeSettings) {
            IMemberAccessor<String, IItem> nameAccessor = JdkAttributes.REC_SETTING_NAME.getAccessor(activeSetting.getType());
            IMemberAccessor<String, IItem> valueAccessor = JdkAttributes.REC_SETTING_VALUE.getAccessor(activeSetting.getType());
            for (IItem item : activeSetting) {
                String name = nameAccessor.getMember(item);
                if ("contextattribute".equals(name)) {
                    recordedContextAttributes.add(valueAccessor.getMember(item));
                }
            }
        }
        assertEquals(3, recordedContextAttributes.size());
        assertTrue(recordedContextAttributes.contains("tag1"));
        assertTrue(recordedContextAttributes.contains("tag2"));
        assertTrue(recordedContextAttributes.contains("tag3"));
    }

    private void work(ContextSetter contextSetter, String contextAttribute, String contextValue)
            throws InterruptedException {
        assertTrue(contextSetter.setContextValue(contextAttribute, contextValue));
        Thread.sleep(10);
        assertTrue(contextSetter.clearContextValue(contextAttribute));
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms,filter=0";
    }
}
