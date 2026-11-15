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
#include "signalSafety.h"
#include "threadState.inline.h"
#include "guards.h"
#include "wallClockCounters.h"
#include "samplerPerf.h"
#include <cassert>
#include <cerrno>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm> // For std::sort and std::binary_search

std::atomic<bool> BaseWallClock::_enabled{false};
#ifdef UNIT_TEST
static std::atomic<BaseWallClock::ThreadStateReaderForTest> thread_state_reader_for_test{nullptr};
static BaseWallClock::UnownedContextProbeHook unowned_context_probe_hook = nullptr;
static void* unowned_context_probe_arg = nullptr;

void BaseWallClock::setUnownedContextProbeHookForTest(UnownedContextProbeHook hook, void* arg) {
  unowned_context_probe_hook = hook;
  unowned_context_probe_arg = arg;
}

BaseWallClock::ThreadStateReaderForTest BaseWallClock::exchangeThreadStateReaderForTest(
    ThreadStateReaderForTest reader) {
  return thread_state_reader_for_test.exchange(reader, std::memory_order_acq_rel);
}
#endif
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
  WallSampleRequest transaction;
  bool suppress = false;
  WallClockBlockTracker::BlockState* owned_block_slot = nullptr;
  u64 owned_block_generation = 0;
  OSThreadState observed_state = OSThreadState::UNKNOWN;
  bool observed_state_valid = false;
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
    ProfiledThread* current, bool precheck, bool transactional = false
#if defined(DEBUG) || defined(UNIT_TEST)
    , OSThreadState observed_state_for_test = OSThreadState::UNKNOWN
#endif
    ) {
  WallPrecheckResult result;
  result.transaction.tid = current != nullptr ? current->tid() : -1;
  result.transaction.trace_epoch = Profiler::instance()->recordingEpoch();
  result.transaction.sampling_epoch_start = WallClockCounters::samplingEpochStart();
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

  result.transaction.slot_id = slot_id;
  result.transaction.lifecycle_generation = slot->lifecycleGeneration();
  result.transaction.registry_epoch = registry->recordingEpoch();

  // In an unfiltered recording, context threads keep their normal MethodSample
  // stream. Only owned blocks that remain outside the context window may replace
  // repeated signals.
  if (registry->unfilteredWallTrackingActive() && slot->inContextWindow()) {
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
    result.transaction.arm_state = block_slot->activeBlockState();
    result.transaction.block_generation = block_generation;
    return result;
  }
  // Delegated and lightweight samples have no reusable local trace ID for
  // replaying a weighted tail. Keep unit-weight sampling for unowned blocks.
  if (!transactional || Profiler::instance()->omitStacktraces() ||
      !block_slot->unownedBlockedFallbackEnabled()) {
    return result;
  }

#if defined(DEBUG) || defined(UNIT_TEST)
  result.observed_state = observed_state_for_test != OSThreadState::UNKNOWN
      ? observed_state_for_test :
#ifdef UNIT_TEST
      thread_state_reader_for_test.load(std::memory_order_acquire) != nullptr
          ? thread_state_reader_for_test.load(std::memory_order_acquire)() :
#endif
      getOSThreadState();
#else
  result.observed_state = getOSThreadState();
#endif
  result.observed_state_valid = true;
  bool force_ordinary = false;
  {
    result.transaction.context = ContextApi::snapshot();
    result.transaction.context_captured = true;
    Context origin{};
    u64 publication = 0;
    bool readable = tracker->readUnownedContext(slot_id, origin, publication);
    bool publishable = tracker->canPublishUnownedContext(slot_id);
    bool unavailable = !publishable ||
        (block_slot->unowned_blocked_call_trace_id.load(std::memory_order_acquire) != 0 && !readable);
    force_ordinary = !readable || !publishable || !origin.equals(result.transaction.context);
    result.transaction.context_publication = publication;
#ifdef UNIT_TEST
    if (unowned_context_probe_hook != nullptr) unowned_context_probe_hook(unowned_context_probe_arg);
#endif
    if (readable) {
      u64 confirmed = 0;
      if (!tracker->readUnownedContext(slot_id, origin, confirmed) || confirmed != publication) {
        force_ordinary = true;
        unavailable = true;
      }
    }
    // A rejected probe cannot justify suppression against a reused owner or a
    // closed recording. Native ownership and recording eligibility are separate.
    if (registry->activeSlotForId(slot_id, result.transaction.tid) != slot ||
        slot->lifecycleGeneration() != result.transaction.lifecycle_generation ||
        registry->recordingEpoch() != result.transaction.registry_epoch) {
      return result;
    }
    if (unavailable) Counters::increment(WC_UNOWNED_CONTEXT_SNAPSHOT_UNAVAILABLE);
    result.transaction.force_unowned_ordinary = force_ordinary;
  }
  if (isPrecheckSuppressionState(result.observed_state)) {
    bool record = block_slot->shouldRecordUnownedBlockedSample(force_ordinary, false);
    if (!record && tracker->deferUnownedWeight(
            slot_id, result.transaction.sampling_epoch_start)) {
      Counters::increment(WC_UNOWNED_BLOCKED_SUPPRESSED);
      result.suppress = true;
      return result;
    }
    result.transaction.unowned_sample = true;
    result.transaction.observed_state = result.observed_state;
    result.transaction.flush_tail = force_ordinary;
  } else {
    result.transaction.flush_tail = true;
  }
  return result;
}

