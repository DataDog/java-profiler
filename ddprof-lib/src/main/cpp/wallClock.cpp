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
#include "otel_context.h"
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

static inline bool isPrecheckSuppressionState(OSThreadState state) {
  return state == OSThreadState::SLEEPING ||
         state == OSThreadState::CONDVAR_WAIT ||
         state == OSThreadState::OBJECT_WAIT ||
         state == OSThreadState::MONITOR_WAIT;
}

static inline u64 loadSpanId(OtelThreadContextRecord* record) {
  u64 span_id = 0;
  for (int i = 0; i < 8; i++) {
    span_id = (span_id << 8) |
              __atomic_load_n(&record->span_id[i], __ATOMIC_RELAXED);
  }
  return span_id;
}

static inline bool hasKnownActiveTraceContext(ProfiledThread* thread) {
  if (thread == nullptr || !thread->isContextInitialized()) {
    return false;
  }

  OtelThreadContextRecord* record = thread->getOtelContextRecord();
  // record->valid is not a context-presence bit. ThreadContext leaves cleared
  // records invalid indefinitely, so gating on valid=1 disables wallprecheck for
  // the common no-context state after a Java ThreadLocal reset.
  return loadSpanId(record) != 0;
}

struct WallPrecheckResult {
  bool suppress = false;
  ThreadFilter::Slot* slot_to_arm = nullptr;
  OSThreadState state_to_arm = OSThreadState::UNKNOWN;
  OSThreadState observed_state = OSThreadState::UNKNOWN;
  bool observed_state_valid = false;
  ThreadFilter::Slot* unowned_weight_slot = nullptr;
  u64 unowned_weight = 1;
  bool flush_unowned_tail = false;
  u64 flush_call_trace_id = 0;
  u64 flush_weight = 0;
  OSThreadState flush_state = OSThreadState::UNKNOWN;
};

static inline void incrementSuppressedSampledRun() {
  Counters::increment(WC_SIGNAL_SUPPRESSED_SAMPLED_RUN);
  WallClockCounters::incrementSuppressedSampledRun();
}

static inline bool suppressAlreadySampledBlock(ThreadFilter::Slot* slot) {
  if (slot == nullptr) {
    return false;
  }
  OSThreadState block_state = slot->activeBlockState();
  if (slot->activeBlockOwner() != BlockRunOwner::NONE &&
      isPrecheckSuppressionState(block_state) &&
      slot->sampledThisRun() &&
      block_state == slot->lastSampledState()) {
    incrementSuppressedSampledRun();
    return true;
  }
  return false;
}

static inline WallPrecheckResult prepareWallPrecheck(ProfiledThread* current,
                                                     bool precheck) {
  WallPrecheckResult result;
  if (current == nullptr || !precheck || hasKnownActiveTraceContext(current)) {
    return result;
  }

  ThreadFilter::Slot* slot =
      Profiler::instance()->threadFilter()->slotForId(current->filterSlotId());
  if (slot == nullptr) {
    return result;
  }

  OSThreadState active_block_state = slot->activeBlockState();
  BlockRunOwner active_block_owner = slot->activeBlockOwner();
  bool has_owned_block =
      active_block_owner != BlockRunOwner::NONE &&
      isPrecheckSuppressionState(active_block_state);
  if (has_owned_block) {
    if (slot->sampledThisRun() &&
        active_block_state == slot->lastSampledState()) {
      incrementSuppressedSampledRun();
      result.suppress = true;
      return result;
    }
    // Arm only after the MethodSample has been successfully recorded. If the
    // JFR write is skipped due to lock contention, the next signal must retry
    // instead of losing the only stack for this blocked run.
    result.slot_to_arm = slot;
    result.state_to_arm = active_block_state;
    return result;
  }

  result.observed_state = getOSThreadState();
  result.observed_state_valid = true;
  if (isPrecheckSuppressionState(result.observed_state)) {
    if (!slot->shouldRecordUnownedBlockedSample()) {
      Counters::increment(WC_UNOWNED_BLOCKED_SUPPRESSED);
      result.suppress = true;
      return result;
    }
    result.unowned_weight_slot = slot;
    result.unowned_weight = slot->consumeUnownedBlockedWeight();
  } else {
    result.flush_unowned_tail = slot->flushUnownedBlockedTail(
        result.flush_call_trace_id, result.flush_weight, result.flush_state);
  }
  return result;
}

