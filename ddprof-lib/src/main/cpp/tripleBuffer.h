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
 *   scratch  — two rotations behind active; ready to be cleared.  At least one
 *              full dump cycle has elapsed since this buffer was last in the
 *              "dump" role, which gives any writer that loaded a stale active
 *              pointer time to complete its lookup before the buffer is freed.
 *
 * Lifecycle per dump cycle:
 *   rotate()        — advance active index; dump thread reads dumpBuffer()
 *   ...dump runs, populating dumpBuffer() with fill-path data...
 *   ...caller clears clearTarget() (the scratch buffer)...
 *
 * Memory: at most two non-empty buffers at any time (active + dump).
 *
 * Thread safety:
 *   _active_index is accessed via __atomic_* with acquire/release ordering.
 *   Writers may briefly operate on a buffer that has just transitioned to
 *   "dump" or "scratch" (TOCTOU at rotate); this is safe because Dictionary
 *   (and similar) operations are lock-free internally and the scratch buffer
 *   is not cleared until one full dump cycle later.
 */
template<typename T>
class TripleBufferRotator {
    T* const _buf[3];
    volatile int _active_index;   // 0/1/2; cycles on rotate()

public:
    // a/b/c must remain valid for the lifetime of this rotator.
    TripleBufferRotator(T* a, T* b, T* c)
        : _buf{a, b, c}, _active_index(0) {}

    T* active() const {
        return _buf[__atomic_load_n(&_active_index, __ATOMIC_ACQUIRE)];
    }

    // Buffer the dump thread reads from: (active_index + 2) % 3 after rotate().
    T* dumpBuffer() const {
        return _buf[(__atomic_load_n(&_active_index, __ATOMIC_ACQUIRE) + 2) % 3];
    }

    // Buffer scheduled for the next clear: (active_index + 1) % 3.
    // At least one full dump cycle has elapsed since this buffer was the
    // "dump" role, so any stale writer pointer to it is no longer in use.
    T* clearTarget() const {
        return _buf[(__atomic_load_n(&_active_index, __ATOMIC_ACQUIRE) + 1) % 3];
    }

    // Advance _active_index by 1 mod 3.
    // After this call the old active is accessible via dumpBuffer().
    void rotate() {
        int old = __atomic_load_n(&_active_index, __ATOMIC_ACQUIRE);
        __atomic_store_n(&_active_index, (old + 1) % 3, __ATOMIC_RELEASE);
    }

    // Reset to initial state (no concurrent writers/readers).
    void reset() {
        __atomic_store_n(&_active_index, 0, __ATOMIC_RELEASE);
    }
};

#endif // _TRIPLE_BUFFER_H
