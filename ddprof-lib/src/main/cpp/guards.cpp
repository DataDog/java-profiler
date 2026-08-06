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

// Signal-context tracking — backed by ProfiledThread::_signal_depth; see
// the comment block in guards.h for the rationale (initial-exec TLS was
// rejected because of the static TLS surplus on Graal).

int getInSignalDepth() {
    ProfiledThread *pt = ProfiledThread::current();
    return pt != nullptr ? static_cast<int>(pt->signalDepth()) : 0;
}

bool isInTrackedSignalContext() {
    ProfiledThread *pt = ProfiledThread::current();
    // null ProfiledThread = no thread context;
    // the SignalHandlerScope never ran, so we have no positive evidence
    // of a signal frame.
    // See header comment for the rationale of returning false here.
    return pt != nullptr && pt->signalDepth() != 0;
}

SignalHandlerScope::SignalHandlerScope() : _active(true), _current(nullptr) {
    ProfiledThread *pt = ProfiledThread::acquireCurrent();
    if (pt != nullptr) {
        _current = pt;
        pt->enterSignalScope();
    } else {
        // No thread context: nothing to update; mark inactive so destructor
        // and release() are no-ops.
        _active = false;
    }
}

SignalHandlerScope::~SignalHandlerScope() {
    if (!_active) return;
    if (_current != nullptr) {
        _current->exitSignalScope();
    }
}

void SignalHandlerScope::release() {
    if (!_active) return;
    ProfiledThread *pt = ProfiledThread::current();
    if (pt != nullptr) {
        pt->exitSignalScope();
    }
    _active = false;
}

void signalHandlerUnwindAfterLongjmp() {
    ProfiledThread *pt = ProfiledThread::current();
    if (pt != nullptr) {
        pt->exitSignalScope();
    }
}


CriticalSection::CriticalSection() : _entered(false), _thread_ptr(nullptr) {
#ifdef UNIT_TEST
    _thread_ptr = ProfiledThread::initCurrentThreadSignalSafe();
#else
    _thread_ptr = ProfiledThread::current();
#endif
    assert(_thread_ptr != nullptr);
    _entered = _thread_ptr->tryEnterCriticalSection();
}

CriticalSection::~CriticalSection() {
    assert(_thread_ptr != nullptr);
    if (_entered) {
        _thread_ptr->exitCriticalSection();
    }
}
