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
#include <setjmp.h>   // sigjmp_buf (JmpCtxScope)
#include <signal.h>
#include <pthread.h>

#include "common.h"

class ProfiledThread;

// Block all profiling signals while a thread is exiting. Without this,
// a profiling signal delivered during the release()/pthread-teardown race
// window can allocate a new ProfiledThread that can never be freed (leak).
void blockProfilingForExit();

// ---------------------------------------------------------------------------
// Signal-context depth tracking — always on.
//
// Profiler::dlopen_hook is the production caller — it queries
// isInTrackedSignalContext() to decide between the synchronous refresh()
// path and the deferred markDirty() path.  The debug-only
// DEBUG_ASSERT_NOT_IN_SIGNAL() macro in signalSafety.h asserts on the
// same counter.
//
// Storage: the depth lives in ProfiledThread::_signal_depth.  An earlier
// design used a thread_local int, but on Graal aarch64 the lazy DTV slot
// allocation triggered malloc inside our signal handler and deadlocked
// against the JVMCI compiler holding the heap lock.  initial-exec fixed
// the malloc but tripped the static TLS surplus and broke dlopen on
// Graal.  ProfiledThread is already AS-safe-accessible via
// pthread_getspecific (POSIX guarantees it does not allocate; returns
// nullptr when unset).
//
// When ProfiledThread is null or via thread priming on a thread
// - Uninstrumented JVM-internal threads now get a ProfiledThread via priming when 
// supportPriming() allows it, so isInTrackedSignalContext() does track them once primed. 
// The no-ProfiledThread (returns false) path only applies when priming is unavailable or 
// the pool is exhausted. The SignalHandlerScope guard is a no-op on those threads
// (nothing to update), so isInTrackedSignalContext() returns false: production code
// prefers synchronous refresh() on null-PT threads because (a) those
// threads regularly call dlopen during normal JVM operation, and (b)
// wasmtime's broken sigaction patching depends on switchLibraryTrap
// running work inline.  The residual risk — an uninstrumented thread
// calling dlopen from inside a foreign signal handler — is small in
// practice: prewarmUnwinder() closes the known libgcc_s lazy-load case
// and mainstream JVM signal handlers are AS-safe by design.
//
// DEBUG_ASSERT_NOT_IN_SIGNAL likewise skips its check when ProfiledThread
// is null so well-behaved non-signal code on uninstrumented threads
// doesn't trip a false abort.
// ---------------------------------------------------------------------------

// Returns the signal-handler depth for the calling thread, or 0 if the
// thread has no ProfiledThread yet.  Intended for tests and diagnostic
// code; production callers should use isInTrackedSignalContext().
int getInSignalDepth();

// Returns true only when we have positively tracked entering one of our
// installed signal handlers on this thread (depth > 0 on a non-null
// ProfiledThread).  null ProfiledThread → false, matching the
// SignalHandlerScope semantics (the guard is a no-op there).
// Used by Profiler::dlopen_hook to gate the deferred-refresh branch.
bool isInTrackedSignalContext();

// Internal RAII type — do not instantiate directly; use the macros below.
class SignalHandlerScope {
public:
    SignalHandlerScope(bool shouldRunPriming = true);
    ~SignalHandlerScope();
    void release();
    SignalHandlerScope(const SignalHandlerScope&)            = delete;
    SignalHandlerScope& operator=(const SignalHandlerScope&) = delete;

    bool isActive() const { return _active; }
    ProfiledThread* current() const { return _current; }
private:
    ProfiledThread* _current;
    bool _active;
    DEBUG_ONLY(int _signal_depth;)
};

// Shared drop-path body for the SIGNAL_HANDLER_GUARD_OR_DROP* macros below.
// extra_stmt runs after the dropped-sample counter increment and before the
// return, so both macros stay in lockstep as the drop-accounting logic
// evolves.
#define SIGNAL_HANDLER_GUARD_OR_DROP_IMPL(extra_stmt)       \
      SignalHandlerScope _signal_handler_scope(true);       \
      if (!_signal_handler_scope.isActive()) {              \
        Counters::increment(SAMPLES_DROPPED_THREAD_LOCAL);  \
        extra_stmt;                                         \
        return;                                             \
      }

// Declare a scope guard local that increments the depth on entry and
// decrements on scope exit.  Use as the first statement after any 
// foreign-signal-origin rejection check, before any profiling-owned work
#define SIGNAL_HANDLER_GUARD_OR_DROP() SIGNAL_HANDLER_GUARD_OR_DROP_IMPL((void)0)
#define SIGNAL_HANDLER_GUARD_OR_DROP_WITH_ERRNO(err) SIGNAL_HANDLER_GUARD_OR_DROP_IMPL(errno = err)


