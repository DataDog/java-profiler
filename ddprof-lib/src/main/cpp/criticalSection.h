/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CRITICALSECTION_H
#define _CRITICALSECTION_H

#include <signal.h>
#include <atomic>

/**
 * Race-free critical section using atomic compare-and-swap.
 * 
 * Instead of expensive syscalls to block signals, this approach uses
 * a thread-local atomic flag with CAS to prevent signal handler reentrancy.
 * 
 * Usage:
 *   {
 *     CriticalSection cs; // Atomically claim critical section
 *     // Complex data structure operations
 *     // Signal handlers will be blocked from entering
 *   } // Critical section automatically released
 * 
 * This eliminates race conditions between signal handlers and normal code
 * by ensuring only one can hold the critical section at a time per thread.
 */
class CriticalSection {
private:
    bool _entered;  // Track if this instance successfully entered
    
public:
    CriticalSection();
    ~CriticalSection();
    
    // Non-copyable, non-movable
    CriticalSection(const CriticalSection&) = delete;
    CriticalSection& operator=(const CriticalSection&) = delete;
    CriticalSection(CriticalSection&&) = delete;
    CriticalSection& operator=(CriticalSection&&) = delete;
    
    // Check if this instance successfully entered the critical section
    bool entered() const { return _entered; }
    
    // Static method for signal handlers to check critical section status
    // Returns true if ANY critical section is active on this thread
    static bool isInCriticalSection();
    
private:
    // Safe accessor for thread-local atomic flag
    static std::atomic<sig_atomic_t>& getThreadLocalFlag();
};

#endif // _CRITICALSECTION_H
