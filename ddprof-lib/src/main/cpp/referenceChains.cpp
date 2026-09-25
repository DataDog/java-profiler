/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "referenceChains.h"
#include "referenceChainInternal.h"
#include "common.h"
#include "counters.h"
#include "jniHelper.h"
#include "jvmThread.h"
#include "livenessTracker.h"
#include "log.h"
#include "objectSampler.h"
#include "os.h"
#include "profiler.h"
#include "rcDebugLevel.h"
#include "tsc.h"
#include "vmEntry.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_set>

// Reference-chains debug-log level (see rcDebugLevel.h). Level 0 silent
namespace {
constexpr const char *kRcDebugLevelEnv = "DD_PROFILING_REFERENCE_CHAINS_DEBUG";
constexpr const char *kRcDebugLevelFile = "/tmp/ddprof_root/refchains_debug_level";
constexpr u64 kRcDebugLevelRefreshTtlNs = 1000000000ULL; // 1s
std::atomic<int> g_rc_debug_level{-1}; // -1 = not yet resolved from env
std::atomic<u64> g_rc_debug_level_last_refresh_ns{0};

int envRcDebugLevel() {
  int lvl = parseRcDebugLevel(getenv(kRcDebugLevelEnv));
  return lvl < 0 ? 0 : lvl; // invalid/unset env means silent
}
} // namespace

int rcDebugLevel() {
  int lvl = g_rc_debug_level.load(std::memory_order_relaxed);
  if (lvl >= 0) {
    return lvl;
  }
  // Lazy one-time env resolve; may fire from a heap callback on the very first log line, which is
  // still strictly cheaper than the fprintf the same line performs in a DEBUG build.
  lvl = envRcDebugLevel();
  g_rc_debug_level.store(lvl, std::memory_order_relaxed);
  return lvl;
}

int parseRcDebugLevel(const char *value) {
  if (value == nullptr || *value == '\0') {
    return -1;
  }
  // Trim surrounding whitespace (files written via `echo N >` end with \n).
  while (*value == ' ' || *value == '\t' || *value == '\n' || *value == '\r') {
    ++value;
  }
  const char *end = value + strlen(value);
  while (end > value && (end[-1] == ' ' || end[-1] == '\t' ||
                         end[-1] == '\n' || end[-1] == '\r')) {
    --end;
  }
  if (end == value || end - value != 1) {
    return -1; // exactly one digit
  }
  if (*value < '0' || *value > '2') {
    return -1;
  }
  return *value - '0';
}

int readRcDebugLevelFile(const char *path) {
  if (path == nullptr) {
    return -1;
  }
  // The knob file lives under the world-writable /tmp (see kRcDebugLevelFile's
  // comment): refuse anything that is not a regular file owned by root or the
  // current user, so a local user cannot plant a symlink or a pre-created
  // file of their own and force the DEBUG-build diagnostics on. The worst
  // impact of a forged file is log-volume/CPU from enabled TEST_LOG in a
  // DEBUG build, but the check is cheap and keeps the knob owner-scoped.
  struct stat st;
  if (lstat(path, &st) != 0 || !S_ISREG(st.st_mode)) {
    return -1; // missing, symlink, fifo, dir - treat as "no override"
  }
  if (st.st_uid != 0 && st.st_uid != geteuid()) {
    return -1;
  }
  FILE *f = fopen(path, "r");
  if (f == nullptr) {
    return -1;
  }
  char buf[16];
  size_t n = fread(buf, 1, sizeof(buf) - 1, f);
  fclose(f);
  buf[n] = '\0';
  return parseRcDebugLevel(buf);
}

void rcDebugLevelRefresh(bool force) {
  u64 now = OS::nanotime();
  u64 last = g_rc_debug_level_last_refresh_ns.load(std::memory_order_relaxed);
  if (!force && last != 0 && now >= last &&
      now - last < kRcDebugLevelRefreshTtlNs) {
    return;
  }
  g_rc_debug_level_last_refresh_ns.store(now, std::memory_order_relaxed);
  int lvl = readRcDebugLevelFile(kRcDebugLevelFile);
  if (lvl < 0) {
    lvl = envRcDebugLevel(); // file absent/invalid -> fall back to env
  }
  g_rc_debug_level.store(lvl, std::memory_order_relaxed);
}

// ReferenceChainTracker

// Marks the calling thread as executing inside the GarbageCollectionStart/ Finish JVMTI callback
// for the duration of the guard's lifetime.
thread_local bool t_inGCCallback = false;

namespace {
class GCCallbackGuard {
public:
  GCCallbackGuard() { t_inGCCallback = true; }
  ~GCCallbackGuard() { t_inGCCallback = false; }
};
} // namespace

