/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "referenceChains.h"
#include "common.h"
#include "counters.h"
#include "livenessTracker.h"
#include "log.h"
#include "objectSampler.h"
#include "os.h"
#include "profiler.h"
#include "tsc.h"
#include "vmEntry.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>

// ---------------------------------------------------------------------------
// FrontierTable (tag-indexed frontier metadata table)
// ---------------------------------------------------------------------------

FrontierTable::FrontierTable(int max_cap)
    : _table_size(0), _table_cap(0), _table_max_cap(std::max(max_cap, 0)),
      _table(nullptr) {
  _table_cap = std::min(INITIAL_TABLE_CAPACITY, _table_max_cap);
  if (_table_cap > 0) {
    _table = (FrontierEntry *)calloc(_table_cap, sizeof(FrontierEntry));
    if (_table == nullptr) {
      _table_cap = 0;
    }
  }
}

FrontierTable::~FrontierTable() { free(_table); }

void FrontierTable::resetCapacityForTest(int max_cap) {
  _table_lock.lock();
  free(_table);
  _table = nullptr;
  _table_max_cap = std::max(max_cap, 0);
  _table_cap = std::min(INITIAL_TABLE_CAPACITY, _table_max_cap);
  if (_table_cap > 0) {
    _table = (FrontierEntry *)calloc(_table_cap, sizeof(FrontierEntry));
    if (_table == nullptr) {
      _table_cap = 0;
    }
  }
  _table_size.store(0, std::memory_order_relaxed);
  _table_lock.unlock();
}

bool FrontierTable::growLocked(int required_cap) {
  if (required_cap <= _table_cap) {
    return true;
  }
  if (_table_cap >= _table_max_cap) {
    return false;
  }

  int newcap = _table_cap;
  while (newcap < required_cap && newcap < _table_max_cap) {
    newcap = newcap == 0 ? std::min(INITIAL_TABLE_CAPACITY, _table_max_cap)
                          : std::min(newcap * 2, _table_max_cap);
  }
  if (newcap <= _table_cap) {
    return false;
  }

  FrontierEntry *tmp =
      (FrontierEntry *)realloc(_table, sizeof(FrontierEntry) * newcap);
  if (tmp == nullptr) {
    Log::debug(
        "ReferenceChains: frontier table resize to %d entries failed", newcap);
    return false;
  }
  // realloc() does not zero the newly grown region - clear it so lookup()
  // never returns garbage state for a slot that hasn't been inserted yet.
  memset(tmp + _table_cap, 0, sizeof(FrontierEntry) * (newcap - _table_cap));
  _table = tmp;
  _table_cap = newcap;
  return _table_cap >= required_cap;
}

bool FrontierTable::insert(jlong tag, jlong parent_tag, u32 referrer_klass,
                            u32 depth, u8 state) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return false;
  }
  int idx = (int)(tag - 1);

  // Exclusive lock for the whole write (growLocked() already requires it) -
  // a shared lock here would not exclude lookup()'s own shared-mode read of
  // the same slot, letting a concurrent reader observe a torn entry.
  _table_lock.lock();
  if (idx >= _table_cap && !growLocked(idx + 1)) {
    _table_lock.unlock();
    Log::debug("ReferenceChains: frontier table capacity exhausted "
               "(cap=%d, max=%d, tag=%lld)",
               _table_cap, _table_max_cap, (long long)tag);
    return false;
  }
  _table[idx].parent_tag = parent_tag;
  _table[idx].referrer_klass = referrer_klass;
  _table[idx].depth = depth;
  _table[idx].state = state;
  _table_lock.unlock();

  int sz = _table_size.load(std::memory_order_relaxed);
  while (sz < idx + 1 &&
         !_table_size.compare_exchange_weak(sz, idx + 1,
                                             std::memory_order_relaxed)) {
    // sz reloaded with the current value by compare_exchange_weak on
    // failure; retry until either this thread wins or another thread
    // already advanced _table_size past idx + 1.
  }
  return true;
}

bool FrontierTable::lookup(jlong tag, FrontierEntry *out) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return false;
  }
  int idx = (int)(tag - 1);

  bool found = false;
  _table_lock.lockShared();
  if (idx < _table_size) {
    *out = _table[idx];
    found = true;
  }
  _table_lock.unlockShared();
  return found;
}

void FrontierTable::clear(jlong tag) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return;
  }
  int idx = (int)(tag - 1);

  // Exclusive lock: this mutates a slot lookup() may be reading concurrently
  // under its own shared lock (see insert()'s own comment above).
  _table_lock.lock();
  if (idx < _table_size) {
    _table[idx].state = FrontierEntryState::ABANDONED;
  }
  _table_lock.unlock();
}

void FrontierTable::markEdge(jlong tag) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return;
  }
  int idx = (int)(tag - 1);

  _table_lock.lock();
  if (idx < _table_size) {
    _table[idx].state = FrontierEntryState::EDGE;
  }
  _table_lock.unlock();
}

void FrontierTable::markExpanded(jlong tag) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return;
  }
  int idx = (int)(tag - 1);

  _table_lock.lock();
  if (idx < _table_size) {
    _table[idx].state = FrontierEntryState::EXPANDED;
  }
  _table_lock.unlock();
}

bool FrontierTable::reconstructChain(jlong target_tag,
                                      std::vector<u32> *out_chain) {
  FrontierEntry entry{};
  if (!lookup(target_tag, &entry)) {
    return false;
  }

  std::vector<u32> chain;
  jlong tag = target_tag;
  // Bounded by maxCapacity(): every tag maps to a distinct slot (this table's
  // "tags/slots are never reused" invariant, see the class comment above),
  // so a well-formed parent_tag chain can visit at most maxCapacity() slots
  // before either reaching parent_tag == 0 or repeating a slot.
  for (int hops = 0; hops <= maxCapacity() && tag != 0; hops++) {
    if (!lookup(tag, &entry)) {
      // parent_tag pointed at a tag that was never inserted - should not
      // happen for a chain built entirely within one BFS pass, but do not
      // fabricate a partial chain silently.
      return false;
    }
    chain.push_back(entry.referrer_klass);
    markEdge(tag);
    tag = entry.parent_tag;
  }
  if (tag != 0) {
    // Ran past the defensive hop bound without reaching a root-attached
    // entry (parent_tag == 0) - a corrupted/cyclic chain. Report failure
    // rather than returning a truncated, possibly-misleading chain.
    return false;
  }

  *out_chain = std::move(chain);
  return true;
}

// ---------------------------------------------------------------------------
// ReferenceChainTracker
// ---------------------------------------------------------------------------

// Marks the calling thread as executing inside the GarbageCollectionStart/
// Finish JVMTI callback for the duration of the guard's lifetime. Used by the
// tag helpers below as a debug-only self-consistency check that this class
// never issues a Heap-category JVMTI call (SetTag/GetTag/...) from a context
// where the JVMTI spec forbids it (see referenceChains.h). Thread-local
// because the JVMTI spec only guarantees the callback runs on the VM thread
// delivering the event, and this must not leak across threads.
static thread_local bool t_inGCCallback = false;

namespace {
class GCCallbackGuard {
public:
  GCCallbackGuard() { t_inGCCallback = true; }
  ~GCCallbackGuard() { t_inGCCallback = false; }
};
} // namespace

