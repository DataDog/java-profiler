/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef THREADLOCALDATA_POOL_H
#define THREADLOCALDATA_POOL_H

#include <stdint.h>

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


    inline bool contains(ProfiledThread* t) {
        return t >= _threads && t <= &_threads[_capacity - 1];
    }

public:
    static void initialize();
    static ProfiledThread* acquire(int tid);
    static bool release(ProfiledThread* t);
};

#endif // THREADLOCALDATA_POOL_H