void ReferenceChainTracker::autoTuneDefaults(Arguments &args) {
  // Only tune defaults the operator did not set explicitly.
  const u8 tuned = args._reference_chains_tuned_mask;

  // Max heap is resolved by LivenessTracker::initialize_table() at this point
  // (ObjectSampler::start() -> LivenessTracker::start() runs before ReferenceChainTracker::start()
  // in Profiler::start()).
  jlong max_heap = LivenessTracker::instance()->maxHeapBytes();
  if (max_heap <= 0) {
    return; // can't tune without heap size
  }

  // Available processors from JVMTI (cached by FlightRecorder, but we can query JVMTI directly
  // here).
  jint nprocs = 1;
  jvmtiEnv *jvmti = VM::jvmti();
  if (jvmti != nullptr) {
    jvmti->GetAvailableProcessors(&nprocs);
  }
  if (nprocs < 1) nprocs = 1;

  // Heap size in MiB.
  double heap_mib = (double)max_heap / (1024.0 * 1024.0);

  // --- Budget (edges per BFS pass) --- Scale with sqrt(heap_mib): a 4 GiB heap gets 2x, a 16 GiB
  // heap gets 4x, a 64 GiB heap gets 8x the default 1000.
  if (!(tuned & REF_CHAINS_TUNED_BUDGET)) {
    int scaled = (int)(DEFAULT_REFERENCE_CHAINS_BUDGET * std::sqrt(heap_mib / 512.0));
    args._reference_chains_budget = std::max(DEFAULT_REFERENCE_CHAINS_BUDGET,
        std::min(scaled, MAX_REFERENCE_CHAINS_BUDGET));
  }

  // --- First-pass budget --- The root enumeration pass is one-shot per search and can afford a
  // much larger budget.
  if (!(tuned & REF_CHAINS_TUNED_FIRST_PASS_BUDGET)) {
    int fpb = args._reference_chains_budget * 10;
    args._reference_chains_first_pass_budget = std::min(fpb,
        MAX_REFERENCE_CHAINS_FIRST_PASS_BUDGET);
  }

  // --- TTL (per-search wall-clock lifetime) --- The search needs enough time to cover the heap at
  // the tuned budget.
  if (!(tuned & REF_CHAINS_TUNED_TTL)) {
    long scaled_ttl = (long)(DEFAULT_REFERENCE_CHAINS_TTL_MS * (heap_mib / 512.0));
    scaled_ttl = std::max(DEFAULT_REFERENCE_CHAINS_TTL_MS, std::min(scaled_ttl,
        (long)(30 * 60 * 1000))); // 30 min max
    args._reference_chains_ttl_ms = scaled_ttl;
  }

  // --- Frontier cap --- The frontier grows with the number of edges admitted per pass.
  if (!(tuned & REF_CHAINS_TUNED_FRONTIER_CAP)) {
    int scaled_cap = (int)(DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP *
        ((double)args._reference_chains_budget / DEFAULT_REFERENCE_CHAINS_BUDGET));
    args._reference_chains_frontier_cap = std::max(
        DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP,
        std::min(scaled_cap, MAX_REFERENCE_CHAINS_FRONTIER_CAP));
  }

  // --- Pause target --- More available processors = the JVM can afford a slightly longer per-pass
  // safepoint without impacting application throughput.
  if (!(tuned & REF_CHAINS_TUNED_PAUSE_TARGET)) {
    long scaled_pause = DEFAULT_REFERENCE_CHAINS_PAUSE_TARGET_MS *
        (1 + (nprocs - 1) / 3);
    args._reference_chains_pause_target_ms = std::min(scaled_pause, (long)50);
  }

  // --- Pain budget percent --- More cores = more spare capacity for background work.
  if (!(tuned & REF_CHAINS_TUNED_PAIN_BUDGET)) {
    int scaled_pain = DEFAULT_REFERENCE_CHAINS_PAIN_BUDGET_PERCENT *
        (1 + (nprocs - 1) / 4);
    args._reference_chains_pain_budget_percent = std::min(scaled_pain, 5);
  }

  Log::info("Reference chain auto-tuner: heap=%.0f MiB nprocs=%d -> "
      "budget=%d ttl=%ldms framecap=%d pausetarget=%ldms painbudget=%d%% firstpassbudget=%d",
      heap_mib, (int)nprocs,
      args._reference_chains_budget, args._reference_chains_ttl_ms,
      args._reference_chains_frontier_cap,
      args._reference_chains_pause_target_ms,
      args._reference_chains_pain_budget_percent,
      args._reference_chains_first_pass_budget);
}

Error ReferenceChainTracker::start(Arguments &args) {
  _enabled = args._reference_chains;

  if (!_enabled) {
    Log::info("Reference chain tracking is disabled");
    return Error::OK;
  }

  // Recording-boundary hygiene: Profiler::start() clears the class dictionary (restart its id
  // namespace) right before this runs, so cached chain events and queued abandonment events from a
  // prior recording carry StringDictionary ids from a wiped generation - re-emitting them into the
  // new recording would write missing or newly-reassigned class ids for chains that describe the
  // previous recording's objects.
  _resolved_chains_lock.lock();
  _resolved_chains.clear();
  _resolved_chains_lock.unlock();
  _pending_abandoned_events_lock.lock();
  _pending_abandoned_events.clear();
  _pending_abandoned_events_lock.unlock();
  _urgency_budget_boosted = false;

  // Auto-tune defaults that the operator did not set explicitly, based on max heap size and
  // available processors.
  autoTuneDefaults(args);

  Log::info("Reference chain tracking is enabled (hops=%d, budget=%d, "
            "ttl=%ldms, framecap=%d, pausetarget=%ldms, painbudget=%d%%)",
            args._reference_chains_hop_cap, args._reference_chains_budget,
            args._reference_chains_ttl_ms, args._reference_chains_frontier_cap,
            args._reference_chains_pause_target_ms,
            args._reference_chains_pain_budget_percent);

  // Like LivenessTracker's own table, construct the frontier table once and keep it across repeated
  // start()/stop() cycles - do not reallocate on a second start() with a possibly different cap,
  // for the same reason LivenessTracker keeps its first-initialize() result.
  _configured_frontier_cap = args._reference_chains_frontier_cap;
  if (_frontier == nullptr) {
    _frontier = new FrontierTable(_configured_frontier_cap);
  }
  // The configured budget is what the urgency ramp restores when urgency clears (see the urgency
  // block in threadLoop()) - the live _budget must not be snapshotted for that, it may already be
  // boosted.
  _configured_budget = args._reference_chains_budget;

  _hop_cap = args._reference_chains_hop_cap;
  _budget = args._reference_chains_budget;
  // 0 (unset) auto-scales from _budget instead of falling back to it plainly - see this field's own
  // comment (referenceChains.h) for why a steady-state per-pass budget is the wrong size for the
  // first pass.
  _first_pass_budget = args._reference_chains_first_pass_budget > 0
                            ? args._reference_chains_first_pass_budget
                            : std::min(_budget * AUTO_FIRST_PASS_BUDGET_MULTIPLIER,
                                       AUTO_FIRST_PASS_BUDGET_CAP);
  _ttl_ms = args._reference_chains_ttl_ms;

  // Pause-time pacing controller: (re)seed the controller's ceiling and the adaptive values it
  // drives.
  _pause_target_ms = args._reference_chains_pause_target_ms;
  _effective_pause_target_ms = _pause_target_ms;
  _effective_budget = _budget;
  _effective_cadence_ns = PASS_CADENCE_NS;
  _candidate_count = 0;
  _candidate_found_bits = 0;
  memset(_candidate_discovered_count, 0, sizeof(_candidate_discovered_count));
  memset(_candidate_qualifying_tid_count, 0,
         sizeof(_candidate_qualifying_tid_count));
  _passes_since_last_candidate_progress = 0;
  _last_candidate_progress_mark = 0;
  // Fresh chase gets a fresh back-to-back spacing allowance (see _canary_backoff_mult's own
  // comment).
  _canary_backoff_mult = 1;
  _canary_pass_ema_ms = 0;
  _last_canary_pass_ns = 0;
  _canary_stuck_restart_count = 0;
  // Budget-borrowing (referenceChains.h's _borrowed_budget comment): reset alongside the rest of
  // the pacing controller's state, so a restarted search never inherits headroom earned by a
  // previous one.
  _borrowed_budget = 0;
  _consecutive_under_target_passes = 0;
  _pause_pid = PidController((u64)std::max(_pause_target_ms, 0L),
                              10,  // proportional gain: reacts to a single
                                   // pass's over/under-ceiling error without needing many passes to
                                   // notice - a duration-ms error is typically single/
                                   // low-double-digit in magnitude (unlike the shared triple's
                                   // event-count scale), so a smaller P keeps a one-pass overshoot
                                   // from.
                              1,   // integral gain: small and round -
                                   // pidController.cpp's `_integral_value` has no built-in clamp,
                                   // and this controller is invoked once per BFS pass rather than
                                   // on the other three usages' roughly-periodic
                                   // one-call-per-second cadence, so windup accumulates faster per
                                   // wall-clock.
                              2,   // derivative gain: small, matching the
                                   // shared triple's own "the derivational gain is rather small"
                                   // rationale (objectSampler.cpp) - a single slow/ fast pass
                                   // should not itself trigger a large swing
                              1,   // sampling_window=1: one compute() call
                                   // *is* one pass, not a fixed real-time window like the other
                                   // three usages assume (see _pause_pid's own comment)
                              5.0  // cutoff_secs: a round value, halved from
                                   // the shared triple's own "15" since a pass-scoped signal is
                                   // naturally noisier per-call than a roughly-1s- cadence one
  );

  // (re)seed _safepoint_pain_budget from the configured refill rate, mirroring _pause_pid's own
  // reconstruct-in-start() pattern above.
  _safepoint_pain_budget = PainBudget(
      std::max(args._reference_chains_pain_budget_percent, 0) / 100.0);
  _pain_budget_refill_rate = std::max(args._reference_chains_pain_budget_percent, 0) / 100.0;
  // Same refill rate as _safepoint_pain_budget above - one operator-facing "how much background
  // cost is acceptable" percentage covers both leaky buckets (see _cpu_pain_budget's own comment,
  // referenceChains.h).
  _cpu_pain_budget = PainBudget(_pain_budget_refill_rate);

  // Lazy-enable, matching LivenessTracker::start(): the GC callbacks are wired unconditionally in
  // vmEntry.cpp, but the events themselves are only turned on for this JVMTI env when the flag is
  // on.
  jvmtiEnv *jvmti = VM::jvmti();
  jvmti->SetEventNotificationMode(
      JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_START, nullptr);
  jvmti->SetEventNotificationMode(
      JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_FINISH, nullptr);

  // Deliberately does NOT create the BFS thread (threadEntry()/threadLoop() below) here -
  // threadLoop()'s VM::attachThread() call dereferences VM::_vm unconditionally (vmEntry.h:191-195)
  // and crashes if the VM is not yet attached, which is exactly the case in this file's own gtest
  // binary (referenceChains_ut.cpp calls start() directly with no live JVM).

  return Error::OK;
}

