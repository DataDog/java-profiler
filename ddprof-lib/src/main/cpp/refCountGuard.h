/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _REFCOUNTGUARD_H
#define _REFCOUNTGUARD_H

#include "arch.h"
#include <stdint.h>
#include <type_traits>

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
 * the displaced active_ptr is parked in outer_stack[] so the scanner can still
 * see every resource currently in use on the slot.  outer_stack is sized to
 * OUTER_STACK_DEPTH; deeper nesting emits a one-time warning and the deepest
 * displaced resource becomes invisible to the scanner (rare: it requires
 * OUTER_STACK_DEPTH+1 nested signal deliveries on the same thread).
 * Ordering: outer_stack[i] must be stored AFTER count++ but BEFORE active_ptr
 * is overwritten; cleared AFTER active_ptr is restored but BEFORE count--.
 */
struct alignas(DEFAULT_CACHE_LINE_SIZE) RefCountSlot {
    static constexpr int OUTER_STACK_DEPTH = 3;

    uint32_t count;                                         // Reference count (0 = inactive); accessed only via __atomic_* builtins
    alignas(alignof(void*)) void* active_ptr;               // Which resource is being referenced
    void* outer_stack[OUTER_STACK_DEPTH];                   // Displaced resources on reentrant nesting
    // Trailing padding fills the cache line.
    // Layout on 64-bit: count(4) + 4-byte gap + active_ptr(8) + OUTER_STACK_DEPTH * 8.
    char padding[DEFAULT_CACHE_LINE_SIZE - alignof(void*) - (1 + OUTER_STACK_DEPTH) * sizeof(void*)];

    // constexpr so the static refcount_slots[] array is constant-initialized:
    // it stays in untouched zero-fill-on-demand .bss instead of having a load-time
    // dynamic initializer write every one of its pages (~512 KiB resident while idle).
    // count is deliberately not volatile: a volatile member makes the class a
    // non-literal type, which would defeat constant initialization.
    constexpr RefCountSlot() : count(0), active_ptr(nullptr), outer_stack{}, padding{} {}
};

static_assert(sizeof(RefCountSlot) == DEFAULT_CACHE_LINE_SIZE,
              "RefCountSlot must be exactly one cache line");
static_assert(std::is_trivially_destructible<RefCountSlot>::value,
              "RefCountSlot must stay trivially destructible to be constant-initialized");

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
 *   slot + MAX_THREADS to signal this case.  The inner guard saves and restores
 *   the outer guard's active_ptr instead of clearing it, so the scanner never
 *   sees a null pointer for an active outer guard.
 * - Ordering invariants differ for the reentrant case:
 *   Constructor: count incremented BEFORE overwriting active_ptr (outer resource
 *     stays visible to the scanner until the new pointer is installed).
 *   Destructor: active_ptr restored to saved outer pointer BEFORE decrementing
 *     count (scanner always sees outer resource while count is still elevated).
 */
class RefCountGuard {
public:
    static constexpr int MAX_THREADS = 8192;
    static constexpr int MAX_PROBE_DISTANCE = 32;
    static constexpr int OUTER_STACK_DEPTH = RefCountSlot::OUTER_STACK_DEPTH;

    static RefCountSlot refcount_slots[MAX_THREADS];
    static int slot_owners[MAX_THREADS];

private:
    bool  _active;
    bool  _is_reentrant;
    int   _outer_slot;     // index into RefCountSlot::outer_stack, or -1 if not parked
    int   _my_slot;
    void* _saved_ptr;

    // Returns slot index in [0, MAX_THREADS) on fresh claim.
    // Returns slot + MAX_THREADS when the calling thread already owns that slot
    // (reentrant signal delivery); the caller must save/restore active_ptr.
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
};

#endif // _REFCOUNTGUARD_H
