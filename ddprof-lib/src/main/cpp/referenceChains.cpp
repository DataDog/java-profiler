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
                            u32 depth, u8 state, u8 root_kind,
                            jlong class_tag) {
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
  _table[idx].class_tag = class_tag;
  _table[idx].leak_tag = 0;
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

bool FrontierTable::improveChain(jlong tag, jlong parent_tag,
                                  u32 referrer_klass, u32 depth,
                                  u8 root_kind) {
  // Replace a shallow root-attached entry (parent_tag == 0, depth == 0)
  // with a deeper chain-attached entry when the object is reached via a
  // longer path. This fixes the "depth=1 chain with no holder" problem:
  // an object first admitted as a JNI-local root (parent_tag == 0) gets
  // its frontier entry overwritten when the static-field → ... → object
  // path reaches it later with a non-zero parent_tag.
  // Returns true if the entry was actually improved (new depth > old).
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
    return false;
  }
  int idx = (int)(tag - 1);

  _table_lock.lock();
  bool improved = false;
  if (idx < _table_size && depth > _table[idx].depth) {
    _table[idx].parent_tag = parent_tag;
    _table[idx].referrer_klass = referrer_klass;
    _table[idx].depth = depth;
    _table[idx].root_kind = root_kind;
    improved = true;
  }
  _table_lock.unlock();
  return improved;
}

