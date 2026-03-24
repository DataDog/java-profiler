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
import java.nio.charset.StandardCharsets;

/**
 * Thread-local context for trace/span identification.
 *
 * <p>Uses OTEP #4947 TLS record for all context storage.
 * Context is written directly to the OTEP record via DirectByteBuffer
 * for minimal overhead. Only little-endian platforms are supported.
 */
public final class ThreadContext {
    private static final int MAX_CUSTOM_SLOTS = 10;
    private static final int OTEL_MAX_RECORD_SIZE = 640;
    private static final int LRS_OTEP_KEY_INDEX = 0;

    private static final BufferWriter BUFFER_WRITER = new BufferWriter();

    // ---- Process-wide bounded direct-mapped caches ----
    // Both caches store {int encoding, byte[] utf8Bytes} per entry.
    // - encoding: Dictionary constant pool ID for DD JFR sidecar
    // - utf8Bytes: UTF-8 value for OTEP attrs_data (external profilers)
    //
    // Collision evicts the old entry. Races between threads cause benign
    // cache misses (redundant work), never corruption.
    // The Dictionary (contextValueMap) is never cleared within a profiler
    // session, so encodings remain valid until the profiler is stopped.
    // On profiler restart, ThreadContext instances are recreated.
    private static final int CACHE_SIZE = 256;
    private static final int CACHE_MASK = CACHE_SIZE - 1;

    // LRS cache: long lrsValue → byte[] decimalUtf8 (for OTEP attrs_data)
    private static final long[] lrsCacheKeys = new long[CACHE_SIZE];
    private static final byte[][] lrsCacheBytes = new byte[CACHE_SIZE][];

    // Attribute value cache: String value → {int encoding, byte[] utf8}
    // Keyed by value string (not by keyIndex) — same string always maps to
    // same encoding regardless of key slot.
    private static final String[] attrCacheKeys = new String[CACHE_SIZE];
    private static final int[] attrCacheEncodings = new int[CACHE_SIZE];
    private static final byte[][] attrCacheBytes = new byte[CACHE_SIZE][];

    // OTEP record field offsets (from packed struct)
    private final int validOffset;
    private final int traceIdOffset;
    private final int spanIdOffset;
    private final int attrsDataSizeOffset;
    private final int attrsDataOffset;
    private final int maxAttrsDataSize;
    private final int lrsSidecarOffset; // localRootSpanId offset in sidecar

    private final ByteBuffer recordBuffer;   // 640 bytes, OtelThreadContextRecord
    private final ByteBuffer tlsPtrBuffer;   // 8 bytes, &custom_labels_current_set_v2
    private final ByteBuffer sidecarBuffer;  // tag encodings + LRS
    private final long recordAddress;        // for re-attach step

    /**
     * Creates a ThreadContext from the three DirectByteBuffers returned by native initializeOtelTls0.
     *
     * @param recordBuffer 640-byte buffer over OtelThreadContextRecord
     * @param tlsPtrBuffer 8-byte buffer over &amp;custom_labels_current_set_v2
     * @param sidecarBuffer buffer over tag encodings + local root span id
     * @param metadata array with [recordAddress, VALID_OFFSET, TRACE_ID_OFFSET,
     *                 SPAN_ID_OFFSET, ATTRS_DATA_SIZE_OFFSET, ATTRS_DATA_OFFSET,
     *                 LRS_SIDECAR_OFFSET]
     */
    public ThreadContext(ByteBuffer recordBuffer, ByteBuffer tlsPtrBuffer, ByteBuffer sidecarBuffer, long[] metadata) {
        // Record buffer uses native order for uint16_t attrs_data_size (read by C as native uint16_t).
        // trace_id/span_id are uint8_t[] arrays requiring big-endian — handled via Long.reverseBytes()
        // in setContextDirect(). Only little-endian platforms are supported.
        this.recordBuffer = recordBuffer.order(ByteOrder.nativeOrder());
        this.tlsPtrBuffer = tlsPtrBuffer.order(ByteOrder.nativeOrder());
        this.sidecarBuffer = sidecarBuffer.order(ByteOrder.nativeOrder());
        this.recordAddress = metadata[0];
        this.validOffset = (int) metadata[1];
        this.traceIdOffset = (int) metadata[2];
        this.spanIdOffset = (int) metadata[3];
        this.attrsDataSizeOffset = (int) metadata[4];
        this.attrsDataOffset = (int) metadata[5];
        this.maxAttrsDataSize = OTEL_MAX_RECORD_SIZE - this.attrsDataOffset;
        this.lrsSidecarOffset = (int) metadata[6];
        if (ByteOrder.nativeOrder() != ByteOrder.LITTLE_ENDIAN) {
            throw new UnsupportedOperationException(
                "ByteBuffer context path requires little-endian platform");
        }
        // Zero sidecar + record to prevent stale encodings from a previous profiler session.
        // The native ProfiledThread survives across sessions, so the sidecar may hold
        // old tag encodings and the record may hold old attrs_data.
        for (int i = 0; i < MAX_CUSTOM_SLOTS; i++) {
            this.sidecarBuffer.putInt(i * 4, 0);
        }
        this.sidecarBuffer.putLong(this.lrsSidecarOffset, 0);
        this.recordBuffer.put(this.validOffset, (byte) 0);
        this.recordBuffer.putShort(this.attrsDataSizeOffset, (short) 0);
        this.tlsPtrBuffer.putLong(0, 0);
    }

