/*
 * Copyright 2018 Andrei Pangin
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

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;

/**
 * Java API for in-process profiling. Serves as a wrapper around
 * java-profiler native library. This class is a singleton.
 * The first call to {@link #getInstance()} initiates loading of
 * libjavaProfiler.so.
 */
public final class JavaProfiler {
    static final class TSCFrequencyHolder {
        /**
         * TSC frequency required to convert ticks into seconds
         */
        static final long FREQUENCY = tscFrequency0();
    }
    private static JavaProfiler instance;

    // Storage for profiling context. Scoped to the carrier thread when available so a
    // mounted virtual thread resolves to its current carrier's OTEP record (the record the
    // sampler reads); falls back to plain thread-local storage otherwise. See
    // OtelContextStorage for the mode selection and the rationale.
    private final ThreadLocal<ThreadContext> tlsContextStorage = OtelContextStorage.create();

    // Process-wide value->(encoding, utf8) cache for the all-native context write path
    // (setTraceContext / setContextValue). See ContextValueCache. One instance on the singleton.
    private final ContextValueCache contextValueCache = new ContextValueCache();

    // Number of custom attribute slots on the all-native path. Must equal the native
    // DD_TAGS_CAPACITY (context.h); kept as a literal (not derived via JNI) because it bounds
    // array-slot checks that can run before the native library is loaded, and kept independent of
    // ThreadContext so the phase-3 removal of ThreadContext does not strand this constant. Drift
    // from the native value is caught at test time by MaxContextSlotsTest via maxContextSlots0().
    static final int MAX_CONTEXT_SLOTS = 10;

    /**
     * Returns the calling thread's (or, in carrier mode, its current carrier's)
     * {@link ThreadContext}, creating and caching it on first use. Replaces the previous
     * {@code ThreadLocal.withInitial(...)} supplier: a carrier-scoped storage instance is
     * built reflectively and cannot carry a supplier, so lazy initialization is done here.
     *
     * <p>Race-free without synchronization: a carrier runs at most one mounted virtual
     * thread at a time and this method has no blocking point, so no unmount can occur
     * mid-call. A redundant re-init could at worst produce a second {@link ThreadContext}
     * over the same carrier record, which is harmless.
     */
    private ThreadContext currentContext() {
        ThreadContext ctx = tlsContextStorage.get();
        if (ctx == null) {
            ctx = initializeThreadContext();
            tlsContextStorage.set(ctx);
        }
        return ctx;
    }

    private JavaProfiler() {
    }

    /**
     * Get a {@linkplain JavaProfiler} instance backed by the bundled native library and using
     * the default temp directory as the scratch where the bundled library will be exploded
     * before linking.
     */
    public static JavaProfiler getInstance() throws IOException {
        return getInstance(null, null);
    }

    /**
     * Get a {@linkplain JavaProfiler} instance backed by the bundled native library and using
     * the given directory as the scratch where the bundled library will be exploded
     * before linking.
     * @param scratchDir directory where the bundled library will be exploded before linking
     */
    public static JavaProfiler getInstance(String scratchDir) throws IOException {
        return getInstance(null, scratchDir);
    }

    /**
     * Get a {@linkplain JavaProfiler} instance backed by the given native library and using
     * the given directory as the scratch where the bundled library will be exploded
     * before linking.
     * @param libLocation the path to the native library to be used instead of the bundled one
     * @param scratchDir directory where the bundled library will be exploded before linking; ignored when 'libLocation' is {@literal null}
     */
    public static synchronized JavaProfiler getInstance(String libLocation, String scratchDir) throws IOException {
        if (instance != null) {
            return instance;
        }

        JavaProfiler profiler = new JavaProfiler();
        LibraryLoader.Result result = LibraryLoader.builder().withLibraryLocation(libLocation).withScratchDir(scratchDir).load();
        if (!result.succeeded) {
            throw new IOException("Failed to load Datadog Java profiler library", result.error);
        }
        init0();

        instance = profiler;

        String maxArenaValue = System.getProperty("ddprof.debug.malloc_arena_max");
        if (maxArenaValue != null) {
            try {
                mallocArenaMax0(Integer.parseInt(maxArenaValue));
            } catch (NumberFormatException e) {
                System.out.println("[WARN] Invalid value for ddprof.debug.malloc_arena_max: " + maxArenaValue + ". Expecting an integer.");
            }
        }

        return profiler;
    }

