/*
 * Copyright 2023 Andrei Pangin
 * Copyright 2025, 2026, Datadog, Inc.
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

#ifdef __linux__

#include "counters.h"
#include "guards.h"
#include "ctimer.h"
#include "debugSupport.h"
#include "jvmThread.h"
#include "libraries.h"
#include "log.h"
#include "profiler.h"
#include "signalCookie.h"
#include "threadState.inline.h"
#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

#ifndef SIGEV_THREAD_ID
#define SIGEV_THREAD_ID 4
#endif

static inline clockid_t thread_cpu_clock(unsigned int tid) {
  return ((~tid) << 3) | 6; // CPUCLOCK_SCHED | CPUCLOCK_PERTHREAD_MASK
}

long CTimer::_interval;
int CTimer::_max_timers = 0;
int *CTimer::_timers = NULL;
CStack CTimer::_cstack;
bool CTimer::_enabled = false;
int CTimer::_signal;

int CTimer::registerThread(int tid) {
  if (tid >= _max_timers) {
    Log::warn("tid[%d] > pid_max[%d]. Restart profiler after changing pid_max",
              tid, _max_timers);
    return -1;
  }

  struct sigevent sev;
  // Zero the whole struct first so any padding / future fields the kernel
  // inspects (sigev_notify_function, sigev_notify_attributes on glibc) are
  // not populated from stack garbage.
  memset(&sev, 0, sizeof(sev));
  // Cookie identifying this timer as ddprof-owned. When the signal is delivered
  // the handler checks siginfo->si_value.sival_ptr against SignalCookie::cpu()
  // and drops/forwards any SIGPROF that does not carry it (e.g. from a Go
  // runtime's setitimer(ITIMER_PROF) or a foreign library's raise()).
  sev.sigev_value.sival_ptr = SignalCookie::cpu();
  sev.sigev_signo = _signal;
  sev.sigev_notify = SIGEV_THREAD_ID;
  // glibc/musl layout convention: sigev_notify_thread_id sits immediately
  // after sigev_notify inside the union — the tid is written as the *second*
  // int starting at &sev.sigev_notify, so bytes [sizeof(int), 2*sizeof(int))
  // of that int-pointer must be in-bounds of struct sigevent. Guard against
  // a future libc change by statically asserting that both ints fit.
  static_assert(offsetof(struct sigevent, sigev_notify) + 2 * sizeof(int)
                    <= sizeof(struct sigevent),
                "sigevent layout assumption broken: tid write would overflow");
  ((int *)&sev.sigev_notify)[1] = tid;

  // Use raw syscalls, since libc wrapper allows only predefined clocks
  clockid_t clock = thread_cpu_clock(tid);
  int timer;
  if (syscall(__NR_timer_create, clock, &sev, &timer) < 0) {
    return -1;
  }

  // Kernel timer ID may start with zero, but we use zero as an empty slot
  if (!__sync_bool_compare_and_swap(&_timers[tid], 0, timer + 1)) {
    // Lost race
    syscall(__NR_timer_delete, timer);
    return -1;
  }

  struct itimerspec ts;
  ts.it_interval.tv_sec = (time_t)(_interval / 1000000000);
  ts.it_interval.tv_nsec = _interval % 1000000000;
  ts.it_value = ts.it_interval;
  if (syscall(__NR_timer_settime, timer, 0, &ts, NULL) < 0) {
    // Arming failed after publishing the timer in _timers[tid]. Reclaim the
    // slot only if it still contains this timer; otherwise a concurrent
    // unregisterThread(tid) has already claimed responsibility for cleanup
    // (avoids a double timer_delete).
    int settime_errno = errno;
    char errbuf[64];
    strerror_r(settime_errno, errbuf, sizeof(errbuf));
    Log::warn("timer_settime failed for tid=%d: %s", tid, errbuf);
    errno = settime_errno;
    if (__sync_bool_compare_and_swap(&_timers[tid], timer + 1, 0)) {
      syscall(__NR_timer_delete, timer);
    }
    return -1;
  }
  return 0;
}

void CTimer::unregisterThread(int tid) {
  if (tid >= _max_timers) {
    return;
  }
  // Atomic acquire to avoid possible leak when unregistering
  // This was raised by tsan, with registers and unregisters done in separate
  // threads.
  int timer = __atomic_load_n(&_timers[tid], __ATOMIC_ACQUIRE);
  if (timer != 0 && __sync_bool_compare_and_swap(&_timers[tid], timer--, 0)) {
    syscall(__NR_timer_delete, timer);
  }
}

Error CTimer::check(Arguments &args) {
  timer_t timer;
  if (timer_create(CLOCK_THREAD_CPUTIME_ID, NULL, &timer) < 0) {
    return Error("Failed to create CPU timer");
  }
  timer_delete(timer);

  return Error::OK;
}

Error CTimer::start(Arguments &args) {
  if (args._interval < 0) {
    return Error("interval must be positive");
  }

  _interval = args.cpuSamplerInterval();
  _cstack = args._cstack;
  _signal = SIGPROF;

  int max_timers = OS::getMaxThreadId();
  if (max_timers != _max_timers) {
    free(_timers);
    _timers = (int *)calloc(max_timers, sizeof(int));
    _max_timers = max_timers;
  }

  // Prime the origin-check cache from this non-signal context before any
  // SIGPROF can fire — reading the env var lazily from the handler itself
  // would go through a C++ function-local-static guard, which is not
  // async-signal-safe.
  OS::primeSignalOriginCheck();

  OS::installSignalHandler(_signal, signalHandler);

  // Register all existing threads
  Error result = Error::OK;
  ThreadList *thread_list = OS::listThreads();
  while (thread_list->hasNext()) { 
    int tid = thread_list->next();
    int err = registerThread(tid);
    if (err != 0) {
      result = Error("Failed to register thread");
    }
  }
  delete thread_list;

  return result;
}

void CTimer::stop() {
  for (int i = 0; i < _max_timers; i++) {
    unregisterThread(i);
  }
}

Error CTimerJvmti::check(Arguments &args) {
  if (!VM::canRequestStackTrace()) {
    return Error("HotSpot RequestStackTrace JVMTI extension not available");
  }
  return CTimer::check(args);
}

Error CTimerJvmti::start(Arguments &args) {
  if (!VM::canRequestStackTrace()) {
    return Error("HotSpot RequestStackTrace JVMTI extension not available");
  }
  Error result = CTimer::start(args);
  if (result) return result;
  // Override the signal handler installed by CTimer::start with our own,
  // which delegates stack walking to the HotSpot JFR extension.
  OS::installSignalHandler(_signal, CTimerJvmti::signalHandler);
  return Error::OK;
}

void CTimerJvmti::signalHandler(int signo, siginfo_t *siginfo, void *ucontext) {
  if (!OS::shouldProcessSignal(siginfo, SI_TIMER, SignalCookie::cpu())) {
    Counters::increment(CTIMER_SIGNAL_FOREIGN);
    OS::forwardForeignSignal(signo, siginfo, ucontext);
    return;
  }
  Counters::increment(CTIMER_SIGNAL_OWN);

  CriticalSection cs;
  if (!cs.entered()) {
    return;
  }
  int saved_errno = errno;
  if (!__atomic_load_n(&_enabled, __ATOMIC_ACQUIRE)) {
    errno = saved_errno;
    return;
  }
  int tid = 0;
  ProfiledThread *current = ProfiledThread::currentSignalSafe();
  assert(current == nullptr || !current->isDeepCrashHandler());
  if (current != nullptr && JVMThread::isInitialized() && JVMThread::current() == nullptr
      && current->inInitWindow()) {
    current->tickInitWindow();
    errno = saved_errno;
    return;
  }
  if (current != NULL) {
    current->noteCPUSample(Profiler::instance()->recordingEpoch());
    tid = current->tid();
  } else {
    tid = OS::threadId();
  }
  Shims::instance().setSighandlerTid(tid);

  ExecutionEvent event;
  event._execution_mode = getThreadExecutionMode();
  // Opted into JVMTI delegation; drop the sample if the JVM rejects the
  // request (WRONG_PHASE if JFR is not recording, NOT_AVAILABLE if
  // jdk.AsyncStackTrace is disabled). recordSampleDelegated() bumps the
  // failure counters; there is no fallback to ASGCT in this engine.
  (void)Profiler::instance()->recordSampleDelegated(ucontext, _interval, tid,
                                                    BCI_CPU, &event);
  Shims::instance().setSighandlerTid(-1);
  errno = saved_errno;
}

void CTimer::signalHandler(int signo, siginfo_t *siginfo, void *ucontext) {
  // Reject signals that did not originate from our timer_create timers.
  // This guards against Go's process-wide setitimer(ITIMER_PROF) and other
  // foreign SIGPROF sources that would otherwise drive our handler onto
  // threads we never registered — see doc/plans/SignalOriginValidation.md.
  if (!OS::shouldProcessSignal(siginfo, SI_TIMER, SignalCookie::cpu())) {
    Counters::increment(CTIMER_SIGNAL_FOREIGN);
    OS::forwardForeignSignal(signo, siginfo, ucontext);
    return;
  }
  Counters::increment(CTIMER_SIGNAL_OWN);

  // Atomically try to enter critical section - prevents all reentrancy races
  CriticalSection cs;
  if (!cs.entered()) {
    return;  // Another critical section is active, defer profiling
  }
  // Save the current errno value
  int saved_errno = errno;
  // we want to ensure memory order because of the possibility the instance gets
  // cleared
  if (!__atomic_load_n(&_enabled, __ATOMIC_ACQUIRE))
    return;
  int tid = 0;
  ProfiledThread *current = ProfiledThread::currentSignalSafe();
  assert(current == nullptr || !current->isDeepCrashHandler());
  // Guard against the race window between Profiler::registerThread() and
  // thread_native_entry setting JVM TLS (PROF-13072): skip at most one signal
  // per thread. Pure native threads (where JVMThread::current() is always null)
  // are allowed through once the one-shot window expires.
  if (current != nullptr && JVMThread::isInitialized() && JVMThread::current() == nullptr
      && current->inInitWindow()) {
    current->tickInitWindow();
    errno = saved_errno;
    return;
  }
  if (current != NULL) {
    current->noteCPUSample(Profiler::instance()->recordingEpoch());
    tid = current->tid();
  } else {
    tid = OS::threadId();
  }
  Shims::instance().setSighandlerTid(tid);

  ExecutionEvent event;
  event._execution_mode = getThreadExecutionMode();
  Profiler::instance()->recordSample(ucontext, _interval, tid, BCI_CPU, 0,
                                     &event);
  Shims::instance().setSighandlerTid(-1);
  // we need to avoid spoiling the value of errno (tsan report)
  errno = saved_errno;
}

#endif // __linux__
