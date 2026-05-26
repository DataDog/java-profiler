/*
 * Copyright 2018 Andrei Pangin
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

#ifndef _ITIMER_H
#define _ITIMER_H

#include "engine.h"
#include <signal.h>

class ITimer : public Engine {
private:
  static volatile bool _enabled;
  static long _interval;
  static CStack _cstack;

  static void signalHandler(int signo, siginfo_t *siginfo, void *ucontext);

public:
  const char *units() { return "ns"; }

  const char *name() { return "ITimer"; }

  long interval() const { return _interval; }

  Error check(Arguments &args);
  Error start(Arguments &args);
  void stop();

  inline void enableEvents(bool enabled) { _enabled = enabled; }
};

// CPU-time engine identical to ITimer in its timer mechanism (process-wide
// setitimer(ITIMER_PROF) / SIGPROF) but delegates stack collection to the
// HotSpot JFR RequestStackTrace JVMTI extension instead of ASGCT.  Used on
// platforms where per-thread CPU timers are unavailable (e.g. macOS), as a
// macOS-compatible alternative to CTimerJvmti.  Because SIGPROF may land on
// any thread, nullptr is passed as ucontext so the JVM uses safepoint-based
// stack walking rather than relying on the signal-frame PC.
class ITimerJvmti : public Engine {
private:
  static volatile bool _enabled;
  static long _interval;

  static void signalHandler(int signo, siginfo_t *siginfo, void *ucontext);

public:
  const char *units() { return "ns"; }
  const char *name()  { return "ITimerJvmti"; }
  long interval() const { return _interval; }

  Error check(Arguments &args);
  Error start(Arguments &args);
  void  stop();

  inline void enableEvents(bool enabled) {
    __atomic_store_n(&_enabled, enabled, __ATOMIC_RELEASE);
  }
};

#endif // _ITIMER_H
