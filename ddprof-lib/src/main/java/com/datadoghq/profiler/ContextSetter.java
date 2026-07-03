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

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

@Deprecated // DirectByteBuffer context wrapper; superseded by JavaProfiler.setTraceContext/setContextValue (all-native). Removed in phase 3.
public class ContextSetter {

    private final List<String> attributes;
    private final JavaProfiler profiler;

    public ContextSetter(JavaProfiler profiler, List<String> attributes) {
        this.profiler = profiler;
        Set<String> unique = new HashSet<>(attributes);
        this.attributes = new ArrayList<>(unique.size());
        for (int i = 0; i < Math.min(attributes.size(), ThreadContext.MAX_CUSTOM_SLOTS); i++) {
            String attribute = attributes.get(i);
            if (unique.remove(attribute)) {
                this.attributes.add(attribute);
            }
        }
    }

    public int[] snapshotTags() {
        int[] snapshot = new int[attributes.size()];
        profiler.copyTags(snapshot);
        return snapshot;
    }

    /**
     * Copies current sidecar encodings into {@code snapshot}. The array must have at least
     * {@code attributes.size()} elements; arrays shorter than {@code attributes.size()} are
     * silently ignored. Indices {@code [attributes.size(), snapshot.length)} are zeroed after
     * copying to prevent stale data from leaking to the caller.
     * Use the no-arg {@link #snapshotTags()} overload to obtain a correctly sized array.
     */
    public void snapshotTags(int[] snapshot) {
        if (snapshot.length >= attributes.size()) {
            profiler.copyTags(snapshot);
            Arrays.fill(snapshot, attributes.size(), snapshot.length, 0);
        }
    }

    public int offsetOf(String attribute) {
        return attributes.indexOf(attribute);
    }

    public boolean setContextValue(String attribute, String value) {
        return setContextValue(offsetOf(attribute), value);
    }

    public boolean setContextValue(int offset, String value) {
        if (offset >= 0) {
            return profiler.setContextAttribute(offset, value);
        }
        return false;
    }

    /**
     * Re-applies attribute values from precomputed constant IDs and UTF-8 bytes, indexed by slot
     * (as produced by {@link #snapshotTags(int[])}). Restores both the DD sidecar encoding and the
     * OTEP attrs_data value for every slot whose constantId is {@code > 0}, in a single atomic
     * publish — no String allocation, hashing, or cache lookup. Intended for re-applying
     * application-managed context after a {@code setContext} span activation wipes the slots.
     *
     * <p><b>Partial-write on overflow.</b> A {@code false} return does not mean the record is
     * unchanged: slots that were written before an attrs_data overflow remain published. Overflowed
     * slots are zeroed in both the sidecar and attrs_data views. Callers must not assume the record
     * is unmodified when {@code false} is returned.
     */
    public boolean setContextValuesByIdAndBytes(int[] constantIds, byte[][] utf8) {
        return profiler.setContextAttributesByIdAndBytes(constantIds, utf8);
    }

    public boolean clearContextValue(String attribute) {
        return clearContextValue(offsetOf(attribute));
    }

    public boolean clearContextValue(int offset) {
        if (offset >= 0) {
            profiler.clearContextAttribute(offset);
            return true;
        }
        return false;
    }
}
