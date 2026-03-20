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
bool ContextApi::_initialized = false;
char* ContextApi::_attribute_keys[MAX_ATTRIBUTE_KEYS] = {};
int ContextApi::_attribute_key_count = 0;

void ContextApi::initialize(const Arguments& args) {
    if (__atomic_load_n(&_initialized, __ATOMIC_ACQUIRE)) {
        return;
    }

    ContextStorageMode mode = args._context_storage;
    if (mode == CTX_STORAGE_OTEL) {
        OtelContexts::initialize();
    }

    __atomic_store_n(&_mode, mode, __ATOMIC_RELEASE);
    __atomic_store_n(&_initialized, true, __ATOMIC_RELEASE);
}

// Called from Profiler::stop() which is single-threaded — no racing with initialize().
void ContextApi::shutdown() {
    if (!__atomic_load_n(&_initialized, __ATOMIC_ACQUIRE)) {
        return;
    }

    if (getMode() == CTX_STORAGE_OTEL) {
        OtelContexts::shutdown();
    }

    // Free registered attribute keys (null first, free later for signal safety)
    int count = _attribute_key_count;
    _attribute_key_count = 0;
    for (int i = 0; i < count; i++) {
        char* key = _attribute_keys[i];
        _attribute_keys[i] = nullptr;
        free(key);
    }

    __atomic_store_n(&_mode, CTX_STORAGE_PROFILER, __ATOMIC_RELEASE);
    __atomic_store_n(&_initialized, false, __ATOMIC_RELEASE);
}

bool ContextApi::isInitialized() {
    return __atomic_load_n(&_initialized, __ATOMIC_ACQUIRE);
}

ContextStorageMode ContextApi::getMode() {
    return __atomic_load_n(&_mode, __ATOMIC_ACQUIRE);
}

/**
 * Initialize OTel TLS for the current thread on first use.
 * Allocates a per-thread OtelThreadContextRecord and caches it in ProfiledThread.
 * Must be called with signals blocked to prevent musl TLS deadlock.
 */
static OtelThreadContextRecord* initializeOtelTls(ProfiledThread* thrd) {
    // Block profiling signals during first TLS access (same pattern as context_tls_v1)
    SignalBlocker blocker;

    // Allocate one record per thread — freed in ProfiledThread destructor/releaseFromBuffer
    OtelThreadContextRecord* record = new OtelThreadContextRecord();
    record->valid = 0;
    record->_reserved = 0;
    record->attrs_data_size = 0;

    // First access to custom_labels_current_set_v2 triggers TLS init
    custom_labels_current_set_v2 = nullptr;

    // Cache in ProfiledThread for signal-safe cross-thread access
    thrd->markOtelContextInitialized(record);

    return record;
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
        // All-zero IDs = context detachment
        if (trace_id_high == 0 && trace_id_low == 0 && span_id == 0) {
            OtelContexts::clear();
            clearOtelSidecar();
            return;
        }

        // Ensure TLS + record are initialized on first use
        ProfiledThread* thrd = ProfiledThread::current();
        if (thrd == nullptr) return;

        if (!thrd->isOtelContextInitialized()) {
            initializeOtelTls(thrd);
        }

        // Write trace_id + span_id to OTEP record
        OtelContexts::set(trace_id_high, trace_id_low, span_id);

        // Store local_root_span_id as hex string attribute at reserved index 0.
        // OTEP spec requires UTF-8 string values in attrs_data.
        // Hand-rolled hex encoder to avoid snprintf overhead on the hot path.
        static const char hex_chars[] = "0123456789abcdef";
        char lrs_hex[16];
        u64 v = local_root_span_id;
        for (int i = 15; i >= 0; i--) {
            lrs_hex[i] = hex_chars[v & 0xF];
            v >>= 4;
        }
        OtelContexts::setAttribute(LOCAL_ROOT_SPAN_ATTR_INDEX, lrs_hex, 16);

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
        u64 trace_high, trace_low;
        if (!OtelContexts::get(trace_high, trace_low, span_id)) {
            return false;
        }

        // Read local_root_span_id from sidecar (O(1), no attrs_data scan)
        root_span_id = 0;
        ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
        if (thrd != nullptr) {
            root_span_id = thrd->getOtelLocalRootSpanId();
        }
        return true;
    } else {
        Context& ctx = Contexts::get();
        u64 checksum1 = __atomic_load_n(&ctx.checksum, __ATOMIC_ACQUIRE);
        span_id = __atomic_load_n(&ctx.spanId, __ATOMIC_RELAXED);
        root_span_id = __atomic_load_n(&ctx.rootSpanId, __ATOMIC_RELAXED);
        return checksum1 != 0 && checksum1 == Contexts::checksum(span_id, root_span_id);
    }
}


