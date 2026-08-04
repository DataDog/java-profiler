
 /*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "threadLocalData.h"
#include "threadLocalDataPool.h"

#include <cassert>
#include <stdlib.h>

ThreadLocalDataPool* ThreadLocalDataPool::_pool = nullptr;

ThreadLocalDataPool::ThreadLocalDataPool(uint64_t capacity)
    : _capacity(capacity), _used(0), _threads(nullptr) {
    const size_t malloc_size = capacity * sizeof(ProfiledThread);
    void* p = malloc(malloc_size);
    if (p == nullptr) {
        return;
    }

    _threads = reinterpret_cast<ProfiledThread*>(p);
    for (uint64_t index = 0; index < capacity; index++) {
        new (&_threads[index]) ProfiledThread(0);
    }
    NativeMem::record(NM_THREAD_LOCAL, malloc_size + sizeof(ThreadLocalDataPool));
}

ThreadLocalDataPool::~ThreadLocalDataPool() {
    if (_threads != nullptr) {
        free(reinterpret_cast<void*>(_threads));
    }
}

ProfiledThread* ThreadLocalDataPool::claim(int tid) {
    if (_threads == nullptr) {
        return nullptr;
    }

    uint16_t used = __atomic_fetch_add(&_used, 1, __ATOMIC_RELAXED);
    if (used >= _capacity) {
        __atomic_fetch_add(&_used, -1, __ATOMIC_RELAXED);
        return nullptr;
    }

    int start_pos = tid % _capacity;
    int index = start_pos;
    do {
        if (_threads[index].claim_acquire()) {
            return &_threads[index];
        }
        index = (index + 1) % _capacity;
    } while (index != start_pos);
    __atomic_fetch_add(&_used, -1, __ATOMIC_RELAXED);
    return nullptr;
}

bool ThreadLocalDataPool::unclaim(ProfiledThread* t) {
    if (contains(t)) {
        t->unclaim();
        uint16_t used = __atomic_fetch_add(&_used, -1, __ATOMIC_RELEASE);
        assert(used > 0);
        return true;
    }
    return false;
}

void ThreadLocalDataPool::initialize() {
    ThreadLocalDataPool* pool = new ThreadLocalDataPool();
    __atomic_store_n(&_pool, pool, __ATOMIC_RELEASE);
}

ProfiledThread* ThreadLocalDataPool::acquire(int tid) {
    ThreadLocalDataPool* pool = __atomic_load_n(&_pool, __ATOMIC_ACQUIRE);
    if (pool == nullptr) {
        return nullptr;
    } else {
        ProfiledThread* t = pool->claim(tid);
        if (t != nullptr) {
            t->resetClaimed(tid);
        }
        return t;
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