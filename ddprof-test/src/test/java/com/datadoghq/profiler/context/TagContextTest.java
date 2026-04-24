package com.datadoghq.profiler.context;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicLong;
import java.util.stream.IntStream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ContextSetter;
import static com.datadoghq.profiler.MoreAssertions.DICTIONARY_PAGE_SIZE;
import static com.datadoghq.profiler.MoreAssertions.assertBoundedBy;
import com.datadoghq.profiler.Platform;

public class TagContextTest extends AbstractProfilerTest {

    @RetryingTest(10)
    public void test() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2", "tag1"));

        // Use session-unique prefix so each @RetryingTest attempt registers fresh values in the
        // native Dictionary. Without this, on musl (no JVM fork) the per-thread attrCacheKeys
        // persists across retries: cache hits skip registerConstant0(), leaving
        // dictionary_context_keys=0 on every retry after the first.
        String pfx = Long.toHexString(System.nanoTime()) + "_";
        String[] strings = IntStream.range(0, 10).mapToObj(i -> pfx + i).toArray(String[]::new);
        for (int i = 0; i < strings.length * 10; i++) {
            work(contextSetter, "tag1", strings[i % strings.length]);
        }
        stopProfiler();
        IItemCollection events = verifyEvents("datadog.MethodSample");
        Map<String, AtomicLong> weightsByTagValue = new HashMap<>();
        long droppedSamplesCount = 0;
        long droppedSamplesWeight = 0;
        long totalSamplesCount = 0;
        long totalSamplesWeight = 0;
        try {
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
                    totalSamplesCount++;
                    totalSamplesWeight += weight;

                    if (stacktrace.contains("<dropped due to contention>")) {
                        // track dropped samples statistics but skip for weight distribution calculation
                        droppedSamplesCount++;
                        droppedSamplesWeight += weight;
                        continue;
                    }

                    String tag = tag1Accessor.getMember(sample);
                    weightsByTagValue.computeIfAbsent(tag, v -> new AtomicLong())
                            .addAndGet(weight);
                    assertNull(tag2Accessor.getMember(sample));
                }
            }
            long sum = 0;
            long[] weights = new long[strings.length];
            System.out.println("Found tag values: " + weightsByTagValue.keySet());
            for (int i = 0; i < strings.length; i++) {
                AtomicLong weight = weightsByTagValue.get(strings[i]);
                assertNotNull(weight, "Weight for " + strings[i] + " not found. Found: " + weightsByTagValue.keySet());
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

            // Verify counters from JFR serialized data (not live process counters which are reset)
            Map<String, Long> jfrCounters = new HashMap<>();
            for (IItemIterable counterEvent : verifyEvents("datadog.ProfilerCounter")) {
                IMemberAccessor<String, IItem> nameAccessor = NAME.getAccessor(counterEvent.getType());
                IMemberAccessor<IQuantity, IItem> countAccessor = COUNT.getAccessor(counterEvent.getType());
                for (IItem item : counterEvent) {
                    String name = nameAccessor.getMember(item);
                    jfrCounters.put(name, countAccessor.getMember(item).longValue());
                }
            }

            assertFalse(jfrCounters.isEmpty());
            assertEquals(strings.length, jfrCounters.get("dictionary_context_keys"));
        } finally {
            // Print statistics about dropped samples for debugging
            double dropRate = totalSamplesCount > 0 ? (100.0 * droppedSamplesCount / totalSamplesCount) : 0.0;
            double dropWeightRate = totalSamplesWeight > 0 ? (100.0 * droppedSamplesWeight / totalSamplesWeight) : 0.0;
            System.out.printf("Sample statistics: %d total (%d dropped, %.2f%%), weight %d total (%d dropped, %.2f%%)%n",
                    totalSamplesCount, droppedSamplesCount, dropRate,
                    totalSamplesWeight, droppedSamplesWeight, dropWeightRate);
        }
    }

    /**
     * Reads the current value of {@code tag} via {@link ThreadContext#readContextAttribute}
     * — the only readback path retained on the Java side (test-only).
     */
    private String readTag(ContextSetter contextSetter, String tag) {
        return profiler.getThreadContext().readContextAttribute(contextSetter.offsetOf(tag));
    }

    @Test
    public void testSnapshotRestore() throws Exception {
        // J9 does not initialize ThreadContext for non-profiled threads; skip.
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));

        // Initially both slots are empty
        assertNull(readTag(contextSetter, "tag1"));
        assertNull(readTag(contextSetter, "tag2"));

        // Set a value and read it back
        assertTrue(contextSetter.setContextValue("tag1", "before"));
        assertEquals("before", readTag(contextSetter, "tag1"));

        // Snapshot the string, overwrite, then restore
        String saved = readTag(contextSetter, "tag1");
        assertTrue(contextSetter.setContextValue("tag1", "inside"));
        assertEquals("inside", readTag(contextSetter, "tag1"));

        // Restore via setContextValue
        assertTrue(contextSetter.setContextValue("tag1", saved));
        assertEquals("before", readTag(contextSetter, "tag1"));

        // put/clear/put cycle: verify offset stability across state transitions
        assertTrue(contextSetter.clearContextValue("tag1"));
        assertNull(readTag(contextSetter, "tag1"));
        assertTrue(contextSetter.setContextValue("tag1", "after"));
        assertEquals("after", readTag(contextSetter, "tag1"));

        // tag2 was never set; readContextAttribute returns null
        assertNull(readTag(contextSetter, "tag2"));
    }

    @Test
    public void testAttrsDataOverflow() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        List<String> attrs = new ArrayList<>();
        for (int i = 1; i <= 10; i++) {
            attrs.add("tag" + i);
        }
        ContextSetter contextSetter = new ContextSetter(profiler, attrs);
        char[] chars = new char[255];
        java.util.Arrays.fill(chars, 'x');
        String bigValue = new String(chars);
        int overflowIndex = -1;
        for (int i = 1; i <= 10; i++) {
            if (!contextSetter.setContextValue("tag" + i, bigValue)) {
                overflowIndex = i;
                break;
            }
        }
        assertTrue(overflowIndex >= 0, "Expected at least one write to overflow attrs_data");
        assertNull(readTag(contextSetter, "tag" + overflowIndex),
                   "Overflowed slot must read null — the entry never landed in attrs_data");
    }

    @Test
    public void testPutClearsCustomSlots() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));

        assertTrue(contextSetter.setContextValue("tag1", "before-put"));
        assertEquals("before-put", readTag(contextSetter, "tag1"));

        // setContext() triggers setContextDirect which resets attrs_data_size to the LRS entry only,
        // dropping all user attribute entries — so scanning attrs_data for tag1 returns null.
        profiler.setContext(1L, 42L, 0L, 42L);
        assertNull(readTag(contextSetter, "tag1"), "tag1 must be null after setContext resets attrs_data");
    }

    @Test
    public void testCrossSlotIsolation() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));

        assertTrue(contextSetter.setContextValue("tag1", "v1"));
        assertTrue(contextSetter.setContextValue("tag2", "v2"));
        assertTrue(contextSetter.clearContextValue("tag2"));
        assertEquals("v1", readTag(contextSetter, "tag1"));
        assertNull(readTag(contextSetter, "tag2"));
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
        return "wall=1ms,filter=0,attributes=tag1;tag2;tag3";
    }
}
