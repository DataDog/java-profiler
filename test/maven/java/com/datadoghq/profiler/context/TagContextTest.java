package com.datadoghq.profiler.context;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ContextSetter;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.IntStream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

public class TagContextTest extends AbstractProfilerTest {

    // FIXME - we want to use arrays of structs eventually
    public static final IAttribute<String> ATTR_1 = attr("attribute1", "", "", PLAIN_TEXT);
    public static final IAttribute<String> VALUE_1 = attr("value1", "", "", PLAIN_TEXT);
    public static final IAttribute<String> ATTR_2 = attr("attribute2", "", "", PLAIN_TEXT);
    public static final IAttribute<String> VALUE_2 = attr("value2", "", "", PLAIN_TEXT);

    @Test
    public void test() throws InterruptedException {
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag", "tag"));

        String[] strings = IntStream.range(0, 10).mapToObj(String::valueOf).toArray(String[]::new);
        for (int i = 0; i < strings.length * 10; i++) {
            work(contextSetter, "tag", strings[i % strings.length]);
        }
        stopProfiler();
        IItemCollection events = verifyEvents("datadog.MethodSample");
        Map<String, AtomicLong> weightsByTagValue = new HashMap<>();
        for (IItemIterable wallclockSamples : events) {
            IMemberAccessor<IQuantity, IItem> weightAccessor = WEIGHT.getAccessor(wallclockSamples.getType());
            // this will become more generic in the future
            IMemberAccessor<String, IItem> attr1Accessor = ATTR_1.getAccessor(wallclockSamples.getType());
            IMemberAccessor<String, IItem> value1Accessor = VALUE_1.getAccessor(wallclockSamples.getType());
            IMemberAccessor<String, IItem> attr2Accessor = ATTR_2.getAccessor(wallclockSamples.getType());
            IMemberAccessor<String, IItem> value2Accessor = VALUE_2.getAccessor(wallclockSamples.getType());
            IMemberAccessor<String, IItem> stacktraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(wallclockSamples.getType());
            for (IItem sample : wallclockSamples) {
                String stacktrace = stacktraceAccessor.getMember(sample);
                if (!stacktrace.contains("sleep")) {
                    // we don't know the context has been set for sure until the sleep has started
                    continue;
                }
                long weight = weightAccessor.getMember(sample).longValue();
                String attribute1 = attr1Accessor.getMember(sample);
                assertEquals("tag", attribute1);
                String value1 = value1Accessor.getMember(sample);
                weightsByTagValue.computeIfAbsent(value1, v -> new AtomicLong())
                        .addAndGet(weight);
                // these cost us 2 bytes per event when unused, but this will be fixed by implementing embedded
                // array support
                assertNull(attr2Accessor.getMember(sample));
                assertNull(value2Accessor.getMember(sample));
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
