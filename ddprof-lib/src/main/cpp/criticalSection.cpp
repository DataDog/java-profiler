/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "criticalSection.h"

CriticalSection::CriticalSection() : _entered(false) {
    // Use safe accessor to ensure TLS is fully initialized
    std::atomic<sig_atomic_t>& flag = getThreadLocalFlag();
    
    // Try to atomically claim the critical section using compare-and-swap
    sig_atomic_t expected = 0;
    _entered = flag.compare_exchange_strong(
        expected, 1, std::memory_order_acq_rel, std::memory_order_acquire);
    
    // If CAS failed, another critical section (likely signal handler) is already active
    // We don't throw or error - we just track that we didn't get ownership
    // The caller can check entered() if needed, but typically signal handlers
    // will use isInCriticalSection() and return early
}

CriticalSection::~CriticalSection() {
    // Only release if we successfully entered
    if (_entered) {
        getThreadLocalFlag().store(0, std::memory_order_release);
    }
}

bool CriticalSection::isInCriticalSection() {
    // Use safe accessor to ensure TLS is fully initialized
    return getThreadLocalFlag().load(std::memory_order_acquire) != 0;
}

std::atomic<sig_atomic_t>& CriticalSection::getThreadLocalFlag() {
    // Force TLS initialization with explicit initialization
    // This ensures the atomic is fully constructed before any signal handler can access it
    static thread_local std::atomic<sig_atomic_t> flag{0};
    return flag;
}
