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

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public final class ThreadContext {
    /**
     * Knuth's multiplicative hash constant for 64-bit values.
     * Based on the golden ratio: 2^64 / φ where φ = (1 + √5) / 2
     */
    private static final long KNUTH_CONSTANT = 0x9E3779B97F4A7C15L; // 11400714819323198485

    private static final int MAX_CUSTOM_SLOTS = 10;

    private static final BufferWriter BUFFER_WRITER = new BufferWriter();

    // Offsets populated from native Context struct using offsetof()
    private final int spanIdOffset;
    private final int rootSpanIdOffset;
    private final int checksumOffset;
    private final int customTagsOffset;

    /**
     * Computes a hash-based checksum for context validation.
     * Uses Knuth's multiplicative hash on both spanId and rootSpanId,
     * then XORs them together. This provides better torn-read detection
     * than simple XOR alone.
     *
     * @param spanId The span identifier
     * @param rootSpanId The root span identifier
     * @return The computed checksum
     */
    public static long computeContextChecksum(long spanId, long rootSpanId) {
        long hashSpanId = spanId * KNUTH_CONSTANT;
        long swappedRootSpanId = ((rootSpanId & 0xFFFFFFFFL) << 32) | (rootSpanId >>> 32);
        long hashRootSpanId = swappedRootSpanId * KNUTH_CONSTANT;
        long computed = hashSpanId ^ hashRootSpanId;
        computed = computed == 0 ? 0xffffffffffffffffL : computed;
        return computed;
    }

    private final ByteBuffer buffer;

    private final boolean useJNI;

    /**
     * Creates a ThreadContext with native struct field offsets.
     *
     * @param buffer Direct ByteBuffer mapped to native Context struct
     * @param offsets Array of native struct field offsets:
     *                [0] = offsetof(Context, spanId)
     *                [1] = offsetof(Context, rootSpanId)
     *                [2] = offsetof(Context, checksum)
     *                [3] = offsetof(Context, tags)
     */
    public ThreadContext(ByteBuffer buffer, int[] offsets) {
        if (offsets == null || offsets.length < 4) {
            throw new IllegalArgumentException("offsets array must have at least 4 elements");
        }
        this.buffer = buffer.order(ByteOrder.LITTLE_ENDIAN);
        this.spanIdOffset = offsets[0];
        this.rootSpanIdOffset = offsets[1];
        this.checksumOffset = offsets[2];
        this.customTagsOffset = offsets[3];
        // For Java 17 and later the cost of downcall to JNI is negligible
        useJNI = Platform.isJavaVersionAtLeast(17);
    }

    public long getSpanId() {
        return buffer.getLong(spanIdOffset);
    }

    public long getRootSpanId() {
        return buffer.getLong(rootSpanIdOffset);
    }

    public long getChecksum() {
        return buffer.getLong(checksumOffset);
    }

    public long put(long spanId, long rootSpanId) {
        return useJNI ? setContext0(spanId, rootSpanId) : putContextJava(spanId, rootSpanId);
    }

    public long putCustom(int offset, int value) {
        if (offset >= MAX_CUSTOM_SLOTS) {
            throw new IllegalArgumentException("Invalid offset: " + offset + " (max " +  MAX_CUSTOM_SLOTS + ")");
        }
        // JNI path uses array indexing (offset is tag index)
        // Java path uses byte buffer (offset needs to be multiplied by 4 for byte positioning)
        return useJNI ? setContextSlot0(offset, value) : setContextSlotJava(offset, value);
    }

    public void copyCustoms(int[] value) {
        int len = Math.min(value.length, MAX_CUSTOM_SLOTS);
        for  (int i = 0; i < len; i++) {
            // custom tags are spaced by 4 bytes (32 bits)
            value[i] = buffer.getInt(customTagsOffset + i * 4);
        }
    }

    private long putContextJava(long spanId, long rootSpanId) {
        long checksum = computeContextChecksum(spanId, rootSpanId);
        BUFFER_WRITER.writeOrderedLong(buffer, checksumOffset, 0); // mark in progress
        BUFFER_WRITER.writeOrderedLong(buffer, spanIdOffset, spanId);
        BUFFER_WRITER.writeOrderedLong(buffer, rootSpanIdOffset, rootSpanId);
        BUFFER_WRITER.writeVolatileLong(buffer, checksumOffset, checksum);
        return checksum;
    }

    private long setContextSlotJava(int offset, int value) {
        BUFFER_WRITER.writeOrderedInt(buffer, customTagsOffset + offset * 4, value);
        return (long) value * offset;
    }

    private static native long setContext0(long spanId, long rootSpanId);
    private static native long setContextSlot0(int offset, int value);
}