void ReferenceChainTracker::stop() {
  if (!_enabled) {
    return;
  }
  Log::info("Reference chain tracking stopped");

  // Do not disable GC notifications here - LivenessTracker follows the same rule since the JVMTI
  // env and its tracker singletons are expected to survive across multiple start/stop recording
  // cycles.
}

void ReferenceChainTracker::startThread() {
  if (!_enabled || _running.load(std::memory_order_acquire)) {
    return;
  }
  // Reset from any previous stopThread() call - a dynamic-attach profiler can go through multiple
  // start()/stop() cycles in one JVM lifetime (this class's own start()/stop() header comments),
  // and a stale abort request left set from the prior cycle would make heapReferenceCallback()
  // abort this new cycle's very first pass instantly.
  _abort_pass_requested.store(false, std::memory_order_relaxed);

  // Publish _running=true *before* creating the thread, not after.
  _running.store(true, std::memory_order_release);
  pthread_t thread;
  if (pthread_create(&thread, NULL, threadEntry, this) != 0) {
    Log::warn("Unable to create ReferenceChains BFS thread");
    _running.store(false, std::memory_order_release);
    return;
  }
  _thread = thread;
}

void ReferenceChainTracker::stopThread() {
  if (!_running.load(std::memory_order_acquire)) {
    return;
  }
  _running.store(false, std::memory_order_release);
  // Ask any in-flight JVMTI FollowReferences walk (heapReferenceCallback()) to abort at its next
  // callback invocation - set before pthread_kill() below, since that signal alone cannot interrupt
  // a call already inside the JVM/JVMTI implementation.
  _abort_pass_requested.store(true, std::memory_order_relaxed);
  // Same wake-then-join shape as BaseWallClock::stop() (wallClock.cpp:324-333):
  // pthread_kill(WAKEUP_SIGNAL) interrupts threadLoop()'s OS::sleep() early (WAKEUP_SIGNAL/SIGIO is
  // installed with a no-op handler unconditionally in vmEntry.cpp, so this signal never terminates
  // the thread) so it re-checks _running and exits promptly rather than waiting out the rest of the
  // current sleep interval.
  pthread_kill(_thread, WAKEUP_SIGNAL);
  int res = pthread_join(_thread, NULL);
  if (res != 0) {
    Log::warn("Unable to join ReferenceChains BFS thread on stop %d", res);
  }
}

