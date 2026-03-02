package com.datadoghq.profiler.context;

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
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

        String[] strings = IntStream.range(0, 10).mapToObj(String::valueOf).toArray(String[]::new);
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
        // Read counters early so they're available in finally block even if assertions fail
        Map<String, Long> jfrCounters = new HashMap<>();
        int debugPrinted = 0;
        int nullTraceCount = 0;
        int emptyTraceCount = 0;
        try {
            for (IItemIterable counterEvent : verifyEvents("datadog.ProfilerCounter")) {
                IMemberAccessor<String, IItem> nameAccessor = NAME.getAccessor(counterEvent.getType());
                IMemberAccessor<IQuantity, IItem> countAccessor = COUNT.getAccessor(counterEvent.getType());
                for (IItem item : counterEvent) {
                    jfrCounters.put(nameAccessor.getMember(item), countAccessor.getMember(item).longValue());
                }
            }
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
                    if (stacktrace == null) { nullTraceCount++; continue; }
                    if (stacktrace.isEmpty()) { emptyTraceCount++; continue; }
                    if (debugPrinted < 10) {
                        System.out.println("[DEBUG-TRACE-" + debugPrinted + "] " + stacktrace.substring(0, Math.min(2000, stacktrace.length())));
                        debugPrinted++;
                    }
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

            // Verify counters from JFR serialized data (already read above)
            assertFalse(jfrCounters.isEmpty());
            assertEquals(strings.length, jfrCounters.get("dictionary_context_keys"));
        } finally {
            // Print statistics about dropped samples for debugging
            double dropRate = totalSamplesCount > 0 ? (100.0 * droppedSamplesCount / totalSamplesCount) : 0.0;
            double dropWeightRate = totalSamplesWeight > 0 ? (100.0 * droppedSamplesWeight / totalSamplesWeight) : 0.0;
            System.out.printf("Sample statistics: %d total (%d dropped, %.2f%%), weight %d total (%d dropped, %.2f%%)%n",
                    totalSamplesCount, droppedSamplesCount, dropRate,
                    totalSamplesWeight, droppedSamplesWeight, dropWeightRate);
            System.out.println("nullTraces=" + nullTraceCount + " emptyTraces=" + emptyTraceCount);
            // Print walkvm diagnostic counters
            System.out.println("walkvm_vmthread_ok=" + jfrCounters.getOrDefault("walkvm_vmthread_ok", 0L)
                    + " walkvm_no_vmthread=" + jfrCounters.getOrDefault("walkvm_no_vmthread", 0L)
                    + " walkvm_thread_inaccessible=" + jfrCounters.getOrDefault("walkvm_thread_inaccessible", 0L)
                    + " walkvm_anchor_null=" + jfrCounters.getOrDefault("walkvm_anchor_null", 0L)
                    + " walkvm_cached_not_java=" + jfrCounters.getOrDefault("walkvm_cached_not_java", 0L)
                    + " thread_entry_mark_detections=" + jfrCounters.getOrDefault("thread_entry_mark_detections", 0L));
            System.out.println("walkvm_hit_codeheap=" + jfrCounters.getOrDefault("walkvm_hit_codeheap", 0L)
                    + " walkvm_codeh_no_vm=" + jfrCounters.getOrDefault("walkvm_codeh_no_vm", 0L)
                    + " walkvm_anchor_used_inline=" + jfrCounters.getOrDefault("walkvm_anchor_used_inline", 0L)
                    + " walkvm_anchor_fallback=" + jfrCounters.getOrDefault("walkvm_anchor_fallback", 0L)
                    + " walkvm_anchor_fallback_fail=" + jfrCounters.getOrDefault("walkvm_anchor_fallback_fail", 0L)
                    + " walkvm_anchor_consumed=" + jfrCounters.getOrDefault("walkvm_anchor_consumed", 0L)
                    + " walkvm_depth_zero=" + jfrCounters.getOrDefault("walkvm_depth_zero", 0L));
            System.out.println("walkvm_break_interpreted=" + jfrCounters.getOrDefault("walkvm_break_interpreted", 0L)
                    + " walkvm_break_compiled=" + jfrCounters.getOrDefault("walkvm_break_compiled", 0L)
                    + " walkvm_java_frame_ok=" + jfrCounters.getOrDefault("walkvm_java_frame_ok", 0L));
        }
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