Error ReferenceChainTracker::start(Arguments &args) {
  _enabled = args._reference_chains;

  if (!_enabled) {
    Log::info("Reference chain tracking is disabled");
    return Error::OK;
  }

  Log::info("Reference chain tracking is enabled (hops=%d, budget=%d, "
            "ttl=%ldms, framecap=%d, pausetarget=%ldms, painbudget=%d%%)",
            args._reference_chains_hop_cap, args._reference_chains_budget,
            args._reference_chains_ttl_ms, args._reference_chains_frontier_cap,
            args._reference_chains_pause_target_ms,
            args._reference_chains_pain_budget_percent);

  // Like LivenessTracker's table (livenessTracker.cpp:225-232), construct the
  // frontier table once and keep it across repeated start()/stop() cycles -
  // do not reallocate on a second start() with a possibly different cap, for
  // the same reason LivenessTracker keeps its first-initialize() result.
  // Recorded unconditionally, even on a start() call that finds _frontier
  // already constructed (see _configured_frontier_cap's own comment) - this
  // is what resetSearchStateForTest() rebuilds the table at, undoing
  // whatever cap an earlier test in this same JVM happened to construct it
  // with.
  _configured_frontier_cap = args._reference_chains_frontier_cap;
  if (_frontier == nullptr) {
    _frontier = new FrontierTable(_configured_frontier_cap);
  }

  _hop_cap = args._reference_chains_hop_cap;
  _budget = args._reference_chains_budget;
  // 0 (unset) auto-scales from _budget instead of falling back to it plainly
  // - see this field's own comment (referenceChains.h) for why a
  // steady-state per-pass budget is the wrong size for the first pass.
  _first_pass_budget = args._reference_chains_first_pass_budget > 0
                            ? args._reference_chains_first_pass_budget
                            : std::min(_budget * AUTO_FIRST_PASS_BUDGET_MULTIPLIER,
                                       AUTO_FIRST_PASS_BUDGET_CAP);
  _ttl_ms = args._reference_chains_ttl_ms;

  // Pause-time pacing controller: (re)seed the controller's ceiling and the
  // adaptive values it drives. _effective_budget/_effective_cadence_ns start
  // exactly at their pre-pacing-controller fixed-constant equivalents
  // (_budget/PASS_CADENCE_NS) so a tracker that has not yet measured a pass
  // behaves identically to before the controller was added - updatePacing()
  // only moves them once a real pass duration is
  // available. _pause_pid is reconstructed (not just reset()) because its
  // target is only known now, from args - same reason RateLimiter::start()
  // reconstructs its own _pid rather than mutating it in place.
  _pause_target_ms = args._reference_chains_pause_target_ms;
  _effective_budget = _budget;
  _effective_cadence_ns = PASS_CADENCE_NS;
  _pause_pid = PidController((u64)std::max(_pause_target_ms, 0L),
                              10,  // proportional gain: reacts to a single
                                   // pass's over/under-ceiling error without
                                   // needing many passes to notice - a
                                   // duration-ms error is typically single/
                                   // low-double-digit in magnitude (unlike
                                   // the shared triple's event-count scale),
                                   // so a smaller P keeps a one-pass
                                   // overshoot from swinging the budget by
                                   // more than a modest fraction of itself
                              1,   // integral gain: small and round -
                                   // pidController.cpp's `_integral_value`
                                   // has no built-in clamp, and this
                                   // controller is invoked once per BFS pass
                                   // rather than on the other three usages'
                                   // roughly-periodic one-call-per-second
                                   // cadence, so windup accumulates faster
                                   // per wall-clock second than it does there
                              2,   // derivative gain: small, matching the
                                   // shared triple's own "the derivational
                                   // gain is rather small" rationale
                                   // (objectSampler.cpp) - a single slow/
                                   // fast pass should not itself trigger a
                                   // large swing
                              1,   // sampling_window=1: one compute() call
                                   // *is* one pass, not a fixed real-time
                                   // window like the other three usages
                                   // assume (see _pause_pid's own comment)
                              5.0  // cutoff_secs: a round value, halved from
                                   // the shared triple's own "15" since a
                                   // pass-scoped signal is naturally
                                   // noisier per-call than a roughly-1s-
                                   // cadence one
  );

  // Search restart (this class's own header comment): (re)seed _pain_budget
  // from the configured refill rate, mirroring _pause_pid's own
  // reconstruct-in-start() pattern above. A search's already-accumulated
  // _search_pain_ms is deliberately left untouched here - only restartSearch()
  // spends it, so a start()/stop() cycle mid-search (if that ever happens)
  // does not erase cost the current search has already incurred.
  _pain_budget = PainBudget(
      std::max(args._reference_chains_pain_budget_percent, 0) / 100.0);

  // Lazy-enable, matching LivenessTracker::start() (livenessTracker.cpp:194-196):
  // the GC callbacks are wired unconditionally in vmEntry.cpp, but the events
  // themselves are only turned on for this JVMTI env when the flag is on.
  jvmtiEnv *jvmti = VM::jvmti();
  jvmti->SetEventNotificationMode(
      JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_START, nullptr);
  jvmti->SetEventNotificationMode(
      JVMTI_ENABLE, JVMTI_EVENT_GARBAGE_COLLECTION_FINISH, nullptr);

  // Deliberately does NOT create the BFS thread (threadEntry()/threadLoop()
  // below) here - threadLoop()'s VM::attachThread() call dereferences
  // VM::_vm unconditionally (vmEntry.h:191-195) and crashes if the VM is not
  // yet attached, which is exactly the case in this file's own gtest binary
  // (referenceChains_ut.cpp calls start() directly with no live JVM).
  // startThread() (referenceChains.h) owns spawning the thread instead, and
  // is called from Profiler::start() (profiler.cpp) immediately after this
  // method returns Error::OK - by that point in the real profiler lifecycle
  // the JVM/JVMTI environment is already fully up, so VM::attachThread() is
  // safe there. runPass() - the actual BFS engine - does not depend on the
  // thread either way and is called directly by this file's own tests.

  return Error::OK;
}

void ReferenceChainTracker::stop() {
  if (!_enabled) {
    return;
  }
  Log::info("Reference chain tracking stopped");

  // Do not disable GC notifications here - LivenessTracker follows the same
  // rule (livenessTracker.cpp:209-210) since the JVMTI env and its tracker
  // singletons are expected to survive across multiple start/stop recording
  // cycles. The BFS thread itself is stopped separately, by
  // Profiler::stop() calling stopThread() (profiler.cpp) - mirroring
  // start()'s split between this method and startThread().
}

void ReferenceChainTracker::startThread() {
  if (!_enabled || _running) {
    return;
  }
  // Create the thread (into a local pthread_t) and only publish _thread /
  // flip _running=true once pthread_create() has actually succeeded.
  // onGCFinish() (GC callback thread) guards its pthread_kill(_thread, ...)
  // call on _running alone - GC-finish notifications are already enabled by
  // start() before this method runs, so a GC-finish callback firing between
  // "_running=true" and pthread_create() actually initializing _thread would
  // previously call pthread_kill() on a still value-initialized (0) or
  // stale/joined pthread_t, which is undefined behavior. Publishing _thread
  // before _running closes that window.
  // Reset from any previous stopThread() call - a dynamic-attach profiler
  // can go through multiple start()/stop() cycles in one JVM lifetime (this
  // class's own start()/stop() header comments), and a stale abort request
  // left set from the prior cycle would make heapReferenceCallback() abort
  // this new cycle's very first pass instantly.
  _abort_pass_requested.store(false, std::memory_order_relaxed);

  pthread_t thread;
  if (pthread_create(&thread, NULL, threadEntry, this) != 0) {
    Log::warn("Unable to create ReferenceChains BFS thread");
    return;
  }
  _thread = thread;
  _running = true;
}

void ReferenceChainTracker::stopThread() {
  if (!_running) {
    return;
  }
  _running = false;
  // Ask any in-flight JVMTI FollowReferences walk (heapReferenceCallback())
  // to abort at its next callback invocation - set before pthread_kill()
  // below, since that signal alone cannot interrupt a call already inside
  // the JVM/JVMTI implementation.
  _abort_pass_requested.store(true, std::memory_order_relaxed);
  // Same wake-then-join shape as BaseWallClock::stop() (wallClock.cpp:324-333):
  // pthread_kill(WAKEUP_SIGNAL) interrupts threadLoop()'s OS::sleep() early
  // (WAKEUP_SIGNAL/SIGIO is installed with a no-op handler unconditionally
  // in vmEntry.cpp, so this signal never terminates the thread) so it
  // re-checks _running and exits promptly rather than waiting out the rest
  // of the current sleep interval.
  pthread_kill(_thread, WAKEUP_SIGNAL);
  int res = pthread_join(_thread, NULL);
  if (res != 0) {
    Log::warn("Unable to join ReferenceChains BFS thread on stop %d", res);
  }
}

