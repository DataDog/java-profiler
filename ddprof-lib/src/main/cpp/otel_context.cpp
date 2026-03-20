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

void OtelContexts::set(OtelThreadContextRecord* record, u64 trace_id_high, u64 trace_id_low, u64 span_id, u64 local_root_span_id) {
    if (record == nullptr) {
        return;
    }

    // OTEP publication protocol:
    // 1. Detach — external readers see no record during construction
    __atomic_store_n(&custom_labels_current_set_v2, (OtelThreadContextRecord*)nullptr, __ATOMIC_RELEASE);

    // 2. Invalidate — internal readers (signal handlers using cached pointer) see invalid record
    __atomic_store_n(&record->valid, (uint8_t)0, __ATOMIC_RELEASE);

    // 3. Populate record fields
    u64ToBytes(trace_id_high, record->trace_id);
    u64ToBytes(trace_id_low, record->trace_id + 8);
    u64ToBytes(span_id, record->span_id);

    // 4. Rebuild attrs_data: preserve user entries (key_index != 0), replace LRS entry.
    //    LOCAL_ROOT_SPAN_ATTR_INDEX = 0 is reserved; user attrs use key_index >= 1.
    //    Use a temp buffer because source and destination regions overlap.
    uint16_t old_size = record->attrs_data_size;
    uint8_t user_buf[OTEL_MAX_ATTRS_DATA_SIZE];
    uint16_t user_size = 0;

    uint16_t pos = 0;
    while (pos + 2 <= old_size) {
        uint8_t k = record->attrs_data[pos];
        uint8_t len = record->attrs_data[pos + 1];
        if (pos + 2 + len > old_size) break;
        if (k != 0) {
            memcpy(user_buf + user_size, record->attrs_data + pos, 2 + len);
            user_size += 2 + len;
        }
        pos += 2 + len;
    }

    uint16_t new_size = 0;

    // Write local_root_span_id as hex string attribute at reserved index 0
    if (local_root_span_id != 0) {
        static const char hex_chars[] = "0123456789abcdef";
        record->attrs_data[0] = 0;   // key_index = LOCAL_ROOT_SPAN_ATTR_INDEX
        record->attrs_data[1] = 16;  // length
        u64 v = local_root_span_id;
        for (int i = 17; i >= 2; i--) {
            record->attrs_data[i] = hex_chars[v & 0xF];
            v >>= 4;
        }
        new_size = 18;
    }

    // Re-append preserved user entries
    if (user_size > 0 && new_size + user_size <= OTEL_MAX_ATTRS_DATA_SIZE) {
        memcpy(record->attrs_data + new_size, user_buf, user_size);
        new_size += user_size;
    }

    record->attrs_data_size = new_size;

    // 5. Mark record valid
    __atomic_store_n(&record->valid, (uint8_t)1, __ATOMIC_RELEASE);

    // 6. Attach — publish completed record
    __atomic_store_n(&custom_labels_current_set_v2, record, __ATOMIC_RELEASE);
}

bool OtelContexts::getSpanId(OtelThreadContextRecord* record, u64& span_id) {
    if (record == nullptr) {
        return false;
    }
    if (__atomic_load_n(&record->valid, __ATOMIC_ACQUIRE) != 1) {
        return false;
    }
    span_id = bytesToU64(record->span_id);
    return true;
}

bool OtelContexts::setAttribute(OtelThreadContextRecord* record, uint8_t key_index, const char* value, uint8_t value_len) {
    if (record == nullptr) {
        return false;
    }

    // Entry size: 1 (key_index) + 1 (length) + value_len
    uint16_t entry_size = 2 + value_len;
    uint16_t current_size = record->attrs_data_size;

    // Fast-path rejection before detach
    if (current_size + entry_size > OTEL_MAX_ATTRS_DATA_SIZE) {
        return false;
    }

    // Detach (external readers) and invalidate (signal handler readers)
    __atomic_store_n(&custom_labels_current_set_v2, (OtelThreadContextRecord*)nullptr, __ATOMIC_RELEASE);
    __atomic_store_n(&record->valid, (uint8_t)0, __ATOMIC_RELEASE);

    // Scan for duplicate key and compact if found
    uint16_t read_pos = 0;
    uint16_t write_pos = 0;
    bool found = false;
    while (read_pos + 2 <= current_size) {
        uint8_t k = record->attrs_data[read_pos];
        uint8_t len = record->attrs_data[read_pos + 1];
        if (read_pos + 2 + len > current_size) break;  // corrupt length guard
        if (k == key_index) {
            found = true;
            read_pos += 2 + len;
        } else {
            if (found && write_pos < read_pos) {
                memmove(record->attrs_data + write_pos, record->attrs_data + read_pos, 2 + len);
            }
            write_pos += 2 + len;
            read_pos += 2 + len;
        }
    }
    if (found) {
        current_size = write_pos;
    }

    // Re-check fit after compaction
    if (current_size + entry_size > OTEL_MAX_ATTRS_DATA_SIZE) {
        record->attrs_data_size = current_size;
        __atomic_store_n(&record->valid, (uint8_t)1, __ATOMIC_RELEASE);
        __atomic_store_n(&custom_labels_current_set_v2, record, __ATOMIC_RELEASE);
        return false;
    }

    // Append the new entry
    record->attrs_data[current_size] = key_index;
    record->attrs_data[current_size + 1] = value_len;
    memcpy(record->attrs_data + current_size + 2, value, value_len);
    record->attrs_data_size = current_size + entry_size;

    // Re-publish
    __atomic_store_n(&record->valid, (uint8_t)1, __ATOMIC_RELEASE);
    __atomic_store_n(&custom_labels_current_set_v2, record, __ATOMIC_RELEASE);
    return true;
}

void OtelContexts::clear(OtelThreadContextRecord* record) {
    if (record != nullptr) {
        __atomic_store_n(&record->valid, (uint8_t)0, __ATOMIC_RELEASE);
        record->attrs_data_size = 0;
    }
    // OTEP context detachment: set TLS pointer to nullptr
    __atomic_store_n(&custom_labels_current_set_v2, (OtelThreadContextRecord*)nullptr, __ATOMIC_RELEASE);
}
