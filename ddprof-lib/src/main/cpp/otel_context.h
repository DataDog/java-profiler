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
#include <cstddef>

/**
 * OTEL-compatible thread context storage.
 *
 * This module implements thread-level context storage that is discoverable
 * by external profilers following the OTEL profiling context proposal.
 *
 * Discovery mechanism:
 * - Linux: The mmap region is named via prctl(PR_SET_VMA_ANON_NAME) and
 *   can be discovered by scanning /proc/<pid>/maps for [anon:DD_OTEL_CTX]
 *
 * Storage layout:
 * - Header with magic number, version, capacity, and slot size
 * - Array of slots indexed by TID % capacity
 *
 * Torn-read protection:
 * - Uses in_use flag (0 = valid, 1 = writing) with memory barriers
 * - Reader must check in_use before and after reading fields
 */

// Name used for mmap discovery via /proc/<pid>/maps
#define OTEL_CONTEXT_MMAP_NAME "DD_OTEL_CTX"

// Magic number for buffer validation (ASCII "OTEL")
static const u32 OTEL_CONTEXT_MAGIC = 0x4F54454C;

// Protocol version
static const u32 OTEL_CONTEXT_VERSION = 1;

// Default capacity (number of thread slots)
static const size_t OTEL_CONTEXT_DEFAULT_CAPACITY = 65536;

/**
 * Per-thread context slot in the OTEL ring buffer.
 *
 * Layout follows OTEL proposal with 128-bit trace ID split into two 64-bit words
 * for atomic access. Aligned to 32 bytes to minimize cache line contention.
 */
struct alignas(32) OtelContextSlot {
    volatile u64 trace_id_high;  // Upper 64 bits of 128-bit trace ID
    volatile u64 trace_id_low;   // Lower 64 bits of 128-bit trace ID
    volatile u64 span_id;        // 64-bit span ID
    volatile u8  in_use;         // 0 = valid, 1 = writing (torn-read protection)
    u8 _padding[7];              // Align to 32 bytes
};

/**
 * OTEL context buffer header.
 *
 * This header is placed at the start of the mmap region and allows
 * external readers to validate and parse the buffer.
 */
struct OtelContextHeader {
    u32 magic;       // Must be OTEL_CONTEXT_MAGIC (0x4F54454C)
    u32 version;     // Protocol version (currently 1)
    u32 capacity;    // Number of slots in the buffer
    u32 slot_size;   // Size of each slot (sizeof(OtelContextSlot))
    // Slot array follows immediately after header
};

/**
 * OTEL context storage manager.
 *
 * Provides thread-safe context storage that can be discovered and read
 * by external profilers. Uses a ring buffer indexed by TID % capacity.
 *
 * Thread safety:
 * - set() uses in_use flag with memory barriers for torn-read protection
 * - get() and getByTid() return false if a write is in progress
 */
class OtelContexts {
public:
    /**
     * Initialize the OTEL context buffer.
     *
     * Creates an anonymous mmap region and names it for discovery.
     * Should be called once during profiler startup when OTEL mode is enabled.
     *
     * @param capacity Number of thread slots (default: 65536)
     * @return true if initialization succeeded, false otherwise
     */
    static bool initialize(size_t capacity = OTEL_CONTEXT_DEFAULT_CAPACITY);

    /**
     * Shutdown and release the OTEL context buffer.
     *
     * Unmaps the memory region. Should be called during profiler shutdown.
     */
    static void shutdown();

    /**
     * Check if OTEL context storage is initialized.
     *
     * @return true if initialized, false otherwise
     */
    static bool isInitialized();

    /**
     * Write context for the current thread.
     *
     * Uses the calling thread's TID to determine the slot.
     * Thread-safe: uses in_use flag with memory barriers.
     *
     * @param trace_id_high Upper 64 bits of 128-bit trace ID
     * @param trace_id_low Lower 64 bits of 128-bit trace ID (rootSpanId for Datadog)
     * @param span_id 64-bit span ID
     */
    static void set(u64 trace_id_high, u64 trace_id_low, u64 span_id);

    /**
     * Read context for the current thread.
     *
     * Uses the calling thread's TID to determine the slot.
     * Returns false if a write is in progress (torn read would occur).
     *
     * @param trace_id_high Output: upper 64 bits of trace ID
     * @param trace_id_low Output: lower 64 bits of trace ID
     * @param span_id Output: span ID
     * @return true if read succeeded, false if write in progress
     */
    static bool get(u64& trace_id_high, u64& trace_id_low, u64& span_id);

    /**
     * Read context for a specific thread by TID.
     *
     * Used by wall-clock JVMTI sampling and external profilers.
     * Returns false if a write is in progress (torn read would occur).
     *
     * @param tid Thread ID to read context for
     * @param trace_id_high Output: upper 64 bits of trace ID
     * @param trace_id_low Output: lower 64 bits of trace ID
     * @param span_id Output: span ID
     * @return true if read succeeded, false if write in progress
     */
    static bool getByTid(int tid, u64& trace_id_high, u64& trace_id_low, u64& span_id);

    /**
     * Clear context for the current thread.
     *
     * Sets all context fields to zero.
     */
    static void clear();

    /**
     * Get the base address of the OTEL context buffer.
     *
     * Used for testing and external access.
     *
     * @return Pointer to the buffer header, or nullptr if not initialized
     */
    static OtelContextHeader* getBuffer();

    /**
     * Get the size of the OTEL context buffer in bytes.
     *
     * @return Buffer size, or 0 if not initialized
     */
    static size_t getBufferSize();

private:
    static OtelContextHeader* _buffer;
    static size_t _buffer_size;
    static size_t _capacity;

    /**
     * Get the slot pointer for a given TID.
     *
     * @param tid Thread ID
     * @return Pointer to the slot, or nullptr if buffer not initialized
     */
    static OtelContextSlot* getSlot(int tid);
};

#endif /* _OTEL_CONTEXT_H */
