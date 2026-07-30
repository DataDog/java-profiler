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
// for exactly the mutex's lifetime (including while `fn` runs). A
// siglongjmp out of `fn` (e.g. Profiler::checkFault() recovering a SIGSEGV)
// bypasses the AsyncSampleMutex destructor, so callers landing at their
// sigsetjmp must check `guard_active` and call
// ThreadLocalData::set_unwinding_Java(false) themselves when it is still
// true on recovery -- see HotspotSupport::walkJavaStack. Pulling this out
// of walkJavaStack lets tests exercise the exact guard/flag lifetime
// pairing production code runs, instead of a hand-copied replica of it.
template <typename Fn>
inline void withAsyncSampleGuard(ThreadLocalData *threadLocalData,
                                  volatile bool &guard_active, Fn &&fn) {
  AsyncSampleMutex mutex(threadLocalData);
  if (mutex.acquired()) {
    guard_active = true;
    fn();
  }
  guard_active = false;
}

#endif // ASYNCSAMPLEMUTEX_H