bool FrontierTable::reparentToDurableRoot(jlong tag, jlong new_parent_tag,
                                          u32 referrer_klass) {
  // See the declaration's own comment (referenceChains.h) for why this
  // exists as a sibling of improveChain(): equal-depth depth-1 noise->real
  // re-parenting. All lookups happen under one lock - three index reads,
  // no allocation, O(1).
  if (tag <= 0 || tag - 1 > (jlong)INT_MAX || new_parent_tag <= 0 ||
      new_parent_tag - 1 > (jlong)INT_MAX) {
    return false;
  }
  int idx = (int)(tag - 1);
  int new_par_idx = (int)(new_parent_tag - 1);

  _table_lock.lock();
  bool swapped = false;
  if (idx < _table_size && _table[idx].depth == 1 &&
      _table[idx].parent_tag > 0 && _table[idx].parent_tag != new_parent_tag) {
    int old_par_idx = (int)(_table[idx].parent_tag - 1);
    if (old_par_idx >= 0 && old_par_idx < _table_size &&
        new_par_idx < _table_size &&
        _table[new_par_idx].parent_tag == 0 &&
        _table[new_par_idx].root_kind != 0 &&
        !isTransientRootKind(_table[new_par_idx].root_kind) &&
        _table[old_par_idx].parent_tag == 0 &&
        isTransientRootKind(_table[old_par_idx].root_kind)) {
      // New parent is a root-attached DURABLE root (static field, JNI
      // global, thread) and the current parent is a root-attached TRANSIENT
      // one - same depth, strictly better retention explanation.
      _table[idx].parent_tag = new_parent_tag;
      _table[idx].referrer_klass = referrer_klass;
      swapped = true;
    }
  }
  _table_lock.unlock();
  return swapped;
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
  // immediately hit the cap. Use a floating-point ratio - integer
  // division here would truncate the scale factor (e.g. a budget
  // of 3741 against a default of 1000 would floor to a 3x
  // multiplier instead of ~3.74x, undershooting the cap by ~20%).
  if (!(tuned & REF_CHAINS_TUNED_FRONTIER_CAP)) {
    int scaled_cap = (int)(DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP *
        ((double)args._reference_chains_budget / DEFAULT_REFERENCE_CHAINS_BUDGET));
    args._reference_chains_frontier_cap = std::max(
        DEFAULT_REFERENCE_CHAINS_FRONTIER_CAP,
        std::min(scaled_cap, MAX_REFERENCE_CHAINS_FRONTIER_CAP));
  }

  // --- Pause target ---
  // More available processors = the JVM can afford a slightly
  // longer per-pass safepoint without impacting application
  // throughput. Scale linearly: 1 core = 50ms, 4 cores = 100ms,
  // 8 cores = 150ms, capped at 50ms (the per-call STW cap from the
  // safepoint budget model).
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
  _effective_pause_target_ms = _pause_target_ms;
  _effective_budget = _budget;
  _effective_cadence_ns = PASS_CADENCE_NS;
  _candidate_count = 0;
  _candidate_found_bits = 0;
  memset(_candidate_discovered_count, 0, sizeof(_candidate_discovered_count));
  _passes_since_last_candidate_progress = 0;
  _last_candidate_progress_mark = 0;
  _canary_stuck_restart_count = 0;
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

  // Search restart (this class's own header comment): (re)seed _safepoint_pain_budget
  // from the configured refill rate, mirroring _pause_pid's own
  // reconstruct-in-start() pattern above. A search's already-accumulated
  // _search_pain_ms is deliberately left untouched here - only restartSearch()
  // spends it, so a start()/stop() cycle mid-search (if that ever happens)
  // does not erase cost the current search has already incurred.
  _safepoint_pain_budget = PainBudget(
      std::max(args._reference_chains_pain_budget_percent, 0) / 100.0);
  _pain_budget_refill_rate = std::max(args._reference_chains_pain_budget_percent, 0) / 100.0;
  // Same refill rate as _safepoint_pain_budget above - one operator-facing
  // "how much background cost is acceptable" percentage covers both
  // leaky buckets (see _cpu_pain_budget's own comment, referenceChains.h).
  _cpu_pain_budget = PainBudget(_pain_budget_refill_rate);

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
      // No cached-class cleanup needed before detaching:
      // _cached_object_class is a global ref, deliberately valid across
      // attach/detach cycles (see its own comment in referenceChains.h) -
      // unlike the per-attach local ref it replaced, which this destructor
      // used to have to clear here.
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
    // Urgency-driven dynamic tuning: as secondsToOOM() falls within
    // OOM_RAMP_START_S of projected exhaustion, ramp the per-pass pause
    // target and cadence exponentially toward their ceilings (see
    // OOM_RAMP_START_S/URGENT_PAUSE_TARGET_MS/URGENT_CADENCE_NS's own
    // comments) - slow at the 30-minute mark, aggressive right before OOM.
    // secondsToOOM() itself already gates on a confirmed rising trend (its
    // NOT_RISING check), so a non-negative value here is real growth, not
    // noise. The PID controller is reconstructed whenever the (rounded)
    // target changes so its ceiling tracks the new value.
    double seconds_to_oom = LivenessTracker::instance()->secondsToOOM();
    bool urgent = seconds_to_oom >= 0 && seconds_to_oom < OOM_RAMP_START_S;
    long target_ms = _pause_target_ms;
    u64 cadence_ns = _effective_cadence_ns;
    if (urgent) {
      double x = 1.0 - seconds_to_oom / OOM_RAMP_START_S; // 0 at 30min out, 1 at OOM
      target_ms = std::lround(_pause_target_ms *
          std::pow((double)URGENT_PAUSE_TARGET_MS / std::max(_pause_target_ms, 1L), x));
      // Ramp from the fixed configured cadence, not the currently-adaptive
      // _effective_cadence_ns - using the live value as the ramp's own
      // moving anchor would compound the exponent across iterations instead
      // of tracking urgency directly from a stable baseline.
      cadence_ns = (u64)std::llround((double)PASS_CADENCE_NS *
          std::pow((double)URGENT_CADENCE_NS / (double)PASS_CADENCE_NS, x));
      // While urgent, the ramp owns _effective_cadence_ns outright so
      // shouldRunPass()'s cadence gate and the per-pass log actually
      // reflect it. updatePacing()'s own overflow-driven widen/narrow
      // adjustment (see _effective_cadence_ns's header comment) resumes
      // sole ownership the instant urgency clears - this block simply stops
      // touching the field then, so there is nothing to snap back from.
      _effective_cadence_ns = cadence_ns;
    }
    if (target_ms != _effective_pause_target_ms) {
      _effective_pause_target_ms = target_ms;
      _pause_pid = PidController((u64)std::max(_effective_pause_target_ms, 0L),
                                  10, 1, 2, 1, 5.0);
      // Once in the ramp window, hold the budget ceiling raised for its
      // entire duration rather than only right before OOM: the process is
      // likely to die anyway, so it's worth spending whatever budget it
      // takes to collect good diagnostic data for as long as we have.
      if (urgent) {
        _budget = std::min(_budget * 4, MAX_REFERENCE_CHAINS_BUDGET);
      }
      TEST_LOG("ReferenceChainTracker::threadLoop urgency=%d pauseTarget=%ldms "
               "cadence=%lluns budget=%d",
               (int)urgent, _effective_pause_target_ms,
               (unsigned long long)cadence_ns, _budget);
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
    // Only sleep when idle (no pass will run). When a canary
    // search is active or a pass is about to run, skip the
    // sleep to run passes back-to-back.
    if (!should_run && cadence_ns > 0) {
      OS::sleep(cadence_ns);
      if (!_running.load(std::memory_order_acquire)) {
        break;
      }
      now_ns = OS::nanotime();
    }
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
      runPassSerialized(jvmti, jni);
    }
    // Target-selection bridging step: poll once per scheduling cycle, after
    // runPass() - so this poll always sees the most recent pass's tagging (see
    // pollWatchedTargets()'s own comment). Unconditional, not gated on
    // shouldRunPass()'s decision above: a candidate discovered by an
    // earlier pass may still be waiting for its first poll even on a cycle
    // where this cycle's own pass was skipped.
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
    bool afford = canAffordNewSearch(now_ns);
    TEST_LOG("ReferenceChainTracker::shouldRunPass search_not_started "
             "canAffordNewSearch=%d", (int)afford);
    if (!afford) {
      return false;
    }
    // This episode's one urgency-authorized search (_urgent_search_spent's
    // own comment, referenceChains.h) is the one about to start.
    _urgent_search_spent = _urgent_latched;
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
      // Same entitlement bookkeeping as the first-search branch above.
      _urgent_search_spent = _urgent_latched;
      restartSearch();
      TEST_LOG("ReferenceChainTracker::shouldRunPass -> true (restarting search)");
      return true;
    }
    // No log here: a terminal search waiting for a restart to become
    // warranted is the common idle state, re-evaluated every second, so
    // logging it is pure per-second noise (see threadLoop()).
    TEST_LOG("ReferenceChainTracker::shouldRunPass terminal_blocked "
             "tags_released=%d safepoint_pain=%d search_state=%d",
             (int)_tags_released,
             (int)_safepoint_pain_budget.canStartNow(now_ns),
             (int)_search_state);
    return false;
  }
  // Canary search active with candidates still to find - computed ahead of
  // the pain-budget check below (CANARY_PAIN_BUDGET_REFILL_MULTIPLIER's own
  // comment) so the escalation and the bypass branch further down agree on
  // the same snapshot of _candidate_found_bits.
  bool canary_active = _candidate_count > 0 &&
      __builtin_popcountll(_candidate_found_bits) < (u64)_candidate_count;
  // Adaptive CPU budget: 100x for emergency (canary stuck, no progress),
  // 15x for uncovered but making progress, 1x when all leak tags resolved.
  bool all_covered = _leak_tags_assigned > 0 &&
      _leak_tags_resolved >= _leak_tags_assigned;
  // Emergency = the canary's CANDIDATES are stuck, not the frontier: the
  // frontier grows on virtually every pass for as long as any unvisited
  // object exists, so frontier progress would make emergency unreachable
  // (observed live: emergency=0 for the entire run while 0/1 candidates were
  // found). _passes_since_last_candidate_progress counts passes without any
  // candidate discovery/refresh - the same signal CANARY_STUCK abandons on.
  bool emergency = canary_active &&
      _passes_since_last_candidate_progress >= CANARY_NO_PROGRESS_PASS_LIMIT;
  double multiplier;
  if (all_covered) {
    multiplier = 1.0;
  } else if (emergency) {
    multiplier = CANARY_PAIN_BUDGET_REFILL_MULTIPLIER;
  } else if (canary_active) {
    multiplier = CANARY_PAIN_BUDGET_COVERING_MULTIPLIER;
  } else {
    multiplier = 1.0;
  }
  _cpu_pain_budget.setRefillRate(
      std::min(_pain_budget_refill_rate * multiplier, 1.0),
      now_ns);
  if (!_cpu_pain_budget.canStartNow(now_ns)) {
    TEST_LOG("ReferenceChainTracker::shouldRunPass blocked by cpu_pain_budget "
             "balance=%.1fms refill_rate=%.4f canary_active=%d all_covered=%d "
             "emergency=%d multiplier=%.1f",
             _cpu_pain_budget.balanceMs(now_ns),
             std::min(_pain_budget_refill_rate * multiplier, 1.0),
             (int)canary_active, (int)all_covered, (int)emergency, multiplier);
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
  // With canary search (candidates pre-tagged), run passes back-to-back
  // until all candidates are found -- the PID controller self-regulates
  // the per-pass STW pause, and the total budget is tiny in practice
  // (<20ms per 60s recording). Only gate on cadence when there
  // are no canary candidates to chase (whole-graph BFS mode).
  if (canary_active) {
    // Canary search active with candidates still to find --
    // run the next pass immediately.
    TEST_LOG("ReferenceChainTracker::shouldRunPass -> true (canary search, "
             "%d/%d candidates found)",
             (int)__builtin_popcountll(_candidate_found_bits),
             (int)_candidate_count);
    return true;
  }
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
// Latching, hysteretic read of LivenessTracker::secondsToOOM() - see
// _urgent_latched's own comment (referenceChains.h) for why a bare threshold
// comparison here flaps, and OOM_URGENT_RELEASE_S for the release bar.
bool ReferenceChainTracker::isUrgent() const {
  double seconds_to_oom = LivenessTracker::instance()->secondsToOOM();
  if (seconds_to_oom >= 0 && seconds_to_oom < OOM_URGENT_THRESHOLD_S) {
    _urgent_release_ticks = 0;
    if (!_urgent_latched) {
      _urgent_latched = true;
      // A fresh episode gets a fresh entitlement to one search.
      _urgent_search_spent = false;
      TEST_LOG("ReferenceChainTracker::isUrgent latching urgency "
               "(secondsToOOM=%.1f < OOM_URGENT_THRESHOLD_S=%.1f)",
               seconds_to_oom, OOM_URGENT_THRESHOLD_S);
    }
    return true;
  }
  if (_urgent_latched) {
    // Negative means "no rising trend to project from" (secondsToOOM()'s own
    // unknown/NOT_RISING encoding), which counts toward release just like a
    // comfortably distant projection does.
    if (seconds_to_oom < 0 || seconds_to_oom >= OOM_URGENT_RELEASE_S) {
      if (++_urgent_release_ticks >= URGENT_RELEASE_CONSECUTIVE) {
        _urgent_latched = false;
        _urgent_release_ticks = 0;
        _urgent_search_spent = false;
        TEST_LOG("ReferenceChainTracker::isUrgent releasing urgency "
                 "(secondsToOOM=%.1f clear of OOM_URGENT_RELEASE_S=%.1f for "
                 "%d consecutive observations)",
                 seconds_to_oom, OOM_URGENT_RELEASE_S,
                 URGENT_RELEASE_CONSECUTIVE);
        return false;
      }
    } else {
      // Between the two bars, or a single noisy reading past the release bar
      // followed by one that is not - neither releases the latch.
      _urgent_release_ticks = 0;
    }
    return true;
  }
  return false;
}

bool ReferenceChainTracker::hasLeakSignal() {
  if (!LivenessTracker::instance()->gcGenerationsEnabled()) {
    // No population-trend signal to gate on at all - see this method's own
    // header comment for why that means "always true" here.
    return true;
  }
  double seconds_to_oom = LivenessTracker::instance()->secondsToOOM();
  // isUrgent() is called unconditionally, not short-circuited behind
  // _urgent_search_spent: it is what maintains the latch/release counter, so
  // skipping it would freeze the episode state (see _urgent_latched).
  bool urgent = isUrgent();
  if (urgent && !_urgent_search_spent) {
    // Heap-wide floor is rising fast enough that OOM is imminent - don't
    // wait for a specific klass to clear selectLeakCandidates()'s own
    // per-klass ring-fill/hysteresis gate; see OOM_URGENT_THRESHOLD_S's own
    // comment (referenceChains.h) for why that gate alone is too slow here.
    // canAffordNewSearch() can still defer this via the pain-budget check it
    // runs before calling this method (this method's own header comment).
    //
    // Only until this episode's one search has been started
    // (_urgent_search_spent): past that point the per-klass probe below is
    // the sole remaining trigger, so a completed urgent search is not torn
    // down and restarted from scratch on the very next tick.
    TEST_LOG("ReferenceChainTracker::hasLeakSignal -> true (urgent, "
             "secondsToOOM=%.1f)",
             seconds_to_oom);
    return true;
  }
  KlassCandidate probe[1];
  int n = LivenessTracker::instance()->selectLeakCandidates(probe, 1);
  TEST_LOG("ReferenceChainTracker::hasLeakSignal -> %s (secondsToOOM=%.1f, "
           "candidates=%d, urgent=%d, urgentSearchSpent=%d)",
           n > 0 ? "true" : "false", seconds_to_oom, n, urgent,
           _urgent_search_spent);
  return n > 0;
}

bool ReferenceChainTracker::canAffordNewSearch(u64 now_ns) {
  if (!_safepoint_pain_budget.canStartNow(now_ns)) {
    TEST_LOG("ReferenceChainTracker::canAffordNewSearch blocked by "
             "safepoint_pain_budget balance=%.1fms refill_rate=%.4f",
             _safepoint_pain_budget.balanceMs(now_ns),
             _pain_budget_refill_rate);
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
  _safepoint_pain_budget.spend(_search_pain_ms);
  _search_pain_ms = 0;

  if (_frontier != nullptr) {
    _frontier->resetForRestart();
  }
  _next_tag = 1;
  // The shared class-tag counter (classTagAllocator.h)/_class_tags
  // intentionally untouched - see this method's own declaration comment
  // (referenceChains.h).

  _search_started = false;
  store(_search_state, (u8)SearchState::RUNNING);
  store(_abandon_reason, (u8)SearchAbandonReason::NONE);
  store(_search_start_ns, (u64)0);
  _pending_expand.clear();
  _priority_expand.clear();
  // Both keyed by frontier tags this restart is about to invalidate (fresh
  // tags start again from 1) - a stale entry surviving past a restart would
  // be compared against whatever unrelated object the new search has since
  // reassigned that tag to. _watched_leak_klass_ids itself is left alone:
  // it reflects LivenessTracker's own growth signal, unrelated to this
  // search's lifecycle, and simply gets refreshed again on the next
  // pollWatchedTargets() tick regardless.
  _leak_signature_totals.clear();
  _leak_signature_prev_totals.clear();
  _leak_parent_fanout.clear();
  _leak_tags_assigned = 0;
  _leak_tags_resolved = 0;
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

  _safepoint_pain_budget.spend(_search_pain_ms);
  _search_pain_ms = 0;
  // Reset the pain budget entirely so a fresh test starts from zero debt,
  // independent of how much wall-clock time has elapsed since the last
  // test's spend(). Without this, a fast CI runner (musl, small heap,
  // no GC pauses) may not have drained enough debt between tests.
  _safepoint_pain_budget = PainBudget(_pain_budget_refill_rate);
  // Mirror the reset for the non-safepoint budget - same test-isolation
  // rationale as _safepoint_pain_budget above.
  _cpu_pain_budget = PainBudget(_pain_budget_refill_rate);
  // Same test-isolation rationale: a latched urgency episode left behind by
  // an earlier test would otherwise deny this one its own
  // urgency-authorized search (see _urgent_search_spent).
  _urgent_latched = false;
  _urgent_release_ticks = 0;
  _urgent_search_spent = false;

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
  _canary_stuck_restart_count = 0;
  // Same "just-constructed values" contract resetForRestart() already
  // documents for these two fields - without it, a prior test's fully-swept
  // (or partially-swept) state survives in this process-wide singleton
  // (ReferenceChainTracker::instance()) and can wrongly skip
  // admitStaticFieldRoots() entirely on this test's first pass if its
  // resolved class count happens to match whatever an earlier test last
  // left behind (found via a real gtest-suite-order failure, not
  // hypothetical).
  _last_resolved_class_count = 0;
  _last_static_field_class_count = -1;
  _static_field_sweep_cursor = 0;
  _static_field_sweep_cycle_truncated = false;
  _candidate_count = 0;
  _candidate_found_bits = 0;
  memset(_candidate_discovered_count, 0, sizeof(_candidate_discovered_count));
  // _candidate_parent_tags/_candidate_referrer_klasses/_candidate_depths
  // will be filled at pruning time.
  // across a production restart, a test reset starts from a blank cache so
  // one test's resolved chains cannot leak into the next.
  _resolved_chains_lock.lock();
  _resolved_chains.clear();
  _resolved_chains_lock.unlock();
  _pending_abandoned_events_lock.lock();
  _pending_abandoned_events.clear();
  _pending_abandoned_events_lock.unlock();

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
  // Resolves the klass_id via the same GetClassSignature +
  // normalizeClassSignature + Profiler::lookupClass sequence every
  // consumer in this subsystem uses (ObjectSampler::recordAllocation(),
  // LivenessTracker::resolveKlassId(), resolveClassMap() above) - the
  // id space is load-bearing here: pollWatchedTargets() matches frontier
  // entries against leak candidates by klass_id, and the candidate ids
  // come from that signature-notation space (Class.getName()'s dot form
  // is a DIFFERENT StringDictionary key - see
  // find-klass-id-notation-mismatch). Test-only, off-hot-path.
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
    TEST_LOG("ReferenceChainTracker::resolveLoadedClasses class_map generation "
             "changed: old=%llu new=%llu - clearing _class_tags and "
             "candidate klass_ids may be stale",
             (unsigned long long)_last_class_map_generation,
             (unsigned long long)current_generation);
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
              TEST_LOG("ReferenceChainTracker::resolveClassMap id=%d name=%.*s",
                       id, (int)name_len, name_slice);
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

  // Rolling resume cursor for expandFrontier(): tracks the tag of the last
  // batch entry that FollowReferences visited (the callback at the
  // batch_tags descent-gate updates this). After FollowReferences returns
  // truncated, expandFrontier() uses this to pop fully-processed entries
  // from the source queue (mark EXPANDED) and leave only the
  // partially-processed and unvisited entries for the next pass — same
  // resumable-cursor pattern as admitStaticFieldRoots()'s sweep cursor.
  // Without this, a truncated batch is retried in its entirety next pass:
  // GetObjectsWithTags + FollowReferences re-walks already-expanded
  // entries (their children are ALREADY_ADMITTED, so idempotent but
  // wasteful — re-paying the full O(tag_map × batch) GOTW cost and the
  // FollowReferences STW for entries that need no work). 0 = no batch
  // entry visited yet this FollowReferences call.
  jlong _last_visited_batch_tag = 0;

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

  // PER-CLASS NON-STATIC QUOTA (admitStaticFieldRoots() only). JVMTI
  // reports a class's entire metadata graph through the same
  // static_field_seed opening - CONSTANT_POOL (resolved String/Class/
  // MethodHandle/MethodType/CallSite constants), INTERFACE, SUPERCLASS,
  // CLASS_LOADER, ... - not just its STATIC_FIELD edges. CONSTANT_POOL
  // alone is 5-15x STATIC_FIELD volume per class, systemically. Admitting
  // all of them would burn the per-chunk callback/deadline budget on
  // non-static-field edges and starve static-field discovery; dropping
  // them entirely would exclude a real (if rarer) leak category. Instead,
  // STATIC_FIELD edges are always admitted and non-STATIC_FIELD edges from
  // a class are admitted up to _class_other_cap per class, then dropped
  // for the rest of that class this lap. The cap resets on class
  // boundary (detected by referrer tag change), so one fat class cannot
  // exhaust the quota for any other. admitStaticFieldRoots() sets
  // _class_other_cap from STATIC_FIELD_SWEEP_NON_STATIC_CAP_PER_CLASS;
  // everywhere else these are zero/unused.
  jlong _seed_class_tag = 0;     // negative tag of the class currently
                                // being descended (0 before the first
                                // class edge is seen)
  int _class_other_admitted = 0; // non-STATIC_FIELD edges admitted for
                                // the current class this lap
  int _class_other_cap = 0;      // per-class cap; 0 disables the quota
                                // (admit all) when not in seed sweep
  // Number of distinct classes entered so far in this chunk's descent
  // (incremented on each class-boundary tag change). Used by
  // admitStaticFieldRoots() to compute the resumable cursor on truncation:
  // resume at chunk_start + count - 1 (redo the partial class) rather
  // than skipping to chunk_end and losing the rest of the chunk.
  int _classes_in_chunk_visited = 0;

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

  // TEMP DIAGNOSTIC (see doc/temp/ investigation notes): per-jvmtiHeapReference
  // Kind callback tally for admitStaticFieldRoots()'s current chunk, to find
  // which reference kind actually drives per-chunk callback volume (e.g.
  // static fields vs. constant-pool entries vs. interfaces). Null everywhere
  // else - only admitStaticFieldRoots() sets this to a non-null, zeroed,
  // stack-local array sized for the full jvmtiHeapReferenceKind range.
  int *kind_counts = nullptr;
};
} // namespace

jint JNICALL ReferenceChainTracker::heapReferenceCallback(
    jvmtiHeapReferenceKind reference_kind,
    const jvmtiHeapReferenceInfo *reference_info, jlong class_tag,
    jlong referrer_class_tag, jlong size, jlong *tag_ptr,
    jlong *referrer_tag_ptr, jint length, void *user_data) {
  PassContext *ctx = (PassContext *)user_data;

  // TEMP DIAGNOSTIC (see doc/temp/ investigation notes): tally every callback
  // by kind before any early-return below, so an aborted/truncated chunk
  // still reports what it actually saw. kind_counts is only non-null for
  // admitStaticFieldRoots()'s call - zero overhead elsewhere.
  if (ctx->kind_counts != nullptr && (int)reference_kind >= 0 &&
      (int)reference_kind < 32) {
    ctx->kind_counts[(int)reference_kind]++;
  }

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

  // Canary pruning: if this object is the pre-tagged representative of a
  // leaked candidate (marker tag MARKER_TAG_BASE - i, negative), record its
  // chain link but do NOT enqueue its children (treat as a leaf). Do not
  // return JVMTI_VISIT_ABORT -- that aborts the entire FollowReferences walk
  // (JVMTI spec). Just skip admitObject() for this object.
  //
  // MUST run before the *tag_ptr < 0 class-tag check below, since marker
  // tags are negative and would be caught by that check first (returning 0
  // without recording the chain link).
  //
  // Matches by object identity (the marker tag SetTag() put on this exact
  // representative object in pollWatchedTargets()), not by class: matching
  // by class alone would record a chain for whichever instance of that class
  // the walk happens to visit first, which for a common class (e.g. byte[])
  // is almost certainly an unrelated, possibly short-lived object - not the
  // specific instance LivenessTracker flagged as growing.
  if (ctx->tracker->_candidate_count > 0 &&
      *tag_ptr <= ReferenceChainTracker::MARKER_TAG_BASE) {
    int candidate_idx = (int)(ReferenceChainTracker::MARKER_TAG_BASE - *tag_ptr);
    if (candidate_idx >= 0 && candidate_idx < ctx->tracker->_candidate_count) {
      jlong rtag = (referrer_tag_ptr != nullptr) ? *referrer_tag_ptr : 0;
      u32 candidate_klass = ctx->tracker->classTags()->resolve(class_tag);
      if (rtag > 0) {
        FrontierEntry parent{};
        if (ctx->frontier->lookup(rtag, &parent)) {
          // Use the marker tag itself as the frontier table key - it is
          // already a unique per-candidate value, so no nextTag() is needed.
          jlong frontier_tag = *tag_ptr;
          ctx->frontier->insert(frontier_tag, rtag,
                                  parent.referrer_klass,
                                  parent.depth + 1,
                                  FrontierEntryState::FRONTIER,
                                  parent.root_kind);
          ctx->tracker->_candidate_parent_tags[candidate_idx] = rtag;
          ctx->tracker->_candidate_frontier_tags[candidate_idx] = frontier_tag;
          ctx->tracker->_candidate_referrer_klasses[candidate_idx] = candidate_klass;
          ctx->tracker->_candidate_depths[candidate_idx] = parent.depth + 1;
          ctx->tracker->_candidate_found_bits |= (1ULL << candidate_idx);
          TEST_LOG("ReferenceChainTracker::heapReferenceCallback canary "
                 "pruned candidate %d (klass_id=%u frontier_tag=%lld)",
                 candidate_idx, candidate_klass, (long long)frontier_tag);
        }
      } else {
        // Root-referenced candidate.
        jlong frontier_tag = *tag_ptr;
        ctx->frontier->insert(frontier_tag, 0,
                                candidate_klass, 1,
                                FrontierEntryState::FRONTIER,
                                (u8)reference_kind);
        ctx->tracker->_candidate_parent_tags[candidate_idx] = 0;
        ctx->tracker->_candidate_frontier_tags[candidate_idx] = frontier_tag;
        ctx->tracker->_candidate_referrer_klasses[candidate_idx] = candidate_klass;
        ctx->tracker->_candidate_depths[candidate_idx] = 1;
        ctx->tracker->_candidate_found_bits |= (1ULL << candidate_idx);
        TEST_LOG("ReferenceChainTracker::heapReferenceCallback canary "
                 "pruned root-referenced candidate %d (klass_id=%u)",
                 candidate_idx, candidate_klass);
      }
      // Do NOT enqueue children for this object.
      return 0;
    }
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

  if (ctx->static_field_seed && referrer_tag_ptr != nullptr &&
      *referrer_tag_ptr < 0) {
    // Referrer is the class object opened by the static_field_seed branch
    // above. JVMTI reports that class's entire metadata reference graph
    // through this same opening, not just its static fields - CONSTANT_POOL
    // (resolved String/Class/MethodHandle/MethodType/CallSite constants),
    // INTERFACE, SUPERCLASS, CLASS_LOADER, ... Those are real reachability
    // edges, just lower-priority for this static-field-root sweep than
    // STATIC_FIELD. Admit STATIC_FIELD unconditionally; admit non-STATIC_FIELD
    // up to the per-class cap (PassContext::_class_other_cap) so one fat
    // class cannot starve the rest, then drop further non-static edges for
    // this class this lap. Track the current class tag for
    // admitStaticFieldRoots()'s resumable cursor (see that method's own
    // comment) and reset the cap counter on class boundary.
    if (*referrer_tag_ptr != ctx->_seed_class_tag) {
      ctx->_seed_class_tag = *referrer_tag_ptr;
      ctx->_class_other_admitted = 0;
      ctx->_classes_in_chunk_visited++;
    }
    if (reference_kind != JVMTI_HEAP_REFERENCE_STATIC_FIELD) {
      if (ctx->_class_other_cap > 0 &&
          ctx->_class_other_admitted >= ctx->_class_other_cap) {
        // Quota exhausted for this class - drop the edge. Count every
        // drop, and count the first drop for this class separately so
        // the two counters together distinguish "a few fat outlier
        // classes dropping many edges" from "systematic drops across
        // almost all classes" (cap too low).
        Counters::increment(REFERENCE_CHAIN_STATIC_SWEEP_NON_STATIC_DROPPED);
        if (ctx->_class_other_admitted == ctx->_class_other_cap) {
          Counters::increment(REFERENCE_CHAIN_STATIC_SWEEP_CLASSES_CAPPED);
        }
        return 0;
      }
      ctx->_class_other_admitted++;
    }
  }

  // Leak tag: this object was directly tagged by LivenessTracker's
  // tagLeakInstances() because it's a tracked leaking object. Convert
  // the leak tag to a frontier tag so the BFS can build its chain, and
  // store the leak tag in the frontier entry for correlation with
  // HeapLiveObject events.
  if (isLeakTag(*tag_ptr)) {
    jlong leak_tag = *tag_ptr;
    // Allocate a frontier tag for this object
    jlong frontier_tag = ctx->tracker->nextTag();
    u32 referrer_klass = ctx->tracker->classTags()->resolve(class_tag);
    u8 root_kind = parent_tag == 0 ? (u8)reference_kind : 0;
    if (ctx->frontier->insert(frontier_tag, parent_tag, referrer_klass,
                               depth, FrontierEntryState::FRONTIER,
                               root_kind, class_tag)) {
      // Store the leak tag in the frontier entry
      ctx->frontier->setLeakTag(frontier_tag, leak_tag);
      *tag_ptr = frontier_tag;
      ctx->edges_admitted++;
      TEST_LOG("ReferenceChainTracker::heapReferenceCallback leak-tag "
               "intercepted: leak_tag=%lld -> frontier_tag=%lld depth=%u "
               "parent_tag=%lld",
               (long long)leak_tag, (long long)frontier_tag, depth,
               (long long)parent_tag);
      ctx->tracker->trackLeakAccumulation(ctx->frontier, class_tag,
                                             parent_tag, frontier_tag);
      // Auto-mark: record this as a discovered instance, with eviction
      // rights over uncorrelated noise slots (see recordDiscoveredInstance).
      if (ctx->tracker->_candidate_count > 0) {
        u32 klass_id = ctx->tracker->classTags()->resolve(class_tag);
        ctx->tracker->recordDiscoveredInstance(klass_id, frontier_tag, true);
      }
    } else {
      // Frontier cap hit
      ctx->truncated = true;
      ctx->frontier_cap_hit = true;
      return JVMTI_VISIT_ABORT;
    }
    return JVMTI_VISIT_OBJECTS;
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
        tag_ptr, parent_tag, referrer_klass, depth, root_kind, class_tag,
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
      // Distinct from ordinary budget exhaustion above - runPass() keeps
      // the search RUNNING on this, deferring to the no-progress detector
      // to abandon only if the frontier then stops growing (see runPass()'s
      // frontier_cap_hit handling).
      ctx->truncated = true;
      ctx->frontier_cap_hit = true;
      return JVMTI_VISIT_ABORT;
    default:
      // ADMITTED, or HOP_CAP/ALREADY_ADMITTED (neither reachable here: the
      // hop-cap check above already returned before this branch, and
      // *tag_ptr == 0 rules out ALREADY_ADMITTED) - nothing further to do.
      break;
    }
    // Already-tagged object reached via a new edge. If this new path
    // is deeper (non-zero parent_tag), improve the chain — replace the
    // shallow root-attached entry with the deeper chain-attached entry.
    // This fixes the "depth=1 chain with no holder" problem: an object
    // first admitted as a JNI-local root (parent_tag == 0) gets its
    // frontier entry improved when the static-field → ... → object path
    // reaches it. Only runs when *tag_ptr != 0 (already admitted);
    // the *tag_ptr == 0 path above handles first admission.
    if (*tag_ptr != 0 && parent_tag != 0 && *tag_ptr > 0) {
      u32 referrer_klass = ctx->tracker->classTags()->resolve(class_tag);
      if (ctx->frontier->improveChain(*tag_ptr, parent_tag, referrer_klass,
                                       depth, 0)) {
        // Chain was improved — invalidate any cached chain for this tag
        // so pollWatchedTargets rebuilds it with the deeper path.
        ctx->tracker->invalidateResolvedChain(*tag_ptr);
      } else if (ctx->frontier->reparentToDurableRoot(*tag_ptr, parent_tag,
                                                    referrer_klass)) {
        // Equal-depth re-parent from a transient root to a durable one
        // (improveChain() cannot express it - see its declaration) - same
        // cache invalidation so the rebuilt chain uses the durable root.
        ctx->tracker->invalidateResolvedChain(*tag_ptr);
      }
    }
    if (*tag_ptr != 0 && parent_tag == 0 && *tag_ptr > 0) {
      // Already-admitted entry reached via a NEW root-like edge
      // (parent_tag == 0): the static-field sweep's class -> field edge
      // reports the class as the referrer with a negative tag, which the
      // rtag < 0 branch above treats as root-like (class objects are never
      // frontier entries), and heap-root references arrive here with
      // referrer_tag_ptr == nullptr. Without this, an entry first admitted
      // through a stack local keeps its transient classification forever
      // even after a later static-field sweep proves the same object is
      // the direct value of a static field - exactly the durable-root
      // discovery maybeUpgradeRootAttachedRootKind() exists for (same
      // tie-break heapRootCallback() applies on its own ALREADY_ADMITTED
      // case), so reuse it: upgrade only when this edge's kind is strictly
      // more durable, and drop any cached chain so it is rebuilt with the
      // upgraded root kind.
      if (ctx->tracker->maybeUpgradeRootAttachedRootKind(ctx->frontier,
                                                          *tag_ptr,
                                                          (u8)reference_kind)) {
        ctx->tracker->invalidateResolvedChain(*tag_ptr);
      }
    }
    // Auto-mark: if this object's class matches a watched leak class,
    // record its frontier tag so pollWatchedTargets() can build a chain
    // event for it. A leaking class typically has many live instances,
    // and each one's reference chain is independently useful — the
    // pre-tagged representative is just one sample, and its representative
    // may change (LRU-evicted) between polls. Recording all discovered
    // instances ensures we emit chain events for all of them, not just
    // whichever single object happened to be the representative when the
    // canary slot was first filled. See _candidate_discovered_tags's own
    // comment.
    if (result == ReferenceChainTracker::AdmitResult::ADMITTED &&
        ctx->tracker->_candidate_count > 0) {
      u32 klass_id = ctx->tracker->classTags()->resolve(class_tag);
      if (klass_id == 0) {
        // class_tag not in _class_tags - either class map rotated
        // (resolveLoadedClasses hasn't re-resolved yet) or this class
        // was never tagged. Log once per pass to diagnose class-map
        // rotation issues.
        TEST_LOG("ReferenceChainTracker::auto-mark class_tag=%lld "
                 "unresolved (not in _class_tags)",
                 (long long)class_tag);
      } else {
        bool matched = false;
        for (int s = 0; s < ctx->tracker->_candidate_count; s++) {
          if (ctx->tracker->_candidate_klass_ids[s] == klass_id) {
            matched = true;
            ctx->tracker->recordDiscoveredInstance(klass_id, *tag_ptr,
                                                   false);
            break;
          }
        }
        if (!matched && klass_id != 0) {
          // klass_id resolved but doesn't match any candidate - likely
          // class map rotation made candidate klass_ids stale
          TEST_LOG("ReferenceChainTracker::auto-mark klass_id=%u "
                   "resolved but no candidate match (candidates=[%u,%u,%u,%u,%u])",
                   klass_id,
                   ctx->tracker->_candidate_count > 0 ? ctx->tracker->_candidate_klass_ids[0] : 0,
                   ctx->tracker->_candidate_count > 1 ? ctx->tracker->_candidate_klass_ids[1] : 0,
                   ctx->tracker->_candidate_count > 2 ? ctx->tracker->_candidate_klass_ids[2] : 0,
                   ctx->tracker->_candidate_count > 3 ? ctx->tracker->_candidate_klass_ids[3] : 0,
                   ctx->tracker->_candidate_count > 4 ? ctx->tracker->_candidate_klass_ids[4] : 0);
        }
      }
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
      // Track this batch entry as visited for the rolling resume cursor
      // (see _last_visited_batch_tag's own comment).
      ctx->_last_visited_batch_tag = my_tag;
      return JVMTI_VISIT_OBJECTS;
    }
    return 0;
  }

  return JVMTI_VISIT_OBJECTS;
}

ReferenceChainTracker::AdmitResult ReferenceChainTracker::admitObject(
    FrontierTable *frontier, int hop_cap, int budget, int *edges_admitted,
    jlong *tag_ptr, jlong parent_tag, u32 referrer_klass, u32 depth,
    u8 root_kind, jlong class_tag, bool priority) {
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
                         FrontierEntryState::FRONTIER, root_kind, class_tag)) {
    return AdmitResult::FRONTIER_CAP_HIT;
  }
  *tag_ptr = tag;
  (*edges_admitted)++;
  // Queue for expandFrontier()/markAllFrontierExpanded() - see
  // _pending_expand's/_priority_expand's own declaration comments for why
  // this replaces a scan over the admitted range, and for why a
  // rotation-discovered child (priority=true) skips the ordinary backlog.
  if (priority && _priority_expand.size() < PRIORITY_EXPAND_CAP) {
    _priority_expand.push_back(tag);
  } else {
    // Priority lane full: the rotation backpressure falls back to the
    // ordinary backlog rather than silently dropping the re-discovered
    // subtree (see PRIORITY_EXPAND_CAP's own comment).
    _pending_expand.push_back(tag);
  }
  trackLeakAccumulation(frontier, class_tag, parent_tag, tag);
  return AdmitResult::ADMITTED;
}