    /**
     * Reads both span ID and root span ID in a single call.
     *
     * @return array with [spanId, rootSpanId], or [0, 0] if not set
     */
    public long[] getContext() {
        long[] ctx = getContext0();
        return ctx != null ? ctx : new long[2];
    }

    public long getSpanId() {
        return getContext()[0];
    }

    public long getRootSpanId() {
        return getContext()[1];
    }

    /**
     * Sets trace context with 2-arg legacy API.
     * Maps rootSpanId to localRootSpanId. Uses spanId as traceIdLow so that
     * the OTEL clear check (all-zero) only fires when spanId is actually 0.
     * Note: this produces a synthetic trace_id of [0, spanId] in the OTEP record.
     * External OTEP readers will see this as a real W3C trace ID. Callers needing
     * correct OTEP interop must use the 4-arg {@link #put(long, long, long, long)}.
     *
     * @deprecated Use {@link #put(long, long, long, long)} instead.
     */
    @Deprecated
    public long put(long spanId, long rootSpanId) {
        put(rootSpanId, spanId, 0, spanId);
        return 0;
    }

    /**
     * Sets trace context with full 128-bit W3C trace ID and local root span ID.
     *
     * @param localRootSpanId Local root span ID (for endpoint correlation)
     * @param spanId The span ID
     * @param traceIdHigh Upper 64 bits of the 128-bit trace ID
     * @param traceIdLow Lower 64 bits of the 128-bit trace ID
     */
    public void put(long localRootSpanId, long spanId, long traceIdHigh, long traceIdLow) {
        setContextDirect(localRootSpanId, spanId, traceIdHigh, traceIdLow);
    }

    public void putCustom(int offset, int value) {
        if (offset < 0 || offset >= MAX_CUSTOM_SLOTS) {
            throw new IllegalArgumentException("Invalid offset: " + offset + " (max " + MAX_CUSTOM_SLOTS + ")");
        }
        BUFFER_WRITER.writeOrderedInt(sidecarBuffer, offset * 4, value);
    }

    public void copyCustoms(int[] value) {
        int len = Math.min(value.length, MAX_CUSTOM_SLOTS);
        for (int i = 0; i < len; i++) {
            value[i] = sidecarBuffer.getInt(i * 4);
        }
    }

    /**
     * Sets a custom attribute on the current thread's context by string value.
     * Uses a process-wide encoding cache to avoid JNI for repeated values
     * (the common case). On cache miss, a single JNI call registers the value
     * in the native Dictionary; subsequent calls with the same value are
     * zero-JNI ByteBuffer writes.
     *
     * @param keyIndex Index into the registered attribute key map (0-based)
     * @param value The string value for this attribute
     * @return true if the attribute was set successfully
     */
    public boolean setContextAttribute(int keyIndex, String value) {
        if (keyIndex < 0 || keyIndex > 255 || value == null) {
            return false;
        }
        return setContextAttributeDirect(keyIndex, value);
    }

