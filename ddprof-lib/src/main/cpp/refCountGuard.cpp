/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "refCountGuard.h"
#include "arch.h"
#include "counters.h"
#include "log.h"
#include "os.h"
#include "primeProbing.h"
#include "thread.h"
#include <atomic>
#include <time.h>

// Static member definitions
RefCountSlot RefCountGuard::refcount_slots[RefCountGuard::MAX_THREADS];
int RefCountGuard::slot_owners[RefCountGuard::MAX_THREADS];

// One-time warning latch: emit at most one Log::warn per process when
// reentrant nesting exceeds OUTER_STACK_DEPTH and the scanner can no longer
// see every displaced resource on the slot.
static std::atomic<bool> s_outer_stack_overflow_warned{false};

int RefCountGuard::getThreadRefCountSlot() {
    ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
    int tid = thrd != nullptr ? thrd->tid() : OS::threadId();

    HashProbe probe(static_cast<u64>(tid), MAX_THREADS);

    int slot = probe.slot();
    for (int i = 0; i < MAX_PROBE_DISTANCE; i++) {
        int expected = 0;
        if (__atomic_compare_exchange_n(&slot_owners[slot], &expected, tid, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)) {
            return slot;
        }

        if (__atomic_load_n(&slot_owners[slot], __ATOMIC_ACQUIRE) == tid) {
            // Only treat as reentrant if the outer guard is still active.
            // When count==0 the outer guard has already decremented and is
            // just clearing slot_owners; creating a "reentrant" guard on a
            // dying slot would publish active_ptr while the outer destructor
            // is about to overwrite it, causing waitForRefCountToClear to
            // miss the new resource.
            if (__atomic_load_n(&refcount_slots[slot].count, __ATOMIC_ACQUIRE) > 0) {
                return slot + MAX_THREADS;
            }
            // Fall through: probe for a fresh slot instead.
        }

        if (probe.hasNext()) {
            slot = probe.next();
        }
    }

    return -1;
}