// Runs scheduled passes on an attached agent thread.
void ReferenceChainTracker::threadLoop() {
  struct Cleanup {
    ReferenceChainTracker *tracker;
    ~Cleanup() {
      // No cached-class cleanup needed before detaching: _cached_object_class is a global ref,
      // deliberately valid across attach/detach cycles (see its own comment in referenceChains.h) -
      // unlike the per-attach local ref it replaced, which this destructor used to have to clear
      // here.
      VM::detachThread();
    }
  } cleanup{this};
  JNIEnv *jni = VM::attachThread("java-profiler ReferenceChains");
  jvmtiEnv *jvmti = VM::jvmti();
  if (jni == nullptr) {
    // AttachCurrentThreadAsDaemon() failed - mirror pollWatchedTargets()'s own jni==nullptr early
    // return rather than letting a null JNIEnv flow into
    // runPass()/resolveLoadedClasses()/expandFrontier()/ releaseSearchTags() below: those only
    // guard their DeleteLocalRef() calls on `jni != nullptr`, so without this check every
    // GetLoadedClasses()/GetObjectsWithTags() local ref returned on this (permanently un-attached)
    // thread would leak for the rest of the process's lifetime.
    Log::warn("ReferenceChains: VM::attachThread failed; BFS thread exiting");
    return;
  }
  DEBUG_ONLY(rcDebugLevelRefresh(true)); // apply the override file before the first log line
  TEST_LOG_SUMMARY("ReferenceChainTracker::threadLoop started, cadence=%lluns rc_debug_level=%d", (unsigned long long)_effective_cadence_ns, rcDebugLevel());

  int iteration = 0;
  while (_running.load(std::memory_order_acquire)) {
    // Fixed ~1s cadence, no early wake on GC (see onGCFinish()'s own comment) - stopThread() still
    // interrupts this via its own pthread_kill so shutdown stays prompt.
    double seconds_to_oom = LivenessTracker::instance()->secondsToOOM();
    bool urgent = seconds_to_oom >= 0 && seconds_to_oom < OOM_RAMP_START_S;
    long target_ms = _pause_target_ms;
    u64 cadence_ns = _effective_cadence_ns;
    if (urgent) {
      double x = 1.0 - seconds_to_oom / OOM_RAMP_START_S; // 0 at 30min out, 1 at OOM
      target_ms = std::lround(_pause_target_ms *
          std::pow((double)URGENT_PAUSE_TARGET_MS / std::max(_pause_target_ms, 1L), x));
      // Ramp from the fixed configured cadence, not the currently-adaptive _effective_cadence_ns -
      // using the live value as the ramp's own moving anchor would compound the exponent across
      // iterations instead of tracking urgency directly from a stable baseline.
      cadence_ns = (u64)std::llround((double)PASS_CADENCE_NS *
          std::pow((double)URGENT_CADENCE_NS / (double)PASS_CADENCE_NS, x));
      // While urgent, the ramp owns _effective_cadence_ns outright so shouldRunPass()'s cadence
      // gate and the per-pass log actually reflect it.
      _effective_cadence_ns = cadence_ns;
    }
    if (target_ms != _effective_pause_target_ms) {
      _effective_pause_target_ms = target_ms;
      _pause_pid = PidController((u64)std::max(_effective_pause_target_ms, 0L),
                                  10, 1, 2, 1, 5.0);
    }
    // Once in the ramp window, hold the budget ceiling raised for the urgency episode's entire
    // duration rather than only right before OOM: the process is likely to die anyway, so it's
    // worth spending whatever budget it takes to collect good diagnostic data for as long as we
    // have.
    if (urgent && !_urgency_budget_boosted) {
      _urgency_budget_boosted = true;
      _budget = std::min(_budget * 4, MAX_REFERENCE_CHAINS_BUDGET);
      TEST_LOG_SUMMARY("ReferenceChainTracker::threadLoop urgency budget boost "
               "budget=%d configured=%d",
               _budget, _configured_budget);
    } else if (!urgent && _urgency_budget_boosted) {
      _urgency_budget_boosted = false;
      _budget = _configured_budget;
      TEST_LOG_SUMMARY("ReferenceChainTracker::threadLoop urgency budget restore "
               "budget=%d", _budget);
    }
    // Third trigger for LivenessTracker::cleanup_table() (see
    // LivenessTracker::maybeForceCleanup()'s own comment): track()'s table-overflow branch and
    // flush_table()'s JFR cadence can both starve under ObjectSampler's PID-controlled sampling
    // interval, leaving hasLeakSignal() below stuck on a stale population history no matter how
    // long a real leak keeps growing.
    u64 wake_now_ns = OS::nanotime();
    LivenessTracker::instance()->maybeForceCleanup(wake_now_ns);

    // No fast-path skip here: shouldRunPass() below already returns false cheaply (a couple of
    // atomic loads/comparisons, no JVMTI call) for a RUNNING search with no new GC and cadence not
    // yet elapsed.
    u64 now_ns = OS::nanotime();

    // Re-check the runtime debug-level override file (~1s TTL; see rcDebugLevel.h) - never in heap
    // callbacks, which only read the cached atomic.
    DEBUG_ONLY(rcDebugLevelRefresh());

    // Hand this iteration's ramp state to shouldRunPass() before it decides - the canary-backoff
    // gate is bypassed while the OOM urgency ramp is active (see _oom_ramp_active's own comment) -
    // and raise LivenessTracker's tracking admission to 100% for the same ramp (see
    // setUrgentTracking()'s own comment, livenessTracker.h): same state, same iteration, so the
    // boost tracks the ramp exactly, engaging and releasing together.
    _oom_ramp_active = urgent;
    LivenessTracker::instance()->setUrgentTracking(urgent);

    bool should_run = shouldRunPass(now_ns);
    // Only sleep when idle (no pass will run). When a canary search is active or a pass is about to
    // run, skip the sleep to run passes back-to-back.
    if (!should_run && cadence_ns > 0) {
      OS::sleep(cadence_ns);
      if (!_running.load(std::memory_order_acquire)) {
        break;
      }
      now_ns = OS::nanotime();
    }
    // Log the loop state only when a pass is actually going to run - the idle wakes (should_run ==
    // false) are the common steady state and logging them every second is pure noise.
    if (should_run) {
      TEST_LOG_SUMMARY("ReferenceChainTracker::threadLoop iteration=%d shouldRunPass=%d searchState=%d "
               "passesRun=%d effectiveCadenceNs=%llu effectiveBudget=%d gcFinishEpoch=%llu "
               "lastPassGcFinishEpoch=%llu nowMinusLastPassNs=%llu",
               ++iteration, should_run, (int)_search_state, _passes_run,
               (unsigned long long)_effective_cadence_ns, _effective_budget,
               (unsigned long long)gcFinishEpoch(), (unsigned long long)_last_pass_gc_finish_epoch,
               (unsigned long long)(now_ns - _last_pass_ns));
      runPassSerialized(jvmti, jni);
    }
    // Target-selection bridging step: poll once per scheduling cycle, after runPass() - so this
    // poll always sees the most recent pass's tagging (see pollWatchedTargets()'s own comment).
    pollWatchedTargetsSerialized(jvmti, jni);
  }
}

void JNICALL ReferenceChainTracker::GarbageCollectionStart(jvmtiEnv *jvmti_env) {
  ReferenceChainTracker::instance()->onGCStart();
}

void JNICALL ReferenceChainTracker::GarbageCollectionFinish(jvmtiEnv *jvmti_env) {
  ReferenceChainTracker::instance()->onGCFinish();
}

void ReferenceChainTracker::onGCStart() {
  if (!_enabled) {
    return;
  }
  // JVMTI spec: only Memory Management category calls (Allocate/Deallocate) are allowed from inside
  // this callback - nothing else may run here.
  GCCallbackGuard guard;
  atomicIncRelaxed(_gc_start_epoch, (u64)1);
}

