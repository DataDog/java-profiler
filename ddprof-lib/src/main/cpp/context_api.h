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
#include "context.h"
#include <cstdint>

/**
 * Unified context API for trace/span context storage.
 *
 * This class provides a mode-agnostic interface for reading and writing
 * thread context. The actual storage is selected at initialization time
 * based on the Arguments::_context_storage setting:
 *
 * - CTX_STORAGE_PROFILER: Uses existing TLS-based storage (context_tls_v1)
 * - CTX_STORAGE_OTEL: Uses OTEP #4947 TLS pointer (custom_labels_current_set_v2)
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
     * For OTEL mode, sets the initialized flag (per-thread TLS init is deferred).
     *
     * @param args Profiler arguments containing _context_storage mode
     */
    static void initialize(const Arguments& args);

    /**
     * Shutdown context storage.
     *
     * Releases resources allocated during initialization.
     * For OTEL mode, clears the initialized flag.
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
     * Write context for the current thread (profiler mode only).
     *
     * NOT supported in OTEL mode — use setFull() instead.
     * In OTEL mode this logs a warning and returns without writing.
     *
     * @param span_id The span ID
     * @param root_span_id The root span ID
     */
    static void set(u64 span_id, u64 root_span_id);

    /**
     * Write full OTEL context with 128-bit trace ID and local root span ID.
     *
     * In OTEL mode: writes trace_id + span_id to the OTEP record, stores
     * local_root_span_id as a reserved attribute (key index 0) for JFR.
     * In profiler mode: trace_id_high is ignored, local_root_span_id maps to rootSpanId.
     *
     * @param local_root_span_id Local root span ID (for endpoint correlation)
     * @param span_id The span ID
     * @param trace_id_high Upper 64 bits of 128-bit trace ID
     * @param trace_id_low Lower 64 bits of 128-bit trace ID
     */
    static void setFull(u64 local_root_span_id, u64 span_id, u64 trace_id_high, u64 trace_id_low);

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
     * Clear context for the current thread.
     */
    static void clear();

    /**
     * Snapshot the current thread's context into a Context struct.
     *
     * In profiler mode, returns Contexts::get() directly.
     * In OTEL mode, populates a Context with spanId, rootSpanId (from sidecar),
     * checksum, and tag encodings (from sidecar) so that writeContext() works
     * identically for both modes.
     *
     * @return A Context struct representing the current thread's context
     */
    static Context snapshot();

    /**
     * Set a custom attribute on the current thread's context.
     *
     * In OTEL mode: encodes into attrs_data of the OTEP record.
     * In profiler mode: registers the string value as a constant and
     * writes the encoding to Context.tags[key_index].
     *
     * @param key_index Index into the registered attribute key map
     * @param value UTF-8 string value
     * @param value_len Length of value in bytes (max 255)
     * @return true if the attribute was set successfully
     */
    static bool setAttribute(uint8_t key_index, const char* value, uint8_t value_len);

    /**
     * Register attribute key names and publish them in the process context.
     * Must be called before setAttribute().
     *
     * @param keys Array of key name strings
     * @param count Number of keys
     */
    static void registerAttributeKeys(const char** keys, int count);

    /**
     * Get registered attribute key name by index.
     *
     * @param index Key index
     * @return Key name string, or nullptr if index is out of range
     */
    static const char* getAttributeKey(int index);

    /**
     * Get number of registered attribute keys.
     */
    static int getAttributeKeyCount();

    static const int MAX_ATTRIBUTE_KEYS = 32;

    // Reserved attribute index for local root span ID in OTEL attrs_data.
    // Stored as 16-char hex string (UTF-8). Visible to external OTEL profilers.
    static const uint8_t LOCAL_ROOT_SPAN_ATTR_INDEX = 0;

private:
    static ContextStorageMode _mode;
    static bool _initialized;
    static char* _attribute_keys[MAX_ATTRIBUTE_KEYS];
    static int _attribute_key_count;

    // Internal: write context to profiler TLS (Context struct)
    static void setProfilerContext(u64 root_span_id, u64 span_id);

    // Clear sidecar fields (tag encodings + localRootSpanId) on context detachment
    static void clearOtelSidecar();
};

#endif /* _CONTEXT_API_H */
