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

#include <cassert>
#include "otel_context.h"
#include "thread.h"

// OTEP #4947 TLS pointer — visible in dynsym for external profiler discovery
DLLEXPORT thread_local OtelThreadContextRecord* custom_labels_current_set_v2 = nullptr;

void OtelContexts::u64ToBytes(u64 val, uint8_t* out) {
    for (int i = 7; i >= 0; i--) {
        out[i] = val & 0xFF;
        val >>= 8;
    }
}

u64 OtelContexts::bytesToU64(const uint8_t* in) {
    u64 val = 0;
    for (int i = 0; i < 8; i++) {
        val = (val << 8) | in[i];
    }
    return val;
}

bool OtelContexts::getSpanId(OtelThreadContextRecord* record, u64& span_id) {
    assert(record != nullptr);
    if (__atomic_load_n(&record->valid, __ATOMIC_ACQUIRE) != 1) {
        return false;
    }
    span_id = bytesToU64(record->span_id);
    return true;
}

