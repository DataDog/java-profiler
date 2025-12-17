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

/**
 * Thread-local context storage with custom labels support.
 *
 * <p>This class provides access to thread-local profiling context including:
 * <ul>
 *   <li>Trace context (span ID and root span ID)</li>
 *   <li>Custom labels (key-value pairs)</li>
 * </ul>
 *
 * <p>All operations delegate to native code for performance and ABI compliance
 * with the Custom Label ABI v1 specification.
 *
 * <p>The implementation uses a fixed-size pre-allocated buffer per thread:
 * <ul>
 *   <li>Maximum 10 labels per thread</li>
 *   <li>Maximum key length: 128 bytes (UTF-8)</li>
 *   <li>Maximum value length: 256 bytes (UTF-8)</li>
 * </ul>
 *
 * <p>Labels at indices 0 and 1 are reserved for trace context:
 * <ul>
 *   <li>Label 0: "span-id" → current span ID</li>
 *   <li>Label 1: "root-span-id" → root span ID</li>
 * </ul>
 *
 * @see <a href="../../../../../docs/custom-labels-v1.md">Custom Label ABI v1</a>
 * @see <a href="../../../../../docs/custom-labels-implementation.md">Implementation Details</a>
 */
public final class ThreadContext {
    /**
     * Creates a ThreadContext instance.
     *
     * <p>This constructor is package-private and should only be called by
     * {@link JavaProfiler#initializeThreadContext()}.
     */
    ThreadContext() {
        // Context initialization is handled entirely in native code
    }

    /**
     * Sets the trace context for the current thread.
     *
     * <p>This updates labels 0 and 1 with the span ID and root span ID,
     * formatted as decimal strings.
     *
     * @param spanId The span identifier
     * @param rootSpanId The root span identifier
     */
    public void put(long spanId, long rootSpanId) {
        setContext0(spanId, rootSpanId);
    }

    /**
     * Sets a custom label for the current thread.
     *
     * <p>If a label with the given key already exists, its value is updated.
     * Otherwise, a new label is added (up to the maximum capacity of 10 labels).
     *
     * <p>Keys and values exceeding their maximum lengths (128 and 256 bytes
     * respectively) will be silently truncated.
     *
     * @param key The label key (must not be null or empty)
     * @param value The label value (must not be null)
     * @return true if the label was set successfully, false if the label
     *         capacity was exceeded or parameters were invalid
     */
    public boolean setLabel(String key, String value) {
        if (key == null || key.isEmpty() || value == null) {
            return false;
        }
        return setLabel0(key, value);
    }

    /**
     * Removes a custom label by key.
     *
     * <p>Reserved labels ("span-id" and "root-span-id") cannot be removed.
     *
     * @param key The label key to remove
     * @return true if the label was found and removed, false otherwise
     */
    public boolean removeLabel(String key) {
        if (key == null || key.isEmpty()) {
            return false;
        }
        return removeLabel0(key);
    }

    /**
     * Clears all custom labels while preserving trace context.
     *
     * <p>This removes labels at indices 2-9 but preserves the reserved
     * labels "span-id" and "root-span-id" at indices 0 and 1.
     */
    public void clearLabels() {
        clearLabels0();
    }

    // Native method declarations
    private static native void setContext0(long spanId, long rootSpanId);
    private static native boolean setLabel0(String key, String value);
    private static native boolean removeLabel0(String key);
    private static native void clearLabels0();
}
