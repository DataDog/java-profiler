/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
import static org.junit.jupiter.api.Assertions.assertThrows;
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
        profiler.setContext(1L, 42L, 0L, 43L);
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
        profiler.setContext(1L, 42L, 0L, 43L);
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

        // Null arrays and length mismatch must throw.
        assertThrows(NullPointerException.class,
                () -> contextSetter.setContextValuesByIdAndBytes(null, new byte[1][]));
        assertThrows(NullPointerException.class,
                () -> contextSetter.setContextValuesByIdAndBytes(new int[1], null));
        assertThrows(IllegalArgumentException.class,
                () -> contextSetter.setContextValuesByIdAndBytes(new int[2], new byte[3][]));

        // A slot with constantId > 0 requires non-null bytes within the size limit.
        assertThrows(NullPointerException.class,
                () -> contextSetter.setContextValuesByIdAndBytes(
                        new int[] {id, 0}, new byte[][] {null, null}));
        assertThrows(IllegalArgumentException.class,
                () -> contextSetter.setContextValuesByIdAndBytes(
                        new int[] {id, 0}, new byte[][] {new byte[256], null}));

        // 255 bytes is the boundary and must be accepted.
        // Register the 255-byte value so its constant ID matches the bytes we pass.
        byte[] ok255 = new byte[255];
        Arrays.fill(ok255, (byte) 'x');
        assertTrue(contextSetter.setContextValue("tag1", new String(ok255, StandardCharsets.UTF_8)));
        int id255 = contextSetter.snapshotTags()[slot];
        assertNotEquals(0, id255);
        assertTrue(contextSetter.setContextValuesByIdAndBytes(
                new int[] {id255, 0}, new byte[][] {ok255, null}));
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
        profiler.setContext(1L, 42L, 0L, 43L);
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

        // Slots processed before the overflow are durably written — false does not mean
        // the record is unchanged. At least tag1 (slot 0) must retain the new value.
        int firstSlot = contextSetter.offsetOf("tag1");
        assertEquals(bigId, contextSetter.snapshotTags()[firstSlot],
                "slot 0 processed before overflow must have its sidecar durably written");
        assertEquals(bigValue, readTag(contextSetter, "tag1"),
                "slot 0 processed before overflow must be readable via attrs_data");
    }

    // -----------------------------------------------------------------------
    // Acceptance tests for the MAX_CUSTOM_SLOTS guard fixes
    // -----------------------------------------------------------------------

    /**
     * Test 1: setContextValuesByIdAndBytes must throw IllegalArgumentException immediately when
     * the arrays are longer than MAX_CUSTOM_SLOTS (10), and must not perform
     * any partial write before the rejection.
     */
    @Test
    public void testSetContextValuesByIdAndBytesRejectsArraysLongerThanMaxSlots() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));
        int slot = contextSetter.offsetOf("tag1");

        // Establish a known value and capture its constant ID.
        assertTrue(contextSetter.setContextValue("tag1", "original"));
        int savedId = contextSetter.snapshotTags()[slot];
        assertNotEquals(0, savedId);

        // Build arrays of length 11 (> MAX_CUSTOM_SLOTS = 10).
        int[] ids = new int[11];
        byte[][] utf8 = new byte[11][];
        ids[0] = savedId;
        utf8[0] = "original".getBytes(StandardCharsets.UTF_8);
        // All other entries remain 0 / null.

        // The call must be rejected with an exception before any write.
        assertThrows(IllegalArgumentException.class,
                () -> contextSetter.setContextValuesByIdAndBytes(ids, utf8),
                "setContextValuesByIdAndBytes must throw when array length > MAX_CUSTOM_SLOTS");

        // No partial write: the sidecar for slot 0 must be unchanged.
        assertEquals(savedId, contextSetter.snapshotTags()[slot],
                "sidecar must not be modified before the length guard fires");
    }

    /**
     * Test 2: setContextValuesByIdAndBytes must accept arrays of exactly
     * MAX_CUSTOM_SLOTS (10) and return true, restoring all sidecar values.
     */
    @Test
    public void testSetContextValuesByIdAndBytesAcceptsExactlyMaxSlots() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        List<String> attrs = new ArrayList<>();
        for (int i = 1; i <= 10; i++) {
            attrs.add("tag" + i);
        }
        ContextSetter contextSetter = new ContextSetter(profiler, attrs);

        // Set all 10 attributes to distinct values and capture constant IDs + bytes.
        int[] savedIds = new int[10];
        byte[][] savedBytes = new byte[10][];
        for (int i = 0; i < 10; i++) {
            String value = "val" + i;
            assertTrue(contextSetter.setContextValue("tag" + (i + 1), value));
            savedBytes[i] = value.getBytes(StandardCharsets.UTF_8);
        }
        int[] snapshot = contextSetter.snapshotTags();
        for (int i = 0; i < 10; i++) {
            savedIds[i] = snapshot[i];
            assertNotEquals(0, savedIds[i], "tag" + (i + 1) + " must have a non-zero sidecar ID");
        }

        // Wipe all slots via setContext (span activation).
        profiler.setContext(1L, 42L, 0L, 43L);

        // Reapply with exactly-10-element arrays — must succeed.
        assertTrue(contextSetter.setContextValuesByIdAndBytes(savedIds, savedBytes),
                "setContextValuesByIdAndBytes must return true for arrays of length == MAX_CUSTOM_SLOTS");

        // All 10 sidecar IDs must be restored.
        int[] restored = contextSetter.snapshotTags();
        for (int i = 0; i < 10; i++) {
            assertEquals(savedIds[i], restored[i],
                    "sidecar for tag" + (i + 1) + " must be restored after reapply");
        }
    }

    /**
     * Test 3: snapshotTags(int[]) with an oversized buffer (length > attributes.size())
     * must write the managed indices [0, attributes.size()) with the current sidecar values,
     * and zero out the extra indices [attributes.size(), snapshot.length).
     */
    @Test
    public void testSnapshotTagsOversizedBufferCopiesAndZerosExtras() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));

        assertTrue(contextSetter.setContextValue("tag1", "v1"));
        assertTrue(contextSetter.setContextValue("tag2", "v2"));

        // Verify no-arg overload returns valid IDs.
        int[] canonical = contextSetter.snapshotTags();
        assertNotEquals(0, canonical[0]);
        assertNotEquals(0, canonical[1]);

        // Oversized buffer: length 5 > attributes.size() == 2.
        int[] oversized = new int[5];
        Arrays.fill(oversized, -1);
        contextSetter.snapshotTags(oversized);

        // Managed indices [0, attributes.size()) must contain the current sidecar values.
        assertEquals(canonical[0], oversized[0],
                "oversized buffer[0] must match no-arg snapshotTags()[0]");
        assertEquals(canonical[1], oversized[1],
                "oversized buffer[1] must match no-arg snapshotTags()[1]");

        // Extra indices [attributes.size(), snapshot.length) must be zeroed.
        for (int i = 2; i < oversized.length; i++) {
            assertEquals(0, oversized[i],
                    "oversized buffer element [" + i + "] must be zeroed by snapshotTags");
        }

        // No-arg overload must still work correctly.
        int[] check = contextSetter.snapshotTags();
        assertEquals(canonical[0], check[0]);
        assertEquals(canonical[1], check[1]);
    }

    /**
     * Test 4: snapshotTags(int[]) with an undersized buffer (length < attributes.size())
     * must be a no-op — existing no-op semantics must be preserved.
     */
    @Test
    public void testSnapshotTagsUndersizedBufferIsNoOp() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2", "tag3"));

        assertTrue(contextSetter.setContextValue("tag1", "a"));
        assertTrue(contextSetter.setContextValue("tag2", "b"));
        assertTrue(contextSetter.setContextValue("tag3", "c"));

        // Undersized buffer: length 1 < attributes.size() == 3.
        int[] undersized = new int[1];
        undersized[0] = -1;
        contextSetter.snapshotTags(undersized);

        assertEquals(-1, undersized[0],
                "undersized buffer must not be written by snapshotTags");
    }

    /**
     * Test 5: snapshotTags(int[]) with an exact-size buffer (length == attributes.size())
     * must copy the current sidecar values correctly.
     */
    @Test
    public void testSnapshotTagsExactSizeBufferCopiesCorrectly() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2"));

        assertTrue(contextSetter.setContextValue("tag1", "x"));
        assertTrue(contextSetter.setContextValue("tag2", "y"));

        // No-arg overload to obtain expected values.
        int[] canonical = contextSetter.snapshotTags();
        assertNotEquals(0, canonical[0]);
        assertNotEquals(0, canonical[1]);

        // Exact-size buffer: length 2 == attributes.size() == 2.
        int[] exact = new int[2];
        contextSetter.snapshotTags(exact);

        assertEquals(canonical[0], exact[0],
                "exact-size buffer[0] must match no-arg snapshotTags()[0]");
        assertEquals(canonical[1], exact[1],
                "exact-size buffer[1] must match no-arg snapshotTags()[1]");
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