void ReferenceChainTracker::onGCFinish() {
  if (!_enabled) {
    return;
  }
  GCCallbackGuard guard;
  // Heap-category JVMTI calls are forbidden from GC callbacks.
  atomicIncRelaxed(_gc_finish_epoch, (u64)1);
}

bool ReferenceChainTracker::shouldRunPass(u64 now_ns) {
  if (!_search_started) {
    // Same gate as a restart (canAffordNewSearch() below) - a brand-new tracker must not pay for
    // the first whole-heap walk/tagging pass either when there is no leak candidate to justify it.
    bool afford = canAffordNewSearch(now_ns);
    TEST_LOG_SUMMARY("ReferenceChainTracker::shouldRunPass search_not_started "
             "canAffordNewSearch=%d", (int)afford);
    if (!afford) {
      return false;
    }
    // This episode's one urgency-authorized search (_urgent_search_spent's own comment,
    // referenceChains.h) is the one about to start.
    _urgent_search_spent = _urgent_latched;
    TEST_LOG_SUMMARY("ReferenceChainTracker::shouldRunPass -> true (search not started yet)");
    return true; // nothing has run yet - always worth taking the first pass
  }
  if (_search_state != SearchState::RUNNING) {
    // Terminal outcome already reached (runPass()'s Termination section).
    if (!_tags_released) {
      // releaseSearchTags() failed to confirm every live tag this search owned was actually cleared
      // - restartSearch() must never run until that is confirmed (see _tags_released's own
      // comment), so return true unconditionally here: that drives threadLoop() to call runPass()
      // again, whose terminal-state branch retries the release, rather than letting
      // canAffordNewSearch()/restartSearch() below run ahead of it.
      TEST_LOG_SUMMARY("ReferenceChainTracker::shouldRunPass -> true (retrying tag "
               "release before restart is allowed)");
      return true;
    }
    // Charge the finished search's accumulated safepoint cost BEFORE the restart gate -
    // canAffordNewSearch() must see the cost of the search that just ended, otherwise an expensive
    // search earns one free immediate successor (the accumulator is spent here, once per search;
    // repeated terminal visits spend a zeroed accumulator).
    _safepoint_pain_budget.spend(_search_pain_ms);
    _search_pain_ms = 0;
    // Restart (this class's own header comment) if the pain budget has drained and there is still
    // (or again) a leak indication to chase - canAffordNewSearch() is always true when
    // LivenessTracker's population trends are not in use at all, so this only ever changes behavior
    // for a search that already ran once.
    if (canAffordNewSearch(now_ns)) {
      // Same entitlement bookkeeping as the first-search branch above.
      _urgent_search_spent = _urgent_latched;
      restartSearch();
      TEST_LOG_SUMMARY("ReferenceChainTracker::shouldRunPass -> true (restarting search)");
      return true;
    }
    // No log here: a terminal search waiting for a restart to become warranted is the common idle
    // state, re-evaluated every second, so logging it is pure per-second noise (see threadLoop()).
    TEST_LOG_SUMMARY("ReferenceChainTracker::shouldRunPass terminal_blocked "
             "tags_released=%d safepoint_pain=%d search_state=%d",
             (int)_tags_released,
             (int)_safepoint_pain_budget.canStartNow(now_ns),
             (int)_search_state);
    return false;
  }
  // Canary search active with candidates still to find - computed ahead of the pain-budget check
  // below so the refill-rate raise and the backoff gate further down agree on the same snapshot of
  // _candidate_found_bits.
  bool canary_active = _candidate_count > 0 &&
      __builtin_popcountll(_candidate_found_bits) < (u64)_candidate_count;
  // Adaptive CPU budget: 100x refill while a canary chase is open - NOT a rate control (the canary
  // lane's rate is bounded by _canary_backoff_ns's progress-driven exponential backoff, see its own
  // comment) but a double-throttle guard: the base refill rate is tuned for the ordinary ~1 pass/s
  // whole-graph cadence and would otherwise starve a chase the backoff has already paced.
  double multiplier =
      canary_active ? CANARY_PAIN_BUDGET_REFILL_MULTIPLIER : 1.0;
  _cpu_pain_budget.setRefillRate(
      std::min(_pain_budget_refill_rate * multiplier, 1.0),
      now_ns);
  if (!_cpu_pain_budget.canStartNow(now_ns)) {
    TEST_LOG_SUMMARY("ReferenceChainTracker::shouldRunPass blocked by cpu_pain_budget "
             "balance=%.1fms refill_rate=%.4f canary_active=%d "
             "multiplier=%.1f",
             _cpu_pain_budget.balanceMs(now_ns),
             std::min(_pain_budget_refill_rate * multiplier, 1.0),
             (int)canary_active, multiplier);
    return false;
  }
  if (canary_active) {
    // Canary-lane pacing: the chase's rate bound - work-scaled spacing (_canary_backoff_mult's own
    // comment for the law and the live burn it bounds).
    u64 spacing_ns =
        (u64)_canary_backoff_mult * _canary_pass_ema_ms * 1000000ULL;
    // mult == 1 (fresh chase, or last pass made progress) means the gate is OFF - the chase runs at
    // its natural pass rate, one pass starting as soon as the last ended.
    if (!_oom_ramp_active && _canary_backoff_mult > 1 &&
        now_ns - _last_canary_pass_ns < spacing_ns) {
      TEST_LOG("ReferenceChainTracker::shouldRunPass held off by canary "
               "backoff mult=%d ema_ms=%llu since_last_pass=%llums",
               _canary_backoff_mult,
               (unsigned long long)_canary_pass_ema_ms,
               (unsigned long long)((now_ns - _last_canary_pass_ns) /
                                   1000000ULL));
      return false;
    }
    TEST_LOG_SUMMARY("ReferenceChainTracker::shouldRunPass -> true (canary search, "
             "%d/%d candidates found, backoff_mult=%d ema_ms=%llu)",
             (int)__builtin_popcountll(_candidate_found_bits),
             (int)_candidate_count, _canary_backoff_mult,
             (unsigned long long)_canary_pass_ema_ms);
    return true;
  }
  u64 gc_finish_epoch = gcFinishEpoch();
  if (gc_finish_epoch != _last_pass_gc_finish_epoch) {
    // Triggering section: "a GC just happened, a pass may be worth running soon".
    TEST_LOG_SUMMARY("ReferenceChainTracker::shouldRunPass -> true (gcFinishEpoch=%llu != "
             "lastPassGcFinishEpoch=%llu)",
             (unsigned long long)gc_finish_epoch,
             (unsigned long long)_last_pass_gc_finish_epoch);
    return true;
  }
  // Pause-time pacing controller: compares against _effective_cadence_ns, not the fixed
  // PASS_CADENCE_NS - see that field's own comment (referenceChains.h) for how updatePacing()
  // widens or relaxes it from the measured pause-time signal.
  bool cadence_elapsed = now_ns - _last_pass_ns >= _effective_cadence_ns;
  // Only log when the cadence actually elapsed (a pass will run).
  if (cadence_elapsed) {
    TEST_LOG_SUMMARY("ReferenceChainTracker::shouldRunPass -> true (now_ns=%llu last_pass_ns=%llu "
             "delta=%llu effectiveCadenceNs=%llu)",
             (unsigned long long)now_ns, (unsigned long long)_last_pass_ns,
             (unsigned long long)(now_ns - _last_pass_ns),
             (unsigned long long)_effective_cadence_ns);
  }
  return cadence_elapsed;
}

