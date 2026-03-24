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

#ifndef _OTEL_CONTEXT_H
#define _OTEL_CONTEXT_H

#include "arch.h"
#include "asprof.h"
#include <cstdint>
#include <cstring>

// Max total record size including header
static const int OTEL_MAX_RECORD_SIZE = 640;
// Header: trace_id(16) + span_id(8) + valid(1) + reserved(1) + attrs_data_size(2) = 28
static const int OTEL_HEADER_SIZE = 28;
// Max space for attribute data
static const int OTEL_MAX_ATTRS_DATA_SIZE = OTEL_MAX_RECORD_SIZE - OTEL_HEADER_SIZE;

/**
 * OTEP #4947-compliant Thread Local Context Record.
 *
 * 640-byte packed structure matching the OTEP specification layout:
 *   offset 0x00: trace_id[16]      — W3C 128-bit trace ID (big-endian)
 *   offset 0x10: span_id[8]        — 64-bit span ID (big-endian)
 *   offset 0x18: valid             — 1 = record ready for reading
 *   offset 0x19: _reserved         — alignment padding
 *   offset 0x1A: attrs_data_size   — number of valid bytes in attrs_data
 *   offset 0x1C: attrs_data[612]   — encoded key/value attribute pairs
 *
 * Each attribute in attrs_data:
 *   key_index: uint8  — index into process context's attribute_key_map
 *   length:    uint8  — length of value string (max 255)
 *   value:     uint8[length] — UTF-8 value bytes
 *
 * Discovery: external profilers find the TLS pointer
 * custom_labels_current_set_v2 via ELF dynsym table.
 */
struct __attribute__((packed)) OtelThreadContextRecord {
    uint8_t  trace_id[16];
    uint8_t  span_id[8];
    uint8_t  valid;
    uint8_t  _reserved;        // OTEP spec: reserved for future use, must be 0
    uint16_t attrs_data_size;
    uint8_t  attrs_data[OTEL_MAX_ATTRS_DATA_SIZE];
};

// OTEP #4947 TLS pointer — MUST appear in dynsym for external profiler discovery
DLLEXPORT extern thread_local OtelThreadContextRecord* custom_labels_current_set_v2;

/**
 * OTEL context storage manager (OTEP #4947 TLS pointer model).
 *
 * Each thread gets a pre-allocated OtelThreadContextRecord cached in
 * ProfiledThread. The TLS pointer custom_labels_current_set_v2 is set
 * to the record when context is active, or nullptr when inactive.
 *
 * Signal safety: signal handlers must never access
 * custom_labels_current_set_v2 directly (TLS lazy init can deadlock
 * in musl). Instead they read via ProfiledThread::getOtelContextRecord().
 */
class OtelContexts {
public:
    /**
     * Read span_id from a record pointer (signal-safe).
     * Checks the valid flag with acquire semantics before reading.
     * Returns false if the record is null or invalid (being mutated).
     */
    static bool getSpanId(OtelThreadContextRecord* record, u64& span_id);

    // Byte conversion helpers (big-endian, W3C trace context)
    static void u64ToBytes(u64 val, uint8_t* out);
    static u64 bytesToU64(const uint8_t* in);
};

#endif /* _OTEL_CONTEXT_H */
