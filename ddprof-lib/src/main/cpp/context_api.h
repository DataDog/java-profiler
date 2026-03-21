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
#include "context.h"
#include <cstdint>

/**
 * Unified context API for trace/span context storage.
 *
 * Uses OTEP #4947 TLS pointer (custom_labels_current_set_v2) for all
 * context reads and writes. The OTEP record is embedded in ProfiledThread
 * and discovered by external profilers via ELF dynsym.
 */
class ContextApi {
public:
    /**
     * Initialize context storage.
     * Must be called once during profiler startup.
     */
    static void initialize();

    /**
     * Shutdown context storage.
     * Releases resources allocated during initialization.
     */
    static void shutdown();

    /**
     * Write full OTEL context with 128-bit trace ID and local root span ID.
     *
     * Writes trace_id + span_id + local_root_span_id to the OTEP record
     * in a single detach/attach cycle.
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
     * Snapshot the current thread's context into a Context struct.
     *
     * Populates a Context with spanId, rootSpanId (from sidecar),
     * checksum, and tag encodings (from sidecar) so that writeContext()
     * works for both live and deferred event paths.
     *
     * @return A Context struct representing the current thread's context
     */
    static Context snapshot();

    /**
     * Set a custom attribute on the current thread's context.
     *
     * Encodes into attrs_data of the OTEP record and caches the
     * encoding in the ProfiledThread sidecar for O(1) signal-handler reads.
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

    static const int MAX_ATTRIBUTE_KEYS = 32;

    // Reserved attribute index for local root span ID in OTEL attrs_data.
    static const uint8_t LOCAL_ROOT_SPAN_ATTR_INDEX = 0;

private:
    static char* _attribute_keys[MAX_ATTRIBUTE_KEYS];
    static int _attribute_key_count;

    // Free registered attribute keys (shared by shutdown() and registerAttributeKeys())
    static void freeAttributeKeys();
};

#endif /* _CONTEXT_API_H */
