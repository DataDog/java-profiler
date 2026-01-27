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

#ifndef _CONTEXT_API_H
#define _CONTEXT_API_H

#include "arch.h"
#include "arguments.h"

/**
 * Unified context API for trace/span context storage.
 *
 * This class provides a mode-agnostic interface for reading and writing
 * thread context. The actual storage is selected at initialization time
 * based on the Arguments::_context_storage setting:
 *
 * - CTX_STORAGE_PROFILER: Uses existing TLS-based storage (context_tls_v1)
 * - CTX_STORAGE_OTEL: Uses OTEL ring buffer storage (discoverable by external profilers)
 *
 * The abstraction allows signal handlers and JNI code to remain unchanged
 * while the underlying storage mechanism can be switched via configuration.
 */
class ContextApi {
public:
    /**
     * Initialize context storage based on configuration.
     *
     * Must be called once during profiler startup.
     * For OTEL mode, creates the discoverable ring buffer.
     *
     * @param args Profiler arguments containing _context_storage mode
     * @return true if initialization succeeded
     */
    static bool initialize(const Arguments& args);

    /**
     * Shutdown context storage.
     *
     * Releases resources allocated during initialization.
     * For OTEL mode, unmaps the ring buffer.
     */
    static void shutdown();

    /**
     * Check if context storage is initialized.
     *
     * @return true if initialized
     */
    static bool isInitialized();

    /**
     * Get the current storage mode.
     *
     * @return The active context storage mode
     */
    static ContextStorageMode getMode();

    /**
     * Write context for the current thread.
     *
     * This is the primary method for setting trace context from the tracer.
     * Maps Datadog's (spanId, rootSpanId) to OTEL's (trace_id_high, trace_id_low, span_id).
     *
     * In OTEL mode: trace_id_high=0, trace_id_low=rootSpanId, span_id=spanId
     *
     * @param span_id The span ID
     * @param root_span_id The root span ID (trace ID low bits for OTEL)
     */
    static void set(u64 span_id, u64 root_span_id);

    /**
     * Write full OTEL context for the current thread.
     *
     * Supports full 128-bit trace IDs when in OTEL mode.
     * In profiler mode, trace_id_high is ignored.
     *
     * @param trace_id_high Upper 64 bits of 128-bit trace ID (OTEL only)
     * @param trace_id_low Lower 64 bits of 128-bit trace ID (rootSpanId)
     * @param span_id The span ID
     */
    static void setOtel(u64 trace_id_high, u64 trace_id_low, u64 span_id);

    /**
     * Read context for the current thread.
     *
     * Used by signal handlers to get the current trace context.
     * Returns false if the context is invalid (torn read or uninitialized).
     *
     * @param span_id Output: the span ID
     * @param root_span_id Output: the root span ID
     * @return true if context was successfully read
     */
    static bool get(u64& span_id, u64& root_span_id);

    /**
     * Read context for a specific thread by TID.
     *
     * Used by JVMTI wall-clock sampling where the sampling thread
     * needs to read another thread's context.
     *
     * @param tid Thread ID to read context for
     * @param span_id Output: the span ID
     * @param root_span_id Output: the root span ID
     * @return true if context was successfully read
     */
    static bool getByTid(int tid, u64& span_id, u64& root_span_id);

    /**
     * Clear context for the current thread.
     */
    static void clear();

private:
    static ContextStorageMode _mode;
    static bool _initialized;
};

#endif /* _CONTEXT_API_H */
