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
        return getInstance(libLocation, scratchDir, false, false);
    }

    /**
     * Get a {@linkplain JavaProfiler} instance with explicit feature flags.
     * @param libLocation the path to the native library, or {@literal null} to use the bundled one
     * @param scratchDir directory where the bundled library will be exploded before linking
     * @param delegateMonitorEvents when {@code true}, {@code Object.wait} TaskBlock events are
     *        emitted by Java instrumentation and native JVMTI wait callbacks are suppressed;
     *        synchronized monitor contention remains native-owned
     * @param wallPrecheck compatibility flag reserved for callers that pass wall-precheck
     *        capability at initialization time; recording behavior is controlled by the
     *        profiling command's {@code wallprecheck=true} option
     */
    public static synchronized JavaProfiler getInstance(String libLocation, String scratchDir,
            boolean delegateMonitorEvents, boolean wallPrecheck) throws IOException {
        if (instance != null) {
            return instance;
        }

        JavaProfiler profiler = new JavaProfiler();
        LibraryLoader.Result result = LibraryLoader.builder().withLibraryLocation(libLocation).withScratchDir(scratchDir).load();
        if (!result.succeeded) {
            throw new IOException("Failed to load Datadog Java profiler library", result.error);
        }
        init0(delegateMonitorEvents, wallPrecheck);

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
        return execute0(command);
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
     */
    public void setContext(long localRootSpanId, long spanId, long traceIdHigh, long traceIdLow) {
        currentContext().put(localRootSpanId, spanId, traceIdHigh, traceIdLow);
    }

    /**
     * Resets the current thread's context to zero (traceId=0, spanId=0, localRootSpanId=0).
     * Custom context attributes are also cleared.
     */
    public void clearContext() {
        currentContext().put(0, 0, 0, 0);
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
     */
    public boolean setContextAttribute(int offset, String value) {
        return currentContext().setContextAttribute(offset, value);
    }

    /**
     * Clears the custom context attribute at the given slot offset for the current thread.
     * Zeros the sidecar encoding and removes it from OTEP {@code attrs_data}.
     *
     * @param offset slot index (0-based, in [0, 9]); out-of-range values are silently ignored
     */
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
     */
    public boolean setContextAttributesByIdAndBytes(int[] constantIds, byte[][] utf8) {
        return currentContext().setContextAttributesByIdAndBytes(constantIds, utf8);
    }

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
     * Called before {@code LockSupport.park}. Captures the block-entry span context
     * and marks the thread as parked so wall-clock sampling can suppress duplicate
     * signals during the blocking interval.
     */
    void parkEnter() {
        parkEnter0();
    }

    /**
     * Called after {@code LockSupport.park}. Clears the parked flag and records a
     * {@code TaskBlock} event for eligible blocking intervals.
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
     * Clears a blocked interval and snapshots reconstruction metadata before native state is reset.
     *
     * @param token opaque token returned by {@link #blockEnter(int)}
     * @param snapshot output array: [callTraceId, correlationId, observedBlockingState]
     */
    public void blockExit(long token, long[] snapshot) {
        blockExitWithSnapshot0(token, snapshot);
    }

    /**
     * Get the ticks for the current thread.
     * @return ticks
     */
    public long getCurrentTicks() {
        return currentTicks0();
    }

    /**
     * Returns the OS-level thread ID (tid) of the calling thread.
     */
    public int getCurrentThreadId() {
        return getTid0();
    }

    /**
     * Reports whether native {@code Object.wait} TaskBlock callbacks were disabled in favor of
     * Java-owned wait instrumentation. Synchronized monitor contention remains native-owned.
     */
    public boolean isMonitorEventsDelegated() {
        return monitorEventsDelegated0();
    }

    /**
     * Returns the TSC frequency in Hz (ticks per second).
     */
    public long getTscFrequency() {
        return tscFrequency0();
    }

    /**
     * Records a TaskBlock event for the calling platform thread. Span context is read from
     * OTEP TLS inside native code (same as the queue-time pattern).
     *
     * @return {@code true} if the event was recorded; {@code false} if it was skipped by
     *         eligibility rules or could not be recorded
     */
    public boolean recordTaskBlock(long startTicks, long endTicks, long blocker, long unblockingSpanId) {
        return recordTaskBlock0(startTicks, endTicks, blocker, unblockingSpanId);
    }

    /**
     * Records a TaskBlock event for the calling profiled thread with an explicit span context.
     * Stack metadata is still attached from the calling thread.
     *
     * @return {@code true} if the event was recorded; {@code false} if it was skipped by
     *         eligibility rules or could not be recorded
     */
    public boolean recordTaskBlockWithContext(long startTicks, long endTicks, long blocker,
            long unblockingSpanId, long spanId, long rootSpanId) {
        return recordTaskBlockWithContext0(startTicks, endTicks, blocker, unblockingSpanId, spanId, rootSpanId);
    }

    /**
     * Attempts to record a TaskBlock event attributed to an explicit thread ID and explicit span
     * context. This overload has no stack-reference metadata, so a recorder thread cannot use it to
     * emit a self-contained TaskBlock on behalf of another thread.
     *
     * @return {@code true} if the event was recorded; {@code false} if it was skipped by
     *         eligibility rules or could not be recorded
     */
    public boolean recordTaskBlockFromContext(int tid, long startTicks, long endTicks,
            long blocker, long unblockingSpanId, long spanId, long rootSpanId) {
        return recordTaskBlockFromContext0(tid, startTicks, endTicks, blocker, unblockingSpanId, spanId, rootSpanId);
    }

    /**
     * Records a TaskBlock event with explicit thread, span context, and stack-reference metadata.
     * This is the required overload when recording from a background thread on behalf of {@code tid}.
     *
     * @return {@code true} if the event was recorded; {@code false} if it was skipped by
     *         eligibility rules or could not be recorded
     */
    public boolean recordTaskBlockFromContext(int tid, long startTicks, long endTicks,
            long blocker, long unblockingSpanId, long spanId, long rootSpanId,
            long callTraceId, long correlationId, int observedBlockingState) {
        return recordTaskBlockFromContextWithStackReference0(tid, startTicks, endTicks, blocker,
                unblockingSpanId, spanId, rootSpanId, callTraceId, correlationId,
                observedBlockingState);
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

    private static native boolean init0(boolean delegateMonitorEvents, boolean wallPrecheck);
    private native void stop0() throws IllegalStateException;
    private native String execute0(String command) throws IllegalArgumentException, IllegalStateException, IOException;

    private static native void filterThreadAdd0();
    private static native void filterThreadRemove0();

    private static native int getTid0();
    private static native boolean monitorEventsDelegated0();

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

    private static native void blockExitWithSnapshot0(long token, long[] snapshot);

    private static native long currentTicks0();

    private static native long tscFrequency0();

    private static native boolean recordTaskBlock0(long startTicks, long endTicks,
            long blocker, long unblockingSpanId);

    private static native boolean recordTaskBlockWithContext0(long startTicks, long endTicks,
            long blocker, long unblockingSpanId, long spanId, long rootSpanId);

    private static native boolean recordTaskBlockFromContext0(int tid, long startTicks, long endTicks,
            long blocker, long unblockingSpanId, long spanId, long rootSpanId);

    private static native boolean recordTaskBlockFromContextWithStackReference0(int tid, long startTicks,
            long endTicks, long blocker, long unblockingSpanId, long spanId, long rootSpanId,
            long callTraceId, long correlationId, int observedBlockingState);

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
     */
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
     * Resets the cached ThreadContext for the current storage slot — the calling thread in
     * {@link ContextStorageMode#THREAD}, or its current carrier in
     * {@link ContextStorageMode#CARRIER}. The next call to {@link #getThreadContext()}
     * or any {@code setContext} overload will re-create it with fresh OTEL TLS buffers.
     */
    public void resetThreadContext() {
        tlsContextStorage.remove();
    }
}