// Declare a scope guard local that increments the depth on entry and
// decrements on scope exit.  Use as the first statement of non-profiling
// signal handlers (segvHandler, busHandler and wakeupHandler) 
#define SIGNAL_HANDLER_GUARD_NO_SAMPLE()                    \
      SignalHandlerScope _signal_handler_scope(false);

// Cheaper way to retrieve current ProfiledThread inside the scope
#define SIGNAL_HANDLER_CURRENT_THREAD() _signal_handler_scope.current()

// Manually release the most recent SIGNAL_HANDLER_GUARD_OR_DROP()/SIGNAL_HANDLER_GUARD_NO_SAMPLE()
// before chaining to another handler that may siglongjmp through us (e.g. J9's SIGSEGV
// null-pointer check handler).  After release(), depth has already been decremented; the
// destructor becomes a no-op.
#define SIGNAL_HANDLER_GUARD_RELEASE() _signal_handler_scope.release()

// Compensate for a siglongjmp that bypassed a SignalHandlerScope's destructor.
// Call at the sigsetjmp landing point AFTER a known siglongjmp originated from
// within a signal handler frame (e.g. HotSpot's checkFault → siglongjmp recovery
// in walkVM).
void signalHandlerUnwindAfterLongjmp();
#define SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP() signalHandlerUnwindAfterLongjmp()

// RAII for the per-thread siglongjmp landing pad (ProfiledThread::_jmp_buf)
// that Profiler::checkFault() jumps through.
//
// The previous landing pad must be reinstated on *every* exit from the frame
// that owns the sigjmp_buf -- normal return, a siglongjmp back into it, or an
// exception unwinding out of it -- because checkFault() will happily jump into
// a landing pad whose stack frame has already been popped. Hand-rolled
// "setJmpCtx(prev) before each return" only covers the returns the author
// remembered.
//
// Both members are const and initialised before the owning frame calls
// sigsetjmp(), and install()/restore() mutate only the ProfiledThread, so the
// guard's own state is never modified between sigsetjmp() and siglongjmp().
// Reading it from the landing pad is therefore well defined -- unlike a plain
// non-volatile local, whose value after siglongjmp is indeterminate if it was
// assigned in the meantime.
//
// Usage:
//   sigjmp_buf ctx;
//   JmpCtxScope jmp_scope(prof_thread);       // pt must be non-null
//   if (sigsetjmp(ctx, 1) != 0) {             // savemask=1: see note below
//     SIGNAL_HANDLER_UNWIND_AFTER_LONGJMP();
//     jmp_scope.restore();                    // disarm before anything else
//     return recovery_value;
//   }
//   jmp_scope.install(&ctx);
//   ... risky work ...
//
// savemask must be 1: the siglongjmp originates inside the SIGSEGV handler,
// where the kernel has SIGSEGV blocked, so without restoring the saved mask the
// signal would stay blocked and the next fault on this thread would be fatal.
class JmpCtxScope {
public:
    // `pt` must be non-null.
    explicit JmpCtxScope(ProfiledThread* pt);
    ~JmpCtxScope();
    // Publish `ctx` as this thread's landing pad; call after sigsetjmp()
    // returns 0.
    void install(sigjmp_buf* ctx);
    // Reinstate the previous landing pad now. Idempotent with the destructor,
    // so it is safe (and required) to call from the sigsetjmp landing pad
    // before touching anything that could fault again.
    void restore();
    JmpCtxScope(const JmpCtxScope&)            = delete;
    JmpCtxScope& operator=(const JmpCtxScope&) = delete;
private:
    ProfiledThread* const _pt;
    sigjmp_buf* const _prev;
};

/**
 * Race-free critical section using atomic compare-and-swap.
 *
 * Backed by ProfiledThread::_in_critical_section (zero extra memory
 * overhead). ProfiledThread::acquireCurrent() is used instead of current()
 * so that a not-yet-primed thread can still get a ProfiledThread from
 * ThreadLocalDataPool's pre-allocated pool. If priming is unsupported
 * (e.g. macOS) and the pool is exhausted, acquireCurrent() returns
 * nullptr and entered() is simply false — there is no unguarded thread
 * pointer dereference in that case.
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
    bool _entered;          // Track if this instance successfully entered
    ProfiledThread* _thread_ptr; // ProfiledThread captured at construction

public:
    CriticalSection(ProfiledThread* pt = nullptr);
    ~CriticalSection();

    // Non-copyable, non-movable
    CriticalSection(const CriticalSection&) = delete;
    CriticalSection& operator=(const CriticalSection&) = delete;
    CriticalSection(CriticalSection&&) = delete;
    CriticalSection& operator=(CriticalSection&&) = delete;

    // Check if this instance successfully entered the critical section
    bool entered() const { return _entered; }
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
