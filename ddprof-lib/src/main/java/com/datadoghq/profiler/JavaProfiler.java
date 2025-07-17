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

import sun.misc.Unsafe;

import java.io.IOException;
import java.lang.reflect.Field;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * Java API for in-process profiling. Serves as a wrapper around
 * java-profiler native library. This class is a singleton.
 * The first call to {@link #getInstance()} initiates loading of
 * libjavaProfiler.so.
 */
public final class JavaProfiler {
    static final Unsafe UNSAFE;
    static {
        Unsafe unsafe = null;
        // a safety and testing valve to disable unsafe access
        if (!Boolean.getBoolean("ddprof.disable_unsafe")) {
            try {
                Field f = Unsafe.class.getDeclaredField("theUnsafe");
                f.setAccessible(true);
                unsafe = (Unsafe) f.get(null);
            } catch (Exception ignore) {
            }
        }
        UNSAFE = unsafe;
    }

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
        ActiveBitmap.initialize();

        profiler.initializeContextStorage();
        instance = profiler;

        return profiler;
    }

    private void initializeContextStorage() {
        if (this.contextStorage == null) {
            int maxPages = getMaxContextPages0();
            if (maxPages > 0) {
                if (UNSAFE != null) {
                    contextBaseOffsets = new long[maxPages];
                    // be sure to choose an illegal address as a sentinel value
                    Arrays.fill(contextBaseOffsets, Long.MIN_VALUE);
                } else {
                    contextStorage = new ByteBuffer[maxPages];
                }
            }
        }
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
    public native long getSamples();

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
        if (UNSAFE != null) {
            ActiveBitmap.setActive(TID.get(), true);
        } else {
            filterThread0(true);
        }
    }

    /**
     * Remove the given thread to the set of profiled threads.
     * 'filter' option must be enabled to use this method.
     */
    public void removeThread() {
        if (UNSAFE != null) {
            ActiveBitmap.setActive(TID.get(), false);
        } else {
            filterThread0(false);
        }
    }


    /**
     * Passing context identifier to a profiler. This ID is thread-local and is dumped in
     * the JFR output only. 0 is a reserved value for "no-context".
     *
     * @param spanId Span identifier that should be stored for current thread
     * @param rootSpanId Root Span identifier that should be stored for current thread
     */
    public void setContext(long spanId, long rootSpanId) {
        int tid = TID.get();
        if (UNSAFE != null) {
            setContextUnsafe(tid, spanId, rootSpanId);
        } else {
            setContextByteBuffer(tid, spanId, rootSpanId);
        }
    }

    private void setContextUnsafe(int tid, long spanId, long rootSpanId) {
        if (contextBaseOffsets == null) {
            return;
        }
        long pageOffset = getPageUnsafe(tid);
        if (pageOffset == 0) {
            return;
        }
        int index = (tid % PAGE_SIZE) * CONTEXT_SIZE;
        long base = pageOffset + index;
        UNSAFE.putLong(base + SPAN_OFFSET, spanId);
        UNSAFE.putLong(base + ROOT_SPAN_OFFSET, rootSpanId);
        UNSAFE.putLong(base + CHECKSUM_OFFSET, spanId ^ rootSpanId);
    }

    private void setContextByteBuffer(int tid, long spanId, long rootSpanId) {
        if (contextStorage == null) {
            return;
        }
        ByteBuffer page = getPage(tid);
        if (page == SENTINEL) {
            return;
        }
        int index = (tid % PAGE_SIZE) * CONTEXT_SIZE;
        page.putLong(index + SPAN_OFFSET, spanId);
        page.putLong(index + ROOT_SPAN_OFFSET, rootSpanId);
        page.putLong(index + CHECKSUM_OFFSET, spanId ^ rootSpanId);
    }

    private ByteBuffer getPage(int tid) {
        int pageIndex = tid / PAGE_SIZE;
        ByteBuffer page = contextStorage[pageIndex];
        if (page == null) {
            // the underlying page allocation is atomic so we don't care which view we have over it
            ByteBuffer buffer = getContextPage0(tid);
            if (buffer == null) {
                page = SENTINEL;
            } else {
                page = buffer.order(ByteOrder.LITTLE_ENDIAN);
            }
            contextStorage[pageIndex] = page;
        }
        return page;
    }

    private long getPageUnsafe(int tid) {
        int pageIndex = tid / PAGE_SIZE;
        long offset = contextBaseOffsets[pageIndex];
        if (offset == Long.MIN_VALUE) {
            contextBaseOffsets[pageIndex] = offset = getContextPageOffset0(tid);
        }
        return offset;
    }

    /**
     * Clears context identifier for current thread.
     */
    public void clearContext() {
        setContext(0, 0);
    }

    /**
     * Sets a context value
     * @param offset the offset
     * @param value the encoding of the value. Must have been encoded via @see JavaProfiler#registerConstant
     */
    public void setContextValue(int offset, int value) {
        int tid = TID.get();
        if (UNSAFE != null) {
            setContextUnsafe(tid, offset, value);
        } else {
            setContextByteBuffer(tid, offset, value);
        }
    }

    private void setContextUnsafe(int tid, int offset, int value) {
        if (contextBaseOffsets == null) {
            return;
        }
        long pageOffset = getPageUnsafe(tid);
        if (pageOffset == 0) {
            return;
        }
        UNSAFE.putInt(pageOffset + addressOf(tid, offset), value);
    }

    public void setContextByteBuffer(int tid, int offset, int value) {
        if (contextStorage == null) {
            return;
        }
        ByteBuffer page = getPage(tid);
        if (page == SENTINEL) {
            return;
        }
        page.putInt(addressOf(tid, offset), value);
    }

    void copyTags(int[] snapshot) {
        int tid = TID.get();
        if (UNSAFE != null) {
            copyTagsUnsafe(tid, snapshot);
        } else {
            copyTagsByteBuffer(tid, snapshot);
        }
    }

    void copyTagsUnsafe(int tid, int[] snapshot) {
        if (contextBaseOffsets == null) {
            return;
        }
        long pageOffset = getPageUnsafe(tid);
        if (pageOffset == 0) {
            return;
        }
        long address = pageOffset + addressOf(tid, 0);
        for (int i = 0; i < snapshot.length; i++) {
            snapshot[i] = UNSAFE.getInt(address);
            address += Integer.BYTES;
        }
    }

    void copyTagsByteBuffer(int tid, int[] snapshot) {
        if (contextStorage == null) {
            return;
        }
        ByteBuffer page = getPage(tid);
        if (page == SENTINEL) {
            return;
        }
        int address = addressOf(tid, 0);
        for (int i = 0; i < snapshot.length; i++) {
            snapshot[i] = page.getInt(address + i * Integer.BYTES);
        }
    }

    private static int addressOf(int tid, int offset) {
        return ((tid % PAGE_SIZE) * CONTEXT_SIZE + DYNAMIC_TAGS_OFFSET)
                // TODO - we want to limit cardinality and a great way to enforce that is with the size of these
                //  fields to a smaller type, say, u16. This would also allow us to pack more data into each thread's
                //  slot. However, the current implementation of the dictionary trades monotonicity and minimality for
                //  space, so imposing a limit of 64K values does not impose a limit on the number of bits required per
                //  value. Condensing this mapping would also result in savings in varint encoded event sizes.
                + offset * Integer.BYTES;
    }

    /**
     * Registers a constant so that its encoding can be used in place of the string
     * @param key the key to be written into the attribute value constant pool
     */
    int registerConstant(String key) {
        return registerConstant0(key);
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

    private static native boolean init0();
    private native void stop0() throws IllegalStateException;
    private native String execute0(String command) throws IllegalArgumentException, IllegalStateException, IOException;
    private native void filterThread0(boolean enable);

    private static native int getTid0();
    private static native ByteBuffer getContextPage0(int tid);
    // this is only here because ByteBuffer.putLong splits its argument into 8 bytes
    // before performing the write, which makes it more likely that writing the context
    // will be interrupted by the signal, leading to more rejected context values on samples
    // ByteBuffer is simpler and fit for purpose on modern JDKs
    private static native long getContextPageOffset0(int tid);
    private static native int getMaxContextPages0();

    private static native boolean recordTrace0(long rootSpanId, String endpoint, String operation, int sizeLimit);

    private static native int registerConstant0(String value);

    private static native void dump0(String recordingFilePath);

    private static native ByteBuffer getDebugCounters0();

    private static native String[] describeDebugCounters0();

    private static native void recordSettingEvent0(String name, String value, String unit);

    private static native void recordQueueEnd0(long startTicks, long endTicks, String task, String scheduler, Thread origin, String queueType, int queueLength);

    private static native long currentTicks0();

    private static native long tscFrequency0();

    private static native void mallocArenaMax0(int max);

    private static native String getStatus0();
}
