/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "counters.h"
#include "log.h"
#include "threadLocalData.inline.h"
#include "threadLocalDataPool.h"

#include <algorithm>
#include <cassert>
#include <pthread.h>
#include <stdlib.h>

ThreadLocalDataPool* ThreadLocalDataPool::_pool = nullptr;

// Serializes pool creation and growth. Never taken on the claim/release path.
static pthread_mutex_t _grow_lock = PTHREAD_MUTEX_INITIALIZER;

ThreadLocalDataPool::ThreadLocalDataPool()
    : _segments{}, _num_segments(0), _total_capacity(0) {
    NativeMem::record(NM_THREAD_LOCAL, sizeof(ThreadLocalDataPool));
}

bool ThreadLocalDataPool::ensureCapacity(uint64_t wanted) {
    pthread_mutex_lock(&_grow_lock);
    ThreadLocalDataPool* pool = __atomic_load_n(&_pool, __ATOMIC_ACQUIRE);
    if (pool == nullptr) {
        // process-lifetime singleton
        pool = new ThreadLocalDataPool();
        __atomic_store_n(&_pool, pool, __ATOMIC_RELEASE);
    }
    bool ok = pool->_total_capacity >= wanted || pool->grow(wanted);
    pthread_mutex_unlock(&_grow_lock);
    return ok;
}

void ThreadLocalDataPool::initialize() {
    ensureCapacity(MIN_SEGMENT_CAPACITY);
}

bool ThreadLocalDataPool::isInitialized() {
    return __atomic_load_n(&_pool, __ATOMIC_ACQUIRE) != nullptr;
}

uint64_t ThreadLocalDataPool::capacity() {
    pthread_mutex_lock(&_grow_lock);
    ThreadLocalDataPool* pool = __atomic_load_n(&_pool, __ATOMIC_ACQUIRE);
    uint64_t result = pool != nullptr ? pool->_total_capacity : 0;
    pthread_mutex_unlock(&_grow_lock);
    return result;
}

bool ThreadLocalDataPool::grow(uint64_t wanted, uint32_t min_segment) {
    if (_total_capacity >= wanted) {
        return true;
    }
    int n = _num_segments;
    if (n >= MAX_SEGMENTS) {
        Log::warn("TLS pool: segment limit reached at %llu slots", (unsigned long long)_total_capacity);
        return false;
    }
    // At least double, so a pool that keeps growing needs few segments.
    uint64_t size = std::max<uint64_t>({wanted - _total_capacity, _total_capacity,
                                        (uint64_t)min_segment});
    size = std::min<uint64_t>(size, UINT32_MAX);

    size_t bytes = size * sizeof(ProfiledThread);
    Segment* segment = (Segment*)malloc(sizeof(Segment));
    void* threads = malloc(bytes);
    if (segment == nullptr || threads == nullptr) {
        free(segment);
        free(threads);
        Log::warn("TLS pool: failed to allocate %llu slots", (unsigned long long)size);
        return false;
    }
    segment->threads = reinterpret_cast<ProfiledThread*>(threads);
    for (uint64_t index = 0; index < size; index++) {
        new (&segment->threads[index]) ProfiledThread(0);
    }
    segment->capacity = (uint32_t)size;
    segment->used = 0;
    NativeMem::record(NM_THREAD_LOCAL, bytes + sizeof(Segment));

    _segments[n] = segment;
    _total_capacity += size;
    // Publish after the segment is fully built: claim() reads it with acquire.
    __atomic_store_n(&_num_segments, n + 1, __ATOMIC_RELEASE);
    return true;
}

ProfiledThread* ThreadLocalDataPool::claim(int tid) {
    int n = __atomic_load_n(&_num_segments, __ATOMIC_ACQUIRE);
    for (int i = 0; i < n; i++) {
        Segment* segment = _segments[i];
        uint32_t capacity = segment->capacity;
        uint32_t used = __atomic_fetch_add(&segment->used, 1, __ATOMIC_RELAXED);
        if (used >= capacity) {
            __atomic_fetch_sub(&segment->used, 1, __ATOMIC_RELAXED);
            continue;
        }
        uint32_t start_pos = (uint32_t)tid % capacity;
        uint32_t index = start_pos;
        do {
            if (segment->threads[index].claimAcquire(tid)) {
                return &segment->threads[index];
            }
            index = (index + 1) % capacity;
        } while (index != start_pos);
        __atomic_fetch_sub(&segment->used, 1, __ATOMIC_RELAXED);
    }
    Counters::increment(SAMPLES_DROPPED_TLS_POOL_EXHAUSTED);
    return nullptr;
}

ThreadLocalDataPool::Segment* ThreadLocalDataPool::segmentOf(ProfiledThread* t) const {
    if (t == nullptr) {
        return nullptr;
    }
    const uintptr_t addr = reinterpret_cast<uintptr_t>(t);
    int n = __atomic_load_n(&_num_segments, __ATOMIC_ACQUIRE);
    for (int i = 0; i < n; i++) {
        Segment* segment = _segments[i];
        const uintptr_t base = reinterpret_cast<uintptr_t>(segment->threads);
        const uintptr_t end  = reinterpret_cast<uintptr_t>(segment->threads + segment->capacity);
        if (addr >= base && addr < end) {
            return segment;
        }
    }
    return nullptr;
}

bool ThreadLocalDataPool::unclaim(ProfiledThread* t) {
    Segment* segment = segmentOf(t);
    if (segment == nullptr) {
        return false;
    }
    t->unclaimAndReset();
    uint32_t used = __atomic_fetch_sub(&segment->used, 1, __ATOMIC_RELAXED);
    assert(used > 0);
    (void)used;
    return true;
}

ProfiledThread* ThreadLocalDataPool::acquire(int tid) {
    ThreadLocalDataPool* pool = __atomic_load_n(&_pool, __ATOMIC_ACQUIRE);
    if (pool == nullptr) {
        return nullptr;
    } else {
        return pool->claim(tid);
    }
}

bool ThreadLocalDataPool::release(ProfiledThread* t) {
    ThreadLocalDataPool* pool = __atomic_load_n(&_pool, __ATOMIC_ACQUIRE);
    if (pool != nullptr) {
        return pool->unclaim(t);
    } else {
        return false;
    }
}

#ifdef UNIT_TEST
void ThreadLocalDataPool::destroyForTest(ThreadLocalDataPool* p) {
    for (int i = 0; i < p->_num_segments; i++) {
        Segment* segment = p->_segments[i];
        for (uint64_t index = 0; index < segment->capacity; index++) {
            segment->threads[index].~ProfiledThread();
        }
        free(reinterpret_cast<void*>(segment->threads));
        free(segment);
    }
    ::operator delete(p);
}
#endif