void ReferenceChainTracker::trackLeakAccumulation(FrontierTable *frontier,
                                                   jlong class_tag,
                                                   jlong parent_tag,
                                                   jlong tag) {
  // Cheapest checks first: no klass_id is currently watched (the common
  // case before hasLeakSignal() has ever fired - see
  // _watched_leak_klass_ids' own comment), or this admission has no real
  // parent to attribute to (a root-attached entry - nothing to aggregate
  // by, since the "container" concept this tracks is specifically about a
  // PARENT object's field holding the leaf, not the leaf itself being
  // root-attached).
  if (_watched_leak_klass_count <= 0 || parent_tag == 0 || class_tag == 0) {
    return;
  }
  // (u32) truncation matches _watched_leak_klass_ids' own storage (see that
  // field's comment) - class tags are small, negative, sequentially-minted
  // values in practice (ClassTagAllocator::next()), so this never actually
  // loses distinguishing information; it just keeps the comparison and the
  // signature-key packing below in the same 32-bit space both already used
  // for the (superseded) classMap-id scheme.
  u32 truncated_class_tag = (u32)class_tag;
  bool watched = false;
  for (int i = 0; i < _watched_leak_klass_count; i++) {
    if (_watched_leak_klass_ids[i] == truncated_class_tag) {
      watched = true;
      break;
    }
  }
  if (!watched) {
    return;
  }
  FrontierEntry parent_entry{};
  if (!frontier->lookup(parent_tag, &parent_entry) ||
      parent_entry.class_tag == 0) {
    // Parent since pruned/dead between its own admission and this child's,
    // or admitted before this field existed on it (should not happen in
    // practice - class_tag is set at every admission - but a stale/unknown
    // parent identity is not something to attribute this observation to
    // either way.
    return;
  }
  u64 key = leakSignatureKey(truncated_class_tag, (u32)parent_entry.class_tag);
  _leak_signature_totals[key]++;
  auto it = _leak_parent_fanout.find(parent_tag);
  if (it == _leak_parent_fanout.end()) {
    TEST_LOG("ReferenceChainTracker::trackLeakAccumulation fanout-insert "
             "parent_tag=%lld parent_class_tag=%lld child_class_tag=%lld",
             (long long)parent_tag, (long long)parent_entry.class_tag,
             (long long)class_tag);
    _leak_parent_fanout.emplace(parent_tag, LeakParentFanoutEntry{key, 1});
  } else {
    // The signature key for a given parent_tag is fixed once recorded
    // (parent_entry.class_tag never changes once admitted; the LEAF side of
    // the key is fixed by which klass_id is currently watched at the time
    // of THIS call, which could in principle differ between two children of
    // the same parent if _watched_leak_klass_ids itself changed between
    // them - overwrite rather than accumulate under a stale key in that
    // case, since the stored signature_key should always reflect the most
    // recently observed watched klass_id for this parent).
    it->second.signature_key = key;
    it->second.fanout++;
  }
  // ANCESTOR FANOUT: the direct parent is not necessarily the part of the
  // holder chain that STAYS LIVE. A container that replaces its internals
  // (the canonical unmaintained-singleton leak: a growing ArrayList swaps
  // elementData on growth, a HashMap resizes its table) leaves the watched
  // instances' direct parents dead - observed live: the fanout filled with
  // old backing arrays while the live holder was never re-walked, its new
  // internals never admitted, and zero tagged chunks ever intercepted.
  // The ancestors up to the root ARE the durable holders, so record every
  // hop of the holder chain, not just the last one. Bounded: this only runs
  // for watched-klass admissions (rare - leak-candidate classes only), and
  // the walk stops at the root-attached entry (parent_tag == 0), typically
  // a handful of lookups.
  jlong ancestor = parent_entry.parent_tag;
  int hops = 0;
  while (ancestor != 0 && hops++ < _hop_cap) {
    FrontierEntry ancestor_entry{};
    if (!_frontier->lookup(ancestor, &ancestor_entry)) {
      break;
    }
    if (_leak_parent_fanout.find(ancestor) == _leak_parent_fanout.end()) {
      _leak_parent_fanout.emplace(ancestor, LeakParentFanoutEntry{key, 1});
    }
    if (ancestor_entry.parent_tag == 0) {
      break; // root-attached: the holder chain ends here
    }
    ancestor = ancestor_entry.parent_tag;
  }
}

