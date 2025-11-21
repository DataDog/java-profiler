/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "criticalSection.h"
#include "common.h"
#include "os.h"
#include "thread.h"

// Static bitmap storage for fallback cases
uint64_t CriticalSection::_fallback_bitmap[CriticalSection::FALLBACK_BITMAP_WORDS] = {};

CriticalSection::CriticalSection() : _entered(false), _using_fallback(false), _word_index(0), _bit_mask(0) {
    ProfiledThread* current = ProfiledThread::currentSignalSafe();
    if (current != nullptr) {
        // Primary path: Use ProfiledThread storage (fast and memory-efficient)
        _entered = current->tryEnterCriticalSection();
    } else {
        // Fallback path: Use hash-based bitmap for stress tests and edge cases
        _using_fallback = true;
        int tid = OS::threadId();

        // Hash TID to distribute across bitmap words, reducing clustering
        // We are OK with false collision for the fallback - it should be used only for testing when we don't have full profiler initialized
        _word_index = hash_tid(tid) % FALLBACK_BITMAP_WORDS;
        uint32_t bit_index = tid % 64;
        _bit_mask = 1ULL << bit_index;

        uint64_t old_word = __atomic_fetch_or(&_fallback_bitmap[_word_index], _bit_mask, __ATOMIC_RELAXED);
        _entered = !(old_word & _bit_mask);  // Success if bit was previously 0
    }
}

CriticalSection::~CriticalSection() {
    if (_entered) {
        if (_using_fallback) {
            // Clear the bit atomically for fallback bitmap
            __atomic_fetch_and(&_fallback_bitmap[_word_index], ~_bit_mask, __ATOMIC_RELAXED);
        } else {
            // Release ProfiledThread flag
            ProfiledThread* current = ProfiledThread::currentSignalSafe();
            if (current != nullptr) {
                current->exitCriticalSection();
            }
        }
    }
}

uint32_t CriticalSection::hash_tid(int tid) {
    return static_cast<uint32_t>(tid * KNUTH_MULTIPLICATIVE_CONSTANT);
}
