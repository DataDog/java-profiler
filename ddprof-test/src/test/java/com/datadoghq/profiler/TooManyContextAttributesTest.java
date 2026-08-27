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
package com.datadoghq.profiler;

import org.junitpioneer.jupiter.RetryingTest;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ThreadLocalRandom;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Regression test: {@code attributes=} used to accept more names than the native
 * {@code DD_TAGS_CAPACITY} (context.h), and {@code Recording::writeContextSnapshot}
 * (flightRecorder.cpp) looped over that unbounded count calling the unchecked
 * {@code Context::get_tag(i)} on a fixed {@code Tag tags[DD_TAGS_CAPACITY]} array -
 * reading past the {@code Context} struct into adjacent native memory on every
 * {@code datadog.HeapLiveObject} event.
 *
 * <p>Requesting more attributes than the native capacity must no longer crash (an
 * ASan build turns the out-of-bounds read into a heap-buffer-overflow abort) and the
 * profiler must cap the attribute list it advertises/serializes at
 * {@link JavaProfiler#MAX_CONTEXT_SLOTS}, keeping the JFR metadata schema and the
 * per-event field count consistent. See {@link MaxContextSlotsTest} for the
 * companion drift guard between {@code JavaProfiler.MAX_CONTEXT_SLOTS} and {@code DD_TAGS_CAPACITY}.
 */
public class TooManyContextAttributesTest extends AbstractProfilerTest {

    private static final int REQUESTED_ATTRIBUTES = JavaProfiler.MAX_CONTEXT_SLOTS + 3;

    @Override
    protected String getProfilerCommand() {
        String attrs = IntStream.range(0, REQUESTED_ATTRIBUTES)
                .mapToObj(i -> "tag" + i)
                .collect(Collectors.joining(";"));
        // memory=...:L enables liveness tracking, which is the only path that writes
        // datadog.HeapLiveObject events via the vulnerable Recording::writeContextSnapshot.
        return "memory=256:L,attributes=" + attrs;
    }

    @Override
    protected boolean isPlatformSupported() {
        // Liveness tracking requires Java 11+ and specific JVM types (see LivenessTrackingTest).
        return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
    }

    @RetryingTest(5)
    public void moreAttributesThanCapacityDoesNotCrashAndIsCapped() throws Exception {
        // Generate enough live allocation volume to clear the 256 KB sampling interval many
        // times over, mirroring the workload LivenessTrackingTest uses to reliably produce
        // datadog.HeapLiveObject samples.
        List<byte[]> liveObjects = new ArrayList<>();
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 10; j++) {
                liveObjects.add(new byte[ThreadLocalRandom.current().nextInt(1024, 4096)]);
            }
        }
        Thread.sleep(100);
        for (int i = 0; i < 6; i++) {
            System.gc();
            Thread.sleep(100);
        }
        Thread.sleep(300);

        stopProfiler();
        assertFalse(liveObjects.isEmpty()); // keep allocations reachable through the GC/dump above

        // If the pre-fix out-of-bounds read had fired, an ASan build would already have
        // aborted the JVM above. On any build, a mismatched schema/field count would make
        // this parse fail or throw - reaching here with samples already proves the fix.
        JfrEvents liveObjectEvents = verifyEvents("datadog.HeapLiveObject", false);
        assertTrue(liveObjectEvents.hasItems(), "expected datadog.HeapLiveObject samples");

        Set<String> recordedContextAttributes = new HashSet<>();
        for (JfrEvent item : verifyEvents("jdk.ActiveSetting")) {
            if ("contextattribute".equals(item.getString("name"))) {
                recordedContextAttributes.add(item.getString("value"));
            }
        }
        assertEquals(JavaProfiler.MAX_CONTEXT_SLOTS, recordedContextAttributes.size(),
                "attributes= list must be capped at JavaProfiler.MAX_CONTEXT_SLOTS (" + JavaProfiler.MAX_CONTEXT_SLOTS
                        + "), got: " + recordedContextAttributes);
        for (int i = 0; i < JavaProfiler.MAX_CONTEXT_SLOTS; i++) {
            assertTrue(recordedContextAttributes.contains("tag" + i),
                    "expected tag" + i + " to survive capping, got: " + recordedContextAttributes);
        }
        for (int i = JavaProfiler.MAX_CONTEXT_SLOTS; i < REQUESTED_ATTRIBUTES; i++) {
            assertFalse(recordedContextAttributes.contains("tag" + i),
                    "tag" + i + " exceeds capacity and must have been dropped");
        }
    }
}
