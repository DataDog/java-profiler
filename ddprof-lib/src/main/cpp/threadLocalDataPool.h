/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef THREADLOCALDATA_POOL_H
#define THREADLOCALDATA_POOL_H

#include <stdint.h>
#include <stdlib.h>
#include <new>

class ProfiledThread;

// Pool of pre-constructed ProfiledThreads, claimed from signal handlers and
// the malloc hook (ProfiledThread::acquireCurrent()) for threads that have no
// ProfiledThread yet: threads that started before the first profiler start
// installed the pthread_create hook. claim() runs in signal handlers, so it is
// lock-free and never allocates.
//
// The pool is segmented and grow-only. Live threads' TLS (and
// otel_thread_ctx_v1) point into claimed slots, so a slot can never move or be
// freed, which rules out realloc. Instead ensureCapacity() -- non-signal
// context only -- appends a segment, sized from the number of live threads at
// Profiler::start(). Segments are never freed; slots go back to the free state
// when their thread exits, so the high-water capacity is reused.
class ThreadLocalDataPool {
    static constexpr uint32_t MIN_SEGMENT_CAPACITY = 64;
    static constexpr int MAX_SEGMENTS = 16;

    struct Segment {
        ProfiledThread* threads;
        uint32_t        capacity;
        uint32_t        used;     // reservations, updated atomically
    };

private:
    static ThreadLocalDataPool* _pool;

    Segment*  _segments[MAX_SEGMENTS];
    int       _num_segments;     // published with release, read with acquire
    uint64_t  _total_capacity;   // written under the grow lock only

    ThreadLocalDataPool(const ThreadLocalDataPool&) = delete;
    ThreadLocalDataPool& operator=(const ThreadLocalDataPool&) = delete;
    ~ThreadLocalDataPool() = delete;

    ThreadLocalDataPool();
    // Appends one segment so total capacity reaches at least `wanted`: at
    // least doubling, and never smaller than `min_segment`. Callers serialize;
    // returns false if the segment can't be added.
    bool grow(uint64_t wanted, uint32_t min_segment = MIN_SEGMENT_CAPACITY);
    ProfiledThread* claim(int tid);
    bool unclaim(ProfiledThread* t);
    Segment* segmentOf(ProfiledThread* t) const;

    inline bool contains(ProfiledThread* t) const {
        return segmentOf(t) != nullptr;
    }

public:
    // Ensures capacity for `wanted` unprimed threads, creating the pool on the
    // first call. Non-signal context only. Returns false if the pool could not
    // be created or grown (existing segments stay usable).
    static bool ensureCapacity(uint64_t wanted);
    // Same as ensureCapacity(MIN_SEGMENT_CAPACITY).
    static void initialize();
    static bool isInitialized();
    static ProfiledThread* acquire(int tid);
    static bool release(ProfiledThread* t);
    static uint64_t capacity();

#ifdef UNIT_TEST
    // Test-only: a pool isolated from the process-wide singleton (_pool), so
    // contains()/boundary tests don't disturb other tests' use of
    // initialize()/acquire()/release().
    static ThreadLocalDataPool* createForTest(uint32_t capacity) {
        ThreadLocalDataPool* p = new ThreadLocalDataPool();
        p->grow(capacity, capacity);
        return p;
    }
    // ThreadLocalDataPool has no destructor definition (it's a process-lifetime
    // singleton in production, never freed), so `delete p` won't link. Mirror
    // what a destructor would do -- destroy each placement-newed ProfiledThread
    // and free() each segment -- then release the ThreadLocalDataPool object
    // itself via the deallocation function directly, without invoking a
    // (nonexistent) destructor.
    static void destroyForTest(ThreadLocalDataPool* p);

    bool containsForTest(ProfiledThread* t) const { return contains(t); }
    // The first segment's slots.
    ProfiledThread* threadsForTest() const {
        return _num_segments > 0 ? _segments[0]->threads : nullptr;
    }
    // Total capacity across all segments.
    uint64_t capacityForTest() const { return _total_capacity; }
    int segmentCountForTest() const { return _num_segments; }
    ProfiledThread* segmentThreadsForTest(int i) const { return _segments[i]->threads; }
    uint32_t segmentCapacityForTest(int i) const { return _segments[i]->capacity; }
    bool growForTest(uint64_t wanted) { return grow(wanted, 1); }
    ProfiledThread* claimForTest(int tid) { return claim(tid); }
    bool unclaimForTest(ProfiledThread* t) { return unclaim(t); }
#endif
};

#endif // THREADLOCALDATA_POOL_H
