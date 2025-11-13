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
    
    private static int SPAN_ID_OFFSET = 0;
    private static int ROOT_SPAN_ID_OFFSET = SPAN_ID_OFFSET + 8;
    private static int CHECKSUM_OFFSET = ROOT_SPAN_ID_OFFSET + 8;
    private static int CUSTOM_TAGS_OFFSET = CHECKSUM_OFFSET + 8;

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
        long swappedRootSpanId = ((rootSpanId & 0xFFFFFFFFL) << 32) | (rootSpanId >> 32);
        long hashRootSpanId = swappedRootSpanId * KNUTH_CONSTANT;
        long computed = hashSpanId ^ hashRootSpanId;
        computed = computed == 0 ? 0xffffffffffffffffL : computed;
        System.out.println("===> hash: (" + Long.toBinaryString(spanId) + ", " + Long.toBinaryString(swappedRootSpanId) + ") -> (" + Long.toBinaryString(hashSpanId) + ", " + Long.toBinaryString(hashRootSpanId) + ") -> " + Long.toBinaryString(computed));
        return computed;
    }

    private final ByteBuffer buffer;

    public ThreadContext(ByteBuffer buffer) {
        this.buffer = buffer.order(ByteOrder.LITTLE_ENDIAN);
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
        long checksum = computeContextChecksum(spanId, rootSpanId);
        buffer.putLong(CHECKSUM_OFFSET, 0); // mark in progress
        buffer.putLong(SPAN_ID_OFFSET, spanId);
        buffer.putLong(ROOT_SPAN_ID_OFFSET, rootSpanId);
        buffer.putLong(CHECKSUM_OFFSET, checksum);
        System.err.println("===> Setting: " + Thread.currentThread().getName() + " :: " + spanId + ", " + rootSpanId + ", " + Long.toHexString(checksum));
        return checksum;
    }

    public void putCustom(int offset, int value) {
        buffer.putInt(CUSTOM_TAGS_OFFSET + offset, value);
    }
}