    /**
     * Stop profiling (without dumping results)
     *
     * @throws IllegalStateException If profiler is not running
     */
    public void stop() throws IllegalStateException {
        stop0();
    }

    /**
     * Get the number of samples collected during the profiling session
     *
     * @return Number of samples
     */
    public static native long getSamples();

    /**
     * Get profiler agent version, e.g. "1.0"
     *
     * @return Version string
     */
    public String getVersion() {
        try {
            return execute0("version");
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }

    public String getStatus() {
        return getStatus0();
    }

    /**
     * Execute an agent-compatible profiling command -
     * the comma-separated list of arguments described in arguments.cpp
     *
     * @param command Profiling command
     * @return The command result
     * @throws IllegalArgumentException If failed to parse the command
     * @throws IOException If failed to create output file
     */
    public String execute(String command) throws IllegalArgumentException, IllegalStateException, IOException {
        if (command == null) {
            throw new NullPointerException();
        }
        String result = execute0(command);
        // A fresh 'start' (ACTION_START) resets the native context-value Dictionary
        // (StringDictionary::clearAll), reassigning encodings. The native side sets a flag when it
        // does so; consume it here and drop the value cache so no stale encoding from the prior
        // session is reused. Driven by the already-parsed native action — no command re-parsing.
        // See ContextValueCache and Profiler::start.
        if (consumeContextDictionaryReset0()) {
            contextValueCache.clear();
        }
        return result;
    }

    /**
     * Records the completion of the trace root
     */
    public boolean recordTraceRoot(long rootSpanId, String endpoint, String operation, int sizeLimit) {
        return recordTrace0(rootSpanId, endpoint, operation, sizeLimit);
    }

    /**
     * Records the completion of the trace root
     */
    @Deprecated
    public boolean recordTraceRoot(long rootSpanId, String endpoint, int sizeLimit) {
        return recordTrace0(rootSpanId, endpoint, null, sizeLimit);
    }

    /**
     * Add the given thread to the set of profiled threads.
     * 'filter' option must be enabled to use this method.
     */
    public void addThread() {
        filterThreadAdd0();
    }

    /**
     * Remove the given thread to the set of profiled threads.
     * 'filter' option must be enabled to use this method.
     */
    public void removeThread() {
        filterThreadRemove0();
    }

    /**
     * Passing context identifier to a profiler. This ID is thread-local and is dumped in
     * the JFR output only. 0 is a reserved value for "no-context".
     *
     * <p>Note: {@code rootSpanId} maps to {@code localRootSpanId} internally. A synthetic
     * trace_id of {@code [0, spanId]} is written to the OTEP record. For correct W3C
     * trace ID interop use {@link #setContext(long, long, long, long)}.
     *
     * @param spanId Span identifier that should be stored for current thread
     * @param rootSpanId Local root span identifier (used for endpoint correlation)
     * @deprecated Use {@link #setContext(long, long, long, long)} for full OTEP interop.
     */
    @Deprecated
    public void setContext(long spanId, long rootSpanId) {
        currentContext().put(spanId, rootSpanId);
    }

    /**
     * Sets trace context with full 128-bit W3C trace ID, span ID, and local root span ID.
     *
     * @param localRootSpanId Local root span ID (for endpoint correlation)
     * @param spanId Span identifier
     * @param traceIdHigh Upper 64 bits of the 128-bit trace ID
     * @param traceIdLow Lower 64 bits of the 128-bit trace ID
     * @deprecated DirectByteBuffer path; use {@link #setTraceContext} (all-native). Removed in phase 3.
     */
    @Deprecated
    public void setContext(long localRootSpanId, long spanId, long traceIdHigh, long traceIdLow) {
        currentContext().put(localRootSpanId, spanId, traceIdHigh, traceIdLow);
    }

    /**
     * Resets the current thread's context to zero (traceId=0, spanId=0, localRootSpanId=0).
     * Custom context attributes are also cleared.
     *
     * @deprecated DirectByteBuffer path; use {@link #clearTraceContext} (all-native). Removed in phase 3.
     */
    @Deprecated
    public void clearContext() {
        currentContext().put(0, 0, 0, 0);
    }

    // ---- All-native context write API (OTEP #4947) --------------------------------------------
    // Provisional names (subject to dd-trace-java coordination). These resolve the current carrier's
    // OTEP record inside a single JNI call per operation — no cached DirectByteBuffer, so they are
    // race-free under virtual-thread migration (see the design note and setTraceContext0 et al.).
    // They coexist with the deprecated DirectByteBuffer path below; both write the same native
    // record, and no thread uses both at once.

    /**
     * Combined per-scope-activation write: full trace/span context plus up to two span-derived
     * attributes (e.g. operation and resource name), in one native call. A negative {@code slotN}
     * (or {@code null}/oversized {@code vN}) skips that attribute. Custom slots are reset first, so
     * this establishes a fresh per-span attribute set.
     *
     * @param rootSpanId  the local root span ID
     * @param spanId      the current span ID
     * @param traceIdHigh upper 64 bits of the 128-bit trace ID
     * @param traceIdLow  lower 64 bits of the 128-bit trace ID
     * @param slot0       first custom attribute slot index in {@code [0, MAX_CONTEXT_SLOTS)}, or
     *                    negative to skip this attribute
     * @param v0          value for {@code slot0}; {@code null} or oversized also skips
     * @param slot1       second custom attribute slot index in {@code [0, MAX_CONTEXT_SLOTS)}, or
     *                    negative to skip this attribute
     * @param v1          value for {@code v1}; {@code null} or oversized also skips
     * @throws IllegalArgumentException if {@code spanId} is 0 — this is the activation path and
     *         requires a real span; to clear the context use {@link #clearTraceContext()} — or if a
     *         non-negative {@code slotN} is {@code >= MAX_CONTEXT_SLOTS} (out of range)
     */
    public void setTraceContext(long rootSpanId, long spanId, long traceIdHigh, long traceIdLow,
                                int slot0, CharSequence v0, int slot1, CharSequence v1) {
        if (spanId == 0) {
            throw new IllegalArgumentException(
                    "spanId must be non-zero; use clearTraceContext() to clear the trace context");
        }
        requireActivationSlot(slot0);
        requireActivationSlot(slot1);
        ContextValueCache.Entry e0 = resolveContextValue(slot0, v0);
        ContextValueCache.Entry e1 = resolveContextValue(slot1, v1);
        setTraceContext0(rootSpanId, spanId, traceIdHigh, traceIdLow,
                e0 == null ? -1 : slot0, e0 == null ? 0 : e0.encoding, e0 == null ? null : e0.utf8,
                e1 == null ? -1 : slot1, e1 == null ? 0 : e1.encoding, e1 == null ? null : e1.utf8);
    }

    /** Combined per-scope-deactivation clear (replaces {@link #clearContext()} on the native path). */
    public void clearTraceContext() {
        clearTraceContext0();
    }

    /**
     * Sets a single custom attribute (sporadic instrumentation-driven attributes such as
     * {@code http.route}). Returns false — a normal "not applied" signal, not an error — if the
     * value is null, its UTF-8 exceeds 255 bytes, or the native Dictionary is full; on such a
     * failure the slot is cleared. An out-of-range {@code slot}, by contrast, is a caller
     * programming error and throws.
     *
     * @param slot  custom attribute slot index in {@code [0, MAX_CONTEXT_SLOTS)}
     * @param value the attribute value; {@code null} clears the slot
     * @return true if the value was written; false if it was null, oversized, or the Dictionary is
     *         full
     * @throws IllegalArgumentException if {@code slot} is out of range
     */
    public boolean setContextValue(int slot, CharSequence value) {
        requireValidSlot(slot);
        ContextValueCache.Entry e = value == null ? null : contextValueCache.resolve(value.toString());
        if (e == null) {
            clearContextValue0(slot);
            return false;
        }
        return setContextValue0(slot, e.encoding, e.utf8);
    }

    /**
     * Clears a single custom attribute slot on the native path.
     *
     * @param slot custom attribute slot index in {@code [0, MAX_CONTEXT_SLOTS)}
     * @throws IllegalArgumentException if {@code slot} is out of range
     */
    public void clearContextValue(int slot) {
        requireValidSlot(slot);
        clearContextValue0(slot);
    }

    /**
     * Copies the current thread's custom-attribute sidecar tag encodings into {@code out} (index =
     * slot), reading the native record directly — no {@link ThreadContext} / DirectByteBuffer, so it
     * does not reset the record. Unlike the deprecated DBB read path, this observes encodings written
     * through the all-native {@link #setContextValue} path. Introspection / test use; entries beyond
     * {@code MAX_CONTEXT_SLOTS} are left untouched.
     */
    public void copyContextTags(int[] out) {
        copyContextTags0(out);
    }

    // A negative activation slot is the documented "skip this attribute" sentinel (normal control
    // flow); a non-negative slot must be a valid index. An out-of-range (>= MAX_CONTEXT_SLOTS) slot
    // is a caller programming error, not a skip, so it fails loudly.
    private static void requireActivationSlot(int slot) {
        if (slot >= MAX_CONTEXT_SLOTS) {
            throw new IllegalArgumentException(
                    "slot " + slot + " out of range [0, " + MAX_CONTEXT_SLOTS + ")");
        }
    }

    // Requires a valid custom-attribute slot index. Unlike the activation path, there is no
    // negative "skip" sentinel here, so any out-of-range slot is a programming error.
    private static void requireValidSlot(int slot) {
        if (slot < 0 || slot >= MAX_CONTEXT_SLOTS) {
            throw new IllegalArgumentException(
                    "slot " + slot + " out of range [0, " + MAX_CONTEXT_SLOTS + ")");
        }
    }

    // Resolves an activation attribute for setTraceContext; null (skip) if the slot is negative
    // (skip sentinel), the value is null, or the value cannot be represented (oversized / Dictionary
    // full). A non-negative out-of-range slot is rejected earlier by requireActivationSlot, so it
    // never reaches here and never registers the value in the permanent native Dictionary.
    private ContextValueCache.Entry resolveContextValue(int slot, CharSequence value) {
        if (slot < 0 || value == null) {
            return null;
        }
        return contextValueCache.resolve(value.toString());
    }

    /**
     * Sets a custom context attribute at the given slot offset for the current thread.
     *
     * @param offset slot index (0-based, in [0, 9]); out-of-range values return {@code false}
     * @param value  the string value to record; {@code null} returns {@code false} without
     *               writing; an empty string is written as a zero-length entry (not a clear —
     *               use {@link #clearContextAttribute(int)} to remove a value)
     * @return true if the value was recorded; false if {@code offset} is out of range,
     *         {@code value} is null, the Dictionary is full, or {@code attrs_data} overflows
     *         for this slot
     * @deprecated DirectByteBuffer path; use {@link #setContextValue} (all-native). Removed in phase 3.
     */
    @Deprecated
    public boolean setContextAttribute(int offset, String value) {
        return currentContext().setContextAttribute(offset, value);
    }

    /**
     * Clears the custom context attribute at the given slot offset for the current thread.
     * Zeros the sidecar encoding and removes it from OTEP {@code attrs_data}.
     *
     * @param offset slot index (0-based, in [0, 9]); out-of-range values are silently ignored
     * @deprecated DirectByteBuffer path; use {@link #clearContextValue} (all-native). Removed in phase 3.
     */
    @Deprecated
    public void clearContextAttribute(int offset) {
        currentContext().clearContextAttribute(offset);
    }

    /**
     * Re-applies multiple custom attributes from precomputed constant IDs and UTF-8 bytes for
     * the current thread in a single detach/attach window.
     *
     * <ul>
     *   <li>Slots with {@code constantIds[i] <= 0} are skipped.</li>
     *   <li>Returns {@code false} without writing if the thread's record is not currently valid
     *       (span-less), to avoid resurrecting a cleared record.</li>
     *   <li>On {@code attrs_data} overflow, the overflowed slot's sidecar is zeroed and
     *       {@code false} is returned; slots written before the overflow are retained.</li>
     * </ul>
     *
     * @param constantIds per-slot Dictionary constant IDs; entries {@code <= 0} are skipped
     * @param utf8        per-slot UTF-8 value bytes; must be non-null and at most 255 bytes
     *                    (the OTEP attrs_data entry length field is one byte) for every slot
     *                    whose {@code constantId > 0}
     * @return true if every slot with {@code constantId > 0} was written; false on a cleared
     *         (span-less) record, or {@code attrs_data} overflow for any slot
     * @throws NullPointerException     if {@code constantIds}, {@code utf8}, or any active
     *                                  {@code utf8[i]} is null
     * @throws IllegalArgumentException if the arrays have different lengths, exceed the slot limit,
     *                                  or any active {@code utf8[i]} exceeds 255 bytes
     * @deprecated DirectByteBuffer path; unused by dd-trace-java. Removed in phase 3.
     */
    @Deprecated
    public boolean setContextAttributesByIdAndBytes(int[] constantIds, byte[][] utf8) {
        return currentContext().setContextAttributesByIdAndBytes(constantIds, utf8);
    }

    @Deprecated
    void copyTags(int[] snapshot) {
        currentContext().copyCustoms(snapshot);
    }

    /**
     * Dumps the JFR recording at the provided path
     * @param recording the path to the recording
     * @throws NullPointerException if recording is null
     */
    public void dump(Path recording) {
        dump0(recording.toAbsolutePath().toString());
    }

    /**
     * Records a datadog.ProfilerSetting event with no unit
     * @param name the name
     * @param value the value
     */
    public void recordSetting(String name, String value) {
        recordSetting(name, value, "");
    }

    /**
     * Records a datadog.ProfilerSetting event
     * @param name the name
     * @param value the value
     * @param unit the unit
     */
    public void recordSetting(String name, String value, String unit) {
        recordSettingEvent0(name, value, unit);
    }


    /**
     * Scales the ticks to milliseconds and applies a threshold
     */
    public boolean isThresholdExceeded(long thresholdMillis, long startTicks, long endTicks) {
        return endTicks - startTicks > thresholdMillis * TSCFrequencyHolder.FREQUENCY / 1000;
    }

    /**
     * Records when queueing ended
     * @param task the name of the enqueue task
     * @param scheduler the name of the thread-pool or executor scheduling the task
     * @param origin the thread the task was submitted on
     */
    public void recordQueueTime(long startTicks,
                                long endTicks,
                                Class<?> task,
                                Class<?> scheduler,
                                Class<?> queueType,
                                int queueLength,
                                Thread origin) {
        recordQueueEnd0(startTicks, endTicks, task.getName(), scheduler.getName(), origin, queueType.getName(), queueLength);
    }

    /**
     * Internal hook called before {@code LockSupport.park}. This remains package-scoped
     * until PR2 wires production TaskBlock instrumentation.
     */
    void parkEnter() {
        parkEnter0();
    }

    /**
     * Internal hook called after {@code LockSupport.park}. Clears the parked flag.
     * {@code blocker} and {@code unblockingSpanId} are reserved for PR2 TaskBlock use.
     */
    void parkExit(long blocker, long unblockingSpanId) {
        parkExit0(blocker, unblockingSpanId);
    }

    /**
     * Internal hook marking the current platform thread as entering an explicitly instrumented
     * blocked interval. This is not public API in this PR; production TaskBlock wiring lands in PR2.
     *
     * @param state native {@code OSThreadState} value for the blocked interval;
     *     currently only {@code SLEEPING} is armed
     * @return an opaque token to pass to {@link #blockExit(long)}, or 0 if no state was armed
     */
    long blockEnter(int state) {
        return blockEnter0(state);
    }

    /**
     * Clears a blocked interval previously armed by {@link #blockEnter(int)}.
     */
    void blockExit(long token) {
        blockExit0(token);
    }

    /**
     * Get the ticks for the current thread.
     * @return ticks
     */
    public long getCurrentTicks() {
        return currentTicks0();
    }

    /**
     * If the profiler is built in debug mode, returns counters recorded during profile execution.
     * These are for whitebox testing and not intended for production use.
     * @return a map of counters
     */
    public Map<String, Long> getDebugCounters() {
        Map<String, Long> counters = new HashMap<>();
        ByteBuffer buffer = getDebugCounters0().order(ByteOrder.LITTLE_ENDIAN);
        if (buffer.hasRemaining()) {
            String[] names = describeDebugCounters0();
            for (int i = 0; i < names.length && i * 128 < buffer.capacity(); i++) {
                counters.put(names[i], buffer.getLong(i * 128));
            }
        }
        return counters;
    }

    private static ThreadContext initializeThreadContext() {
        long[] metadata = new long[6];
        ByteBuffer buffer = initializeContextTLS0(metadata);
        if (buffer == null) {
            throw new IllegalStateException("Failed to initialize OTEL TLS — ProfiledThread not available");
        }
        return new ThreadContext(buffer, metadata);
    }

    private static native boolean init0();
    private native void stop0() throws IllegalStateException;
    private native String execute0(String command) throws IllegalArgumentException, IllegalStateException, IOException;

    private static native void filterThreadAdd0();
    private static native void filterThreadRemove0();

    private static native int getTid0();

    private static native boolean recordTrace0(long rootSpanId, String endpoint, String operation, int sizeLimit);

    private static native void dump0(String recordingFilePath);

    private static native ByteBuffer getDebugCounters0();

    private static native String[] describeDebugCounters0();

    private static native void recordSettingEvent0(String name, String value, String unit);

    private static native void recordQueueEnd0(long startTicks, long endTicks, String task, String scheduler, Thread origin, String queueType, int queueLength);

    private static native void parkEnter0();

    private static native void parkExit0(long blocker, long unblockingSpanId);

    private static native long blockEnter0(int state);

    private static native void blockExit0(long token);

    private static native long currentTicks0();

    private static native long tscFrequency0();

    private static native void mallocArenaMax0(int max);

    private static native String getStatus0();

    /**
     * Initializes context TLS for the current thread and returns a single DirectByteBuffer
     * spanning the OTEP record + tag-encoding sidecar + LRS (688 bytes, contiguous in
     * ProfiledThread). Sets otel_thread_ctx_v1 permanently to the thread's
     * OtelThreadContextRecord.
     *
     * @param metadata output array filled with absolute offsets into the returned buffer:
     *   [0] VALID_OFFSET — offset of 'valid' field
     *   [1] TRACE_ID_OFFSET — offset of 'trace_id' field
     *   [2] SPAN_ID_OFFSET — offset of 'span_id' field
     *   [3] ATTRS_DATA_SIZE_OFFSET — offset of 'attrs_data_size' field
     *   [4] ATTRS_DATA_OFFSET — offset of 'attrs_data' field
     *   [5] LRS_OFFSET — offset of local_root_span_id
     */
    private static native ByteBuffer initializeContextTLS0(long[] metadata);

    // All-native context write primitives (OTEP #4947). Each resolves the current carrier's record
    // inside the JNI call (which pins a mounted virtual thread to its carrier), so there is no
    // cached per-thread buffer to dangle. See the native implementations in javaApi.cpp and the
    // public API built on top of these. A negative slot skips that activation attribute.
    private static native void setTraceContext0(long localRootSpanId, long spanId, long traceIdHigh,
            long traceIdLow, int slot0, int enc0, byte[] utf0, int slot1, int enc1, byte[] utf1);
    private static native void clearTraceContext0();
    private static native boolean setContextValue0(int slot, int encoding, byte[] utf8);
    private static native void clearContextValue0(int slot);
    private static native void copyContextTags0(int[] out);

    /** Native DD_TAGS_CAPACITY (context.h). Test-only drift guard for {@link #MAX_CONTEXT_SLOTS}. */
    static native int maxContextSlots0();

    /**
     * Atomically reads and clears the native "context-value dictionary was reset" flag, set when a
     * fresh {@code start} resets the encoding Dictionary. Used by {@link #execute} to invalidate the
     * {@link ContextValueCache} without re-parsing the command in Java.
     */
    private static native boolean consumeContextDictionaryReset0();

    /**
     * Returns the {@link ThreadContext} for the current storage slot (the calling thread, or in
     * {@link ContextStorageMode#CARRIER} its current carrier).
     *
     * <p><b>Do not cache the returned instance across a point where the calling thread may be
     * unmounted and remounted on a different carrier</b> (any blocking operation on a virtual
     * thread). In carrier mode the returned context's buffer targets the carrier that was mounted
     * at call time; after migration it no longer corresponds to the current carrier's record — the
     * sampler reads the new carrier, and once the old carrier's OS thread exits the buffer dangles.
     * Callers that write context (span/attributes) should re-fetch per use — the {@code setContext*}
     * methods already do this internally via {@code currentContext()}.
     *
     * @deprecated DirectByteBuffer path (test/diagnostic only); the all-native API is stateless and
     *             exposes no per-thread handle. Removed in phase 3.
     */
    @Deprecated
    public ThreadContext getThreadContext() {
        return currentContext();
    }

    /**
     * Diagnostics/tests: the resolved OTEL context storage mode, as selected by
     * {@code -D}{@value OtelContextStorage#MODE_PROPERTY} and the availability of
     * {@code jdk.internal.misc.CarrierThreadLocal}.
     */
    public ContextStorageMode contextStorageMode() {
        return OtelContextStorage.modeOf(tlsContextStorage);
    }

// --- test and debug utility methods

    /**
     * Write the profiler TEST_LOG - the message will be in sequence with other profiler logs
     * @param msg the log message
     */
    public static native void testlog(String msg);

    public static native void dumpContext();

    /**
     * Test seam (debug native builds only - a no-op returning {@code false}/{@code 0}/an
     * empty array in release builds): decouples LivenessTracker's leak-candidate
     * detection from ReferenceChainTracker's chain reconstruction, each independently
     * verifiable end-to-end without depending on both the probabilistic JVMTI heap
     * sampler and the reference-chain BFS search organically producing the right
     * conditions in the same test run.
     * <p>
     * Enables/disables LivenessTracker's per-klass population tracking directly,
     * bypassing {@code initialize()}'s live-JVM requirement. Returns {@code true} on
     * debug builds.
     */
    public static native boolean setGcGenerationsEnabled0(boolean enabled);

    /**
     * Test seam (debug native builds only): seeds one epoch's worth of population
     * history for {@code klassId} directly into LivenessTracker's ring buffer,
     * bypassing real allocation sampling. Repeated calls (with distinct
     * {@code epoch} values) build up a trend {@link #selectLeakCandidateKlassIds0()}
     * can then rank, letting a test assert a slope signal would be generated for a
     * chosen klass id without waiting on real GC epochs.
     */
    public static native void seedKlassPopulationSample0(int klassId, int count, long epoch);

    /**
     * Test seam (debug native builds only): wires {@code representative} in as {@code klassId}'s
     * leak-candidate representative directly (a fresh weak global ref owned by LivenessTracker),
     * bypassing the real allocation-sampling path that would otherwise populate this. Combined
     * with {@link #seedKlassPopulationSample0} and {@link #tagAsReferenceChainRoot0}, lets a test
     * join a synthetic slope signal to a real, directly-tagged object so
     * {@link #pollReferenceChainTargets0()}'s bridging step can be exercised end-to-end with
     * neither the real sampler nor the real root-seeded walk involved.
     */
    public static native void setKlassPopulationRepresentativeForTest0(int klassId, Object representative);

    /**
     * Test seam (debug native builds only): clears LivenessTracker's per-klass population table,
     * so a later test in the same JVM does not observe leak candidates seeded by an earlier one.
     */
    public static native void resetKlassPopulationForTest0();

    /**
     * Test seam (debug native builds only): returns the klass ids LivenessTracker's
     * real leak-candidate ranking (positive population slope, top 5) currently
     * selects - the same call ReferenceChainTracker's restart gate and target-polling
     * bridge use in production, exposed here so a test can assert a slope signal was
     * generated (real or seeded via {@link #seedKlassPopulationSample0}) without
     * needing a reference-chain search to also be running.
     */
    public static native int[] selectLeakCandidateKlassIds0();

    /**
     * Test seam (debug native builds only): tags {@code target} and inserts it
     * directly as a reference-chain frontier root, bypassing ReferenceChainTracker's
     * normal discovery path (a root-seeded FollowReferences walk) and
     * LivenessTracker's leak-candidate selection entirely. Lets a test drive
     * {@link #runReferenceChainPass0()}/{@link #pollReferenceChainTargets0()} against
     * a known, caller-chosen live object. Returns the assigned frontier tag (matching
     * the {@code target_tag} a resulting {@code datadog.ReferenceChain} event
     * reports), or {@code 0} on failure (reference chains disabled, or the frontier
     * table is at capacity).
     */
    public static native long tagAsReferenceChainRoot0(Object target);

    /**
     * Test seam (debug native builds only): runs exactly one bounded BFS pass of the
     * reference-chain search synchronously, rather than waiting on the tracker's own
     * background thread/cadence. Returns {@code false} if reference chains are
     * disabled or the tracker was never started.
     */
    public static native boolean runReferenceChainPass0();

    /**
     * Test seam (debug native builds only): runs one poll of
     * ReferenceChainTracker's LivenessTracker-to-chain-reconstruction bridging step
     * synchronously - for each current leak candidate already discovered by a prior
     * {@link #runReferenceChainPass0()} walk, reconstructs and queues its chain
     * event, rather than waiting on the background thread's own scheduling cycle.
     */
    public static native void pollReferenceChainTargets0();

    /**
     * Test seam (debug native builds only): drains and returns the number of
     * reference-chain events queued by {@link #pollReferenceChainTargets0()} so far
     * (the same queue {@code Profiler.dump()} drains in production to write
     * {@code datadog.ReferenceChain} JFR events) - lets a test assert a chain was
     * actually reconstructed without needing a real JFR dump.
     */
    public static native int drainReferenceChainEventCount0();

    /**
     * Test seam (debug native builds only): resets ReferenceChainTracker's search/frontier state
     * back to a brand-new tracker's, releasing any tags a previous search still held. Since the
     * tracker is a process-wide singleton, an in-process test that needs its own genuine first
     * root-seeded walk (runPass() only re-walks from the roots once per search's whole lifetime)
     * calls this at the start of its test body to force one, rather than depending on being the
     * first reference-chain test to run in a shared test JVM.
     */
    public static native void resetReferenceChainSearchForTest0();

    /**
     * Test seam (debug native builds only): returns {@code VMStructs::isG1Active()} -
     * whether the attached JVM resolved {@code -XX:+UseG1GC} as its active collector
     * at {@code resolveOffsets()} time. Reference-chain search behavior does not yet
     * depend on this (the collector dispatch point in {@code ReferenceChainTracker::runPass()}
     * always takes the existing JVMTI path today); this seam only lets a test assert
     * the gate itself resolves correctly for whichever collector the test JVM was
     * launched with.
     */
    public static native boolean isG1ActiveForTest0();

    /**
     * Test seam (debug native builds only): runs {@code FieldWalker::walkOneHop()}
     * (referenceChainsWalker.h/.cpp) directly against {@code target}'s live oop-map/array
     * layout, bypassing JVMTI's {@code FollowReferences}-driven heap walk entirely - the
     * manual VMStructs field-walker this seam exercises is the traversal engine a later
     * (G1-only) integration phase wires into {@code ReferenceChainTracker}'s pass driver, not
     * yet anything {@link #runReferenceChainPass0()} calls. Returns the byte offset (instance
     * fields) or element index (object arrays) of every direct, non-null oop child discovered,
     * in walk order; an empty array for a primitive array, a klass with no oop-map, or when the
     * required VMStructs primitives ({@code FieldWalker::available()}) did not resolve on this
     * JVM. Internally wraps the raw-oop read in a minimal real {@code FollowReferences} call
     * so it only ever dereferences {@code target}'s oop while the VM is at the same
     * {@code VM_HeapWalkOperation} safepoint {@code heapReferenceCallback()}'s own raw-oop reads
     * already rely on - this seam is not itself safe to call outside that safepoint window.
     */
    public static native int[] walkOneHopForTest0(Object target);

    /**
     * Test seam (debug native builds only): returns {@code FieldWalker::available()} -
     * whether every VMStructs primitive {@code walkOneHopForTest0()} depends on (oop-map
     * blocks, array layout_helper decoding) resolved on the attached JVM. Not guaranteed
     * true on every vendor JDK distribution - callers of {@link #walkOneHopForTest0(Object)}
     * must check this first rather than assume availability.
     */
    public static native boolean fieldWalkerAvailableForTest0();

    /**
     * Test seam (debug native builds only): returns the raw VMStructs-derived layout numbers
     * {@code FieldWalker} depends on for {@code target}'s klass - {@code {vtableLength,
     * itableLength, oopMapCount, arrayHeaderSizeBytes, isObjectArrayKlass}} - each {@code -1} if
     * not applicable or not resolved. Exists so tests can assert sane bounds on the numbers
     * themselves (e.g. a header size of a few bytes, not hundreds), which catches a wrong
     * VMStructs field resolution or a units mistake (words vs. bytes) loudly and immediately,
     * even in cases where a walk driven by the wrong number would happen not to crash or
     * mis-count. Requires {@link #fieldWalkerAvailableForTest0()} to be true.
     */
    public static native int[] layoutSanityForTest0(Object target);

    /**
     * Resets the cached ThreadContext for the current storage slot — the calling thread in
     * {@link ContextStorageMode#THREAD}, or its current carrier in
     * {@link ContextStorageMode#CARRIER}. The next call to {@link #getThreadContext()}
     * or any {@code setContext} overload will re-create it with fresh OTEL TLS buffers.
     */
    public void resetThreadContext() {
        tlsContextStorage.remove();
    }
}
