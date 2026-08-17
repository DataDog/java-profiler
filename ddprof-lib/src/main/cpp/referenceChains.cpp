/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "referenceChains.h"
#include "common.h"
#include "counters.h"
#include "jniHelper.h"
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
#include <unordered_set>

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
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_BYTES,
                       (jlong)_table_cap * sizeof(FrontierEntry));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_CAPACITY, _table_cap);
}

FrontierTable::~FrontierTable() {
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_BYTES,
                       -(jlong)_table_cap * sizeof(FrontierEntry));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_CAPACITY, -_table_cap);
  free(_table);
}

void FrontierTable::resetCapacityForTest(int max_cap) {
  _table_lock.lock();
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_BYTES,
                       -(jlong)_table_cap * sizeof(FrontierEntry));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_CAPACITY, -_table_cap);
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
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_BYTES,
                       (jlong)_table_cap * sizeof(FrontierEntry));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_CAPACITY, _table_cap);
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
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_BYTES,
                       (jlong)(newcap - _table_cap) * sizeof(FrontierEntry));
  Counters::increment(REFERENCE_CHAIN_FRONTIER_TABLE_CAPACITY,
                       newcap - _table_cap);
  _table = tmp;
  _table_cap = newcap;
  return _table_cap >= required_cap;
}

bool FrontierTable::insert(jlong tag, jlong parent_tag, u32 referrer_klass,
                            u32 depth, u8 state, u8 root_kind) {
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
  _table[idx].root_kind = root_kind;
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

bool FrontierTable::lookupLocked(jlong tag, FrontierEntry *out) const {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return false;
  }
  int idx = (int)(tag - 1);
  if (idx < _table_size) {
    *out = _table[idx];
    return true;
  }
  return false;
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

void FrontierTable::updateRootKind(jlong tag, u8 root_kind) {
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return;
  }
  int idx = (int)(tag - 1);

  _table_lock.lock();
  if (idx < _table_size) {
    _table[idx].root_kind = root_kind;
  }
  _table_lock.unlock();
}

bool FrontierTable::reconstructChain(jlong target_tag,
                                      std::vector<u32> *out_chain,
                                      u8 *out_root_kind) {
  FrontierEntry entry{};
  if (!lookup(target_tag, &entry)) {
    return false;
  }

  std::vector<u32> chain;
  jlong tag = target_tag;
  u8 root_kind = 0;
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
    root_kind = entry.root_kind;
    tag = entry.parent_tag;
  }
  if (tag != 0) {
    // Ran past the defensive hop bound without reaching a root-attached
    // entry (parent_tag == 0) - a corrupted/cyclic chain. Report failure
    // rather than returning a truncated, possibly-misleading chain.
    return false;
  }

  *out_chain = std::move(chain);
  if (out_root_kind != nullptr) {
    // The loop's last iteration is always the root-attached entry (the one
    // whose parent_tag == 0 that just ended the loop), so root_kind here is
    // that entry's own FrontierEntry::root_kind.
    *out_root_kind = root_kind;
  }
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

