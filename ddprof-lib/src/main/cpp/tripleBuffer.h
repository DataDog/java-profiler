/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _TRIPLE_BUFFER_H
#define _TRIPLE_BUFFER_H

/**
 * Generic triple-buffer rotation manager.
 *
 * Manages three externally-owned objects that cycle through three roles:
 *
 *   active   — receives new writes (signal handlers, fill-path)
 *   dump     — snapshot being read by the current dump (old active after rotate)
 *   recent   — last *completed* dump's snapshot; stable for the full profiling
 *              interval between dumps; used for read-only fallback lookups
 *              (e.g. walkVM vtable-stub class resolution)
 *
 * Lifecycle per dump cycle:
 *   rotate()        — advance active index; dump thread reads dumpBuffer()
 *   ...dump runs, populating dumpBuffer() with fill-path data...
 *   advanceRecent() — publish dumpBuffer() as the new recent; returns the
 *                     old recent so the caller can drain in-flight readers
 *                     (RefCountGuard::waitForRefCountToClear) then clear it
 *
 * Memory: at most two non-empty buffers at any time (recent + active).
 * Churn: stale entries purged after at most one full dump cycle.
 *
 * Thread safety:
 *   _active_index and _recent_ptr are accessed via __atomic_* with
 *   acquire/release ordering.  Callers that read from recent() must
 *   protect against concurrent advanceRecent()+clear() via RefCountGuard.
 */
template<typename T>
class TripleBufferRotator {
    T* const _buf[3];
    volatile int _active_index;   // 0/1/2; cycles on rotate()
    T* volatile _recent_ptr;      // last completed dump's buffer

public:
    // a/b/c must remain valid for the lifetime of this rotator.
    // c is used as the initial recent pointer (empty at construction).
    TripleBufferRotator(T* a, T* b, T* c)
        : _buf{a, b, c}, _active_index(0), _recent_ptr(c) {}

    T* active() const {
        return _buf[__atomic_load_n(&_active_index, __ATOMIC_ACQUIRE)];
    }

    // Buffer the dump thread reads from: (active_index + 2) % 3 after rotate().
    T* dumpBuffer() const {
        return _buf[(__atomic_load_n(&_active_index, __ATOMIC_ACQUIRE) + 2) % 3];
    }

    // Last completed dump's buffer.  Stable between advanceRecent() calls.
    T* recent() const {
        return __atomic_load_n(const_cast<T* const volatile*>(&_recent_ptr), __ATOMIC_ACQUIRE);
    }

    // Advance _active_index by 1 mod 3.
    // After this call the old active is accessible via dumpBuffer().
    void rotate() {
        int old = __atomic_load_n(&_active_index, __ATOMIC_ACQUIRE);
        __atomic_store_n(&_active_index, (old + 1) % 3, __ATOMIC_RELEASE);
    }

    // Atomically publish dumpBuffer() as the new recent.
    // Returns the previous recent; the caller must:
    //   1. RefCountGuard::waitForRefCountToClear(old_recent)
    //   2. old_recent->clear()  (or equivalent cleanup)
    T* advanceRecent() {
        T* new_recent = dumpBuffer();
        return __atomic_exchange_n(
            const_cast<T**>(const_cast<T* const volatile*>(&_recent_ptr)),
            new_recent, __ATOMIC_ACQ_REL);
    }

    // Reset to initial state (no concurrent writers/readers).
    void reset(T* initial_recent) {
        __atomic_store_n(&_active_index, 0, __ATOMIC_RELEASE);
        __atomic_store_n(
            const_cast<T**>(const_cast<T* const volatile*>(&_recent_ptr)),
            initial_recent, __ATOMIC_RELEASE);
    }
};

#endif // _TRIPLE_BUFFER_H
