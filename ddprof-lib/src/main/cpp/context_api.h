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

class ProfiledThread;

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
     * Shutdown context storage.
     * Releases resources allocated during initialization.
     */
    static void shutdown();

    /**
     * Initialize OTel TLS for the given thread on first use.
     * Must be called with signals blocked (SignalBlocker).
     */
    static void initializeOtelTls(ProfiledThread* thrd);

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
     * Populates a Context with spanId, rootSpanId (from sidecar)
     * and tag encodings (from sidecar) so that writeContext()
     * works for both live and deferred event paths.
     *
     * @return A Context struct representing the current thread's context
     */
    static Context snapshot();

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
