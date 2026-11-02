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
#include "libraries.h"
#include "log.h"
#include "otel_context.h"
#include "profiler.h"
#include "signalCookie.h"
#include "signalInflight.h"
#include "threadState.inline.h"
#include "guards.h"
#include "wallClockCounters.h"
#include "samplerPerf.h"
#include <cassert>
#include <cerrno>
#include <string.h>
#include <math.h>
#include <algorithm> // For std::sort and std::binary_search

std::atomic<bool> BaseWallClock::_enabled{false};
#if defined(UNIT_TEST) || defined(DEBUG)
std::atomic<bool> BaseWallClock::_force_start_failure_for_test{false};
#endif

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
  // record->valid is not a context-presence bit. clearTraceContext0 leaves cleared
  // records invalid indefinitely, so gating on valid=1 disables wallprecheck for
  // the common no-context state after deactivation.
  return loadSpanId(record) != 0;
}

struct WallPrecheckResult {
  bool suppress = false;
  WallClockBlockTracker::BlockState* owned_block_slot = nullptr;
  u64 owned_block_generation = 0;
  OSThreadState observed_state = OSThreadState::UNKNOWN;
  bool observed_state_valid = false;
  WallClockBlockTracker::BlockState* unowned_weight_slot = nullptr;
  u64 unowned_weight = 1;
  bool flush_unowned_tail = false;
  WallClockBlockTracker::BlockState* unowned_tail_slot = nullptr;
  u64 flush_call_trace_id = 0;
  u64 flush_weight = 0;
  OSThreadState flush_state = OSThreadState::UNKNOWN;
};

static inline void incrementSuppressedOwnedBlock() {
  Counters::increment(WC_SIGNAL_SUPPRESSED_OWNED_BLOCK);
  WallClockCounters::incrementSuppressedOwnedBlock();
}

bool BaseWallClock::suppressAlreadySampled(const ThreadEntry& entry) {
  ThreadFilter* thread_filter = Profiler::instance()->threadFilter();
  WallClockBlockTracker* tracker = Profiler::instance()->blockTracker();
  if (tracker->isOwnedBlockSuppressionCandidate(thread_filter, entry)) {
    incrementSuppressedOwnedBlock();
    return true;
  }
  return false;
}

static inline WallPrecheckResult prepareWallPrecheck(
    ProfiledThread* current, bool precheck, bool unowned_fallback
#if defined(DEBUG) || defined(UNIT_TEST)
    , OSThreadState observed_state_for_test = OSThreadState::UNKNOWN
#endif
    ) {
  WallPrecheckResult result;
  if (current == nullptr || !precheck || hasKnownActiveTraceContext(current)) {
    return result;
  }

  ThreadFilter* registry = Profiler::instance()->threadFilter();
  ThreadFilter::SlotID slot_id = current->filterSlotId();
  ThreadFilter::Slot* slot = registry->activeSlotForId(slot_id, current->tid());

  if (slot == nullptr) {
    return result;
  }

  WallClockBlockTracker* tracker = Profiler::instance()->blockTracker();
  WallClockBlockTracker::BlockState* block_slot = tracker->slotForId(slot_id);
  if (block_slot == nullptr) {
    return result;
  }

  // Owned blocks replace repeated signals only after their current generation
  // has produced one MethodSample. Context-scoped profiling must continue
  // sampling its selected threads normally.
  if (!registry->unfilteredWallTrackingActive() || slot->inContextWindow()) {
    return result;
  }

  ThreadEntry entry{current->tid(), slot, slot_id, slot->lifecycleGeneration(),
                    slot->recordingEpoch()};
  u64 block_generation = 0;
  bool already_sampled = false;
  if (tracker->ownedBlockDecision(registry, entry, already_sampled,
                                  block_generation)) {
    if (already_sampled) {
      incrementSuppressedOwnedBlock();
      result.suppress = true;
      return result;
    }
    // Arm only after recordSample succeeds. A skipped JFR write must leave the
    // run eligible so the next signal retries instead of losing its only stack.
    result.owned_block_slot = block_slot;
    result.owned_block_generation = block_generation;
    return result;
  }
  // Delegated samples have no reusable local trace ID for replaying a weighted
  // tail. Bypass only the unowned fallback when the engine cannot emit it.
  if (!unowned_fallback || !block_slot->unownedBlockedFallbackEnabled()) {
    return result;
  }

#if defined(DEBUG) || defined(UNIT_TEST)
  result.observed_state = observed_state_for_test != OSThreadState::UNKNOWN
      ? observed_state_for_test : getOSThreadState();
#else
  result.observed_state = getOSThreadState();
#endif
  result.observed_state_valid = true;
  if (isPrecheckSuppressionState(result.observed_state)) {
    if (!block_slot->shouldRecordUnownedBlockedSample()) {
      Counters::increment(WC_UNOWNED_BLOCKED_SUPPRESSED);
      result.suppress = true;
      return result;
    }
    result.unowned_weight_slot = block_slot;
    result.unowned_weight = block_slot->consumeUnownedBlockedWeight();
  } else {
    result.flush_unowned_tail = block_slot->prepareUnownedBlockedTail(
        result.flush_call_trace_id, result.flush_weight, result.flush_state);
    if (result.flush_unowned_tail) result.unowned_tail_slot = block_slot;
  }
  return result;
}

