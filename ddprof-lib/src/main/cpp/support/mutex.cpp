/*
 * Copyright The async-profiler authors
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mutex.h"
#include "hotspot/vmStructs.h"

// Use the support-side signal-context probe to restore the AS-safety assertion
// without pulling in ProfiledThread (which lives in libjavaProfiler).
// The probe is null before VM::initProfilerBridge runs; treat null as "not in signal"
// so uninstrumented code paths are never falsely flagged.
#if !defined(NDEBUG)
#include <unistd.h>
#include <stdlib.h>
#define DEBUG_ASSERT_NOT_IN_SIGNAL()                                                \
    do {                                                                             \
        IsInSignalProbe _probe = g_is_in_signal_probe.load(std::memory_order_acquire); \
        if (_probe != nullptr && _probe()) {                                         \
            static const char _msg[] =                                               \
                "[java-profiler] mutex::lock() called from signal handler context\n";\
            (void)write(STDERR_FILENO, _msg, sizeof(_msg) - 1);                     \
            abort();                                                                 \
        }                                                                            \
    } while (0)
#else
#define DEBUG_ASSERT_NOT_IN_SIGNAL() ((void)0)
#endif

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
