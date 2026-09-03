/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef THREADLOCALDATA_INLINE_H
#define THREADLOCALDATA_INLINE_H

#include "guards.h"
#include "jvmThread.h"
#include "os.h"
#include "threadLocalData.h"
#include "threadLocalDataPool.h"

inline ProfiledThread* ProfiledThread::current() {
    if (!isThreadKeyValid()) {
      return nullptr;
    }
    return _current_thread.get();
}

inline ProfiledThread* ProfiledThread::acquireCurrent() {
    ProfiledThread* prof_thread = current();
    if (prof_thread == nullptr) {
        SignalBlocker blocker;
        // Check again, in case the call is interrupted by another signal
        prof_thread = current();
        if (prof_thread == nullptr) {
            prof_thread = ThreadLocalDataPool::acquire(OS::threadId());
            if (prof_thread != nullptr) {
                _current_thread.set(prof_thread);
            }
        }
    }
    return prof_thread;
}

inline bool ProfiledThread::claimAcquire(int tid) {
    if (isClaimed()) {
        return false;
    }

    u32 flags = __atomic_fetch_or(&_misc_flags, FLAG_CLAIMED, __ATOMIC_ACQUIRE);
    if((flags & FLAG_CLAIMED) == 0) {
      _tid = tid;
#ifdef __FAULT_INJECTION__
    _fi_rng = ((u64)(uintptr_t)this) ^ (0x9e3779b97f4a7c15ULL * (u64)tid);
    if (_fi_rng == 0) _fi_rng = 1;
#endif
      return true;
    }
    return false;
}

// Shared init-window guard used by the CPU/wall profiling signal handlers.
// Guards against the race window between Profiler::registerThread() and
// thread_native_entry setting JVM TLS (PROF-13072): a pure native thread
// (where JVMThread::current() is always null) is allowed through once its
// one-shot init window has ticked down. Returns true if the caller should
// tick-and-return, in which case the tick has already happened. All call
// sites are signal handlers holding an ErrnoPreserver, so no manual errno
// handling is needed on this return path.
static inline bool tickInitWindowIfNeeded(ProfiledThread* current) {
    if (JVMThread::current() == nullptr && current->inInitWindow()) {
        current->tickInitWindow();
        return true;
    }
    return false;
}

#endif // THREADLOCALDATA_INLINE_H