// Search restart gate (this class's own header comment). Deliberately a probe (max=1) rather than
// reusing pollWatchedTargets()'s own selectLeakCandidates() call - that one runs after runPass() in
// threadLoop()'s own iteration and needs the *list* to poll each candidate's tag; this only needs
// to know whether at least one exists.
bool ReferenceChainTracker::isUrgent() const {
  double seconds_to_oom = LivenessTracker::instance()->secondsToOOM();
  if (seconds_to_oom >= 0 && seconds_to_oom < OOM_URGENT_THRESHOLD_S) {
    _urgent_release_ticks = 0;
    if (!_urgent_latched) {
      _urgent_latched = true;
      // A fresh episode gets a fresh entitlement to one search.
      _urgent_search_spent = false;
      TEST_LOG_SUMMARY("ReferenceChainTracker::isUrgent latching urgency "
               "(secondsToOOM=%.1f < OOM_URGENT_THRESHOLD_S=%.1f)",
               seconds_to_oom, OOM_URGENT_THRESHOLD_S);
    }
    return true;
  }
  if (_urgent_latched) {
    // Negative means "no rising trend to project from" (secondsToOOM()'s own unknown/NOT_RISING
    // encoding), which counts toward release just like a comfortably distant projection does.
    if (seconds_to_oom < 0 || seconds_to_oom >= OOM_URGENT_RELEASE_S) {
      if (++_urgent_release_ticks >= URGENT_RELEASE_CONSECUTIVE) {
        _urgent_latched = false;
        _urgent_release_ticks = 0;
        _urgent_search_spent = false;
        TEST_LOG_SUMMARY("ReferenceChainTracker::isUrgent releasing urgency "
                 "(secondsToOOM=%.1f clear of OOM_URGENT_RELEASE_S=%.1f for "
                 "%d consecutive observations)",
                 seconds_to_oom, OOM_URGENT_RELEASE_S,
                 URGENT_RELEASE_CONSECUTIVE);
        return false;
      }
    } else {
      // Between the two bars, or a single noisy reading past the release bar followed by one that
      // is not - neither releases the latch.
      _urgent_release_ticks = 0;
    }
    return true;
  }
  return false;
}

bool ReferenceChainTracker::hasLeakSignal() {
  if (!LivenessTracker::instance()->gcGenerationsEnabled()) {
    // No population-trend signal to gate on at all - see this method's own header comment for why
    // that means "always true" here.
    return true;
  }
  double seconds_to_oom = LivenessTracker::instance()->secondsToOOM();
  // isUrgent() is called unconditionally, not short-circuited behind _urgent_search_spent: it is
  // what maintains the latch/release counter, so skipping it would freeze the episode state (see
  // _urgent_latched).
  bool urgent = isUrgent();
  if (urgent && !_urgent_search_spent) {
    // Heap-wide floor is rising fast enough that OOM is imminent - don't wait for a specific klass
    // to clear selectLeakCandidates()'s own per-klass ring-fill/hysteresis gate; see
    // OOM_URGENT_THRESHOLD_S's own comment (referenceChains.h) for why that gate alone is too slow
    // here.
    TEST_LOG_SUMMARY("ReferenceChainTracker::hasLeakSignal -> true (urgent, "
             "secondsToOOM=%.1f)",
             seconds_to_oom);
    return true;
  }
  KlassCandidate probe[1];
  int n = LivenessTracker::instance()->selectLeakCandidates(probe, 1);
  TEST_LOG_SUMMARY("ReferenceChainTracker::hasLeakSignal -> %s (secondsToOOM=%.1f, "
           "candidates=%d, urgent=%d, urgentSearchSpent=%d)",
           n > 0 ? "true" : "false", seconds_to_oom, n, urgent,
           _urgent_search_spent);
  return n > 0;
}

bool ReferenceChainTracker::canAffordNewSearch(u64 now_ns) {
  if (!_safepoint_pain_budget.canStartNow(now_ns)) {
    TEST_LOG_SUMMARY("ReferenceChainTracker::canAffordNewSearch blocked by "
             "safepoint_pain_budget balance=%.1fms refill_rate=%.4f",
             _safepoint_pain_budget.balanceMs(now_ns),
             _pain_budget_refill_rate);
    return false; // still cooling down from the last search's own cost
  }
  return hasLeakSignal();
}

