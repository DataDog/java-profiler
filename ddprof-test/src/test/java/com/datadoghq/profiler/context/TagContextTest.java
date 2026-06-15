package com.datadoghq.profiler.context;

import java.nio.charset.StandardCharsets;
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

    @Test
    public void testReapplyByIdAndBytes() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));
        int slot = contextSetter.offsetOf("tag1");
        String value = "app-managed";

        // Set the attribute the normal way, then capture both the constant ID (sidecar) and the
        // UTF-8 bytes — exactly what dd-trace-java retains for the reapply hot path.
        assertTrue(contextSetter.setContextValue("tag1", value));
        int[] ids = contextSetter.snapshotTags();
        int savedId = ids[slot];
        assertNotEquals(0, savedId);
        byte[][] bytes = new byte[ids.length][];
        bytes[slot] = value.getBytes(StandardCharsets.UTF_8);

        // setContext (span activation) wipes both views.
        profiler.setContext(1L, 42L, 0L, 42L);
        assertNull(readTag(contextSetter, "tag1"), "attrs_data must be wiped by setContext");
        assertEquals(0, contextSetter.snapshotTags()[slot], "sidecar must be wiped by setContext");

        // Reapply by ID + bytes restores BOTH views.
        assertTrue(contextSetter.setContextValuesByIdAndBytes(ids, bytes));
        assertEquals(value, readTag(contextSetter, "tag1"), "attrs_data must be restored");
        assertEquals(savedId, contextSetter.snapshotTags()[slot], "sidecar must be restored");
    }

    @Test
    public void testReapplyByIdAndBytesRejectsBadArgs() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));
        int slot = contextSetter.offsetOf("tag1");

        assertTrue(contextSetter.setContextValue("tag1", "v"));
        int id = contextSetter.snapshotTags()[slot];
        assertNotEquals(0, id);

        // Null arrays and length mismatch.
        assertFalse(contextSetter.setContextValuesByIdAndBytes(null, new byte[1][]));
        assertFalse(contextSetter.setContextValuesByIdAndBytes(new int[1], null));
        assertFalse(contextSetter.setContextValuesByIdAndBytes(new int[2], new byte[3][]));

        // A slot with constantId > 0 requires non-null bytes within the size limit.
        assertFalse(contextSetter.setContextValuesByIdAndBytes(
                new int[] {id, 0}, new byte[][] {null, null}));
        assertFalse(contextSetter.setContextValuesByIdAndBytes(
                new int[] {id, 0}, new byte[][] {new byte[256], null}));

        // 255 bytes is the boundary and must be accepted.
        byte[] ok255 = new byte[255];
        Arrays.fill(ok255, (byte) 'x');
        assertTrue(contextSetter.setContextValuesByIdAndBytes(
                new int[] {id, 0}, new byte[][] {ok255, null}));
    }

    @Test
    public void testReapplyByIdAndBytesReplacesExistingValue() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));
        int slot = contextSetter.offsetOf("tag1");

        // Capture the ID + bytes for "first".
        assertTrue(contextSetter.setContextValue("tag1", "first"));
        int[] idsFirst = contextSetter.snapshotTags();
        byte[][] bytesFirst = new byte[idsFirst.length][];
        bytesFirst[slot] = "first".getBytes(StandardCharsets.UTF_8);

        // Overwrite the live slot with a different value.
        assertTrue(contextSetter.setContextValue("tag1", "second"));
        assertEquals("second", readTag(contextSetter, "tag1"));

        // Reapply "first" by ID + bytes over the live "second" — exercises the
        // compact-then-insert path in replaceOtepAttribute.
        assertTrue(contextSetter.setContextValuesByIdAndBytes(idsFirst, bytesFirst));
        assertEquals("first", readTag(contextSetter, "tag1"));
        assertEquals(idsFirst[slot], contextSetter.snapshotTags()[slot]);
    }

    @Test
    public void testReapplyByIdAndBytesAfterClear() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));
        int slot = contextSetter.offsetOf("tag1");

        assertTrue(contextSetter.setContextValue("tag1", "live"));
        int[] ids = contextSetter.snapshotTags();
        byte[][] bytes = new byte[ids.length][];
        bytes[slot] = "live".getBytes(StandardCharsets.UTF_8);

        assertTrue(contextSetter.clearContextValue("tag1"));
        assertNull(readTag(contextSetter, "tag1"));
        assertEquals(0, contextSetter.snapshotTags()[slot]);

        assertTrue(contextSetter.setContextValuesByIdAndBytes(ids, bytes));
        assertEquals("live", readTag(contextSetter, "tag1"));
        assertEquals(ids[slot], contextSetter.snapshotTags()[slot]);
    }

    @Test
    public void testReapplyByIdAndBytesClearedRecord() throws Exception {
        // Verifies that setContextValuesByIdAndBytes never resurrects a cleared (span-less) record.
        // A cleared record has valid=0 and no trace/span context; re-publishing it would expose
        // attribute values with no associated trace, which is meaningless to the signal handler.
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));
        int slot = contextSetter.offsetOf("tag1");

        // Establish a live record with tag1 set.
        profiler.setContext(1L, 42L, 0L, 42L);
        assertTrue(contextSetter.setContextValue("tag1", "will-be-cleared"));
        int[] ids = contextSetter.snapshotTags();
        byte[][] bytes = new byte[ids.length][];
        bytes[slot] = "will-be-cleared".getBytes(StandardCharsets.UTF_8);

        // Drive valid=0 via the all-zero clear path (clearContext → put(0,0,0,0) → no attach()).
        profiler.clearContext();
        // readContextAttribute respects valid=0 and returns null, confirming the record is dark.
        assertNull(readTag(contextSetter, "tag1"));

        // Reapply must return false and must not resurrect the cleared record.
        assertFalse(contextSetter.setContextValuesByIdAndBytes(ids, bytes),
                "setContextValuesByIdAndBytes must return false when the record is cleared (valid=0)");
        assertNull(readTag(contextSetter, "tag1"),
                "cleared record must not be resurrected by setContextValuesByIdAndBytes");
    }

    @Test
    public void testReapplyByIdAndBytesOverflowRollback() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        List<String> attrs = new ArrayList<>();
        for (int i = 1; i <= 10; i++) {
            attrs.add("tag" + i);
        }
        ContextSetter contextSetter = new ContextSetter(profiler, attrs);

        // Register one 255-byte value to obtain a valid constant ID.
        char[] chars = new char[255];
        Arrays.fill(chars, 'x');
        String bigValue = new String(chars);
        assertTrue(contextSetter.setContextValue("tag1", bigValue));
        int bigId = contextSetter.snapshotTags()[contextSetter.offsetOf("tag1")];
        assertNotEquals(0, bigId);
        byte[] bigBytes = bigValue.getBytes(StandardCharsets.UTF_8);

        // Reapply the same 255-byte value to all 10 slots — attrs_data cannot hold them all.
        int[] ids = new int[10];
        byte[][] bytes = new byte[10][];
        Arrays.fill(ids, bigId);
        Arrays.fill(bytes, bigBytes);
        assertFalse(contextSetter.setContextValuesByIdAndBytes(ids, bytes),
                "10 x 255-byte values must overflow attrs_data");

        // The last slot certainly overflowed: its sidecar must be zeroed and attrs_data empty.
        int lastSlot = contextSetter.offsetOf("tag10");
        assertEquals(0, contextSetter.snapshotTags()[lastSlot],
                "overflowed slot's sidecar must be zeroed");
        assertNull(readTag(contextSetter, "tag10"),
                "overflowed slot must read null — the entry never landed in attrs_data");
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
