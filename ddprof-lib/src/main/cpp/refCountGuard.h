/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
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
 * - Constructor: store active_ptr (RELEASE) first, then increment count (RELEASE)
 * - Destructor:  decrement count (RELEASE) first, then clear active_ptr (RELEASE)
 * - Scanner:     load count (ACQUIRE); if 0, also load active_ptr (ACQUIRE);
 *                treat the slot as active if either count > 0 or active_ptr != null
 *
 * The scanner checks active_ptr even when count==0 to cover the non-reentrant
 * constructor's activation window (active_ptr stored but count not yet incremented)
 * and the destructor's deactivation window (count decremented but active_ptr not yet
 * cleared).  The RELEASE/ACQUIRE pairing on active_ptr itself guarantees the scanner
 * sees the stored value if it was written before the load in program order.
 *
 * REENTRANT NESTING: when a signal fires inside an outer guard (same thread),
 * the nested guard stores its resource in nested[depth - 1] and leaves
 * active_ptr alone.  Every resource therefore stays in one place for as long
 * as it is protected - the root guard's in active_ptr, each nested guard's in
 * its nested[] entry - so a scan that reads active_ptr and then nested[] sees
 * it no matter how many nested guards start or end during the scan.  (When a
 * nested guard moved the outer resource out of active_ptr and back, a scan
 * could read each location while the resource was in the other one.)
 * nested is sized to NESTED_DEPTH; deeper nesting emits a one-time warning and
 * that guard's resource is invisible to the scanner (rare: it requires
 * NESTED_DEPTH+1 nested signal deliveries on the same thread).
 * Ordering: nested[i] is stored after count++ and cleared before count--.
 */
struct alignas(DEFAULT_CACHE_LINE_SIZE) RefCountSlot {
    static constexpr int NESTED_DEPTH = 3;

    volatile uint32_t count;                                // Reference count (0 = inactive)
    alignas(alignof(void*)) void* active_ptr;               // The root (outermost) guard's resource
    void* nested[NESTED_DEPTH];                             // Resources of reentrant (nested) guards
    // Trailing padding fills the cache line.
    // Layout on 64-bit: count(4) + 4-byte gap + active_ptr(8) + NESTED_DEPTH * 8.
    char padding[DEFAULT_CACHE_LINE_SIZE - alignof(void*) - (1 + NESTED_DEPTH) * sizeof(void*)];

    RefCountSlot() : count(0), active_ptr(nullptr), nested{}, padding{} {
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
 * - Scanner checks both count and active_ptr to close the activation window
 *
 * Reentrancy:
 * - A signal handler may create a RefCountGuard while a JNI thread already
 *   holds one on the same slot (same tid).  getThreadRefCountSlot() returns
 *   slot + MAX_THREADS to signal this case.  The nested guard records its
 *   resource in the slot's nested[] entry for its depth and never touches
 *   active_ptr, which keeps the outer guard's resource throughout.
 * - Constructor: count incremented, then nested[depth - 1] stored.
 *   Destructor: nested[depth - 1] cleared, then count decremented.
 */
class RefCountGuard {
public:
    static constexpr int MAX_THREADS = 8192;
    static constexpr int MAX_PROBE_DISTANCE = 32;
    static constexpr int NESTED_DEPTH = RefCountSlot::NESTED_DEPTH;

    static RefCountSlot refcount_slots[MAX_THREADS];
    static int slot_owners[MAX_THREADS];

private:
    bool  _active;
    bool  _is_reentrant;
    int   _nested_index;   // index into RefCountSlot::nested, or -1 if not recorded
    int   _my_slot;

    // Returns slot index in [0, MAX_THREADS) on fresh claim.
    // Returns slot + MAX_THREADS when the calling thread already owns that slot
    // (reentrant signal delivery); the guard then records its resource in nested[].
    static int getThreadRefCountSlot();

    // Ends this guard's protection on its slot; no-op if inactive.
    void release();

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

    /**
     * Waits for every in-flight guard referencing any of the count resources
     * in targets to be released, giving up after ~500ms.
     *
     * Only the targets are considered, so guards on unrelated resources can
     * neither delay nor time out this drain.  Nothing is logged or counted on
     * timeout; the caller decides how to react.
     *
     * @return true when no guard referenced a target on the final scan;
     *         false on timeout, in which case the targets must not be freed
     *         or reset because an accessor may still be using them.
     */
    [[nodiscard]] static bool tryWaitForRefCountsToClear(void* const* targets, int count);

    /**
     * One scan of all slots, without waiting.
     *
     * @return true if any slot references any of the count resources in
     *         targets, as active_ptr or as a nested guard's resource.
     */
    static bool isReferenced(void* const* targets, int count);
};

#endif // _REFCOUNTGUARD_H
