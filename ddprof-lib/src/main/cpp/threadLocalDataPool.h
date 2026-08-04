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

class ThreadLocalDataPool {
    static constexpr uint16_t DEFAULT_CAPACITY = 64;
private:
    static ThreadLocalDataPool* _pool;

    const uint64_t      _capacity;
    volatile uint16_t   _used;
    ProfiledThread*     _threads;

    ThreadLocalDataPool(const ThreadLocalDataPool&) = delete;
    ThreadLocalDataPool& operator=(const ThreadLocalDataPool&) = delete;

    ThreadLocalDataPool(uint64_t capacity = DEFAULT_CAPACITY);
    ~ThreadLocalDataPool();

    ProfiledThread* claim(int tid);
    bool unclaim(ProfiledThread* t);


    inline bool contains(ProfiledThread* t) const {
        if (_threads == nullptr || t == nullptr) return false;
        const uintptr_t addr = reinterpret_cast<uintptr_t>(t);
        const uintptr_t base = reinterpret_cast<uintptr_t>(_threads);
        const uintptr_t end  = reinterpret_cast<uintptr_t>(_threads + _capacity);
        return addr >= base && addr < end;
    }

public:
    static void initialize();
    static ProfiledThread* acquire(int tid);
    static bool release(ProfiledThread* t);

#ifdef UNIT_TEST
    // Test-only: a pool isolated from the process-wide singleton (_pool), so
    // contains()/boundary tests don't disturb other tests' use of
    // initialize()/acquire()/release().
    static ThreadLocalDataPool* createForTest(uint64_t capacity) {
        return new ThreadLocalDataPool(capacity);
    }
    // ThreadLocalDataPool has no destructor definition (it's a process-lifetime
    // singleton in production, never freed), so `delete p` won't link. Mirror
    // what a destructor would do -- destroy each placement-newed ProfiledThread
    // and free() the malloc'd buffer -- then release the ThreadLocalDataPool
    // object itself via the deallocation function directly, without invoking a
    // (nonexistent) destructor.
    static void destroyForTest(ThreadLocalDataPool* p) {
        if (p->_threads != nullptr) {
            for (uint64_t index = 0; index < p->_capacity; index++) {
                p->_threads[index].~ProfiledThread();
            }
            free(reinterpret_cast<void*>(p->_threads));
        }
        ::operator delete(p);
    }

    bool containsForTest(ProfiledThread* t) const { return contains(t); }
    ProfiledThread* threadsForTest() const { return _threads; }
    uint64_t capacityForTest() const { return _capacity; }
    ProfiledThread* claimForTest(int tid) { return claim(tid); }
    bool unclaimForTest(ProfiledThread* t) { return unclaim(t); }
#endif
};

#endif // THREADLOCALDATA_POOL_H
