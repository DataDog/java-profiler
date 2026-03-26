/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _THREADSTATE_INLINE_H
#define _THREADSTATE_INLINE_H

#include "threadState.h"
#include "hotspot/vmStructs.h"

inline ExecutionMode getThreadExecutionMode() {
    return VM::isHotspot() ? VMThread::getExecutionMode() :
                             ExecutionMode::UNKNOWN;
}

inline OSThreadState getOSThreadState() {
    return VM::isHotspot() ? VMThread::getOSThreadState() :
                             OSThreadState::UNKNOWN;
}

#endif // _THREADSTATE_INLINE_H