static inline void finishWallPrecheck(const WallPrecheckResult& precheck,
                                      bool recorded) {
  if (recorded && precheck.owned_block_slot != nullptr) {
    precheck.owned_block_slot->markBlockGenerationSampled(
        precheck.owned_block_generation);
  }
  if (!recorded && precheck.unowned_weight_slot != nullptr) {
    precheck.unowned_weight_slot->restoreUnownedBlockedWeight(
        precheck.unowned_weight);
  } else if (recorded && precheck.unowned_weight_slot != nullptr) {
    Counters::increment(WC_UNOWNED_BLOCKED_RECORDED);
  }
}

#ifdef UNIT_TEST
bool BaseWallClock::wallPrecheckForTest(
    ProfiledThread* current, bool unowned_fallback, OSThreadState observed_state,
    u64& weight, bool recorded) {
  WallPrecheckResult result =
      prepareWallPrecheck(current, true, unowned_fallback, observed_state);
  weight = result.unowned_weight;
  finishWallPrecheck(result, recorded);
  return result.suppress;
}
#endif

static inline void emitUnownedBlockedTailForWallPrecheck(
    int tid, const WallPrecheckResult& precheck) {
  if (!precheck.flush_unowned_tail || precheck.flush_call_trace_id == 0) {
    return;
  }

  Profiler::instance()->recordUnownedBlockedTail(
      tid, precheck.unowned_tail_slot, precheck.flush_weight);
}

#ifdef DEBUG
// Only the synchronous JNI test driver supplies this argument. It inserts a
// real dump at a boundary outside the profiler stripe locks, without waiting
// inside a signal handler or adding hooks to release builds.
struct WallPrecheckDumpTest {
  jthread thread;
  const char* path;
  int path_length;
  bool before_publication;
  bool reset_before_tail;
  Error error = Error::OK;

  void dumpAtBoundary(bool publication) {
    if (publication == before_publication) {
      error = Profiler::instance()->dump(path, path_length);
    }
  }
};

static inline bool recordAsgctWallSample(
    void* ucontext, u64 counter, int tid, u64 call_trace_id,
    ExecutionEvent* event, const WallPrecheckResult& precheck,
    WallPrecheckDumpTest* dump_test = nullptr) {
  if (dump_test != nullptr) {
    if (precheck.flush_unowned_tail) dump_test->dumpAtBoundary(false);
    if (precheck.flush_unowned_tail && dump_test->reset_before_tail) {
      precheck.unowned_tail_slot->resetUnownedBlockedSampling();
    }
    // A synchronous JNI driver has no signal ucontext. Capture a real Java
    // stack through JVMTI, then use recordSample's existing trace-reuse path.
    call_trace_id = Profiler::instance()->recordJVMTISample(
        counter, tid, dump_test->thread, BCI_WALL, event, true);
    if (call_trace_id == 0) return false;
  }
  bool recorded = Profiler::instance()->recordWallSample(
      ucontext, counter, tid, call_trace_id, event, precheck.unowned_weight_slot);
  if (dump_test != nullptr && recorded && precheck.unowned_weight_slot != nullptr) {
    dump_test->dumpAtBoundary(true);
  }
  finishWallPrecheck(precheck, recorded);
  emitUnownedBlockedTailForWallPrecheck(tid, precheck);
  return recorded;
}