static inline void finishWallPrecheck(const WallPrecheckResult& precheck,
                                      bool recorded,
                                      u64 recorded_call_trace_id = 0) {
  if (!recorded && precheck.unowned_weight_slot != nullptr) {
    precheck.unowned_weight_slot->restoreUnownedBlockedWeight(
        precheck.unowned_weight);
  } else if (recorded && precheck.unowned_weight_slot != nullptr) {
    Counters::increment(WC_UNOWNED_BLOCKED_RECORDED);
    if (recorded_call_trace_id != 0) {
      precheck.unowned_weight_slot->recordUnownedBlockedSample(
          recorded_call_trace_id, precheck.observed_state);
    }
  }
  if (recorded && precheck.slot_to_arm != nullptr) {
    precheck.slot_to_arm->markSampledThisRun(precheck.state_to_arm, sample_id);
  }
}

static inline void recordDeferredWallSample(int tid, u64 call_trace_id,
                                            ExecutionEvent* event) {
  Profiler::instance()->recordDeferredSample(tid, call_trace_id, BCI_WALL, event);
}

static inline void emitUnownedBlockedTailForWallPrecheck(
    int tid, const WallPrecheckResult& precheck) {
  if (!precheck.flush_unowned_tail || precheck.flush_call_trace_id == 0) {
    return;
  }

  ExecutionEvent flush_event;
  flush_event._thread_state = precheck.flush_state;
  flush_event._execution_mode = ExecutionMode::UNKNOWN;
  flush_event._weight = precheck.flush_weight;
  recordDeferredWallSample(tid, precheck.flush_call_trace_id, &flush_event);
}

static inline void recordDeferredWallSample(int tid, u64 call_trace_id,
                                            ExecutionEvent* event) {
  Profiler::instance()->recordDeferredSample(tid, call_trace_id, BCI_WALL, event);
}

