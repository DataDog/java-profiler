/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef THREADLOCALDATA_INLINE_H
#define THREADLOCALDATA_INLINE_H

#include "guards.h"
#include "os.h"
#include "threadLocalData.h"
#include "threadLocalDataPool.h"

inline ProfiledThread* ProfiledThread::current() {
    if (!isThreadKeyValid()) {
      return nullptr;
    }
    return _current_thread.get();
}

ProfiledThread* ProfiledThread::acquireCurrent() {
    ProfiledThread* prof_thread = current();
    if (prof_thread == nullptr) {
        SignalBlocker blocker;
        // Check again, in case the call is interrupted by another signal
        prof_thread = current();
        if (prof_thread == nullptr) {
            prof_thread = ThreadLocalDataPool::acquire(OS::threadId());
            if (prof_thread != nullptr) {
                // Claim the critical section before publishing the pointer. A signal
                // that interrupts us on this thread right after publish (cross-type
                // nesting isn't blocked — see os_linux.cpp's empty sa_mask) would
                // otherwise see a non-null ProfiledThread whose _in_critical_section
                // is still false and race into the primary path. CriticalSection's
                // fallback-path destructor releases this once the outer handler exits.
                prof_thread->tryEnterCriticalSection();
                _current_thread.set(prof_thread);
            }
        }
    }
    return prof_thread;
}

#endif // THREADLOCALDATA_INLINE_H