bool BaseWallClock::recordUnownedWallTailAcrossDumpForTest(
    jthread thread, const char* path, int path_length, bool before_publication,
    bool reset_before_tail) {
  SignalBlocker blocker;
  Profiler* profiler = Profiler::instance();
  ProfiledThread* current = ProfiledThread::initCurrentThreadSignalSafe();
  ThreadFilter* registry = profiler->threadFilter();
  if (current == nullptr || !profiler->isRunning() ||
      !registry->unfilteredWallTrackingActive()) return false;
  ThreadFilter::SlotID slot_id = registry->ensureCurrentThreadSlot(current);
  WallClockBlockTracker::BlockState* slot = profiler->blockTracker()->slotForId(slot_id);
  if (slot == nullptr || slot->activeBlockOwner() != BlockRunOwner::NONE) return false;
  slot->resetUnownedBlockedSampling();

  WallPrecheckDumpTest dump_test{thread, path, path_length, before_publication, reset_before_tail};
  ExecutionEvent event;
  event._thread_state = OSThreadState::SLEEPING;
  event._execution_mode = ExecutionMode::JAVA;
  WallPrecheckResult first = prepareWallPrecheck(current, true, true, OSThreadState::SLEEPING);
  if (first.suppress || first.unowned_weight_slot != slot) return false;
  if (!recordAsgctWallSample(nullptr, 1, current->tid(), 0, &event, first, &dump_test) ||
      dump_test.error) return false;

  // One further blocked observation contributes exactly one pending unit.
  if (!prepareWallPrecheck(current, true, true, OSThreadState::SLEEPING).suppress) return false;
  WallPrecheckResult tail = prepareWallPrecheck(current, true, true, OSThreadState::RUNNABLE);
  if (!tail.flush_unowned_tail || tail.flush_weight != 1) return false;
  event._thread_state = OSThreadState::RUNNABLE;
  return recordAsgctWallSample(nullptr, 1, current->tid(), 0, &event, tail, &dump_test) &&
      !dump_test.error;
}
#endif

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
  ErrnoPreserver errno_preserver;
  // Reject any SIGVTALRM that did not originate from our rt_tgsigqueueinfo
  // send. Defends against stray in-process tgkill / external sigqueue that
  // would otherwise drive our wallclock sampling path.
  if (!OS::shouldProcessSignal(siginfo, SI_QUEUE, SignalCookie::wallclock())) {
    Counters::increment(WALLCLOCK_SIGNAL_FOREIGN);
    OS::forwardForeignSignal(signo, siginfo, ucontext);
    return;
  }
  Counters::increment(WALLCLOCK_SIGNAL_OWN);

  // One signal delivery is one sample attempt for this thread; the reservoir
  // that decides which threads to signal runs in the timer thread
  // (BaseWallClock::timerLoopCommon), not here. So this handler -- not the
  // inner signalHandler() it calls -- is the per-sample unit, mirroring CPU.
  // Declared past the origin check so stray SIGVTALRM is not timed as our work.
  SAMPLER_PERF_PROBE(SP_WALL);

  SIGNAL_HANDLER_GUARD_OR_DROP();

  WallClockASGCT *engine = reinterpret_cast<WallClockASGCT *>(Profiler::instance()->wallEngine());
  // Past the foreign-signal filter: any work below this point can write JFR.
  // Participate in SignalInflight::drain() so Profiler::stop() does not tear
  // down JFR while this handler is still inside recordSample().
  InflightGuard inflight;
  if (!BaseWallClock::eventsEnabled()) {
    return;
  }
  if (signo == SIGVTALRM) {
    engine->signalHandler(signo, siginfo, ucontext, engine->_interval, SIGNAL_HANDLER_CURRENT_THREAD());
  }
}