// Not yet started by anything (see start()'s comment above for why) - but
// now implements the real scheduling loop the design doc asks for, matching
// J9WallClock's attach/park/detach lifecycle (j9WallClock.cpp:28-57): each
// wake (adaptive cadence, or earlier via onGCFinish()'s pthread_kill below)
// checks shouldRunPass() and calls runPass() if it says so. The pause-time
// pacing controller sleeps for _effective_cadence_ns rather than the fixed
// PASS_CADENCE_NS, so a
// controller-driven relaxed cadence (updatePacing()) actually shortens how
// long an idle, no-GC-event search waits between passes, not just
// shouldRunPass()'s own comparison.
void ReferenceChainTracker::threadLoop() {
  struct Cleanup {
    ~Cleanup() { VM::detachThread(); }
  } cleanup;
  JNIEnv *jni = VM::attachThread("java-profiler ReferenceChains");
  jvmtiEnv *jvmti = VM::jvmti();
  if (jni == nullptr) {
    // AttachCurrentThreadAsDaemon() failed - mirror pollWatchedTargets()'s
    // own jni==nullptr early return rather than letting a null JNIEnv flow
    // into runPass()/resolveLoadedClasses()/expandFrontier()/
    // releaseSearchTags() below: those only guard their DeleteLocalRef()
    // calls on `jni != nullptr`, so without this check every
    // GetLoadedClasses()/GetObjectsWithTags() local ref returned on this
    // (permanently un-attached) thread would leak for the rest of the
    // process's lifetime. Nothing this thread does is safe without a live
    // JNIEnv, so give up on the whole loop rather than retrying per
    // iteration - detachThread() in Cleanup is a safe no-op if attach never
    // actually succeeded.
    Log::warn("ReferenceChains: VM::attachThread failed; BFS thread exiting");
    return;
  }
  TEST_LOG("ReferenceChainTracker::threadLoop started, cadence=%lluns", (unsigned long long)_effective_cadence_ns);

  int iteration = 0;
  u64 last_observed_gc_finish_epoch = gcFinishEpoch();
  while (_running) {
    // Fixed ~1s cadence, no early wake on GC (see onGCFinish()'s own
    // comment) - stopThread() still interrupts this via its own
    // pthread_kill so shutdown stays prompt.
    OS::sleep(_effective_cadence_ns);
    if (!_running) {
      break;
    }

    u64 gc_finish_epoch = gcFinishEpoch();
    bool new_gc_since_last_wake = gc_finish_epoch != last_observed_gc_finish_epoch;
    last_observed_gc_finish_epoch = gc_finish_epoch;

    // Third trigger for LivenessTracker::cleanup_table() (see
    // LivenessTracker::maybeForceCleanup()'s own comment): track()'s
    // table-overflow branch and flush_table()'s JFR cadence can both starve
    // under ObjectSampler's PID-controlled sampling interval, leaving
    // hasLeakSignal() below stuck on a stale population history no matter
    // how long a real leak keeps growing. This thread already wakes every
    // ~1s with a live JNIEnv, so it doubles as that fallback tick - cheap,
    // and a no-op unless 30s have actually elapsed with a GC in between (see
    // that method for the exact gate).
    u64 wake_now_ns = OS::nanotime();
    LivenessTracker::instance()->maybeForceCleanup(wake_now_ns);

    // Steady-state fast path: an active search is just waiting on the next
    // trigger. If no GC happened since the last wake, there's nothing new
    // for shouldRunPass()'s own gc-epoch/cadence checks to find - skip the
    // whole iteration (no probe, no logging) rather than re-deriving the
    // same "nothing to do" answer every cadence tick. Only applies once a
    // search has actually started and is still RUNNING - the
    // not-yet-started and restart-gating branches below need every wake
    // regardless of GC activity (shouldRunPass()'s own comment).
    if (_search_started && _search_state == SearchState::RUNNING && !new_gc_since_last_wake) {
      continue;
    }

    // Generation-count-slope check first, before any of the more expensive
    // work below: if LivenessTracker's population trends show nothing
    // growing, a GC by itself isn't a reason to run a pass. Same
    // hasLeakSignal() probe canAffordNewSearch() uses for restarts, and
    // like that method, always true when LivenessTracker::gcGenerationsEnabled()
    // is off (no signal to gate on) or before a search has ever started
    // (nothing to compare a slope against yet).
    if (_search_started && _search_state == SearchState::RUNNING && !hasLeakSignal()) {
      continue;
    }

    u64 now_ns = OS::nanotime();
    bool should_run = shouldRunPass(now_ns);
    // Log the loop state only when a pass is actually going to run - the idle
    // wakes (should_run == false) are the common steady state and logging them
    // every second is pure noise.
    if (should_run) {
      TEST_LOG("ReferenceChainTracker::threadLoop iteration=%d shouldRunPass=%d searchState=%d "
               "passesRun=%d effectiveCadenceNs=%llu effectiveBudget=%d gcFinishEpoch=%llu "
               "lastPassGcFinishEpoch=%llu nowMinusLastPassNs=%llu",
               ++iteration, should_run, (int)_search_state, _passes_run,
               (unsigned long long)_effective_cadence_ns, _effective_budget,
               (unsigned long long)gcFinishEpoch(), (unsigned long long)_last_pass_gc_finish_epoch,
               (unsigned long long)(now_ns - _last_pass_ns));
      runPass(jvmti, jni, nullptr);
    }
    // Target-selection bridging step: poll once per scheduling cycle, after
    // runPass() - so this poll always sees the most recent pass's tagging (see
    // pollWatchedTargets()'s own comment). Unconditional, not gated on
    // shouldRunPass()'s decision above: a candidate discovered by an
    // earlier pass may still be waiting for its first poll even on a cycle
    // where this cycle's own pass was skipped.
    pollWatchedTargets(jvmti, jni);
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
  // JVMTI spec: only Memory Management category calls (Allocate/Deallocate)
  // are allowed from inside this callback - nothing else may run here.
  GCCallbackGuard guard;
  atomicIncRelaxed(_gc_start_epoch, (u64)1);
}

void ReferenceChainTracker::onGCFinish() {
  if (!_enabled) {
    return;
  }
  GCCallbackGuard guard;
  // Design doc's Triggering section: GC callbacks are only a scheduling
  // *signal*, never a pass's execution vehicle (Heap-category JVMTI calls
  // are forbidden here - see this file's header comment). Deliberately just
  // bookkeeping - no pthread_kill/early wake here. threadLoop() below wakes
  // on its own fixed ~1s cadence and reads this epoch then; waking it early
  // on every GC gains at most ~1s of latency but, under any GC-heavy
  // workload, collapses the loop's cadence to GC frequency instead (each
  // early wake is itself a full iteration's worth of shouldRunPass()/
  // pollWatchedTargets() work), which is not worth the latency win.
  atomicIncRelaxed(_gc_finish_epoch, (u64)1);
}

bool ReferenceChainTracker::shouldRunPass(u64 now_ns) {
  if (!_search_started) {
    TEST_LOG("ReferenceChainTracker::shouldRunPass -> true (search not started yet)");
    return true; // nothing has run yet - always worth taking the first pass
  }
  if (_search_state != SearchState::RUNNING) {
    // Terminal outcome already reached (runPass()'s Termination section).
    if (!_tags_released) {
      // releaseSearchTags() failed to confirm every live tag this search
      // owned was actually cleared - restartSearch() must never run until
      // that is confirmed (see _tags_released's own comment), so return
      // true unconditionally here: that drives threadLoop() to call
      // runPass() again, whose terminal-state branch retries the release,
      // rather than letting canAffordNewSearch()/restartSearch() below run
      // ahead of it.
      TEST_LOG("ReferenceChainTracker::shouldRunPass -> true (retrying tag "
               "release before restart is allowed)");
      return true;
    }
    // Restart (this class's own header comment) if the pain budget has
    // drained and there is still (or again) a leak indication to chase -
    // canAffordNewSearch() is always true when LivenessTracker's population
    // trends are not in use at all, so this only ever changes behavior for a
    // search that already ran once.
    if (canAffordNewSearch(now_ns)) {
      restartSearch();
      TEST_LOG("ReferenceChainTracker::shouldRunPass -> true (restarting search)");
      return true;
    }
    // No log here: a terminal search waiting for a restart to become
    // warranted is the common idle state, re-evaluated every second, so
    // logging it is pure per-second noise (see threadLoop()).
    return false;
  }
  u64 gc_finish_epoch = gcFinishEpoch();
  if (gc_finish_epoch != _last_pass_gc_finish_epoch) {
    // Triggering section: "a GC just happened, a pass may be worth running
    // soon".
    TEST_LOG("ReferenceChainTracker::shouldRunPass -> true (gcFinishEpoch=%llu != "
             "lastPassGcFinishEpoch=%llu)",
             (unsigned long long)gc_finish_epoch,
             (unsigned long long)_last_pass_gc_finish_epoch);
    return true;
  }
  // Pause-time pacing controller: compares against _effective_cadence_ns, not
  // the fixed PASS_CADENCE_NS - see that
  // field's own comment (referenceChains.h) for how updatePacing() widens or
  // relaxes it from the measured pause-time signal.
  bool cadence_elapsed = now_ns - _last_pass_ns >= _effective_cadence_ns;
  // Only log when the cadence actually elapsed (a pass will run). The
  // not-yet-elapsed case is the common idle wake and logging it every second
  // is noise.
  if (cadence_elapsed) {
    TEST_LOG("ReferenceChainTracker::shouldRunPass -> true (now_ns=%llu last_pass_ns=%llu "
             "delta=%llu effectiveCadenceNs=%llu)",
             (unsigned long long)now_ns, (unsigned long long)_last_pass_ns,
             (unsigned long long)(now_ns - _last_pass_ns),
             (unsigned long long)_effective_cadence_ns);
  }
  return cadence_elapsed;
}

// Search restart gate (this class's own header comment). Deliberately a
// probe (max=1) rather than reusing pollWatchedTargets()'s own
// selectLeakCandidates() call - that one runs after runPass() in
// threadLoop()'s own iteration and needs the *list* to poll each candidate's
// tag; this only needs to know whether at least one exists.
bool ReferenceChainTracker::hasLeakSignal() {
  if (!LivenessTracker::instance()->gcGenerationsEnabled()) {
    // No population-trend signal to gate on at all - see this method's own
    // header comment for why that means "always true" here.
    return true;
  }
  KlassCandidate probe[1];
  return LivenessTracker::instance()->selectLeakCandidates(probe, 1) > 0;
}

bool ReferenceChainTracker::canAffordNewSearch(u64 now_ns) {
  if (!_pain_budget.canStartNow(now_ns)) {
    return false; // still cooling down from the last search's own cost
  }
  return hasLeakSignal();
}

// Search restart (this class's own header comment). Called only from
// shouldRunPass() once canAffordNewSearch() has approved it, immediately
// before returning true for this same iteration - runPass() then sees
// _search_started == false and takes the first-pass branch, exactly like a
// brand-new tracker.
void ReferenceChainTracker::restartSearch() {
  // Only called once shouldRunPass() has confirmed _tags_released - never
  // while a prior search's release might still be pending (see
  // _tags_released's own comment): resetting _next_tag to 1 / the frontier
  // table below while some object could still hold this search's now-
  // ambiguous tag would let the restarted search's fresh tags collide with
  // it.
  assert(_tags_released &&
         "restartSearch() must not run before releaseSearchTags() has "
         "confirmed every live tag was cleared");

  // Spend the finishing search's own cost before clearing the accumulator -
  // canAffordNewSearch()'s *next* call must see this search's cost, not a
  // reset-to-zero balance.
  _pain_budget.spend(_search_pain_ms);
  _search_pain_ms = 0;

  if (_frontier != nullptr) {
    _frontier->resetForRestart();
  }
  _next_tag = 1;
  // _next_class_tag_magnitude/_class_tags intentionally untouched - see this
  // method's own declaration comment (referenceChains.h).

  _search_started = false;
  store(_search_state, (u8)SearchState::RUNNING);
  store(_abandon_reason, (u8)SearchAbandonReason::NONE);
  store(_search_start_ns, (u64)0);
  _pending_expand.clear();
  _last_pass_gc_finish_epoch = 0;
  store(_last_pass_ns, (u64)0);
  store(_passes_run, 0);
  // _emitted_target_tags/_emitted_search_start_ns are left for
  // pollWatchedTargets() itself to clear, the next time it observes
  // _search_start_ns change (its own comment) - runPass() sets
  // _search_start_ns again on this restarted search's own first pass.
}

void ReferenceChainTracker::resetSearchStateForTest(jvmtiEnv *jvmti,
                                                     JNIEnv *jni) {
  // Every field touched below is otherwise only ever mutated by the BFS
  // thread itself (threadLoop()/runPass()/pollWatchedTargets()) - without
  // stopping it first, a pass already in flight on that thread can observe
  // this reset only partially, or overwrite it right back (e.g. finish a
  // pass that was already headed for SearchState::ABANDONED after this
  // method has just forced SearchState::RUNNING below), a race found in
  // practice, not just in theory. stopThread() (now that it can abort an
  // in-flight JVMTI walk promptly - see its own comment) makes this a cheap,
  // clean stop/reset/restart rather than an indefinite wait.
  stopThread();

  // Clear every live tag this search still holds before resetting - the
  // same ordering restartSearch() itself requires (its own assert), so a
  // stale tag from whatever search a previous test left running cannot
  // collide with the fresh search's own tags once _next_tag is rewound
  // below.
  if (jvmti != nullptr && jni != nullptr) {
    releaseSearchTags(jvmti, jni);
  }
  _tags_released = true;

  _pain_budget.spend(_search_pain_ms);
  _search_pain_ms = 0;

  if (_frontier != nullptr) {
    // Rebuilds the table at this test's own _configured_frontier_cap,
    // undoing any smaller framecap= an earlier test left it permanently
    // sized at (this class's own header comment on @TestMethodOrder) -
    // restartSearch()'s production path only calls the cheaper
    // resetForRestart() since it never needs to change the cap mid-JVM.
    _frontier->resetCapacityForTest(_configured_frontier_cap);
  }
  _next_tag = 1;

  _search_started = false;
  store(_search_state, (u8)SearchState::RUNNING);
  store(_abandon_reason, (u8)SearchAbandonReason::NONE);
  store(_search_start_ns, (u64)0);
  _pending_expand.clear();
  _last_pass_gc_finish_epoch = 0;
  store(_last_pass_ns, (u64)0);
  store(_passes_run, 0);

  // Unlike restartSearch(), which leaves these for pollWatchedTargets() to
  // notice the _search_start_ns change and clear naturally on its own next
  // call, this reset must take effect immediately - there is no next real
  // pass here to trigger that self-clear.
  _emitted_target_tags.clear();
  _emitted_search_start_ns = 0;

  _pending_chain_events_lock.lock();
  _pending_chain_events.clear();
  _pending_chain_events_lock.unlock();

  // Restart the BFS thread against this freshly reset state - startThread()
  // itself clears _abort_pass_requested, so the new thread's very first
  // pass is not instantly aborted by the flag stopThread() just set above.
  startThread();
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
    return 0;
  }
  // Resolves the klass_id the same way LivenessTracker::resolveKlassId()
  // does (GetObjectClass + Class.getName() + Profiler::lookupClass()) -
  // this is a test-only, off-hot-path call so caching _Class/_Class_getName
  // like LivenessTracker does is not worth the extra state.
  u32 klass_id = 0;
  jclass klass = jni->GetObjectClass(obj);
  jclass class_class = jni->FindClass("java/lang/Class");
  if (class_class != nullptr) {
    jmethodID get_name =
        jni->GetMethodID(class_class, "getName", "()Ljava/lang/String;");
    if (get_name != nullptr) {
      jstring name_str = (jstring)jni->CallObjectMethod(klass, get_name);
      if (name_str != nullptr) {
        const char *name = jni->GetStringUTFChars(name_str, nullptr);
        if (name != nullptr) {
          int id = Profiler::instance()->lookupClass(name, strlen(name));
          if (id > 0) {
            klass_id = (u32)id;
          }
          jni->ReleaseStringUTFChars(name_str, name);
        }
        jni->DeleteLocalRef(name_str);
      }
    }
    jni->DeleteLocalRef(class_class);
  }
  jni->DeleteLocalRef(klass);

  // Tags `obj` and inserts it as a frontier root (parent_tag=0, depth=0),
  // exactly the convention runPass()'s heap-root callback path already uses
  // (referenceChains.cpp's heapReferenceCallback(), referrer_tag_ptr ==
  // nullptr branch) - this lets a test drive the real BFS/chain-
  // reconstruction logic (runPass()/pollWatchedTargets()/buildChainEvent())
  // against a known, caller-chosen live object, decoupled from whether the
  // real root-seeded walk or LivenessTracker's probabilistic sampler happens
  // to reach/select it on its own.
  jlong tag = tagObject(jvmti, obj);
  if (tag == 0) {
    return 0;
  }
  if (!_frontier->insert(tag, 0, klass_id, 0)) {
    clearTag(jvmti, obj);
    return 0;
  }
  return tag;
}

