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

// Reserved attribute index for local root span ID in OTEL attrs_data.
// Only used within this translation unit; not part of the public ContextApi header.
static const uint8_t LOCAL_ROOT_SPAN_ATTR_INDEX = 0;

/**
 * Initialize context TLS for the current thread on first use.
 * Must be called with signals blocked to prevent musl TLS deadlock:
 * on musl, the first write to a TLS variable triggers lazy slot allocation,
 * which acquires an internal lock that is also held during signal delivery,
 * causing deadlock if a signal fires mid-init.
 * The OtelThreadContextRecord is already zero-initialized by the ProfiledThread ctor.
 */
void ContextApi::initializeContextTLS(ProfiledThread* thrd) {
    SignalBlocker blocker;
    // Set the TLS pointer permanently to this thread's record.
    // This first write triggers musl's TLS slot initialization (see above).
    // The pointer remains stable for the thread's lifetime; external profilers
    // rely solely on the valid flag for consistency, not pointer nullness.
    otel_thread_ctx_v1 = thrd->getOtelContextRecord();
    thrd->markContextInitialized();
}

bool ContextApi::get(u64& span_id, u64& root_span_id) {
    ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
    if (thrd == nullptr || !thrd->isContextInitialized()) {
        return false;
    }

    OtelThreadContextRecord* record = thrd->getOtelContextRecord();
    if (__atomic_load_n(&record->valid, __ATOMIC_ACQUIRE) != 1) {
        return false;
    }
    u64 val = 0;
    for (int i = 0; i < 8; i++) { val = (val << 8) | record->span_id[i]; }
    span_id = val;

    root_span_id = thrd->getOtelLocalRootSpanId();
    return true;
}

Context ContextApi::snapshot() {
    ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
    if (thrd == nullptr) {
        return {};
    }
    size_t numAttrs = Profiler::instance()->numContextAttributes();
    return thrd->snapshotContext(numAttrs);
}

void ContextApi::registerAttributeKeys(const char** keys, int count) {
    // Clip to DD_TAGS_CAPACITY: that is the actual sidecar slot limit and the
    // maximum keyIndex accepted by ThreadContext.setContextAttribute.
    int n = count < (int)DD_TAGS_CAPACITY ? count : (int)DD_TAGS_CAPACITY;

    // Build NULL-terminated key array for the process context config.
    // Index LOCAL_ROOT_SPAN_ATTR_INDEX (0) is reserved for local_root_span_id; user keys start at index 1.
    // otel_process_ctx_publish copies all strings, so no strdup is needed.
    const char* key_ptrs[DD_TAGS_CAPACITY + 2]; // +1 reserved, +1 null
    key_ptrs[LOCAL_ROOT_SPAN_ATTR_INDEX] = "datadog.local_root_span_id";
    for (int i = 0; i < n; i++) {
        key_ptrs[i + 1] = keys[i];
    }
    key_ptrs[n + 1] = nullptr;

    otel_thread_ctx_config_data config = {
        .schema_version = "tlsdesc_v1_dev",
        .attribute_key_map = key_ptrs,
    };

#ifndef OTEL_PROCESS_CTX_NO_READ
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

void ContextApi::registerAttributeKeys(const std::vector<std::string>& keys) {
    // Clip to DD_TAGS_CAPACITY before materializing C string pointers.
    size_t n = keys.size() < DD_TAGS_CAPACITY ? keys.size() : DD_TAGS_CAPACITY;
    const char* key_ptrs[DD_TAGS_CAPACITY];
    for (size_t i = 0; i < n; i++) {
        key_ptrs[i] = keys[i].c_str();
    }
    registerAttributeKeys(key_ptrs, (int)n);
}
