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
        prof_thread = ThreadLocalDataPool::acquire(OS::threadId());
        if (prof_thread != nullptr) {
            _current_thread.set(prof_thread);
        }
    }
    return prof_thread;
}

#endif // THREADLOCALDATA_INLINE_H