RefCountGuard::RefCountGuard(void* resource) : _active(true), _is_reentrant(false), _outer_slot(-1), _my_slot(-1), _saved_ptr(nullptr) {
    int raw = getThreadRefCountSlot();

    if (raw == -1) {
        _active = false;
        return;
    }

    _is_reentrant = (raw >= MAX_THREADS);
    _my_slot = _is_reentrant ? (raw - MAX_THREADS) : raw;

    if (_is_reentrant) {
        _saved_ptr = __atomic_load_n(&refcount_slots[_my_slot].active_ptr, __ATOMIC_ACQUIRE);
        // Reentrant: increment count first so the scanner always sees the outer
        // resource while active_ptr is being updated.  fetch_add returns the
        // PRE-increment count, which is the reentrancy depth this guard is
        // about to occupy (depth 1 = first nested signal, depth 2 = second...).
        uint32_t prev_count = __atomic_fetch_add(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
        // Park the displaced active_ptr in outer_stack[prev_count - 1] so
        // waitForRefCountToClear() can see every resource currently in use
        // on this slot.  outer_stack[0] holds the outermost (root) resource.
        int idx = static_cast<int>(prev_count) - 1;
        if (idx >= 0 && idx < OUTER_STACK_DEPTH) {
            _outer_slot = idx;
            __atomic_store_n(&refcount_slots[_my_slot].outer_stack[idx], _saved_ptr, __ATOMIC_RELEASE);
        } else {
            // Reentrant nesting deeper than OUTER_STACK_DEPTH; the displaced
            // resource lives only in this guard's _saved_ptr and is invisible
            // to the scanner.  Latch a single warning per process.
            bool expected = false;
            if (s_outer_stack_overflow_warned.compare_exchange_strong(expected, true, std::memory_order_relaxed)) {
                Log::warn("RefCountGuard reentrancy depth %u exceeds OUTER_STACK_DEPTH=%d; scanner may miss intermediate resources",
                          static_cast<unsigned>(prev_count) + 1, OUTER_STACK_DEPTH);
            }
        }
        __atomic_store_n(&refcount_slots[_my_slot].active_ptr, resource, __ATOMIC_RELEASE);
    } else {
        // Non-reentrant (count was 0): store pointer first so the scanner skips
        // this slot during the activation window (count=0 → treated as inactive).
        __atomic_store_n(&refcount_slots[_my_slot].active_ptr, resource, __ATOMIC_RELEASE);
        __atomic_fetch_add(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
    }
}

RefCountGuard::~RefCountGuard() {
    if (_active && _my_slot >= 0) {
        if (_is_reentrant) {
            // Restore outer active_ptr first, then (if we parked one) clear our
            // outer_stack slot, then decrement count.  Scanner always observes
            // the outer resource while count > 0.
            __atomic_store_n(&refcount_slots[_my_slot].active_ptr, _saved_ptr, __ATOMIC_RELEASE);
            if (_outer_slot >= 0) {
                __atomic_store_n(&refcount_slots[_my_slot].outer_stack[_outer_slot], nullptr, __ATOMIC_RELEASE);
            }
            __atomic_fetch_sub(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
        } else {
            __atomic_fetch_sub(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
            __atomic_store_n(&refcount_slots[_my_slot].active_ptr, nullptr, __ATOMIC_RELEASE);
            __atomic_store_n(&slot_owners[_my_slot], 0, __ATOMIC_RELEASE);
        }
    }
}

RefCountGuard::RefCountGuard(RefCountGuard&& other) noexcept
    : _active(other._active), _is_reentrant(other._is_reentrant),
      _outer_slot(other._outer_slot),
      _my_slot(other._my_slot), _saved_ptr(other._saved_ptr) {
    other._active = false;
}

RefCountGuard& RefCountGuard::operator=(RefCountGuard&& other) noexcept {
    if (this != &other) {
        if (_active && _my_slot >= 0) {
            if (_is_reentrant) {
                __atomic_store_n(&refcount_slots[_my_slot].active_ptr, _saved_ptr, __ATOMIC_RELEASE);
                if (_outer_slot >= 0) {
                    __atomic_store_n(&refcount_slots[_my_slot].outer_stack[_outer_slot], nullptr, __ATOMIC_RELEASE);
                }
                __atomic_fetch_sub(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
            } else {
                __atomic_fetch_sub(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
                __atomic_store_n(&refcount_slots[_my_slot].active_ptr, nullptr, __ATOMIC_RELEASE);
                __atomic_store_n(&slot_owners[_my_slot], 0, __ATOMIC_RELEASE);
            }
        }
        _active        = other._active;
        _is_reentrant  = other._is_reentrant;
        _outer_slot    = other._outer_slot;
        _my_slot       = other._my_slot;
        _saved_ptr     = other._saved_ptr;
        other._active  = false;
    }
    return *this;
}

// Returns true iff the slot currently references the resource we want to delete,
// either as active_ptr or as any non-null entry in outer_stack.
static inline bool slotReferences(const RefCountSlot& s, void* target) {
    void* table = __atomic_load_n(&s.active_ptr, __ATOMIC_ACQUIRE);
    if (table == target) return true;
    for (int j = 0; j < RefCountSlot::OUTER_STACK_DEPTH; ++j) {
        void* o = __atomic_load_n(&s.outer_stack[j], __ATOMIC_ACQUIRE);
        if (o == target) return true;
    }
    return false;
}

void RefCountGuard::waitForRefCountToClear(void* table_to_delete) {
    const int SPIN_ITERATIONS = 100;
    for (int spin = 0; spin < SPIN_ITERATIONS; ++spin) {
        bool all_clear = true;
        for (int i = 0; i < MAX_THREADS; ++i) {
            uint32_t count = __atomic_load_n(&refcount_slots[i].count, __ATOMIC_ACQUIRE);
            if (count == 0) continue;
            if (slotReferences(refcount_slots[i], table_to_delete)) { all_clear = false; break; }
        }
        if (all_clear) return;
        spinPause();
    }

    const int MAX_WAIT_ITERATIONS = 5000;
    struct timespec sleep_time = {0, 100000};
    for (int wait_count = 0; wait_count < MAX_WAIT_ITERATIONS; ++wait_count) {
        bool all_clear = true;
        for (int i = 0; i < MAX_THREADS; ++i) {
            uint32_t count = __atomic_load_n(&refcount_slots[i].count, __ATOMIC_ACQUIRE);
            if (count == 0) continue;
            if (slotReferences(refcount_slots[i], table_to_delete)) { all_clear = false; break; }
        }
        if (all_clear) return;
        nanosleep(&sleep_time, nullptr);
    }

    Counters::increment(DICTIONARY_DRAIN_TIMEOUTS, 1);
    Log::warn("waitForRefCountToClear: timeout after ~500ms waiting for %p; "
              "drain incomplete, proceeding (dictionary snapshot may miss late inserts)",
              table_to_delete);
#ifndef NDEBUG
    // Under DEBUG builds, treat the timeout as a fatal bug — keeping the abort
    // out of release avoids turning a survivable rotation glitch into a crash
    // in production.
    abort();
#endif
}

void RefCountGuard::waitForAllRefCountsToClear() {
    const int SPIN_ITERATIONS = 100;
    for (int spin = 0; spin < SPIN_ITERATIONS; ++spin) {
        bool any = false;
        for (int i = 0; i < MAX_THREADS; ++i) {
            if (__atomic_load_n(&refcount_slots[i].count, __ATOMIC_ACQUIRE) > 0) { any = true; break; }
        }
        if (!any) return;
        spinPause();
    }

    const int MAX_WAIT_ITERATIONS = 5000;
    struct timespec sleep_time = {0, 100000};
    int last_nonzero_slot = -1;  // for timeout diagnostic below
    for (int wait_count = 0; wait_count < MAX_WAIT_ITERATIONS; ++wait_count) {
        bool any = false;
        for (int i = 0; i < MAX_THREADS; ++i) {
            if (__atomic_load_n(&refcount_slots[i].count, __ATOMIC_ACQUIRE) > 0) { any = true; last_nonzero_slot = i; break; }
        }
        if (!any) return;
        nanosleep(&sleep_time, nullptr);
    }
    Log::warn("waitForAllRefCountsToClear: timeout after ~500ms; slot %d last seen non-zero, proceeding", last_nonzero_slot);
}