void WallClockASGCT::signalHandler(int signo, siginfo_t *siginfo, void *ucontext,
                              u64 last_sample, ProfiledThread* current) {
  assert(current != nullptr);
  // Atomically try to enter critical section - prevents all reentrancy races
  CriticalSection cs(current);
  if (!cs.entered()) {
    return;  // Another critical section is active, defer profiling
  }
  if (tickInitWindowIfNeeded(current)) {
    return;
  }
  // Once-per-run filter (wallprecheck=true): an explicitly owned block keeps
  // its first successful MethodSample and suppresses subsequent signals.
  // Unowned blocked observations use weighted fallback sampling because raw OS
  // state cannot distinguish one long sleep from several shorter runs.
  WallPrecheckResult precheck = prepareWallPrecheck(current, _precheck, true);
  if (precheck.suppress) {
    return;
  }
  int tid = current->tid();

  {
    SighandlerTidScope sighandler_tid(tid);
    u64 call_trace_id = 0;
    if (_collapsing) {
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
#ifdef DEBUG
    recordAsgctWallSample(ucontext, last_sample, tid, call_trace_id, &event, precheck);
#else
    bool recorded = Profiler::instance()->recordWallSample(
        ucontext, last_sample, tid, call_trace_id, &event, precheck.unowned_weight_slot);
    finishWallPrecheck(precheck, recorded);
    emitUnownedBlockedTailForWallPrecheck(tid, precheck);
#endif
  }
}

Error BaseWallClock::start(Arguments &args) {
#if defined(UNIT_TEST) || defined(DEBUG)
  if (_force_start_failure_for_test.load(std::memory_order_acquire)) {
    return Error("Forced wall engine start failure (unit test)");
  }
#endif
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
  // start() can return before pthread_create() runs (e.g. the forced-failure
  // test hook, or pthread_create() itself failing), leaving _thread at its
  // constructor sentinel of 0. Profiler::stop() only reaches this call when
  // start() actually activated the wall engine, but this guard is kept as
  // defense-in-depth for any other caller of stop() on a never-started
  // instance. Skipping it crashes on musl when _thread is still 0 (observed);
  // glibc tolerates a zero pthread_t here, musl does not.
  if (_thread == 0) {
#ifdef DEBUG
    Counters::increment(CounterId::WALL_STOP_WHILE_NOT_ACTIVATED);
#endif
    return;
  }
  // the thread join ensures we wait for the thread to finish before returning
  // (and possibly removing the object)
  pthread_kill(_thread, WAKEUP_SIGNAL);
  int res = pthread_join(_thread, NULL);
  if (res != 0) {
    Log::warn("Unable to join WallClock thread on stop %d", res);
  }
  _thread = 0;
}

bool BaseWallClock::isEnabled() const {
  return _enabled.load(std::memory_order_acquire);
}

WallClockCandidateOutcome BaseWallClock::sampleThreadCommon(
    ThreadEntry entry, int& num_failures, int& threads_already_exited,
    int& permission_denied, int& registry_lookups, bool lookup_registry_slot,
    bool precheck, ThreadFilter* thread_filter,
    ThreadFilter::RecordingEpoch recording_epoch) {
  if (lookup_registry_slot && entry.slot == nullptr) {
    registry_lookups++;
    thread_filter->lookupThreadEntry(entry, recording_epoch);
  }
  // Missing entries, including capacity rejections, stay eligible for ordinary
  // sampling. Registry admission is only a precheck optimization in unfiltered mode.
  // Timer-thread fast path (wallprecheck=true): skip the kernel IPI entirely
  // only when an explicit lifecycle hook still owns an already-sampled blocked
  // run. Raw OS thread state is intentionally not used here because the timer
  // thread cannot prove run boundaries for the target thread.
  if (precheck && suppressAlreadySampled(entry)) {
    return WallClockCandidateOutcome::PRECHECK_REJECTED;
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
    return WallClockCandidateOutcome::SIGNAL_FAILED;
  }
  return WallClockCandidateOutcome::SIGNAL_SENT;
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
    ThreadFilter* thread_filter = Profiler::instance()->threadFilter();
    const bool lazy_backfill =
        _precheck && thread_filter->unfilteredWallTrackingActive();
    const ThreadFilter::RecordingEpoch recording_epoch =
        lazy_backfill ? thread_filter->recordingEpoch() : 0;
    auto collectThreads = [&](std::vector<ThreadEntry>& entries) {
      // Get thread IDs from the filter if it's enabled
      // Otherwise list all threads in the system
      if (thread_filter->enabled()) {
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
            entries.push_back({tid, nullptr, -1, 0, 0});
          }
        }
        delete thread_list;
      }
    };

    auto sampleThreads = [&](ThreadEntry entry, int& num_failures,
                             int& threads_already_exited, int& permission_denied,
                             int& registry_lookups, bool lookup_registry_slot) {
      return sampleThreadCommon(entry, num_failures, threads_already_exited,
                                 permission_denied, registry_lookups,
                                 lookup_registry_slot, _precheck, thread_filter,
                                 recording_epoch);
    };

    auto doNothing = []() {
    };

    timerLoopCommon<ThreadEntry>(collectThreads, sampleThreads, doNothing,
                                 _reservoir_size, _interval, _precheck,
                                 lazy_backfill);
}

// WallClockJvmti: mirrors WallClockASGCT's dispatch, but the signal handler
// delegates the stack walk to HotSpot's JFR RequestStackTrace JVMTI extension
// instead of invoking ASGCT. Used only when VM::canRequestStackTrace() is true
// and the profiler has opted into jvmtistacks.

