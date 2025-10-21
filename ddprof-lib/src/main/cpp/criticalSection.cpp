/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "criticalSection.h"

CriticalSection::CriticalSection() : _entered(false) {
    // Use safe accessor to ensure TLS is fully initialized
    sig_atomic_t& flag = getThreadLocalFlag();
    
    sig_atomic_t expected = 0;
    if (!flag) {
        flag = 1;
        _entered = 1;
    }
    
    // If the attempt failed, another critical section (likely signal handler) is already active
    // We don't throw or error - we just track that we didn't get ownership
    // The caller can check entered() if needed, but typically signal handlers
    // will use isInCriticalSection() and return early
}

CriticalSection::~CriticalSection() {
    // Only release if we successfully entered
    if (_entered) {
        getThreadLocalFlag() = 0;
    }
}

sig_atomic_t& CriticalSection::getThreadLocalFlag() {
    // Force TLS initialization with explicit initialization
    // This ensures the atomic is fully constructed before any signal handler can access it
    static thread_local sig_atomic_t flag{0};
    return flag;
}
