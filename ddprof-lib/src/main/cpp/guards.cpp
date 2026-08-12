/*
 * Copyright 2025, 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cassert>

#include "guards.h"
#include "common.h"
#include "os.h"
#include "threadLocalData.h"

// Signal-context tracking — backed by ProfiledThread::_signal_depth; see
// the comment block in guards.h for the rationale (initial-exec TLS was
// rejected because of the static TLS surplus on Graal).

int getInSignalDepth() {
    ProfiledThread *pt = ProfiledThread::current();
    // Deliberately returns the raw counter, negative values included, so a
    // pairing bug is visible to tests and diagnostics rather than clamped away.
    return pt != nullptr ? pt->signalDepth() : 0;
}

bool isInTrackedSignalContext() {
    ProfiledThread *pt = ProfiledThread::current();
    // null ProfiledThread = no thread context; the SignalHandlerScope
    // never ran, so we have no positive evidence of a signal frame.
    // See header comment for the rationale of returning false here.
    //
    // `> 0`, not `!= 0`: exitSignalScope() asserts the depth never drops below
    // zero, but that assert is compiled out under -DNDEBUG, so in a release
    // build an unmatched decrement would leave the counter negative. Reading a
    // negative depth as "not in a signal handler" keeps the blast radius of
    // such a bug to the one bad decrement, instead of latching dlopen_hook onto
    // the deferred-refresh path for the rest of the thread's life.
    return pt != nullptr && pt->signalDepth() > 0;
}

SignalHandlerScope::SignalHandlerScope() : _active(true) {
    ProfiledThread *pt = ProfiledThread::current();
    if (pt != nullptr) {
        DEBUG_ONLY(_signal_depth = pt->signalDepth();)
        pt->enterSignalScope();
    } else {
        // No thread context: nothing to update; mark inactive so destructor
        // and release() are no-ops.
        _active = false;
    }
}

SignalHandlerScope::~SignalHandlerScope() {
    if (!_active) return;
    ProfiledThread *pt = ProfiledThread::current();
    if (pt != nullptr) {
        pt->exitSignalScope();
        DEBUG_ONLY(assert(_signal_depth == pt->signalDepth());)
    }
}

void SignalHandlerScope::release() {
    if (!_active) return;
    ProfiledThread *pt = ProfiledThread::current();
    if (pt != nullptr) {
        pt->exitSignalScope();
        DEBUG_ONLY(assert(_signal_depth == pt->signalDepth());)
    }
    _active = false;
}

void signalHandlerUnwindAfterLongjmp() {
    ProfiledThread *pt = ProfiledThread::current();
    if (pt != nullptr) {
        pt->exitSignalScope();
    }
}

JmpCtxScope::JmpCtxScope(ProfiledThread *pt) : _pt(pt), _prev(pt->getJmpCtx()) {
    assert(pt != nullptr);
}

JmpCtxScope::~JmpCtxScope() { _pt->setJmpCtx(_prev); }

void JmpCtxScope::install(sigjmp_buf *ctx) { _pt->setJmpCtx(ctx); }

void JmpCtxScope::restore() { _pt->setJmpCtx(_prev); }

// Static bitmap storage for fallback cases
uint64_t CriticalSection::_fallback_bitmap[CriticalSection::FALLBACK_BITMAP_WORDS] = {};

CriticalSection::CriticalSection() : _entered(false), _using_fallback(false), _word_index(0), _bit_mask(0), _thread_ptr(nullptr) {
    _thread_ptr = ProfiledThread::current();
    if (_thread_ptr != nullptr) {
        // Primary path: Use ProfiledThread storage (fast and memory-efficient)
        _entered = _thread_ptr->tryEnterCriticalSection();
    } else {
        // Fallback path: Use hash-based bitmap for stress tests and edge cases
        _using_fallback = true;
        int tid = OS::threadId();

        // Hash TID to distribute across bitmap words, reducing clustering
        // We are OK with false collision for the fallback - it should be used only for testing when we don't have full profiler initialized
        _word_index = hash_tid(tid) % FALLBACK_BITMAP_WORDS;
        uint32_t bit_index = tid % 64;
        _bit_mask = 1ULL << bit_index;

        // Use ACQUIRE ordering to ensure visibility of protected data after acquiring critical section
        uint64_t old_word = __atomic_fetch_or(&_fallback_bitmap[_word_index], _bit_mask, __ATOMIC_ACQUIRE);
        _entered = !(old_word & _bit_mask);  // Success if bit was previously 0
    }
}

CriticalSection::~CriticalSection() {
    if (_entered) {
        if (_using_fallback) {
            // Clear the bit atomically for fallback bitmap
            // Use RELEASE ordering to ensure protected data writes are visible before releasing
            __atomic_fetch_and(&_fallback_bitmap[_word_index], ~_bit_mask, __ATOMIC_RELEASE);
        } else {
            // Release ProfiledThread flag using the pointer captured at construction
            if (_thread_ptr != nullptr) {
                _thread_ptr->exitCriticalSection();
            }
        }
    }
}

uint32_t CriticalSection::hash_tid(int tid) {
    return static_cast<uint32_t>(tid * KNUTH_MULTIPLICATIVE_CONSTANT);
}
