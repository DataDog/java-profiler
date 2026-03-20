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
#include "guards.h"
#include "otel_context.h"
#include "otel_process_ctx.h"
#include "profiler.h"
#include "thread.h"
#include <cstring>

// Static member initialization
ContextStorageMode ContextApi::_mode = CTX_STORAGE_PROFILER;
char* ContextApi::_attribute_keys[MAX_ATTRIBUTE_KEYS] = {};
int ContextApi::_attribute_key_count = 0;

void ContextApi::initialize(const Arguments& args) {
    ContextStorageMode mode = args._context_storage;
    __atomic_store_n(&_mode, mode, __ATOMIC_RELEASE);
}

// Called from Profiler::stop() which is single-threaded — no racing with initialize().
void ContextApi::shutdown() {
    freeAttributeKeys();
    __atomic_store_n(&_mode, CTX_STORAGE_PROFILER, __ATOMIC_RELEASE);
}

/**
 * Initialize OTel TLS for the current thread on first use.
 * Zero-inits the embedded OtelThreadContextRecord and triggers TLS init.
 * Must be called with signals blocked to prevent musl TLS deadlock.
 */
static void initializeOtelTls(ProfiledThread* thrd) {
    // Block profiling signals during first TLS access (same pattern as context_tls_v1)
    SignalBlocker blocker;

    // Zero-init the embedded record fields
    OtelThreadContextRecord* record = thrd->getOtelContextRecord();
    record->valid = 0;
    record->_reserved = 0;
    record->attrs_data_size = 0;

    // First access to custom_labels_current_set_v2 triggers TLS init
    custom_labels_current_set_v2 = nullptr;

    // Mark initialized for signal-safe access
    thrd->markOtelContextInitialized();
}

void ContextApi::set(u64 span_id, u64 root_span_id) {
    ContextStorageMode mode = getMode();
    if (mode == CTX_STORAGE_OTEL) {
        Log::warn("set(spanId, rootSpanId) called in OTEL mode — use setFull() instead");
        return;
    }
    // Profiler mode: rootSpanId is used directly for trace correlation
    setProfilerContext(root_span_id, span_id);
}

void ContextApi::setFull(u64 local_root_span_id, u64 span_id, u64 trace_id_high, u64 trace_id_low) {
    ContextStorageMode mode = getMode();

    if (mode == CTX_STORAGE_OTEL) {
        // Ensure TLS + record are initialized on first use
        ProfiledThread* thrd = ProfiledThread::current();
        if (thrd == nullptr) return;

        if (!thrd->isOtelContextInitialized()) {
            initializeOtelTls(thrd);
        }

        // All-zero IDs = context detachment
        if (trace_id_high == 0 && trace_id_low == 0 && span_id == 0) {
            OtelContexts::clear(thrd->getOtelContextRecord());
            thrd->clearOtelSidecar();
            return;
        }

        // Write trace_id + span_id + local_root_span_id in a single detach/attach cycle
        OtelContexts::set(thrd->getOtelContextRecord(), trace_id_high, trace_id_low, span_id, local_root_span_id);

        // Cache in sidecar for O(1) signal-handler reads
        thrd->setOtelLocalRootSpanId(local_root_span_id);
    } else {
        // Profiler mode: local_root_span_id maps to rootSpanId, trace_id_high ignored
        setProfilerContext(local_root_span_id, span_id);
    }
}

void ContextApi::setProfilerContext(u64 root_span_id, u64 span_id) {
    Context& ctx = Contexts::get();

    __atomic_store_n(&ctx.checksum, 0ULL, __ATOMIC_RELEASE);
    __atomic_store_n(&ctx.spanId, span_id, __ATOMIC_RELAXED);
    __atomic_store_n(&ctx.rootSpanId, root_span_id, __ATOMIC_RELAXED);

    u64 newChecksum = Contexts::checksum(span_id, root_span_id);
    __atomic_store_n(&ctx.checksum, newChecksum, __ATOMIC_RELEASE);
}

bool ContextApi::get(u64& span_id, u64& root_span_id) {
    ContextStorageMode mode = getMode();

    if (mode == CTX_STORAGE_OTEL) {
        // Single thread lookup for both span_id and root_span_id
        ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
        if (thrd == nullptr || !thrd->isOtelContextInitialized()) {
            return false;
        }

        if (!OtelContexts::getSpanId(thrd->getOtelContextRecord(), span_id)) {
            return false;
        }

        root_span_id = thrd->getOtelLocalRootSpanId();
        return true;
    } else {
        Context& ctx = Contexts::get();
        u64 checksum1 = __atomic_load_n(&ctx.checksum, __ATOMIC_ACQUIRE);
        span_id = __atomic_load_n(&ctx.spanId, __ATOMIC_RELAXED);
        root_span_id = __atomic_load_n(&ctx.rootSpanId, __ATOMIC_RELAXED);
        return checksum1 != 0 && checksum1 == Contexts::checksum(span_id, root_span_id);
    }
}

