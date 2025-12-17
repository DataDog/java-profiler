/*
 * Copyright 2025, Datadog, Inc
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

import java.util.Collections;
import java.util.List;
import java.util.Set;
import java.util.HashSet;

/**
 * Helper class for setting profiling context values.
 *
 * <p>This class provides a simplified interface for setting custom labels
 * on the current thread's profiling context.
 *
 * <p>Note: Custom labels are limited to 8 slots (indices 2-9), as indices
 * 0 and 1 are reserved for trace context (span-id and root-span-id).
 */
public class ContextSetter {
    private final JavaProfiler profiler;
    private final Set<String> allowedAttributes;

    /**
     * Creates a ContextSetter with a whitelist of allowed attribute names.
     *
     * @param profiler The JavaProfiler instance
     * @param attributes List of attribute names that are allowed to be set.
     *                   Only attributes in this list can be set via this ContextSetter.
     *                   If null or empty, all attributes are allowed.
     */
    public ContextSetter(JavaProfiler profiler, List<String> attributes) {
        this.profiler = profiler;
        if (attributes == null || attributes.isEmpty()) {
            this.allowedAttributes = Collections.emptySet();
        } else {
            this.allowedAttributes = new HashSet<>(attributes);
        }
    }

    /**
     * Sets a context value for the current thread.
     *
     * <p>If a whitelist of attributes was provided in the constructor,
     * only attributes in that whitelist can be set.
     *
     * @param attribute The attribute name (label key)
     * @param value The attribute value (label value)
     * @return true if the label was set successfully, false if the attribute
     *         is not in the whitelist or if the operation failed
     */
    public boolean setContextValue(String attribute, String value) {
        if (attribute == null || value == null) {
            return false;
        }

        // Check whitelist if configured
        if (!allowedAttributes.isEmpty() && !allowedAttributes.contains(attribute)) {
            return false;
        }

        ThreadContext context = profiler.getThreadContext();
        return context.setLabel(attribute, value);
    }

    /**
     * Clears a context value for the current thread.
     *
     * @param attribute The attribute name (label key) to clear
     * @return true if the label was cleared successfully, false otherwise
     */
    public boolean clearContextValue(String attribute) {
        if (attribute == null) {
            return false;
        }

        // Check whitelist if configured
        if (!allowedAttributes.isEmpty() && !allowedAttributes.contains(attribute)) {
            return false;
        }

        ThreadContext context = profiler.getThreadContext();
        return context.removeLabel(attribute);
    }
}