// ---------------------------------------------------------------------------
// Heap-walk engine
// ---------------------------------------------------------------------------

void ReferenceChainTracker::resolveLoadedClasses(jvmtiEnv *jvmti,
                                                  JNIEnv *jni) {
  // Profiler::start() resets the class-name StringDictionary
  // (_class_map.clearAll(), profiler.cpp) whenever `reset || _start_time ==
  // 0` - which restarts its id namespace at 1, but does NOT touch any
  // class's JVMTI-level class-object tag (JVM-level state, unrelated to our
  // dictionary). Detect that reset via the dictionary's own generation
  // counter and drop every id this table cached from the now-gone
  // generation before the scan below - see _last_class_map_generation's own
  // comment (referenceChains.h) for why leaving them in place would keep
  // resolving heap references to the wrong (or nonexistent) class name.
  u64 current_generation = Profiler::instance()->classMap()->generation();
  bool class_map_reset = current_generation != _last_class_map_generation;
  if (class_map_reset) {
    _class_tags.clear();
    // Force the scan below to run even if GetLoadedClasses()'s count happens
    // to match the last-seen count - -1 can never equal `class_count`
    // (always >= 0), unlike 0 which is a legitimate "no classes loaded yet"
    // starting value.
    _last_resolved_class_count = -1;
    _last_class_map_generation = current_generation;
  }

  jclass *classes = nullptr;
  jint class_count = 0;
  if (jvmti->GetLoadedClasses(&class_count, &classes) != JVMTI_ERROR_NONE ||
      classes == nullptr) {
    return;
  }

  // Skip the per-class GetTag()/GetClassSignature() scan entirely once the
  // loaded-class count has not CHANGED since the last time this ran it:
  // every already-tagged class stays tagged forever (tags are never
  // cleared once assigned - see _class_tags' own comment), so a resumed
  // pass with no newly-loaded classes has nothing left to resolve. Without
  // this, every single pass pays a full GetTag() call per loaded class
  // (potentially thousands) even though almost all of them are already
  // resolved, and that cost is invisible to the pause-time-SLO pacing
  // controller (runPass()'s pass_wall_ticks measurement deliberately scopes
  // out this call - see that field's own comment).
  //
  // Deliberately `!=`, not `>`: GetLoadedClasses()'s count is NOT monotonic
  // - class unloading (a GC'd custom classloader, JSP/bytecode-macro
  // recompilation, etc.) can shrink it. A `>` check would then stay
  // permanently skipped once new classes are loaded back up to, but not
  // past, a prior historical peak - e.g. 1000 classes loaded then unloaded
  // down to 400, then 50 different new classes loaded (total 450, still
  // below the 1000 peak) - silently leaving those 50 new classes' tag == 0
  // forever, so any object of theirs discovered by the BFS walk never
  // resolves a referrer_klass. `!=` catches both directions; the only
  // residual gap is the count-preserving unload-then-reload-same-count case,
  // far narrower than the permanent gap `>` left open.
  if (class_count != _last_resolved_class_count) {
    for (jint i = 0; i < class_count; i++) {
      jclass klass = classes[i];
      jlong tag = 0;
      // Resolve if not yet tagged (ordinary case: a newly-loaded class), or
      // unconditionally on a class-map reset (class_map_reset above) - a
      // class already tagged from a prior generation still carries that same
      // JVMTI tag (untouched by clearAll()), but the dictionary id it used to
      // map to is gone, so its name must be re-resolved into the new
      // generation too.
      if (jvmti->GetTag(klass, &tag) == JVMTI_ERROR_NONE &&
          (tag == 0 || class_map_reset)) {
        // Resolve its name now, via the same GetClassSignature +
        // normalizeClassSignature + Profiler::lookupClass sequence
        // ObjectSampler::recordAllocation() already uses
        // (objectSampler.cpp:76-90), reused rather than re-derived.
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
              // Reuse the existing tag if this class was already tagged by a
              // prior generation - only the resolved id needs refreshing,
              // not the tag identity heapReferenceCallback() keys off of.
              jlong class_tag = tag != 0 ? tag : nextClassTag();
              if (tag != 0 ||
                  jvmti->SetTag(klass, class_tag) == JVMTI_ERROR_NONE) {
                _class_tags.insert(class_tag, (u32)id);
              }
            }
          }
          jvmti->Deallocate((unsigned char *)class_name);
        }
      }
      // GetLoadedClasses() hands back class_count fresh JNI local refs -
      // delete each immediately rather than holding all of them alive at
      // once, since class_count can run into the thousands.
      if (jni != nullptr) {
        jni->DeleteLocalRef(klass);
      }
    }
    _last_resolved_class_count = class_count;
  } else if (jni != nullptr) {
    // Still owe DeleteLocalRef for every fresh local ref GetLoadedClasses()
    // just handed back, even though the scan above was skipped.
    for (jint i = 0; i < class_count; i++) {
      jni->DeleteLocalRef(classes[i]);
    }
  }
  jvmti->Deallocate((unsigned char *)classes);
}

