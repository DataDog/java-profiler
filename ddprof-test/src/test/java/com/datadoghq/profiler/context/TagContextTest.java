package com.datadoghq.profiler.context;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ContextSetter;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
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

import static com.datadoghq.profiler.MoreAssertions.*;
import static org.junit.jupiter.api.Assertions.*;

public class TagContextTest extends AbstractProfilerTest {

    @Test
    public void test() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9() || (Platform.isJ9() && Platform.isJavaVersion(8)));
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
            assertTrue(Math.abs(weights[i] - avg) < 0.15 * weights[i], strings[i]
                    + " more than 15% from mean");
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

        Map<String, Long> debugCounters = profiler.getDebugCounters();
        assertFalse(debugCounters.isEmpty());
        assertEquals(1, debugCounters.get("context_storage_pages"));
        assertEquals(0x10000, debugCounters.get("context_storage_bytes"));
        assertEquals(strings.length, debugCounters.get("dictionary_context_keys"));
        assertEquals(Arrays.stream(strings).mapToInt(s -> s.length() + 1).sum(), debugCounters.get("dictionary_context_keys_bytes"));
        assertBoundedBy(debugCounters.get("dictionary_context_pages"), strings.length, "context storage too many pages");
        assertBoundedBy(debugCounters.get("dictionary_context_bytes"), strings.length * DICTIONARY_PAGE_SIZE, "context storage too many pages");
    }

    private void work(ContextSetter contextSetter, String contextAttribute, String contextValue)
            throws InterruptedException {
        assertTrue(contextSetter.setContextValue(contextAttribute, contextValue));
        checkTagValues(contextSetter, contextAttribute);
        Thread.sleep(10);
        assertTrue(contextSetter.clearContextValue(contextAttribute));
    }

    private void checkTagValues(ContextSetter contextSetter, String contextAttribute) {
        int[] tags = contextSetter.snapshotTags();
        // expects tag1/tag2/tag3 - change this if the tested tags change
        int offset = Integer.parseInt(contextAttribute.substring(3)) - 1;
        for (int i = 0; i < tags.length; i++) {
            if (i == offset) {
                assertNotEquals(0, tags[i]);
            } else {
                assertEquals(0, tags[i]);
            }
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms,filter=0";
    }
}
