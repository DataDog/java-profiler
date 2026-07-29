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
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Resolves configured context attribute names to their fixed slot indices in the all-native
 * context record. Deduplicates and truncates the configured attribute list to {@link
 * JavaProfiler#MAX_CONTEXT_SLOTS} slots; callers use {@link #offsetOf} to translate an attribute
 * name into the slot index passed to {@link JavaProfiler#setContextValue}.
 */
public class ContextSetter {

    private final List<String> attributes;

    public ContextSetter(JavaProfiler profiler, List<String> attributes) {
        Set<String> unique = new HashSet<>(attributes);
        this.attributes = new ArrayList<>(unique.size());
        for (int i = 0; i < Math.min(attributes.size(), JavaProfiler.MAX_CONTEXT_SLOTS); i++) {
            String attribute = attributes.get(i);
            if (unique.remove(attribute)) {
                this.attributes.add(attribute);
            }
        }
    }

    public int offsetOf(String attribute) {
        return attributes.indexOf(attribute);
    }

    /** Number of (deduplicated, truncated) context attribute slots. */
    public int size() {
        return attributes.size();
    }
}