namespace {
// Per-runPass() state threaded through heapReferenceCallback() via
// FollowReferences' user_data parameter. Private to this .cpp - the type
// never needs to be visible in referenceChains.h since only runPass()
// constructs one and only heapReferenceCallback() reads it.
struct PassContext {
  ReferenceChainTracker *tracker;
  FrontierTable *frontier;
  int hop_cap;
  int budget;
  int edges_admitted;
  bool truncated;

  // Set only when `truncated` became true because frontier->insert() itself
  // reported capacity exhaustion, as opposed to edges_admitted reaching
  // budget. runPass() uses this to distinguish "this pass ran out
  // of budget, more work remains for a later pass" (search stays RUNNING)
  // from "the frontier table itself is full" (design doc's Termination
  // section: grounds to ABANDON the whole search, not just this pass).
  bool frontier_cap_hit;
};
} // namespace

jint JNICALL ReferenceChainTracker::heapReferenceCallback(
    jvmtiHeapReferenceKind reference_kind,
    const jvmtiHeapReferenceInfo *reference_info, jlong class_tag,
    jlong referrer_class_tag, jlong size, jlong *tag_ptr,
    jlong *referrer_tag_ptr, jint length, void *user_data) {
  PassContext *ctx = (PassContext *)user_data;

  if (ctx->tracker->_abort_pass_requested.load(std::memory_order_relaxed)) {
    // stopThread() has set this right before pthread_kill()/pthread_join() -
    // see that method's own comment. pthread_kill(WAKEUP_SIGNAL) only
    // interrupts threadLoop()'s OS::sleep(); it cannot interrupt an
    // in-flight JVMTI FollowReferences call, so without this check
    // pthread_join() would block until this pass's walk finishes on its own
    // - potentially the whole reachable graph, well past any caller's
    // shutdown timeout. Treat it exactly like an ordinary budget exhaustion
    // (ctx->truncated = true): this pass ends early and the search stays
    // non-terminal - fine, since the tracker is shutting down and simply
    // never resumes it.
    ctx->truncated = true;
    return JVMTI_VISIT_ABORT;
  }

  if (*tag_ptr < 0 || reference_kind == JVMTI_HEAP_REFERENCE_CLASS ||
      reference_kind == JVMTI_HEAP_REFERENCE_SYSTEM_CLASS) {
    // Referee is a class object - either already tagged negative by
    // resolveLoadedClasses() (the common case: that pre-pass runs before
    // FollowReferences in runPass(), so every loaded class already carries
    // a negative tag by this point), or definitionally a class by
    // reference_kind (CLASS: "reference from an object to its class";
    // SYSTEM_CLASS: a root reference to a class) even if
    // resolveLoadedClasses() failed to resolve/tag this particular one
    // (e.g. a transient StringDictionary contention failure). Never expand
    // from a class's own metadata graph
    // (static fields, superclass, interfaces, constant pool, class loader,
    // ...) and never admit a class object into the frontier as if it were
    // an ordinary retained instance. Out of scope per the design doc's
    // non-goals (no field-level/exhaustive paths) and keeps the walk
    // bounded to the instance-reachability graph that actually explains
    // "why is this object alive".
    return 0;
  }

  if (ctx->truncated) {
    // Defensive: FollowReferences should already have stopped delivering
    // callbacks after a JVMTI_VISIT_ABORT return below; this just avoids
    // doing further work if one more callback arrives anyway.
    return JVMTI_VISIT_ABORT;
  }

  jlong parent_tag = 0;
  u32 depth = 0;
  if (referrer_tag_ptr != nullptr) {
    jlong rtag = *referrer_tag_ptr;
    if (rtag > 0) {
      FrontierEntry parent{};
      if (ctx->frontier->lookup(rtag, &parent)) {
        parent_tag = rtag;
        depth = parent.depth + 1;
      }
      // lookup() failing for a positive rtag should not happen - a referrer
      // must already be one of our tagged frontier objects for its own
      // outgoing edges to be traversed at all (FollowReferences only
      // explores past an object this callback returned JVMTI_VISIT_OBJECTS
      // for) - but fall back to root-like (parent_tag=0/depth=0) rather
      // than corrupt the chain if it ever does.
    }
    // rtag < 0: referrer is a pre-tagged class object (e.g. a static field
    // holding this reference) - treated as root-like rather than attributed
    // to a parent hop, since class objects are never admitted as frontier
    // entries and so have no depth/parent_tag of their own (see the
    // *tag_ptr < 0 check above). rtag == 0: referrer not yet tagged, should
    // not happen for the same reason noted above.
  }
  // referrer_tag_ptr == nullptr: a heap-root reference (JNI global, thread
  // stack local/JNI local, monitor, thread, system class, ...) - parent_tag
  // and depth stay 0.

  if (depth >= (u32)ctx->hop_cap) {
    // Hop cap: do not admit this object into the frontier, and do not
    // expand further from it - enforced here rather than
    // discovering-then-discarding, per the plan.
    return 0;
  }

  if (*tag_ptr == 0) {
    // First time this object is visited in this pass.
    if (ctx->edges_admitted >= ctx->budget) {
      ctx->truncated = true;
      return JVMTI_VISIT_ABORT;
    }

    jlong tag = ctx->tracker->nextTag();
    u32 referrer_klass = ctx->tracker->classTags()->resolve(class_tag);
    if (!ctx->frontier->insert(tag, parent_tag, referrer_klass, depth)) {
      // Frontier-size cap hit (FrontierTable::insert() returns false
      // without partially writing) - stop admitting new entries and report
      // the truncation (design doc: "stop admitting new entries ... report
      // it"), rather than silently dropping this object and continuing.
      // Distinct from ordinary budget exhaustion below (frontier_cap_hit) -
      // runPass() abandons the whole search for this, not just this pass.
      ctx->truncated = true;
      ctx->frontier_cap_hit = true;
      return JVMTI_VISIT_ABORT;
    }
    *tag_ptr = tag;
    ctx->edges_admitted++;
    // Queue for expandFrontier()/markAllFrontierExpanded() - see
    // _pending_expand's own declaration comment for why this replaces a
    // scan over the admitted range.
    ctx->tracker->_pending_expand.push_back(tag);
  }

  return JVMTI_VISIT_OBJECTS;
}

// ---------------------------------------------------------------------------
// Incremental resumption across passes.
// ---------------------------------------------------------------------------

void ReferenceChainTracker::markAllFrontierExpanded() {
  while (!_pending_expand.empty()) {
    _frontier->markExpanded(_pending_expand.front());
    _pending_expand.pop_front();
  }
}

