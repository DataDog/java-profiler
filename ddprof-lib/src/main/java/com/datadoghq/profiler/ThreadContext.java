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
    // LRS is always a fixed 16-hex-char value in attrs_data (zero-padded u64).
    // The entry header is 2 bytes (key_index + length), giving 18 bytes total.
    private static final int LRS_FIXED_VALUE_LEN = 16;
    private static final int LRS_ENTRY_SIZE = 2 + LRS_FIXED_VALUE_LEN;
    private static final byte[] HEX_DIGITS = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

    private static final BufferWriter BUFFER_WRITER = new BufferWriter();

    // ---- Per-thread bounded direct-mapped cache for attribute values ----
    // Stores {int encoding, byte[] utf8Bytes} per entry.
    // - encoding: Dictionary constant pool ID for DD JFR sidecar
    // - utf8Bytes: UTF-8 value for OTEP attrs_data (external profilers)
    //
    // Instance (not static) so that only the owning thread ever reads or writes
    // the cache arrays — no cross-thread races, no memory barriers needed.
    // Collision evicts the old entry; a miss triggers one JNI registerConstant0() call.
    // The Dictionary (contextValueMap) is never cleared, so encodings remain valid
    // for the JVM lifetime. On profiler restart the ThreadContext instance is recreated,
    // clearing the cache; the first miss per value pays one JNI call to re-populate.
    private static final int CACHE_SIZE = 256;
    private static final int CACHE_MASK = CACHE_SIZE - 1;

    // Attribute value cache: String value → {int encoding, byte[] utf8}
    // Keyed by value string (not by keyIndex) — same string always maps to
    // same encoding regardless of key slot.
    private final String[] attrCacheKeys = new String[CACHE_SIZE];
    private final int[] attrCacheEncodings = new int[CACHE_SIZE];
    private final byte[][] attrCacheBytes = new byte[CACHE_SIZE][];

    // OTEP record field offsets (from packed struct)
    private final int validOffset;
    private final int traceIdOffset;
    private final int spanIdOffset;
    private final int attrsDataSizeOffset;
    private final int attrsDataOffset;
    private final int maxAttrsDataSize;
    private final int lrsSidecarOffset; // localRootSpanId offset in sidecar

    private final ByteBuffer recordBuffer;   // 640 bytes, OtelThreadContextRecord
    private final ByteBuffer sidecarBuffer;  // tag encodings + LRS

    /**
     * Creates a ThreadContext from the two DirectByteBuffers returned by native initializeContextTLS0.
     *
     * @param recordBuffer 640-byte buffer over OtelThreadContextRecord
     * @param sidecarBuffer buffer over tag encodings + local root span id
     * @param metadata array with [VALID_OFFSET, TRACE_ID_OFFSET, SPAN_ID_OFFSET,
     *                 ATTRS_DATA_SIZE_OFFSET, ATTRS_DATA_OFFSET, LRS_SIDECAR_OFFSET]
     */
    public ThreadContext(ByteBuffer recordBuffer, ByteBuffer sidecarBuffer, long[] metadata) {
        // Record buffer uses native order for uint16_t attrs_data_size (read by C as native uint16_t).
        // trace_id/span_id are uint8_t[] arrays requiring big-endian — handled via Long.reverseBytes()
        // in setContextDirect(). Only little-endian platforms are supported.
        this.recordBuffer = recordBuffer.order(ByteOrder.nativeOrder());
        this.sidecarBuffer = sidecarBuffer.order(ByteOrder.nativeOrder());
        this.validOffset = (int) metadata[0];
        this.traceIdOffset = (int) metadata[1];
        this.spanIdOffset = (int) metadata[2];
        this.attrsDataSizeOffset = (int) metadata[3];
        this.attrsDataOffset = (int) metadata[4];
        this.maxAttrsDataSize = OTEL_MAX_RECORD_SIZE - this.attrsDataOffset;
        this.lrsSidecarOffset = (int) metadata[5];
        if (ByteOrder.nativeOrder() != ByteOrder.LITTLE_ENDIAN) {
            throw new UnsupportedOperationException(
                "ByteBuffer context path requires little-endian platform");
        }
        // Zero sidecar + record to prevent stale encodings from a previous profiler session.
        // The native ProfiledThread survives across sessions, so the sidecar may hold
        // old tag encodings and the record may hold old attrs_data.
        for (int i = 0; i < MAX_CUSTOM_SLOTS; i++) {
            this.sidecarBuffer.putInt(i * Integer.BYTES, 0);
        }
        this.sidecarBuffer.putLong(this.lrsSidecarOffset, 0);
        this.recordBuffer.put(this.validOffset, (byte) 0);
        // Pre-initialize the fixed-size LRS entry at attrs_data[0..LRS_ENTRY_SIZE-1]:
        //   key_index=0, length=16, value=16 zero hex bytes.
        // The entry is always present; updates overwrite only the 16 value bytes.
        this.recordBuffer.put(this.attrsDataOffset, (byte) LRS_OTEP_KEY_INDEX);
        this.recordBuffer.put(this.attrsDataOffset + 1, (byte) LRS_FIXED_VALUE_LEN);
        for (int i = 0; i < LRS_FIXED_VALUE_LEN; i++) {
            this.recordBuffer.put(this.attrsDataOffset + 2 + i, (byte) '0');
        }
        this.recordBuffer.putShort(this.attrsDataSizeOffset, (short) LRS_ENTRY_SIZE);
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
        return 0; // Return type kept for ABI compatibility; value carries no meaning.
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

    /**
     * Clears a custom attribute: zeros the sidecar encoding and removes it from OTEP attrs_data.
     */
    public void clearContextAttribute(int keyIndex) {
        if (keyIndex < 0 || keyIndex >= MAX_CUSTOM_SLOTS) {
            return;
        }
        int otepKeyIndex = keyIndex + 1;
        detach();
        sidecarBuffer.putInt(keyIndex * Integer.BYTES, 0);
        removeOtepAttribute(otepKeyIndex);
        attach();
    }

    public void copyCustoms(int[] value) {
        int len = Math.min(value.length, MAX_CUSTOM_SLOTS);
        for (int i = 0; i < len; i++) {
            value[i] = sidecarBuffer.getInt(i * Integer.BYTES);
        }
    }

    /**
     * Sets a custom attribute on the current thread's context by string value.
     * Uses a per-thread encoding cache to avoid JNI for repeated values
     * (the common case). On cache miss, a single JNI call registers the value
     * in the native Dictionary; subsequent calls with the same value are
     * zero-JNI ByteBuffer writes.
     *
     * <p><b>High-cardinality values are not supported.</b> Each unique value
     * permanently occupies one slot in the native Dictionary, which is bounded
     * at 65536 entries across all threads for the JVM lifetime. Once exhausted,
     * this method returns {@code false} and clears the attribute. Use only
     * low-cardinality values (e.g. endpoint names, DB system names). UUIDs,
     * request IDs, and other per-request-unique strings will exhaust the
     * Dictionary and cause attributes to be silently dropped.
     *
     * @param keyIndex Index into the registered attribute key map (0-based)
     * @param value The string value for this attribute
     * @return true if the attribute was set successfully, false if the
     *         Dictionary is full or the keyIndex is out of range
     */
    public boolean setContextAttribute(int keyIndex, String value) {
        if (keyIndex < 0 || keyIndex >= MAX_CUSTOM_SLOTS || value == null) {
            return false;
        }
        return setContextAttributeDirect(keyIndex, value);
    }

    /**
     * Writes both the sidecar encoding (DD signal handler) and OTEP attrs_data
     * UTF-8 value (external profilers) via ByteBuffer.
     */
    private boolean setContextAttributeDirect(int keyIndex, String value) {

        // Resolve encoding + UTF-8 bytes from per-thread cache
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
                // Dictionary full: clear sidecar AND remove the OTEP attrs_data entry
                // so both views stay consistent (both report no value for this key).
                clearContextAttribute(keyIndex);
                return false;
            }
            utf8 = value.getBytes(StandardCharsets.UTF_8);
            attrCacheEncodings[slot] = encoding;
            attrCacheBytes[slot] = utf8;
            attrCacheKeys[slot] = value;
        }

        // Write both sidecar and OTEP attrs_data inside the detach/attach window
        // so a signal handler never sees a new sidecar encoding alongside old attrs_data.
        int otepKeyIndex = keyIndex + 1;
        detach();
        sidecarBuffer.putInt(keyIndex * Integer.BYTES, encoding);
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

        if (trHi == 0 && trLo == 0 && spanId == 0) {
            clearContextDirect();
            return;
        }

        // Write trace_id (big-endian) + span_id (big-endian)
        recordBuffer.putLong(traceIdOffset, Long.reverseBytes(trHi));
        recordBuffer.putLong(traceIdOffset + 8, Long.reverseBytes(trLo));
        recordBuffer.putLong(spanIdOffset, Long.reverseBytes(spanId));

        // Reset custom attribute state so the previous span's values don't leak
        // into this span. Callers set attributes again via setContextAttribute().
        for (int i = 0; i < MAX_CUSTOM_SLOTS; i++) {
            // i * Integer.BYTES: byte offset into sidecar buffer for int slot i
            sidecarBuffer.putInt(i * Integer.BYTES, 0);
        }
        // Reset attrs_data_size to contain only the fixed LRS entry, discarding
        // any custom attribute entries written during the previous span.
        recordBuffer.putShort(attrsDataSizeOffset, (short) LRS_ENTRY_SIZE);

        // Update LRS sidecar and OTEP attrs_data inside the detach/attach window so a
        // signal handler never sees the new LRS with old trace/span IDs.
        sidecarBuffer.putLong(lrsSidecarOffset, localRootSpanId);
        writeLrsHex(localRootSpanId);

        attach();
    }

    // ---- LRS helpers ----

    /**
     * Zeros trace/span IDs, sidecar encodings, and LRS. Called between detach() and the
     * return in the all-zero path; valid stays 0 (no attach) so no reader can see attrs_data.
     * attrs_data_size is not reset here; the next non-zero setContext call will reset it
     * before attach(). This is safe because valid remains 0 after clear, so no reader will
     * observe the stale attrs_data_size.
     */
    private void clearContextDirect() {
        recordBuffer.putLong(traceIdOffset, 0);
        recordBuffer.putLong(traceIdOffset + 8, 0);
        recordBuffer.putLong(spanIdOffset, 0);
        writeLrsHex(0);
        for (int i = 0; i < MAX_CUSTOM_SLOTS; i++) {
            sidecarBuffer.putInt(i * Integer.BYTES, 0);
        }
        sidecarBuffer.putLong(lrsSidecarOffset, 0);
    }

    /**
     * Overwrite the 16 hex value bytes of the fixed LRS entry in-place.
     * The entry header (key_index=0, length=16) is pre-initialized and never touched.
     * Called between detach() and attach(); no allocation.
     */
    private void writeLrsHex(long val) {
        int base = attrsDataOffset + 2; // skip key_index byte + length byte
        for (int i = 15; i >= 0; i--) {
            recordBuffer.put(base + i, HEX_DIGITS[(int)(val & 0xF)]);
            val >>>= 4;
        }
    }

    // ---- OTEP record helpers (called between detach/attach) ----

    /**
     * Invalidates the record (sets valid=0). Typically followed by attach(), but the
     * clear path intentionally leaves the record invalid without calling attach().
     */
    private void detach() {
        recordBuffer.put(validOffset, (byte) 0);
        BUFFER_WRITER.storeFence();
    }

    /** Validate record. */
    private void attach() {
        // storeFence ensures all record writes are visible before valid=1.
        // The TLS pointer (otel_thread_ctx_v1) is permanent and never
        // written here; external profilers rely solely on the valid flag.
        BUFFER_WRITER.storeFence();
        // Plain put is sufficient: signal handlers run on the same hardware thread,
        // so they observe stores in program order — no volatile needed for same-thread
        // visibility. The preceding storeFence() provides the release barrier.
        recordBuffer.put(validOffset, (byte) 1);
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

    /**
     * Reads a custom attribute value from attrs_data by key index.
     * Scans the attrs_data entries and returns the UTF-8 string for the matching key.
     * Intended for tests only.
     *
     * @param keyIndex 0-based user key index (same as passed to setContextAttribute)
     * @return the attribute value string, or null if not set
     */
    public String readContextAttribute(int keyIndex) {
        if (keyIndex < 0 || keyIndex >= MAX_CUSTOM_SLOTS) {
            return null;
        }
        int otepKeyIndex = keyIndex + 1;
        int size = recordBuffer.getShort(attrsDataSizeOffset) & 0xFFFF;
        int pos = 0;
        while (pos + 2 <= size) {
            int k = recordBuffer.get(attrsDataOffset + pos) & 0xFF;
            int len = recordBuffer.get(attrsDataOffset + pos + 1) & 0xFF;
            if (pos + 2 + len > size) {
                break;
            }
            if (k == otepKeyIndex) {
                byte[] bytes = new byte[len];
                for (int i = 0; i < len; i++) {
                    bytes[i] = recordBuffer.get(attrsDataOffset + pos + 2 + i);
                }
                return new String(bytes, StandardCharsets.UTF_8);
            }
            pos += 2 + len;
        }
        return null;
    }

    /**
     * Reads the trace ID from the OTEP record as a 32-char lowercase hex string.
     * The trace ID is stored big-endian; this method returns it as-is.
     * Intended for tests only.
     */
    public String readTraceId() {
        StringBuilder sb = new StringBuilder(32);
        for (int i = 0; i < 16; i++) {
            int b = recordBuffer.get(traceIdOffset + i) & 0xFF;
            sb.append((char) HEX_DIGITS[b >> 4]);
            sb.append((char) HEX_DIGITS[b & 0xF]);
        }
        return sb.toString();
    }

    private static native int registerConstant0(String value);
    private static native long[] getContext0();
}
