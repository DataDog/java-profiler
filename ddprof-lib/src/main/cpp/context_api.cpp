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

#include "context_api.h"
#include "context.h"
#include "otel_context.h"

// Static member initialization
ContextStorageMode ContextApi::_mode = CTX_STORAGE_PROFILER;
bool ContextApi::_initialized = false;

bool ContextApi::initialize(const Arguments& args) {
    if (__atomic_load_n(&_initialized, __ATOMIC_ACQUIRE)) {
        return true;
    }

    ContextStorageMode mode = args._context_storage;
    if (mode == CTX_STORAGE_OTEL) {
        if (!OtelContexts::initialize()) {
            // Failed to initialize OTEL buffer, fall back to profiler mode
            mode = CTX_STORAGE_PROFILER;
            __atomic_store_n(&_mode, mode, __ATOMIC_RELEASE);
            return false;
        }
    }
    // PROFILER mode uses existing TLS (context_tls_v1) - no explicit init needed

    __atomic_store_n(&_mode, mode, __ATOMIC_RELEASE);
    __atomic_store_n(&_initialized, true, __ATOMIC_RELEASE);
    return true;
}

void ContextApi::shutdown() {
    if (!__atomic_load_n(&_initialized, __ATOMIC_ACQUIRE)) {
        return;
    }

    if (__atomic_load_n(&_mode, __ATOMIC_ACQUIRE) == CTX_STORAGE_OTEL) {
        OtelContexts::shutdown();
    }

    __atomic_store_n(&_initialized, false, __ATOMIC_RELEASE);
}

bool ContextApi::isInitialized() {
    return __atomic_load_n(&_initialized, __ATOMIC_ACQUIRE);
}

ContextStorageMode ContextApi::getMode() {
    return __atomic_load_n(&_mode, __ATOMIC_ACQUIRE);
}

void ContextApi::set(u64 span_id, u64 root_span_id) {
    // Map Datadog format to storage
    // In OTEL mode: trace_id = (0, root_span_id), span_id = span_id
    setOtel(0, root_span_id, span_id);
}

void ContextApi::setOtel(u64 trace_id_high, u64 trace_id_low, u64 span_id) {
    // Use atomic load for mode check - may be called from signal handlers
    ContextStorageMode mode = __atomic_load_n(&_mode, __ATOMIC_ACQUIRE);

    if (mode == CTX_STORAGE_OTEL) {
        OtelContexts::set(trace_id_high, trace_id_low, span_id);
    } else {
        // Profiler mode: use existing TLS
        // Note: trace_id_high is ignored in profiler mode (only 64-bit root span ID)
        Context& ctx = Contexts::get();

        // Use checksum protocol for torn-read safety with proper memory ordering
        // 1. Clear checksum to mark update in progress (release to ensure visibility)
        __atomic_store_n(&ctx.checksum, 0ULL, __ATOMIC_RELEASE);

        // 2. Write data fields with relaxed atomics (ordering guaranteed by checksum barriers)
        __atomic_store_n(&ctx.spanId, span_id, __ATOMIC_RELAXED);
        __atomic_store_n(&ctx.rootSpanId, trace_id_low, __ATOMIC_RELAXED);

        // 3. Set final checksum with release semantics
        // This ensures all prior writes are visible before checksum update
        u64 newChecksum = Contexts::checksum(span_id, trace_id_low);
        __atomic_store_n(&ctx.checksum, newChecksum, __ATOMIC_RELEASE);
    }
}

bool ContextApi::get(u64& span_id, u64& root_span_id) {
    // Use atomic load for mode check - may be called from signal handlers
    ContextStorageMode mode = __atomic_load_n(&_mode, __ATOMIC_ACQUIRE);

    if (mode == CTX_STORAGE_OTEL) {
        u64 trace_high, trace_low;
        if (OtelContexts::get(trace_high, trace_low, span_id)) {
            root_span_id = trace_low;
            return true;
        }
        return false;
    } else {
        // Profiler mode: use existing TLS
        Context& ctx = Contexts::get();
        // Read with acquire to synchronize with release in set()
        u64 checksum1 = __atomic_load_n(&ctx.checksum, __ATOMIC_ACQUIRE);
        span_id = __atomic_load_n(&ctx.spanId, __ATOMIC_RELAXED);
        root_span_id = __atomic_load_n(&ctx.rootSpanId, __ATOMIC_RELAXED);
        // Validate checksum to detect torn reads
        return checksum1 != 0 && checksum1 == Contexts::checksum(span_id, root_span_id);
    }
}

bool ContextApi::getByTid(int tid, u64& span_id, u64& root_span_id) {
    // Use atomic load for mode check - may be called from signal handlers
    ContextStorageMode mode = __atomic_load_n(&_mode, __ATOMIC_ACQUIRE);

    if (mode == CTX_STORAGE_OTEL) {
        u64 trace_high, trace_low;
        if (OtelContexts::getByTid(tid, trace_high, trace_low, span_id)) {
            root_span_id = trace_low;
            return true;
        }
        return false;
    } else {
        // Profiler mode: cannot read other thread's TLS
        // This is a limitation - JVMTI wall-clock needs OTEL mode for remote reads
        // Fall back to returning false (no context available)
        span_id = 0;
        root_span_id = 0;
        return false;
    }
}

void ContextApi::clear() {
    set(0, 0);
}
