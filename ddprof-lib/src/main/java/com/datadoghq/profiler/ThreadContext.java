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
    
    private static final int SPAN_ID_OFFSET = 0;
    private static final int ROOT_SPAN_ID_OFFSET = SPAN_ID_OFFSET + 8;
    private static final int CHECKSUM_OFFSET = ROOT_SPAN_ID_OFFSET + 8;
    private static final int CUSTOM_TAGS_OFFSET = CHECKSUM_OFFSET + 8;

    private static final int MAX_CUSTOM_SLOTS = 10;

    private static final BufferWriter BUFFER_WRITER = new BufferWriter();

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

    public ThreadContext(ByteBuffer buffer) {
        this.buffer = buffer.order(ByteOrder.LITTLE_ENDIAN);
        // For Java 17 and later the cost of downcall to JNI is negligible
        useJNI = Platform.isJavaVersionAtLeast(17);
    }

    public long getSpanId() {
        return buffer.getLong(SPAN_ID_OFFSET);
    }

    public long getRootSpanId() {
        return buffer.getLong(ROOT_SPAN_ID_OFFSET);
    }

    public long getChecksum() {
        return buffer.getLong(CHECKSUM_OFFSET);
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
            value[i] = buffer.getInt(CUSTOM_TAGS_OFFSET + i * 4);
        }
    }

    private long putContextJava(long spanId, long rootSpanId) {
        long checksum = computeContextChecksum(spanId, rootSpanId);
        BUFFER_WRITER.writeLong(buffer, CHECKSUM_OFFSET, 0); // mark in progress
        BUFFER_WRITER.writeLong(buffer, SPAN_ID_OFFSET, spanId);
        BUFFER_WRITER.writeLong(buffer, ROOT_SPAN_ID_OFFSET, rootSpanId);
        BUFFER_WRITER.writeVolatileLong(buffer, CHECKSUM_OFFSET, checksum);
        return checksum;
    }

    private long setContextSlotJava(int offset, int value) {
        BUFFER_WRITER.writeInt(buffer, CUSTOM_TAGS_OFFSET + offset, value);
        return (long) value * offset;
    }

    private static native long setContext0(long spanId, long rootSpanId);
    private static native long setContextSlot0(int offset, int value);
}
