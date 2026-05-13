/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _REFCOUNTGUARD_H
#define _REFCOUNTGUARD_H

#include "arch.h"
#include <stdint.h>

/**
 * Cache-aligned reference counting slot for thread-local reference counting.
 * Each slot occupies a full cache line (64 bytes) to eliminate false sharing.
 *
 * ACTIVATION PROTOCOL (pointer-first):
 * - Constructor: store active_ptr first, then increment count
 * - Destructor:  decrement count first, then clear active_ptr
 * - Scanner:     check count; if 0, skip slot (treats it as inactive)
 *
 * There is a brief activation window between the store of active_ptr and the
 * increment of count where the scanner sees count=0 and may skip the slot.
 * For signal handlers this window is never observed in practice: handlers
 * complete within microseconds while a buffer can only be cleared after TWO
 * full dump cycles (typically seconds).  If the window were hit, the operation
 * would return INT_MAX (miss) — an observable incorrect-state outcome that
 * callers handle as a dropped trace or generic vtable frame, not a crash.
 */
struct alignas(DEFAULT_CACHE_LINE_SIZE) RefCountSlot {
    volatile uint32_t count;                    // Reference count (0 = inactive)
    alignas(alignof(void*)) void* active_ptr;   // Which resource is being referenced
    // Remaining padding: accounts for the alignment gap between count and active_ptr.
    // Formula: total - alignof(void*) - sizeof(void*) is correct on both 32-bit and
    // 64-bit because alignof(void*) equals sizeof(uint32_t) + implicit_gap on 64-bit.
    char padding[DEFAULT_CACHE_LINE_SIZE - alignof(void*) - sizeof(void*)];

    RefCountSlot() : count(0), active_ptr(nullptr), padding{} {
        static_assert(sizeof(RefCountSlot) == DEFAULT_CACHE_LINE_SIZE,
                      "RefCountSlot must be exactly one cache line");
    }
};

/**
 * RAII guard for thread-local reference counting.
 *
 * Provides lock-free memory reclamation for any heap-allocated resource that
 * may be accessed from signal handlers concurrently with deallocation.
 * Uses the pointer-first protocol to avoid race conditions.
 *
 * Performance: ~44-94 cycles hot-path; thread-local cache line, zero contention.
 *
 * Correctness:
 * - Pointer stored BEFORE count increment (activation)
 * - Count decremented BEFORE pointer cleared (deactivation)
 * - Scanner checks count first, ensuring consistent view
 */
class RefCountGuard {
public:
    static constexpr int MAX_THREADS = 8192;
    static constexpr int MAX_PROBE_DISTANCE = 32;

    static RefCountSlot refcount_slots[MAX_THREADS];
    static int slot_owners[MAX_THREADS];

private:
    bool _active;
    int _my_slot;

    static int getThreadRefCountSlot();

public:
    explicit RefCountGuard(void* resource);
    ~RefCountGuard();

    RefCountGuard(const RefCountGuard&) = delete;
    RefCountGuard& operator=(const RefCountGuard&) = delete;

    RefCountGuard(RefCountGuard&& other) noexcept;
    RefCountGuard& operator=(RefCountGuard&& other) noexcept;

    bool isActive() const { return _active; }

    // Wait for all in-flight guards protecting ptr_to_delete to be released.
    static void waitForRefCountToClear(void* ptr_to_delete);

    // Wait for ALL reference counts to clear.
    static void waitForAllRefCountsToClear();
};

#endif // _REFCOUNTGUARD_H
