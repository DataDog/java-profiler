/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "refCountGuard.h"
#include "arch.h"
#include "log.h"
#include "os.h"
#include "primeProbing.h"
#include "thread.h"
#include <time.h>

// Static member definitions
RefCountSlot RefCountGuard::refcount_slots[RefCountGuard::MAX_THREADS];
int RefCountGuard::slot_owners[RefCountGuard::MAX_THREADS];

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
            return slot + MAX_THREADS;
        }

        if (probe.hasNext()) {
            slot = probe.next();
        }
    }

    return -1;
}

RefCountGuard::RefCountGuard(void* resource) : _active(true), _is_reentrant(false), _my_slot(-1), _saved_ptr(nullptr) {
    int raw = getThreadRefCountSlot();

    if (raw == -1) {
        _active = false;
        return;
    }

    _is_reentrant = (raw >= MAX_THREADS);
    _my_slot = _is_reentrant ? (raw - MAX_THREADS) : raw;

    if (_is_reentrant) {
        _saved_ptr = __atomic_load_n(&refcount_slots[_my_slot].active_ptr, __ATOMIC_ACQUIRE);
        // Reentrant: increment count first, then publish outer_ptr so the scanner
        // sees the outer resource while active_ptr is updated to the inner one.
        __atomic_fetch_add(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
        __atomic_store_n(&refcount_slots[_my_slot].outer_ptr, _saved_ptr, __ATOMIC_RELEASE);
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
            // Restore outer active_ptr first, then clear outer_ptr, then decrement
            // count; scanner always observes the outer resource while count > 0.
            __atomic_store_n(&refcount_slots[_my_slot].active_ptr, _saved_ptr, __ATOMIC_RELEASE);
            __atomic_store_n(&refcount_slots[_my_slot].outer_ptr, nullptr, __ATOMIC_RELEASE);
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
      _my_slot(other._my_slot), _saved_ptr(other._saved_ptr) {
    other._active = false;
}

RefCountGuard& RefCountGuard::operator=(RefCountGuard&& other) noexcept {
    if (this != &other) {
        if (_active && _my_slot >= 0) {
            if (_is_reentrant) {
                __atomic_store_n(&refcount_slots[_my_slot].active_ptr, _saved_ptr, __ATOMIC_RELEASE);
                __atomic_store_n(&refcount_slots[_my_slot].outer_ptr, nullptr, __ATOMIC_RELEASE);
                __atomic_fetch_sub(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
            } else {
                __atomic_fetch_sub(&refcount_slots[_my_slot].count, 1, __ATOMIC_RELEASE);
                __atomic_store_n(&refcount_slots[_my_slot].active_ptr, nullptr, __ATOMIC_RELEASE);
                __atomic_store_n(&slot_owners[_my_slot], 0, __ATOMIC_RELEASE);
            }
        }
        _active       = other._active;
        _is_reentrant = other._is_reentrant;
        _my_slot      = other._my_slot;
        _saved_ptr    = other._saved_ptr;
        other._active = false;
    }
    return *this;
}

void RefCountGuard::waitForRefCountToClear(void* table_to_delete) {
    const int SPIN_ITERATIONS = 100;
    for (int spin = 0; spin < SPIN_ITERATIONS; ++spin) {
        bool all_clear = true;
        for (int i = 0; i < MAX_THREADS; ++i) {
            uint32_t count = __atomic_load_n(&refcount_slots[i].count, __ATOMIC_ACQUIRE);
            if (count == 0) continue;
            void* table = __atomic_load_n(&refcount_slots[i].active_ptr, __ATOMIC_ACQUIRE);
            void* outer = __atomic_load_n(&refcount_slots[i].outer_ptr, __ATOMIC_ACQUIRE);
            if (table == table_to_delete || outer == table_to_delete) { all_clear = false; break; }
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
            void* table = __atomic_load_n(&refcount_slots[i].active_ptr, __ATOMIC_ACQUIRE);
            void* outer = __atomic_load_n(&refcount_slots[i].outer_ptr, __ATOMIC_ACQUIRE);
            if (table == table_to_delete || outer == table_to_delete) { all_clear = false; break; }
        }
        if (all_clear) return;
        nanosleep(&sleep_time, nullptr);
    }

    Log::warn("waitForRefCountToClear: timeout waiting for %p, proceeding", table_to_delete);
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
    for (int wait_count = 0; wait_count < MAX_WAIT_ITERATIONS; ++wait_count) {
        bool any = false;
        for (int i = 0; i < MAX_THREADS; ++i) {
            if (__atomic_load_n(&refcount_slots[i].count, __ATOMIC_ACQUIRE) > 0) { any = true; break; }
        }
        if (!any) return;
        nanosleep(&sleep_time, nullptr);
    }
}