void ReferenceChainTracker::seedLeakAccumulationForNewlyWatchedKlass(
    u32 klass_id) {
  if (_frontier == nullptr) {
    // pollWatchedTargets() can run before the first pass has ever created
    // the frontier table - nothing to seed from yet.
    return;
  }
  int table_size = _frontier->size();
  if (table_size <= 0) {
    return;
  }
  // Inlines trackLeakAccumulation()'s own signature/fanout update logic
  // (rather than calling it per matching entry) deliberately: this whole
  // scan already holds _frontier's shared lock for its duration (matching
  // collectStaleExpandedEntriesForRotation()'s own lockShared() rationale -
  // a per-tag SpinLock acquisition would double the cost of this O(table_size)
  // sweep), and trackLeakAccumulation() takes that same lock itself via
  // frontier->lookup() - calling it from inside an already-held shared
  // section would risk a reentrant-lock deadlock if a writer is ever
  // concurrently pending, so this uses lookupLocked() throughout instead.
  // Compares against (u32) FrontierEntry::class_tag - see that field's own
  // comment for why this, and not referrer_klass, is the stable identifier
  // klass_id (itself a truncated class_tag - _watched_leak_klass_ids' own
  // comment) can actually be matched against.
  _frontier->withSharedLock([&](const FrontierTable *frontier) {
    for (jlong tag = 1; tag <= table_size; tag++) {
      FrontierEntry entry{};
      if (!frontier->lookupLocked(tag, &entry) ||
          entry.state != FrontierEntryState::EXPANDED ||
          entry.parent_tag == 0 || (u32)entry.class_tag != klass_id) {
        continue;
      }
      FrontierEntry parent_entry{};
      if (!frontier->lookupLocked(entry.parent_tag, &parent_entry) ||
          parent_entry.class_tag == 0) {
        continue;
      }
      u64 key = leakSignatureKey(klass_id, (u32)parent_entry.class_tag);
      _leak_signature_totals[key]++;
      auto it = _leak_parent_fanout.find(entry.parent_tag);
      if (it == _leak_parent_fanout.end()) {
        _leak_parent_fanout.emplace(entry.parent_tag,
                                     LeakParentFanoutEntry{key, 1});
      } else {
        it->second.signature_key = key;
        it->second.fanout++;
      }
    }
  });
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
  TEST_LOG("ReferenceChainTracker::maybeUpgradeRootAttachedRootKind tag=%lld "
           "old_root_kind=%d -> new_root_kind=%d",
           (long long)tag, (int)entry.root_kind, (int)new_root_kind);
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
          !isQueuedForRotation(tag) &&
          _priority_expand.size() < PRIORITY_EXPAND_CAP) {
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
  // LEAK-PARENT PRIORITY, FAIR-SHARED WITH THE BLIND LAP: _leak_parent_fanout
  // knows the EXPANDED parents that actually lead to watched leak-klass
  // children - re-walking one of those re-sees its current children
  // (improveChain() upgrades children first admitted via a shallower path,
  // leak-tag interception for the tagged ones) and catches elements added
  // since its expansion, which is exactly the mutation this rotation exists
  // to observe. The fanout is orders of magnitude smaller than the table;
  // select from it first (rotating via _leak_parent_rotation_cursor for
  // coverage), up to HALF the budget (ceil) - then the blind table lap below
  // fills the remainder.
  //
  // Why capped at half rather than fanout-first-until-exhausted (the
  // original design, observed broken live): the fanout only ever contains
  // parents of watched instances ALREADY ADMITTED as their direct children -
  // and for a container that REPLACES its internals (the canonical
  // unmaintained-singleton case: a growing ArrayList swaps elementData on
  // growth), the watched instances' direct parents are the OLD, now-dead
  // backing arrays, while the live holder's new internals are never in the
  // fanout at all (the holder's own direct children are non-watched
  // container internals). Re-walking the LIVE holder is what admits each
  // new backing array; only the blind lap selects an arbitrary EXPANDED
  // holder. With an unbounded fanout-first policy and a fanout grown to
  // ~11k entries, the fanout filled ALL 256 selections every pass
  // (observed live: rotation edges admitted in only 4 of 206 passes, the
  // sink's resized backing arrays never admitted, zero interceptions) and
  // the lap never ran - the exact starvation this rotation was built to
  // prevent, reproduced one level down. A half/half split guarantees both
  // tiers make progress every pass.
  //
  // FANOUT HYGIENE: entries whose parent no longer resolves in the
  // frontier (pruned: dead object, search-restart wipe) can never be
  // re-walked again, yet accumulate forever without this erase - observed
  // live as an 11k-entry fanout of overwhelmingly-dead old backing arrays,
  // which both bloats this scan and makes _leak_parent_rotation_cursor's
  // lap arithmetic cover mostly corpses. Entries that exist but are not
  // EXPANDED yet (still pending expansion) are kept - their children have
  // not even been seen once.
  if (!_leak_parent_fanout.empty() &&
      _priority_expand.size() < PRIORITY_EXPAND_CAP) {
    int fanout_budget = (max_count + 1) / 2;
    size_t fanout_size = _leak_parent_fanout.size();
    u64 skip = _leak_parent_rotation_cursor % fanout_size;
    auto it = _leak_parent_fanout.begin();
    while (it != _leak_parent_fanout.end()) {
      if ((int)selected.size() >= fanout_budget ||
          _priority_expand.size() >= PRIORITY_EXPAND_CAP) {
        break;
      }
      if (skip > 0) {
        skip--;
        ++it;
        continue;
      }
      jlong parent_tag = it->first;
      if (isQueuedForRotation(parent_tag)) {
        ++it;
        continue;
      }
      FrontierEntry entry{};
      // Dead parent: either the frontier slot is gone entirely, or it was
      // clear()'d (dead object / restart wipe) - clear() marks the slot
      // ABANDONED rather than removing it, so both conditions must erase
      // (tags are never reused within a search and the fanout is wiped on
      // restart, so an ABANDONED parent can never come back to life).
      if (!_frontier->lookup(parent_tag, &entry) ||
          entry.state == FrontierEntryState::ABANDONED) {
        it = _leak_parent_fanout.erase(it);
        continue;
      }
      if (entry.state != FrontierEntryState::EXPANDED) {
        ++it;
        continue;
      }
      selected.push_back(parent_tag);
      _priority_expand.push_back(parent_tag);
      ++it;
    }
    _leak_parent_rotation_cursor += selected.size() + 1;
    if ((int)selected.size() >= max_count) {
      // Budget exhausted by the fanout alone (only possible for
      // max_count == 1, where the fanout's ceil-half share is the whole
      // budget) - fanout-priority preserved, and the lap below has nothing
      // left to do this pass.
      return selected;
    }
  }
  if (_stale_expanded_rotation_cursor <= 0 ||
      _stale_expanded_rotation_cursor > table_size) {
    _stale_expanded_rotation_cursor = 1;
  }
  // Resume scanning from _stale_expanded_rotation_cursor rather than always
  // restarting at tag 1: a frontier table can accumulate far more than
  // max_count entries that are EXPANDED and stay that way forever
  // (long-lived infrastructure objects - caches, maps, bootstrap classes).
  // An always-from-1 scan would let that low-tag population fill this
  // sweep's entire cap on every single call, permanently starving any
  // EXPANDED entry with a higher tag (e.g. a static field's collection,
  // admitted only once its class loads well after startup) of ever being
  // re-queued. A wrapping cursor, like collectStaleRootKindEntriesForRotation()
  // above already uses, guarantees every entry gets a turn within
  // ceil(table_size / max_count) calls instead of never.
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
  //
  // A sparse stretch of non-EXPANDED/already-queued tags could make this
  // scan run long chasing max_count with no wall-clock bound of its own -
  // unlike heapReferenceCallback()'s per-edge check, this scan isn't itself
  // a JVMTI/STW call, but it still steals from the same _pass_deadline_ns
  // window the actual walk needs (see that field's own comment). Amortized
  // the same way heapReferenceCallback() amortizes its own check: an
  // OS::nanotime() call every iteration would
  // itself be a meaningful fraction of this loop's per-tag cost.
  int deadline_check_counter = 0;
  jlong start_tag = _stale_expanded_rotation_cursor;
  jlong tag = start_tag;
  _frontier->withSharedLock([&](const FrontierTable *frontier) {
    do {
      if (_pass_deadline_ns != 0 &&
          (++deadline_check_counter & 0xFFF) == 0 &&
          OS::nanotime() >= _pass_deadline_ns) {
        // Ran past this pass's wall-clock share - stop scanning with
        // whatever was already selected (possibly none) and resume from
        // here next call. The wrapping cursor already tolerates a call that
        // selects fewer than max_count, so this composes without any
        // special-casing.
        break;
      }
      FrontierEntry entry{};
      if (frontier->lookupLocked(tag, &entry) &&
          entry.state == FrontierEntryState::EXPANDED &&
          !isQueuedForRotation(tag) &&
          _priority_expand.size() < PRIORITY_EXPAND_CAP) {
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
  _stale_expanded_rotation_cursor = tag;
  return selected;
}

// Bounded rotating re-expansion targeting the accumulation point of a
// klass LivenessTracker has flagged as growing - the design's actual
// targeted tier, replacing an earlier structural (depth + root-durability +
// class-shape) heuristic that measurement against a real classpath showed
// selects far too much of the reachable graph to fit in a small budget (see
// git history and doc/temp/ investigation notes). This design instead uses
// the one signal that CAN distinguish "the specific container that is
// leaking" from "the many unrelated objects that happen to hold instances
// of a common leaf class" without needing a full dominator-tree/retained-
// size computation (a wider web search into how heap analysis tools solve
// this - Eclipse MAT's accumulation-point/big-drop-in-dominator-tree
// heuristic, Cork's class-level points-from summary diffed across GCs,
// LeakBot's rank-cheaply-then-track-only-the-winners discipline - converged
// on the same two-tier shape implemented here):
//
// Tier 1 (class-level, cheap, aggregated at admission time by
// trackLeakAccumulation() into _leak_signature_totals/_leak_parent_fanout -
// no full-table scan): rank (leaf_klass_id, parent_class_id) signatures by
// growth since the previous pass (current total minus the snapshot rolled
// forward at the end of that pass), Cork-style. This collapses "thousands
// of objects holding a common leaf class" into a handful of signatures - a
// legitimate cache class that merely holds MANY instances, but not a
// GROWING number of them pass over pass, never wins here, regardless of its
// absolute size.
//
// Tier 2 (spent only within the winning signature): rank the concrete
// parent objects contributing to it by their own fanout of the flagged
// leaf klass_id - the highest-fanout parent is the one whose already-
// EXPANDED state is most likely stale (i.e. its own children were admitted
// once and it has since accumulated more that were never observed), so it
// is the one worth spending this pass's rotation budget re-expanding.
//
// Unlike the other two rotation collectors, this one does not use a
// wrapping cursor: it always selects the current best candidates rather
// than guaranteeing fair coverage of a population, since re-selecting the
// same still-growing parent every pass is exactly the desired behavior,
// not something a fairness guarantee needs to correct for.
std::vector<jlong>
ReferenceChainTracker::collectLeakAccumulationCandidatesForRotation(
    int max_count) {
  std::vector<jlong> selected;
  if (max_count <= 0 || _leak_signature_totals.empty()) {
    return selected;
  }

  // Tier 1: rank signatures by growth since the last pass's snapshot. A
  // signature with no prior snapshot (brand new this pass) compares against
  // an implicit prev_total of 0 - see _leak_signature_prev_totals' own
  // comment for why that is the correct behavior, not a special case.
  u64 winning_key = 0;
  bool have_winner = false;
  u32 best_delta = 0;
  for (const auto &kv : _leak_signature_totals) {
    u32 prev = 0;
    auto prev_it = _leak_signature_prev_totals.find(kv.first);
    if (prev_it != _leak_signature_prev_totals.end()) {
      prev = prev_it->second;
    }
    u32 delta = kv.second > prev ? kv.second - prev : 0;
    if (delta > 0 && (!have_winner || delta > best_delta)) {
      have_winner = true;
      best_delta = delta;
      winning_key = kv.first;
    }
  }
  // Roll the snapshot forward for the NEXT pass's comparison regardless of
  // whether this pass found a winner - a signature that didn't grow this
  // pass still needs its current total remembered so a future pass's delta
  // is computed against the right baseline, not against however many
  // passes ago it was last checked.
  _leak_signature_prev_totals = _leak_signature_totals;
  if (!have_winner) {
    // Nothing grew since last pass - nothing to prioritize this tier this
    // time (collectStaleExpandedEntriesForRotation()'s unprioritized
    // fallback still covers this population eventually).
    return selected;
  }

  // Tier 2: within the winning signature only, rank concrete parent objects
  // by their own fanout - collected first, then partially sorted, since
  // _leak_parent_fanout's total size is what bounds this method's cost (not
  // table_size), and is expected to be small (see that map's own comment).
  std::vector<std::pair<jlong, u32>> candidates; // (parent_tag, fanout)
  for (const auto &kv : _leak_parent_fanout) {
    if (kv.second.signature_key == winning_key && !isQueuedForRotation(kv.first)) {
      FrontierEntry entry{};
      if (_frontier->lookup(kv.first, &entry) &&
          entry.state == FrontierEntryState::EXPANDED) {
        candidates.emplace_back(kv.first, kv.second.fanout);
      }
    }
  }
  std::sort(candidates.begin(), candidates.end(),
            [](const std::pair<jlong, u32> &a, const std::pair<jlong, u32> &b) {
              return a.second > b.second;
            });
  for (const auto &c : candidates) {
    if ((int)selected.size() >= max_count ||
        _priority_expand.size() >= PRIORITY_EXPAND_CAP) {
      break;
    }
    selected.push_back(c.first);
    _priority_expand.push_back(c.first);
  }
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
      /*parent_tag=*/0, referrer_klass, /*depth=*/0, translated_root_kind,
      class_tag);
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
                                               bool *frontier_cap_hit,
                                               u64 *safepoint_ticks) {
  assert(!t_inGCCallback &&
         "IterateOverReachableObjects/FollowReferences are JVMTI "
         "Heap-category calls and must not be made from "
         "GarbageCollectionStart/Finish");

  *safepoint_ticks = 0;

  // Shared wall-clock ceiling for this whole call's static-field sweep,
  // expandFrontier(), and rotation sub-calls below (see _pass_deadline_ns's
  // own comment) - deliberately NOT applied to root/stack-ref enumeration
  // itself, which is instead cadence-gated by run_root_enum/
  // ROOT_ENUM_MIN_INTERVAL_NS.
  _pass_deadline_ns = _effective_pause_target_ms > 0
                          ? OS::nanotime() + (u64)_effective_pause_target_ms * 1000000ULL
                          : 0;

  *edges_admitted = 0;
  *truncated = false;
  *frontier_cap_hit = false;

  // Reserve a slice for rotation up front, across all three tiers (see
  // ROOT_KIND_ROTATION_BUDGET/LEAK_ACCUMULATION_ROTATION_BUDGET/
  // STALE_EXPANDED_ROTATION_BUDGET's own comments) so rotation still gets to
  // run this pass even when ordinary work below spends everything else and
  // truncates. Also capped at half of expand_budget: without that cap, a
  // pacing-throttled pass (expand_budget down near MIN_EFFECTIVE_BUDGET)
  // would hand rotation its full reservation and leave ordinary expansion
  // with 0 - exactly the priority inversion this reservation exists to
  // avoid, just for the other side. Capping at half means each side
  // degrades proportionally as pacing throttles down, instead of either one
  // hitting a hard 0.
  int rotation_reserved_budget = std::min(
      expand_budget / 2, ROOT_KIND_ROTATION_BUDGET +
                              LEAK_ACCUMULATION_ROTATION_BUDGET +
                              STALE_EXPANDED_ROTATION_BUDGET);
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

    u64 root_enum_start_ticks = TSC::ticks();
    jvmtiError root_err = jvmti->IterateOverReachableObjects(
        heapRootCallback, stackRefCallback, /*object_ref_callback=*/nullptr,
        &ctx);
    *safepoint_ticks += TSC::ticks() - root_enum_start_ticks;

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
  TEST_LOG("ReferenceChainTracker::runPassManualWalk static_sweep_gate "
           "resolved=%d swept=%d cursor=%d",
           _last_resolved_class_count, _last_static_field_class_count,
           _static_field_sweep_cursor);
  if (_last_resolved_class_count != _last_static_field_class_count) {
    int static_field_edges_admitted = 0;
    bool static_field_truncated = false;
    bool static_field_frontier_cap_hit = false;
    bool static_field_cycle_complete = false;
    int static_field_budget = std::max(budget - expand_phase_edges_admitted, 0);
    admitStaticFieldRoots(jvmti, jni, _hop_cap, static_field_budget,
                          &static_field_edges_admitted, &static_field_truncated,
                          &static_field_frontier_cap_hit,
                          &static_field_cycle_complete, safepoint_ticks);
    expand_phase_edges_admitted += static_field_edges_admitted;
    *edges_admitted += static_field_edges_admitted;
    // TEMP DIAGNOSTIC (see doc/temp/ investigation notes): split out how much
    // of this pass's budget/deadline the static-field sweep's current chunk
    // alone consumed, and whether that chunk completed / the lap wrapped -
    // to distinguish "a chunk never finishes within the per-pass deadline"
    // from "chunks finish but rotation/expansion still can't find the
    // target".
    TEST_LOG("ReferenceChainTracker::runPassManualWalk static_field_phase "
             "edges_admitted=%d truncated=%d frontier_cap_hit=%d "
             "cycle_complete=%d sweep_cursor=%d "
             "last_resolved_class_count=%d last_static_field_class_count=%d",
             static_field_edges_admitted, (int)static_field_truncated,
             (int)static_field_frontier_cap_hit, (int)static_field_cycle_complete,
             _static_field_sweep_cursor, _last_resolved_class_count,
             _last_static_field_class_count);
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
    }
    if (static_field_cycle_complete) {
      // The chunk cursor completed a full lap over the loaded-class list
      // with no chunk truncating along the way (possibly discovering
      // nothing, if every static field seen was already ALREADY_ADMITTED) -
      // remember the class count it covered so a later pass with no new
      // classes can skip re-running the sweep entirely. Left unset if any
      // chunk in the lap truncated (admitStaticFieldRoots() already started
      // the next lap immediately in that case) so passes keep retrying
      // instead of wrongly treating a still-incomplete sweep as done.
      _last_static_field_class_count = _last_resolved_class_count;
    }
  }

  int expand_edges_admitted = 0;
  bool expand_truncated = false;
  bool expand_frontier_cap_hit = false;
  int remaining_budget = std::max(budget - expand_phase_edges_admitted, 0);
  // Give expand its own fresh deadline so the static-field sweep's
  // FollowReferences calls don't eat expand's time. Each sub-operation
  // (sweep, expand, rotation) gets its own _effective_pause_target_ms
  // wall-clock budget — the cumulative rate is still capped by the pass
  // cadence (effectiveCadenceNs). See q-safepoint-budget-model.
  _pass_deadline_ns = _effective_pause_target_ms > 0
                          ? OS::nanotime() + (u64)_effective_pause_target_ms * 1000000ULL
                          : 0;
  expandFrontier(jvmti, jni, _hop_cap, remaining_budget,
                 &expand_edges_admitted, &expand_truncated,
                 &expand_frontier_cap_hit, safepoint_ticks);
  expand_phase_edges_admitted += expand_edges_admitted;
  *edges_admitted += expand_edges_admitted;
  *truncated = *truncated || expand_truncated;
  *frontier_cap_hit = expand_frontier_cap_hit;
  TEST_LOG("ReferenceChainTracker::runPassManualWalk expand_phase "
           "edges_admitted=%d truncated=%d frontier_cap_hit=%d "
           "remaining_budget=%d",
           expand_edges_admitted, (int)expand_truncated,
           (int)expand_frontier_cap_hit, remaining_budget);

  // Note: unlike a hard truncation during root/stack-ref enumeration or the
  // static-field sweep above (which return early - the pass never even
  // reached ordinary expansion), a truncated ordinary expansion does NOT
  // skip rotation below: rotation runs on its own reserved slice of budget
  // (see rotation_reserved_budget's own comment above) precisely because
  // ordinary expansion truncates on nearly every pass under a sustained
  // fast-growing backlog, and that is exactly the situation - a mutable
  // field reassigned out from under an already-EXPANDED entry - rotation
  // exists to correct.

  // Three-tier bounded rotating re-expansion (design doc's closing section,
  // Phase 5 item 3, extended - see each collector's own comment for why it
  // exists as its own tier): re-walk a bounded, rotating subset of
  // already-EXPANDED entries so mutations to an already-expanded object's
  // fields - a durable root discovered elsewhere for a stale attribution, or
  // a mutable collection field reassigned out from under a container object
  // - get a chance to be observed on a later pass. Runs after the ordinary
  // expansion above so it only ever spends whatever budget that left
  // unused, plus its own reserved slice. Ordered highest-value/cheapest
  // first: root-attribution re-verification (small, bounded population),
  // then the leak-accumulation growth-catching tier (also small, bounded,
  // and the one that actually targets this leak shape), then the
  // unprioritized whole-table fallback last.
  std::vector<jlong> rotation_tags =
      collectStaleRootKindEntriesForRotation(ROOT_KIND_ROTATION_BUDGET);
  std::vector<jlong> leak_accumulation_tags =
      collectLeakAccumulationCandidatesForRotation(
          LEAK_ACCUMULATION_ROTATION_BUDGET);
  // Also re-walk a bounded, rotating subset of EXPANDED entries regardless
  // of root attribution: a mutable field reassigned since an
  // object's one-time expansion - e.g. HashMap.table on resize - is
  // otherwise never observed again, silently orphaning everything only
  // reachable through the field's current value. See
  // collectStaleExpandedEntriesForRotation()'s own comment.
  std::vector<jlong> stale_expanded_tags =
      collectStaleExpandedEntriesForRotation(STALE_EXPANDED_ROTATION_BUDGET);
  // TEMP DIAGNOSTIC (see static_field_phase log above).
  TEST_LOG("ReferenceChainTracker::runPassManualWalk rotation_candidates "
           "root_kind_tags=%zu leak_accumulation_tags=%zu stale_expanded_tags=%zu "
           "watched_leak_klass_count=%d leak_signatures=%zu leak_parents=%zu",
           rotation_tags.size(), leak_accumulation_tags.size(),
           stale_expanded_tags.size(), _watched_leak_klass_count,
           _leak_signature_totals.size(), _leak_parent_fanout.size());
  if (rotation_tags.empty() && leak_accumulation_tags.empty() &&
      stale_expanded_tags.empty()) {
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
  // Give rotation its own fresh deadline, same as expand above.
  _pass_deadline_ns = _effective_pause_target_ms > 0
                          ? OS::nanotime() + (u64)_effective_pause_target_ms * 1000000ULL
                          : 0;
  bool rotation_frontier_cap_hit = false;
  expandFrontier(jvmti, jni, _hop_cap, rotation_budget,
                 &rotation_edges_admitted, &rotation_truncated,
                 &rotation_frontier_cap_hit, safepoint_ticks);
  *edges_admitted += rotation_edges_admitted;
  // TEMP DIAGNOSTIC (see static_field_phase log above).
  TEST_LOG("ReferenceChainTracker::runPassManualWalk rotation_phase "
           "edges_admitted=%d truncated=%d frontier_cap_hit=%d "
           "rotation_budget=%d",
           rotation_edges_admitted, (int)rotation_truncated,
           (int)rotation_frontier_cap_hit, rotation_budget);
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
                                            bool *frontier_cap_hit,
                                            u64 *safepoint_ticks) {
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
  if (jni != nullptr && _cached_object_class == nullptr) {
    jclass local = jni->FindClass("java/lang/Object");
    if (!jniExceptionCheck(jni) && local != nullptr) {
      _cached_object_class = (jclass)jni->NewGlobalRef(local);
    }
    if (local != nullptr) {
      jni->DeleteLocalRef(local);
    }
  }
  jclass object_class = _cached_object_class;

  bool progress = true;
  // FAIR-SHARE DRAIN: alternate batches between _priority_expand and
  // _pending_expand whenever both are non-empty (priority still takes the
  // first batch of each call). The original strict priority-first drain
  // starved the ordinary backlog whenever rotation's inflow
  // (~STALE_EXPANDED_ROTATION_BUDGET+ROOT_KIND_ROTATION_BUDGET per pass)
  // exceeded the deadline-bounded drain (~2-3 GetObjectsWithTags calls per
  // phase) - observed live on hotdog: _priority_expand grew 39k->103k in 20
  // minutes while the BFS's own _pending_expand (66k entries) was never
  // drained by a single batch, freezing all new-territory crawl.
  // Alternation guarantees the ordinary frontier at least every other
  // batch regardless of queue depths; an empty lane falls back to the
  // other one. The toggle is the _expand_lane_prefer_priority MEMBER
  // (not a local of this invocation): the phase deadlines bound a typical
  // invocation to a single batch, so a per-invocation reset made priority
  // win every invocation - observed live on hotdog with round 3's build,
  // where _pending_expand GREW 109k->113k across 260 passes while every
  // gotw call drained the priority lane's stale re-walks (edges=0).
  while (!ctx.truncated && progress && object_class != nullptr) {
    // Wall-clock deadline check per iteration: GetObjectsWithTags runs OUTSIDE
    // any FollowReferences callback, so heapReferenceCallback()'s amortized
    // deadline check never sees its cost. Measured live on hotdog: a
    // collapsed batch (batch=2) let ~1400 unchecked GetObjectsWithTags calls
    // (~20ms each) run in one expand phase, spending 10.4s of CPU and ~30s of
    // wall time in a single pass. Checking here bounds each phase to
    // _effective_pause_target_ms regardless of batch health.
    if (_pass_deadline_ns != 0 && OS::nanotime() >= _pass_deadline_ns) {
      ctx.truncated = true;
      break;
    }
    progress = false;

    // Alternate lanes (see FAIR-SHARE DRAIN above); priority still goes
    // first so a rotation-selected parent's re-discovery keeps its
    // head-of-queue property, but no lane can monopolize the drain.
    bool from_priority;
    if (_priority_expand.empty()) {
      from_priority = false;
    } else if (_pending_expand.empty()) {
      from_priority = true;
    } else {
      from_priority = _expand_lane_prefer_priority;
      _expand_lane_prefer_priority = !_expand_lane_prefer_priority;
    }
    std::deque<jlong> &source =
        from_priority ? _priority_expand : _pending_expand;
    ctx.admit_priority = from_priority;
    if (source.empty()) {
      break; // nothing pending in either lane
    }

    // SELF-CALIBRATING ADAPTIVE BATCH SIZE for GetObjectsWithTags.
    // GetObjectsWithTags iterates the whole JVMTI tag map per call, so its
    // cost has a batch-independent floor that grows with the frontier
    // (measured live: ~20ms at a 225k-entry map regardless of batch_size).
    // Calibrating batch_size from a per-tag EMA collapses in that regime
    // (small batch inflates per-tag cost, which shrinks the batch further —
    // observed live driving batch from ~400 to 2). Instead, AIMD directly on
    // batch size against the measured per-CALL time vs GOTW_CPU_BUDGET_NS —
    // see _gotw_batch_size's own comment.
    //
    // Still capped at `budget` and `_budget` for the original reasons
    // (first-pass budget can be far larger than the backlog; a single
    // huge batch risks JNI local-capacity/OOM with zero progress).
    size_t gotw_batch_size =
        _gotw_batch_size != 0 ? _gotw_batch_size : GOTW_INITIAL_BATCH_SIZE;
    size_t batch_size = std::min(
        source.size(),
        std::min((size_t)std::max(std::min(budget, _budget), 1),
                 gotw_batch_size));
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
    u64 gotw_start_ns = OS::nanotime();
    jvmtiError resolve_err = jvmti->GetObjectsWithTags(
        (jint)candidate_tags.size(), candidate_tags.data(), &resolved_count,
        &resolved_objects, &resolved_tags);
    u64 gotw_elapsed_ns = OS::nanotime() - gotw_start_ns;
    // Self-calibrate (PROPORTIONAL batch control): update the EMA of
    // PER-CALL elapsed time, then scale the batch so ONE call fills the
    // remaining wall-clock window. This replaces the earlier per-call AIMD
    // (fixed budget, halve/add-64): measured live on hotdog, the tag map
    // grew until the per-call floor alone (~27ms at a 243k-entry map)
    // exceeded the fixed 25ms budget, so AIMD ratcheted to GOTW_MIN_BATCH
    // and stayed there (batch=8 forever) even though batch=72 cost only
    // +36% for 9x the objects - the floor-dominated regime in which a
    // BIGGER batch is the right move, and only a proportion against the
    // remaining deadline can see that. See _gotw_batch_size's own
    // comment for the full history (incl. the earlier per-tag collapse).
    if (batch_size > 0 && gotw_elapsed_ns > 0) {
      if (_gotw_ema_call_ns == 0) {
        _gotw_ema_call_ns = gotw_elapsed_ns;
      } else {
        _gotw_ema_call_ns = _gotw_ema_call_ns * 4 / 5 + gotw_elapsed_ns / 5;
      }
      u64 now_ns = OS::nanotime();
      u64 window_ns =
          _pass_deadline_ns != 0 && _pass_deadline_ns > now_ns
              ? _pass_deadline_ns - now_ns
              : GOTW_CPU_BUDGET_NS;
      // window_ns / ema_call_ns == how many such calls fit the window;
      // scaling the CURRENT calibration batch by that ratio sizes the next
      // call to consume the whole window in one go. Extrapolate from the
      // stored _gotw_batch_size (the intended size), not from batch_size:
      // batch_size is capped by the lane depth (min(source.size(), ...)),
      // and a shallow lane would calibrate the stored size toward its own
      // depth even though the stored size is what the next deep-lane call
      // will use. Integer division biases the next batch slightly small -
      // safe (an under-filled window just runs a second call; an
      // over-filled one overruns the deadline).
      size_t calib_batch =
          _gotw_batch_size != 0 ? _gotw_batch_size : GOTW_INITIAL_BATCH_SIZE;
      size_t next_batch = (size_t)((u64)calib_batch * window_ns /
                                   std::max(_gotw_ema_call_ns, 1ULL));
      _gotw_batch_size = std::min(std::max(next_batch, GOTW_MIN_BATCH),
                                  GOTW_MAX_BATCH);
    }
    if (resolve_err != JVMTI_ERROR_NONE) {
      ctx.truncated = true;
      break;
    }

    // TEMP DIAGNOSTIC: verify adaptive batch_size is working
    TEST_LOG("ReferenceChainTracker::expandFrontier gotw "
             "batch_size=%zu resolved=%d edges=%d gotw_ms=%llu ema_call_ms=%llu "
             "next_batch=%llu",
             batch_size, resolved_count, ctx.edges_admitted,
             (unsigned long long)(gotw_elapsed_ns / 1000000ULL),
             (unsigned long long)(_gotw_ema_call_ns / 1000000ULL),
             (unsigned long long)(_gotw_batch_size != 0 ? _gotw_batch_size
                                                       : GOTW_INITIAL_BATCH_SIZE));

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
          ctx._last_visited_batch_tag = 0; // reset rolling cursor
          u64 follow_start_ticks = TSC::ticks();
          jvmtiError follow_err =
              jvmti->FollowReferences(0, nullptr, holder, &callbacks, &ctx);
          *safepoint_ticks += TSC::ticks() - follow_start_ticks;
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
    } else if (ctx._last_visited_batch_tag != 0) {
      // ROLLING RESUME: FollowReferences truncated mid-batch, but we know
      // which batch entry was being visited when it stopped (tracked by
      // the callback's batch_tags descent-gate). Pop entries that were
      // fully processed BEFORE that entry (mark live ones EXPANDED, clear
      // dead ones), and leave the partially-processed entry and everything
      // after it at the front of the source queue for the next pass to
      // retry. Same resumable-cursor pattern as admitStaticFieldRoots()'s
      // sweep cursor — avoids re-walking already-expanded entries (and
      // re-paying GetObjectsWithTags's O(tag_map × batch) cost for them)
      // on every retry.
      //
      // The partially-visited entry (at _last_visited_batch_tag) stays:
      // some of its children may have been admitted before the truncation,
      // and the rest are discovered on retry (admitObject is idempotent —
      // already-admitted children return ALREADY_ADMITTED).
      for (size_t i = 0; i < candidate_tags.size(); i++) {
        if (candidate_tags[i] == ctx._last_visited_batch_tag) {
          break; // stop at the partially-visited entry
        }
        jlong tag = candidate_tags[i];
        if (live.find(tag) == live.end()) {
          _frontier->clear(tag);
        } else {
          _frontier->markExpanded(tag);
        }
        source.pop_front();
      }
    }
    // else truncated with no batch entry visited (e.g. GetObjectsWithTags
    // error, holder allocation failure, or truncation before the first
    // batch entry was reached): leave the entire batch at the front of the
    // source queue for a later pass to retry, same as before.

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
                                                   bool *frontier_cap_hit,
                                                   bool *cycle_complete,
                                                   u64 *safepoint_ticks) {
  assert(!t_inGCCallback &&
         "GetLoadedClasses/FollowReferences are JVMTI Heap-category calls "
         "and must not be made from GarbageCollectionStart/Finish");
  *edges_admitted = 0;
  *truncated = false;
  *frontier_cap_hit = false;
  *cycle_complete = false;

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

  // GetLoadedClasses() gives no ordering guarantee across separate calls, so
  // the cursor below is only meaningful as an index into THIS call's array -
  // reprioritize it every call rather than trying to cache an ordering.
  // Application/library classes (any non-bootstrap classloader) are moved to
  // the front so a chunked sweep (below) reaches a likely leak source within
  // its first several chunks instead of only after every JDK/platform class
  // (typically the majority of a real JVM's loaded-class count) has been
  // swept first. In-place two-way partition, no extra allocation.
  jint app_boundary = 0;
  for (jint i = 0; i < class_count; i++) {
    jobject loader = nullptr;
    jvmtiError loader_err = jvmti->GetClassLoader(classes[i], &loader);
    bool is_app_class = (loader_err == JVMTI_ERROR_NONE) && (loader != nullptr);
    if (loader != nullptr) {
      jni->DeleteLocalRef(loader);
    }
    if (is_app_class) {
      if (i != app_boundary) {
        std::swap(classes[i], classes[app_boundary]);
      }
      app_boundary++;
    }
  }

  if (_static_field_sweep_cursor >= class_count) {
    // Loaded-class count shrank since the last chunk (classes unloaded) -
    // restart the lap rather than reading out of range.
    _static_field_sweep_cursor = 0;
    _static_field_sweep_cycle_truncated = false;
  }
  jint chunk_start = _static_field_sweep_cursor;
  jint chunk_end =
      std::min(chunk_start + STATIC_FIELD_SWEEP_CHUNK_CLASSES, class_count);
  jint chunk_count = chunk_end - chunk_start;

  // Same java/lang/Object element-type cache expandFrontier() uses for its
  // own frontier-holder array - shared across both call sites on this same
  // attached JNIEnv rather than a second FindClass() per pass.
  if (_cached_object_class == nullptr) {
    jclass local = jni->FindClass("java/lang/Object");
    if (!jniExceptionCheck(jni) && local != nullptr) {
      _cached_object_class = (jclass)jni->NewGlobalRef(local);
    }
    if (local != nullptr) {
      jni->DeleteLocalRef(local);
    }
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

  jobjectArray holder = jni->NewObjectArray(chunk_count, object_class, nullptr);
  if (jniExceptionCheck(jni)) {
    // OutOfMemoryError (or any other exception) building the holder -
    // clear it rather than let it survive into the DeleteLocalRef() calls
    // below (JNI spec: undefined behavior with a pending exception across
    // ordinary JNI calls), same as expandFrontier()'s identical case.
    holder = nullptr;
  }
  if (holder != nullptr) {
    // Fill in REVERSE chunk order: holder[0] = classes[chunk_end-1], ...,
    // holder[chunk_count-1] = classes[chunk_start]. HotSpot's
    // FollowReferences visits the initial_object (the holder array) by
    // pushing it on a LIFO visit_stack and popping (jvmtiTagMap.cpp:
    // iterate_over_array pushes elements 0..n-1 in order, the while-loop
    // pops LIFO), so classes are descended in REVERSE holder order.
    // Reversing the fill makes the descent visit classes in ASCENDING
    // original index order (chunk_start first), which is what
    // admitStaticFieldRoots()'s resumable cursor below assumes: an abort
    // at class p means classes chunk_start..p-1 are done and p+1..chunk_end-1
    // are pending, so the cursor resumes at p (redoing the partial class)
    // without re-walking completed classes.
    for (jint i = 0; i < chunk_count; i++) {
      jni->SetObjectArrayElement(holder, i, classes[chunk_end - 1 - i]);
      if (jniExceptionCheck(jni)) {
        holder = nullptr;
        break;
      }
    }
  }

  // GetLoadedClasses() returned a local ref for every class regardless of
  // chunk selection - free all of them here, not just the chunk.
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
  // Per-class non-STATIC_FIELD admission cap (see PassContext::_class_other_cap's
  // own comment). STATIC_FIELD edges are always admitted; non-static edges
  // (CONSTANT_POOL, INTERFACE, SUPERCLASS, CLASS_LOADER, ...) are admitted
  // up to this many per class per lap, then dropped for the rest of that
  // class. 32 covers a typical class's full constant-pool/interface set;
  // outlier classes are bounded so they cannot blow the chunk's deadline.
  ctx._class_other_cap = STATIC_FIELD_SWEEP_NON_STATIC_CAP_PER_CLASS;
  // TEMP DIAGNOSTIC (see doc/temp/ investigation notes): see PassContext::
  // kind_counts's own comment.
  int kind_counts[32];
  memset(kind_counts, 0, sizeof(kind_counts));
  ctx.kind_counts = kind_counts;

  jvmtiHeapCallbacks callbacks;
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.heap_reference_callback = heapReferenceCallback;
  u64 follow_start_ticks = TSC::ticks();
  jvmtiError follow_err =
      jvmti->FollowReferences(0, nullptr, holder, &callbacks, &ctx);
  *safepoint_ticks += TSC::ticks() - follow_start_ticks;
  jni->DeleteLocalRef(holder);
  // TEMP DIAGNOSTIC (see doc/temp/ investigation notes): kind indices per
  // jvmti.h's jvmtiHeapReferenceKind - 1=CLASS 2=FIELD 3=ARRAY_ELEMENT
  // 4=CLASS_LOADER 5=SIGNERS 6=PROTECTION_DOMAIN 7=INTERFACE 8=STATIC_FIELD
  // 9=CONSTANT_POOL 10=SUPERCLASS (21-27 are root kinds, not expected here).
  TEST_LOG("ReferenceChainTracker::admitStaticFieldRoots kind_counts "
           "k1=%d k2=%d k3=%d k4=%d k5=%d k6=%d k7=%d k8=%d k9=%d k10=%d",
           kind_counts[1], kind_counts[2], kind_counts[3], kind_counts[4],
           kind_counts[5], kind_counts[6], kind_counts[7], kind_counts[8],
           kind_counts[9], kind_counts[10]);
  if (follow_err != JVMTI_ERROR_NONE) {
    return;
  }

  *edges_admitted = ctx.edges_admitted;
  *truncated = ctx.truncated;
  *frontier_cap_hit = ctx.frontier_cap_hit;

  if (ctx.truncated) {
    _static_field_sweep_cycle_truncated = true;
    // Resumable cursor: instead of skipping to chunk_end (losing every
    // class after the interruption point for the rest of this lap), resume
    // at the class we were inside when the walk aborted. The holder was
    // filled in reversed order so descent visits classes in ascending
    // original index order; _classes_in_chunk_visited counts how many
    // classes were entered before the abort. Resume at chunk_start + count
    // - 1 to redo the partial class (its already-admitted edges hit
    // ALREADY_ADMITTED cheaply; with the per-class quota its non-static
    // edges complete within the cap). Classes before it are done; classes
    // after it are pending and will be reached on the next pass.
    if (ctx._classes_in_chunk_visited > 0) {
      _static_field_sweep_cursor =
          chunk_start + ctx._classes_in_chunk_visited - 1;
    } else {
      // Aborted before any class's own edges were seen (e.g. during the
      // holder->class seed edges) - redo the whole chunk.
      _static_field_sweep_cursor = chunk_start;
    }
  } else {
    // Full advance: every class in the chunk was processed.
    _static_field_sweep_cursor = chunk_end;
  }
  if (_static_field_sweep_cursor >= class_count) {
    *cycle_complete = !_static_field_sweep_cycle_truncated;
    _static_field_sweep_cursor = 0;
    _static_field_sweep_cycle_truncated = false;
  }
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
  // Whole-call wall-clock duration of runPassManualWalk() below - includes
  // root/stack-ref enumeration dispatch, frontier-table bookkeeping, and
  // rotation-candidate collection, in addition to the actual in-safepoint
  // JVMTI calls. Used only to derive non_safepoint_ticks below for
  // _cpu_pain_budget; NOT fed to updatePacing()/_pause_pid directly (see
  // safepoint_ticks below for that). Measured via TSC::ticks() rather than
  // OS::nanotime(), matching this codebase's other interval-timing call
  // sites (LivenessTracker::track(), pollWatchedTargets() below);
  // TSC::ticks() itself falls back to OS::nanotime() when the TSC is
  // unavailable/disabled, so this is a strict upgrade with no behavior
  // change on hosts without a usable timestamp counter.
  u64 pass_wall_ticks = 0;
  // Genuine in-safepoint cost of this pass, accumulated by
  // runPassManualWalk() across every IterateOverReachableObjects/
  // FollowReferences call it makes (root enum, static-field sweep, ordinary
  // expansion, rotation re-expansion) - explicitly excluding
  // GetObjectsWithTags (not a safepoint call) and every bookkeeping line in
  // between. This, not pass_wall_ticks, is what updatePacing()/
  // maybeRevokeBorrowForRootEnumPass() below actually regulate: JFR
  // (jdk.ExecuteVMOperation[operation=HeapWalkOperation]) confirmed the two
  // can differ substantially - a pass's non-safepoint bookkeeping must not
  // be mistaken for pause-time-SLO pressure and throttle the PID controller
  // on its behalf.
  u64 safepoint_ticks = 0;

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

  int frontier_size_before_pass = _frontier != nullptr ? _frontier->size() : 0;

  u64 call_start_ticks = TSC::ticks();
  runPassManualWalk(jvmti, jni, run_root_enum, _first_pass_budget,
                     _effective_budget, &edges_admitted, &truncated,
                     &frontier_cap_hit, &safepoint_ticks);
  pass_wall_ticks = TSC::ticks() - call_start_ticks;
  // TSC::ticks() is monotonic but not necessarily free of measurement noise
  // between the outer call_start_ticks snapshot and the several inner
  // TSC::ticks() snapshots safepoint_ticks is built from - clamp rather than
  // underflow if the accumulated safepoint portion ever reads back larger
  // than the whole-call wall time it's a subset of.
  u64 non_safepoint_ticks =
      pass_wall_ticks > safepoint_ticks ? pass_wall_ticks - safepoint_ticks : 0;
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
    updatePacing(safepoint_ticks);
  } else {
    // Excluded from the budget/cadence controller above, but not from the
    // borrow ceiling's revocation check (see maybeRevokeBorrowForRootEnumPass()'s
    // own comment) - a root-enum pass's in-safepoint cost is real pause time
    // and must still be able to revoke a borrowed-budget grant the pacing
    // controller would otherwise keep believing is safe.
    maybeRevokeBorrowForRootEnumPass(safepoint_ticks);
  }
  // Search restart (this class's own header comment): accumulate this
  // pass's own in-safepoint cost toward the running total restartSearch()
  // will spend into _safepoint_pain_budget once the search reaches a terminal state -
  // same TSC::ticks_to_millis() conversion updatePacing() already uses for
  // its own pass-duration signal.
  _search_pain_ms += TSC::ticks_to_millis(safepoint_ticks);
  // Independent leaky bucket for the non-safepoint remainder of this pass
  // (root/stack-ref enumeration dispatch, frontier-table admission,
  // rotation-candidate collection) - see _cpu_pain_budget's own comment
  // (referenceChains.h) for why this needs to be tracked separately from
  // both _safepoint_pain_budget above and _pause_pid's safepoint_ticks signal.
  // Spent every pass, root-enum or not: none of this cost is
  // cadence-gated the way root enum's in-safepoint dispatch is.
  _cpu_pain_budget.spend(TSC::ticks_to_millis(non_safepoint_ticks));

  // Design doc's Termination section, decided in priority order:
  //   1. Frontier-size cap hit -> abandon immediately, regardless of TTL.
  //   2. No pending frontier entries left (this pass wasn't truncated) AND no
  //      active leak-accumulation watch -> the reachable graph was fully
  //      explored within the hop cap with nothing left to keep re-checking;
  //      natural completion (the hop cap alone is a normal boundary, not
  //      truncation - see heapReferenceCallback()'s own comment). See the
  //      _watched_leak_klass_count clause's own comment below for why an
  //      active watch withholds completion here even with an empty pending
  //      queue.
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
  int frontier_size_after = _frontier->size();
  if (frontier_cap_hit) {
    // Frontier table is full -- no new entries can ever be admitted, so
    // frontier_size_after can never exceed frontier_size_before_pass again.
    // Deferring to the no-progress detector below (as a prior version of
    // this branch did) would never actually reach it: this same `if` would
    // keep matching every subsequent pass, permanently short-circuiting the
    // else-if chain before _passes_since_last_progress is ever read. Abandon
    // immediately instead, matching this function's own design-doc priority
    // list above (frontier-size cap hit abandons regardless of TTL).
    store(_abandon_reason, (u8)SearchAbandonReason::FRONTIER_CAP);
    storeRelease(_search_state, (u8)SearchState::ABANDONED);
    enqueuePendingAbandonedEvent();
    TEST_LOG("ReferenceChainTracker::runPass frontier cap hit -- "
             "abandoning search (size=%d)",
             frontier_size_after);
  } else if (!has_pending_frontier && _watched_leak_klass_count == 0) {
    storeRelease(_search_state, (u8)SearchState::COMPLETED);
  } else if (!has_pending_frontier) {
    // Reachable graph fully explored, but LivenessTracker still has at least
    // one klass under active leak watch (_watched_leak_klass_count's own
    // comment) - do NOT complete. Rotation (collectLeakAccumulationCandidates
    // ForRotation() et al., runPassManualWalk()'s own comment) exists
    // precisely to re-observe already-EXPANDED entries whose fields mutate
    // after their one-time expansion - e.g. an element appended to a
    // static-field-rooted collection well after the walk first visited it.
    // Once every reachable object has been visited once, has_pending_frontier
    // goes permanently false and runPass()'s terminal-state branch would
    // otherwise make every future call to this method a no-op forever
    // (search_state != RUNNING short-circuits before rotation ever runs
    // again) - silently disabling the one mechanism built to catch that
    // exact mutation. Falling through here leaves _search_state at RUNNING,
    // so the next pass (still gated by shouldRunPass()'s normal cadence/pain
    // budget) runs the rotation collectors again with a fresh view of
    // whatever object identities LivenessTracker is currently watching.
    // _passes_since_last_progress below still counts this pass as "no
    // progress" (frontier size is genuinely unchanged), so a watch that
    // never resolves anything still bounds out via the TTL/no-progress
    // branch below once isUrgent() clears - this only keeps a search alive
    // while there is an active signal to keep probing for, not forever
    // unconditionally.
  } else if (_passes_since_last_progress >= NO_PROGRESS_PASS_LIMIT &&
             !isUrgent()) {
    // The frontier hasn't grown for NO_PROGRESS_PASS_LIMIT consecutive
    // passes — the search is genuinely stuck (not just slow), so
    // abandon. A large heap takes more passes simply because
    // there are more objects to explore; that is not "stuck".
    // Only abandon when the frontier stops growing entirely.
    // Suppressed when urgent (secondsToOOM() < OOM_URGENT_THRESHOLD_S):
    // the search must complete to find the leak before the app OOMs.
    store(_abandon_reason, (u8)SearchAbandonReason::TTL);
    storeRelease(_search_state, (u8)SearchState::ABANDONED);
    enqueuePendingAbandonedEvent();
  } else if (_candidate_count > 0 &&
             __builtin_popcountll(_candidate_found_bits) ==
                 (u64)_candidate_count) {
    // Canary early termination: all leaked candidates have been
    // found -- the search is complete.
    storeRelease(_search_state, (u8)SearchState::COMPLETED);
    Counters::increment(REFERENCE_CHAIN_CANDIDATES_FOUND,
                             __builtin_popcountll(_candidate_found_bits));
  } else if (_candidate_count > 0 &&
             _passes_since_last_progress >= NO_PROGRESS_PASS_LIMIT &&
             _passes_since_last_candidate_progress >=
                 canaryStuckPassLimit()) {
    // Canary-specific stuck detector - deliberately NOT suppressed by
    // isUrgent() (contrast the ordinary TTL check above). The ordinary
    // check's !isUrgent() guard protects a search that's still making real
    // (whole-graph) progress from being killed just because the process is
    // close to OOM; but _passes_since_last_candidate_progress only advances
    // when NO candidate has been newly found and NO new candidate has been
    // admitted, which frontier growth elsewhere in the graph does not
    // affect. A canary that has made zero discovery progress for this many
    // passes is provably not converging regardless of urgency, so letting
    // isUrgent() keep it RUNNING would only burn urgency-boosted STW pause
    // budget during the same OOM approach this search exists to diagnose.
    //
    // Also requires the whole-graph frontier to have stalled
    // (_passes_since_last_progress >= NO_PROGRESS_PASS_LIMIT): a search
    // whose frontier is still growing is making real progress toward
    // eventually reaching the candidate even if it hasn't yet, so it is
    // not "stuck" in the sense this detector exists to catch - see
    // canaryStuckPassLimit()'s own comment for why the pass limit itself
    // also escalates across consecutive restarts of the same chase.
    store(_abandon_reason, (u8)SearchAbandonReason::CANARY_STUCK);
    storeRelease(_search_state, (u8)SearchState::ABANDONED);
    enqueuePendingAbandonedEvent();
    if (_canary_stuck_restart_count < MAX_CANARY_STUCK_BACKOFF_SHIFT) {
      _canary_stuck_restart_count++;
    }
  }

  // Track progress: if the frontier grew this pass, reset the no-progress
  // counter. Otherwise increment it.
  if (frontier_size_after > frontier_size_before_pass) {
    _passes_since_last_progress = 0;
  } else {
    _passes_since_last_progress++;
  }

  // Track canary-specific progress separately - see
  // _passes_since_last_candidate_progress's own comment for why frontier
  // growth above does not substitute for this.
  int candidate_progress_mark =
      _candidate_count + (int)__builtin_popcountll(_candidate_found_bits);
  if (candidate_progress_mark > _last_candidate_progress_mark) {
    _last_candidate_progress_mark = candidate_progress_mark;
    _passes_since_last_candidate_progress = 0;
  } else {
    _passes_since_last_candidate_progress++;
  }

  if (load(_search_state) != SearchState::RUNNING) {
    _tags_released = releaseSearchTags(jvmti, jni);
    // Release canary marker tags: use GetObjectsWithTags
    // to find all live marker-tagged objects and clear
    // them. DeleteLocalRef each object before
    // Deallocate-ing the array (matches the
    // existing pattern at referenceChains.cpp:2125-2133).
    if (_candidate_count > 0) {
      for (int i = 0; i < _candidate_count; i++) {
        jlong tag = _candidate_tags[i];
        jint count = 0;
        jobject *objects = nullptr;
        jlong *result_tags = nullptr;
        jvmtiError cerr = jvmti->GetObjectsWithTags(
            1, &tag, &count, &objects, &result_tags);
        if (cerr == JVMTI_ERROR_NONE && count > 0) {
          for (jint j = 0; j < count; j++) {
            jvmti->SetTag(objects[j], 0);
            jni->DeleteLocalRef(objects[j]);
          }
          jvmti->Deallocate((unsigned char *)objects);
          jvmti->Deallocate((unsigned char *)result_tags);
        }
      }
      _candidate_count = 0;
      _candidate_found_bits = 0;
      memset(_candidate_discovered_count, 0, sizeof(_candidate_discovered_count));
      _passes_since_last_candidate_progress = 0;
    }
    // Only CANARY_STUCK should keep escalating canaryStuckPassLimit() -
    // any other terminal reason (natural completion, all candidates found,
    // frontier cap, TTL) is an unrelated outcome for this chase sequence,
    // so a fresh restart afterward should start back at the base limit.
    if (load(_abandon_reason) != SearchAbandonReason::CANARY_STUCK) {
      _canary_stuck_restart_count = 0;
    }
  }

  if (out_truncated != nullptr) {
    *out_truncated = truncated;
  }

  TEST_LOG("ReferenceChainTracker::runPass done: err=%d edges_admitted=%d truncated=%d "
           "frontier_cap_hit=%d searchState=%d abandonReason=%d frontierSize=%d "
           "effectiveBudget=%d effectiveCadenceNs=%llu pendingExpand=%zu priorityExpand=%zu "
           "candidateFound=%d/%d discoveredCounts=[%d,%d,%d,%d,%d]",
           (int)err, edges_admitted, truncated, frontier_cap_hit, (int)load(_search_state),
           (int)_abandon_reason, _frontier->size(), _effective_budget,
           (unsigned long long)_effective_cadence_ns,
           _pending_expand.size(), _priority_expand.size(),
           (int)__builtin_popcountll(_candidate_found_bits), _candidate_count,
           _candidate_count > 0 ? _candidate_discovered_count[0] : 0,
           _candidate_count > 1 ? _candidate_discovered_count[1] : 0,
           _candidate_count > 2 ? _candidate_discovered_count[2] : 0,
           _candidate_count > 3 ? _candidate_discovered_count[3] : 0,
           _candidate_count > 4 ? _candidate_discovered_count[4] : 0);

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
      _effective_pause_target_ms > 0 &&
      (double)pass_ms <= (double)_effective_pause_target_ms * BORROW_UNDER_TARGET_FRACTION;
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
  if (_effective_pause_target_ms <= 0) {
    return;
  }
  u64 pass_ms = TSC::ticks_to_millis(pass_wall_ticks);
  bool comfortably_under_target =
      (double)pass_ms <= (double)_effective_pause_target_ms * BORROW_UNDER_TARGET_FRACTION;
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

void ReferenceChainTracker::requeueChainRootForRotation(jlong tag) {
  if (_frontier == nullptr || tag <= 0) {
    return;
  }
  // Walk the parent chain up to the root-attached entry - the same links
  // reconstructChain() walks, but we only need the tag, not the class ids.
  // Bounded by _hop_cap (the frontier's own invariant: depth <= hop_cap),
  // so a corrupt cycle cannot spin here.
  jlong root_tag = tag;
  FrontierEntry entry{};
  int hops = 0;
  while (hops++ < _hop_cap) {
    if (!_frontier->lookup(root_tag, &entry) || entry.parent_tag == 0) {
      break;
    }
    root_tag = entry.parent_tag;
  }
  if (root_tag == tag) {
    return; // tag IS the root - nothing above it to requeue
  }
  if (!_frontier->lookup(root_tag, &entry) ||
      entry.state != FrontierEntryState::EXPANDED) {
    return; // root pruned or still pending expansion - nothing to re-walk
  }
  if (isQueuedForRotation(root_tag) ||
      _priority_expand.size() >= PRIORITY_EXPAND_CAP) {
    return;
  }
  TEST_LOG("ReferenceChainTracker::requeueChainRootForRotation root_tag=%lld "
           "target_tag=%lld",
           (long long)root_tag, (long long)tag);
  _priority_expand.push_back(root_tag);
}

namespace {

// The discovered-chain gate's suppression predicate, shared by EVERY site
// that caches a resolved chain - the poll's discovered-instances loop AND
// both representative build paths (the canary/marker path and the
// normal-tag path). Chains shallower than the first real holder hop
// (depth < 2) rooted at a TRANSIENT root (stack local / JNI local) are the
// observed noise shape - a momentarily-live frame's variable holding the
// instance - whose retention explanation evaporates when the frame dies.
// Everything else is real: a depth==1 chain rooted at a durable root is the
// singleton-collection leak shape (a depth-0 static root's elements are
// depth 1), and a depth==0 chain rooted at a durable root is the
// direct-retention shape (the root-retained object itself - e.g. a static
// field's value, or a Thread object for thread-local leaks) - suppressing
// those unconditionally would drop exactly the retention categories the
// search exists to report. Anything deeper passes regardless of root kind
// (at depth >= 2 the chain has at least one real holder hop).
// Representative-driven builds used to bypass this check entirely (found
// live: the canary path cached a stack-local-rooted depth-1 chain for a
// seeded noise-class representative and snapshot-and-keep re-emitted it
// forever) - every cacheResolvedChain() call site in pollWatchedTargets()
// must pass this gate.
bool suppressChainEvent(const ReferenceChainEvent &event) {
  return event._depth < 2 && isTransientRootKind(event._root_kind);
}

}  // namespace

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
  // Per-instance caching: no per-klass prune needed (see comment below
  // where the prune logic used to be).

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

  // Refresh the faster, un-hysteresis-gated klass_id ranking rotation
  // priority uses (see _watched_leak_klass_ids' own comment) - but only
  // once selectLeakCandidates() above has ALREADY found at least one
  // qualifying candidate via its own slower hysteresis gate: this mechanism
  // is meant to crank once the trend detector has triggered, not to run the
  // ranking independently before that gate has ever fired. Refreshed even
  // when candidate_count's specific candidates are unrelated to whichever
  // klass ends up ranked highest by generation count - the two lists serve
  // different purposes (canary marker output vs. rotation priority) and are
  // deliberately not required to agree.
  if (candidate_count > 0) {
    // Snapshot the OLD watched set before overwriting it, so any klass_id
    // that's newly appearing this refresh can get its one-time retroactive
    // catch-up (seedLeakAccumulationForNewlyWatchedKlass() - see
    // _watched_leak_klass_ids' own comment for why admission-time tracking
    // alone cannot see objects admitted before watching started).
    u32 previously_watched[MAX_WATCHED_LEAK_KLASSES];
    int previously_watched_count = _watched_leak_klass_count;
    for (int i = 0; i < previously_watched_count; i++) {
      previously_watched[i] = _watched_leak_klass_ids[i];
    }
    _watched_leak_klass_count = LivenessTracker::instance()->topKlassesByGenerationCount(
        _watched_leak_klass_ids, MAX_WATCHED_LEAK_KLASSES);
    for (int i = 0; i < _watched_leak_klass_count; i++) {
      u32 klass_id = _watched_leak_klass_ids[i];
      bool already_watched = false;
      for (int j = 0; j < previously_watched_count; j++) {
        if (previously_watched[j] == klass_id) {
          already_watched = true;
          break;
        }
      }
      if (!already_watched) {
        seedLeakAccumulationForNewlyWatchedKlass(klass_id);
      }
    }
  }
  // Only log when there are candidates to act on - this poll runs on every
  // BFS-thread wake (once per second), so logging a zero count is per-second
  // noise for the common idle case.
  if (candidate_count > 0) {
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate_count=%d", candidate_count);
    // Admit any candidate selectLeakCandidates() returns this poll that
    // doesn't already occupy a slot, into the next free slot. This runs on
    // every poll (not gated to "only the first time") because
    // selectLeakCandidates()'s result set can change across polls - a new
    // klass_id can start qualifying well after the search began. Slots are
    // never retired or reassigned once occupied: a klass_id that stops
    // qualifying just keeps whatever slot it has (and can still be found
    // there), it is never freed for reuse by a different klass_id. That
    // keeps the marker tag (MARKER_TAG_BASE - slot) a stable, search-lifetime
    // identity for heapReferenceCallback()'s decode (referenceChains.cpp,
    // near the *tag_ptr <= MARKER_TAG_BASE check) - reusing a slot mid-search
    // would let a live marker tag on one object suddenly decode to a
    // different klass_id's bookkeeping.
    // Use resolveCandidateRepresentative() (re-reads under lock)
    // instead of candidates[i].representative (stale jweak).
    for (int i = 0; i < candidate_count; i++) {
      u32 klass_id = candidates[i].klass_id;
      bool already_tracked = false;
      for (int s = 0; s < _candidate_count; s++) {
        if (_candidate_klass_ids[s] == klass_id) {
          already_tracked = true;
          break;
        }
      }
      if (already_tracked) {
        continue;
      }
      if (_candidate_count >= MAX_LEAK_CANDIDATES_FROM_LT) {
        TEST_LOG("ReferenceChainTracker::pollWatchedTargets canary: klass_id=%u "
                 "qualifies but all %d slots are occupied - not tracked this search",
                 klass_id, MAX_LEAK_CANDIDATES_FROM_LT);
        continue;
      }
      // Tag this candidate's specific representative object with a distinct
      // marker tag (MARKER_TAG_BASE - slot) so heapReferenceCallback() can
      // identify that exact object by identity when the walk reaches it -
      // matching by class alone would record a chain for whichever instance
      // of that class the walk happens to visit, not necessarily the one
      // LivenessTracker flagged as growing.
      int slot = _candidate_count;
      _candidate_klass_ids[slot] = klass_id;
      _candidate_tags[slot] = 0; // no marker tags — using leak tags now
      _candidate_count = slot + 1;
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets canary: admitted klass_id=%u "
               "into slot=%d (candidate_count now %d)",
               klass_id, slot, _candidate_count);
      Counters::increment(REFERENCE_CHAIN_CANDIDATE_COUNT, 1);
    }
    // Tag all tracked instances of all candidate classes with leak tags.
    // This replaces the old single-representative marker-tag approach —
    // the BFS will find these specific leaking objects by tag, not by
    // class match, eliminating noise from unrelated instances of the same
    // class.
    u32 klass_ids[MAX_LEAK_CANDIDATES_FROM_LT];
    for (int s = 0; s < _candidate_count; s++) {
      klass_ids[s] = _candidate_klass_ids[s];
    }
    int tagged = LivenessTracker::instance()->tagLeakInstances(
        jvmti, klass_ids, _candidate_count);
    _leak_tags_assigned = tagged;
    _leak_tags_resolved = 0; // reset on each tagging round
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets tagLeakInstances tagged=%d",
             tagged);
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
    // Per-instance caching: no per-klass prune needed.
    const u32 klass_id = candidates[i].klass_id;
    jobject obj = LivenessTracker::instance()->resolveCandidateRepresentative(
        jni, klass_id);
    if (obj == nullptr) {
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate[%d] klass_id=%u "
               "representative could not be resolved (died/evicted)",
               i, klass_id);
      // The representative died, but the canary chain (if the candidate
      // was pruned by BFS before the representative died) only needs the
      // frontier table — not the live representative. Try to build it
      // before erasing the cached chain and skipping this candidate.
      bool built_from_canary = false;
      for (int s = 0; s < _candidate_count; s++) {
        if (_candidate_klass_ids[s] != klass_id) continue;
        if ((_candidate_found_bits & (1ULL << s)) &&
            _candidate_frontier_tags[s] != 0) {
          jlong canary_ftag = _candidate_frontier_tags[s];
          _resolved_chains_lock.lock();
          bool need = (_resolved_chains.find(canary_ftag) == _resolved_chains.end());
          _resolved_chains_lock.unlock();
          if (need) {
            ReferenceChainEvent event;
            built_from_canary = buildCanaryChainEvent(s, &event);
            TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
                     "buildCanaryChainEvent(dead rep, slot=%d) -> %d",
                     s, (int)built_from_canary);
            if (built_from_canary && suppressChainEvent(event)) {
              TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
                       "filtered depth=%u root_kind=%d canary_ftag=%lld "
                       "klass_id=%u (dead-rep path)",
                       event._depth, (int)event._root_kind,
                       (long long)canary_ftag, klass_id);
              built_from_canary = false;
              invalidateResolvedChain(canary_ftag);
            } else if (built_from_canary) {
              event._start_time = TSC::ticks();
              cacheResolvedChain(canary_ftag, std::move(event),
                                  canary_ftag, current_search_ns);
            }
          }
        }
        break;
      }
      if (!built_from_canary) {
        // The representative died. Per-instance caching means we don't erase
        // by klass_id — chains for other instances of this class may still
        // be valid. The dead representative's chain (if any) will expire
        // when the search restarts and the frontier is wiped.
      }
      continue; // candidate died, or was evicted, since LivenessTracker flagged it
    }

    {
      jclass obj_klass = jni->GetObjectClass(obj);
      char *obj_class_name = nullptr;
      if (obj_klass != nullptr &&
          jvmti->GetClassSignature(obj_klass, &obj_class_name, nullptr) ==
              JVMTI_ERROR_NONE &&
          obj_class_name != nullptr) {
        TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate[%d] "
                 "klass_id=%u class_name=%s",
                 i, klass_id, obj_class_name);
        jvmti->Deallocate((unsigned char *)obj_class_name);
      }
      if (obj_klass != nullptr) {
        jni->DeleteLocalRef(obj_klass);
      }
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

    // Canary search: if this candidate was pre-tagged with a marker tag
    // (negative, set above), use the canary chain reconstruction. The
    // marker tag itself stays on the representative for the whole search
    // (heapReferenceCallback() never overwrites it), so this stays true
    // regardless of whether the walk has actually reached it yet this pass -
    // buildCanaryChainEvent() below is what distinguishes "found" (parent_tag
    // or frontier_tag populated) from "not yet pruned".
    if (tag <= MARKER_TAG_BASE) {
      // The marker tag encodes the slot this object was pre-tagged at
      // (MARKER_TAG_BASE - slot, mirroring heapReferenceCallback()'s own
      // decode at referenceChains.cpp:1510). Decode it from the tag itself
      // rather than reusing the loop index `i`: selectLeakCandidates() is
      // not guaranteed to return candidates in the same order across polls,
      // so `i` can drift from the slot this object was actually tagged at.
      int candidate_slot = (int)(MARKER_TAG_BASE - tag);
      if (candidate_slot < 0 || candidate_slot >= _candidate_count) {
        TEST_LOG("ReferenceChainTracker::pollWatchedTargets canary candidate[%d] "
                 "klass_id=%u marker_tag=%lld decodes to out-of-range slot=%d "
                 "(candidate_count=%d) - skipping",
                 i, klass_id, (long long)tag, candidate_slot, _candidate_count);
        jni->DeleteLocalRef(obj);
        continue;
      }
      bool need_refresh = false;
      jlong canary_ftag = _candidate_frontier_tags[candidate_slot];
      _resolved_chains_lock.lock();
      auto it = _resolved_chains.find(canary_ftag);
      need_refresh = (it == _resolved_chains.end() ||
                      it->second.source_search_ns != current_search_ns);
      _resolved_chains_lock.unlock();
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets canary candidate[%d] "
               "klass_id=%u marker_tag=%lld slot=%d needRefresh=%d",
               i, klass_id, (long long)tag, candidate_slot, need_refresh);
      if (need_refresh) {
        ReferenceChainEvent event;
        bool built = buildCanaryChainEvent(candidate_slot, &event);
        TEST_LOG("ReferenceChainTracker::pollWatchedTargets canary "
                 "buildCanaryChainEvent(slot=%d) -> %d",
                 candidate_slot, built);
        if (built && suppressChainEvent(event)) {
          TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
                   "filtered depth=%u root_kind=%d canary_ftag=%lld "
                   "klass_id=%u (canary path)",
                   event._depth, (int)event._root_kind,
                   (long long)canary_ftag, klass_id);
          built = false;
          invalidateResolvedChain(canary_ftag);
        }
        if (built) {
          event._start_time = TSC::ticks();
          cacheResolvedChain(canary_ftag, std::move(event),
                              canary_ftag, current_search_ns);
        }
      }
      // Fall through to discovered-instances check below — the canary
      // representative may not have been reached by BFS yet, but other
      // instances of the same class may have been admitted and their
      // chains can be built now.
    }

    // Normal (non-canary) path: tag > 0 means the walk visited this
    // object and assigned it a frontier tag.

    // Keep the holder chain's root warm in the rotation queue: a growing
    // container's current internals are only reachable via the holder's
    // re-walk (requeueChainRootForRotation()'s own comment). Every poll,
    // not just on cache refresh - the holder must be re-walked CONTINUOUSLY
    // to observe each resize as it happens.
    if (tag > 0) {
      requeueChainRootForRotation(tag);
    }

    // Reconstruct only when this klass has no current chain cached: either
    // nothing cached yet, or what is cached was built from a different tag or
    // an earlier search generation (see current_search_ns above). A klass
    // that keeps getting flagged, unchanged, across many polls is left alone
    // - its cached chain is already being re-emitted on every dump.
    bool need_refresh = false;
    if (tag > 0) {
      _resolved_chains_lock.lock();
      auto it = _resolved_chains.find(tag);
      need_refresh = (it == _resolved_chains.end() ||
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
      if (built && suppressChainEvent(event)) {
        TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
                 "filtered depth=%u root_kind=%d rep_tag=%lld klass_id=%u "
                 "(representative path)",
                 event._depth, (int)event._root_kind, (long long)tag,
                 klass_id);
        built = false;
        invalidateResolvedChain(tag);
      }
      if (built) {
        // Provisional stamp; drainPendingChainEvents() re-stamps each copy at
        // dump time so the event lands in that chunk's window.
        event._start_time = TSC::ticks();
        cacheResolvedChain(tag, std::move(event), tag, current_search_ns);
      }
    }
    // tag == 0: The representative object has no tag — the BFS walk
    // hasn't reached it yet AND it is not yet leak-tagged. No action here:
    // tagLeakInstances() (earlier in this same poll) tags every tracked
    // instance of candidate classes from the reusable pool, so the next
    // tagLeakInstances round or the next walk pass will pick it up. The
    // old marker-tag re-tag path is gone — marker tags are no longer the
    // candidate discovery mechanism (leak tags are), and re-tagging with
    // a marker tag here would resurrect the dead mechanism on objects the
    // leak-tag pool has not yet reached.

    // Build chain events for auto-marked discovered instances of this class.
    // These are objects the BFS walk admitted whose class matched this
    // candidate slot — each one has a frontier tag and a chain in the
    // frontier table. We build chain events for all of them (up to
    // MAX_DISCOVERED_INSTANCES_PER_CLASS) so the JFR output includes
    // chains for all leaking instances, not just the representative.
    // This runs for BOTH the canary and non-canary paths: the canary
    // representative may not have been reached by BFS yet, but other
    // instances of the same class may have been admitted already.
    //
    // Per-instance caching: each discovered instance gets its own chain
    // entry keyed by its frontier tag. The profiling backend aggregates
    // by class. This ensures the first chain found (which may be noise —
    // a shallow JNI-local instance) does not block chains for deeper,
    // actually-leaking instances.
    for (int s = 0; s < _candidate_count; s++) {
      if (_candidate_klass_ids[s] != klass_id) continue;
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
               "discovered loop: klass_id=%u slot=%d discovered_count=%d",
               klass_id, s, _candidate_discovered_count[s]);
      if (_candidate_discovered_count[s] == 0) {
        TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
                 "no discovered instances for klass_id=%u slot=%d",
                 klass_id, s);
      }
      for (int d = 0; d < _candidate_discovered_count[s]; d++) {
        jlong disc_tag = _candidate_discovered_tags[s][d];
        if (disc_tag == 0) {
          TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
                   "disc_tag=0 at idx=%d for klass_id=%u slot=%d",
                   d, klass_id, s);
          continue;
        }
        // Skip if already cached for this instance
        _resolved_chains_lock.lock();
        bool already_cached = (_resolved_chains.find(disc_tag) != _resolved_chains.end());
        _resolved_chains_lock.unlock();
        if (already_cached) {
          TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
                   "already_cached disc_tag=%lld klass_id=%u slot=%d idx=%d",
                   (long long)disc_tag, klass_id, s, d);
          continue;
        }
        ReferenceChainEvent event;
        bool built = buildChainEvent(disc_tag, &event);
        // Retention-explanation filter. Only applies to discovered
        // instances, not canary. Suppress:
        //   - depth==0: the instance IS the root (chain is just [object],
        //     no holder to explain anything);
        //   - depth==1 rooted at a TRANSIENT root (stack local / JNI
        //     local): the observed noise shape - a momentarily-live
        //     frame's variable holding the instance. The chain explains a
        //     retention that evaporates when the frame dies.
        // Both durable-rooted shapes are REAL direct-retention chains and
        // must NOT be caught by a blanket depth filter: depth==1 rooted at
        // a static field is the singleton-collection leak shape (a depth-0
        // static root's elements are depth 1), and depth==0 rooted at a
        // durable root is the root-retained object itself (a static field's
        // value, a Thread object for thread-local leaks) - the actual
        // retention categories the search exists to report. Anything
        // deeper passes regardless of root kind (at depth >= 2 the chain
        // has at least one real holder hop).
        if (built && suppressChainEvent(event)) {
          TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
                   "filtered depth=%u root_kind=%d disc_tag=%lld klass_id=%u",
                   event._depth, (int)event._root_kind,
                   (long long)disc_tag, klass_id);
          built = false;
          // Also drop any chain cached for this tag before the filter
          // existed (or before an improveChain/reparent upgraded it) -
          // drainPendingChainEvents() re-emits cached chains
          // unconditionally, so suppressing only the build would leave the
          // noise chains re-emitting forever.
          invalidateResolvedChain(disc_tag);
        }
        if (built) {
          event._start_time = TSC::ticks();
          cacheResolvedChain(disc_tag, std::move(event), disc_tag,
                              current_search_ns);
          // Track coverage for adaptive CPU budget
          if (event._target_tag >= (u64)LEAK_TAG_BASE) {
            _leak_tags_resolved++;
          }
          TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
                   "auto-marked chain for klass_id=%u tag=%lld target_tag=%llu",
                   klass_id, (long long)disc_tag,
                   (unsigned long long)event._target_tag);
        } else {
          TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
                   "buildChainEvent failed for discovered tag=%lld "
                   "klass_id=%u slot=%d disc_idx=%d",
                   (long long)disc_tag, klass_id, s, d);
        }
      }
      break;
    }

    jni->DeleteLocalRef(obj);
  }

  // Per-instance caching: chains are keyed by frontier tag, not klass_id.
  // There is no per-klass prune — chains for dead instances are harmless
  // (they describe a reference path that was valid at resolution time) and
  // expire naturally when the search restarts (frontier is wiped, all tags
  // become invalid, _resolved_chains is cleared in restartSearch()).
  // The backend can filter stale chains by cross-referencing with
  // HeapLiveObject events from the same chunk.
}