void ContextApi::clearOtelSidecar() {
    ProfiledThread* thrd = ProfiledThread::current();
    if (thrd != nullptr) {
        thrd->setOtelLocalRootSpanId(0);
        for (u32 i = 0; i < DD_TAGS_CAPACITY; i++) {
            thrd->setOtelTagEncoding(i, 0);
        }
    }
}

void ContextApi::clear() {
    ContextStorageMode mode = getMode();

    if (mode == CTX_STORAGE_OTEL) {
        OtelContexts::clear();
        clearOtelSidecar();
    } else {
        set(0, 0);
    }
}

Context ContextApi::snapshot() {
    ContextStorageMode mode = getMode();

    if (mode == CTX_STORAGE_OTEL) {
        Context ctx = {};
        u64 span_id = 0, root_span_id = 0;
        if (get(span_id, root_span_id)) {
            ctx.spanId = span_id;
            ctx.rootSpanId = root_span_id;
            ctx.checksum = Contexts::checksum(span_id, root_span_id);
        }
        ProfiledThread* thrd = ProfiledThread::current();
        size_t numAttrs = Profiler::instance()->numContextAttributes();
        for (size_t i = 0; i < numAttrs && i < DD_TAGS_CAPACITY; i++) {
            ctx.tags[i].value = thrd->getOtelTagEncoding(i);
        }
        return ctx;
    }

    return Contexts::get();
}

bool ContextApi::setAttribute(uint8_t key_index, const char* value, uint8_t value_len) {
    ContextStorageMode mode = getMode();

    if (mode == CTX_STORAGE_OTEL) {
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
        thrd->setOtelTagEncoding(key_index, encoding != INT_MAX ? encoding : 0);

        return OtelContexts::setAttribute(key_index, value, value_len);
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

// Called from JNI during setup, before profiling starts.
void ContextApi::registerAttributeKeys(const char** keys, int count) {
    // Free any previously registered keys (null first, free later)
    int oldCount = _attribute_key_count;
    _attribute_key_count = 0;
    char* oldKeys[MAX_ATTRIBUTE_KEYS];
    for (int i = 0; i < oldCount; i++) {
        oldKeys[i] = _attribute_keys[i];
        _attribute_keys[i] = nullptr;
    }
    for (int i = 0; i < oldCount; i++) {
        free(oldKeys[i]);
    }

    _attribute_key_count = count < MAX_ATTRIBUTE_KEYS ? count : MAX_ATTRIBUTE_KEYS;
    for (int i = 0; i < _attribute_key_count; i++) {
        _attribute_keys[i] = strdup(keys[i]);
    }

    // If in OTEL mode, re-publish process context with thread_ctx_config
    ContextStorageMode mode = getMode();
    if (mode == CTX_STORAGE_OTEL) {
        // Build NULL-terminated key array for the process context config
        const char* key_ptrs[MAX_ATTRIBUTE_KEYS + 1];
        for (int i = 0; i < _attribute_key_count; i++) {
            key_ptrs[i] = _attribute_keys[i];
        }
        key_ptrs[_attribute_key_count] = nullptr;

        otel_thread_ctx_config_data config = {
            .schema_version = "tlsdesc_v1_dev",
            .attribute_key_map = key_ptrs,
        };

#ifndef OTEL_PROCESS_CTX_NO_READ
        // Re-publish the process context with thread_ctx_config.
        // Guard: otel_process_ctx_read() is only available when the read API is compiled in.
        // We need to read the current context and re-publish with the config
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

const char* ContextApi::getAttributeKey(int index) {
    if (index < 0 || index >= _attribute_key_count) {
        return nullptr;
    }
    return _attribute_keys[index];
}

int ContextApi::getAttributeKeyCount() {
    return _attribute_key_count;
}