Context ContextApi::snapshot() {
    ContextStorageMode mode = getMode();

    if (mode == CTX_STORAGE_OTEL) {
        ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
        if (thrd == nullptr) {
            return {};
        }
        size_t numAttrs = Profiler::instance()->numContextAttributes();
        return thrd->snapshotContext(numAttrs);
    }

    return Contexts::get();
}

bool ContextApi::setAttribute(uint8_t key_index, const char* value, uint8_t value_len) {
    ContextStorageMode mode = getMode();

    if (mode == CTX_STORAGE_OTEL) {
        if (key_index >= DD_TAGS_CAPACITY) return false;

        // Ensure TLS + record are initialized on first use
        ProfiledThread* thrd = ProfiledThread::current();
        if (thrd == nullptr) return false;

        if (!thrd->isOtelContextInitialized()) {
            initializeOtelTls(thrd);
        }

        // Pre-register the value string in the Dictionary and cache the encoding
        // in the sidecar for O(1) signal-handler reads (no hash lookup needed).
        u32 encoding = Profiler::instance()->contextValueMap()->bounded_lookup(
            value, value_len, 1 << 16);
        if (encoding == INT_MAX) {
            thrd->setOtelTagEncoding(key_index, 0);
            return false;
        }
        thrd->setOtelTagEncoding(key_index, encoding);

        // Offset by 1 in the OTEP record: index 0 is reserved for LOCAL_ROOT_SPAN_ATTR_INDEX
        uint8_t otep_key_index = key_index + 1;
        return OtelContexts::setAttribute(thrd->getOtelContextRecord(), otep_key_index, value, value_len);
    } else {
        // Profiler mode: register the string and write encoding to Context.tags[]
        if (key_index >= DD_TAGS_CAPACITY) return false;

        u32 encoding = Profiler::instance()->contextValueMap()->bounded_lookup(
            value, value_len, 1 << 16);
        if (encoding == INT_MAX) return false;

        Context& ctx = Contexts::get();
        ctx.tags[key_index].value = encoding;
        return true;
    }
}

void ContextApi::freeAttributeKeys() {
    int count = _attribute_key_count;
    // Null pointers before setting count to 0 — a signal handler could read
    // _attribute_key_count > 0 and then dereference a freed pointer otherwise.
    char* old_keys[MAX_ATTRIBUTE_KEYS];
    for (int i = 0; i < count; i++) {
        old_keys[i] = _attribute_keys[i];
        _attribute_keys[i] = nullptr;
    }
    _attribute_key_count = 0;
    for (int i = 0; i < count; i++) {
        free(old_keys[i]);
    }
}

// Called from JNI during setup, before profiling starts.
void ContextApi::registerAttributeKeys(const char** keys, int count) {
    freeAttributeKeys();

    _attribute_key_count = count < MAX_ATTRIBUTE_KEYS ? count : MAX_ATTRIBUTE_KEYS;
    for (int i = 0; i < _attribute_key_count; i++) {
        _attribute_keys[i] = strdup(keys[i]);
    }

    // If in OTEL mode, re-publish process context with thread_ctx_config
    ContextStorageMode mode = getMode();
    if (mode == CTX_STORAGE_OTEL) {
        // Build NULL-terminated key array for the process context config.
        // Index 0 is reserved for local_root_span_id; user keys start at index 1.
        const char* key_ptrs[MAX_ATTRIBUTE_KEYS + 2]; // +1 reserved, +1 null
        key_ptrs[0] = "dd.local_root_span_id";
        for (int i = 0; i < _attribute_key_count; i++) {
            key_ptrs[i + 1] = _attribute_keys[i];
        }
        key_ptrs[_attribute_key_count + 1] = nullptr;

        otel_thread_ctx_config_data config = {
            .schema_version = "tlsdesc_v1_dev",
            .attribute_key_map = key_ptrs,
        };

#ifndef OTEL_PROCESS_CTX_NO_READ
        // Re-publish the process context with thread_ctx_config.
        otel_process_ctx_read_result read_result = otel_process_ctx_read();
        if (read_result.success) {
            otel_process_ctx_data data = {
                .deployment_environment_name = read_result.data.deployment_environment_name,
                .service_instance_id = read_result.data.service_instance_id,
                .service_name = read_result.data.service_name,
                .service_version = read_result.data.service_version,
                .telemetry_sdk_language = read_result.data.telemetry_sdk_language,
                .telemetry_sdk_version = read_result.data.telemetry_sdk_version,
                .telemetry_sdk_name = read_result.data.telemetry_sdk_name,
                .resource_attributes = read_result.data.resource_attributes,
                .extra_attributes = read_result.data.extra_attributes,
                .thread_ctx_config = &config,
            };

            otel_process_ctx_publish(&data);
            otel_process_ctx_read_drop(&read_result);
        }
#endif
    }
}
