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

// Planted violations for `utils/check-signal-reachability.py --self-test`.
// Compiled on its own into a temporary directory; never linked or run.
// Class and function names mirror the checker's ROOTS / UNSAFE_SINKS.
//
//   EXPECT:             must be reported as a new finding
//   EXPECT-ALLOWLISTED: must be found and suppressed by the self-test allowlist
//   EXPECT-NOT:         must not be reported
// Entries are "<caller> -> <unsafe symbol>" exactly as the checker prints them.

struct siginfo_t;

extern "C" {
void *malloc(unsigned long size);
int snprintf(char *buf, unsigned long size, const char *fmt, ...);
}

class Log {
public:
  static void warn(const char *fmt, ...);
};

class SpinLock {
public:
  void lock();
};

class ProfiledThread {
public:
  static ProfiledThread *initCurrentThread();
  static ProfiledThread *initCurrentThreadSignalSafe();
};

// Direct libc call from a signal handler.
// EXPECT: CTimer::signalHandler -> malloc
class CTimer {
public:
  static void signalHandler(int signo, siginfo_t *info, void *ucontext);
};
void CTimer::signalHandler(int, siginfo_t *, void *) { (void)malloc(16); }

// Transitive call through static helpers: the calls go through section
// symbols (.text._ZL...), not function symbols.
// EXPECT: formatSlowPath -> snprintf
static void formatSlowPath(char *buf) { snprintf(buf, 8, "%d", 1); }
static void formatValue(char *buf) { formatSlowPath(buf); }
class ITimer {
public:
  static void signalHandler(int signo, siginfo_t *info, void *ucontext);
};
void ITimer::signalHandler(int, siginfo_t *, void *) {
  char buf[8];
  formatValue(buf);
}

// Lock taken in a constructor: the call site references the complete-object
// constructor (C1), whose body is emitted as an alias of the base-object
// constructor (C2).
// EXPECT: LockGuard::LockGuard -> SpinLock::lock
class LockGuard {
public:
  explicit LockGuard(SpinLock *lock);
};
LockGuard::LockGuard(SpinLock *lock) { lock->lock(); }
class PerfEvents {
public:
  static void signalHandler(int signo, siginfo_t *info, void *ucontext);
};
void PerfEvents::signalHandler(int, siginfo_t *, void *) {
  static SpinLock lock;
  LockGuard guard(&lock);
}

// thread_local access (dynamic TLS) from a signal handler.
// EXPECT: Profiler::segvHandler -> TLS_ACCESS:t_depth
// A singleton accessor is a barrier: its callees are not followed.
// EXPECT-NOT: Profiler::instance -> malloc
thread_local int t_depth;
class Profiler {
public:
  static Profiler *instance();
  static bool segvHandler(int signo, siginfo_t *info, void *ucontext);
};
Profiler *Profiler::instance() { return static_cast<Profiler *>(malloc(1)); }
bool Profiler::segvHandler(int, siginfo_t *, void *) {
  Profiler::instance();
  return ++t_depth > 1;
}

// Heap allocation from a malloc interposer.
// EXPECT: malloc_hook -> operator new[]
extern "C" __attribute__((visibility("default"))) void *malloc_hook(unsigned long size) {
  return new char[size];
}

// Allocation inside a standard-library template is attributed to the
// profiler function calling into it.
// EXPECT: CTimerJvmti::signalHandler -> operator new
namespace std {
template <class T> struct fixture_box {
  static T *make() { return new T(); }
};
} // namespace std
class CTimerJvmti {
public:
  static void signalHandler(int signo, siginfo_t *info, void *ucontext);
};
void CTimerJvmti::signalHandler(int, siginfo_t *, void *) {
  (void)std::fixture_box<int>::make();
}

// Only the non-signal-safe ProfiledThread initializer is a sink.
// EXPECT: WallClockJvmti::sharedSignalHandler -> ProfiledThread::initCurrentThread
// EXPECT-NOT: WallClockASGCT::sharedSignalHandler -> ProfiledThread::initCurrentThreadSignalSafe
class WallClockJvmti {
public:
  static void sharedSignalHandler(int signo, siginfo_t *info, void *ucontext);
};
void WallClockJvmti::sharedSignalHandler(int, siginfo_t *, void *) {
  ProfiledThread::initCurrentThread();
}
class WallClockASGCT {
public:
  static void sharedSignalHandler(int signo, siginfo_t *info, void *ucontext);
};
void WallClockASGCT::sharedSignalHandler(int, siginfo_t *, void *) {
  ProfiledThread::initCurrentThreadSignalSafe();
}

// Static (local-symbol) root; finding suppressed by the self-test allowlist.
// EXPECT-ALLOWLISTED: wakeupHandler -> Log::warn
__attribute__((used)) static void wakeupHandler(int) { Log::warn("wakeup"); }

// Not reachable from any root.
// EXPECT-NOT: unrelatedFunction -> malloc
void unrelatedFunction() { (void)malloc(1); }