void WallClockJvmti::sharedSignalHandler(int signo, siginfo_t *siginfo,
                                         void *ucontext) {
  ErrnoPreserver errno_preserver;
  // Reject any SIGVTALRM that did not originate from our rt_tgsigqueueinfo
  // send (mirrors WallClockASGCT). Defends against stray in-process tgkill or
  // external sigqueue driving the JVMTI RequestStackTrace path.
  if (!OS::shouldProcessSignal(siginfo, SI_QUEUE, SignalCookie::wallclock())) {
    Counters::increment(WALLCLOCK_SIGNAL_FOREIGN);
    OS::forwardForeignSignal(signo, siginfo, ucontext);
    return;
  }
  Counters::increment(WALLCLOCK_SIGNAL_OWN);
  // Per-sample unit for this engine; see WallClockASGCT::sharedSignalHandler.
  SAMPLER_PERF_PROBE(SP_WALL);
  SIGNAL_HANDLER_GUARD_OR_DROP();

  WallClockJvmti *engine =
      reinterpret_cast<WallClockJvmti *>(Profiler::instance()->wallEngine());
  // Past the foreign-signal filter: any work below this point can write JFR.
  // Participate in SignalInflight::drain() so Profiler::stop() does not tear
  // down JFR while this handler is still inside recordSampleDelegated().
  InflightGuard inflight;
  if (!BaseWallClock::eventsEnabled()) {
    return;
  }
  if (signo == SIGVTALRM) {
    engine->signalHandler(signo, siginfo, ucontext, engine->_interval, SIGNAL_HANDLER_CURRENT_THREAD());
  }
}

void WallClockJvmti::signalHandler(int signo, siginfo_t *siginfo,
                                   void *ucontext, u64 last_sample,
                                   ProfiledThread* current) {
  assert(current != nullptr);
  CriticalSection cs(current);
  if (!cs.entered()) {
    return;
  }

  if (tickInitWindowIfNeeded(current)) {
    return;
  }

  WallPrecheckResult precheck = prepareWallPrecheck(current, _precheck, false);
  if (precheck.suppress) {
    return;
  }
  int tid = current->tid();

  {
    SighandlerTidScope sighandler_tid(tid);
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
    // Unowned observations retain unit weight: this engine cannot replay a
    // cached blocked stack to account for suppressed tail observations.
    bool recorded = Profiler::instance()->recordSampleDelegated(
        nullptr, last_sample, tid, BCI_WALL, &event);
    finishWallPrecheck(precheck, recorded);
  }
}

void WallClockJvmti::initialize(Arguments &args) {
  // Caller must have verified VM::canRequestStackTrace() before selecting
  // this engine; see Profiler::selectWallEngine().
  _precheck = args._wall_precheck;
  OS::primeSignalOriginCheck();
  OS::installSignalHandler(SIGVTALRM, sharedSignalHandler);
}

void WallClockJvmti::timerLoop() {
  ThreadFilter* thread_filter = Profiler::instance()->threadFilter();
  const bool lazy_backfill =
      _precheck && thread_filter->unfilteredWallTrackingActive();
  const ThreadFilter::RecordingEpoch recording_epoch =
      lazy_backfill ? thread_filter->recordingEpoch() : 0;
  auto collectThreads = [&](std::vector<ThreadEntry> &entries) {
    const int refresher_tid = Libraries::instance()->refresherTid();
    if (thread_filter->enabled()) {
      Profiler::instance()->threadFilter()->collect(entries);
    } else {
      ThreadList *thread_list = OS::listThreads();
      while (thread_list->hasNext()) {
        int tid = thread_list->next();
        // Exclude the wallclock timer thread itself and the Libraries
        // refresher (profiler-internal).
        if (tid != OS::threadId() && tid != refresher_tid) {
          entries.push_back({tid, nullptr, -1, 0, 0});
        }
      }
      delete thread_list;
    }
  };

  auto sampleThreads = [&](ThreadEntry entry, int &num_failures,
                           int &threads_already_exited, int &permission_denied,
                           int &registry_lookups, bool lookup_registry_slot) {
    return sampleThreadCommon(entry, num_failures, threads_already_exited,
                               permission_denied, registry_lookups,
                               lookup_registry_slot, _precheck, thread_filter,
                               recording_epoch);
  };

  auto doNothing = []() {};

  timerLoopCommon<ThreadEntry>(collectThreads, sampleThreads, doNothing,
                               _reservoir_size, _interval, _precheck,
                               lazy_backfill);
}
