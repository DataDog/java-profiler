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

bool OtelContexts::_initialized = false;

void OtelContexts::initialize() {
    _initialized = true;
}

void OtelContexts::shutdown() {
    _initialized = false;
}

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

// NOT async-signal-safe — uses ProfiledThread::current() which may allocate.
// Must only be called from application threads.
OtelThreadContextRecord* OtelContexts::ensureRecord() {
    ProfiledThread* thrd = ProfiledThread::current();
    if (thrd == nullptr) {
        return nullptr;
    }
    return thrd->getOtelContextRecord();
}

void OtelContexts::set(u64 trace_id_high, u64 trace_id_low, u64 span_id) {
    OtelThreadContextRecord* record = ensureRecord();
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
    record->attrs_data_size = 0;

    // 4. Mark record valid
    __atomic_store_n(&record->valid, (uint8_t)1, __ATOMIC_RELEASE);

    // 5. Attach — publish completed record
    __atomic_store_n(&custom_labels_current_set_v2, record, __ATOMIC_RELEASE);
}

bool OtelContexts::setAttribute(uint8_t key_index, const char* value, uint8_t value_len) {
    OtelThreadContextRecord* record = ensureRecord();
    if (record == nullptr) {
        return false;
    }

    // Entry size: 1 (key_index) + 1 (length) + value_len
    uint16_t entry_size = 2 + value_len;
    uint16_t current_size = record->attrs_data_size;

    // Fast-path rejection before detach. If a duplicate key exists, compaction
    // below may free space, so this is conservative — but avoids unnecessary detach.
    if (current_size + entry_size > OTEL_MAX_ATTRS_DATA_SIZE) {
        return false;
    }

    // Detach (external readers) and invalidate (signal handler readers)
    __atomic_store_n(&custom_labels_current_set_v2, (OtelThreadContextRecord*)nullptr, __ATOMIC_RELEASE);
    __atomic_store_n(&record->valid, (uint8_t)0, __ATOMIC_RELEASE);

    // Scan for duplicate key and compact if found.
    // Before the duplicate is encountered, write_pos == read_pos (no movement needed).
    // After the duplicate is skipped, write_pos < read_pos and subsequent entries
    // are moved backward to close the gap.
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

const uint8_t* OtelContexts::readAttrsData(OtelThreadContextRecord* record, uint16_t& out_size) {
    if (record == nullptr || __atomic_load_n(&record->valid, __ATOMIC_ACQUIRE) != 1) {
        out_size = 0;
        return nullptr;
    }
    // Use a local copy to avoid taking address of packed member
    uint16_t size = record->attrs_data_size;
    __atomic_thread_fence(__ATOMIC_ACQUIRE);
    out_size = size;
    return record->attrs_data;
}

bool OtelContexts::get(u64& trace_id_high, u64& trace_id_low, u64& span_id) {
    ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
    if (thrd == nullptr || !thrd->isOtelContextInitialized()) {
        return false;
    }
    return readRecord(thrd->getOtelContextRecord(), trace_id_high, trace_id_low, span_id);
}

bool OtelContexts::readRecord(OtelThreadContextRecord* record,
                               u64& trace_id_high, u64& trace_id_low, u64& span_id) {
    if (record == nullptr) {
        return false;
    }

    // Check valid flag with acquire semantics
    if (__atomic_load_n(&record->valid, __ATOMIC_ACQUIRE) != 1) {
        return false;
    }

    trace_id_high = bytesToU64(record->trace_id);
    trace_id_low = bytesToU64(record->trace_id + 8);
    span_id = bytesToU64(record->span_id);
    return true;
}

void OtelContexts::clear() {
    // Must only be called from application threads (not signal handlers),
    // because ensureRecord() uses ProfiledThread::current() which is not signal-safe.
    // Invalidate the record first so readRecord() via cached pointer returns false.
    OtelThreadContextRecord* record = ensureRecord();
    if (record != nullptr) {
        __atomic_store_n(&record->valid, (uint8_t)0, __ATOMIC_RELEASE);
        record->attrs_data_size = 0;
    }
    // OTEP context detachment: set TLS pointer to nullptr
    __atomic_store_n(&custom_labels_current_set_v2, (OtelThreadContextRecord*)nullptr, __ATOMIC_RELEASE);
}