#ifdef UNIT_TEST
WallSampleRequest BaseWallClock::prepareWallSampleRequestForTest(ProfiledThread* current,
                                                                bool& suppressed) {
  WallPrecheckResult prepared = prepareWallPrecheck(current, true, true);
  suppressed = prepared.suppress;
  return prepared.transaction;
}
#endif

static inline void finishWallPrecheck(const WallPrecheckResult& precheck,
                                      bool recorded) {
  if (recorded && precheck.owned_block_slot != nullptr) {
    precheck.owned_block_slot->markBlockGenerationSampled(
        precheck.owned_block_generation);
  }
}

#ifdef UNIT_TEST
bool BaseWallClock::wallPrecheckForTest(
    ProfiledThread* current, bool unowned_fallback, OSThreadState observed_state,
    u64& weight, bool recorded) {
  WallPrecheckResult result =
      prepareWallPrecheck(current, true, unowned_fallback, observed_state);
  weight = 1;
  finishWallPrecheck(result, recorded);
  return result.suppress;
}
#endif

#if defined(DEBUG) || defined(UNIT_TEST)
bool BaseWallClock::awaitInitialSamplingEpochForTest(u64 timeout_nanos) {
  DEBUG_ASSERT_NOT_IN_SIGNAL();
  u64 start = OS::nanotime();
  while (WallClockCounters::samplingEpochStart() == 0) {
    if (OS::nanotime() - start >= timeout_nanos) return false;
    OS::sleep(1000000);
  }
  return true;
}
#endif

#ifdef DEBUG
// Only the synchronous JNI test driver supplies this argument. It inserts a
// real dump at a boundary outside the profiler stripe locks, without waiting
// inside a signal handler or adding hooks to release builds.
struct WallPrecheckDumpTest {
  jthread thread;
  const char* path;
  int path_length;
  bool dump_after_primary;
  Error error = Error::OK;

  void dumpAtBoundary(bool publication) {
    if (publication == dump_after_primary) {
      error = Profiler::instance()->dump(path, path_length);
    }
  }
};

static bool recordAsgctWallSampleForTest(
    ExecutionEvent* event, WallSampleRequest request, WallPrecheckDumpTest& dump_test) {
  Profiler* profiler = Profiler::instance();
  // Capture on the synchronous JNI thread, outside the signal handler and stripe.
  u64 trace_id = profiler->recordJVMTISample(
      1, request.tid, dump_test.thread, BCI_WALL, event, true);
  if (trace_id == 0) return false;
  request.trace_epoch = profiler->recordingEpoch();
  return profiler->recordWallSample(nullptr, 1, trace_id, event, request).ordinary_recorded;
}

