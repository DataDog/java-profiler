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

#include "guards.h"
#include "common.h"
#include "os.h"
#include "threadLocalData.inline.h"

#include <cassert>

void blockProfilingForExit() {
    sigset_t prof_signals, old_signals;
    sigemptyset(&prof_signals);
    sigaddset(&prof_signals, SIGPROF);     // Used by ITimer and CTimer
    sigaddset(&prof_signals, SIGVTALRM);   // Used by WallClock

    int rc= pthread_sigmask(SIG_BLOCK, &prof_signals, &old_signals);
    assert(rc == 0);
}

// Signal-context tracking — backed by ProfiledThread::_signal_depth; see
// the comment block in guards.h for the rationale (initial-exec TLS was
// rejected because of the static TLS surplus on Graal).

int getInSignalDepth() {
    ProfiledThread *pt = ProfiledThread::current();
    // Deliberately returns the raw counter, negative values included, so a
    // pairing bug is visible to tests and diagnostics rather than clamped away.
    int depth = pt != nullptr ? pt->signalDepth() : 0;
    assert(depth >= 0 && "Mismatched signal scope");
    return depth;
}

bool isInTrackedSignalContext() {
    ProfiledThread *pt = ProfiledThread::current();
    // null ProfiledThread = no thread context; the SignalHandlerScope
    // never ran, so we have no positive evidence of a signal frame.

    // See header comment for the rationale of returning false here.
    // `> 0` rather than `!= 0`: a negative depth is a pairing bug (an
    // unmatched signalHandlerUnwindAfterLongjmp()), not evidence of being in
    // a signal handler, and must not pin dlopen_hook to the deferred-refresh
    // path for the rest of the thread's life.
    return pt != nullptr && pt->signalDepth() > 0;
}

SignalHandlerScope::SignalHandlerScope(bool shouldRunPriming) : _current(nullptr), _active(true) {
    ProfiledThread *pt = shouldRunPriming ? ProfiledThread::acquireCurrent() : ProfiledThread::current();
    if (pt != nullptr) {
        DEBUG_ONLY(_signal_depth = pt->signalDepth();)
        _current = pt;
        pt->enterSignalScope();
    } else {
        // No thread context: nothing to update; mark inactive so destructor
        // and release() are no-ops.
        _active = false;
    }
}

SignalHandlerScope::~SignalHandlerScope() {
    release();
}

void SignalHandlerScope::release() {
    if (!_active) return;
    if (_current != nullptr) {
        _current->exitSignalScope();
        DEBUG_ONLY(assert(_signal_depth == _current->signalDepth());)
    }
    _active = false;
}

void signalHandlerUnwindAfterLongjmp() {
    ProfiledThread *pt = ProfiledThread::current();
    if (pt != nullptr) {
        pt->exitSignalScope();
    }
}

CriticalSection::CriticalSection(ProfiledThread* pt) : _entered(false), _thread_ptr(pt) {
    // acquireCurrent() falls back to ThreadLocalDataPool::acquire() (a
    // pre-allocated, async-signal-safe pool) when the calling thread has
    // not been primed yet. _thread_ptr can still legitimately be nullptr
    // here if priming is unsupported (e.g. macOS) and the pool is
    // exhausted; treat that as "did not enter" rather than dereferencing.
    if (_thread_ptr == nullptr) {
        _thread_ptr = ProfiledThread::acquireCurrent();
    }

    if (_thread_ptr != nullptr) {
        _entered = _thread_ptr->tryEnterCriticalSection();
    }
}

CriticalSection::~CriticalSection() {
    if (_entered && _thread_ptr != nullptr) {
        _thread_ptr->exitCriticalSection();
    }
}


// Reads the currently installed landing pad, asserting the non-null contract
// *before* the pointer is dereferenced. This lives in a helper rather than the
// constructor body because the mem-initialiser for _prev runs first, so an
// assert in the body would only fire after the deref it is meant to guard.
static sigjmp_buf* prevJmpCtxOf(ProfiledThread* pt) {
    assert(pt != nullptr);
    return pt->getJmpCtx();
}

JmpCtxScope::JmpCtxScope(ProfiledThread* pt) : _pt(pt), _prev(prevJmpCtxOf(pt)) {}

// Unconditional store, deliberately not guarded by an "already restored" flag;
// see restore().
JmpCtxScope::~JmpCtxScope() {
   restore();
}

void JmpCtxScope::install(sigjmp_buf* ctx) {
    _pt->setJmpCtx(ctx);
}

// Idempotent with the destructor by construction: _prev is const, so this is
// the same store every time it runs. No mutable "restored" flag is used -- and
// none may be added -- because this object is an automatic local of the frame
// that owns the sigjmp_buf, so any member mutated between sigsetjmp() and
// siglongjmp() would have an indeterminate value at the landing pad.
//
// Nesting stays correct without a flag: scopes are automatic objects, so
// construction/destruction is strictly LIFO and each constructor snapshots
// getJmpCtx() at its own construction time. An outer scope's destructor can
// therefore never clobber a context installed by an inner one.
void JmpCtxScope::restore() {
    _pt->setJmpCtx(_prev);
}
