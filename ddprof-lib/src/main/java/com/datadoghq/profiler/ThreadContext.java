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

import java.nio.Buffer;
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
    // Max UTF-8 byte length for a custom attribute value. Matches the 1-byte length
    // field in the OTEP attrs_data entry header. Enforced up front in setContextAttribute
    // so replaceOtepAttribute can assume the input always fits.
    private static final int MAX_VALUE_BYTES = 255;
    private static final int OTEL_MAX_RECORD_SIZE = 640;
    private static final int SIDECAR_SIZE = MAX_CUSTOM_SLOTS * Integer.BYTES + Long.BYTES; // 48
    // Package-private so ScopeStack can size its byte[] scratch.
    static final int SNAPSHOT_SIZE = OTEL_MAX_RECORD_SIZE + SIDECAR_SIZE; // 688
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
    private final int lrsOffset; // localRootSpanId offset in the unified buffer
    // Base offset of the tag-encoding sidecar within the unified buffer. Every tag slot i
    // lives at ctxBuffer[tagEncodingsOffset + i * Integer.BYTES]. Equal to OTEL_MAX_RECORD_SIZE.
    private static final int TAG_ENCODINGS_OFFSET = OTEL_MAX_RECORD_SIZE;

    // Single buffer spanning [OTEP record | tag_encodings | LRS] — 688 bytes contiguous.
    // Used for per-field access AND for bulk snapshot/restore memcpy. Position state is
    // thread-confined to snapshot/restore, which reset it before each bulk op.
    private final ByteBuffer ctxBuffer;

    /**
     * Creates a ThreadContext from the single DirectByteBuffer returned by native initializeContextTLS0.
     *
     * @param ctxBuffer 688-byte unified buffer spanning record + tag_encodings + LRS
     * @param metadata array with absolute offsets [VALID, TRACE_ID, SPAN_ID,
     *                 ATTRS_DATA_SIZE, ATTRS_DATA, LRS]
     */
    public ThreadContext(ByteBuffer ctxBuffer, long[] metadata) {
        // Uses native order for uint16_t attrs_data_size (read by C as native uint16_t).
        // trace_id/span_id are uint8_t[] arrays requiring big-endian — handled via Long.reverseBytes()
        // in setContextDirect(). Only little-endian platforms are supported.
        this.ctxBuffer = ctxBuffer.order(ByteOrder.nativeOrder());
        this.validOffset = (int) metadata[0];
        this.traceIdOffset = (int) metadata[1];
        this.spanIdOffset = (int) metadata[2];
        this.attrsDataSizeOffset = (int) metadata[3];
        this.attrsDataOffset = (int) metadata[4];
        this.maxAttrsDataSize = OTEL_MAX_RECORD_SIZE - this.attrsDataOffset;
        this.lrsOffset = (int) metadata[5];
        if (ByteOrder.nativeOrder() != ByteOrder.LITTLE_ENDIAN) {
            throw new UnsupportedOperationException(
                "ByteBuffer context path requires little-endian platform");
        }
        // Zero sidecar + record to prevent stale encodings from a previous profiler session.
        // The native ProfiledThread survives across sessions, so the buffer may hold
        // old tag encodings and the record may hold old attrs_data.
        for (int i = 0; i < MAX_CUSTOM_SLOTS; i++) {
            this.ctxBuffer.putInt(TAG_ENCODINGS_OFFSET + i * Integer.BYTES, 0);
        }
        this.ctxBuffer.putLong(this.lrsOffset, 0);
        this.ctxBuffer.put(this.validOffset, (byte) 0);
        // Pre-initialize the fixed-size LRS entry at attrs_data[0..LRS_ENTRY_SIZE-1]:
        //   key_index=0, length=16, value=16 zero hex bytes.
        // The entry is always present; updates overwrite only the 16 value bytes.
        this.ctxBuffer.put(this.attrsDataOffset, (byte) LRS_OTEP_KEY_INDEX);
        this.ctxBuffer.put(this.attrsDataOffset + 1, (byte) LRS_FIXED_VALUE_LEN);
        for (int i = 0; i < LRS_FIXED_VALUE_LEN; i++) {
            this.ctxBuffer.put(this.attrsDataOffset + 2 + i, (byte) '0');
        }
        this.ctxBuffer.putShort(this.attrsDataSizeOffset, (short) LRS_ENTRY_SIZE);
    }

    /**
     * Returns the current span ID.
     * Reads directly from the OTEP record buffer (big-endian bytes → native long).
     */
    public long getSpanId() {
        return Long.reverseBytes(ctxBuffer.getLong(spanIdOffset));
    }

    /**
     * Returns the current local root span ID.
     * Reads directly from the LRS region of ctxBuffer (native long).
     */
    public long getRootSpanId() {
        return ctxBuffer.getLong(lrsOffset);
    }

    /**
     * Sets trace context with 2-arg legacy API.
     * Maps rootSpanId to localRootSpanId. Uses spanId as traceIdLow so that
     * the OTEL clear check (all-zero) only fires when spanId is actually 0.
     * Note: this produces a synthetic trace_id of [0, spanId] in the OTEP record.
     * External OTEP readers will see this as a real W3C trace ID. Callers needing
     * correct OTEP interop must use the 4-arg {@link #put(long, long, long, long)}.
     *
     * <p>Parameter mapping to the 4-arg API: {@code spanId} → {@code spanId},
     * {@code rootSpanId} → {@code localRootSpanId} (first argument).
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
        ctxBuffer.putInt(TAG_ENCODINGS_OFFSET + keyIndex * Integer.BYTES, 0);
        removeOtepAttribute(otepKeyIndex);
        attach();
    }

    public void copyCustoms(int[] value) {
        int len = Math.min(value.length, MAX_CUSTOM_SLOTS);
        for (int i = 0; i < len; i++) {
            value[i] = ctxBuffer.getInt(TAG_ENCODINGS_OFFSET + i * Integer.BYTES);
        }
    }

    /**
     * Captures the full record + sidecar state into {@code scratch[offset..offset+SNAPSHOT_SIZE)}.
     * Pair with {@link #restore} for nested-scope propagation.
     *
     * <p>The detach/memcpy/re-publish pair hides the bulk read from any signal handler going
     * through {@code ContextApi::get} — while {@code valid=0}, sidecar reads are gated off. The
     * pre-snapshot {@code valid} state is preserved in {@code scratch[offset + validOffset]} so
     * {@link #restore} can replay it. If the record was already invalid (e.g. the all-zero clear
     * path in {@link #setContextDirect} leaves {@code valid=0} with a stale {@code attrs_data_size}
     * / {@code attrs_data}), the live buffer is left invalid after snapshot — re-publishing would
     * expose a cleared-but-stale record.
     */
    public void snapshot(byte[] scratch, int offset) {
        byte priorValid = ctxBuffer.get(validOffset);
        detach();
        // Cast to Buffer: ByteBuffer.position(int) only returns ByteBuffer since JDK 9 (covariant
        // return). This source is compiled for Java 8 runtimes where the method lives on Buffer.
        ((Buffer) ctxBuffer).position(0);
        ctxBuffer.get(scratch, offset, SNAPSHOT_SIZE);
        // Overwrite the valid byte in scratch (memcpy captured the post-detach 0) with the
        // pre-snapshot value. restore() consults this to decide whether to re-attach.
        scratch[offset + validOffset] = priorValid;
        if (priorValid != 0) {
            attach();
        }
    }

    /**
     * Restores a previously captured state. The detach/memcpy/conditional-attach pair hides the
     * memcpy from readers going through {@link #ctxBuffer}'s valid flag ({@code ContextApi::get}
     * in native code), which is the sole gate for sidecar reads (see {@code thread.h}).
     *
     * <p>The valid byte inside scratch is cleared to 0 for the duration of the memcpy so that
     * even if the captured state had {@code valid=1}, the live buffer cannot transiently observe
     * {@code valid=1} alongside partially-written fields. The captured value is restored into
     * scratch after the memcpy so subsequent snapshot/restore cycles keep working, and
     * {@link #attach} re-publishes only when the saved state was itself valid — matching the
     * semantics of {@link #snapshot}.
     */
    public void restore(byte[] scratch, int offset) {
        int validIdx = offset + validOffset;
        byte wasValid = scratch[validIdx];
        scratch[validIdx] = 0;
        detach();
        ((Buffer) ctxBuffer).position(0);
        ctxBuffer.put(scratch, offset, SNAPSHOT_SIZE);
        if (wasValid != 0) {
            scratch[validIdx] = wasValid;
            attach();
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
     * <p><b>Value size limit.</b> The UTF-8 encoding of {@code value} must fit in
     * {@value #MAX_VALUE_BYTES} bytes (the OTEP attrs_data entry length field is one byte).
     * Oversized values are rejected up front — they never reach the Dictionary or attrs_data.
     *
     * @param keyIndex Index into the registered attribute key map (0-based)
     * @param value The string value for this attribute
     * @return true if the attribute was set successfully, false if the value is too long,
     *         the Dictionary is full, attrs_data overflows, or keyIndex is out of range
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
            // Cache hit — the value was previously validated and cached; no re-check needed.
            encoding = attrCacheEncodings[slot];
            utf8 = attrCacheBytes[slot];
        } else {
            // Cache miss: encode UTF-8 and validate size BEFORE touching the Dictionary.
            // Rejecting here avoids an orphan Dictionary entry (the native Dictionary is
            // write-only for the JVM lifetime and cannot be undone).
            utf8 = value.getBytes(StandardCharsets.UTF_8);
            if (utf8.length > MAX_VALUE_BYTES) {
                return false;
            }
            encoding = registerConstant0(value);
            if (encoding < 0) {
                // Dictionary full: clear sidecar AND remove the OTEP attrs_data entry
                // so both views stay consistent (both report no value for this key).
                clearContextAttribute(keyIndex);
                return false;
            }
            attrCacheEncodings[slot] = encoding;
            attrCacheBytes[slot] = utf8;
            attrCacheKeys[slot] = value;
        }

        // Write both sidecar and OTEP attrs_data inside the detach/attach window
        // so a signal handler never sees a new sidecar encoding alongside old attrs_data.
        int otepKeyIndex = keyIndex + 1;
        detach();
        ctxBuffer.putInt(TAG_ENCODINGS_OFFSET + keyIndex * Integer.BYTES, encoding);
        boolean written = replaceOtepAttribute(otepKeyIndex, utf8);
        if (!written) {
            // attrs_data overflow: the old entry was compacted out and the new one
            // couldn't fit. Zero the sidecar so both views agree there is no value.
            ctxBuffer.putInt(TAG_ENCODINGS_OFFSET + keyIndex * Integer.BYTES, 0);
        }
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
        ctxBuffer.putLong(traceIdOffset, Long.reverseBytes(trHi));
        ctxBuffer.putLong(traceIdOffset + 8, Long.reverseBytes(trLo));
        ctxBuffer.putLong(spanIdOffset, Long.reverseBytes(spanId));

        // Reset custom attribute state so the previous span's values don't leak
        // into this span. Callers set attributes again via setContextAttribute().
        for (int i = 0; i < MAX_CUSTOM_SLOTS; i++) {
            // offset into ctxBuffer for tag-encoding slot i
            ctxBuffer.putInt(TAG_ENCODINGS_OFFSET + i * Integer.BYTES, 0);
        }
        // Reset attrs_data_size to contain only the fixed LRS entry, discarding
        // any custom attribute entries written during the previous span.
        ctxBuffer.putShort(attrsDataSizeOffset, (short) LRS_ENTRY_SIZE);

        // Update LRS sidecar and OTEP attrs_data inside the detach/attach window so a
        // signal handler never sees the new LRS with old trace/span IDs.
        ctxBuffer.putLong(lrsOffset, localRootSpanId);
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
     *
     * <p>External OTEP readers see valid=0 and skip the record — they cannot distinguish
     * "cleared" from "being mutated". This is intentional: without also resetting
     * attrs_data_size here, publishing valid=1 with a stale attrs_data_size would expose
     * a partially-valid record. The cleared state is effectively invisible to external
     * readers until the next non-zero setContext call publishes it.
     */
    private void clearContextDirect() {
        ctxBuffer.putLong(traceIdOffset, 0);
        ctxBuffer.putLong(traceIdOffset + 8, 0);
        ctxBuffer.putLong(spanIdOffset, 0);
        writeLrsHex(0);
        for (int i = 0; i < MAX_CUSTOM_SLOTS; i++) {
            ctxBuffer.putInt(TAG_ENCODINGS_OFFSET + i * Integer.BYTES, 0);
        }
        ctxBuffer.putLong(lrsOffset, 0);
    }

    /**
     * Overwrite the 16 hex value bytes of the fixed LRS entry in-place.
     * The entry header (key_index=0, length=16) is pre-initialized and never touched.
     * Called between detach() and attach(); no allocation.
     */
    private void writeLrsHex(long val) {
        int base = attrsDataOffset + 2; // skip key_index byte + length byte
        for (int i = 15; i >= 0; i--) {
            ctxBuffer.put(base + i, HEX_DIGITS[(int)(val & 0xF)]);
            val >>>= 4;
        }
    }

    // ---- OTEP record helpers (called between detach/attach) ----

    /**
     * Invalidates the record (sets valid=0). Typically followed by attach(), but the
     * clear path intentionally leaves the record invalid without calling attach().
     */
    private void detach() {
        ctxBuffer.put(validOffset, (byte) 0);
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
        ctxBuffer.put(validOffset, (byte) 1);
    }

    /**
     * Replace or insert an attribute in attrs_data. Record must be detached.
     * Writes the pre-encoded UTF-8 bytes into the record.
     *
     * <p>Caller contract: {@code utf8.length <= MAX_VALUE_BYTES}, enforced at the public
     * entry point in {@link #setContextAttributeDirect}.
     */
    private boolean replaceOtepAttribute(int otepKeyIndex, byte[] utf8) {
        int currentSize = compactOtepAttribute(otepKeyIndex);
        int valueLen = utf8.length;
        int entrySize = 2 + valueLen;
        if (currentSize + entrySize <= maxAttrsDataSize) {
            int base = attrsDataOffset + currentSize;
            ctxBuffer.put(base, (byte) otepKeyIndex);
            ctxBuffer.put(base + 1, (byte) valueLen);
            for (int i = 0; i < valueLen; i++) {
                ctxBuffer.put(base + 2 + i, utf8[i]);
            }
            currentSize += entrySize;
            ctxBuffer.putShort(attrsDataSizeOffset, (short) currentSize);
            return true;
        }
        ctxBuffer.putShort(attrsDataSizeOffset, (short) currentSize);
        return false;
    }

    /** Remove an attribute from attrs_data by compacting. Record must be detached. */
    private void removeOtepAttribute(int otepKeyIndex) {
        int currentSize = compactOtepAttribute(otepKeyIndex);
        ctxBuffer.putShort(attrsDataSizeOffset, (short) currentSize);
    }

    /**
     * Scan attrs_data and compact out the entry with the given key_index.
     * Returns the new attrs_data size after compaction.
     *
     * <p>{@code otepKeyIndex} is always {@code keyIndex + 1} for user attributes,
     * so it is never 0. Index 0 is reserved for the fixed LRS entry.
     */
    private int compactOtepAttribute(int otepKeyIndex) {
        int currentSize = ctxBuffer.getShort(attrsDataSizeOffset) & 0xFFFF;
        int readPos = 0;
        int writePos = 0;
        boolean found = false;
        while (readPos + 2 <= currentSize) {
            int k = ctxBuffer.get(attrsDataOffset + readPos) & 0xFF;
            int len = ctxBuffer.get(attrsDataOffset + readPos + 1) & 0xFF;
            if (readPos + 2 + len > currentSize) { currentSize = writePos; break; }
            if (k == otepKeyIndex) {
                found = true;
                readPos += 2 + len;
            } else {
                if (found && writePos < readPos) {
                    for (int i = 0; i < 2 + len; i++) {
                        ctxBuffer.put(attrsDataOffset + writePos + i,
                            ctxBuffer.get(attrsDataOffset + readPos + i));
                    }
                }
                writePos += 2 + len;
                readPos += 2 + len;
            }
        }
        return found ? writePos : currentSize;
    }

    /**
     * Reads a custom attribute value by key index by scanning {@code attrs_data}.
     *
     * <p><b>Test-only.</b> The only caller is {@code TagContextTest}, which uses it via
     * {@link JavaProfiler#getThreadContext()} to verify that writes to the OTEP record are
     * observable after set / clear / span-reset cycles. No production path — neither the DD
     * signal handler nor the OTEL eBPF reader — ever calls this method: the DD handler reads
     * sidecar encoding IDs and the OTEL reader parses {@code attrs_data} directly from native
     * memory. The per-call {@code byte[]} / {@code String} allocation is therefore acceptable;
     * do not introduce a readback cache unless a real production consumer appears.
     *
     * @param keyIndex 0-based user key index (same as passed to setContextAttribute)
     * @return the attribute value string, or null if not set
     */
    public String readContextAttribute(int keyIndex) {
        if (keyIndex < 0 || keyIndex >= MAX_CUSTOM_SLOTS) {
            return null;
        }
        // valid=0 → record was detached or never published. No attrs_data to trust.
        if (ctxBuffer.get(validOffset) == 0) {
            return null;
        }
        int otepKeyIndex = keyIndex + 1;
        int size = ctxBuffer.getShort(attrsDataSizeOffset) & 0xFFFF;
        int pos = 0;
        while (pos + 2 <= size) {
            int k = ctxBuffer.get(attrsDataOffset + pos) & 0xFF;
            int len = ctxBuffer.get(attrsDataOffset + pos + 1) & 0xFF;
            if (pos + 2 + len > size) {
                break;
            }
            if (k == otepKeyIndex) {
                byte[] bytes = new byte[len];
                for (int i = 0; i < len; i++) {
                    bytes[i] = ctxBuffer.get(attrsDataOffset + pos + 2 + i);
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
            int b = ctxBuffer.get(traceIdOffset + i) & 0xFF;
            sb.append((char) HEX_DIGITS[b >> 4]);
            sb.append((char) HEX_DIGITS[b & 0xF]);
        }
        return sb.toString();
    }

    private static native int registerConstant0(String value);
}