static inline void emitUnownedBlockedTailForWallPrecheck(
    int tid, const WallPrecheckResult& precheck) {
  if (!precheck.flush_unowned_tail || precheck.flush_call_trace_id == 0) {
    return;
  }

  ExecutionEvent flush_event;
  flush_event._thread_state = precheck.flush_state;
  flush_event._execution_mode = ExecutionMode::UNKNOWN;
  flush_event._weight = precheck.flush_weight;
  recordDeferredWallSample(tid, precheck.flush_call_trace_id, &flush_event);
}

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
    SIGNAL_HANDLER_GUARD_RELEASE();
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
  // Once-per-run filter (wallprecheck=true): for untraced threads, exact
  // suppression is only valid while an explicit lifecycle hook owns the blocked
  // interval. Raw OS thread state is only an observation; it cannot distinguish
  // one long sleep from several short sleeps separated by runnable gaps between
  // signals. Unowned blocked observations therefore use weighted fallback
  // sampling instead of arming sampled_this_run.
  WallPrecheckResult precheck = prepareWallPrecheck(current, _precheck);
  if (precheck.suppress) {
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
  OSThreadState state =
      precheck.observed_state_valid ? precheck.observed_state : getOSThreadState();
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
  event._weight = precheck.unowned_weight;
  u64 recorded_call_trace_id = 0;
  bool recorded = Profiler::instance()->recordSample(ucontext, last_sample, tid,
                                                     BCI_WALL, call_trace_id,
                                                     &event,
                                                     &recorded_call_trace_id);
  finishWallPrecheck(precheck, recorded, recorded_call_trace_id);
  emitUnownedBlockedTailForWallPrecheck(tid, precheck);
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
        Profiler::instance()->threadFilter()->collect(entries);
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
            entries.push_back({tid, nullptr}); // no-filter: precheck fast path is skipped (null guards)
          }
        }
        delete thread_list;
      }
    };

    auto sampleThreads = [&](ThreadEntry entry, int& num_failures, int& threads_already_exited,
                             int& permission_denied) {
      // Timer-thread fast path (wallprecheck=true): skip the kernel IPI entirely
      // only when an explicit lifecycle hook still owns an already-sampled blocked
      // run. Raw OS thread state is intentionally not used here because the timer
      // thread cannot prove run boundaries for the target thread.
      if (_precheck && suppressAlreadySampledBlock(entry.slot)) {
        return false;
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
  // Reject any SIGVTALRM that did not originate from our rt_tgsigqueueinfo
  // send (mirrors WallClockASGCT). Defends against stray in-process tgkill or
  // external sigqueue driving the JVMTI RequestStackTrace path.
  if (!OS::shouldProcessSignal(siginfo, SI_QUEUE, SignalCookie::wallclock())) {
    Counters::increment(WALLCLOCK_SIGNAL_FOREIGN);
    SIGNAL_HANDLER_GUARD_RELEASE();
    OS::forwardForeignSignal(signo, siginfo, ucontext);
    return;
  }
  Counters::increment(WALLCLOCK_SIGNAL_OWN);

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
  WallPrecheckResult precheck = prepareWallPrecheck(current, _precheck);
  if (precheck.suppress) {
    errno = saved_errno;
    return;
  }
  int tid = current != NULL ? current->tid() : OS::threadId();
  Shims::instance().setSighandlerTid(tid);

  ExecutionEvent event;
  OSThreadState state =
      precheck.observed_state_valid ? precheck.observed_state : getOSThreadState();
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
  event._weight = precheck.unowned_weight;
  // Pass nullptr ucontext so the JVM uses safepoint-based stack walking.
  // Passing the signal-frame PC causes the extension to reject samples where
  // the thread is currently inside JVM-internal (non-Java) code.
  // JVMTI-delegated samples carry a correlation_id, not a call_trace_id, so
  // unowned tail flushing remains limited to the ASGCT wall engine.
  bool recorded = Profiler::instance()->recordSampleDelegated(
      nullptr, last_sample, tid, BCI_WALL, &event);
  finishWallPrecheck(precheck, recorded, event._sample_id);
  Shims::instance().setSighandlerTid(-1);
  errno = saved_errno;
}

void WallClockJvmti::initialize(Arguments &args) {
  // Caller must have verified VM::canRequestStackTrace() before selecting
  // this engine; see Profiler::selectWallEngine().
  _precheck = args._wall_precheck;
  OS::primeSignalOriginCheck();
  OS::installSignalHandler(SIGVTALRM, sharedSignalHandler);
}

void WallClockJvmti::timerLoop() {
  auto collectThreads = [&](std::vector<ThreadEntry> &entries) {
    const int refresher_tid = Libraries::instance()->refresherTid();
    if (Profiler::instance()->threadFilter()->enabled()) {
      Profiler::instance()->threadFilter()->collect(entries);
    } else {
      ThreadList *thread_list = OS::listThreads();
      while (thread_list->hasNext()) {
        int tid = thread_list->next();
        // Exclude the wallclock timer thread itself and the Libraries
        // refresher (profiler-internal).
        if (tid != OS::threadId() && tid != refresher_tid) {
          entries.push_back({tid, nullptr});
        }
      }
      delete thread_list;
    }
  };

  auto sampleThreads = [&](ThreadEntry entry, int &num_failures,
                           int &threads_already_exited, int &permission_denied) {
    if (_precheck && suppressAlreadySampledBlock(entry.slot)) {
      return false;
    }
    if (!OS::sendSignalWithCookie(entry.tid, SIGVTALRM, SignalCookie::wallclock())) {
      num_failures++;
      if (errno != 0) {
        if (errno == ESRCH) {
          threads_already_exited++;
        } else if (errno == EPERM) {
          permission_denied++;
        } else if (errno == EAGAIN) {
          // Signal queue limit (RLIMIT_SIGPENDING) reached — count as missed.
          Counters::increment(WC_SIGNAL_QUEUE_FULL);
        } else {
          Log::debug("unexpected error %s", strerror(errno));
        }
      }
      return false;
    }
    return true;
  };

  auto doNothing = []() {};

  timerLoopCommon<ThreadEntry>(collectThreads, sampleThreads, doNothing,
                               _reservoir_size, _interval);
}
