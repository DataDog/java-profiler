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
protected:
  // This is accessed from signal handlers, so must be async-signal-safe
  static bool _enabled;

public:
  // Count of signal handlers currently executing past the _enabled check.
  // stop() drains this to zero before tearing down JFR structures, closing
  // the TOCTOU window between the _enabled check and JFR buffer access.
  // Public so InflightGuard (in guards.cpp) can access it.
  // Placed on its own cache line to avoid false sharing with _enabled:
  // _enabled is read-only on the hot path; _inflight is read-write.
  alignas(64) static int _inflight;

  // Returns true if any handlers are still in-flight (stuck after timeout)
  static bool hasInflightHandlers() {
    return __atomic_load_n(&_inflight, __ATOMIC_ACQUIRE) > 0;
  }
  static long _interval;
  static CStack _cstack;
  static int _signal;

  static int _max_timers;
  static int *_timers;

  int registerThread(int tid);
  void unregisterThread(int tid);

private:
  // cppcheck-suppress unusedPrivateFunction
  static void signalHandler(int signo, siginfo_t *siginfo, void *ucontext);

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

  // Spin until all signal handlers that passed the _enabled=true check have
  // returned. Must be called with _enabled already false (after disableEngines()),
  // before any JFR teardown that handlers could race against.
  // Returns true if all handlers drained successfully, false if timeout fired.
  // Caller must NOT proceed with JFR teardown if this returns false.
  static bool drainInflight();

  // Get the signal number used by CTimer (0 if not initialized)
  static int getSignal() { return _signal; }
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