    /**
     * Writes both the sidecar encoding (DD signal handler) and OTEP attrs_data
     * UTF-8 value (external profilers) via ByteBuffer.
     */
    private boolean setContextAttributeDirect(int keyIndex, String value) {
        if (keyIndex >= MAX_CUSTOM_SLOTS) return false;

        // Resolve encoding + UTF-8 bytes from process-wide cache
        int slot = value.hashCode() & CACHE_MASK;
        int encoding;
        byte[] utf8;
        if (value.equals(attrCacheKeys[slot])) {
            encoding = attrCacheEncodings[slot];
            utf8 = attrCacheBytes[slot];
        } else {
            // Cache miss: register in Dictionary, encode UTF-8, cache both.
            // Allocates byte[] once per unique value; cached for reuse.
            encoding = registerConstant0(value);
            if (encoding < 0) {
                BUFFER_WRITER.writeOrderedInt(sidecarBuffer, keyIndex * 4, 0);
                return false;
            }
            utf8 = value.getBytes(StandardCharsets.UTF_8);
            // Write encoding + bytes BEFORE the key — the key acts as the
            // commit for concurrent readers. The fence ensures ARM cores see
            // the values before the key that guards them.
            attrCacheEncodings[slot] = encoding;
            attrCacheBytes[slot] = utf8;
            BUFFER_WRITER.storeFence();
            attrCacheKeys[slot] = value;
        }

        // Write both sidecar and OTEP attrs_data inside the detach/attach window
        // so a signal handler never sees a new sidecar encoding alongside old attrs_data.
        int otepKeyIndex = keyIndex + 1;
        detach();
        BUFFER_WRITER.writeOrderedInt(sidecarBuffer, keyIndex * 4, encoding);
        boolean written = replaceOtepAttribute(otepKeyIndex, utf8);
        attach();
        return written;
    }

    /**
     * Write context directly to the OTEP record via ByteBuffer.
     * trace_id and span_id are OTEP big-endian byte arrays — Long.reverseBytes()
     * converts from native LE to big-endian.
     */
    private void setContextDirect(long localRootSpanId, long spanId, long trHi, long trLo) {
        detach();

        // Update LRS in sidecar inside the detach/attach window to avoid a
        // brief inconsistency where a signal handler sees the new LRS with
        // the old trace/span IDs.
        BUFFER_WRITER.writeOrderedLong(sidecarBuffer, lrsSidecarOffset, localRootSpanId);

        if (trHi == 0 && trLo == 0 && spanId == 0) {
            // Clear: zero all fields + sidecar, leave detached
            recordBuffer.putLong(traceIdOffset, 0);
            recordBuffer.putLong(traceIdOffset + 8, 0);
            recordBuffer.putLong(spanIdOffset, 0);
            recordBuffer.putShort(attrsDataSizeOffset, (short) 0);
            for (int i = 0; i < MAX_CUSTOM_SLOTS; i++) {
                sidecarBuffer.putInt(i * 4, 0);
            }
            BUFFER_WRITER.writeOrderedLong(sidecarBuffer, lrsSidecarOffset, 0);
            return;
        }

        // Write trace_id (big-endian) + span_id (big-endian)
        recordBuffer.putLong(traceIdOffset, Long.reverseBytes(trHi));
        recordBuffer.putLong(traceIdOffset + 8, Long.reverseBytes(trLo));
        recordBuffer.putLong(spanIdOffset, Long.reverseBytes(spanId));

        // Write local root span ID as a decimal UTF-8 OTEP attribute at key_index=0
        if (localRootSpanId != 0) {
            byte[] lrsUtf8 = lookupLrs(localRootSpanId);
            replaceOtepAttribute(LRS_OTEP_KEY_INDEX, lrsUtf8);
        } else {
            removeOtepAttribute(LRS_OTEP_KEY_INDEX);
        }

        attach();
    }

    // ---- LRS cache ----

