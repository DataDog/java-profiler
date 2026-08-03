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

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ContextSetter;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junitpioneer.jupiter.RetryingTest;
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
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * End-to-end coverage for the custom-attribute {@code setContextValue}/{@code ContextSetter} ->
 * JFR field pipeline, on the all-native context write path.
 *
 * <p>{@link com.datadoghq.profiler.ContextValueCacheTest} covers the value-cache unit in
 * isolation, and {@link AllNativeContextSamplingTest} covers span/root-span propagation into JFR,
 * but neither confirms that a value written via {@code setContextValue} actually surfaces as a
 * correctly-named, correctly-weighted JFR field. This closes that gap.
 */
public class CustomContextAttributeSamplingTest extends AbstractProfilerTest {

    @BeforeEach
    void assumeNotJ9() {
        // On J9, ProfiledThread (and thus the OTEP TLS buffer) is not allocated until the thread
        // is registered for wall-clock profiling, so a fresh context write throws.
        Assumptions.assumeTrue(!Platform.isJ9());
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,attributes=tag1;tag2;tag3";
    }

    @RetryingTest(10)
    public void customAttributeValueSurfacesInJfr() throws InterruptedException {
        registerCurrentThreadForWallClockProfiling();
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList("tag1", "tag2", "tag3"));
        int slot = contextSetter.offsetOf("tag1");

        // Session-unique prefix so each @RetryingTest attempt registers fresh values in the
        // native Dictionary, matching dictionary_context_keys to this run's writes only.
        String pfx = Long.toHexString(System.nanoTime()) + "_";
        String[] values = IntStream.range(0, 10).mapToObj(i -> pfx + i).toArray(String[]::new);
        for (int i = 0; i < values.length * 10; i++) {
            String value = values[i % values.length];
            assertTrue(profiler.setContextValue(slot, value));
            Thread.sleep(10);
            profiler.clearContextValue(slot);
        }
        stopProfiler();

        IItemCollection events = verifyEvents("datadog.MethodSample");
        Map<String, AtomicLong> weightsByTagValue = new HashMap<>();
        for (IItemIterable samples : events) {
            IMemberAccessor<IQuantity, IItem> weightAccessor = WEIGHT.getAccessor(samples.getType());
            IMemberAccessor<String, IItem> tag1Accessor = TAG_1.getAccessor(samples.getType());
            IMemberAccessor<String, IItem> tag2Accessor = TAG_2.getAccessor(samples.getType());
            if (tag1Accessor == null || tag2Accessor == null) {
                continue;
            }
            IMemberAccessor<String, IItem> stacktraceAccessor =
                    JdkAttributes.STACK_TRACE_STRING.getAccessor(samples.getType());
            for (IItem sample : samples) {
                String stacktrace = stacktraceAccessor.getMember(sample);
                if (!stacktrace.contains("sleep") || stacktrace.contains("<dropped due to contention>")) {
                    // Only count samples taken while the context was definitely active.
                    continue;
                }
                String tag = tag1Accessor.getMember(sample);
                if (tag == null) {
                    continue;
                }
                weightsByTagValue.computeIfAbsent(tag, v -> new AtomicLong())
                        .addAndGet(weightAccessor.getMember(sample).longValue());
                assertNull(tag2Accessor.getMember(sample), "tag2 was never set for this thread");
            }
        }
        for (String value : values) {
            assertNotNull(weightsByTagValue.get(value),
                    "no sample carried tag1=" + value + ". Found: " + weightsByTagValue.keySet());
        }

        // jdk.ActiveSetting must enumerate the configured attribute names, unbundling the
        // dynamic-column config into the recording.
        IItemCollection activeSettings = verifyEvents("jdk.ActiveSetting");
        Set<String> recordedContextAttributes = new HashSet<>();
        for (IItemIterable activeSetting : activeSettings) {
            IMemberAccessor<String, IItem> nameAccessor =
                    JdkAttributes.REC_SETTING_NAME.getAccessor(activeSetting.getType());
            IMemberAccessor<String, IItem> valueAccessor =
                    JdkAttributes.REC_SETTING_VALUE.getAccessor(activeSetting.getType());
            for (IItem item : activeSetting) {
                if ("contextattribute".equals(nameAccessor.getMember(item))) {
                    recordedContextAttributes.add(valueAccessor.getMember(item));
                }
            }
        }
        assertEquals(3, recordedContextAttributes.size());
        assertTrue(recordedContextAttributes.contains("tag1"));
        assertTrue(recordedContextAttributes.contains("tag2"));
        assertTrue(recordedContextAttributes.contains("tag3"));

        // dictionary_context_keys must match the number of distinct values registered above.
        Map<String, Long> jfrCounters = new HashMap<>();
        for (IItemIterable counterEvent : verifyEvents("datadog.ProfilerCounter")) {
            IMemberAccessor<String, IItem> nameAccessor = NAME.getAccessor(counterEvent.getType());
            IMemberAccessor<IQuantity, IItem> countAccessor = COUNT.getAccessor(counterEvent.getType());
            for (IItem item : counterEvent) {
                jfrCounters.put(nameAccessor.getMember(item), countAccessor.getMember(item).longValue());
            }
        }
        assertFalse(jfrCounters.isEmpty());
        assertEquals(values.length, jfrCounters.get("dictionary_context_keys"));
    }
}
