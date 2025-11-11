/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CRITICALSECTION_H
#define _CRITICALSECTION_H

#include <cstdint>
#include <cstddef>

/**
 * Race-free critical section using atomic compare-and-swap.
 * 
 * Hybrid implementation:
 * - Primary: Uses ProfiledThread storage when available (zero memory overhead)
 * - Fallback: Hash-based bitmap for stress tests and cases without ProfiledThread
 *
 * This approach is async-signal-safe and avoids TLS allocation issues.
 * 
 * Usage:
 *   {
 *     CriticalSection cs; // Atomically claim critical section
 *     if (!cs.entered()) return; // Another thread/signal handler is active
 *     // Complex data structure operations
 *     // Signal handlers will be blocked from entering
 *   } // Critical section automatically released
 * 
 * This eliminates race conditions between signal handlers and normal code
 * by ensuring only one can hold the critical section at a time per thread.
 */
class CriticalSection {
private:
    static constexpr size_t FALLBACK_BITMAP_WORDS = 1024;  // 8KB for 64K bits
    // Atomic bitmap for thread-safe critical section tracking without TLS
    // Must be atomic because multiple signal handlers can run concurrently across
    // different threads and attempt to set/clear bits simultaneously. Compare-and-swap
    // operations ensure race-free bit manipulation even during signal interruption.
    static uint64_t _fallback_bitmap[FALLBACK_BITMAP_WORDS];

    bool _entered;          // Track if this instance successfully entered
    bool _using_fallback;   // Track which storage mechanism we're using
    uint32_t _word_index;   // For fallback bitmap cleanup
    uint64_t _bit_mask;     // For fallback bitmap cleanup
    
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

private:
    // Hash function to distribute thread IDs across bitmap words
    static uint32_t hash_tid(int tid);
};

#endif // _CRITICALSECTION_H