bool BaseWallClock::recordUnownedWallTailAcrossDumpForTest(
    jthread thread, const char* path, int path_length, bool dump_after_primary,
    bool reset_before_tail) {
  SignalBlocker blocker;
  Profiler* profiler = Profiler::instance();
  ProfiledThread* current = ProfiledThread::initCurrentThreadSignalSafe();
  ThreadFilter* registry = profiler->threadFilter();
  if (current == nullptr || !profiler->isRunning() ||
      !registry->unfilteredWallTrackingActive()) return false;
  ThreadFilter::SlotID slot_id = registry->ensureOwnerSlot(*current);
  auto* tracker = profiler->blockTracker();
  WallClockBlockTracker::BlockState* slot = tracker->slotForId(slot_id);
  if (slot == nullptr || slot->activeBlockOwner() != BlockRunOwner::NONE) return false;
  // Epoch zero deliberately cannot defer weight; wait for timer initialization.
  if (!awaitInitialSamplingEpochForTest(5 * NANOTIME_FREQ)) return false;
  tracker->resetSlot(slot_id);

  WallPrecheckDumpTest dump_test{thread, path, path_length, dump_after_primary};
  ExecutionEvent event;
  event._thread_state = OSThreadState::SLEEPING;
  event._execution_mode = ExecutionMode::JAVA;
  WallPrecheckResult first = prepareWallPrecheck(current, true, true, OSThreadState::SLEEPING);
  if (first.suppress || !first.transaction.unowned_sample) return false;
  if (!recordAsgctWallSampleForTest(&event, first.transaction, dump_test)) return false;
  // Publication is stripe-atomic; dump can run only after the whole transaction.
  dump_test.dumpAtBoundary(true);
  if (dump_test.error) return false;

  if (!prepareWallPrecheck(current, true, true, OSThreadState::SLEEPING).suppress) return false;
  WallPrecheckResult tail = prepareWallPrecheck(current, true, true, OSThreadState::RUNNABLE);
  if (!tail.transaction.flush_tail || slot->unowned_blocked_pending_weight.load() != 1) return false;
  dump_test.dumpAtBoundary(false);
  if (dump_test.error) return false;
  if (reset_before_tail) tracker->resetSlot(slot_id);
  event._thread_state = OSThreadState::RUNNABLE;
  return recordAsgctWallSampleForTest(&event, tail.transaction, dump_test);
}

bool BaseWallClock::seedUnownedWallTailForTest(jthread thread) {
  Profiler* profiler = Profiler::instance();
  ProfiledThread* current = ProfiledThread::initCurrentThreadSignalSafe();
  ThreadFilter* registry = profiler->threadFilter();
  if (current == nullptr || !profiler->isRunning() ||
      !registry->unfilteredWallTrackingActive()) return false;
  ThreadFilter::SlotID slot_id = registry->ensureOwnerSlot(*current);
  WallClockBlockTracker::BlockState* slot = profiler->blockTracker()->slotForId(slot_id);
  if (slot == nullptr || slot->activeBlockOwner() != BlockRunOwner::NONE) return false;
  if (!awaitInitialSamplingEpochForTest(5 * NANOTIME_FREQ)) return false;
  profiler->blockTracker()->resetSlot(slot_id);
  ExecutionEvent event;
  event._thread_state = OSThreadState::SLEEPING;
  event._execution_mode = ExecutionMode::JAVA;
  WallPrecheckResult first = prepareWallPrecheck(current, true, true, OSThreadState::SLEEPING);
  if (first.suppress || !first.transaction.unowned_sample) return false;
  u64 trace_id = profiler->recordJVMTISample(
      1, current->tid(), thread, BCI_WALL, &event, true);
  first.transaction.trace_epoch = profiler->recordingEpoch();
  if (trace_id == 0 || !profiler->recordWallSample(
      nullptr, 1, trace_id, &event, first.transaction).ordinary_recorded) return false;
  finishWallPrecheck(first, true);
  for (int i = 0; i < 5; i++) {
    if (!prepareWallPrecheck(current, true, true, OSThreadState::SLEEPING).suppress) return false;
  }
  return true;
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
    event._weight = 1;
    Profiler::instance()->recordWallSample(ucontext, last_sample, call_trace_id,
                                           &event, precheck.transaction);
  }
}

