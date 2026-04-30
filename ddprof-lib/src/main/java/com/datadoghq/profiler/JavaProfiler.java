/*
 * Copyright 2018 Andrei Pangin
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

    // Thread-local storage for profiling context
    private final ThreadLocal<ThreadContext> tlsContextStorage = ThreadLocal.withInitial(JavaProfiler::initializeThreadContext);

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
        tlsContextStorage.get().put(spanId, rootSpanId);
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
        tlsContextStorage.get().put(localRootSpanId, spanId, traceIdHigh, traceIdLow);
    }

    /**
     * Resets the current thread's context to zero (traceId=0, spanId=0, localRootSpanId=0).
     * Custom context attributes are also cleared.
     */
    public void clearContext() {
        tlsContextStorage.get().put(0, 0, 0, 0);
    }

    public boolean setContextAttribute(int offset, String value) {
        return tlsContextStorage.get().setContextAttribute(offset, value);
    }

    public void clearContextAttribute(int offset) {
        tlsContextStorage.get().clearContextAttribute(offset);
    }

    void copyTags(int[] snapshot) {
        tlsContextStorage.get().copyCustoms(snapshot);
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
     * Records a {@code datadog.TaskBlock} interval for the current thread (direct API).
     *
     * @param startTicks TSC tick at block start
     * @param endTicks TSC tick at block end
     * @param spanId active span id when blocking began
     * @param rootSpanId active local root span id when blocking began
     * @param blocker blocker identity (e.g. monitor hash), or 0
     * @param unblockingSpanId span id of unblocking thread, or 0
     */
    public void recordTaskBlock(long startTicks,
                                long endTicks,
                                long spanId,
                                long rootSpanId,
                                long blocker,
                                long unblockingSpanId) {
        recordTaskBlock0(startTicks, endTicks, spanId, rootSpanId, blocker, unblockingSpanId);
    }

    /**
     * Called before {@code LockSupport.park}; native wall-clock sampling may skip SIGVTALRM for this interval.
     */
    public void parkEnter(long spanId, long rootSpanId) {
        parkEnter0(spanId, rootSpanId);
    }

    /**
     * Called after {@code LockSupport.park}; clears parked state and may emit {@code datadog.TaskBlock}.
     */
    public void parkExit(long blocker, long unblockingSpanId) {
        parkExit0(blocker, unblockingSpanId);
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

    private static native void recordTaskBlock0(long startTicks, long endTicks, long spanId, long rootSpanId, long blocker, long unblockingSpanId);

    private static native void parkEnter0(long spanId, long rootSpanId);

    private static native void parkExit0(long blocker, long unblockingSpanId);

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

    public ThreadContext getThreadContext() {
        return tlsContextStorage.get();
    }

// --- test and debug utility methods

    /**
     * Write the profiler TEST_LOG - the message will be in sequence with other profiler logs
     * @param msg the log message
     */
    public static native void testlog(String msg);

    public static native void dumpContext();

    /**
     * Resets the cached ThreadContext for the current thread.
     * The next call to {@link #getThreadContext()} or any {@code setContext} overload
     * will re-create it with fresh OTEL TLS buffers.
     */
    public void resetThreadContext() {
        tlsContextStorage.remove();
    }
}
