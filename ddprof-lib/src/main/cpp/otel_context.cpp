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
#include "os.h"
#include "common.h"  // For TEST_LOG

#include <sys/mman.h>
#include <string.h>

#ifdef __linux__
#include <sys/prctl.h>
#ifndef PR_SET_VMA
#define PR_SET_VMA 0x53564d41
#endif
#ifndef PR_SET_VMA_ANON_NAME
#define PR_SET_VMA_ANON_NAME 0
#endif
#endif

// Static member initialization
OtelContextHeader* OtelContexts::_buffer = nullptr;
size_t OtelContexts::_buffer_size = 0;
size_t OtelContexts::_capacity = 0;

// V2 context record storage and pointer for external profiler discovery.
// Since OtelContextV2Record has a flexible array member, we allocate a fixed-size
// buffer that can hold the header plus attributes data.
// Thread-local buffer for per-thread V2 records (header + attrs_data space).
static thread_local alignas(4) u8 otel_context_v2_buffer[V2_DEFAULT_MAX_RECORD_SIZE] = {};
static thread_local OtelContextV2Record* otel_context_v2_record =
    reinterpret_cast<OtelContextV2Record*>(otel_context_v2_buffer);

// External profiler discovery symbol - points to the active V2 record or nullptr.
DLLEXPORT thread_local OtelContextV2Record* custom_labels_current_set_v2 = nullptr;

/**
 * Helper to write a 64-bit value as big-endian bytes.
 */
static inline void write_be64(u8* dest, u64 value) {
  dest[0] = (value >> 56) & 0xFF;
  dest[1] = (value >> 48) & 0xFF;
  dest[2] = (value >> 40) & 0xFF;
  dest[3] = (value >> 32) & 0xFF;
  dest[4] = (value >> 24) & 0xFF;
  dest[5] = (value >> 16) & 0xFF;
  dest[6] = (value >> 8) & 0xFF;
  dest[7] = value & 0xFF;
}

/**
 * Helper to read a 64-bit value from big-endian bytes.
 */
static inline u64 read_be64(const u8* src) {
  return ((u64)src[0] << 56) | ((u64)src[1] << 48) |
         ((u64)src[2] << 40) | ((u64)src[3] << 32) |
         ((u64)src[4] << 24) | ((u64)src[5] << 16) |
         ((u64)src[6] << 8)  | (u64)src[7];
}

/**
 * Updates the V2 context record when context changes.
 * Called internally when OtelContexts::set() is invoked.
 *
 * Record layout (tlsdesc_v1_dev schema):
 *   trace_id[16]       - bytes 0-15: 128-bit trace ID (network order / big-endian)
 *   span_id[8]         - bytes 16-23: 64-bit span ID (network order / big-endian)
 *   valid[1]           - byte 24: non-zero if record is valid
 *   _padding[1]        - byte 25: padding for alignment
 *   attrs_data_size[2] - bytes 26-27: size of attrs_data (little-endian u16)
 *   attrs_data[]       - bytes 28+: [key_index:1][length:1][value:length]...
 */
static void updateV2Record(u64 trace_id_high, u64 trace_id_low, u64 span_id) {
  // Clear valid flag first (atomic visibility)
  otel_context_v2_record->valid = 0;
  __atomic_thread_fence(__ATOMIC_SEQ_CST);

  // Write trace_id (16 bytes, big-endian: high part first, then low part)
  write_be64(otel_context_v2_record->trace_id, trace_id_high);
  write_be64(otel_context_v2_record->trace_id + 8, trace_id_low);

  // Write span_id (8 bytes, big-endian)
  write_be64(otel_context_v2_record->span_id, span_id);

  // No attributes for now
  otel_context_v2_record->_padding = 0;
  otel_context_v2_record->attrs_data_size = 0;

  // Memory fence before setting valid
  __atomic_thread_fence(__ATOMIC_SEQ_CST);

  // Set valid flag and pointer
  otel_context_v2_record->valid = 1;
  custom_labels_current_set_v2 = otel_context_v2_record;

  TEST_LOG("updateV2Record: tid=%d ptr=%p trace_high=0x%llx trace_low=0x%llx span=0x%llx",
           OS::threadId(), (void*)custom_labels_current_set_v2,
           (unsigned long long)trace_id_high, (unsigned long long)trace_id_low,
           (unsigned long long)span_id);
}

/**
 * Clears the V2 context record.
 */
static void clearV2Record() {
  otel_context_v2_record->valid = 0;
  custom_labels_current_set_v2 = nullptr;
  TEST_LOG("clearV2Record: tid=%d cleared context", OS::threadId());
}

