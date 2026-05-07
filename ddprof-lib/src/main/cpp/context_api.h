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
#include <string>
#include <vector>

class ProfiledThread;

/**
 * Unified context API for trace/span context storage.
 *
 * Uses OTEP #4947 TLS pointer (otel_thread_ctx_v1) for all
 * context reads and writes. The OTEP record is embedded in ProfiledThread
 * and discovered by external profilers via ELF dynsym.
 */
class ContextApi {
public:
    /**
     * Initialize context TLS for the given thread on first use.
     * Must be called with signals blocked (SignalBlocker).
     */
    static void initializeContextTLS(ProfiledThread* thrd);

    /**
     * Read span ID and local root span ID for the current thread.
     *
     * Used by signal handlers to get the current trace context.
     * Returns false if the OTEP valid flag is not set (record being mutated
     * or thread not yet initialized). Does not modify span_id or root_span_id
     * on failure; callers must pre-initialize output parameters to their
     * desired default. Does not detect torn reads (the valid flag guards that).
     *
     * Unlike snapshot(), this reads only spanId and rootSpanId — use
     * snapshot() when tag encodings are also needed.
     *
     * @param span_id Output: the span ID
     * @param root_span_id Output: the root span ID (from sidecar)
     * @return true if the valid flag was set and context was read
     */
    static bool get(u64& span_id, u64& root_span_id);

    /**
     * Snapshot the current thread's full context into a Context struct.
     *
     * Populates a Context with spanId, rootSpanId (from sidecar)
     * and tag encodings (from sidecar) so that writeContextSnapshot()
     * works for both live and deferred event paths. Unlike get(), this
     * also captures custom attribute tag encodings.
     *
     * @return A Context struct representing the current thread's context
     */
    static Context snapshot();

    /**
     * Register attribute key names and publish them in the process context.
     * Must be called before setAttribute().
     * Keys beyond DD_TAGS_CAPACITY are silently clipped.
     *
     * @param keys Array of key name strings
     * @param count Number of keys (clipped to DD_TAGS_CAPACITY)
     */
    static void registerAttributeKeys(const char** keys, int count);

    /**
     * std::vector overload of registerAttributeKeys, used from the C++ start
     * path so that the attributes=... CLI argument auto-publishes the OTEP
     * attribute_key_map without requiring an explicit Java-side call.
     */
    static void registerAttributeKeys(const std::vector<std::string>& keys);
};

#endif /* _CONTEXT_API_H */