// Inserts or refreshes klass_id's resolved chain - see _resolved_chains'
// comment (referenceChains.h) for why a resolved chain is cached and
// re-emitted rather than emitted once. A refresh (klass_id already present)
// always succeeds; only a brand-new klass_id arriving with the cache already
// full is dropped (counted, not silent), rather than evicting some other
// still-live sample's chain. Split out of pollWatchedTargets() so
// ResolvedChainCacheTest (referenceChains_ut.cpp) can drive the overflow path
// directly, without standing up hundreds of real LivenessTracker candidates.
void ReferenceChainTracker::cacheResolvedChain(jlong source_tag,
                                               ReferenceChainEvent &&event,
                                               jlong source_tag_val,
                                               u64 source_search_ns) {
  _resolved_chains_lock.lock();
  auto it = _resolved_chains.find(source_tag);
  if (it == _resolved_chains.end() &&
      (int)_resolved_chains.size() >= MAX_RESOLVED_CHAINS) {
    _resolved_chains_lock.unlock();
    Counters::increment(REFERENCE_CHAIN_EVENTS_DROPPED);
    TEST_LOG("ReferenceChainTracker::cacheResolvedChain dropped new source_tag=%lld, "
             "cache full (at MAX_RESOLVED_CHAINS=%d)",
             (long long)source_tag, MAX_RESOLVED_CHAINS);
    return;
  }
  CachedChain &slot = _resolved_chains[source_tag];
  slot.event = std::move(event);
  slot.source_tag = source_tag_val;
  slot.source_search_ns = source_search_ns;
  TEST_LOG("ReferenceChainTracker::cacheResolvedChain source_tag=%lld cache_size=%d",
           (long long)source_tag, (int)_resolved_chains.size());
  _resolved_chains_lock.unlock();
}

