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
#include "wallClockCounters.h"
#include <cerrno>
#include <string.h>
#include <math.h>
#include <random>
#include <algorithm> // For std::sort and std::binary_search

std::atomic<bool> BaseWallClock::_enabled{false};

bool BaseWallClock::inSyscall(void *ucontext) {
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
  SIGNAL_HANDLER_GUARD();
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
  // Once-per-run filter (wallprecheck=true): emit one MethodSample at the start of
  // a SLEEPING/CONDVAR_WAIT run, suppress subsequent signals until state changes.
  // On J9/Zing getOSThreadState() returns UNKNOWN, so every signal falls through.
  if (current != nullptr && _precheck) {
    ThreadFilter::Slot* slot =
        Profiler::instance()->threadFilter()->slotForId(current->filterSlotId());
    if (slot != nullptr) {
      OSThreadState precheck_state = getOSThreadState();
      bool is_blocked_skip_state = (precheck_state == OSThreadState::SLEEPING ||
                                    precheck_state == OSThreadState::CONDVAR_WAIT);
      if (is_blocked_skip_state) {
        if (slot->sampledThisRun() && precheck_state == slot->lastSampledState()) {
          Counters::increment(WC_SIGNAL_SUPPRESSED_SAMPLED_RUN);
          WallClockCounters::incrementSuppressedSampledRun();
          return;  // suppress: same blocked-state run, already sampled
        }
        slot->markSampledThisRun(precheck_state); // arm: first signal of this run
      } else if (!slot->inParkRun()) {
        // Only disarm when the thread is genuinely outside a park run. Transient
        // RUNNABLE states from SIGVTALRM-driven EINTR re-entry would otherwise
        // disarm the slot, causing the timer to re-send the next tick.
        slot->resetSampledRun(precheck_state);
      }
    }
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
  _precheck   = args._wall_precheck;
  // J9WallClock uses JVMTI GetAllStackTracesExtended polling, not SIGVTALRM
  // signals — it has no sharedSignalHandler and needs no signal-origin gate.
  // Engines are started sequentially; this call is idempotent (no-op after first).
  OS::primeSignalOriginCheck();
  OS::installSignalHandler(SIGVTALRM, sharedSignalHandler);
}

void WallClockASGCT::timerLoop() {
    // todo: re-allocating the vector every time is not efficient
    auto collectThreads = [&](std::vector<ThreadEntry>& entries) {
      // Get thread IDs from the filter if it's enabled
      // Otherwise list all threads in the system
      if (Profiler::instance()->threadFilter()->enabled()) {
        Profiler::instance()->threadFilter()->collectWithState(entries);
      } else {
        const int refresher_tid = Libraries::instance()->refresherTid();
        ThreadList *thread_list = OS::listThreads();
        while (thread_list->hasNext()) {
          int tid = thread_list->next();
          // Don't include the current thread, nor the Libraries refresher
          // thread (profiler-internal — masking SIGVTALRM there is not
          // enough; we also want to avoid the kill() round-trip and any
          // pending-signal accumulation).
          if (tid != OS::threadId() && tid != refresher_tid) {
            entries.push_back({tid, nullptr, nullptr}); // no-filter: precheck fast path is skipped (null guards)
            }
        }
        delete thread_list;
      }
    };

    auto sampleThreads = [&](ThreadEntry entry, int& num_failures, int& threads_already_exited,
                             int& permission_denied) {
      // Timer-thread fast path (wallprecheck=true): skip the kernel IPI entirely when
      // we already armed a sample for this blocked-state run. The signal handler's filter
      // is the authoritative check and still runs on any signal that gets through,
      // covering the race window where this peek was stale.
      // Assumption (HotSpot only): VMThread objects are not freed on thread exit and
      // remain valid until JVM shutdown. vm_thread is cleared to nullptr in remove()
      // before the slot is recycled, so a null check here is sufficient.
      if (_precheck && entry.vm_thread != nullptr && entry.slot != nullptr) {
        OSThreadState peek_state = entry.vm_thread->osThreadState();
        bool in_skip_state = (peek_state == OSThreadState::SLEEPING ||
          peek_state == OSThreadState::CONDVAR_WAIT);
          // Also suppress when the thread is transiently RUNNABLE between consecutive
          // pthread_cond_timedwait calls after SIGVTALRM-driven EINTR re-entry.
          // inParkRun() is set by parkEnter0 and cleared by parkExit0, so it remains
          // true for the entire logical park run including the brief RUNNABLE gaps.
        if ((in_skip_state || entry.slot->inParkRun()) && entry.slot->sampledThisRun()) {
          // For skip-set states, also verify the state hasn't changed (e.g. SLEEP→CONDVAR).
          if (!in_skip_state || peek_state == entry.slot->lastSampledState()) {
            Counters::increment(WC_SIGNAL_SUPPRESSED_SAMPLED_RUN);
            WallClockCounters::incrementSuppressedSampledRun();
            return false;
          }
        }
      }
      if (!OS::sendSignalWithCookie(entry.tid, SIGVTALRM, SignalCookie::wallclock())) {
        num_failures++;
        if (errno != 0) {
          if (errno == ESRCH) {
            threads_already_exited++;
          } else if (errno == EPERM) {
            permission_denied++;
          } else if (errno == EAGAIN) {
            // Signal queue limit (RLIMIT_SIGPENDING) reached; not a permission error.
            Counters::increment(WC_SIGNAL_QUEUE_FULL);
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

    timerLoopCommon<ThreadEntry>(collectThreads, sampleThreads, doNothing, _reservoir_size, _interval);
}

// WallClockJvmti: mirrors WallClockASGCT's dispatch, but the signal handler
// delegates the stack walk to HotSpot's JFR RequestStackTrace JVMTI extension
// instead of invoking ASGCT. Used only when VM::canRequestStackTrace() is true
// and the profiler has opted into jvmtistacks.

void WallClockJvmti::sharedSignalHandler(int signo, siginfo_t *siginfo,
                                         void *ucontext) {
  SIGNAL_HANDLER_GUARD();
  WallClockJvmti *engine =
      reinterpret_cast<WallClockJvmti *>(Profiler::instance()->wallEngine());
  if (signo == SIGVTALRM) {
    engine->signalHandler(signo, siginfo, ucontext, engine->_interval);
  }
}

void WallClockJvmti::signalHandler(int signo, siginfo_t *siginfo,
                                   void *ucontext, u64 last_sample) {
  CriticalSection cs;
  if (!cs.entered()) {
    return;
  }
  int saved_errno = errno;
  ProfiledThread *current = ProfiledThread::currentSignalSafe();
  if (current != nullptr && JVMThread::isInitialized() && JVMThread::current() == nullptr
      && current->inInitWindow()) {
    current->tickInitWindow();
    errno = saved_errno;
    return;
  }
  int tid = current != NULL ? current->tid() : OS::threadId();
  Shims::instance().setSighandlerTid(tid);

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
  // Pass nullptr ucontext so the JVM uses safepoint-based stack walking.
  // Passing the signal-frame PC causes the extension to reject samples where
  // the thread is currently inside JVM-internal (non-Java) code.
  Profiler::instance()->recordSampleDelegated(nullptr, last_sample, tid,
                                               BCI_WALL, &event);
  Shims::instance().setSighandlerTid(-1);
  errno = saved_errno;
}

void WallClockJvmti::initialize(Arguments &args) {
  // Caller must have verified VM::canRequestStackTrace() before selecting
  // this engine; see Profiler::selectWallEngine().
  OS::installSignalHandler(SIGVTALRM, sharedSignalHandler);
}

void WallClockJvmti::timerLoop() {
  auto collectThreads = [&](std::vector<int> &tids) {
    const int refresher_tid = Libraries::instance()->refresherTid();
    if (Profiler::instance()->threadFilter()->enabled()) {
      Profiler::instance()->threadFilter()->collect(tids);
    } else {
      ThreadList *thread_list = OS::listThreads();
      while (thread_list->hasNext()) {
        int tid = thread_list->next();
        // Exclude the wallclock timer thread itself and the Libraries
        // refresher (profiler-internal).
        if (tid != OS::threadId() && tid != refresher_tid) {
          tids.push_back(tid);
        }
      }
      delete thread_list;
    }
  };

  auto sampleThreads = [&](int tid, int &num_failures,
                           int &threads_already_exited, int &permission_denied) {
    if (!OS::sendSignalToThread(tid, SIGVTALRM)) {
      num_failures++;
      if (errno != 0) {
        if (errno == ESRCH) {
          threads_already_exited++;
        } else if (errno == EPERM) {
          permission_denied++;
        } else if (errno == EAGAIN) {
          // Signal queue limit (RLIMIT_SIGPENDING) reached — count as missed.
        } else {
          Log::debug("unexpected error %s", strerror(errno));
        }
      }
      return false;
    }
    return true;
  };

  auto doNothing = []() {};

  timerLoopCommon<int>(collectThreads, sampleThreads, doNothing,
                      _reservoir_size, _interval);
}
