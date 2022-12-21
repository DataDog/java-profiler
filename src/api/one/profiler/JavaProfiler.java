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

package one.profiler;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.file.Files;
import java.nio.file.Path;

/**
 * Java API for in-process profiling. Serves as a wrapper around
 * java-profiler native library. This class is a singleton.
 * The first call to {@link #getInstance()} initiates loading of
 * libjavaProfiler.so.
 */
public final class JavaProfiler {
    private static JavaProfiler instance;
    private static final int CONTEXT_SIZE = 64;
    // must be kept in sync with PAGE_SIZE in context.h
    private static final int PAGE_SIZE = 1024;
    private static final ThreadLocal<Integer> TID = new ThreadLocal<Integer>() {
        @Override protected Integer initialValue() {
            return getTid0();
        }
    };

    private ByteBuffer[] contextStorage;

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
                contextStorage = new ByteBuffer[maxPages];
            }
        }
    }

    /**
     * Start profiling
     *
     * @param event Profiling event, see {@link Events}
     * @param interval Sampling interval, e.g. nanoseconds for Events.CPU
     * @throws IllegalStateException If profiler is already running
     */
    public void start(String event, long interval) throws IllegalStateException {
        if (event == null) {
            throw new NullPointerException();
        }
        start0(event, interval, true);
    }

    /**
     * Start or resume profiling without resetting collected data.
     * Note that event and interval may change since the previous profiling session.
     *
     * @param event Profiling event, see {@link Events}
     * @param interval Sampling interval, e.g. nanoseconds for Events.CPU
     * @throws IllegalStateException If profiler is already running
     */
    public void resume(String event, long interval) throws IllegalStateException {
        if (event == null) {
            throw new NullPointerException();
        }
        start0(event, interval, false);
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
        if (contextStorage == null) {
            return;
        }
        ByteBuffer page = getPage(tid);
        int index = (tid % PAGE_SIZE) * CONTEXT_SIZE;
        page.putLong(index, spanId);
        page.putLong(index + 8, rootSpanId);
        page.putLong(index + 16, spanId ^ rootSpanId);
    }

    /**
     * Clears context identifier for current thread.
     */
    public void clearContext() {
        clearContext(TID.get());
    }

    /**
     * Records the available parallelism of the thread pool the thread belongs to.
     */
    public void setPoolParallelism(int tid, int parallelism) {
        if (contextStorage == null) {
            return;
        }
        ByteBuffer page = getPage(tid);
        int index = (tid % PAGE_SIZE) * CONTEXT_SIZE;
        page.putInt(index + 24, parallelism);
    }

    /**
     * Resets the thread-local pool parallelism
     */
    public void clearPoolParallelism(int tid) {
        if (contextStorage == null) {
            return;
        }
        ByteBuffer page = getPage(tid);
        int index = (tid % PAGE_SIZE) * CONTEXT_SIZE;
        page.putInt(index + 24, 1);
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

    /**
     * Clears context identifier for the given thread id.
     * @param tid the native thread id
     */
    public void clearContext(int tid) {
        setContext(tid, 0, 0);
    }

    public int getNativeThreadId() {
        return getTid0();
    }

    private native void start0(String event, long interval, boolean reset) throws IllegalStateException;
    private native void stop0() throws IllegalStateException;
    private native String execute0(String command) throws IllegalArgumentException, IllegalStateException, IOException;
    private native void filterThread0(int tid, boolean enable);

    private static native int getTid0();
    private static native ByteBuffer getContextPage0(int tid);
    private static native int getMaxContextPages0();
}