void ReferenceChainTracker::expandFrontier(jvmtiEnv *jvmti, JNIEnv *jni,
                                            int hop_cap, int budget,
                                            int *edges_admitted,
                                            bool *truncated,
                                            bool *frontier_cap_hit) {
  assert(!t_inGCCallback &&
         "GetObjectsWithTags/FollowReferences are JVMTI Heap-category calls "
         "and must not be made from GarbageCollectionStart/Finish");

  PassContext ctx;
  ctx.tracker = this;
  ctx.frontier = _frontier;
  ctx.hop_cap = hop_cap;
  ctx.budget = budget;
  ctx.edges_admitted = 0;
  ctx.truncated = false;
  ctx.frontier_cap_hit = false;

  jvmtiHeapCallbacks callbacks;
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.heap_reference_callback = heapReferenceCallback;

  bool progress = true;
  while (!ctx.truncated && progress) {
    progress = false;

    if (_pending_expand.empty()) {
      break; // nothing pending
    }

    // Snapshot at most `budget` pending tags per iteration, not the whole
    // queue: _pending_expand can hold far more than this call could ever
    // admit (e.g. every hop_cap-limited entry from a huge one-shot first
    // pass), and GetObjectsWithTags()'s own cost scales with the batch size
    // handed to it - resolving the entire backlog up front just to abandon
    // most of it once `budget` is hit would reintroduce the same
    // admitted-range-sized cost this queue was meant to avoid. Entries
    // expanded below can push new FRONTIER children onto the back of
    // _pending_expand (design doc Algorithm step 3/4 - admitting them
    // immediately, rather than waiting for a whole extra pass, is a
    // strictly tighter use of the budget this call already has); those wait
    // for a later outer-loop iteration.
    size_t batch_size =
        std::min(_pending_expand.size(), (size_t)std::max(budget, 1));
    std::vector<jlong> candidate_tags(_pending_expand.begin(),
                                       _pending_expand.begin() + batch_size);

    // Design doc Algorithm step 2: "resolve currently-live tagged frontier
    // objects" - batched via one GetObjectsWithTags call rather than one
    // resolve per entry.
    jint resolved_count = 0;
    jobject *resolved_objects = nullptr;
    jlong *resolved_tags = nullptr;
    jvmtiError resolve_err = jvmti->GetObjectsWithTags(
        (jint)candidate_tags.size(), candidate_tags.data(), &resolved_count,
        &resolved_objects, &resolved_tags);
    if (resolve_err != JVMTI_ERROR_NONE) {
      // Could not resolve this (non-empty) batch - there IS still pending
      // work, we just could not make progress on it this call. Mark
      // truncated (not "search complete") so runPass() does not mistake a
      // transient resolve failure for the reachable graph being fully
      // explored; a later pass retries the same candidates.
      ctx.truncated = true;
      break;
    }

    std::unordered_map<jlong, jobject> live;
    for (jint i = 0; i < resolved_count; i++) {
      live[resolved_tags[i]] = resolved_objects[i];
    }

    for (jlong tag : candidate_tags) {
      if (ctx.truncated) {
        break; // budget/frontier-cap already hit by a sibling in this batch
      }
      // `tag` is always _pending_expand's current front here: candidate_tags
      // is a front-to-back snapshot, and nothing removes from the front
      // except this loop itself - concurrent admissions (below) only append
      // to the back.
      auto it = live.find(tag);
      if (it == live.end()) {
        // Design doc Algorithm step 2: "objects that fail to resolve are
        // dropped (dead - free pruning)". The object died between passes;
        // JVMTI already forgot its tag along with it, so there is nothing
        // left to expand and no live object to release a tag on.
        _frontier->clear(tag);
        _pending_expand.pop_front();
        progress = true;
        continue;
      }

      // initial_object=<this entry's object>: only this object's own
      // outgoing edges (and anything transitively reachable that our own
      // callback admits) are visited - not the whole heap - which is why a
      // resumed pass costs proportionally to what is newly expanded, not to
      // everything already discovered (see runPass()'s own comment for why
      // that distinction matters).
      jvmtiError follow_err =
          jvmti->FollowReferences(0, nullptr, it->second, &callbacks, &ctx);
      if (follow_err != JVMTI_ERROR_NONE || ctx.truncated) {
        // Either this call failed outright, or ran into the budget/
        // frontier-cap mid-way through this entry's own children. Leave
        // `tag` at the front of _pending_expand (still FRONTIER, not
        // EXPANDED) so a later pass retries it - already-admitted children
        // stay tagged/in the table, and heapReferenceCallback()'s
        // *tag_ptr == 0 check makes re-expanding this entry idempotent, so
        // no work is lost, only deferred.
        break;
      }
      _frontier->markExpanded(tag);
      _pending_expand.pop_front();
      progress = true;
    }

    if (jni != nullptr) {
      for (jint i = 0; i < resolved_count; i++) {
        jni->DeleteLocalRef(resolved_objects[i]);
      }
    }
    if (resolved_objects != nullptr) {
      jvmti->Deallocate((unsigned char *)resolved_objects);
    }
    if (resolved_tags != nullptr) {
      jvmti->Deallocate((unsigned char *)resolved_tags);
    }
  }

  *edges_admitted = ctx.edges_admitted;
  *truncated = ctx.truncated;
  *frontier_cap_hit = ctx.frontier_cap_hit;
}

bool ReferenceChainTracker::releaseSearchTags(jvmtiEnv *jvmti, JNIEnv *jni) {
  assert(!t_inGCCallback &&
         "GetObjectsWithTags is a JVMTI Heap-category call and must not be "
         "made from GarbageCollectionStart/Finish");
  if (jvmti == nullptr || _frontier == nullptr) {
    return true; // nothing to release
  }

  jlong scan_limit = _frontier->size();
  std::vector<jlong> live_tags;
  for (jlong tag = 1; tag <= scan_limit; tag++) {
    FrontierEntry entry{};
    if (_frontier->lookup(tag, &entry) &&
        entry.state != FrontierEntryState::ABANDONED) {
      live_tags.push_back(tag);
    }
  }
  if (live_tags.empty()) {
    return true;
  }

  jint resolved_count = 0;
  jobject *resolved_objects = nullptr;
  jlong *resolved_tags = nullptr;
  if (jvmti->GetObjectsWithTags((jint)live_tags.size(), live_tags.data(),
                                 &resolved_count, &resolved_objects,
                                 &resolved_tags) != JVMTI_ERROR_NONE) {
    // GetObjectsWithTags() itself failed (e.g. JVMTI_ERROR_OUT_OF_MEMORY):
    // we do NOT know which, if any, of live_tags are still live objects, so
    // do not mark any of them ABANDONED here - doing so while their JVMTI
    // tag might still be set would let a restarted search's nextTag()
    // sequence eventually reissue the same numeric tag to a brand-new
    // object, corrupting FrontierTable's tag-uniqueness invariant (see this
    // method's own header comment). Report failure so the caller retries
    // this same batch later instead of proceeding to restart.
    Counters::increment(REFERENCE_CHAIN_TAG_RELEASE_FAILED);
    Log::warn("ReferenceChains: GetObjectsWithTags failed while releasing "
              "%zu search tag(s); will retry before allowing a search "
              "restart",
              live_tags.size());
    return false;
  }

  for (jint i = 0; i < resolved_count; i++) {
    // clearTag() rather than a raw SetTag() call - reuses the
    // same helper (and its GC-callback self-consistency assert) tagObject/
    // getTag already go through.
    clearTag(jvmti, resolved_objects[i]);
    if (jni != nullptr) {
      jni->DeleteLocalRef(resolved_objects[i]);
    }
  }
  if (resolved_objects != nullptr) {
    jvmti->Deallocate((unsigned char *)resolved_objects);
  }
  if (resolved_tags != nullptr) {
    jvmti->Deallocate((unsigned char *)resolved_tags);
  }
  // Tags that failed to resolve above are already dead (JVMTI forgot them
  // with their object) - nothing to release, just mark the record ABANDONED
  // below like every other entry this search owned. Only reached once
  // GetObjectsWithTags() itself succeeded, so every live_tags entry has now
  // either been resolved-and-cleared or confirmed dead.
  for (jlong tag : live_tags) {
    _frontier->clear(tag);
  }
  return true;
}

