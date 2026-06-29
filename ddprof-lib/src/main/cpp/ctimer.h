/*
 * Copyright 2017 Andrei Pangin
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

#ifndef _CTIMER_H
#define _CTIMER_H

#include "engine.h"
#include <atomic>
#ifdef __linux__

#include "arch.h"
#include <signal.h>

class CTimer : public Engine {
private:
  // Count of signal handlers currently executing past the _enabled check.
  // drainInflight() waits for this to reach zero before JFR teardown, closing
  // the TOCTOU window between the _enabled check and JFR buffer access.
  // Placed on its own cache line to avoid false sharing with _enabled:
  // _enabled is read-only on the hot path; _inflight is read-write.
  alignas(64) static int _inflight;

  // cppcheck-suppress unusedPrivateFunction
  static void signalHandler(int signo, siginfo_t *siginfo, void *ucontext);

protected:
  // Accessed from signal handlers (including CTimerJvmti subclass), so must
  // be async-signal-safe. Mutated via enableEvents().
  static bool _enabled;

  static long _interval;
  static CStack _cstack;
  static int _signal;

  static int _max_timers;
  static int *_timers;

  int registerThread(int tid);
  void unregisterThread(int tid);

public:
  const char *units() { return "ns"; }

  const char *name() { return "CTimer"; }

  long interval() const { return _interval; }

  Error check(Arguments &args);
  Error start(Arguments &args);
  void stop();

  inline void enableEvents(bool enabled) {
    __atomic_store_n(&_enabled, enabled, __ATOMIC_RELEASE);
  }

  // In-flight handler tracking accessors (used by InflightGuard).
  // ACQUIRE on increment / RELEASE on decrement so drainInflight() observes
  // all handler-side writes before observing the counter at zero.
  static void enterHandler() {
    __atomic_fetch_add(&_inflight, 1, __ATOMIC_ACQUIRE);
  }
  static void exitHandler() {
    __atomic_fetch_sub(&_inflight, 1, __ATOMIC_RELEASE);
  }
  static bool hasInflightHandlers() {
    return __atomic_load_n(&_inflight, __ATOMIC_ACQUIRE) > 0;
  }

  // Spin until all signal handlers that passed the _enabled=true check have
  // returned. Must be called with _enabled already false (after disableEngines()),
  // before any JFR teardown that handlers could race against.
  // Returns true if all handlers drained successfully, false if timeout fired.
  // Caller must NOT proceed with JFR teardown if this returns false.
  static bool drainInflight();

  // Get the signal number used by CTimer (0 if not initialized)
  static int getSignal() { return _signal; }
};

// RAII guard for CTimer signal handler in-flight tracking.
// Increments the in-flight counter on construction and decrements on destruction,
// ensuring the counter is always balanced regardless of which exit path the
// handler takes. The counter (CTimer::_inflight) is cache-line-aligned to avoid
// false sharing with _enabled, minimizing cache line bouncing.
//
// Usage (at the start of CTimer signal handlers):
//   InflightGuard inflight;
class InflightGuard {
public:
    InflightGuard()  { CTimer::enterHandler(); }
    ~InflightGuard() { CTimer::exitHandler(); }

    // Non-copyable, non-movable
    InflightGuard(const InflightGuard&) = delete;
    InflightGuard& operator=(const InflightGuard&) = delete;
    InflightGuard(InflightGuard&&) = delete;
    InflightGuard& operator=(InflightGuard&&) = delete;
};

// A CPU-time engine that reuses CTimer's per-thread timer_create / SIGPROF
// dispatch, but instead of walking the stack in the signal handler delegates
// the walk to HotSpot's JFR RequestStackTrace JVMTI extension. The sampled
// event is emitted on our side with only a correlation ID; the JVM writes
// the stack trace (and its own JFR stack-trace id) into the concurrent JFR
// recording as jdk.StackTraceRequest. See VM::canRequestStackTrace().
class CTimerJvmti : public CTimer {
private:
  // cppcheck-suppress unusedPrivateFunction
  static void signalHandler(int signo, siginfo_t *siginfo, void *ucontext);

public:
  const char *name() { return "CTimerJvmti"; }

  Error check(Arguments &args);
  Error start(Arguments &args);
};

#else

class CTimer : public Engine {
public:
  Error check(Arguments &args) {
    return Error("CTimer is not supported on this platform");
  }

  Error start(Arguments &args) {
    return Error("CTimer is not supported on this platform");
  }

  static bool supported() { return false; }

  // No-op on non-Linux platforms
  static bool drainInflight() { return true; }
  static bool hasInflightHandlers() { return false; }
};

// No-op InflightGuard on non-Linux platforms where CTimer is unavailable.
class InflightGuard {
public:
    InflightGuard()  {}
    ~InflightGuard() {}
    InflightGuard(const InflightGuard&) = delete;
    InflightGuard& operator=(const InflightGuard&) = delete;
};

class CTimerJvmti : public Engine {
public:
  const char *name() { return "CTimerJvmti"; }

  Error check(Arguments &args) {
    return Error("CTimerJvmti is not supported on this platform");
  }

  Error start(Arguments &args) {
    return Error("CTimerJvmti is not supported on this platform");
  }
};

#endif // __linux__

#endif // _CTIMER_H