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

#ifndef _GUARDS_H
#define _GUARDS_H

#include <cstdint>
#include <cstddef>
#include <signal.h>
#include <pthread.h>

class ProfiledThread;

// ---------------------------------------------------------------------------
// Signal-context depth tracking — always on.
//
// Code paths that must choose between an async-signal-safe deferred path and
// a synchronous path (e.g. Profiler::dlopen_hook, which has to defer when a
// library is lazily loaded from signal context) query isInSignalContext().
// The debug-only DEBUG_ASSERT_NOT_IN_SIGNAL() macro in signalSafety.h
// asserts on the same counter.
//
// Cost in release: ~2 thread-local writes per signal handler invocation
// (negligible).  Pre-warming libgcc_s in Profiler::start() closes the
// known case; this counter is the safety net for the remainder.
// ---------------------------------------------------------------------------

// Counter so nested signals (e.g. SIGSEGV inside SIGPROF) keep the flag
// asserted until the outermost handler returns.
extern thread_local int _in_signal_handler_depth;

inline int getInSignalDepth()    { return _in_signal_handler_depth; }
inline bool isInSignalContext()  { return _in_signal_handler_depth != 0; }

// Internal RAII type — do not instantiate directly; use the macros below.
class SignalHandlerScope {
public:
    SignalHandlerScope()  { ++_in_signal_handler_depth; }
    ~SignalHandlerScope() { if (_active) --_in_signal_handler_depth; }
    void release()        { if (_active) { --_in_signal_handler_depth; _active = false; } }
    SignalHandlerScope(const SignalHandlerScope&)            = delete;
    SignalHandlerScope& operator=(const SignalHandlerScope&) = delete;
private:
    bool _active = true;
};

// Declare a scope guard local that increments the depth on entry and
// decrements on scope exit.  Use as the very first statement in every
// installed signal handler.
#define SIGNAL_HANDLER_GUARD() SignalHandlerScope _signal_handler_scope

// Manually release the most recent SIGNAL_HANDLER_GUARD() before chaining to
// another handler that may longjmp through us (e.g. J9's SIGSEGV null-pointer
// check handler).  After release(), depth has already been decremented; the
// destructor becomes a no-op.
#define SIGNAL_HANDLER_GUARD_RELEASE() _signal_handler_scope.release()

// Compensate for a longjmp that bypassed a SignalHandlerScope's destructor.
// Call at the setjmp landing point AFTER a known longjmp originated from
// within a signal handler frame (e.g. HotSpot's checkFault → longjmp recovery
// in walkVM).
#define SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP()           \
    do {                                                \
        if (_in_signal_handler_depth > 0)               \
            --_in_signal_handler_depth;                 \
    } while (0)

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
 *
 * !Warning! This is not a generic critical section implementation.
 * It relies on the fact that 'put' operations can not be preempted by the 'processing' operation.
 * That means that each 'put' operation will fully complete before 'processing' proceeds.
 *
 * The only preemption sequence is like this:
 * - processing enter
 * - processing acquire critical section
 * - signal interrupts processing; results in calling put
 * - put tries to acquire the critical section and fails
 * - put bails out
 * - processing proceeds and eventually releases the critical section
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
    ProfiledThread* _thread_ptr; // ProfiledThread captured at construction

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

/**
 * RAII guard to block profiling signals during critical operations.
 *
 * Blocks SIGPROF and SIGVTALRM signals on construction and automatically
 * restores the original signal mask on destruction. This prevents signal
 * handlers from interrupting operations that are not async-signal-safe,
 * such as musl libc's TLS initialization.
 *
 * !WARNING!
 * For guarding access to code running as a signal handler use CriticalSection
 * !WARNING!
 *
 * Usage:
 *   {
 *     SignalBlocker blocker; // Blocks profiling signals
 *     // Perform operations that must not be interrupted by signals
 *     // (e.g., TLS initialization, malloc, etc.)
 *   } // Signal mask automatically restored
 *
 * The blocker is exception-safe: the signal mask will be restored even
 * if an exception is thrown within the protected scope.
 *
 * Note: This only blocks signals for the current thread. Other threads
 * continue to receive profiling signals normally.
 */
class SignalBlocker {
private:
  sigset_t _old_mask;
  bool _active;

public:
  SignalBlocker() : _active(false) {
    sigset_t prof_signals;
    sigemptyset(&prof_signals);

    // Block only the profiling signals that the profiler actually registers.
    // No profiler engine uses RT signals, so blocking them is unnecessary
    // and risks interfering with glibc NPTL internals (SIGRTMIN, SIGRTMIN+1)
    // or other JVM-internal signal usage.
    sigaddset(&prof_signals, SIGPROF);     // Used by ITimer and CTimer
    sigaddset(&prof_signals, SIGVTALRM);   // Used by WallClock

    if (pthread_sigmask(SIG_BLOCK, &prof_signals, &_old_mask) == 0) {
      _active = true;
    }
  }

  ~SignalBlocker() {
    if (_active) {
      pthread_sigmask(SIG_SETMASK, &_old_mask, nullptr);
    }
  }

  // Non-copyable
  SignalBlocker(const SignalBlocker&) = delete;
  SignalBlocker& operator=(const SignalBlocker&) = delete;
};

#endif // _GUARDS_H