// Search restart (this class's own header comment). Called only from shouldRunPass() once
// canAffordNewSearch() has approved it, immediately before returning true for this same iteration -
// runPass() then sees _search_started == false and takes the first-pass branch, exactly like a
// brand-new tracker.
void ReferenceChainTracker::restartSearch() {
  // Only called once shouldRunPass() has confirmed _tags_released - never while a prior search's
  // release might still be pending (see _tags_released's own comment): resetting _next_tag to 1 /
  // the frontier table below while some object could still hold this search's now- ambiguous tag
  // would let the restarted search's fresh tags collide with it.
  assert(_tags_released &&
         "restartSearch() must not run before releaseSearchTags() has "
         "confirmed every live tag was cleared");

  // The finishing search's accumulated safepoint cost is spent by the terminal restart gate in
  // shouldRunPass() BEFORE it calls this (see the gate's comment: the gate must see the finished
  // search's cost), so no spend happens here.

  if (_frontier != nullptr) {
    _frontier->resetForRestart();
  }
  _next_tag = 1;
  // Hop-edge label cache: keyed by raw class tags, which survive a restart (the shared class-tag
  // allocator is deliberately not reset - see this method's own declaration comment) - but the
  // frontier entries referencing them do not, and a restart is the natural bounded clear point for
  // a cache capped by HOP_LABEL_CLASS_CACHE_CAP wholesale.
  _hop_label_cache.clear();
  // The shared class-tag counter (classTagAllocator.h)/_class_tags intentionally untouched - see
  // this method's own declaration comment (referenceChains.h).

  _search_started = false;
  store(_search_state, (u8)SearchState::RUNNING);
  store(_abandon_reason, (u8)SearchAbandonReason::NONE);
  store(_search_start_ns, (u64)0);
  _pending_expand.clear();
  _priority_expand.clear();
  _priority_expand_set.clear();
  _static_anchor_fifo.clear();
  _static_anchor_fifo_set.clear();
  _static_anchor_fifo_klass_counts.clear();
  _static_anchor_index.clear();
  _static_anchor_own_class_tags.clear();
  _static_anchor_index_tags.clear();
  _anchor_container_cursor = 0;
  _anchor_other_cursor = 0;
  // Fresh lane: nothing admits before the search does, so nothing can have a pending first look
  // either.
  _static_anchor_fresh_queue.clear();
  // Discovered-instance tags are FRONTIER tags - the reset above just invalidated every one of them
  // (fresh tags restart from 1).
  memset(_candidate_discovered_tags, 0, sizeof(_candidate_discovered_tags));
  memset(_candidate_discovered_count, 0, sizeof(_candidate_discovered_count));
  // Both keyed by frontier tags this restart is about to invalidate (fresh tags start again from 1)
  // - a stale entry surviving past a restart would be compared against whatever unrelated object
  // the new search has since reassigned that tag to.
  _leak_signature_totals.clear();
  _leak_signature_prev_totals.clear();
  _leak_parent_fanout.clear();
  _leak_tags_assigned = 0;
  _leak_tags_resolved = 0;
  _last_pass_gc_finish_epoch = 0;
  store(_last_pass_ns, (u64)0);
  store(_passes_run, 0);
  // Reset back to their just-constructed values (0 / -1) like every other per-search field this
  // method touches: resolveLoadedClasses() and admitStaticFieldRoots() must both run
  // unconditionally on the restarted search's first pass, exactly as they do for a brand-new
  // tracker.
  _last_resolved_class_count = 0;
  _last_static_field_class_count = -1;
  // _resolved_chains is intentionally left intact: a chain resolved by the finishing search stays
  // cached (and keeps being re-emitted on every dump) across the restart, since it describes a
  // sample that is still live.
}

void ReferenceChainTracker::resetSearchStateForTest(jvmtiEnv *jvmti,
                                                     JNIEnv *jni) {
  // Every field touched below is otherwise only ever mutated by the BFS thread itself
  // (threadLoop()/runPass()/pollWatchedTargets()) - without stopping it first, a pass already in
  // flight on that thread can observe this reset only partially, or overwrite it right back (e.g.
  // finish a pass that was already headed for SearchState::ABANDONED after this method has just
  // forced SearchState::RUNNING below), a race found in practice, not just in theory.
  stopThread();

  // Clear every live tag this search still holds before resetting - the same ordering
  // restartSearch() itself requires (its own assert), so a stale tag from whatever search a
  // previous test left running cannot collide with the fresh search's own tags once _next_tag is
  // rewound below.
  if (jvmti != nullptr && jni != nullptr) {
    releaseSearchTags(jvmti, jni);
  }
  _tags_released = true;

  _safepoint_pain_budget.spend(_search_pain_ms);
  _search_pain_ms = 0;
  // Reset the pain budget entirely so a fresh test starts from zero debt, independent of how much
  // wall-clock time has elapsed since the last test's spend().
  _safepoint_pain_budget = PainBudget(_pain_budget_refill_rate);
  // Mirror the reset for the non-safepoint budget - same test-isolation rationale as
  // _safepoint_pain_budget above.
  _cpu_pain_budget = PainBudget(_pain_budget_refill_rate);
  // Same test-isolation rationale: a latched urgency episode left behind by an earlier test would
  // otherwise deny this one its own urgency-authorized search (see _urgent_search_spent).
  _urgent_latched = false;
  _urgent_release_ticks = 0;
  _urgent_search_spent = false;

  if (_frontier != nullptr) {
    // Rebuilds the table at this test's own _configured_frontier_cap, undoing any smaller framecap=
    // an earlier test left it permanently sized at (this class's own header comment on
    // @TestMethodOrder) - restartSearch()'s production path only calls the cheaper
    // resetForRestart() since it never needs to change the cap mid-JVM.
    _frontier->resetCapacityForTest(_configured_frontier_cap);
  }
  _next_tag = 1;

  _search_started = false;
  store(_search_state, (u8)SearchState::RUNNING);
  store(_abandon_reason, (u8)SearchAbandonReason::NONE);
  store(_search_start_ns, (u64)0);
  _pending_expand.clear();
  _priority_expand.clear();
  _priority_expand_set.clear();
  _static_anchor_fifo.clear();
  _static_anchor_fifo_set.clear();
  _static_anchor_fifo_klass_counts.clear();
  _static_anchor_index.clear();
  _static_anchor_own_class_tags.clear();
  _static_anchor_index_tags.clear();
  _anchor_container_cursor = 0;
  _anchor_other_cursor = 0;
  _static_anchor_fresh_queue.clear();
  // Same stale-frontier-tag hygiene as restartSearch() (see its comment): discovered tags are
  // frontier tags, invalid across the test reset just as across a restart.
  memset(_candidate_discovered_tags, 0, sizeof(_candidate_discovered_tags));
  memset(_candidate_discovered_count, 0, sizeof(_candidate_discovered_count));
  // Test-only extra: production restartSearch() keeps _class_shape_cache (class tags are
  // JVM-lifetime-stable there), but test scenarios script class-tag values directly and a later
  // test can reuse an earlier one for a different mock class - clear the cache between tests.
  _class_shape_cache.clear();
  // Same reset rationale as restartSearch()'s own comment.
  _leak_signature_totals.clear();
  _leak_signature_prev_totals.clear();
  _leak_parent_fanout.clear();
  _leak_tags_assigned = 0;
  _leak_tags_resolved = 0;
  _last_pass_gc_finish_epoch = 0;
  store(_last_pass_ns, (u64)0);
  store(_passes_run, 0);
  _passes_since_last_progress = 0;
  _passes_since_last_candidate_progress = 0;
  _last_candidate_progress_mark = 0;
  _canary_backoff_mult = 1;
  _canary_pass_ema_ms = 0;
  _last_canary_pass_ns = 0;
  _canary_stuck_restart_count = 0;
  // Same "just-constructed values" contract resetForRestart() already documents for these two
  // fields - without it, a prior test's fully-swept (or partially-swept) state survives in this
  // process-wide singleton (ReferenceChainTracker::instance()) and can wrongly skip
  // admitStaticFieldRoots() entirely on this test's first pass if its resolved class count happens
  // to match whatever an earlier test last left behind (found via a real gtest-suite-order failure,
  // not hypothetical).
  _last_resolved_class_count = 0;
  _last_static_field_class_count = -1;
  _static_field_sweep_cursor = 0;
  _static_field_sweep_cycle_truncated = false;
  _candidate_count = 0;
  _candidate_found_bits = 0;
  memset(_candidate_discovered_count, 0, sizeof(_candidate_discovered_count));
  memset(_candidate_qualifying_tid_count, 0,
         sizeof(_candidate_qualifying_tid_count));
  // _candidate_parent_tags/_candidate_referrer_klasses/_candidate_depths will be filled at pruning
  // time.
  _resolved_chains_lock.lock();
  _resolved_chains.clear();
  _resolved_chains_lock.unlock();
  _pending_abandoned_events_lock.lock();
  _pending_abandoned_events.clear();
  _pending_abandoned_events_lock.unlock();

  // Restart the BFS thread against this freshly reset state - startThread() itself clears
  // _abort_pass_requested, so the new thread's very first pass is not instantly aborted by the flag
  // stopThread() just set above.
  startThread();
}

