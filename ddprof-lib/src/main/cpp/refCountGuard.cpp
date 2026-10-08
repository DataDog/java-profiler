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
#include "threadLocalData.inline.h"
#include <atomic>
#include <time.h>

// Static member definitions
RefCountSlot RefCountGuard::refcount_slots[RefCountGuard::MAX_THREADS];
int RefCountGuard::slot_owners[RefCountGuard::MAX_THREADS];

// One-time warning latch: emit at most one Log::warn per process when
// reentrant nesting exceeds NESTED_DEPTH and the scanner can no longer see
// every nested resource on the slot.
static std::atomic<bool> s_nested_overflow_warned{false};

int RefCountGuard::getThreadRefCountSlot() {
    ProfiledThread* thrd = ProfiledThread::current();
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
            // just clearing slot_owners; a "reentrant" guard on that dying
            // slot would record its resource in nested[] of a slot the
            // scanner treats as holding at most an activation-window
            // active_ptr, so the resource would be missed.
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

RefCountGuard::RefCountGuard(void* resource) : _active(true), _is_reentrant(false), _nested_index(-1), _my_slot(-1) {
    int raw = getThreadRefCountSlot();

    if (raw == -1) {
        _active = false;
        return;
    }

    _is_reentrant = (raw >= MAX_THREADS);
    _my_slot = _is_reentrant ? (raw - MAX_THREADS) : raw;

    if (_is_reentrant) {
        // Reentrant: active_ptr keeps the root guard's resource; this guard's
        // resource goes into nested[].  fetch_add returns the PRE-increment
        // count, which is the reentrancy depth this guard is about to occupy
        // (depth 1 = first nested signal, depth 2 = second...).
        uint32_t prev_count = __atomic_fetch_add(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
        int idx = static_cast<int>(prev_count) - 1;
        if (idx >= 0 && idx < NESTED_DEPTH) {
            _nested_index = idx;
            __atomic_store_n(&refcount_slots[_my_slot].nested[idx], resource, __ATOMIC_RELEASE);
        } else {
            // Reentrant nesting deeper than NESTED_DEPTH; this guard's resource
            // is invisible to the scanner.  Latch a single warning per process.
            bool expected = false;
            if (s_nested_overflow_warned.compare_exchange_strong(expected, true, std::memory_order_relaxed)) {
                Log::warn("RefCountGuard reentrancy depth %u exceeds NESTED_DEPTH=%d; scanner may miss nested resources",
                          static_cast<unsigned>(prev_count) + 1, NESTED_DEPTH);
            }
        }
    } else {
        // Non-reentrant (count was 0): store pointer first so the scanner skips
        // this slot during the activation window (count=0 → treated as inactive).
        __atomic_store_n(&refcount_slots[_my_slot].active_ptr, resource, __ATOMIC_RELEASE);
        __atomic_fetch_add(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
    }
}

void RefCountGuard::release() {
    if (!_active || _my_slot < 0) return;
    if (_is_reentrant) {
        // Clear this guard's nested[] entry, then decrement count.  active_ptr
        // still holds the root guard's resource and is left alone.
        if (_nested_index >= 0) {
            __atomic_store_n(&refcount_slots[_my_slot].nested[_nested_index], nullptr, __ATOMIC_RELEASE);
        }
        __atomic_fetch_sub(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
    } else {
        __atomic_fetch_sub(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
        __atomic_store_n(&refcount_slots[_my_slot].active_ptr, nullptr, __ATOMIC_RELEASE);
        __atomic_store_n(&slot_owners[_my_slot], 0, __ATOMIC_RELEASE);
    }
}

RefCountGuard::~RefCountGuard() {
    release();
}

RefCountGuard::RefCountGuard(RefCountGuard&& other) noexcept
    : _active(other._active), _is_reentrant(other._is_reentrant),
      _nested_index(other._nested_index), _my_slot(other._my_slot) {
    other._active = false;
}

RefCountGuard& RefCountGuard::operator=(RefCountGuard&& other) noexcept {
    if (this != &other) {
        release();
        _active        = other._active;
        _is_reentrant  = other._is_reentrant;
        _nested_index  = other._nested_index;
        _my_slot       = other._my_slot;
        other._active  = false;
    }
    return *this;
}

// Returns true iff the slot currently references the resource we want to delete,
// either as active_ptr (root guard) or as a nested[] entry (reentrant guard).
// Each resource stays in one of those places for as long as it is protected
// (see RefCountSlot), so one pass over them cannot miss it.
static inline bool slotReferences(const RefCountSlot& s, void* target) {
    void* table = __atomic_load_n(&s.active_ptr, __ATOMIC_ACQUIRE);
    if (table == target) return true;
    for (int j = 0; j < RefCountSlot::NESTED_DEPTH; ++j) {
        void* o = __atomic_load_n(&s.nested[j], __ATOMIC_ACQUIRE);
        if (o == target) return true;
    }
    return false;
}

static inline bool slotReferencesAny(const RefCountSlot& s, void* const* targets, int count) {
    for (int t = 0; t < count; ++t) {
        if (slotReferences(s, targets[t])) return true;
    }
    return false;
}

// One pass over all slots: true iff some slot references any of the targets.
static bool anySlotReferences(void* const* targets, int count) {
    for (int i = 0; i < RefCountGuard::MAX_THREADS; ++i) {
        const RefCountSlot& s = RefCountGuard::refcount_slots[i];
        if (__atomic_load_n(&s.count, __ATOMIC_ACQUIRE) == 0) {
            // Check active_ptr to cover the non-reentrant constructor's activation window:
            // active_ptr is stored (RELEASE) before count++ (RELEASE), so count==0 with
            // active_ptr set means the thread is in the window and must be waited for.
            void* aptr = __atomic_load_n(&s.active_ptr, __ATOMIC_ACQUIRE);
            for (int t = 0; t < count; ++t) {
                if (aptr == targets[t]) return true;
            }
            continue;
        }
        if (slotReferencesAny(s, targets, count)) return true;
    }
    return false;
}

bool RefCountGuard::isReferenced(void* const* targets, int count) {
    return anySlotReferences(targets, count);
}

bool RefCountGuard::tryWaitForRefCountsToClear(void* const* targets, int count) {
    const int SPIN_ITERATIONS = 100;
    for (int spin = 0; spin < SPIN_ITERATIONS; ++spin) {
        if (!anySlotReferences(targets, count)) return true;
        spinPause();
    }

    const int MAX_WAIT_ITERATIONS = 5000;
    struct timespec sleep_time = {0, 100000};
    for (int wait_count = 0; wait_count < MAX_WAIT_ITERATIONS; ++wait_count) {
        if (!anySlotReferences(targets, count)) return true;
        nanosleep(&sleep_time, nullptr);
    }
    return false;
}

void RefCountGuard::waitForRefCountToClear(void* table_to_delete) {
    if (tryWaitForRefCountsToClear(&table_to_delete, 1)) return;

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
