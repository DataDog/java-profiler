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
char* ContextApi::_attribute_keys[MAX_ATTRIBUTE_KEYS] = {};
int ContextApi::_attribute_key_count = 0;

void ContextApi::shutdown() {
    freeAttributeKeys();
}

/**
 * Initialize OTel TLS for the current thread on first use.
 * Triggers the first access to custom_labels_current_set_v2 (TLS init).
 * Must be called with signals blocked to prevent musl TLS deadlock.
 * The OtelThreadContextRecord is already zero-initialized by the ProfiledThread ctor.
 */
void ContextApi::initializeOtelTls(ProfiledThread* thrd) {
    SignalBlocker blocker;
    // Set the TLS pointer permanently to this thread's record.
    // First access here triggers TLS slot initialization (needed on musl).
    // The pointer remains stable for the thread's lifetime; external profilers
    // rely solely on the valid flag for consistency, not pointer nullness.
    custom_labels_current_set_v2 = thrd->getOtelContextRecord();
    thrd->markOtelContextInitialized();
}

bool ContextApi::get(u64& span_id, u64& root_span_id) {
    ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
    if (thrd == nullptr || !thrd->isOtelContextInitialized()) {
        return false;
    }

    if (!OtelContexts::getSpanId(thrd->getOtelContextRecord(), span_id)) {
        return false;
    }

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

void ContextApi::freeAttributeKeys() {
    int count = _attribute_key_count;
    _attribute_key_count = 0;
    for (int i = 0; i < count; i++) {
        char* key = _attribute_keys[i];
        _attribute_keys[i] = nullptr;
        free(key);
    }
}

void ContextApi::registerAttributeKeys(const char** keys, int count) {
    freeAttributeKeys();

    _attribute_key_count = count < MAX_ATTRIBUTE_KEYS ? count : MAX_ATTRIBUTE_KEYS;
    for (int i = 0; i < _attribute_key_count; i++) {
        _attribute_keys[i] = strdup(keys[i]);
    }

    // Build NULL-terminated key array for the process context config.
    // Index LOCAL_ROOT_SPAN_ATTR_INDEX (0) is reserved for local_root_span_id; user keys start at index 1.
    const char* key_ptrs[MAX_ATTRIBUTE_KEYS + 2]; // +1 reserved, +1 null
    key_ptrs[LOCAL_ROOT_SPAN_ATTR_INDEX] = "datadog.local_root_span_id";
    for (int i = 0; i < _attribute_key_count; i++) {
        key_ptrs[i + 1] = _attribute_keys[i];
    }
    key_ptrs[_attribute_key_count + 1] = nullptr;

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