long ReferenceChainTracker::pendingExpandPositionForTest(jlong tag) const {
  if (tag == 0) {
    return -2;
  }
  // _priority_expand drains first (expandFrontier()'s own comment), so its entries are reported as
  // coming before _pending_expand's.
  long pos = 0;
  for (jlong queued : _priority_expand) {
    if (queued == tag) {
      return pos;
    }
    pos++;
  }
  for (jlong queued : _pending_expand) {
    if (queued == tag) {
      return pos;
    }
    pos++;
  }
  return -1;
}

size_t ReferenceChainTracker::pendingExpandSizeForTest() const {
  return _pending_expand.size() + _priority_expand.size();
}

jlong ReferenceChainTracker::tagObject(jvmtiEnv *jvmti, jobject obj) {
  assert(!t_inGCCallback &&
         "SetTag is a JVMTI Heap-category call and must not be made from "
         "GarbageCollectionStart/Finish");
  jlong tag = nextTag();
  jvmtiError err = jvmti->SetTag(obj, tag);
  if (err != JVMTI_ERROR_NONE) {
    return 0;
  }
  return tag;
}

jlong ReferenceChainTracker::getTag(jvmtiEnv *jvmti, jobject obj) {
  assert(!t_inGCCallback &&
         "GetTag is a JVMTI Heap-category call and must not be made from "
         "GarbageCollectionStart/Finish");
  jlong tag = 0;
  jvmtiError err = jvmti->GetTag(obj, &tag);
  if (err != JVMTI_ERROR_NONE) {
    return 0;
  }
  return tag;
}

void ReferenceChainTracker::clearTag(jvmtiEnv *jvmti, jobject obj) {
  assert(!t_inGCCallback &&
         "SetTag is a JVMTI Heap-category call and must not be made from "
         "GarbageCollectionStart/Finish");
  jvmti->SetTag(obj, 0);
}

jlong ReferenceChainTracker::tagAsRootForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                               jobject obj) {
  if (_frontier == nullptr || jvmti == nullptr || jni == nullptr ||
      obj == nullptr) {
    TEST_LOG_SUMMARY("ReferenceChainTracker::tagAsRootForTest refused: "
             "frontier=%p jvmti=%p jni=%p obj=%p",
             (void *)_frontier, (void *)jvmti, (void *)jni, (void *)obj);
    return 0;
  }
  // Resolves the klass_id via the same GetClassSignature + normalizeClassSignature +
  // Profiler::lookupClass sequence every consumer in this subsystem uses
  // (ObjectSampler::recordAllocation(), LivenessTracker::resolveKlassId(), resolveClassMap() above)
  // - the id space is load-bearing here: pollWatchedTargets() matches frontier entries against leak
  // candidates by klass_id, and the candidate ids come from that signature-notation space
  // (Class.getName()'s dot form is a DIFFERENT StringDictionary key - see
  // find-klass-id-notation-mismatch).
  u32 klass_id = 0;
  jclass klass = jni->GetObjectClass(obj);
  char *class_name = nullptr;
  if (jvmti->GetClassSignature(klass, &class_name, nullptr) ==
          JVMTI_ERROR_NONE &&
      class_name != nullptr) {
    const char *name_slice = nullptr;
    size_t name_len = 0;
    if (ObjectSampler::normalizeClassSignature(class_name, &name_slice,
                                                &name_len)) {
      int id = Profiler::instance()->lookupClass(name_slice, name_len);
      if (id != -1) {
        klass_id = (u32)id;
      }
    }
    jvmti->Deallocate((unsigned char *)class_name);
  }
  jni->DeleteLocalRef(klass);

  // Tags `obj` and inserts it as a frontier root (parent_tag=0, depth=0), exactly the convention
  // runPass()'s heap-root callback path already uses (referenceChains.cpp's
  // heapReferenceCallback(), referrer_tag_ptr == nullptr branch) - this lets a test drive the real
  // BFS/chain- reconstruction logic (runPass()/pollWatchedTargets()/buildChainEvent()) against a
  // known, caller-chosen live object, decoupled from whether the real root-seeded walk or
  // LivenessTracker's probabilistic sampler happens to reach/select it on its own.
  jlong tag = tagObject(jvmti, obj);
  if (tag == 0) {
    TEST_LOG_SUMMARY("ReferenceChainTracker::tagAsRootForTest refused: "
             "tagObject (SetTag) failed");
    return 0;
  }
  if (!_frontier->insert(tag, 0, klass_id, 0)) {
    TEST_LOG_SUMMARY("ReferenceChainTracker::tagAsRootForTest refused: "
             "frontier insert failed tag=%lld klass_id=%u",
             (long long)tag, klass_id);
    clearTag(jvmti, obj);
    return 0;
  }
  // Discovery recording for this seam's decoupling contract.
  if (_candidate_count > 0) {
    recordDiscoveredInstance(klass_id, tag, false);
  }
  return tag;
}