    /**
     * Look up LRS decimal UTF-8 bytes from the process-wide cache.
     * On miss: converts to unsigned decimal string and caches the UTF-8 bytes.
     * Allocates one byte[] per unique LRS value (cached for reuse).
     */
    private static byte[] lookupLrs(long lrs) {
        int slot = Long.hashCode(lrs) & CACHE_MASK;
        if (lrsCacheKeys[slot] == lrs && lrsCacheBytes[slot] != null) {
            return lrsCacheBytes[slot];
        }
        byte[] utf8 = Long.toUnsignedString(lrs).getBytes(StandardCharsets.UTF_8);
        // Write bytes BEFORE key — key acts as commit for concurrent readers.
        // Fence ensures ARM cores see the bytes before the key that guards them.
        lrsCacheBytes[slot] = utf8;
        BUFFER_WRITER.storeFence();
        lrsCacheKeys[slot] = lrs;
        return utf8;
    }

    // ---- OTEP record helpers (called between detach/attach) ----

    /** Detach TLS pointer + invalidate record. Must be paired with attach(). */
    private void detach() {
        BUFFER_WRITER.writeOrderedLong(tlsPtrBuffer, 0, 0);
        recordBuffer.put(validOffset, (byte) 0);
        BUFFER_WRITER.storeFence();
    }

    /** Validate record + re-attach TLS pointer. */
    private void attach() {
        // storeFence ensures all record writes are visible before valid=1.
        // The volatile TLS pointer write provides a release barrier that
        // prevents valid=1 from being reordered past the pointer publication.
        BUFFER_WRITER.storeFence();
        recordBuffer.put(validOffset, (byte) 1);
        BUFFER_WRITER.writeVolatileLong(tlsPtrBuffer, 0, recordAddress);
    }

    /**
     * Replace or insert an attribute in attrs_data. Record must be detached.
     * Writes the pre-encoded UTF-8 bytes into the record.
     */
    private boolean replaceOtepAttribute(int otepKeyIndex, byte[] utf8) {
        int currentSize = compactOtepAttribute(otepKeyIndex);
        int valueLen = Math.min(utf8.length, 255);
        int entrySize = 2 + valueLen;
        if (currentSize + entrySize <= maxAttrsDataSize) {
            int base = attrsDataOffset + currentSize;
            recordBuffer.put(base, (byte) otepKeyIndex);
            recordBuffer.put(base + 1, (byte) valueLen);
            for (int i = 0; i < valueLen; i++) {
                recordBuffer.put(base + 2 + i, utf8[i]);
            }
            currentSize += entrySize;
            recordBuffer.putShort(attrsDataSizeOffset, (short) currentSize);
            return true;
        }
        recordBuffer.putShort(attrsDataSizeOffset, (short) currentSize);
        return false;
    }

    /** Remove an attribute from attrs_data by compacting. Record must be detached. */
    private void removeOtepAttribute(int otepKeyIndex) {
        int currentSize = compactOtepAttribute(otepKeyIndex);
        recordBuffer.putShort(attrsDataSizeOffset, (short) currentSize);
    }

    /**
     * Scan attrs_data and compact out the entry with the given key_index.
     * Returns the new attrs_data size after compaction.
     */
    private int compactOtepAttribute(int otepKeyIndex) {
        int currentSize = recordBuffer.getShort(attrsDataSizeOffset) & 0xFFFF;
        int readPos = 0;
        int writePos = 0;
        boolean found = false;
        while (readPos + 2 <= currentSize) {
            int k = recordBuffer.get(attrsDataOffset + readPos) & 0xFF;
            int len = recordBuffer.get(attrsDataOffset + readPos + 1) & 0xFF;
            if (readPos + 2 + len > currentSize) { currentSize = writePos; break; }
            if (k == otepKeyIndex) {
                found = true;
                readPos += 2 + len;
            } else {
                if (found && writePos < readPos) {
                    for (int i = 0; i < 2 + len; i++) {
                        recordBuffer.put(attrsDataOffset + writePos + i,
                            recordBuffer.get(attrsDataOffset + readPos + i));
                    }
                }
                writePos += 2 + len;
                readPos += 2 + len;
            }
        }
        return found ? writePos : currentSize;
    }

    private static native int registerConstant0(String value);
    private static native long[] getContext0();
}
