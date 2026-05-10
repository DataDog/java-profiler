/*
 * Copyright The async-profiler authors
 * Copyright 2025, 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "wallClock.h"

#include "counters.h"
#include "stackFrame.h"
#include "context.h"
#include "context_api.h"
#include "debugSupport.h"
#include "jvmThread.h"
#include "libraries.h"
#include "log.h"
#include "profiler.h"
#include "signalCookie.h"
#include "thread.h"
#include "threadState.inline.h"
#include "guards.h"
#include <cerrno>
#include <string.h>
#include <math.h>
#include <random>
#include <algorithm> // For std::sort and std::binary_search

std::atomic<bool> BaseWallClock::_enabled{false};

bool WallClockASGCT::inSyscall(void *ucontext) {
  StackFrame frame(ucontext);
  uintptr_t pc = frame.pc();

  // Consider a thread sleeping, if it has been interrupted in the middle of
  // syscall execution, either when PC points to the syscall instruction, or if
  // syscall has just returned with EINTR
  if (StackFrame::isSyscall((instruction_t *)pc)) {
    return true;
  }

  // Make sure the previous instruction address is readable
  uintptr_t prev_pc = pc - SYSCALL_SIZE;
  if ((pc & 0xfff) >= SYSCALL_SIZE ||
      Libraries::instance()->findLibraryByAddress((instruction_t *)prev_pc) !=
          NULL) {
    if (StackFrame::isSyscall((instruction_t *)prev_pc) &&
        frame.checkInterruptedSyscall()) {
      return true;
    }
  }

  return false;
}

void WallClockASGCT::sharedSignalHandler(int signo, siginfo_t *siginfo,
                                    void *ucontext) {
  // Reject any SIGVTALRM that did not originate from our rt_tgsigqueueinfo
  // send. Defends against stray in-process tgkill / external sigqueue that
  // would otherwise drive our wallclock sampling path.
  if (!OS::shouldProcessSignal(siginfo, SI_QUEUE, SignalCookie::wallclock())) {
    Counters::increment(WALLCLOCK_SIGNAL_FOREIGN);
    OS::forwardForeignSignal(signo, siginfo, ucontext);
    return;
  }
  Counters::increment(WALLCLOCK_SIGNAL_OWN);

  WallClockASGCT *engine = reinterpret_cast<WallClockASGCT *>(Profiler::instance()->wallEngine());
  if (signo == SIGVTALRM) {
    engine->signalHandler(signo, siginfo, ucontext, engine->_interval);
  }
}

void WallClockASGCT::signalHandler(int signo, siginfo_t *siginfo, void *ucontext,
                              u64 last_sample) {
  // Atomically try to enter critical section - prevents all reentrancy races
  CriticalSection cs;
  if (!cs.entered()) {
    return;  // Another critical section is active, defer profiling
  }
  ProfiledThread *current = ProfiledThread::currentSignalSafe();
  // Guard against the race window between Profiler::registerThread() and
  // thread_native_entry setting JVM TLS (PROF-13072): skip at most one signal
  // per thread. Pure native threads (where JVMThread::current() is always null)
  // are allowed through once the one-shot window expires.
  if (current != nullptr && JVMThread::isInitialized() && JVMThread::current() == nullptr
      && current->inInitWindow()) {
    current->tickInitWindow();
    return;
  }
  int tid = current != NULL ? current->tid() : OS::threadId();
  Shims::instance().setSighandlerTid(tid);
  u64 call_trace_id = 0;
  if (current != NULL && _collapsing) {
    StackFrame frame(ucontext);
    u64 spanId = 0, rootSpanId = 0;
    // contextValid is not redundant with (spanId==0 && rootSpanId==0): a cleared
    // context has spanId=0 and contextValid=true, while an uninitialized/mid-write
    // thread has spanId=0 and contextValid=false. lookupWallclockCallTraceId uses
    // contextValid to decide whether to update the sidecar _otel_local_root_span_id.
    bool contextValid = ContextApi::get(spanId, rootSpanId);
    call_trace_id = current->lookupWallclockCallTraceId(
        (u64)frame.pc(), (u64)frame.sp(),
        Profiler::instance()->recordingEpoch(),
        contextValid, spanId, rootSpanId);
    if (call_trace_id != 0) {
      Counters::increment(SKIPPED_WALLCLOCK_UNWINDS);
    }
  }

  ExecutionEvent event;
  OSThreadState state = getOSThreadState();
  ExecutionMode mode = getThreadExecutionMode();
  if (state == OSThreadState::UNKNOWN) {
    if (inSyscall(ucontext)) {
      state = OSThreadState::SYSCALL;
      mode = ExecutionMode::SYSCALL;
    } else {
      state = OSThreadState::RUNNABLE;
    }
  }
  event._thread_state = state;
  event._execution_mode = mode;
  event._weight = 1;
  Profiler::instance()->recordSample(ucontext, last_sample, tid, BCI_WALL,
                                     call_trace_id, &event);
  Shims::instance().setSighandlerTid(-1);
}

Error BaseWallClock::start(Arguments &args) {
  int interval = args._event != NULL ? args._interval : args._wall;
  if (interval < 0) {
    return Error("interval must be positive");
  }
  _interval = interval ? interval : DEFAULT_WALL_INTERVAL;

  _reservoir_size =
            args._wall_threads_per_tick ?
            args._wall_threads_per_tick : DEFAULT_WALL_THREADS_PER_TICK;

  initialize(args);

  _running = true;

  if (pthread_create(&_thread, NULL, threadEntry, this) != 0) {
    return Error("Unable to create timer thread");
  }

  return Error::OK;
}

void BaseWallClock::stop() {
  _running.store(false);
  // the thread join ensures we wait for the thread to finish before returning
  // (and possibly removing the object)
  pthread_kill(_thread, WAKEUP_SIGNAL);
  int res = pthread_join(_thread, NULL);
  if (res != 0) {
    Log::warn("Unable to join WallClock thread on stop %d", res);
  }
}

bool BaseWallClock::isEnabled() const {
  return _enabled.load(std::memory_order_acquire);
}

void WallClockASGCT::initialize(Arguments& args) {
  _collapsing = args._wall_collapsing;
  // J9WallClock uses JVMTI GetAllStackTracesExtended polling, not SIGVTALRM
  // signals — it has no sharedSignalHandler and needs no signal-origin gate.
  // Engines are started sequentially; this call is idempotent (no-op after first).
  OS::primeSignalOriginCheck();
  OS::installSignalHandler(SIGVTALRM, sharedSignalHandler);
}

void WallClockASGCT::timerLoop() {
    // todo: re-allocating the vector every time is not efficient
    auto collectThreads = [&](std::vector<int>& tids) {
      // Get thread IDs from the filter if it's enabled
      // Otherwise list all threads in the system
      if (Profiler::instance()->threadFilter()->enabled()) {
        Profiler::instance()->threadFilter()->collect(tids);
      } else {
        ThreadList *thread_list = OS::listThreads();
        while (thread_list->hasNext()) {
          int tid = thread_list->next();
          // Don't include the current thread
          if (tid != OS::threadId()) {
            tids.push_back(tid);
          }
        }
        delete thread_list;
      }
    };

    auto sampleThreads = [&](int tid, int& num_failures, int& threads_already_exited, int& permission_denied) {
      // Deliver SIGVTALRM with a cookie so our handler can distinguish this
      // signal from any other in-process sender (see signalCookie.h /
      // wallClock.cpp sharedSignalHandler).
      if (!OS::sendSignalWithCookie(tid, SIGVTALRM, SignalCookie::wallclock())) {
        num_failures++;
        if (errno != 0) {
          if (errno == ESRCH) {
              threads_already_exited++;
          } else if (errno == EPERM) {
              permission_denied++;
          } else if (errno == EAGAIN) {
              // Signal queue limit (RLIMIT_SIGPENDING) reached; signal was not
              // delivered — count as missed sample.
          } else {
              Log::debug("unexpected error %s", strerror(errno));
          }
        }
        return false;
      }
      return true;
    };

    auto doNothing = []() {
    };

    timerLoopCommon<int>(collectThreads, sampleThreads, doNothing, _reservoir_size, _interval);
}