void ReferenceChainTracker::invalidateResolvedChain(jlong source_tag) {
  _resolved_chains_lock.lock();
  auto it = _resolved_chains.find(source_tag);
  if (it != _resolved_chains.end()) {
    _resolved_chains.erase(it);
    TEST_LOG("ReferenceChainTracker::invalidateResolvedChain source_tag=%lld",
             (long long)source_tag);
  }
  _resolved_chains_lock.unlock();
}

void ReferenceChainTracker::recordDiscoveredInstance(u32 klass_id,
                                                     jlong frontier_tag,
                                                     bool leak_correlated) {
  // See the declaration's own comment (referenceChains.h) for the
  // noise-eviction rationale. Bounded: at most MAX_DISCOVERED_INSTANCES-
  // PER_CLASS frontier lookups when evicting, zero allocation (slots are
  // fixed arrays).
  for (int s = 0; s < _candidate_count; s++) {
    if (_candidate_klass_ids[s] != klass_id) {
      continue;
    }
    if (_candidate_discovered_count[s] < MAX_DISCOVERED_INSTANCES_PER_CLASS) {
      _candidate_discovered_tags[s][_candidate_discovered_count[s]++] =
          frontier_tag;
      TEST_LOG("ReferenceChainTracker::recordDiscoveredInstance slot=%d "
               "klass_id=%u tag=%lld leak_correlated=%d count=%d",
               s, klass_id, (long long)frontier_tag, (int)leak_correlated,
               _candidate_discovered_count[s]);
      return;
    }
    if (!leak_correlated) {
      return; // full - noise never displaces anything
    }
    // All slots full and this instance is leak-correlated: evict the first
    // slot held by an entry with no leak tag (a noise instance). Also drop
    // the evicted instance's cached chain so it stops re-emitting - the
    // discovered-loop gate below suppresses new noise builds, but a chain
    // cached before that gate keeps draining forever.
    for (int d = 0; d < _candidate_discovered_count[s]; d++) {
      jlong victim = _candidate_discovered_tags[s][d];
      FrontierEntry victim_entry{};
      if (_frontier == nullptr ||
          !_frontier->lookup(victim, &victim_entry) ||
          victim_entry.leak_tag == 0) {
        _candidate_discovered_tags[s][d] = frontier_tag;
        invalidateResolvedChain(victim);
        TEST_LOG("ReferenceChainTracker::recordDiscoveredInstance evicted "
                 "noise slot=%d idx=%d victim_tag=%lld for leak tag=%lld",
                 s, d, (long long)victim, (long long)frontier_tag);
        return;
      }
    }
    TEST_LOG("ReferenceChainTracker::recordDiscoveredInstance all slots "
             "leak-correlated, dropping tag=%lld klass_id=%u",
             (long long)frontier_tag, klass_id);
    return;
  }
}