bool OtelContexts::initialize(size_t capacity) {
    if (_buffer != nullptr) {
        // Already initialized
        return true;
    }

    // Calculate buffer size: header + slots array
    size_t slots_offset = sizeof(OtelContextHeader);
    // Align slots to slot size for proper alignment
    slots_offset = (slots_offset + sizeof(OtelContextSlot) - 1) & ~(sizeof(OtelContextSlot) - 1);
    size_t total_size = slots_offset + capacity * sizeof(OtelContextSlot);

    // Create anonymous mmap
    void* ptr = mmap(nullptr, total_size, PROT_READ | PROT_WRITE,
                     MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED) {
        return false;
    }

    // Zero-initialize the buffer
    memset(ptr, 0, total_size);

    // Initialize header
    OtelContextHeader* header = static_cast<OtelContextHeader*>(ptr);
    header->magic = OTEL_CONTEXT_MAGIC;
    header->version = OTEL_CONTEXT_VERSION;
    header->capacity = static_cast<u32>(capacity);
    header->slot_size = static_cast<u32>(sizeof(OtelContextSlot));

#ifdef __linux__
    // Name the region for discovery via /proc/<pid>/maps
    // This creates an entry like: [anon:DD_OTEL_CTX]
    // Note: PR_SET_VMA_ANON_NAME requires kernel 5.17+
    // Failure is not fatal - discovery will still work via magic number scanning
    prctl(PR_SET_VMA, PR_SET_VMA_ANON_NAME, ptr, total_size, OTEL_CONTEXT_MMAP_NAME);
#endif

    _buffer = header;
    _buffer_size = total_size;
    _capacity = capacity;

    return true;
}

void OtelContexts::shutdown() {
    if (_buffer == nullptr) {
        return;
    }

    munmap(_buffer, _buffer_size);
    _buffer = nullptr;
    _buffer_size = 0;
    _capacity = 0;
}

bool OtelContexts::isInitialized() {
    return _buffer != nullptr;
}

OtelContextSlot* OtelContexts::getSlot(int tid) {
    if (_buffer == nullptr || _capacity == 0) {
        return nullptr;
    }

    // Calculate slot index using modulo
    // Note: TIDs that differ by multiples of _capacity will share the same slot.
    // With default capacity of 65536, this is acceptable for most workloads.
    // For extremely high TID values or long-running systems with TID recycling,
    // consider increasing capacity or implementing a TID-to-slot hash table.
    size_t index = static_cast<size_t>(tid) % _capacity;

    // Calculate slot address (slots start after header, properly aligned)
    size_t slots_offset = sizeof(OtelContextHeader);
    slots_offset = (slots_offset + sizeof(OtelContextSlot) - 1) & ~(sizeof(OtelContextSlot) - 1);

    char* slots_base = reinterpret_cast<char*>(_buffer) + slots_offset;
    return reinterpret_cast<OtelContextSlot*>(slots_base) + index;
}

void OtelContexts::set(u64 trace_id_high, u64 trace_id_low, u64 span_id) {
    // V2 TLS record is the primary storage - external profilers read from here
    // via the custom_labels_current_set_v2 symbol
    int tid = OS::threadId();
    TEST_LOG("OtelContexts::set: tid=%d trace_high=0x%llx trace_low=0x%llx span=0x%llx",
             tid, (unsigned long long)trace_id_high, (unsigned long long)trace_id_low,
             (unsigned long long)span_id);
    updateV2Record(trace_id_high, trace_id_low, span_id);
}

bool OtelContexts::get(u64& trace_id_high, u64& trace_id_low, u64& span_id) {
    // Read from V2 TLS record (primary storage)
    // This is a facade that presents the V2 record in the same API as before

    // Check if context is valid using acquire fence to synchronize with set()
    __atomic_thread_fence(__ATOMIC_ACQUIRE);

    if (custom_labels_current_set_v2 == nullptr || !otel_context_v2_record->valid) {
        TEST_LOG("OtelContexts::get() failed: ptr=%p valid=%d",
                 (void*)custom_labels_current_set_v2, (int)otel_context_v2_record->valid);
        return false;
    }

    // Read fields from V2 record (big-endian to native)
    trace_id_high = read_be64(otel_context_v2_record->trace_id);
    trace_id_low = read_be64(otel_context_v2_record->trace_id + 8);
    span_id = read_be64(otel_context_v2_record->span_id);

    TEST_LOG("OtelContexts::get() returning trace_high=0x%llx, trace_low=0x%llx, span=0x%llx",
             (unsigned long long)trace_id_high, (unsigned long long)trace_id_low,
             (unsigned long long)span_id);

    // Double-check validity after read
    __atomic_thread_fence(__ATOMIC_ACQUIRE);
    if (!otel_context_v2_record->valid) {
        return false;
    }

    return true;
}

bool OtelContexts::getByTid(int tid, u64& trace_id_high, u64& trace_id_low, u64& span_id) {
    // V2 TLS records are per-thread and cannot be read cross-thread from within
    // the process. External profilers use ptrace/process_vm_readv to read them.
    // If cross-thread reads are needed internally, use PROFILER mode with ContextApi.
    (void)tid;
    trace_id_high = 0;
    trace_id_low = 0;
    span_id = 0;
    return false;
}

void OtelContexts::clear() {
    // Clear the V2 record properly - set pointer to NULL and valid to 0
    // This matches the reference implementation behavior
    clearV2Record();
}

OtelContextHeader* OtelContexts::getBuffer() {
    return _buffer;
}

size_t OtelContexts::getBufferSize() {
    return _buffer_size;
}
