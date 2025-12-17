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
    private static final int CONTEXT_SIZE = 64;
    // must be kept in sync with PAGE_SIZE in context.h
    private static final int PAGE_SIZE = 1024;
    private static final int SPAN_OFFSET = 0;
    private static final int ROOT_SPAN_OFFSET = 8;
    private static final int CHECKSUM_OFFSET = 16;
    private static final int DYNAMIC_TAGS_OFFSET = 24;
    private static final ThreadLocal<Integer> TID = ThreadLocal.withInitial(JavaProfiler::getTid0);

    private ByteBuffer[] contextStorage;
    private long[] contextBaseOffsets;
    private static final ByteBuffer SENTINEL = ByteBuffer.allocate(0);

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
     * @param spanId Span identifier that should be stored for current thread
     * @param rootSpanId Root Span identifier that should be stored for current thread
     */
    public void setContext(long spanId, long rootSpanId) {
        tlsContextStorage.get().put(spanId, rootSpanId);
    }

    /**
     * Clears context identifier for current thread.
     */
    public void clearContext() {
        setContext(0, 0);
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
        initializeContextTls0();
        return new ThreadContext();
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

    private static native long currentTicks0();

    private static native long tscFrequency0();

    private static native void mallocArenaMax0(int max);

    private static native String getStatus0();

    private static native void initializeContextTls0();

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
}
