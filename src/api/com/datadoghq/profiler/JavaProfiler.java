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
import java.util.Arrays;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Java API for in-process profiling. Serves as a wrapper around
 * java-profiler native library. This class is a singleton.
 * The first call to {@link #getInstance()} initiates loading of
 * libjavaProfiler.so.
 */
public final class JavaProfiler {

    private static final int PROVENANCE = ThreadLocalRandom.current().nextInt();

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
    private final AtomicInteger tagOffset = new AtomicInteger(0);

    private JavaProfiler() {
    }

    public static JavaProfiler getInstance() {
        return getInstance(null);
    }

    public static synchronized JavaProfiler getInstance(String libPath) {
        if (instance != null) {
            return instance;
        }

        JavaProfiler profiler = new JavaProfiler();
        if (libPath != null) {
            System.load(libPath);
        } else {
            try {
                // No need to load library, if it has been preloaded with -agentpath
                profiler.getVersion();
            } catch (UnsatisfiedLinkError e) {
                System.loadLibrary("javaProfiler");
            }
        }
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
     *
     * @param tid native thread id to include in profiling
     */
    public void addThread(int tid) {
        filterThread0(tid, true);
    }

    /**
     * Remove the given thread to the set of profiled threads.
     * 'filter' option must be enabled to use this method.
     *
     * @param tid native thread id to remove from profiling
     */
    public void removeThread(int tid) {
        filterThread0(tid, false);
    }


    /**
     * Passing context identifier to a profiler. This ID is thread-local and is dumped in
     * the JFR output only. 0 is a reserved value for "no-context".
     *
     * @param spanId Span identifier that should be stored for current thread
     * @param rootSpanId Root Span identifier that should be stored for current thread
     */
    public void setContext(long spanId, long rootSpanId) {
        setContext(TID.get(), spanId, rootSpanId);
    }

    /**
     * Passing context identifier to a profiler. This ID is thread-local and is dumped in
     * the JFR output only. 0 is a reserved value for "no-context".
     *
     * @param tid the native thread id
     * @param spanId Span identifier that should be stored for current thread
     * @param rootSpanId Root Span identifier that should be stored for current thread
     */
    public void setContext(int tid, long spanId, long rootSpanId) {
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

    /**
     * Clears context identifier for current thread.
     */
    public void clearContext() {
        clearContext(TID.get());
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
     * Clears context identifier for the given thread id.
     * @param tid the native thread id
     */
    public void clearContext(int tid) {
        setContext(tid, 0, 0);
    }

    /**
     * Sets a context value
     * @param tid the thread the context is associated with
     * @param attribute the attribute, must have been registered via @see JavaProfiler#registerContextAttribute
     * @param value the encoding of the value. Must have been encoded via @see JavaProfiler#registerContextValue
     */
    public void setContextValue(int tid, ContextAttribute attribute, int value) {
        if (UNSAFE != null) {
            setContextJDK8(tid, attribute, value);
        } else {
            setContextByteBuffer(tid, attribute, value);
        }
    }

    private void setContextJDK8(int tid, ContextAttribute attribute, int value) {
        if (contextBaseOffsets == null) {
            return;
        }
        long pageOffset = getPageUnsafe(tid);
        UNSAFE.putLong(pageOffset + addressOf(tid, attribute), pack(attribute, value));
    }

    public void setContextByteBuffer(int tid, ContextAttribute attribute, int value) {
        if (contextStorage == null) {
            return;
        }
        ByteBuffer page = getPage(tid);

        page.putLong(addressOf(tid, attribute), pack(attribute, value));
    }

    private static long pack(ContextAttribute attribute, int value) {
        return ((long) attribute.encoding << 32) | value;
    }

    private static int addressOf(int tid, ContextAttribute attribute) {
        if (attribute.provenance != PROVENANCE) {
            throw new IllegalStateException("context attribute not registered with profiler");
        }
        return ((tid % PAGE_SIZE) * CONTEXT_SIZE + DYNAMIC_TAGS_OFFSET)
                // TODO - we want to limit cardinality and a great way to enforce that is with the size of these
                //  fields to a smaller type, say, u16. This would also allow us to pack more data into each thread's
                //  slot. However, the current implementation of the dictionary trades monotonicity and minimality for
                //  space, so imposing a limit of 64K values does not impose a limit on the number of bits required per
                //  value. Condensing this mapping would also result in savings in varint encoded event sizes.
                //
                // TODO - for now we just embed the tag attribute and value next to each other in the slot, which is
                //  very wasteful (this limits us to 5 tags in total but we use 32 bits to represent the tag name)
                //  but this is much simpler than implementing suitable global storage to associate slots
                //  with an attribute - this will be done in a second iteration.
                + attribute.offset * Long.BYTES;
    }

    // can be increased to 10 if the attribute labels are stored elsewhere,
    // or further by limiting to 16 bits per value
    // FIXME must be kept in sync with context.h
    private static final int TAGS_STORAGE_LIMIT = 2;

    /**
     * Registers an attribute which can be used later to set context
     * @param attribute the name of the attribute
     * @return the tag if registration is possible, otherwise null
     */
    public ContextAttribute registerContextAttribute(CharSequence attribute) {
        int encoding = registerContextAttribute0(attribute.toString(), TAGS_STORAGE_LIMIT);
        if (encoding >= 0) {
            int offset = tagOffset.getAndIncrement();
            if (offset < TAGS_STORAGE_LIMIT) {
                return new ContextAttribute(PROVENANCE, offset, encoding, attribute);
            }
        }
        return null;
    }

    /**
     * Registers a value and returns an encoding which can be used to refer
     * to the value in the future
     * @param value the value to record
     * @return the encoding to use to refer to the value when setting context
     */
    public int registerContextValue(CharSequence value) {
        return registerContextValue0(value.toString());
    }

    public int getNativeThreadId() {
        return getTid0();
    }

    private native void stop0() throws IllegalStateException;
    private native String execute0(String command) throws IllegalArgumentException, IllegalStateException, IOException;
    private native void filterThread0(int tid, boolean enable);

    private static native int getTid0();
    private static native ByteBuffer getContextPage0(int tid);
    // this is only here because ByteBuffer.putLong splits its argument into 8 bytes
    // before performing the write, which makes it more likely that writing the context
    // will be interrupted by the signal, leading to more rejected context values on samples
    // ByteBuffer is simpler and fit for purpose on modern JDKs
    private static native long getContextPageOffset0(int tid);
    private static native int getMaxContextPages0();

    private static native boolean recordTrace0(long rootSpanId, String endpoint, int sizeLimit);

    private static native int registerContextAttribute0(String attribute, int limit);

    private static native int registerContextValue0(String value);
}