bool ReferenceChainTracker::runPass(jvmtiEnv *jvmti, JNIEnv *jni,
                                     bool *out_truncated) {
  if (!_enabled || jvmti == nullptr || _frontier == nullptr) {
    TEST_LOG("ReferenceChainTracker::runPass early-exit: enabled=%d jvmti=%p frontier=%p",
             _enabled, (void *)jvmti, (void *)_frontier);
    return false;
  }

  if (_search_state != SearchState::RUNNING) {
    // The search already reached a terminal outcome - nothing left for
    // another pass to do until shouldRunPass() decides to restartSearch()
    // (this class's header comment), which flips _search_started back to
    // false before this method is called again. If a prior terminal-state
    // transition's releaseSearchTags() call failed, retry it here rather
    // than leaving _tags_released false forever - shouldRunPass() refuses
    // to restart the search until this succeeds (see _tags_released's own
    // comment), so this is the only remaining call site that can make
    // progress on the retry.
    if (!_tags_released) {
      _tags_released = releaseSearchTags(jvmti, jni);
    }
    TEST_LOG("ReferenceChainTracker::runPass no-op: searchState=%d already terminal "
             "tagsReleased=%d",
             (int)_search_state, _tags_released);
    if (out_truncated != nullptr) {
      *out_truncated = false;
    }
    return true;
  }

  resolveLoadedClasses(jvmti, jni);

  TEST_LOG("ReferenceChainTracker::runPass starting JVMTI walk: "
           "search_started=%d frontierSize=%zu",
           _search_started, _frontier != nullptr ? _frontier->size() : (size_t)0);

  int edges_admitted = 0;
  bool truncated = false;
  bool frontier_cap_hit = false;
  jvmtiError err;
  // Wall-clock duration of the actual safepoint-triggering JVMTI call below
  // (FollowReferences or, inside expandFrontier(), FollowReferences preceded
  // by GetObjectsWithTags) - the measured signal updatePacing() below feeds
  // into _pause_pid. Deliberately scoped to just that call, not this whole
  // method, so resolveLoadedClasses()'s own JNI/JVMTI cost and this method's
  // own bookkeeping are not mistaken for safepoint time. Measured via
  // TSC::ticks() rather than OS::nanotime(), matching this codebase's other
  // interval-timing call sites (LivenessTracker::track(), pollWatchedTargets()
  // below); TSC::ticks() itself falls back to OS::nanotime() when the TSC is
  // unavailable/disabled, so this is a strict upgrade with no behavior change
  // on hosts without a usable timestamp counter.
  u64 pass_wall_ticks = 0;
  // Captured before _search_started flips below - see its use at
  // updatePacing() further down for why the first pass's own duration must
  // not feed that controller the same way every later pass's does.
  bool was_first_pass = !_search_started;

  if (!_search_started) {
    _search_started = true;
    store(_search_start_ns, OS::nanotime());

    PassContext ctx;
    ctx.tracker = this;
    ctx.frontier = _frontier;
    ctx.hop_cap = _hop_cap;
    ctx.budget = _first_pass_budget;
    ctx.edges_admitted = 0;
    ctx.truncated = false;
    ctx.frontier_cap_hit = false;

    jvmtiHeapCallbacks callbacks;
    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.heap_reference_callback = heapReferenceCallback;

    // heap_filter=0/klass=NULL/initial_object=NULL: follow references from
    // all heap roots over the entire reachable object graph (design doc's
    // Algorithm step 1, "first pass" case). Every *resumed* pass instead
    // goes through expandFrontier() below, seeded from the persisted
    // frontier rather than the roots - re-walking from the roots every call
    // would make FollowReferences re-traverse the entire already-discovered
    // subgraph each time (our callback still has to return
    // JVMTI_VISIT_OBJECTS for already-tagged objects so their unvisited
    // siblings/children stay reachable), which grows without bound as the
    // search progresses and defeats the point of a per-pass budget bounding
    // the safepoint length.
    //
    // FollowReferences, not IterateThroughHeap (implementation plan's "Open
    // items to resolve before starting the heap-walk work", item 3): IterateThroughHeap
    // enumerates every heap object with no referrer/reference information at
    // all - its callback (jvmtiHeapIterationCallback) has no referrer_tag_ptr,
    // reference_kind, or referrer_class_tag parameters, so it cannot report
    // the parent linkage this subsystem needs at any cost. The JVMTI spec is
    // explicit about this (IterateThroughHeap's own doc): "References between
    // objects are not reported. If ... object reference information is
    // needed, use FollowReferences." This is therefore not a cost/benefit
    // tradeoff for this use case - FollowReferences is the only JVMTI call
    // that reports referrer information at all.
    u64 call_start_ticks = TSC::ticks();
    err = jvmti->FollowReferences(0, nullptr, nullptr, &callbacks, &ctx);
    pass_wall_ticks = TSC::ticks() - call_start_ticks;

    edges_admitted = ctx.edges_admitted;
    truncated = ctx.truncated;
    frontier_cap_hit = ctx.frontier_cap_hit;

    if (err != JVMTI_ERROR_NONE) {
      // FollowReferences() itself failing (e.g. JVMTI_ERROR_OUT_OF_MEMORY)
      // means heapReferenceCallback() never ran, so ctx.truncated is still
      // false - without forcing it true here, the Termination section below
      // would read has_pending_frontier as false and mark the search
      // COMPLETED even though the reachable graph was never walked. Treat a
      // failed first pass the same way expandFrontier() already treats its
      // own internal JVMTI failures: truncated, not complete, so the search
      // stays RUNNING and a later pass retries.
      truncated = true;
      // Also undo _search_started's flip above: a resumed pass's branch
      // (expandFrontier(), below) walks the *persisted frontier*, which is
      // still empty here since the failed FollowReferences call never ran
      // heapReferenceCallback() to populate it. Left alone, the next
      // runPass() call would take the resumed-pass branch over that empty
      // frontier, see truncated=false (nothing pending) and mark the search
      // falsely COMPLETED with zero discovered objects instead of ever
      // retrying the root-seeded walk. Resetting _search_started here makes
      // the next call take this same first-pass branch again.
      _search_started = false;
    } else if (!truncated) {
      markAllFrontierExpanded();
    }
  } else {
    u64 call_start_ticks = TSC::ticks();
    expandFrontier(jvmti, jni, _hop_cap, _effective_budget, &edges_admitted,
                   &truncated, &frontier_cap_hit);
    pass_wall_ticks = TSC::ticks() - call_start_ticks;
    err = JVMTI_ERROR_NONE;
  }

  store(_passes_run, load(_passes_run) + 1);
  _last_pass_gc_finish_epoch = gcFinishEpoch();
  store(_last_pass_ns, OS::nanotime());
  if (!was_first_pass) {
    // The first pass spends _first_pass_budget, not _effective_budget - its
    // duration is not a signal about the per-pass cost updatePacing() is
    // trying to regulate (expandFrontier()'s cheap, per-node expansion
    // calls), so feeding it in here would throttle _effective_budget down
    // for every one of those unrelated later passes based on a single,
    // deliberately oversized outlier.
    updatePacing(pass_wall_ticks);
  }
  // Search restart (this class's own header comment): accumulate this
  // pass's own cost toward the running total restartSearch() will spend into
  // _pain_budget once the search reaches a terminal state - same
  // TSC::ticks_to_millis() conversion updatePacing() already uses for its
  // own pass-duration signal.
  _search_pain_ms += TSC::ticks_to_millis(pass_wall_ticks);

  // Design doc's Termination section, decided in priority order:
  //   1. Frontier-size cap hit -> abandon immediately, regardless of TTL.
  //   2. No pending frontier entries left (this pass wasn't truncated) ->
  //      the reachable graph was fully explored within the hop cap; natural
  //      completion (the hop cap alone is a normal boundary, not
  //      truncation - see heapReferenceCallback()'s own comment).
  //   3. TTL exceeded while work is still pending -> abandon.
  //   4. Otherwise stay RUNNING - more pending work, no cap hit yet.
  bool has_pending_frontier = truncated;
  if (frontier_cap_hit) {
    store(_search_state, (u8)SearchState::ABANDONED);
    store(_abandon_reason, (u8)SearchAbandonReason::FRONTIER_CAP);
  } else if (!has_pending_frontier) {
    store(_search_state, (u8)SearchState::COMPLETED);
  } else if (_ttl_ms > 0 &&
             _last_pass_ns - _search_start_ns >= (u64)_ttl_ms * 1000000ULL) {
    store(_search_state, (u8)SearchState::ABANDONED);
    store(_abandon_reason, (u8)SearchAbandonReason::TTL);
  }

  if (load(_search_state) != SearchState::RUNNING) {
    _tags_released = releaseSearchTags(jvmti, jni);
  }

  if (out_truncated != nullptr) {
    *out_truncated = truncated;
  }

  TEST_LOG("ReferenceChainTracker::runPass done: err=%d edges_admitted=%d truncated=%d "
           "frontier_cap_hit=%d searchState=%d abandonReason=%d frontierSize=%d "
           "effectiveBudget=%d effectiveCadenceNs=%llu",
           (int)err, edges_admitted, truncated, frontier_cap_hit, (int)load(_search_state),
           (int)_abandon_reason, _frontier->size(), _effective_budget,
           (unsigned long long)_effective_cadence_ns);

  return err == JVMTI_ERROR_NONE;
}

// ---------------------------------------------------------------------------
// Pause-time-SLO feedback loop (see this method's declaration in
// referenceChains.h for the full mechanism).
// ---------------------------------------------------------------------------