Error BaseWallClock::start(Arguments &args) {
#if defined(UNIT_TEST) || defined(DEBUG)
  if (_force_start_failure_for_test.load(std::memory_order_acquire)) {
    return Error("Forced wall engine start failure (unit test)");
  }
#endif
  // Defensive (R-C1): a previous stop() whose join failed kept the handle. That
  // thread was already told to exit; retry the join before reusing _thread. A
  // join failure on a thread we created signals a programming error, so the
  // rejection is sticky (logged by the caller).
  if (_thread != 0) {
    if (pthread_join(_thread, NULL) == 0) {
      _thread = 0;
    } else {
      return Error("WallClock timer thread from previous run was not joined");
    }
  }
  int interval = args._event != NULL ? args._interval : args._wall;
  if (interval < 0) {
    return Error("interval must be positive");
  }
  _interval = interval ? interval : DEFAULT_WALL_INTERVAL;

  _reservoir_size =
            args._wall_threads_per_tick ?
            args._wall_threads_per_tick : DEFAULT_WALL_THREADS_PER_TICK;
  initialize(args);

  const char* diagnostics = getenv("DDPROF_WALL_TIMER_DIAGNOSTICS");
  _timer_diagnostics = diagnostics != nullptr && strcmp(diagnostics, "1") == 0;
  _timer_phases = TimerPhases{};
  _running = true;

  if (pthread_create(&_thread, NULL, threadEntry, this) != 0) {
    _thread = 0;  // *thread is undefined on error (R-C1)
    return Error("Unable to create timer thread");
  }

  return Error::OK;
}

void BaseWallClock::stop() {
  _running.store(false);
  // _thread is non-zero only between a successful pthread_create() and a
  // successful pthread_join() (R-C1): start() resets it to 0 when
  // pthread_create() fails, and the forced-failure test hook returns before
  // any create, so 0 means "no thread owned". Profiler::stop() only reaches this call when
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
    // Keep the handle: the next start() retries the join (R-C1).
    Log::warn("Unable to join WallClock thread on stop %d; keeping handle for retry", res);
    return;
  }
  _thread = 0;
  if (_timer_diagnostics) {
    const auto& p = _timer_phases;
    fprintf(stderr, "WallClock timer phases: iterations=%llu empty=%llu single=%llu large=%llu "
            "selected=%llu sent=%llu failed=%llu firstEligibleTicks=%llu lastEligibleTicks=%llu "
            "firstSendTicks=%llu lastSendTicks=%llu frequency=%llu collectNs=%llu selectNs=%llu "
            "sendNs=%llu finishNs=%llu requestedSleepNs=%llu actualSleepNs=%llu\n",
            p.iterations, p.empty, p.single, p.large, p.selected, p.sent, p.failed,
            p.first_eligible, p.last_eligible, p.first_send, p.last_send, TSC::frequency(),
            p.collect_ns, p.select_ns, p.send_ns, p.finish_ns,
            p.requested_sleep_ns, p.actual_sleep_ns);
  }
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
    const bool lookup_registry_slot =
        _precheck && thread_filter->unfilteredWallTrackingActive();
    ThreadFilter::RecordingEpoch recording_epoch = 0;
    auto collectThreads = [&](std::vector<ThreadEntry>& entries) {
      // Re-read once per tick, before any sampleThreads.
      recording_epoch = lookup_registry_slot ? thread_filter->recordingEpoch() : 0;
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
                                 _reservoir_size, _interval, lookup_registry_slot);
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
    event._weight = 1;
    // Pass the interrupted context for HotSpot's no-last-Java-frame path.
    // Unowned samples retain unit weight: this engine cannot replay a cached stack.
    bool recorded = Profiler::instance()->recordSampleDelegated(
        ucontext, last_sample, tid, BCI_WALL, &event);
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
  const bool lookup_registry_slot =
      _precheck && thread_filter->unfilteredWallTrackingActive();
  ThreadFilter::RecordingEpoch recording_epoch = 0;
  auto collectThreads = [&](std::vector<ThreadEntry> &entries) {
    // Re-read once per tick, before any sampleThreads.
    recording_epoch = lookup_registry_slot ? thread_filter->recordingEpoch() : 0;
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
                               _reservoir_size, _interval, lookup_registry_slot);
}
