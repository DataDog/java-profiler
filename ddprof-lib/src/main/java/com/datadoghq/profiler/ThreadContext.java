/*
 * Copyright 2025, 2026 Datadog, Inc
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

/**
 * Thread-local context for trace/span identification.
 *
 * <p>Provides access to thread-local context storage used by the profiler to correlate
 * samples with distributed traces. Supports two storage modes:
 * <ul>
 *   <li><b>Profiler mode (default)</b>: Context stored in TLS via direct ByteBuffer mapping</li>
 *   <li><b>OTEL mode</b>: Context stored in OTEP TLS record accessible by external profilers</li>
 * </ul>
 *
 * <p>The storage mode is determined at profiler startup via the {@code ctxstorage} option.
 * Reading and writing context automatically routes to the correct storage via JNI.
 */
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

    /**
     * Direct ByteBuffer mapped to ProfiledThread._otel_tag_encodings[].
     * Non-null only in OTEL mode; allows Java to write tag encodings directly
     * to the same memory the signal handler reads — zero JNI overhead.
     */
    private final ByteBuffer sidecarBuffer;

    private final boolean useJNI;

    /**
     * True if OTEL context storage mode is active.
     * In OTEL mode, context reads must go through JNI since the OTEP
     * record is managed via a separate TLS pointer, not the direct ByteBuffer.
     */
    private final boolean otelMode;

    /**
     * Creates a ThreadContext with native struct field offsets.
     *
     * @param buffer Direct ByteBuffer mapped to native Context struct
     * @param offsets Array of native struct field offsets:
     *                [0] = offsetof(Context, spanId)
     *                [1] = offsetof(Context, rootSpanId)
     *                [2] = offsetof(Context, checksum)
     *                [3] = offsetof(Context, tags)
     * @param sidecarBuffer Direct ByteBuffer mapped to ProfiledThread._otel_tag_encodings,
     *                      or null if not in OTEL mode
     */
    public ThreadContext(ByteBuffer buffer, int[] offsets, ByteBuffer sidecarBuffer) {
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
        // Check if OTEL mode is active - if so, reads must go through JNI
        otelMode = isOtelMode0();
        this.sidecarBuffer = sidecarBuffer != null
            ? sidecarBuffer.order(ByteOrder.LITTLE_ENDIAN) : null;
    }

    /**
     * Gets the span ID from the current thread's context.
     *
     * <p>In OTEL mode, reads from the OTEP TLS record via JNI.
     * In profiler mode, reads directly from the TLS ByteBuffer.
     *
     * @return the span ID, or 0 if not set
     */
    public long getSpanId() {
        return getContext()[0];
    }

    /**
     * Gets the root span ID from the current thread's context.
     *
     * <p>In OTEL mode, reads from the OTEP TLS record via JNI.
     * In profiler mode, reads directly from the TLS ByteBuffer.
     *
     * @return the root span ID, or 0 if not set
     */
    public long getRootSpanId() {
        return getContext()[1];
    }

    /**
     * Reads both span ID and root span ID in a single call.
     * Prefer this over separate getSpanId() + getRootSpanId() calls
     * to avoid double JNI round-trips in OTEL mode.
     *
     * @return array with [spanId, rootSpanId], or [0, 0] if not set
     */
    public long[] getContext() {
        if (otelMode) {
            long[] ctx = getContext0();
            return ctx != null ? ctx : new long[2];
        }
        return new long[] { buffer.getLong(spanIdOffset), buffer.getLong(rootSpanIdOffset) };
    }

    public long getChecksum() {
        if (otelMode) {
            return 0; // OTEL mode uses valid-flag validation, not checksums
        }
        return buffer.getLong(checksumOffset);
    }

    public long put(long spanId, long rootSpanId) {
        if (otelMode) {
            // In OTEL mode, delegate to setFull with zero trace IDs.
            // rootSpanId maps to localRootSpanId for endpoint correlation.
            setContextFull0(rootSpanId, spanId, 0, 0);
            return 0;
        }
        return useJNI ? setContext0(spanId, rootSpanId) : putContextJava(spanId, rootSpanId);
    }

    /**
     * Sets trace context with full 128-bit W3C trace ID and local root span ID.
     * In OTEL mode: writes trace_id + span_id to the OTEP record, stores
     * localRootSpanId as a reserved attribute for JFR endpoint correlation.
     * In profiler mode: traceIdHigh is ignored, localRootSpanId maps to rootSpanId.
     *
     * @param localRootSpanId Local root span ID (for endpoint correlation)
     * @param spanId The span ID
     * @param traceIdHigh Upper 64 bits of the 128-bit trace ID
     * @param traceIdLow Lower 64 bits of the 128-bit trace ID
     */
    public void put(long localRootSpanId, long spanId, long traceIdHigh, long traceIdLow) {
        setContextFull0(localRootSpanId, spanId, traceIdHigh, traceIdLow);
    }

    public void putCustom(int offset, int value) {
        if (offset >= MAX_CUSTOM_SLOTS) {
            throw new IllegalArgumentException("Invalid offset: " + offset + " (max " +  MAX_CUSTOM_SLOTS + ")");
        }
        if (otelMode && sidecarBuffer != null) {
            // Write directly to the sidecar buffer (same memory the signal handler reads)
            BUFFER_WRITER.writeOrderedInt(sidecarBuffer, offset * 4, value);
        } else if (useJNI || otelMode) {
            // OTEL without sidecar (shouldn't happen) must still go through JNI
            // to write to ProfiledThread sidecar, not the Context struct buffer.
            setContextSlot0(offset, value);
        } else {
            setContextSlotJava(offset, value);
        }
    }

    public void copyCustoms(int[] value) {
        int len = Math.min(value.length, MAX_CUSTOM_SLOTS);
        ByteBuffer src = (otelMode && sidecarBuffer != null) ? sidecarBuffer : buffer;
        int baseOffset = (otelMode && sidecarBuffer != null) ? 0 : customTagsOffset;
        for (int i = 0; i < len; i++) {
            value[i] = src.getInt(baseOffset + i * 4);
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

    /**
     * Sets a custom attribute on the current thread's context by string value.
     *
     * <p>In OTEL mode: encodes the value directly into the OTEP record's attrs_data.
     * In profiler mode: registers the string as a constant and writes the encoding
     * to the TLS context tag slot (same as registerConstant + putCustom).
     *
     * @param keyIndex Index into the registered attribute key map (0-based)
     * @param value The string value for this attribute
     * @return true if the attribute was set successfully
     */
    public boolean setContextAttribute(int keyIndex, String value) {
        if (keyIndex < 0 || keyIndex > 255 || value == null) {
            return false;
        }
        return setContextAttribute0(keyIndex, value);
    }

    private static native long setContext0(long spanId, long rootSpanId);
    private static native void setContextFull0(long localRootSpanId, long spanId, long traceIdHigh, long traceIdLow);
    private static native void setContextSlot0(int offset, int value);
    private static native boolean setContextAttribute0(int keyIndex, String value);

    /**
     * Checks if OTEL context storage mode is active.
     *
     * @return true if OTEL mode is active, false for default profiler mode
     */
    private static native boolean isOtelMode0();

    /**
     * Reads context via the native ContextApi.
     *
     * <p>This method routes to the appropriate storage backend based on the
     * active storage mode (OTEP TLS record or TLS).
     *
     * @return array with [spanId, rootSpanId], or null on error
     */
    private static native long[] getContext0();
}
