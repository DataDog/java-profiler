/*
 * Copyright The async-profiler authors
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mutex.h"

// signalSafety.h is intentionally omitted here: the DEBUG_ASSERT_NOT_IN_SIGNAL
// guard references ProfiledThread which lives in libjavaProfiler.  The mutex
// itself is correct without the guard; the assertion is retained in callers
// that operate in a profiler context and include signalSafety.h directly.
#define DEBUG_ASSERT_NOT_IN_SIGNAL() ((void)0)

Mutex::Mutex() {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&_mutex, &attr);
}

void Mutex::lock() {
    DEBUG_ASSERT_NOT_IN_SIGNAL();
    pthread_mutex_lock(&_mutex);
}

void Mutex::unlock() {
    pthread_mutex_unlock(&_mutex);
}

WaitableMutex::WaitableMutex() : Mutex() {
    pthread_cond_init(&_cond, NULL);
}

bool WaitableMutex::waitUntil(u64 wall_time) {
    struct timespec ts = {(time_t)(wall_time / 1000000), (long)(wall_time % 1000000) * 1000};
    return pthread_cond_timedwait(&_cond, &_mutex, &ts) != 0;
}

void WaitableMutex::notify() {
    pthread_cond_signal(&_cond);
}
