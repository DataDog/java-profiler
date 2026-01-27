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
    int tid = OS::threadId();
    OtelContextSlot* slot = getSlot(tid);
    if (slot == nullptr) {
        return;
    }

    // Mark write in progress using atomic store with release semantics
    // This ensures proper memory ordering on weakly-ordered architectures (ARM64)
    __atomic_store_n(&slot->in_use, 1, __ATOMIC_RELEASE);

    // Write fields using atomic stores with relaxed ordering
    // The release barrier above ensures these are visible after in_use=1
    // The release barrier below ensures these complete before in_use=0
    __atomic_store_n(&slot->trace_id_high, trace_id_high, __ATOMIC_RELAXED);
    __atomic_store_n(&slot->trace_id_low, trace_id_low, __ATOMIC_RELAXED);
    __atomic_store_n(&slot->span_id, span_id, __ATOMIC_RELAXED);

    // Mark write complete with release semantics to ensure all prior writes
    // are visible to readers before they see in_use=0
    __atomic_store_n(&slot->in_use, 0, __ATOMIC_RELEASE);
}

bool OtelContexts::get(u64& trace_id_high, u64& trace_id_low, u64& span_id) {
    return getByTid(OS::threadId(), trace_id_high, trace_id_low, span_id);
}

bool OtelContexts::getByTid(int tid, u64& trace_id_high, u64& trace_id_low, u64& span_id) {
    OtelContextSlot* slot = getSlot(tid);
    if (slot == nullptr) {
        return false;
    }

    // Check if write in progress using atomic load with acquire semantics
    // This synchronizes with the release store in set() and ensures we see
    // all prior writes if in_use=0
    if (__atomic_load_n(&slot->in_use, __ATOMIC_ACQUIRE)) {
        return false;
    }

    // Read fields using atomic loads with relaxed ordering
    // The acquire barrier above ensures we see all writes that completed before in_use=0
    trace_id_high = __atomic_load_n(&slot->trace_id_high, __ATOMIC_RELAXED);
    trace_id_low = __atomic_load_n(&slot->trace_id_low, __ATOMIC_RELAXED);
    span_id = __atomic_load_n(&slot->span_id, __ATOMIC_RELAXED);

    // Double-check that no write started during our read
    // Uses acquire semantics to ensure we don't reorder reads after this check
    if (__atomic_load_n(&slot->in_use, __ATOMIC_ACQUIRE)) {
        return false;
    }

    return true;
}

void OtelContexts::clear() {
    set(0, 0, 0);
}

OtelContextHeader* OtelContexts::getBuffer() {
    return _buffer;
}

size_t OtelContexts::getBufferSize() {
    return _buffer_size;
}
