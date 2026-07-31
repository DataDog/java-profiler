/*
 * Copyright 2026, Datadog, Inc
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

#ifndef ASYNCSAMPLEMUTEX_H
#define ASYNCSAMPLEMUTEX_H

#include "threadLocalData.h"

// controls access to AGCT
class AsyncSampleMutex {
private:
  ThreadLocalData *_threadLocalData;
  bool _acquired;

  bool try_acquire() {
    if (_threadLocalData != nullptr && !_threadLocalData->is_unwinding_Java()) {
      _threadLocalData->set_unwinding_Java(true);
      return true;
    }
    return false;
  }

public:
  AsyncSampleMutex(ThreadLocalData *threadLocalData)
      : _threadLocalData(threadLocalData) {
    _acquired = try_acquire();
  }

  AsyncSampleMutex(AsyncSampleMutex &other) = delete;

  ~AsyncSampleMutex() {
    if (_acquired) {
      _threadLocalData->set_unwinding_Java(false);
    }
  }

  bool acquired() { return _acquired; }
};

// Runs `fn` while holding an AsyncSampleMutex, keeping `guard_active` true
// for at least the mutex's lifetime (including while `fn` runs). A
// siglongjmp out of `fn` (e.g. Profiler::checkFault() recovering a SIGSEGV)
// bypasses the AsyncSampleMutex destructor, so callers landing at their
// sigsetjmp must check `guard_active` and call
// ThreadLocalData::set_unwinding_Java(false) themselves when it is still
// true on recovery -- see HotspotSupport::walkJavaStack. Pulling this out
// of walkJavaStack lets tests exercise the exact guard/flag lifetime
// pairing production code runs, instead of a hand-copied replica of it.
//
// The mutex lives in its own nested scope so its destructor -- which clears
// is_unwinding_Java on the owning ThreadLocalData -- runs before
// `guard_active` is cleared below, not after. If `guard_active` were cleared
// first (as a single flat scope would do, since the mutex's destructor only
// runs at the function's closing brace), a second signal/fault landing in
// that gap and recovered via the caller's sigsetjmp would see `guard_active
// == false`, skip the compensating clear, and never get another chance --
// the real siglongjmp already bypassed the destructor -- leaving
// is_unwinding_Java stuck true and the thread permanently excluded from
// async sampling. Clearing `guard_active` only after the destructor has
// already run makes a fault in that gap a harmless redundant compensation
// instead of a missed one.
template <typename Fn>
inline void withAsyncSampleGuard(ThreadLocalData *threadLocalData,
                                  volatile bool &guard_active, Fn &&fn) {
  {
    AsyncSampleMutex mutex(threadLocalData);
    if (mutex.acquired()) {
      guard_active = true;
      fn();
    }
  }
  guard_active = false;
}

#endif // ASYNCSAMPLEMUTEX_H
