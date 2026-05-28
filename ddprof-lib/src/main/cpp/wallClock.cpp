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
  // Wall-clock once-per-run filter (wallprecheck=true): emit exactly one
  // MethodSample at the first signal of a SLEEPING / CONDVAR_WAIT run on this
  // thread, suppress subsequent signals until the OS state leaves the skip set.
  // State lives on the JVM-process-stable ThreadFilter::Slot (not on ProfiledThread,
  // which is deleted on thread exit), so the wall-clock timer can safely read these
  // bits cross-thread for its fast-path skip without a use-after-free hazard.
  // The osThreadState read is HotSpot-only; on J9/Zing getOSThreadState() returns
  // UNKNOWN so the filter is a no-op (every signal falls through to emission, same
  // as wallprecheck=false).
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
          return;  // suppress emission — same blocked-state run, already armed
        }
        // First signal of this blocked-state run — arm the filter and emit.
        // Transitions within the skip set (e.g. SLEEPING → CONDVAR_WAIT) re-arm
        // because the state-equality check above gates suppression on identity.
        slot->markSampledThisRun(precheck_state);
      } else {
        // Out of the skip set: reset so the next blocked-state entry emits.
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
    auto collectThreads = [&](std::vector<ThreadEntry>& entries) {
      if (Profiler::instance()->threadFilter()->enabled()) {
        Profiler::instance()->threadFilter()->collectWithState(entries);
      } else {
        ThreadList *thread_list = OS::listThreads();
        while (thread_list->hasNext()) {
          int tid = thread_list->next();
          if (tid != OS::threadId()) {
            // No-filter mode: vm_thread and slot are both nullptr.
            // The wallprecheck fast path below gates on (vm_thread && slot) so it
            // simply degrades to "always send the signal" here, matching prior behavior.
            entries.push_back({tid, nullptr, nullptr});
          }
        }
        delete thread_list;
      }
    };

    auto sampleThreads = [&](ThreadEntry entry, int& num_failures, int& threads_already_exited,
                             int& permission_denied) {
      // Safety of dereferencing entry.vm_thread / entry.slot here relies on:
      //   1) collectWithState uses acquire loads when reading the filter slot, so once
      //      ThreadFilter::setVMThread(slot, nullptr) has been published the timer
      //      thread observes a null vm_thread for any *future* tick. The same applies
      //      to the slot pointer (set to nullptr in the no-filter path; never cleared
      //      in the filtered path because slots are JVM-lifetime stable).
      //   2) Assumed (HotSpot only): JavaThread objects are not freed when the OS thread
      //      exits; they remain valid until JVM shutdown. The JVMTI specification makes
      //      no such guarantee. If this assumption ever breaks, this site would need a
      //      hazard-pointer or epoch-based reclamation scheme.
      //   3) ThreadFilter::Slot instances live inside ChunkStorage arrays that are
      //      allocated on first use and never freed for the JVM-process lifetime, so
      //      a captured Slot* is dereferenceable forever. This is the lifetime
      //      guarantee that makes the cross-thread once-per-run read below safe.
      //      ProfiledThread* is deliberately absent from ThreadEntry — its lifetime
      //      ends at ProfiledThread::release() and dereferencing it here would be
      //      a use-after-free.
      //
      // Wall-clock once-per-run filter — timer-thread fast path (wallprecheck=true):
      // elide pthread_kill / kernel IPI when the candidate is already in a blocked-state
      // run we have armed a sample for. Mirrors the handler-side filter (which still runs
      // as the authoritative correctness check for any signal that reaches it — covers the
      // race window where the state read here was stale or the worker's run transitioned
      // between this peek and signal delivery). The "already armed" bit is written by the
      // handler on the owning thread with release ordering; the timer reads it with
      // acquire ordering, fencing the subsequent relaxed read of the paired state.
      if (_precheck && entry.vm_thread != nullptr && entry.slot != nullptr) {
        OSThreadState peek_state = entry.vm_thread->osThreadState();
        if (peek_state == OSThreadState::SLEEPING || peek_state == OSThreadState::CONDVAR_WAIT) {
          // Read order matters: sampledThisRun() (acquire) must come first so the
          // && short-circuit fences the subsequent relaxed load of lastSampledState().
          if (entry.slot->sampledThisRun() &&
              peek_state == entry.slot->lastSampledState()) {
            Counters::increment(WC_SIGNAL_SUPPRESSED_SAMPLED_RUN);
            WallClockCounters::incrementSuppressedSampledRun();
            return false;  // intentional skip: no signal sent, not a failure but not a successful sample either
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