void ReferenceChainTracker::updatePacing(u64 pass_wall_ticks) {
  // Truncating to whole milliseconds matches every other PidController usage
  // in this codebase (ObjectSampler/MallocTracer/NativeSocketSampler all feed
  // it integer counts, pidController.h's `compute(u64 input, ...)`) - sub-ms
  // precision is not meaningful against a millisecond-scale target anyway.
  // TSC::ticks_to_millis() already falls back to a nanotime-based conversion
  // when the TSC is unavailable/disabled (tsc.h), matching runPass()'s own
  // TSC::ticks() fallback for pass_wall_ticks itself.
  u64 pass_ms = TSC::ticks_to_millis(pass_wall_ticks);
  // time_delta_coefficient is deliberately 1.0, not a real-elapsed-time
  // ratio - unlike ObjectSampler's usage (objectSampler.cpp), which
  // rescales an event count accumulated over a variable-length real-time
  // window against a fixed-real-time target, _pause_pid was constructed
  // with sampling_window=1 (its own constructor comment above, in start()):
  // one compute() call *is* one pass, and pass_ms already IS the per-call
  // quantity being compared against the per-call ceiling _target encodes.
  // Rescaling pass_ms by how much real wall-clock time elapsed since the
  // previous call would compare it against a target calibrated for a
  // different unit (per-second, not per-pass), double-counting the same
  // irregular-cadence effect this coefficient exists to correct for in the
  // per-second case. (Re-litigated after review: an earlier pass flagged
  // this as a bug and a fix using TSC-measured elapsed time was drafted,
  // but re-checking against this constructor's own documented design
  // confirmed 1.0 is correct here - see this comment instead of changing
  // it again.)
  double signal = _pause_pid.compute(pass_ms, 1.0);

  int64_t ceiling = _budget;
  int64_t floor = ceiling > 0 ? std::min((int64_t)MIN_EFFECTIVE_BUDGET, ceiling)
                               : 0;
  int64_t desired = (int64_t)_effective_budget + (int64_t)std::lround(signal);
  int64_t clamped = std::max(floor, std::min(ceiling, desired));
  // Whatever part of `desired` the clamp above could not absorb - positive
  // when there was more headroom than the ceiling allows, negative when the
  // pass is still over the pause-time target even at the floor. Drives
  // _effective_cadence_ns below, per this method's own comment on folding
  // Open Question 5 into the same controller output.
  int64_t overflow = desired - clamped;
  _effective_budget = (int)clamped;

  if (overflow < 0) {
    // Still over the pause-time ceiling even at the minimum budget - widen
    // the fallback interval instead of shrinking the budget further.
    u64 step = (u64)(-overflow) * CADENCE_NS_PER_EDGE_OVERFLOW;
    _effective_cadence_ns =
        std::min(_effective_cadence_ns + step, MAX_EFFECTIVE_CADENCE_NS);
  } else if (overflow > 0) {
    // Comfortably under the ceiling even at the maximum (config) budget -
    // relax the fallback interval. The GC-finish-epoch trigger already fires
    // independently of cadence (shouldRunPass() above), so this only
    // shortens how long an idle, no-GC-event search waits between passes.
    u64 step = (u64)overflow * CADENCE_NS_PER_EDGE_OVERFLOW;
    _effective_cadence_ns =
        step >= _effective_cadence_ns
            ? MIN_EFFECTIVE_CADENCE_NS
            : std::max(_effective_cadence_ns - step, MIN_EFFECTIVE_CADENCE_NS);
  }
  // overflow == 0: the budget clamp alone fully absorbed this pass's
  // correction - leave the cadence at its current value.
}

// ---------------------------------------------------------------------------
// Target-selection bridging step - LivenessTracker's leak-candidate ranking feeds
// this tracker's already-running BFS search (design doc's Open Question 3,
// corrected mechanism - see this method's own comment below and the plan
// doc's "Correction to the design doc's Open Question 3 mechanism").
// ---------------------------------------------------------------------------

void ReferenceChainTracker::pollWatchedTargets(jvmtiEnv *jvmti, JNIEnv *jni) {
  if (!_enabled || jvmti == nullptr || jni == nullptr ||
      !LivenessTracker::instance()->gcGenerationsEnabled()) {
    // Explicit guard, even though selectLeakCandidates() below already
    // returns 0 candidates whenever its own _gc_generations gate
    // (livenessTracker.h) is off - keeps this method's cost at the four
    // checks above, not even a shared-lock-guarded table scan, when the
    // feature isn't in use (design doc's Open Question 3 "still undecided"
    // fallback: referencechains=... alone gets no target-seeding).
    return;
  }

  // _search_start_ns is set exactly once per search, the first time
  // _search_started flips true (runPass()'s own comment) - the only "a new
  // search began" signal this tracker currently exposes, since runPass()
  // does not yet support starting a new search once one ends (its own
  // comment). Clearing _emitted_target_tags on a change here future-proofs
  // this method for whenever that restart capability lands, at no cost
  // today: the comparison is false on every poll after the first one of the
  // tracker's one and only search.
  if (_emitted_search_start_ns != load(_search_start_ns)) {
    _emitted_target_tags.clear();
    _emitted_search_start_ns = load(_search_start_ns);
  }

  // Sized generously above LivenessTracker::selectLeakCandidates()'s own
  // private MAX_LEAK_CANDIDATES cap (design doc: top 3-5) - that method
  // clamps internally to whichever of `max`/its own cap/the qualifying-
  // candidate count is smallest, so this local bound only needs to be
  // "large enough", not exactly synchronized to a constant this class has
  // no visibility into (MAX_LEAK_CANDIDATES is private to LivenessTracker).
  constexpr int kMaxWatchedCandidates = 8;
  KlassCandidate candidates[kMaxWatchedCandidates];
  int candidate_count = LivenessTracker::instance()->selectLeakCandidates(
      candidates, kMaxWatchedCandidates);
  // Only log when there are candidates to act on - this poll runs on every
  // BFS-thread wake (once per second), so logging a zero count is per-second
  // noise for the common idle case.
  if (candidate_count > 0) {
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate_count=%d", candidate_count);
  }

  for (int i = 0; i < candidate_count; i++) {
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate[%d] klass_id=%u", i,
             candidates[i].klass_id);
    // Deliberately does NOT resolve candidates[i].representative directly:
    // that field is a snapshot taken under selectLeakCandidates()'s own
    // shared-lock scan, which can go stale (LRU-evicted and
    // DeleteWeakGlobalRef()'d by LivenessTracker's cleanup_table(), running
    // concurrently on a different thread) at any point between that call and
    // this one - see selectLeakCandidates()'s comment (livenessTracker.h) for
    // why resolving it here would be undefined behavior, not just a null
    // result. resolveCandidateRepresentative() re-reads the table's current
    // value for this klass_id and resolves it atomically under the same
    // lock, so it is always safe to call from here.
    jobject obj = LivenessTracker::instance()->resolveCandidateRepresentative(
        jni, candidates[i].klass_id);
    if (obj == nullptr) {
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate[%d] klass_id=%u "
               "representative could not be resolved (died/evicted)",
               i, candidates[i].klass_id);
      continue; // candidate died, or was evicted, since LivenessTracker flagged it
    }

    // Corrected mechanism (the plan doc's own correction to the design doc's
    // original proposal): a READ, never a SetTag
    // seed. runPass()'s whole-graph walk is the only thing that ever
    // assigns a tag; if it already has (tag > 0), heapReferenceCallback()
    // already recorded a correct parent_tag/depth chain for this object the
    // moment it was first visited - pre-tagging it here instead would make
    // that callback's `*tag_ptr == 0` branch (the only branch that records
    // parent_tag/depth, referenceChains.h) skip it entirely the next time a
    // pass reached it.
    jlong tag = getTag(jvmti, obj);
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate[%d] klass_id=%u tag=%lld "
             "alreadyEmitted=%d",
             i, candidates[i].klass_id, (long long)tag,
             _emitted_target_tags.find(tag) != _emitted_target_tags.end());
    if (tag > 0 &&
        _emitted_target_tags.find(tag) == _emitted_target_tags.end()) {
      ReferenceChainEvent event;
      bool built = buildChainEvent(tag, &event);
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets buildChainEvent(tag=%lld) -> %d",
               (long long)tag, built);
      if (built) {
        event._start_time = TSC::ticks();
        enqueueChainEvent(std::move(event));
        _emitted_target_tags.insert(tag);
      }
    }
    // tag == 0: not yet discovered by any pass - retry on the next poll,
    // once a pass has had a chance to reach it (this method's own comment).

    jni->DeleteLocalRef(obj);
  }
}

// Pushes `event` onto _pending_chain_events rather than calling
// Profiler::writeReferenceChain() directly - see that field's own comment
// (referenceChains.h) for why the write is deferred off the caller's thread.
// Drop-oldest on overflow: best-effort, matching this whole subsystem's
// other bounded tables, and only reachable if dump() goes a long stretch
// without being called while many distinct klasses keep getting flagged.
// Extracted out of pollWatchedTargets() as its own method so
// PendingChainEventsQueueTest (referenceChains_ut.cpp) can drive the
// overflow path directly, without needing hundreds of real LivenessTracker
// candidates to fill a 256-entry queue through the full bridging pipeline.
void ReferenceChainTracker::enqueueChainEvent(ReferenceChainEvent &&event) {
  _pending_chain_events_lock.lock();
  if ((int)_pending_chain_events.size() >= MAX_PENDING_CHAIN_EVENTS) {
    // The oldest queued event is about to be permanently lost - its tag was
    // already marked emitted by the caller when *it* was queued, so it will
    // never be retried. Countable, not silent (this codebase's own
    // "dropped-event-without-counter" review lens).
    _pending_chain_events.erase(_pending_chain_events.begin());
    Counters::increment(REFERENCE_CHAIN_EVENTS_DROPPED);
    TEST_LOG("ReferenceChainTracker::enqueueChainEvent dropped oldest queued event, "
             "queue_size=%d (at MAX_PENDING_CHAIN_EVENTS=%d)",
             (int)_pending_chain_events.size(), MAX_PENDING_CHAIN_EVENTS);
  }
  _pending_chain_events.push_back(std::move(event));
  TEST_LOG("ReferenceChainTracker::enqueueChainEvent queued, queue_size=%d",
           (int)_pending_chain_events.size());
  _pending_chain_events_lock.unlock();
}

void ReferenceChainTracker::drainPendingChainEvents(
    std::vector<ReferenceChainEvent> *out) {
  if (out == nullptr) {
    return;
  }
  _pending_chain_events_lock.lock();
  if (!_pending_chain_events.empty()) {
    for (auto &event : _pending_chain_events) {
      out->push_back(std::move(event));
    }
    _pending_chain_events.clear();
  }
  _pending_chain_events_lock.unlock();
  TEST_LOG("ReferenceChainTracker::drainPendingChainEvents drained=%d",
           (int)out->size());
}
