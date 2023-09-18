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
import java.io.InputStream;
import java.lang.reflect.Field;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
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
    private static final String NATIVE_LIBS = "/META-INF/native-libs";
    private static final String LIBRARY_NAME = "libjavaProfiler." + (OperatingSystem.current() == OperatingSystem.macos ? "dylib" : "so");
    
    private static final Unsafe UNSAFE;
    static {
        Unsafe unsafe = null;
        String version = System.getProperty("java.version");
        if (version.startsWith("1.8")) {
            try {
                Field f = Unsafe.class.getDeclaredField("theUnsafe");
                f.setAccessible(true);
                unsafe = (Unsafe) f.get(null);
            } catch (Exception ignore) { }
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
        Path libraryPath = null;
        if (libLocation == null) {
            OperatingSystem os = OperatingSystem.current();
            String qualifier = (os == OperatingSystem.linux && isMusl()) ? "musl" : null;

            libraryPath = libraryFromClasspath(os, Arch.current(), qualifier, Paths.get(scratchDir != null ? scratchDir : System.getProperty("java.io.tmpdir")));
            libLocation = libraryPath.toString();
        }
        System.load(libLocation);
        Files.deleteIfExists(libraryPath == null ? Paths.get(libLocation) : libraryPath);
        profiler.initializeContextStorage();
        instance = profiler;
        return profiler;
    }

    /**
     * Locates a library on class-path (eg. in a JAR) and creates a publicly accessible temporary copy
     * of the library which can then be used by the application by its absolute path.
     *
     * @param os The operating system
     * @param arch The architecture
     * @param qualifier An optional qualifier (eg. musl)
     * @param tempDir The working scratch dir where to store the temp library file
     * @return The library absolute path. The caller should properly dispose of the file once it is
     *     not needed. The file is marked for 'delete-on-exit' so it won't survive a JVM restart.
     * @throws IOException, IllegalStateException if the resource is not found on the classpath
     */
    private static Path libraryFromClasspath(OperatingSystem os, Arch arch, String qualifier, Path tempDir) throws IOException {
        String resourcePath = NATIVE_LIBS + "/" + os.name().toLowerCase() + "-" + arch.name().toLowerCase() + ((qualifier != null && !qualifier.isEmpty()) ? "-" + qualifier : "") + "/" + LIBRARY_NAME;
        
        InputStream libraryData =  JavaProfiler.class.getResourceAsStream(resourcePath);

        if (libraryData != null) {
            Path libFile = Files.createTempFile(tempDir, "libjavaProfiler", ".so");
            Files.copy(libraryData, libFile, StandardCopyOption.REPLACE_EXISTING);
            libFile.toFile().deleteOnExit();
            return libFile;
        }
        throw new IllegalStateException(resourcePath + " not found on classpath");
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
    public boolean recordTraceRoot(long rootSpanId, String endpoint, int sizeLimit) {
        return recordTrace0(rootSpanId, endpoint, sizeLimit);
    }

    /**
     * Add the given thread to the set of profiled threads.
     * 'filter' option must be enabled to use this method.
     */
    public void addThread() {
        filterThread0(true);
    }

    /**
     * Remove the given thread to the set of profiled threads.
     * 'filter' option must be enabled to use this method.
     */
    public void removeThread() {
        filterThread0(false);
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
            setContextJDK8(tid, spanId, rootSpanId);
        } else {
            setContextByteBuffer(tid, spanId, rootSpanId);
        }
    }

    private void setContextJDK8(int tid, long spanId, long rootSpanId) {
        if (contextBaseOffsets == null) {
            return;
        }
        long pageOffset = getPageUnsafe(tid);
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
            contextStorage[pageIndex] = page = getContextPage0(tid).order(ByteOrder.LITTLE_ENDIAN);
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
            setContextJDK8(tid, offset, value);
        } else {
            setContextByteBuffer(tid, offset, value);
        }
    }

    private void setContextJDK8(int tid, int offset, int value) {
        if (contextBaseOffsets == null) {
            return;
        }
        long pageOffset = getPageUnsafe(tid);
        UNSAFE.putInt(pageOffset + addressOf(tid, offset), value);
    }

    public void setContextByteBuffer(int tid, int offset, int value) {
        if (contextStorage == null) {
            return;
        }
        ByteBuffer page = getPage(tid);
        page.putInt(addressOf(tid, offset), value);
    }

    void copyTags(int[] snapshot) {
        int tid = TID.get();
        if (UNSAFE != null) {
            copyTagsJDK8(tid, snapshot);
        } else {
            copyTagsByteBuffer(tid, snapshot);
        }
    }

    void copyTagsJDK8(int tid, int[] snapshot) {
        if (contextBaseOffsets == null) {
            return;
        }
        long pageOffset = getPageUnsafe(tid);
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
    public void recordQueueTime(long startTicks, long endTicks, Class<?> task, Class<?> scheduler,
                               Thread origin) {
        recordQueueEnd0(startTicks, endTicks, task.getName(), scheduler.getName(), origin);
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

    /**
     * There is information about the linking in the ELF file. Since properly parsing ELF is not
     * trivial this code will attempt a brute-force approach and will scan the first 4096 bytes
     * of the 'java' program image for anything prefixed with `/ld-` - in practice this will contain
     * `/ld-musl` for musl systems and probably something else for non-musl systems (eg. `/ld-linux-...`).
     * However, if such string is missing should indicate that the system is not a musl one.
     */
    private static boolean isMusl() throws IOException {
        
        byte[] magic = new byte[]{(byte)0x7f, (byte)'E', (byte)'L', (byte)'F'};
        byte[] prefix = new byte[]{(byte)'/', (byte)'l', (byte)'d', (byte)'-'}; // '/ld-*'
        byte[] musl = new byte[]{(byte)'m', (byte)'u', (byte)'s', (byte)'l'}; // 'musl'

        Path binary = Paths.get(System.getProperty("java.home"), "bin", "java");
        byte[] buffer = new byte[4096];

        try (InputStream  is = Files.newInputStream(binary)) {
            int read = is.read(buffer, 0, 4);
            if (read != 4 || !containsArray(buffer, 0, magic)) {
                throw new IOException(Arrays.toString(buffer));
            }
            read = is.read(buffer);
            if (read <= 0) {
                throw new IOException();
            }
            int prefixPos = 0;
            for (int i = 0; i < read; i++) {
                if (buffer[i] == prefix[prefixPos]) {
                    if (++prefixPos == prefix.length) {
                        return containsArray(buffer, i + 1, musl);
                    }
                } else {
                    prefixPos = 0;
                }
            }
        }
        return false;
    }

    private static boolean containsArray(byte[] container, int offset, byte[] contained) {
        for (int i = 0; i < contained.length; i++) {
            int leftPos = offset + i;
            if (leftPos >= container.length) {
                return false;
            }
            if (container[leftPos] != contained[i]) {
                return false;
            }
        }
        return true;
    }

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

    private static native boolean recordTrace0(long rootSpanId, String endpoint, int sizeLimit);

    private static native int registerConstant0(String value);

    private static native void dump0(String recordingFilePath);

    private static native ByteBuffer getDebugCounters0();

    private static native String[] describeDebugCounters0();

    private static native void recordSettingEvent0(String name, String value, String unit);

    private static native void recordQueueEnd0(long startTicks, long endTicks, String task, String scheduler, Thread origin);

    private static native long currentTicks0();

    private static native long tscFrequency0();
}