bool ReferenceChainTracker::correlateAdmittedLeakTag(jlong frontier_tag,
                                                      jlong leak_tag,
                                                      u32 klass_id) {
  // See the declaration's own comment (referenceChains.h). Called from
  // LivenessTracker::tagLeakInstances() on this same thread
  // (pollWatchedTargets -> tagLeakInstances), so _candidate_* slot access
  // here never races heapReferenceCallback's auto-mark path.
  if (_frontier == nullptr) {
    return false;
  }
  FrontierEntry entry{};
  if (!_frontier->lookup(frontier_tag, &entry)) {
    return false; // not a live frontier tag (or the search restarted)
  }
  if (entry.leak_tag != 0) {
    // Already correlated (idempotent) - e.g. a second tagLeakInstances
    // round after a post-restart re-admission.
    return true;
  }
  _frontier->setLeakTag(frontier_tag, leak_tag);
  TEST_LOG("ReferenceChainTracker::correlateAdmittedLeakTag "
           "frontier_tag=%lld leak_tag=%lld depth=%u parent_tag=%lld",
           (long long)frontier_tag, (long long)leak_tag, entry.depth,
           (long long)entry.parent_tag);
  recordDiscoveredInstance(klass_id, frontier_tag, true);
  return true;
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

void ReferenceChainTracker::enqueuePendingAbandonedEvent() {
  // Called right after runPass() (referenceChains.cpp) writes
  // SearchState::ABANDONED, on the same thread, before shouldRunPass() gets
  // a chance to call restartSearch() - so buildAbandonedEvent()'s live read
  // of _search_state/_abandon_reason/etc. is guaranteed to still succeed
  // here even though it cannot be trusted to succeed later, from dump()'s
  // independent clock (see _pending_abandoned_events' own comment).
  ReferenceChainAbandonedEvent event;
  if (!buildAbandonedEvent(&event)) {
    return;
  }
  _pending_abandoned_events_lock.lock();
  if ((int)_pending_abandoned_events.size() >= MAX_PENDING_ABANDONED_EVENTS) {
    _pending_abandoned_events_lock.unlock();
    Counters::increment(REFERENCE_CHAIN_EVENTS_DROPPED);
    TEST_LOG("ReferenceChainTracker::enqueuePendingAbandonedEvent dropped, "
             "queue full (at MAX_PENDING_ABANDONED_EVENTS=%d)",
             MAX_PENDING_ABANDONED_EVENTS);
    return;
  }
  _pending_abandoned_events.push_back(event);
  TEST_LOG("ReferenceChainTracker::enqueuePendingAbandonedEvent reason=%d "
           "queue_size=%d",
           (int)event._reason, (int)_pending_abandoned_events.size());
  _pending_abandoned_events_lock.unlock();
}

void ReferenceChainTracker::drainPendingAbandonedEvents(
    std::vector<ReferenceChainAbandonedEvent> *out) {
  if (out == nullptr) {
    return;
  }
  // True drain, unlike drainPendingChainEvents() above: each queued event
  // describes a discrete past occurrence, not an ongoing live sample, so
  // once Profiler::dump() (profiler.cpp) has emitted it there is nothing
  // left to re-report on the next dump.
  _pending_abandoned_events_lock.lock();
  out->insert(out->end(), _pending_abandoned_events.begin(),
              _pending_abandoned_events.end());
  _pending_abandoned_events.clear();
  _pending_abandoned_events_lock.unlock();
  TEST_LOG("ReferenceChainTracker::drainPendingAbandonedEvents drained=%d",
           (int)out->size());
}
