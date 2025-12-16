/*
 * Copyright 2018 Andrei Pangin
 * Copyright 2025, Datadog, Inc.
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

#include "itimer.h"
#include "debugSupport.h"
#include "os_dd.h"
#include "profiler.h"
#include "stackWalker.h"
#include "thread.h"
#include "vmStructs.h"
#include "criticalSection.h"
#include <sys/time.h>

volatile bool ITimer::_enabled = false;
long ITimer::_interval;
CStack ITimer::_cstack;

void ITimer::signalHandler(int signo, siginfo_t *siginfo, void *ucontext) {
  if (!_enabled)
    return;
  
  // Atomically try to enter critical section - prevents all reentrancy races
  CriticalSection cs;
  if (!cs.entered()) {
    return;  // Another critical section is active, defer profiling
  }
  int tid = 0;
  ProfiledThread *current = ProfiledThread::currentSignalSafe();
  if (current != NULL) {
    current->noteCPUSample(Profiler::instance()->recordingEpoch());
    tid = current->tid();
  } else {
    tid = OS::threadId();
  }
  Shims::instance().setSighandlerTid(tid);

  ExecutionEvent event;
  VMThread *vm_thread = VMThread::current();
  if (vm_thread) {
    // Check thread state to distinguish Java threads from JVM internal threads.
    // Java threads have states in [4, 12) range (_thread_in_native to _thread_max_state).
    // JVM internal threads (GC, Compiler) have state 0 or outside this range.
    //
    // We MUST NOT call VM::jni() here because it calls JavaVM->GetEnv(), which triggers
    // __tls_get_addr for thread-local JNIEnv lookup. If the signal interrupts during
    // TLS initialization (e.g., ForkJoinWorkerThread startup), this causes re-entrant
    // TLS allocation and heap corruption.
    //
    // Thread states defined in OpenJDK:
    // https://github.com/openjdk/jdk/blob/master/src/hotspot/share/utilities/globalDefinitions.hpp
    // Search for "enum JavaThreadState"
    int raw_thread_state = vm_thread->state();
    bool is_java_thread = raw_thread_state >= 4 && raw_thread_state < 12;
    event._execution_mode = is_java_thread
                                ? convertJvmExecutionState(raw_thread_state)
                                : ExecutionMode::JVM;
  }
  Profiler::instance()->recordSample(ucontext, _interval, tid, BCI_CPU, 0,
                                     &event);
  Shims::instance().setSighandlerTid(-1);
}

Error ITimer::check(Arguments &args) {
  OS::installSignalHandler(SIGPROF, NULL, SIG_IGN);

  struct itimerval tv_on = {{1, 0}, {1, 0}};
  if (setitimer(ITIMER_PROF, &tv_on, NULL) != 0) {
    return Error("ITIMER_PROF is not supported on this system");
  }

  struct itimerval tv_off = {{0, 0}, {0, 0}};
  setitimer(ITIMER_PROF, &tv_off, NULL);

  return Error::OK;
}

Error ITimer::start(Arguments &args) {
  _interval = args.cpuSamplerInterval();
  _cstack = args._cstack;

  OS::installSignalHandler(SIGPROF, signalHandler);

  time_t sec = _interval / 1000000000;
  suseconds_t usec = (_interval % 1000000000) / 1000;
  struct itimerval tv = {{sec, usec}, {sec, usec}};

  if (setitimer(ITIMER_PROF, &tv, NULL) != 0) {
    return Error("ITIMER_PROF is not supported on this system");
  }

  return Error::OK;
}

void ITimer::stop() {
  struct itimerval tv = {{0, 0}, {0, 0}};
  setitimer(ITIMER_PROF, &tv, NULL);
}