void ReferenceChainTracker::autoTuneDefaults(Arguments &args) {
  // Only tune defaults the operator did not set explicitly.
  const u8 tuned = args._reference_chains_tuned_mask;

  // Max heap is resolved by LivenessTracker::initialize_table() at this
  // point (ObjectSampler::start() -> LivenessTracker::start() runs
  // before ReferenceChainTracker::start() in Profiler::start()).
  jlong max_heap = LivenessTracker::instance()->maxHeapBytes();
  if (max_heap <= 0) {
    return; // can't tune without heap size
  }

  // Available processors from JVMTI (cached by FlightRecorder, but we
  // can query JVMTI directly here).
  jint nprocs = 1;
  jvmtiEnv *jvmti = VM::jvmti();
  if (jvmti != nullptr) {
    jvmti->GetAvailableProcessors(&nprocs);
  }
  if (nprocs < 1) nprocs = 1;

  // Heap size in MiB.
  double heap_mib = (double)max_heap / (1024.0 * 1024.0);

  // --- Budget (edges per BFS pass) ---
  // Scale with sqrt(heap_mib): a 4 GiB heap gets 2x, a 16 GiB heap
  // gets 4x, a 64 GiB heap gets 8x the default 1000. This keeps the
  // per-pass safepoint pause proportional to sqrt(heap) — the
  // number of edges explored per pass grows, but not quadratically.
  if (!(tuned & REF_CHAINS_TUNED_BUDGET)) {
    int scaled = (int)(DEFAULT_REFERENCE_CHAINS_BUDGET * std::sqrt(heap_mib / 512.0));
    args._reference_chains_budget = std::max(DEFAULT_REFERENCE_CHAINS_BUDGET,
        std::min(scaled, MAX_REFERENCE_CHAINS_BUDGET));
  }

  // --- First-pass budget ---
  // The root enumeration pass is one-shot per search and can
  // afford a much larger budget. Scale it 10x the per-pass budget
  // so the first pass covers more roots.
  if (!(tuned & REF_CHAINS_TUNED_FIRST_PASS_BUDGET)) {
    int fpb = args._reference_chains_budget * 10;
    args._reference_chains_first_pass_budget = std::min(fpb,
        MAX_REFERENCE_CHAINS_FIRST_PASS_BUDGET);
  }

  // --- TTL (per-search wall-clock lifetime) ---
  // The search needs enough time to cover the heap at the tuned
  // budget. At ~1 pass/sec, TTL_seconds >= heap_edges / budget.
  // We don't know heap_edges, but it scales with heap size. Use
  // heap_mib as a proxy: TTL = base_ttl * (heap_mib / 512),
  // clamped to [60s, 30min].
  if (!(tuned & REF_CHAINS_TUNED_TTL)) {
    long scaled_ttl = (long)(DEFAULT_REFERENCE_CHAINS_TTL_MS * (heap_mib / 512.0));
    scaled_ttl = std::max(DEFAULT_REFERENCE_CHAINS_TTL_MS, std::min(scaled_ttl,
        (long)(30 * 60 * 1000))); // 30 min max
    args._reference_chains_ttl_ms = scaled_ttl;
  }

  // --- Frontier cap ---
  // The frontier grows with the number of edges admitted per
  // pass. Scale with budget so a larger budget doesn't
  // immediately hit the cap.
  if (!(tuned & REF_CHAINS_TUNED_FRONTIER_CAP)) {
    int scaled_cap = DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP *
        (args._reference_chains_budget / DEFAULT_REFERENCE_CHAINS_BUDGET);
    args._reference_chains_frontier_cap = std::max(
        DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP,
        std::min(scaled_cap, MAX_REFERENCE_CHAINS_FRONTIER_CAP));
  }

  // --- Pause target ---
  // More available processors = the JVM can afford a slightly
  // longer per-pass safepoint without impacting application
  // throughput. Scale linearly: 1 core = 5ms, 4 cores = 10ms,
  // 8 cores = 15ms, capped at 50ms.
  if (!(tuned & REF_CHAINS_TUNED_PAUSE_TARGET)) {
    long scaled_pause = DEFAULT_REFERENCE_CHAINS_PAUSE_TARGET_MS *
        (1 + (nprocs - 1) / 3);
    args._reference_chains_pause_target_ms = std::min(scaled_pause, (long)50);
  }

  // --- Pain budget percent ---
  // More cores = more spare capacity for background work.
  // Scale: 1 core = 1%, 4 cores = 2%, 8 cores = 3%, capped at 5%.
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

  // Auto-tune defaults that the operator did not set explicitly,
  // based on max heap size and available processors. Must run before
  // _configured_frontier_cap is read below.
  autoTuneDefaults(args);

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
  // Budget-borrowing (referenceChains.h's _borrowed_budget comment): reset
  // alongside the rest of the pacing controller's state, so a restarted
  // search never inherits headroom earned by a previous one.
  _borrowed_budget = 0;
  _consecutive_under_target_passes = 0;
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
  _pain_budget_refill_rate = std::max(args._reference_chains_pain_budget_percent, 0) / 100.0;

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
  if (!_enabled || _running.load(std::memory_order_acquire)) {
    return;
  }
  // Reset from any previous stopThread() call - a dynamic-attach profiler
  // can go through multiple start()/stop() cycles in one JVM lifetime (this
  // class's own start()/stop() header comments), and a stale abort request
  // left set from the prior cycle would make heapReferenceCallback() abort
  // this new cycle's very first pass instantly.
  _abort_pass_requested.store(false, std::memory_order_relaxed);

  // Same reasoning as _abort_pass_requested above, for a different stale-state
  // hazard: expandFrontier()'s _cached_object_class[_jni] is keyed on JNIEnv*
  // identity to detect a fresh attach, but a new pthread's VM::attachThread()
  // (threadLoop(), below) can be handed back a JNIEnv* the JVM already freed
  // and is now reusing for this new session - the pointer value alone cannot
  // distinguish "still this session" from "coincidentally the same address as
  // a prior, already-detached session". A prior session's now-dangling local
  // ref would then look "cached and valid" to that identity check and get
  // passed straight into NewObjectArray(). stopThread() already joined that
  // prior session's thread before this method can run (Profiler::stop()/
  // start() always pair stopThread()+start() sequentially), so it is safe to
  // force the cache to re-resolve unconditionally on this new session's first
  // expandFrontier() call rather than trust the old JNIEnv* comparison.
  _cached_object_class = nullptr;
  _cached_object_class_jni = nullptr;

  // Publish _running=true *before* creating the thread, not after. If the
  // OS schedules the new thread ahead of the parent, threadLoop()'s startup
  // check (`while (_running.load(...))`) would otherwise be racing against
  // this store: the child could see the still-`false` initial value, fall
  // straight through the loop, detach and exit - and the parent would then
  // publish `true` regardless, leaving startThread() reporting the tracker
  // as running while no BFS thread is actually alive for the rest of the
  // recording. pthread_create() itself is the fix's synchronization point:
  // POSIX guarantees everything the calling thread writes before this call
  // is visible to the new thread once it starts running, so ordering the
  // store first removes the race outright rather than narrowing it. Roll
  // back on a failed create so a later startThread() call is not blocked by
  // a stale `_running=true` with no thread behind it. stopThread() is only
  // ever called after this method has returned (Profiler::start()/stop()
  // pair the two sequentially - see this class's own start()/stop() header
  // comments), so its use of _thread below is unaffected by this reordering.
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
    ReferenceChainTracker *tracker;
    ~Cleanup() {
      // Drop the cached java/lang/Object local ref (and the JNIEnv* it was
      // resolved on) before detaching: DetachCurrentThread() invalidates
      // every local ref this attach ever created, but _cached_object_class
      // and _cached_object_class_jni are tracker-lifetime fields that
      // survive into the next start()'s brand-new BFS thread/attach. If the
      // JVM happens to hand that next attach the same JNIEnv* address (JNIEnv
      // structs are heap-allocated per attach and can be reused once freed),
      // the "_cached_object_class_jni != jni" check in expandFrontier()
      // would wrongly treat the now-dangling local ref as still valid.
      // Clearing both here forces an unconditional FindClass() on the first
      // expandFrontier() call of the next attach instead.
      tracker->_cached_object_class = nullptr;
      tracker->_cached_object_class_jni = nullptr;
      VM::detachThread();
    }
  } cleanup{this};
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
  while (_running.load(std::memory_order_acquire)) {
    // Fixed ~1s cadence, no early wake on GC (see onGCFinish()'s own
    // comment) - stopThread() still interrupts this via its own
    // pthread_kill so shutdown stays prompt.
    OS::sleep(_effective_cadence_ns);
    if (!_running.load(std::memory_order_acquire)) {
      break;
    }

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

    // No fast-path skip here: shouldRunPass() below already returns false
    // cheaply (a couple of atomic loads/comparisons, no JVMTI call) for a
    // RUNNING search with no new GC and cadence not yet elapsed. An earlier
    // revision additionally gated this on hasLeakSignal() (LivenessTracker's
    // population-trend signal, also used by canAffordNewSearch() below to gate
    // the first-ever search and every restart), but that signal answers "is
    // there a leak candidate right now", which is unrelated to whether an
    // already-RUNNING search's own frontier still has pending work - gating a
    // RUNNING search's every pass on it would stall that search's own
    // convergence for as long as no leak candidate happens to be visible,
    // even with GC epochs advancing or cadence elapsed. hasLeakSignal()
    // remains the right gate for starting a *new* search, whether that is the
    // first one ever or a restart of a *terminal* one (shouldRunPass()'s own
    // canAffordNewSearch() call).
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
    // Same gate as a restart (canAffordNewSearch() below) - a brand-new
    // tracker must not pay for the first whole-heap walk/tagging pass either
    // when there is no leak candidate to justify it. The pain-budget half is
    // always a no-op here (nothing has ever been spent yet), so this reduces
    // to hasLeakSignal() in practice, but sharing the one gate keeps both
    // call sites from drifting apart.
    if (!canAffordNewSearch(now_ns)) {
      return false;
    }
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
  double seconds_to_oom = LivenessTracker::instance()->secondsToOOM();
  if (seconds_to_oom >= 0 && seconds_to_oom < OOM_URGENT_THRESHOLD_S) {
    // Heap-wide floor is rising fast enough that OOM is imminent - don't
    // wait for a specific klass to clear selectLeakCandidates()'s own
    // per-klass ring-fill/hysteresis gate; see OOM_URGENT_THRESHOLD_S's own
    // comment (referenceChains.h) for why that gate alone is too slow here.
    // canAffordNewSearch() can still defer this via the pain-budget check it
    // runs before calling this method (this method's own header comment).
    TEST_LOG("ReferenceChainTracker::hasLeakSignal -> true (secondsToOOM=%.1f < "
             "OOM_URGENT_THRESHOLD_S=%.1f)",
             seconds_to_oom, OOM_URGENT_THRESHOLD_S);
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
  _priority_expand.clear();
  _last_pass_gc_finish_epoch = 0;
  store(_last_pass_ns, (u64)0);
  store(_passes_run, 0);
  // Reset back to their just-constructed values (0 / -1) like every other
  // per-search field this method touches: resolveLoadedClasses() and
  // admitStaticFieldRoots() must both run unconditionally on the restarted
  // search's first pass, exactly as they do for a brand-new tracker.
  _last_resolved_class_count = 0;
  _last_static_field_class_count = -1;
  // _resolved_chains is intentionally left intact: a chain resolved by the
  // finishing search stays cached (and keeps being re-emitted on every dump)
  // across the restart, since it describes a sample that is still live. The
  // restarted search re-tags that sample under a fresh _search_start_ns, and
  // pollWatchedTargets() refreshes the cached entry then (its own comment);
  // it prunes the entry if the sample has since been collected.
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
  // Reset the pain budget entirely so a fresh test starts from zero debt,
  // independent of how much wall-clock time has elapsed since the last
  // test's spend(). Without this, a fast CI runner (musl, small heap,
  // no GC pauses) may not have drained enough debt between tests.
  _pain_budget = PainBudget(_pain_budget_refill_rate);

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
  _priority_expand.clear();
  _last_pass_gc_finish_epoch = 0;
  store(_last_pass_ns, (u64)0);
  store(_passes_run, 0);

  // Unlike restartSearch(), which deliberately keeps _resolved_chains alive
  // across a production restart, a test reset starts from a blank cache so
  // one test's resolved chains cannot leak into the next.
  _resolved_chains_lock.lock();
  _resolved_chains.clear();
  _resolved_chains_lock.unlock();

  // Restart the BFS thread against this freshly reset state - startThread()
  // itself clears _abort_pass_requested, so the new thread's very first
  // pass is not instantly aborted by the flag stopThread() just set above.
  startThread();
}

long ReferenceChainTracker::pendingExpandPositionForTest(jlong tag) const {
  if (tag == 0) {
    return -2;
  }
  // _priority_expand drains first (expandFrontier()'s own comment), so its
  // entries are reported as coming before _pending_expand's.
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

  // ARRAY-HOLDER BATCHING: when non-null, expandFrontier() is driving a
  // one-hop expansion of a batch of boundary objects passed to a single
  // FollowReferences(initial_object=holder_array) call. heapReferenceCallback()
  // then descends ONLY into objects whose tag is in this set (the boundary
  // objects we deliberately put in the array), and returns "do not descend"
  // (0) for everything else - so a freshly-admitted child is tagged but its
  // own subtree is left for a later pass, and an already-expanded object from
  // a prior pass is never re-traversed. Null on the whole-heap first pass
  // (runPass()'s !_search_started branch) and IterateOverReachableObjects
  // root enumeration, which keep the unconditional-descend behavior.
  std::unordered_set<jlong> *batch_tags = nullptr;

  // Set only by admitStaticFieldRoots(): the seed holder array for that
  // sweep holds loaded-class objects (negative-tagged by
  // resolveLoadedClasses(), see the *tag_ptr < 0 branch below), and the
  // whole point of the sweep is to walk past that holder->class edge into
  // each class's own outgoing references - chiefly STATIC_FIELD - which the
  // *tag_ptr < 0 check would otherwise stop cold before FollowReferences
  // ever gets to report them. Left false everywhere else (expandFrontier()'s
  // batching, root enumeration, the whole-heap first pass), where a
  // negative-tagged referee must never be descended into.
  bool static_field_seed = false;

  // Amortizes tracker->_pass_deadline_ns's OS::nanotime() check (heapReference
  // Callback()/heapRootCallback() run once per visited edge/root - checking
  // wall-clock on literally every call would add real overhead on a large
  // heap) - checked only every 4096th call, local to this ctx so each of
  // runPassManualWalk()'s several sub-calls (root enum, static-field sweep,
  // expandFrontier(), rotation) starts its own count.
  int deadline_check_counter = 0;

  // True while expandFrontier() is walking a batch drawn from
  // _priority_expand (a rotation-selected, already-EXPANDED parent) rather
  // than the ordinary _pending_expand backlog - see _priority_expand's own
  // comment. Newly admitted children inherit the fast lane so the whole
  // re-discovered subtree, not just the immediate child, skips the backlog.
  bool admit_priority = false;
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

  if (ctx->tracker->_pass_deadline_ns != 0 &&
      (++ctx->deadline_check_counter & 0xFFF) == 0 &&
      OS::nanotime() >= ctx->tracker->_pass_deadline_ns) {
    // This pass has run past its wall-clock share (see _pass_deadline_ns's
    // own comment) - treat it exactly like ordinary budget exhaustion so it
    // ends early without abandoning the search; a later pass re-enumerates
    // whatever roots/edges this one didn't get to.
    ctx->truncated = true;
    return JVMTI_VISIT_ABORT;
  }

  if (*tag_ptr < 0) {
    if (ctx->static_field_seed &&
        reference_kind == JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT &&
        referrer_tag_ptr != nullptr && *referrer_tag_ptr == 0) {
      // admitStaticFieldRoots()'s own holder[i] -> class edge: referrer_tag_ptr
      // points at the transient, never-tagged seed array itself (tag 0), not
      // at a frontier-admitted parent. Continue the walk into this class's
      // own outgoing references - static fields chief among them - instead
      // of stopping here; that is the entire purpose of the sweep. The class
      // object itself is still never admitted into the frontier (tag_ptr is
      // left untouched, so it stays negative).
      return JVMTI_VISIT_OBJECTS;
    }
    // Referee is a class object already tagged negative by
    // resolveLoadedClasses() (that pre-pass runs before FollowReferences in
    // runPass(), so every loaded class already carries a negative tag by
    // this point). Never admit a class object into the frontier as if it
    // were an ordinary retained instance, and - outside the
    // admitStaticFieldRoots() seed edge handled above - never expand from a
    // class's own metadata graph (static fields, superclass, interfaces,
    // constant pool, class loader, ...). Out of scope per the design doc's
    // non-goals (no field-level/exhaustive paths) and keeps the walk bounded
    // to the instance-reachability graph that actually explains "why is
    // this object alive".
    return 0;
  }
  if (reference_kind == JVMTI_HEAP_REFERENCE_CLASS ||
      reference_kind == JVMTI_HEAP_REFERENCE_SYSTEM_CLASS) {
    // Definitionally a class by reference_kind (CLASS: "reference from an
    // object to its class"; SYSTEM_CLASS: a root reference to a class) even
    // if resolveLoadedClasses() failed to resolve/tag this particular one
    // (e.g. a transient StringDictionary contention failure) and its tag is
    // therefore not yet negative. Same non-goal as above: never expand from
    // or admit a class object.
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
    u32 referrer_klass = ctx->tracker->classTags()->resolve(class_tag);
    // reference_kind describes this admitting edge; only meaningful for a
    // root-attached entry (parent_tag == 0) - see FrontierEntry::root_kind's
    // own comment for why a non-root entry's edge kind is not recorded.
    u8 root_kind = parent_tag == 0 ? (u8)reference_kind : 0;
    ReferenceChainTracker::AdmitResult result = ctx->tracker->admitObject(
        ctx->frontier, ctx->hop_cap, ctx->budget, &ctx->edges_admitted,
        tag_ptr, parent_tag, referrer_klass, depth, root_kind,
        ctx->admit_priority);
    switch (result) {
    case ReferenceChainTracker::AdmitResult::BUDGET_EXHAUSTED:
      ctx->truncated = true;
      return JVMTI_VISIT_ABORT;
    case ReferenceChainTracker::AdmitResult::FRONTIER_CAP_HIT:
      // Frontier-size cap hit (FrontierTable::insert() returned false
      // without partially writing) - stop admitting new entries and report
      // the truncation (design doc: "stop admitting new entries ... report
      // it"), rather than silently dropping this object and continuing.
      // Distinct from ordinary budget exhaustion above - runPass() abandons
      // the whole search for this, not just this pass.
      ctx->truncated = true;
      ctx->frontier_cap_hit = true;
      return JVMTI_VISIT_ABORT;
    default:
      // ADMITTED, or HOP_CAP/ALREADY_ADMITTED (neither reachable here: the
      // hop-cap check above already returned before this branch, and
      // *tag_ptr == 0 rules out ALREADY_ADMITTED) - nothing further to do.
      break;
    }
  }

  if (ctx->batch_tags != nullptr) {
    // ARRAY-HOLDER BATCHING one-hop descent control (see PassContext::
    // batch_tags). Descend only into this pass's boundary objects so the
    // single FollowReferences(holder_array) call expands exactly one hop:
    // a boundary object yields its direct children (which get tagged above),
    // but those children are not themselves descended into, and any
    // already-expanded object from a prior pass is skipped rather than
    // re-traversed.
    jlong my_tag = *tag_ptr;
    if (my_tag > 0 && ctx->batch_tags->count(my_tag) != 0) {
      return JVMTI_VISIT_OBJECTS;
    }
    return 0;
  }

  return JVMTI_VISIT_OBJECTS;
}

ReferenceChainTracker::AdmitResult ReferenceChainTracker::admitObject(
    FrontierTable *frontier, int hop_cap, int budget, int *edges_admitted,
    jlong *tag_ptr, jlong parent_tag, u32 referrer_klass, u32 depth,
    u8 root_kind, bool priority) {
  if (*tag_ptr != 0) {
    return AdmitResult::ALREADY_ADMITTED;
  }
  if (depth >= (u32)hop_cap) {
    return AdmitResult::HOP_CAP;
  }
  if (*edges_admitted >= budget) {
    return AdmitResult::BUDGET_EXHAUSTED;
  }
  jlong tag = nextTag();
  if (!frontier->insert(tag, parent_tag, referrer_klass, depth,
                         FrontierEntryState::FRONTIER, root_kind)) {
    return AdmitResult::FRONTIER_CAP_HIT;
  }
  *tag_ptr = tag;
  (*edges_admitted)++;
  // Queue for expandFrontier()/markAllFrontierExpanded() - see
  // _pending_expand's/_priority_expand's own declaration comments for why
  // this replaces a scan over the admitted range, and for why a
  // rotation-discovered child (priority=true) skips the ordinary backlog.
  if (priority) {
    _priority_expand.push_back(tag);
  } else {
    _pending_expand.push_back(tag);
  }
  return AdmitResult::ADMITTED;
}

bool ReferenceChainTracker::maybeUpgradeRootAttachedRootKind(
    FrontierTable *frontier, jlong tag, u8 new_root_kind) {
  FrontierEntry entry{};
  if (!frontier->lookup(tag, &entry)) {
    return false;
  }
  if (entry.parent_tag != 0) {
    // Not root-attached - per this phase's option (a) resolution of the
    // parent_tag==0/root_kind invariant conflict (referenceChains.h's
    // FrontierEntry::root_kind comment), only a root-context update may ever
    // write a non-zero root_kind, and only onto an entry that is already
    // root-attached. An object that happens to also be a genuine GC root but
    // was first discovered as a non-root child (e.g. via frontier
    // expansion) keeps its original, non-root attribution - a known,
    // documented limitation rather than an attempt to retroactively flip
    // parent_tag to 0, which reconstructChain()'s parent-link walk does not
    // support.
    return false;
  }
  if (rootKindDurability(new_root_kind) <= rootKindDurability(entry.root_kind)) {
    return false;
  }
  frontier->updateRootKind(tag, new_root_kind);
  return true;
}

std::vector<jlong>
ReferenceChainTracker::collectStaleRootKindEntriesForRotation(
    int max_count) {
  std::vector<jlong> selected;
  int table_size = _frontier->size();
  if (max_count <= 0 || table_size <= 0) {
    return selected;
  }
  if (_root_kind_rotation_cursor <= 0 ||
      _root_kind_rotation_cursor > table_size) {
    _root_kind_rotation_cursor = 1;
  }

  // Held for the whole sweep below (potentially wrapping all the way around
  // table_size) rather than once per tag via lookup() - the same rationale
  // as collectStaleExpandedEntriesForRotation()'s own lockShared() use: a
  // per-tag SpinLock acquisition would double this scan's cost under a large
  // frontier table.
  jlong start_tag = _root_kind_rotation_cursor;
  jlong tag = start_tag;
  _frontier->withSharedLock([&](const FrontierTable *frontier) {
    do {
      FrontierEntry entry{};
      if (frontier->lookupLocked(tag, &entry) &&
          entry.state == FrontierEntryState::EXPANDED &&
          entry.parent_tag == 0 && isTransientRootKind(entry.root_kind) &&
          !isQueuedForRotation(tag)) {
        selected.push_back(tag);
        _priority_expand.push_back(tag);
        if ((int)selected.size() >= max_count) {
          tag = tag % table_size + 1;
          break;
        }
      }
      tag = tag % table_size + 1;
    } while (tag != start_tag);
  });

  _root_kind_rotation_cursor = tag;
  return selected;
}

std::vector<jlong>
ReferenceChainTracker::collectStaleExpandedEntriesForRotation(
    int max_count) {
  std::vector<jlong> selected;
  int table_size = _frontier->size();
  if (max_count <= 0 || table_size <= 0) {
    return selected;
  }
  // Always sweep from the lowest tag, instead of resuming from where the
  // last call left off: low tags are the earliest-admitted entries, which
  // tend to be long-lived infrastructure objects (caches, maps) closest to
  // a GC root, while a round-robin cursor gives every entry equal turn and
  // takes O(table_size / max_count) passes to cycle back to any one of
  // them - far too slow once the table holds tens of thousands of entries.
  //
  // This scan's own EXPANDED criterion is a strict superset of
  // collectStaleRootKindEntriesForRotation()'s (which additionally requires
  // parent_tag == 0 and a transient root_kind), and that function always
  // runs first within the same pass and pushes its picks onto
  // _priority_expand before this one runs - so without a check here, a tag
  // it already selected would be pushed a second time, and
  // expandFrontier() re-expands each deque entry as its own independent
  // unit of work. isQueuedForRotation() also covers any entries still
  // sitting there from a prior pass's truncated batch (expandFrontier()
  // leaves those at the front of the queue for a later retry rather than
  // popping them).
  // Held for the whole scan below instead of once per tag via lookup() - a
  // per-tag SpinLock acquisition/release would double the cost of this
  // O(table_size) sweep under a large frontier table (the exact scenario -
  // tens of thousands of entries - this rotation mechanism targets).
  jlong tag = 1;
  _frontier->withSharedLock([&](const FrontierTable *frontier) {
    while (tag <= table_size && (int)selected.size() < max_count) {
      FrontierEntry entry{};
      if (frontier->lookupLocked(tag, &entry) &&
          entry.state == FrontierEntryState::EXPANDED &&
          !isQueuedForRotation(tag)) {
        selected.push_back(tag);
        _priority_expand.push_back(tag);
      }
      tag++;
    }
  });
  return selected;
}

// ---------------------------------------------------------------------------
// Manual walk driver - IterateOverReachableObjects root/stack-ref enumeration
// plus expandFrontier()'s batched array-holder FollowReferences hop expansion.
// The only path driven by runPass() below.
// ---------------------------------------------------------------------------

namespace {
// jvmtiHeapRootKind (IterateOverReachableObjects's root/stack-ref callbacks,
// ordinals 1-7) and jvmtiHeapReferenceKind (FrontierEntry::root_kind's own
// type, FollowReferences' callback, ordinals 8/21-27) are different, disjoint
// enums per the real jvmti.h - storing a raw jvmtiHeapRootKind value into
// root_kind unmodified would make flightRecorder.cpp's rootKindName() report
// "unknown" for every root-callback-attributed chain. Every jvmtiHeapRootKind
// value maps onto its jvmtiHeapReferenceKind namesake; there is no root-kind
// equivalent of STATIC_FIELD (that value only ever arises from
// heapReferenceCallback()'s own referrer-is-a-tagged-class case), so it is
// never produced here.
u8 translateHeapRootKind(jvmtiHeapRootKind root_kind) {
  switch (root_kind) {
  case JVMTI_HEAP_ROOT_JNI_GLOBAL:
    return (u8)JVMTI_HEAP_REFERENCE_JNI_GLOBAL;
  case JVMTI_HEAP_ROOT_SYSTEM_CLASS:
    return (u8)JVMTI_HEAP_REFERENCE_SYSTEM_CLASS;
  case JVMTI_HEAP_ROOT_MONITOR:
    return (u8)JVMTI_HEAP_REFERENCE_MONITOR;
  case JVMTI_HEAP_ROOT_STACK_LOCAL:
    return (u8)JVMTI_HEAP_REFERENCE_STACK_LOCAL;
  case JVMTI_HEAP_ROOT_JNI_LOCAL:
    return (u8)JVMTI_HEAP_REFERENCE_JNI_LOCAL;
  case JVMTI_HEAP_ROOT_THREAD:
    return (u8)JVMTI_HEAP_REFERENCE_THREAD;
  case JVMTI_HEAP_ROOT_OTHER:
  default:
    return (u8)JVMTI_HEAP_REFERENCE_OTHER;
  }
}

} // namespace

jvmtiIterationControl JNICALL ReferenceChainTracker::heapRootCallback(
    jvmtiHeapRootKind root_kind, jlong class_tag, jlong size, jlong *tag_ptr,
    void *user_data) {
  PassContext *ctx = (PassContext *)user_data;
  if (ctx->tracker->_abort_pass_requested.load(std::memory_order_relaxed)) {
    ctx->truncated = true;
    return JVMTI_ITERATION_ABORT;
  }
  if (ctx->truncated) {
    return JVMTI_ITERATION_ABORT;
  }

  u32 referrer_klass = ctx->tracker->classTags()->resolve(class_tag);
  u8 translated_root_kind = translateHeapRootKind(root_kind);
  AdmitResult result = ctx->tracker->admitObject(
      ctx->frontier, ctx->hop_cap, ctx->budget, &ctx->edges_admitted, tag_ptr,
      /*parent_tag=*/0, referrer_klass, /*depth=*/0, translated_root_kind);
  switch (result) {
  case AdmitResult::BUDGET_EXHAUSTED:
    ctx->truncated = true;
    return JVMTI_ITERATION_ABORT;
  case AdmitResult::FRONTIER_CAP_HIT:
    ctx->truncated = true;
    ctx->frontier_cap_hit = true;
    return JVMTI_ITERATION_ABORT;
  case AdmitResult::ALREADY_ADMITTED:
    // Rediscovery via a second heap root - either later in this same pass's
    // root enumeration, or in a later pass re-enumerating roots entirely
    // (design doc's durability tie-break / "opportunistic upgrade", "Fix for
    // root-attribution staleness" point 1 and Phase 5 item 1): apply the
    // same durability ranking admitObject() would have used on first
    // discovery, upgrading root_kind if this root is more durable than
    // whatever is currently recorded. Restricted to root-attached entries
    // only (parent_tag == 0) - see maybeUpgradeRootAttachedRootKind()'s own
    // comment for why.
    ctx->tracker->maybeUpgradeRootAttachedRootKind(ctx->frontier, *tag_ptr,
                                                    translated_root_kind);
    break;
  default:
    break;
  }
  return JVMTI_ITERATION_CONTINUE;
}

jvmtiIterationControl JNICALL ReferenceChainTracker::stackRefCallback(
    jvmtiHeapRootKind root_kind, jlong class_tag, jlong size, jlong *tag_ptr,
    jlong thread_tag, jint depth, jmethodID method, jint slot,
    void *user_data) {
  // Stack-local/JNI-local roots carry thread/frame/slot detail JVMTI reports
  // via this callback's richer shape, but FrontierEntry has nowhere to
  // record it (depth/method/slot are not part of the record) - admission is
  // otherwise identical to heapRootCallback() above, so this just forwards.
  return heapRootCallback(root_kind, class_tag, size, tag_ptr, user_data);
}

void ReferenceChainTracker::runPassManualWalk(jvmtiEnv *jvmti, JNIEnv *jni,
                                               bool run_root_enum,
                                               int root_enum_budget,
                                               int expand_budget,
                                               int *edges_admitted,
                                               bool *truncated,
                                               bool *frontier_cap_hit) {
  assert(!t_inGCCallback &&
         "IterateOverReachableObjects/FollowReferences are JVMTI "
         "Heap-category calls and must not be made from "
         "GarbageCollectionStart/Finish");

  // Shared wall-clock ceiling for this whole call's static-field sweep,
  // expandFrontier(), and rotation sub-calls below (see _pass_deadline_ns's
  // own comment) - deliberately NOT applied to root/stack-ref enumeration
  // itself, which is instead cadence-gated by run_root_enum/
  // ROOT_ENUM_MIN_INTERVAL_NS.
  _pass_deadline_ns = _pause_target_ms > 0
                          ? OS::nanotime() + (u64)_pause_target_ms * 1000000ULL
                          : 0;

  *edges_admitted = 0;
  *truncated = false;
  *frontier_cap_hit = false;

  // Reserve a slice for rotation up front (see ROTATION_RESERVED_BUDGET's
  // own comment) so it still gets to run this pass even when ordinary work
  // below spends everything else and truncates. Also capped at half of
  // expand_budget: without that cap, a pacing-throttled pass (expand_budget
  // down near MIN_EFFECTIVE_BUDGET) would hand rotation its full fixed
  // reservation and leave ordinary expansion with 0 - exactly the priority
  // inversion this reservation exists to avoid, just for the other side.
  // Capping at half means each side degrades proportionally as pacing
  // throttles down, instead of either one hitting a hard 0.
  int rotation_reserved_budget =
      std::min(expand_budget / 2, ROTATION_RESERVED_BUDGET);
  int budget = expand_budget - rotation_reserved_budget;

  // Root/stack-ref enumeration alone (unlike a root-seeded FollowReferences
  // call on the fallback path) never discovers a root's own transitive
  // children - IterateOverReachableObjects's root/stack-ref callbacks are
  // given no oop, only a tag_ptr (see heapRootCallback()'s own comment) - so
  // even when it runs this pass, the expandFrontier() call below is still
  // needed to make any further progress. Gated behind run_root_enum (see
  // ROOT_ENUM_MIN_INTERVAL_NS's own comment) since the call's fixed
  // root-walk-and-dispatch cost is paid in full every time it runs,
  // regardless of budget.
  if (run_root_enum) {
    PassContext ctx;
    ctx.tracker = this;
    ctx.frontier = _frontier;
    ctx.hop_cap = _hop_cap;
    ctx.budget = root_enum_budget;
    ctx.edges_admitted = 0;
    ctx.truncated = false;
    ctx.frontier_cap_hit = false;

    jvmtiError root_err = jvmti->IterateOverReachableObjects(
        heapRootCallback, stackRefCallback, /*object_ref_callback=*/nullptr,
        &ctx);

    // expand_budget is spent independently of root_enum_budget below (see
    // ROOT_ENUM_MIN_INTERVAL_NS's own comment) - ctx.edges_admitted is
    // written straight into *edges_admitted so the static-field/expand/
    // rotation budget math below is never shrunk by whatever root
    // enumeration admitted.
    *edges_admitted = ctx.edges_admitted;
    _last_root_enum_ns = OS::nanotime();

    if (root_err != JVMTI_ERROR_NONE) {
      *truncated = true;
      *frontier_cap_hit = false;
      _root_enum_truncated_last_time = false;
      return;
    }
    if (ctx.truncated) {
      *truncated = true;
      *frontier_cap_hit = ctx.frontier_cap_hit;
      // Only a budget-exhausted truncation (not a frontier-cap-hit, which
      // abandons the search outright) is grounds to retry root enumeration
      // on the very next pass - see _root_enum_truncated_last_time's own
      // comment.
      _root_enum_truncated_last_time = !ctx.frontier_cap_hit;
      return;
    }
    _root_enum_truncated_last_time = false;
  }

  // Static-field roots (SomeClass.staticField -> obj) are not reachable via
  // IterateOverReachableObjects' root/stack-ref callbacks above - see
  // admitStaticFieldRoots()'s own comment - so this pass would otherwise
  // never discover an object retained only that way. Best-effort: failures
  // here do not truncate the pass, they just mean this sweep found nothing
  // new this time around.
  //
  // Only run the sweep when the loaded-class set has actually changed since
  // the last time it completed (same guard shape resolveLoadedClasses() uses
  // for its own GetLoadedClasses()-driven scan, and reusing the count that
  // call already refreshed via resolveLoadedClasses() earlier this same
  // runPass() - see _last_static_field_class_count's own comment). Without
  // this, admitStaticFieldRoots() would re-run its own GetLoadedClasses()
  // call and a FollowReferences over every loaded class - a stop-the-world
  // HeapWalkOperation - on every pass, forever, at the per-second pass
  // cadence, even once every loaded class's static fields have already been
  // swept and no new class has appeared to introduce new ones.
  int expand_phase_edges_admitted = 0;
  if (_last_resolved_class_count != _last_static_field_class_count) {
    int static_field_edges_admitted = 0;
    bool static_field_truncated = false;
    bool static_field_frontier_cap_hit = false;
    int static_field_budget = std::max(budget - expand_phase_edges_admitted, 0);
    admitStaticFieldRoots(jvmti, jni, _hop_cap, static_field_budget,
                          &static_field_edges_admitted, &static_field_truncated,
                          &static_field_frontier_cap_hit);
    expand_phase_edges_admitted += static_field_edges_admitted;
    *edges_admitted += static_field_edges_admitted;
    if (static_field_truncated) {
      *truncated = true;
      *frontier_cap_hit = static_field_frontier_cap_hit;
      if (static_field_frontier_cap_hit) {
        // Frontier-size cap hit while admitting static-field roots is the
        // same "grounds to ABANDON the whole search" outcome
        // BUDGET_EXHAUSTED/FRONTIER_CAP_HIT handling above gives root
        // enumeration - do not spend any more of this pass's budget on the
        // ordinary expansion below.
        return;
      }
    } else {
      // Sweep completed (possibly discovering nothing, if every static field
      // it saw was already ALREADY_ADMITTED) - remember the class count it
      // covered so a later pass with no new classes can skip re-running it.
      // Left unset on a truncated sweep (above) so the next pass retries
      // instead of wrongly treating a still-incomplete sweep as done.
      _last_static_field_class_count = _last_resolved_class_count;
    }
  }

  int expand_edges_admitted = 0;
  bool expand_truncated = false;
  bool expand_frontier_cap_hit = false;
  int remaining_budget = std::max(budget - expand_phase_edges_admitted, 0);
  expandFrontier(jvmti, jni, _hop_cap, remaining_budget,
                 &expand_edges_admitted, &expand_truncated,
                 &expand_frontier_cap_hit);
  expand_phase_edges_admitted += expand_edges_admitted;
  *edges_admitted += expand_edges_admitted;
  *truncated = *truncated || expand_truncated;
  *frontier_cap_hit = expand_frontier_cap_hit;

  // Note: unlike a hard truncation during root/stack-ref enumeration or the
  // static-field sweep above (which return early - the pass never even
  // reached ordinary expansion), a truncated ordinary expansion does NOT
  // skip rotation below: rotation runs on its own reserved slice of budget
  // (see ROTATION_RESERVED_BUDGET's own comment) precisely because ordinary
  // expansion truncates on nearly every pass under a sustained fast-growing
  // backlog, and that is exactly the situation - a mutable field reassigned
  // out from under an already-EXPANDED entry - rotation exists to correct.

  // Bounded rotating re-expansion (design doc's closing section, Phase 5
  // item 3): re-walk a bounded, rotating subset of already-EXPANDED,
  // transiently-root-attributed entries so a durable root discovered
  // elsewhere on a later pass (via maybeUpgradeRootAttachedRootKind() above)
  // gets a chance to be observed even for an entry whose own fields were
  // already fully expanded once. Runs after the ordinary expansion above so
  // it only ever spends whatever budget that left unused, plus its own
  // reserved slice.
  std::vector<jlong> rotation_tags =
      collectStaleRootKindEntriesForRotation(ROOT_KIND_ROTATION_BUDGET);
  // Also re-walk a bounded, rotating subset of EXPANDED entries regardless
  // of root attribution: a mutable field reassigned since an
  // object's one-time expansion - e.g. HashMap.table on resize - is
  // otherwise never observed again, silently orphaning everything only
  // reachable through the field's current value. See
  // collectStaleExpandedEntriesForRotation()'s own comment.
  std::vector<jlong> stale_expanded_tags =
      collectStaleExpandedEntriesForRotation(STALE_EXPANDED_ROTATION_BUDGET);
  if (rotation_tags.empty() && stale_expanded_tags.empty()) {
    return;
  }
  // rotation_reserved_budget + max(budget - expand_phase_edges_admitted, 0) is
  // exactly expand_budget - expand_phase_edges_admitted: budget already IS
  // expand_budget - rotation_reserved_budget (above), and expand_phase_edges_
  // admitted can never exceed budget (the static-field sweep and ordinary
  // expandFrontier() calls above are both capped to budget-derived slices),
  // so the max() is never actually needed to avoid going negative. Folding
  // rotation_reserved_budget back into expand_budget here - rather than
  // subtracting it out and then adding it back - says directly what this
  // value is: whatever of the whole pass's budget the phases above didn't
  // spend.
  int rotation_budget = expand_budget - expand_phase_edges_admitted;
  int rotation_edges_admitted = 0;
  bool rotation_truncated = false;
  bool rotation_frontier_cap_hit = false;
  expandFrontier(jvmti, jni, _hop_cap, rotation_budget,
                 &rotation_edges_admitted, &rotation_truncated,
                 &rotation_frontier_cap_hit);
  *edges_admitted += rotation_edges_admitted;
  // OR, not overwrite: the ordinary expand phase above may have already set
  // these to true (real truncation/cap-hit left in _pending_expand), and a
  // rotation batch that happens to finish cleanly must not erase that -
  // has_pending_frontier (runPass()) and the FRONTIER_CAP abandon check both
  // read these as "did any of this pass's sub-phases truncate/cap-hit", not
  // just the last one that ran.
  *truncated = *truncated || rotation_truncated;
  *frontier_cap_hit = *frontier_cap_hit || rotation_frontier_cap_hit;
}

// ---------------------------------------------------------------------------
// Incremental resumption across passes.
// ---------------------------------------------------------------------------

void ReferenceChainTracker::markAllFrontierExpanded() {
  while (!_priority_expand.empty()) {
    _frontier->markExpanded(_priority_expand.front());
    _priority_expand.pop_front();
  }
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

  // ARRAY-HOLDER BATCHING: expand a whole batch of boundary objects with ONE
  // FollowReferences(initial_object=holder_array) call per BFS level, instead
  // of one FollowReferences PER frontier entry. batch_tags gates
  // heapReferenceCallback() to a single hop (see its own comment). This is
  // the unconditional default expansion path (runPass()'s only non-fallback
  // walk), not a prototype relative to anything else still in the codebase.
  std::unordered_set<jlong> batch_tags;
  ctx.batch_tags = &batch_tags;

  jvmtiHeapCallbacks callbacks;
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.heap_reference_callback = heapReferenceCallback;

  // java/lang/Object element type for the transient frontier-holder array.
  // Cached across calls on this same (attached) JNIEnv rather than re-resolved
  // via a fresh FindClass() every call - expandFrontier() runs roughly once
  // per BFS-thread wake for the tracker's lifetime, and the class never
  // changes, so a per-pass class-loader lookup is unnecessary churn. Without
  // a JNIEnv (some test seams) the array-holder path cannot run; a JNIEnv
  // change (fresh attach) invalidates the cache since the previous call's
  // local ref is only guaranteed valid for that attach's lifetime.
  if (jni != nullptr) {
    if (_cached_object_class_jni != jni) {
      _cached_object_class = jni->FindClass("java/lang/Object");
      if (jniExceptionCheck(jni)) {
        _cached_object_class = nullptr;
      }
      _cached_object_class_jni = jni;
    }
  } else {
    _cached_object_class = nullptr;
    _cached_object_class_jni = nullptr;
  }
  jclass object_class = _cached_object_class;

  bool progress = true;
  while (!ctx.truncated && progress && object_class != nullptr) {
    progress = false;

    // Drain _priority_expand ahead of the ordinary backlog (see its own
    // declaration comment) - a rotation-selected parent's re-discovered
    // children must not queue behind however much of _pending_expand is
    // still outstanding, or the re-discovery never visibly progresses.
    bool from_priority = !_priority_expand.empty();
    std::deque<jlong> &source =
        from_priority ? _priority_expand : _pending_expand;
    ctx.admit_priority = from_priority;
    if (source.empty()) {
      break; // nothing pending
    }

    // Same batch-sizing rationale as before: at most `budget` pending tags
    // per level so GetObjectsWithTags()'s cost stays proportional to what we
    // will actually expand this iteration, not to the whole backlog.
    // Additionally capped at the configured steady per-pass budget
    // (_budget), independent of how large `budget` itself is: the first
    // pass's caller-supplied budget is _first_pass_budget, which can be
    // (and by design, for a whole-JVM root enumeration, routinely is) far
    // larger than the actual pending backlog - e.g. 200000 vs. 81672 roots
    // enumerated. Without this second cap, batch_size collapses to the
    // entire backlog in one shot, building one huge holder array and
    // spending this pass's whole expansion budget on a single
    // FollowReferences call that can fail outright (JNI local-capacity/OOM)
    // with zero progress, stalling every root at the front of
    // _pending_expand for however many later, budget-capped passes it takes
    // to drain that same backlog before any real expansion happens. Capping
    // at _budget keeps every batch - first pass or not - the same size this
    // array-holder mechanism is already proven to handle on every other
    // pass.
    size_t batch_size = std::min(
        source.size(),
        (size_t)std::max(std::min(budget, _budget), 1));
    std::vector<jlong> candidate_tags(source.begin(),
                                       source.begin() + batch_size);

    // Resolve this batch's live boundary objects. GetObjectsWithTags iterates
    // the whole tag map, but does so under a no-safepoint mutex on this
    // (Java) thread - it is NOT a stop-the-world VM operation, unlike the
    // FollowReferences below (jvmtiTagMap.cpp: get_objects_with_tags takes
    // Mutex::_no_safepoint_check_flag and calls entry_iterate directly,
    // whereas follow_references does VMThread::execute()).
    jint resolved_count = 0;
    jobject *resolved_objects = nullptr;
    jlong *resolved_tags = nullptr;
    jvmtiError resolve_err = jvmti->GetObjectsWithTags(
        (jint)candidate_tags.size(), candidate_tags.data(), &resolved_count,
        &resolved_objects, &resolved_tags);
    if (resolve_err != JVMTI_ERROR_NONE) {
      ctx.truncated = true;
      break;
    }

    std::unordered_map<jlong, jobject> live;
    for (jint i = 0; i < resolved_count; i++) {
      live[resolved_tags[i]] = resolved_objects[i];
    }

    // Build the frontier-holder array from the live boundary objects and
    // record their tags so heapReferenceCallback() descends into exactly
    // these (one hop).
    batch_tags.clear();
    jobjectArray holder = nullptr;
    if (resolved_count > 0) {
      jint capacity_err = jni->EnsureLocalCapacity(resolved_count + 16);
      if (capacity_err < 0 || jniExceptionCheck(jni)) {
        // Could not guarantee local-ref headroom for this batch - treat like
        // any other batch-level failure below (JVMTI error / OOM building the
        // holder array): retry this batch on a later pass rather than
        // proceeding into NewObjectArray with no capacity guarantee.
        ctx.truncated = true;
      } else {
        holder = jni->NewObjectArray(resolved_count, object_class, nullptr);
        if (jniExceptionCheck(jni)) {
          // OutOfMemoryError building the holder array (or any other
          // exception NewObjectArray raised) left `holder` null; make sure
          // the pending exception does not survive into the next JNI call
          // below or the next expandFrontier() invocation on this same
          // long-lived BFS-thread JNIEnv (JNI spec: undefined behavior with
          // a pending exception across ordinary JNI calls).
          holder = nullptr;
        }
        if (holder != nullptr) {
          for (jint i = 0; i < resolved_count; i++) {
            jni->SetObjectArrayElement(holder, i, resolved_objects[i]);
            if (jniExceptionCheck(jni)) {
              // e.g. an array-store-class failure. Abort building this
              // batch's holder rather than handing a partially-populated
              // array (with a just-cleared pending exception) to
              // FollowReferences.
              ctx.truncated = true;
              break;
            }
            batch_tags.insert(resolved_tags[i]);
          }
        }
        if (holder == nullptr) {
          // NewObjectArray failed (OOM/local-ref exhaustion) - the
          // FollowReferences call below (which would have discovered this
          // batch's children) never runs. Falling through to the
          // mark-EXPANDED-and-dequeue path further down would silently and
          // permanently drop these still-undiscovered children, so this must
          // be treated exactly like a failed FollowReferences/JVMTI call:
          // retry the batch on a later pass instead.
          ctx.truncated = true;
        } else if (!ctx.truncated) {
          // A single FollowReferences over the holder array expands this whole
          // BFS level in one stop-the-world HeapWalkOperation (instead of one
          // per frontier entry). initial_object=holder means the traversal
          // starts from the array only (never enumerates roots / the whole
          // heap); heapReferenceCallback() returns "descend" for the array's
          // elements (the boundary objects, in batch_tags) and "no descend" for
          // their children, so exactly one hop past the boundary is explored.
          jvmtiError follow_err =
              jvmti->FollowReferences(0, nullptr, holder, &callbacks, &ctx);
          if (follow_err != JVMTI_ERROR_NONE) {
            ctx.truncated = true;
          }
        }
      }
    }

    if (!ctx.truncated) {
      // The whole batch had all its direct children admitted this level:
      // dead entries are pruned, live ones are marked EXPANDED, and all are
      // popped off the front. New children were appended to the back by
      // admitObject() and become the next level's batch.
      for (jlong tag : candidate_tags) {
        if (live.find(tag) == live.end()) {
          _frontier->clear(tag);
        } else {
          _frontier->markExpanded(tag);
        }
        source.pop_front();
      }
      progress = true;
    }
    // else truncated (budget/frontier-cap/JVMTI error): leave the batch at
    // the front of the source queue for a later pass to retry. Re-walking is
    // idempotent - already-admitted children are ALREADY_ADMITTED (not
    // re-counted, not descended), so a retry only admits the remaining
    // children. The while condition (!ctx.truncated) ends the loop here.

    if (holder != nullptr) {
      jni->DeleteLocalRef(holder);
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

  // object_class is NOT deleted here - it is now cached in
  // _cached_object_class and reused across calls on this same JNIEnv (see
  // above), not a per-call local ref.

  if (!ctx.truncated && jni != nullptr && object_class == nullptr &&
      (!_pending_expand.empty() || !_priority_expand.empty())) {
    // FindClass("java/lang/Object") failed for this (attached) JNIEnv, so
    // the batching loop above never ran even though pending frontier work
    // remains. Report truncated rather than leaving *truncated false: the
    // caller (runPassManualWalk()/runPass()) treats false as "no pending
    // frontier work", which would falsely mark the search
    // SearchState::COMPLETED instead of retrying - directly contradicting
    // this subsystem's documented "no silent truncation" requirement (see
    // SearchAbandonReason's header comment).
    ctx.truncated = true;
  }

  *edges_admitted = ctx.edges_admitted;
  *truncated = ctx.truncated;
  *frontier_cap_hit = ctx.frontier_cap_hit;
}

void ReferenceChainTracker::admitStaticFieldRoots(jvmtiEnv *jvmti, JNIEnv *jni,
                                                   int hop_cap, int budget,
                                                   int *edges_admitted,
                                                   bool *truncated,
                                                   bool *frontier_cap_hit) {
  assert(!t_inGCCallback &&
         "GetLoadedClasses/FollowReferences are JVMTI Heap-category calls "
         "and must not be made from GarbageCollectionStart/Finish");
  *edges_admitted = 0;
  *truncated = false;
  *frontier_cap_hit = false;

  if (jni == nullptr) {
    // No JNIEnv to build the holder array on (some test seams) - see
    // expandFrontier()'s own identical guard. Best-effort sweep: nothing
    // discovered this call, not this pass's own truncation.
    return;
  }

  jint class_count = 0;
  jclass *classes = nullptr;
  jvmtiError classes_err = jvmti->GetLoadedClasses(&class_count, &classes);
  if (classes_err != JVMTI_ERROR_NONE) {
    return;
  }
  if (class_count <= 0) {
    if (classes != nullptr) {
      jvmti->Deallocate((unsigned char *)classes);
    }
    return;
  }

  // Same java/lang/Object element-type cache expandFrontier() uses for its
  // own frontier-holder array - shared across both call sites on this same
  // attached JNIEnv rather than a second FindClass() per pass.
  if (_cached_object_class_jni != jni) {
    _cached_object_class = jni->FindClass("java/lang/Object");
    if (jniExceptionCheck(jni)) {
      _cached_object_class = nullptr;
    }
    _cached_object_class_jni = jni;
  }
  jclass object_class = _cached_object_class;

  if (object_class == nullptr ||
      jni->EnsureLocalCapacity(class_count + 16) < 0 ||
      jniExceptionCheck(jni)) {
    for (jint i = 0; i < class_count; i++) {
      jni->DeleteLocalRef(classes[i]);
    }
    jvmti->Deallocate((unsigned char *)classes);
    return;
  }

  jobjectArray holder = jni->NewObjectArray(class_count, object_class, nullptr);
  if (jniExceptionCheck(jni)) {
    // OutOfMemoryError (or any other exception) building the holder -
    // clear it rather than let it survive into the DeleteLocalRef() calls
    // below (JNI spec: undefined behavior with a pending exception across
    // ordinary JNI calls), same as expandFrontier()'s identical case.
    holder = nullptr;
  }
  if (holder != nullptr) {
    for (jint i = 0; i < class_count; i++) {
      jni->SetObjectArrayElement(holder, i, classes[i]);
      if (jniExceptionCheck(jni)) {
        holder = nullptr;
        break;
      }
    }
  }

  for (jint i = 0; i < class_count; i++) {
    jni->DeleteLocalRef(classes[i]);
  }
  jvmti->Deallocate((unsigned char *)classes);

  if (holder == nullptr) {
    // OOM/local-ref exhaustion/array-store failure - skip this pass's sweep
    // rather than treating it like the manual walk's own truncation (see
    // this method's own header comment).
    return;
  }

  PassContext ctx;
  ctx.tracker = this;
  ctx.frontier = _frontier;
  ctx.hop_cap = hop_cap;
  ctx.budget = budget;
  ctx.edges_admitted = 0;
  ctx.truncated = false;
  ctx.frontier_cap_hit = false;
  // Empty (not null) batch_tags forces heapReferenceCallback() to stop at
  // exactly one hop past each class - see this method's own header comment
  // for why a deeper descent here would reintroduce the whole-graph
  // FollowReferences cost the array-holder batching design otherwise avoids.
  std::unordered_set<jlong> empty_batch_tags;
  ctx.batch_tags = &empty_batch_tags;
  // Lets heapReferenceCallback() walk past the holder->class seed edge (see
  // PassContext::static_field_seed's own comment) so this sweep actually
  // reaches each class's static fields instead of stopping at the
  // negative-tagged class object itself.
  ctx.static_field_seed = true;

  jvmtiHeapCallbacks callbacks;
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.heap_reference_callback = heapReferenceCallback;
  jvmtiError follow_err =
      jvmti->FollowReferences(0, nullptr, holder, &callbacks, &ctx);
  jni->DeleteLocalRef(holder);
  if (follow_err != JVMTI_ERROR_NONE) {
    return;
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

  // Every pass is driven by the manual walk (runPassManualWalk() -
  // IterateOverReachableObjects for roots, then a batched array-holder
  // FollowReferences per BFS level in expandFrontier()), on every collector
  // including ZGC. The walk issues only JVMTI heap calls, which run inside
  // the VM_HeapWalkOperation safepoint and honor ZGC's load barriers, so
  // concurrent relocation cannot corrupt it - it reads no raw oop. Batching
  // one hop per level keeps each FollowReferences bounded, avoiding the
  // multi-hundred-ms-to-second STW pauses a whole-graph FollowReferences
  // would impose.
  bool manual_first_pass = !_search_started;
  if (manual_first_pass) {
    _search_started = true;
    store(_search_start_ns, OS::nanotime());
  }

  // Root/stack-ref enumeration alone never discovers a root's transitive
  // children (runPassManualWalk()'s own comment) - there is no "first pass
  // walks the whole graph inline" shortcut here, so every pass (first or
  // resumed) takes the same expand-frontier shape. Root/stack-ref
  // enumeration itself, though, does NOT run on every pass: its fixed
  // native dispatch cost is paid in full regardless of budget (see
  // ROOT_ENUM_MIN_INTERVAL_NS's own comment), so it is cadence-gated to the
  // first pass, a still-truncated retry from last time, or once
  // ROOT_ENUM_MIN_INTERVAL_NS has elapsed since it last ran - not every
  // pass, unlike expandFrontier()'s cheap incremental work below.
  u64 now_ns = OS::nanotime();
  bool run_root_enum = manual_first_pass || _root_enum_truncated_last_time ||
                       (now_ns - _last_root_enum_ns >= ROOT_ENUM_MIN_INTERVAL_NS);

  u64 call_start_ticks = TSC::ticks();
  runPassManualWalk(jvmti, jni, run_root_enum, _first_pass_budget,
                     _effective_budget, &edges_admitted, &truncated,
                     &frontier_cap_hit);
  pass_wall_ticks = TSC::ticks() - call_start_ticks;
  err = JVMTI_ERROR_NONE;

  store(_passes_run, load(_passes_run) + 1);
  _last_pass_gc_finish_epoch = gcFinishEpoch();
  store(_last_pass_ns, OS::nanotime());
  if (!run_root_enum) {
    // A pass that ran root/stack-ref enumeration spends _first_pass_budget,
    // not _effective_budget - its duration is not a signal about the
    // per-pass cost updatePacing() is trying to regulate (expandFrontier()'s
    // cheap, per-node expansion calls), so feeding it in here would
    // throttle _effective_budget down for every one of those unrelated
    // later passes based on a single, deliberately oversized outlier.
    updatePacing(pass_wall_ticks);
  } else {
    // Excluded from the budget/cadence controller above, but not from the
    // borrow ceiling's revocation check (see maybeRevokeBorrowForRootEnumPass()'s
    // own comment) - a root-enum pass's wall-clock cost is real pause time
    // and must still be able to revoke a borrowed-budget grant the pacing
    // controller would otherwise keep believing is safe.
    maybeRevokeBorrowForRootEnumPass(pass_wall_ticks);
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
  // Write the abandon reason (and every other detail field
  // buildAbandonedEvent() reads: _passes_run/_last_pass_ns/_search_start_ns
  // above, _frontier's size, ...) BEFORE the _search_state transition below,
  // and publish that transition with a release store - dump()'s reader side
  // (buildAbandonedEvent()/searchState()) pairs it with an acquire load, so
  // observing the new _search_state also guarantees every detail field
  // written before this release store is visible too, even on a weakly
  // ordered CPU (e.g. arm64) where relaxed stores to two different atomics
  // carry no such guarantee.
  bool has_pending_frontier = truncated;
  if (frontier_cap_hit) {
    store(_abandon_reason, (u8)SearchAbandonReason::FRONTIER_CAP);
    storeRelease(_search_state, (u8)SearchState::ABANDONED);
  } else if (!has_pending_frontier) {
    storeRelease(_search_state, (u8)SearchState::COMPLETED);
  } else if (_ttl_ms > 0 &&
             _last_pass_ns - _search_start_ns >= (u64)_ttl_ms * 1000000ULL) {
    store(_abandon_reason, (u8)SearchAbandonReason::TTL);
    storeRelease(_search_state, (u8)SearchState::ABANDONED);
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

  // Budget-borrowing (referenceChains.h's _borrowed_budget comment): only a
  // sustained run of comfortably-under-target passes earns extra headroom
  // above _budget, and any pass that is not comfortably under target revokes
  // it immediately - _budget itself must stay the ceiling the instant this
  // search stops proving it has pause-time room to spare.
  bool comfortably_under_target =
      _pause_target_ms > 0 &&
      (double)pass_ms <= (double)_pause_target_ms * BORROW_UNDER_TARGET_FRACTION;
  if (comfortably_under_target) {
    if (_consecutive_under_target_passes < BORROW_WARMUP_PASSES) {
      _consecutive_under_target_passes++;
    }
    if (_consecutive_under_target_passes >= BORROW_WARMUP_PASSES) {
      int64_t max_borrow = (int64_t)_budget * (BORROW_CEILING_MULTIPLIER - 1);
      int64_t grown = _borrowed_budget +
                      (int64_t)std::llround((double)_budget * BORROW_GROWTH_FRACTION);
      _borrowed_budget = std::min(grown, max_borrow);
    }
  } else {
    _consecutive_under_target_passes = 0;
    _borrowed_budget = 0;
  }

  int64_t ceiling = (int64_t)_budget + _borrowed_budget;
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

// A root/stack-ref enumeration pass never reaches updatePacing() above (see
// runPass()'s own comment on why its wall-clock cost is excluded from the
// per-pass PID/effective-budget signal), but it still spends real
// pause-time-SLO time. _borrowed_budget's own comment requires the grant be
// revoked the instant ANY pass is not comfortably under target, so this
// mirrors updatePacing()'s comfortably_under_target check for that one
// purpose only - it never grows _consecutive_under_target_passes/
// _borrowed_budget, since the warmup streak is calibrated against
// expandFrontier()'s per-node cost, not this call's unrelated fixed
// dispatch cost.
void ReferenceChainTracker::maybeRevokeBorrowForRootEnumPass(
    u64 pass_wall_ticks) {
  if (_pause_target_ms <= 0) {
    return;
  }
  u64 pass_ms = TSC::ticks_to_millis(pass_wall_ticks);
  bool comfortably_under_target =
      (double)pass_ms <= (double)_pause_target_ms * BORROW_UNDER_TARGET_FRACTION;
  if (!comfortably_under_target) {
    _consecutive_under_target_passes = 0;
    _borrowed_budget = 0;
    // The ceiling updatePacing() would compute right now collapses to
    // _budget alone (no _borrowed_budget term above) - re-clamp
    // _effective_budget immediately instead of leaving the borrow-inflated
    // value in place until the next ordinary pass's updatePacing() call.
    _effective_budget = std::min(_effective_budget, (int)_budget);
  }
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

  // Stamp every entry this poll refreshes with the current search
  // generation. _search_start_ns changes each time restartSearch() begins a
  // new search (runPass() sets it on the restarted search's first pass); a
  // cached chain whose source_search_ns predates the current one was
  // reconstructed from a FrontierTable the restart has since reset, so it is
  // refreshed below the moment the restarted search re-tags its sample -
  // trusting the stale source_tag would risk matching a tag the reset has
  // reassigned to an unrelated object.
  const u64 current_search_ns = load(_search_start_ns);

  // klass_ids resolved (and therefore already pruned-if-dead) by the
  // candidate loop below, so the prune pass afterwards skips re-resolving
  // them - it only needs to cover cached klasses that are no longer flagged.
  std::unordered_set<u32> handled;

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
    const u32 klass_id = candidates[i].klass_id;
    handled.insert(klass_id);
    jobject obj = LivenessTracker::instance()->resolveCandidateRepresentative(
        jni, klass_id);
    if (obj == nullptr) {
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate[%d] klass_id=%u "
               "representative could not be resolved (died/evicted)",
               i, klass_id);
      // The sample this klass's cached chain describes is gone - stop
      // re-emitting it (this poll's own prune contract).
      _resolved_chains_lock.lock();
      _resolved_chains.erase(klass_id);
      _resolved_chains_lock.unlock();
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

    // Reconstruct only when this klass has no current chain cached: either
    // nothing cached yet, or what is cached was built from a different tag or
    // an earlier search generation (see current_search_ns above). A klass
    // that keeps getting flagged, unchanged, across many polls is left alone
    // - its cached chain is already being re-emitted on every dump.
    bool need_refresh = false;
    if (tag > 0) {
      _resolved_chains_lock.lock();
      auto it = _resolved_chains.find(klass_id);
      need_refresh = (it == _resolved_chains.end() ||
                      it->second.source_tag != tag ||
                      it->second.source_search_ns != current_search_ns);
      _resolved_chains_lock.unlock();
    }
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate[%d] klass_id=%u tag=%lld "
             "needRefresh=%d",
             i, klass_id, (long long)tag, need_refresh);
    if (need_refresh) {
      ReferenceChainEvent event;
      bool built = buildChainEvent(tag, &event);
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets buildChainEvent(tag=%lld) -> %d",
               (long long)tag, built);
      if (built) {
        // Provisional stamp; drainPendingChainEvents() re-stamps each copy at
        // dump time so the event lands in that chunk's window.
        event._start_time = TSC::ticks();
        cacheResolvedChain(klass_id, std::move(event), tag, current_search_ns);
      }
    }
    // tag == 0: not yet discovered by any pass - retry on the next poll,
    // once a pass has had a chance to reach it (this method's own comment).

    jni->DeleteLocalRef(obj);
  }

  // Prune cached chains for samples that are gone but were not visited by the
  // candidate loop above (a klass that stopped being flagged but may still be
  // alive). Snapshot the keys under lock, resolve each without holding it
  // (resolveCandidateRepresentative() takes LivenessTracker's own lock and
  // calls JNI), then erase the ones whose representative no longer resolves.
  std::vector<u32> cached_keys;
  _resolved_chains_lock.lock();
  cached_keys.reserve(_resolved_chains.size());
  for (const auto &kv : _resolved_chains) {
    cached_keys.push_back(kv.first);
  }
  _resolved_chains_lock.unlock();

  std::vector<u32> dead_keys;
  for (u32 k : cached_keys) {
    if (handled.find(k) != handled.end()) {
      continue; // candidate loop already resolved (and pruned if dead) this one
    }
    jobject o = LivenessTracker::instance()->resolveCandidateRepresentative(jni, k);
    if (o == nullptr) {
      dead_keys.push_back(k);
    } else {
      jni->DeleteLocalRef(o);
    }
  }
  if (!dead_keys.empty()) {
    _resolved_chains_lock.lock();
    for (u32 k : dead_keys) {
      _resolved_chains.erase(k);
    }
    _resolved_chains_lock.unlock();
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets pruned=%d stale cached chains",
             (int)dead_keys.size());
  }
}

// Inserts or refreshes klass_id's resolved chain - see _resolved_chains'
// comment (referenceChains.h) for why a resolved chain is cached and
// re-emitted rather than emitted once. A refresh (klass_id already present)
// always succeeds; only a brand-new klass_id arriving with the cache already
// full is dropped (counted, not silent), rather than evicting some other
// still-live sample's chain. Split out of pollWatchedTargets() so
// ResolvedChainCacheTest (referenceChains_ut.cpp) can drive the overflow path
// directly, without standing up hundreds of real LivenessTracker candidates.
void ReferenceChainTracker::cacheResolvedChain(u32 klass_id,
                                               ReferenceChainEvent &&event,
                                               jlong source_tag,
                                               u64 source_search_ns) {
  _resolved_chains_lock.lock();
  auto it = _resolved_chains.find(klass_id);
  if (it == _resolved_chains.end() &&
      (int)_resolved_chains.size() >= MAX_RESOLVED_CHAINS) {
    _resolved_chains_lock.unlock();
    Counters::increment(REFERENCE_CHAIN_EVENTS_DROPPED);
    TEST_LOG("ReferenceChainTracker::cacheResolvedChain dropped new klass_id=%u, "
             "cache full (at MAX_RESOLVED_CHAINS=%d)",
             klass_id, MAX_RESOLVED_CHAINS);
    return;
  }
  CachedChain &slot = _resolved_chains[klass_id];
  slot.event = std::move(event);
  slot.source_tag = source_tag;
  slot.source_search_ns = source_search_ns;
  TEST_LOG("ReferenceChainTracker::cacheResolvedChain klass_id=%u source_tag=%lld "
           "cache_size=%d",
           klass_id, (long long)source_tag, (int)_resolved_chains.size());
  _resolved_chains_lock.unlock();
}

void ReferenceChainTracker::drainPendingChainEvents(
    std::vector<ReferenceChainEvent> *out) {
  if (out == nullptr) {
    return;
  }
  // Snapshot-and-keep, not a drain: every cached chain is copied out (and
  // re-stamped so it lands in the dumping chunk's window) while the cache
  // itself is left intact, so the same live sample's chain re-emits into
  // every chunk it survives into (see _resolved_chains' comment). `now` is
  // read once, before the lock, so every event in one dump shares a stamp.
  u64 now = TSC::ticks();
  _resolved_chains_lock.lock();
  for (const auto &kv : _resolved_chains) {
    out->push_back(kv.second.event);
    out->back()._start_time = now;
  }
  _resolved_chains_lock.unlock();
  TEST_LOG("ReferenceChainTracker::drainPendingChainEvents re-emitted=%d",
           (int)out->size());
}
