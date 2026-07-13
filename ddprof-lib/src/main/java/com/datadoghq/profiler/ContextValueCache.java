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

import java.nio.charset.StandardCharsets;
import java.util.concurrent.atomic.AtomicReferenceArray;

/**
 * Process-wide cache resolving an attribute value to its {@code (encoding, utf8)} pair for the
 * all-native context write path, avoiding a JNI {@code registerConstant0} call on every write.
 *
 * <p>Within a single recording session the encoding is a <em>stable</em> ID: {@code registerConstant0}
 * interns the value in the native Dictionary and returns the same ID for the life of that session.
 * That stability is what makes a single shared, lock-free cache correct without per-thread copies:
 * <ul>
 *   <li>Entries are immutable and published atomically (one array slot store), so a concurrent
 *       reader never sees a torn {@code (key, encoding, utf8)}.</li>
 *   <li>A miss just calls {@code registerConstant0} again — idempotent, returns the same encoding —
 *       and re-stores an equivalent entry; racing writers converge (last write wins, all correct).</li>
 *   <li>Direct-mapped by {@code value.hashCode()}; a hash collision evicts the previous value, which
 *       is simply re-resolved on its next use.</li>
 * </ul>
 *
 * <p><b>Session boundary:</b> the encoding is stable only <em>within</em> a recording session. A
 * fresh {@code start} (native {@code Profiler::start} with reset) calls
 * {@code StringDictionary::clearAll()}, which resets the ID counter, so encodings from the previous
 * session become stale. {@link JavaProfiler} therefore calls {@link #clear()} on every {@code start}
 * command; a subsequent {@link #resolve} re-registers the value and re-caches its new encoding.
 *
 * <p>Replaces the per-{@link ThreadContext} value cache: in the all-native model there is no
 * per-thread {@code ThreadContext} instance to host it, and a global cache avoids duplicating the
 * table across every carrier / virtual thread.
 */
final class ContextValueCache {

    /** Max UTF-8 byte length for a value (the OTEP attrs_data entry length field is one byte). */
    static final int MAX_VALUE_BYTES = 255;

    private static final int SIZE = 256;
    private static final int MASK = SIZE - 1;

    /** Immutable resolved value; published as a single atomic array-slot store. */
    static final class Entry {
        final String key;
        final int encoding;
        final byte[] utf8;

        Entry(String key, int encoding, byte[] utf8) {
            this.key = key;
            this.encoding = encoding;
            this.utf8 = utf8;
        }
    }

    private final AtomicReferenceArray<Entry> table = new AtomicReferenceArray<>(SIZE);

    /**
     * Resolves {@code value} to its cached {@code (encoding, utf8)} pair, registering it on a miss.
     *
     * @return the entry, or {@code null} if the value cannot be represented — {@code null} input, a
     *         UTF-8 encoding longer than {@value #MAX_VALUE_BYTES} bytes, or a full native Dictionary
     *         (encoding {@code < 0}). Callers treat {@code null} as "no attribute" (skip / clear).
     */
    Entry resolve(String value) {
        if (value == null) {
            return null;
        }
        int slot = value.hashCode() & MASK;
        Entry e = table.get(slot);
        if (e != null && value.equals(e.key)) {
            return e; // hit — no JNI
        }
        // Miss: encode + validate size before touching the Dictionary (a rejected value must not
        // create an orphan Dictionary entry).
        byte[] utf8 = value.getBytes(StandardCharsets.UTF_8);
        if (utf8.length > MAX_VALUE_BYTES) {
            return null;
        }
        int encoding = ThreadContext.registerConstant0(value);
        if (encoding < 0) {
            return null; // Dictionary full
        }
        Entry ne = new Entry(value, encoding, utf8);
        table.set(slot, ne); // benign race: converges on an equivalent entry
        return ne;
    }

    /**
     * Drops all cached entries. Called when a fresh recording session starts and the native
     * Dictionary is reset, so stale encodings from the previous session are not reused. A concurrent
     * {@link #resolve} racing this simply observes a miss and re-registers the value against the new
     * Dictionary — correct, just an extra {@code registerConstant0} call.
     */
    void clear() {
        for (int i = 0; i < SIZE; i++) {
            table.set(i, null);
        }
    }
}
