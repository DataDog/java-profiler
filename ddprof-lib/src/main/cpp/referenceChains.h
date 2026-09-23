/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _REFERENCECHAINS_H
#define _REFERENCECHAINS_H

#include "arch.h"
#include "arguments.h"
#include "classTagAllocator.h"
#include "common.h"
#include "event.h"
#include "painBudget.h"
#include "pidController.h"
#include "spinLock.h"
#include "mutex.h"
#include <algorithm>
#include <atomic>
#include <climits>
#include <cstring>
#include <deque>
#include <jni.h>
#include <jvmti.h>
#include <pthread.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Incremental reference-chain search: discovers heap objects during JVMTI
// heap walks, tracks them in a tag-indexed FrontierTable, and reconstructs
// the retention chain from a leak candidate back to a GC root, emitting
// datadog.ReferenceChain JFR events. A single agent-owned BFS thread
// (threadLoop()/runPass()) alternates root enumeration (GC roots + stack refs
// via IterateOverReachableObjects) with resumable frontier expansion
// (expandFrontier(): GetObjectsWithTags resolves live entries - dead ones
// pruned for free - then FollowReferences per object); passes run on
// GC-finish epochs or a cadence (shouldRunPass()), and a terminal search
// restarts when a leak candidate exists and canAffordNewSearch()'s PainBudget
// allows it (restartSearch()).
//
// Invariants: GC callbacks fire at a safepoint where only Memory-Management-
// category JVMTI calls are legal, so onGCStart/onGCFinish only bump epoch
// counters; frontier tags are sequential from 1 and never reused, class tags
// always negative (ClassTagAllocator); heap callbacks only call callback-safe
// JVMTI functions, so class names resolve up front and callback-observed
// values are captured at admission (a callback cannot be replayed); terminal
// search state is snapshotted before restartSearch() reuses those live
// fields.
namespace FrontierEntryState {
constexpr u8 FRONTIER = 0;  // discovered, not yet expanded by FollowReferences
constexpr u8 EXPANDED = 1;  // expanded; children (if any) are in the table
constexpr u8 EDGE = 2;      // on a path toward a target sample (EdgeStore)
constexpr u8 ABANDONED = 3; // tag released; entry kept only to avoid reuse
} // namespace FrontierEntryState

// Search-level outcome, distinct from a single pass's truncation: a pass
// can exhaust its budget while the search stays RUNNING.
namespace SearchState {
constexpr u8 RUNNING = 0;   // at least one more pass may still make progress
constexpr u8 COMPLETED = 1; // reachable graph fully explored within caps
constexpr u8 ABANDONED = 2; // TTL or frontier-size cap forced an incomplete stop
} // namespace SearchState

// Which cutoff moved the search out of RUNNING, so abandonReason() can
// report why. Values match Recording::recordReferenceChainAbandoned()'s
// kReasons table (flightRecorder.cpp) index-for-index.
namespace SearchAbandonReason {
constexpr u8 NONE = 0;         // not (yet) abandoned
constexpr u8 FRONTIER_CAP = 1; // frontier-size cap hit
constexpr u8 TTL = 2;          // wall-clock TTL exceeded with work still pending
constexpr u8 CANARY_STUCK = 3;
} // namespace SearchAbandonReason

// Frontier metadata record. Deliberately holds no jclass/jobject: retaining
// either would defeat the point of non-retaining JVMTI tags for identity.
typedef struct FrontierEntry {
  jlong parent_tag;    // links back to the record that discovered this one
  u32 referrer_klass;  // StringDictionary id, 0 = unresolved/none
  u32 depth;           // hop count from the frontier's seed, for the hop cap
  u8 state;            // one of FrontierEntryState's constants
  // Leak tag assigned by LivenessTracker, copied at admission time. 0 =
  // ordinary admission. Non-zero: the correlation key joining
  // ReferenceChain.targetTag and HeapLiveObject.leakTag.
  jlong leak_tag;
  // jvmtiHeapReferenceKind of the admitting edge, only meaningful when
  // parent_tag == 0 (root-attached): callers label the root, not every hop.
  u8 root_kind;
  // Raw JVMTI class tag of THIS entry's object, from the shared allocator
  // (classTagAllocator.h) - NOT referrer_klass, whose dictionary namespace can be reset.
  jlong class_tag;

  // For a FIELD/STATIC_FIELD admitting edge: the JVMTI field ordinal of that field in the
  // REFERRER's flattened field space (jvmtiHeapReferenceInfoField semantics - spans the full
  // hierarchy; decode via resolveHopEdgeLabel()). -1 = not a field edge.
  jint referrer_field_index;

  // jvmtiHeapReferenceKind of the admitting edge for an interior hop
  // (parent_tag != 0). Root-attached entries use root_kind. 0 = not recorded.
  u8 edge_kind;

  // Referrer's class tag when the referrer is a CLASS OBJECT (root-attached static-field
  // admission; parent_tag == 0, so no parent entry to read a class from).
  jlong referrer_class_tag;
} FrontierEntry;

// Per-hop retention-edge identity collected by reconstructChain(): edges[i]
// describes the edge INTO chain[i], so each hop can be labeled with the
// field it is retained through.
typedef struct ChainHopEdge {
  // FrontierEntry::referrer_field_index/edge_kind of the entry for chain[i]
  jint field_index; // -1 = not a field/static-field edge
  u8 edge_kind;      // admitting edge kind (root hops: root_kind)
  // Referrer's raw class tag: the parent entry's class_tag for interior
  // hops, referrer_class_tag for root-attached hops. 0 = unknown.
  jlong referrer_class_tag;
} ChainHopEdge;

// Durability ranking for FrontierEntry::root_kind: higher is more durable.
inline int rootKindDurability(u8 root_kind) {
  switch (root_kind) {
  case JVMTI_HEAP_REFERENCE_STATIC_FIELD:
  case JVMTI_HEAP_REFERENCE_SYSTEM_CLASS:
    return 3;
  case JVMTI_HEAP_REFERENCE_JNI_GLOBAL:
    return 2;
  case JVMTI_HEAP_REFERENCE_MONITOR:
  case JVMTI_HEAP_REFERENCE_STACK_LOCAL:
  case JVMTI_HEAP_REFERENCE_JNI_LOCAL:
  case JVMTI_HEAP_REFERENCE_THREAD:
  case JVMTI_HEAP_REFERENCE_OTHER:
    return 1;
  default:
    return 0; // root_kind's own "not set"/non-root-attached value
  }
}

// Stack-local/JNI-local references are only alive while their owning frame/handle scope is on
// some thread's stack, so entries admitted through these roots are candidates for durability
// upgrades, softer output labels, and bounded re-expansion.
inline bool isTransientRootKind(u8 root_kind) {
  return root_kind == JVMTI_HEAP_REFERENCE_STACK_LOCAL ||
         root_kind == JVMTI_HEAP_REFERENCE_JNI_LOCAL;
}

// Tag-indexed slot table of FrontierEntry records. Slot index = tag - 1; safe because
// nextTag() hands out sequential tags from 1 and never reuses one.
class alignas(alignof(SpinLock)) FrontierTable {
private:
  // Provisional starting size, not benchmark-derived.
  static constexpr int INITIAL_TABLE_CAPACITY = 1024;

  // mutable: const accessors below still take this lock.
  mutable SpinLock _table_lock;
  // 1 + highest index ever inserted; never shrinks (tags/slots are never reused). atomic, not
  // volatile: insert() updates it via CAS concurrently with plain reads, and volatile mixed
  // with a CAS has no synchronizes-with edge (a data race).
  std::atomic<int> _table_size;
  int _table_cap;
  int _table_max_cap;
  FrontierEntry *_table;

  // Grows _table (doubling) up to _table_max_cap. Must hold _table_lock
  // exclusively; returns false without resizing if required_cap exceeds it.
  bool growLocked(int required_cap);

public:
  // max_cap <= 0 disables the table (insert() reports exhaustion) - a
  // misconfigured cap fails safe rather than crashing.
  explicit FrontierTable(int max_cap);
  ~FrontierTable();

  FrontierTable(const FrontierTable &) = delete;
  FrontierTable &operator=(const FrontierTable &) = delete;

  // Writes the slot for `tag` (index = tag - 1), growing the table if needed.
  bool insert(jlong tag, jlong parent_tag, u32 referrer_klass, u32 depth,
              u8 state = FrontierEntryState::FRONTIER, u8 root_kind = 0,
              jlong class_tag = 0,
              jint referrer_field_index = -1, u8 edge_kind = 0,
              jlong referrer_class_tag = 0);

  // Reads the slot for `tag` into *out. Returns false (leaving *out
  // untouched) if `tag` is not positive or has never been inserted.
  bool lookup(jlong tag, FrontierEntry *out);

  // Runs fn(this) under ONE shared-lock acquisition, for callers that
  // look up many tags back to back. RAII releases the lock on every exit
  // path. fn must only call lookupLocked().
  template <typename Fn> void withSharedLock(Fn &&fn) const {
    SharedLockGuard guard(&_table_lock);
    fn(this);
  }

  // Same as lookup() above, but assumes the caller already holds the shared
  // lock via withSharedLock() below.
  bool lookupLocked(jlong tag, FrontierEntry *out) const;

  // Marks the slot ABANDONED in place; no-op if never inserted. Only the
  // metadata side of tag release - the caller still owes SetTag(obj, 0)
  // via clearTag().
  void clear(jlong tag);

  // Marks the slot EDGE in place (on a reconstructed chain's path). No-op
  // if never inserted.
  void markEdge(jlong tag);

  // Marks the slot EXPANDED in place (its outgoing edges were visited).
  void markExpanded(jlong tag);

  // Overwrites only the slot's root_kind; no-op if never inserted. Sole
  // caller: maybeUpgradeRootAttachedRootKind(), which refuses entries with
  // parent_tag != 0 - a root_kind on a non-root-attached entry would be dead
  // data nothing else reads.
  void updateRootKind(jlong tag, u8 root_kind);

  // Set FrontierEntry::leak_tag on the entry for `tag`.
  void setLeakTag(jlong tag, jlong leak_tag) {
    if (tag <= 0 || tag - 1 > (jlong)INT_MAX) {
      return;
    }
    int idx = (int)(tag - 1);
    _table_lock.lock();
    if (idx < _table_size) {
      _table[idx].leak_tag = leak_tag;
    }
    _table_lock.unlock();
  }

  // Replaces a shallow root-attached entry (parent_tag == 0, depth == 0) when the object is
  // later reached via a longer path - otherwise an object first admitted as a JNI-local root
  // keeps a depth-1 "chain with no holder" even once the real static-field path reaches it.
  bool improveChain(jlong tag, jlong parent_tag, u32 referrer_klass,
                     u32 depth, u8 root_kind, jint referrer_field_index = -1,
                     u8 edge_kind = 0, jlong referrer_class_tag = 0);

  // Equal-depth re-parenting, the case improveChain() cannot express: a depth-1 entry whose
  // parent is a TRANSIENT root (stack/JNI local) is re-parented to a DURABLE root-attached
  // parent seen at the same depth - a depth-1 chain's explanation is entirely its root hop.
  bool reparentToDurableRoot(jlong tag, jlong new_parent_tag,
                              u32 referrer_klass,
                              jint referrer_field_index = -1, u8 edge_kind = 0);

  // Walks parent_tag links from `target_tag` back to a root-attached entry, appending each
  // entry's referrer_klass to *out_chain in leaf-to-root order and marking each visited entry
  // EDGE.
  bool reconstructChain(jlong target_tag, std::vector<u32> *out_chain,
                        u8 *out_root_kind = nullptr,
                        std::vector<ChainHopEdge> *out_edges = nullptr,
                        FrontierEntry *out_terminal = nullptr);

  // Marks every slot unoccupied without freeing: a new search's nextTag()
  // sequence restarts at 1. Only call once releaseSearchTags() has
  // confirmed every live JVMTI tag was cleared.
  void resetForRestart() {
    _table_lock.lock();
    _table_size.store(0, std::memory_order_relaxed);
    _table_lock.unlock();
  }

  // Debug-only test seam (resetSearchStateForTest()): discards the whole
  // allocation and rebuilds it at `max_cap` - the only way to undo the
  // "sized once, on the first enabled start()" capacity choice, which
  // would otherwise leave later tests in a shared gtest JVM stuck with it.
  void resetCapacityForTest(int max_cap);

  // resetCapacityForTest() rewrites these under the lock; so do these accessors.
  int capacity() const {
    _table_lock.lock();
    int cap = _table_cap;
    _table_lock.unlock();
    return cap;
  }
  int maxCapacity() const {
    _table_lock.lock();
    int max_cap = _table_max_cap;
    _table_lock.unlock();
    return max_cap;
  }

  // Relaxed: a racing insert() only makes the scan window one tag short.
  int size() const { return _table_size.load(std::memory_order_relaxed); }
};

// Maps a *class* tag (always negative - see nextClassTag()) to the StringDictionary id of the
// class's resolved name (Profiler::classMap()).
class ClassTagTable {
private:
  std::unordered_map<jlong, u32> _table;

public:
  void insert(jlong class_tag, u32 dict_id) { _table[class_tag] = dict_id; }

  // Returns the StringDictionary id for `class_tag`, or 0 if never inserted
  // (composes with the 0 = unresolved convention elsewhere).
  u32 resolve(jlong class_tag) const {
    auto it = _table.find(class_tag);
    return it != _table.end() ? it->second : 0;
  }

  size_t size() const { return _table.size(); }

  // Drops every mapping, e.g. when the StringDictionary was reset.
  void clear() { _table.clear(); }
};

// Singleton shape mirrors LivenessTracker (livenessTracker.h).
class ReferenceChainTracker {
  // Test-only accessor (referenceChains_ut.cpp): instance() is a process-
  // wide singleton, so search-lifecycle fields would otherwise leak across
  // TEST_F cases in one gtest binary.
  friend class ReferenceChainsTestAccessor;

private:
  bool _enabled;

  // Frontier metadata table. Constructed lazily on the first enabled
  // start(); survives stop() so it persists across recording cycles.
  FrontierTable *_frontier;

  // Recorded even once _frontier exists, so resetSearchStateForTest() can rebuild at the configured cap.
  int _configured_frontier_cap;

  // args-configured per-pass budget, recorded at start(). The urgency ramp
  // multiplies the live _budget and restores THIS value when urgency
  // clears - the live _budget may already carry the boost.
  int _configured_budget;

  // Class-tag -> StringDictionary id table, populated by resolveLoadedClasses() and read by
  // heapReferenceCallback().
  ClassTagTable _class_tags;

  // Profiler::classMap()'s generation as of the last resolveLoadedClasses().
  // Profiler::start() calls _class_map.clearAll() (profiler.cpp), restarting
  // the dictionary's id namespace - but a class's JVMTI class tag survives
  // that reset, so the "already tagged -> already resolved" skip would keep
  // stale ids; on a mismatch, every loaded class is re-resolved.
  u64 _last_class_map_generation;

  // GetLoadedClasses() count as of the last resolveLoadedClasses() scan - lets it skip the
  // scan when the count is UNCHANGED (equality, not a "grew" check: the count is not
  // monotonic once class unloading is in play).
  int _last_resolved_class_count;

  // GetLoadedClasses() count as of the last admitStaticFieldRoots() sweep that ran AND
  // completed untruncated (separate from _last_resolved_class_count: the sweep re-walks every
  // loaded class via FollowReferences, a stop-the-world HeapWalkOperation, so it only runs
  // when the loaded-class set actually changed).
  int _last_static_field_class_count;

  // Index into the loaded-class list that admitStaticFieldRoots() resumes from (one
  // un-chunked FollowReferences could never fit a pass's safepoint deadline).
  int _static_field_sweep_cursor;

  // Set when any chunk within the current lap truncates; a lap that
  // truncated must not be marked done, so the next lap retries.
  bool _static_field_sweep_cycle_truncated;

  // Per-call cap on how many classes admitStaticFieldRoots() includes in one FollowReferences
  // call.
  static constexpr int STATIC_FIELD_SWEEP_CHUNK_CLASSES = 512;

  // Per-class cap on non-STATIC_FIELD edges admitted during one
  // admitStaticFieldRoots() lap (STATIC_FIELD edges are always admitted -
  // the high-priority leak root). Bounds outlier classes.
  static constexpr int STATIC_FIELD_SWEEP_NON_STATIC_CAP_PER_CLASS = 32;

  // "GC just happened" signals, bumped only from
  // onGCStart()/onGCFinish(); gcFinishEpoch() feeds shouldRunPass().
  volatile u64 _gc_start_epoch;
  volatile u64 _gc_finish_epoch;

  // Monotonically increasing tag source for frontier objects. 0 is
  // reserved (JVMTI convention: untagged reads 0, SetTag(obj, 0) clears),
  // so this starts at 1. Classes use a disjoint negative range.
  volatile jlong _next_tag;

  // Per-pass tunables, copied from Arguments in start(); one fixed value
  // per start()/stop() cycle.
  int _hop_cap;
  int _budget;

  // Edge budget for the search's one-shot, root-seeded first pass, copied from Arguments
  // (auto-scaled from _budget when unset): a steady-state per-pass budget truncates a
  // cold root-seeded walk long before it reaches anything interesting.
  int _first_pass_budget;

  // Wall-clock TTL from the search's first pass. <= 0 disables the cutoff.
  long _ttl_ms;

  // Pause-time-SLO ceiling; used only to construct _pause_pid in start().
  long _pause_target_ms;
  // Runtime-adjusted pause target: bumped to URGENT_PAUSE_TARGET_MS while
  // isUrgent() holds, restored when urgency clears; _pause_pid is
  // reconstructed whenever this changes.
  long _effective_pause_target_ms;
  // Passes since the frontier last grew; beyond NO_PROGRESS_PASS_LIMIT the search is stuck.
  int _passes_since_last_progress;
  // Passes since the canary candidates last showed progress (a new candidate admitted, or a
  // found-bit set). Distinct from _passes_since_last_progress: whole-graph frontier growth
  // keeps resetting that counter even while the canary's candidates never resolve.
  int _passes_since_last_candidate_progress;
  // candidate_count + popcount(found_bits); monotonic while RUNNING, so an unchanged sum = no canary progress.
  int _last_candidate_progress_mark;

  // Canary-lane pass pacing, work-scaled: the chase's inter-pass spacing is
  // _canary_backoff_mult x _canary_pass_ema_ms - a multiple of what a pass actually COSTS,
  // not a fixed wall-clock constant.
  int _canary_backoff_mult;
  // 0.8/0.2 EMA of each pass's whole-call wall duration in ms, kept warm every pass.
  u64 _canary_pass_ema_ms;
  // End-of-pass timestamp of the last pass with a canary chase open. 0 = no
  // canary pass since the search (re)started.
  u64 _last_canary_pass_ns;
  // Whether threadLoop()'s OOM urgency ramp is active, set each loop iteration BEFORE
  // shouldRunPass() (same thread, no atomics needed).
  bool _oom_ramp_active;

  // Consecutive canary-stuck abandonments of this candidate-chase
  // sequence. Never reset by restartSearch() - it must survive across
  // restarts so canaryStuckPassLimit()'s escalation actually widens.
  int _canary_stuck_restart_count;

  // Canary-search candidate set: each candidate's representative object is pre-tagged with a
  // distinct marker tag (MARKER_TAG_BASE - i) before the walk; matching by class alone would
  // let the walk record a chain for an unrelated, possibly short-lived instance of the same
  // class.
  static constexpr int MAX_LEAK_CANDIDATES_FROM_LT = 5;

  // Matches LivenessTracker::MAX_LEAK_CANDIDATES; duplicated to avoid the include chain.
  static constexpr int MAX_WATCHED_LEAK_KLASSES = 5;
  int _candidate_count;
  u64 _candidate_found_bits;
  // klass_id occupying each slot, so pollWatchedTargets() can tell
  // whether a polled klass_id already has a slot (never re-tagged).
  // Slots are never retired or reused within a search.
  u32 _candidate_klass_ids[MAX_LEAK_CANDIDATES_FROM_LT];
  jlong _candidate_tags[MAX_LEAK_CANDIDATES_FROM_LT];
  jlong _candidate_frontier_tags[MAX_LEAK_CANDIDATES_FROM_LT];
  // Per-candidate chain link recorded at pruning time, so
  // buildCanaryChainEvent() can reconstruct the chain without a frontier
  // lookup on the negative marker tag (which lookup() rejects).
  jlong _candidate_parent_tags[MAX_LEAK_CANDIDATES_FROM_LT];
  u32 _candidate_referrer_klasses[MAX_LEAK_CANDIDATES_FROM_LT];
  u32 _candidate_depths[MAX_LEAK_CANDIDATES_FROM_LT];

  // Per-SLOT snapshot of the qualifying allocating-thread tids selectLeakCandidates()
  // reported this poll (zeroed, then refilled).
  static constexpr int MAX_CANDIDATE_QUALIFYING_TIDS = 16;
  jint _candidate_qualifying_tids[MAX_LEAK_CANDIDATES_FROM_LT]
                                [MAX_CANDIDATE_QUALIFYING_TIDS];
  int _candidate_qualifying_tid_count[MAX_LEAK_CANDIDATES_FROM_LT];

  // tid -> JNI global ref to the live java.lang.Thread object, fed from
  // Profiler::onThreadStart/onThreadEnd.
  Mutex _thread_objects_lock;
  std::unordered_map<jint, jobject> _thread_objects;
  // Global refs of ended threads awaiting deletion.
  std::vector<jobject> _thread_refs_pending_delete;

  // Auto-marked instances: when the walk discovers ANY object whose class matches a watched
  // leak class (not just the pre-tagged representative), its frontier tag is recorded here so
  // pollWatchedTargets() can emit chains for all of them - a leaking class typically has many
  // live instances with different retention paths.
  static constexpr int MAX_DISCOVERED_INSTANCES_PER_CLASS = 8;
  jlong _candidate_discovered_tags[MAX_LEAK_CANDIDATES_FROM_LT]
                                   [MAX_DISCOVERED_INSTANCES_PER_CLASS];
  int _candidate_discovered_count[MAX_LEAK_CANDIDATES_FROM_LT];

  // klass_ids from LivenessTracker::topKlassesByGenerationCount()
  u32 _watched_leak_klass_ids[MAX_WATCHED_LEAK_KLASSES];
  int _watched_leak_klass_count = 0;

  // Packs a (leaf_klass_id, parent_class_id) pair into one map key; both
  // are u32 dictionary ids, so no information is lost.
  static u64 leakSignatureKey(u32 leaf_klass_id, u32 parent_class_id) {
    return ((u64)leaf_klass_id << 32) | (u64)parent_class_id;
  }

  // Leak-accumulation rotation, tier 1: aggregate, per (leaf_klass_id, parent_class_id)
  // signature - not per object - how many admitted children of that leaf klass were observed
  // under a parent of that class.
  std::unordered_map<u64, u32> _leak_signature_totals;

  // Snapshot of _leak_signature_totals as of the END of the previous
  // pass; runPassManualWalk() ranks signatures by delta before rolling
  // this forward. A brand-new signature's delta is its whole total.
  std::unordered_map<u64, u32> _leak_signature_prev_totals;

  // Leak-accumulation rotation, tier 2: per PARENT TAG (not per class), how many admitted
  // children of a watched leaf klass this specific parent holds, plus which signature it
  // belongs to.
  struct LeakParentFanoutEntry {
    u64 signature_key;
    u32 fanout;
  };
  std::unordered_map<jlong, LeakParentFanoutEntry> _leak_parent_fanout;

  // Rotating skip-count over _leak_parent_fanout's iteration order,
  // advanced by the number of parents selected each pass so every fanout
  // parent is re-walked within ceil(fanout_size/budget) passes.
  u64 _leak_parent_rotation_cursor = 0;

  // Pause-time pacing: the actual per-pass budget runPass() passes to
  // FollowReferences/expandFrontier().
  int _effective_budget;

  // Pause-time pacing: the fallback cadence; PASS_CADENCE_NS is its starting value.
  u64 _effective_cadence_ns;

  // Budget borrowing: extra headroom updatePacing() has temporarily granted above _budget's
  // ceiling, earned by a sustained run of comfortably under-target passes (the one exception
  // to "_budget is never exceeded") - a fast-growing frontier can otherwise starve under a
  // steady-state budget and never converge within the TTL.
  int64_t _borrowed_budget;

  // Budget borrowing: consecutive passes comfortably under _pause_target_ms.
  int _consecutive_under_target_passes;

  // Pause-time pacing: this tracker's own PidController. Placeholder-
  // constructed (target=1, unit gains); start() reconstructs it once
  // _pause_target_ms is known, mirroring RateLimiter's pattern.
  PidController _pause_pid;

  // Self-calibrating adaptive batch sizing for GetObjectsWithTags.
  size_t _gotw_batch_size = 0; // 0 = unset, use GOTW_INITIAL_BATCH_SIZE
  u64 _gotw_ema_call_ns = 0;    // EMA of per-call elapsed, 0 = unset

  // Nominal per-call window for the proportional batch control when no
  // phase deadline is set; also a CPU-overhead sanity target.
  static constexpr u64 GOTW_CPU_BUDGET_NS = 25000000; // 25ms

  // Effective window for the proportional batch control, given the remaining pass deadline
  // and the depth of the lane the next call will drain.
  u64 gotwWindowNs(u64 remaining_ns, size_t lane_depth) const {
    u64 window_ns = remaining_ns != 0 ? remaining_ns : GOTW_CPU_BUDGET_NS;
    if (lane_depth >= GOTW_BACKLOG_MIN_DEPTH &&
        _gotw_ema_call_ns > window_ns) {
      window_ns = std::max(window_ns,
                            _gotw_ema_call_ns * GOTW_BACKLOG_WINDOW_MULT);
    }
    return window_ns;
  }

  // Lane depth above which gotwWindowNs()'s backlog widening applies.
  static constexpr size_t GOTW_BACKLOG_MIN_DEPTH = 4096;

  // How many measured per-call floors one widened window may cost.
  static constexpr u64 GOTW_BACKLOG_WINDOW_MULT = 3;

  // Initial batch size before the first measurement: small enough to be
  // safe on any machine, large enough to make meaningful progress.
  static constexpr int GOTW_INITIAL_BATCH_SIZE = 64;
  // Batch bounds.
  static constexpr size_t GOTW_MAX_BATCH = 512;
  static constexpr size_t GOTW_MIN_BATCH = 8;

  // Search lifecycle state. _search_started distinguishes a search's first pass (root-seeded
  // walk) from a resumed pass (expandFrontier()); _search_state only moves forward.
  // Read cross-thread by searchState()/buildAbandonedEvent(), so volatile.
  bool _search_started;
  volatile u8 _search_state;

  // True once releaseSearchTags() has confirmed every live tag this search owned was cleared
  // (a GetObjectsWithTags() failure must NOT count as "released"). shouldRunPass() refuses to
  // restartSearch() while false, so tags/the table are never reset under a search whose tags
  // might still be live.
  bool _tags_released;

  // Whether threadLoop()'s urgency ramp currently holds the multiplied
  // _budget. BFS thread only.
  bool _urgency_budget_boosted;

  // Hysteresis state behind isUrgent(). secondsToOOM() is computed from a short ring of heap
  // deltas, so it swings by orders of magnitude between consecutive observations of the same
  // steadily growing heap; a bare threshold comparison flaps.
  mutable bool _urgent_latched;
  mutable int _urgent_release_ticks;
  mutable bool _urgent_search_spent;

  // Which cutoff moved the search to ABANDONED (see
  // SearchAbandonReason). Cross-thread read like _search_state.
  volatile u8 _abandon_reason;

  // Timestamp of the search's first pass - the TTL baseline. Volatile: read cross-thread by buildAbandonedEvent().
  volatile u64 _search_start_ns;

  // Tags in FrontierEntryState::FRONTIER (pending expansion), in admission order - pushed by
  // heapReferenceCallback() (both walks share that callback), popped by
  // expandFrontier()/markAllFrontierExpanded(). BFS thread only, no locking.
  std::deque<jlong> _pending_expand;

  // Fast-lane counterpart to _pending_expand: entries admitted while re-walking a
  // rotation-selected (already-EXPANDED) parent go here, and expandFrontier() drains this
  // queue ahead of the ordinary one.
  std::deque<jlong> _priority_expand;

  // Which lane the NEXT expandFrontier() batch comes from when both lanes are non-empty.
  bool _expand_lane_prefer_priority = true;

  // Upper bound on _priority_expand: a few passes' worth of rotation selection.
  static constexpr size_t PRIORITY_EXPAND_CAP = 1024;

  // O(1) membership index over _priority_expand, backing isQueuedForRotation(): the rotation
  // collectors run that check for EVERY FrontierTable slot they visit (~199k EXPANDED entries
  // on a large heap), where a linear scan cost up to ~200M comparisons per rotation pass at
  // the cap.
  class PriorityExpandSet {
   private:
    // 2^11 == 2 * PRIORITY_EXPAND_CAP == 2048 slots. The shift below
    // derives from it; keep both in sync.
    static constexpr u64 SLOT_SHIFT = 11;
    static constexpr u64 SLOT_MASK = (1ULL << SLOT_SHIFT) - 1;
    jlong _keys[1ULL << SLOT_SHIFT];
    u8 _used[1ULL << SLOT_SHIFT]; // 0 = empty, 1 = occupied

    static u64 mix(jlong tag) {
      // Fibonacci hashing: spreads near-sequential integer tags evenly
      // across the table's power-of-two slot space.
      return (u64)tag * 0x9E3779B97F4A7C15ULL;
    }

   public:
    bool contains(jlong tag) const {
      u64 i = mix(tag) >> (64 - SLOT_SHIFT);
      while (_used[i]) {
        if (_keys[i] == tag) {
          return true;
        }
        i = (i + 1) & SLOT_MASK;
      }
      return false;
    }

    // Idempotent: returns false if `tag` is already indexed.
    bool insert(jlong tag) {
      u64 i = mix(tag) >> (64 - SLOT_SHIFT);
      while (_used[i]) {
        if (_keys[i] == tag) {
          return false;
        }
        i = (i + 1) & SLOT_MASK;
      }
      _used[i] = 1;
      _keys[i] = tag;
      return true;
    }

    void clear() {
      memset(_used, 0, sizeof(_used));
    }

    // Re-derives the index from the deque's CURRENT contents; call after
    // any pops so membership matches the queue again.
    template <typename Deque> void rebuildFrom(const Deque &queue) {
      clear();
      for (jlong tag : queue) {
        insert(tag);
      }
    }
  } _priority_expand_set;

  // At-risk static-anchor feed: a static holder richly referenced from the running graph is
  // EXCLUDED from the static-anchor tier forever once its frontier entry is chain-attached
  // (maybeUpgradeRootAttachedRootKind() refuses entries with parent_tag != 0, and
  // collectStaticFieldAnchorsForRotation() filters on parent_tag == 0).
  struct AtRiskAnchor {
    jlong tag;
    u32 klass_id;
    // Implicit jlong conversion keeps PriorityExpandSet::rebuildFrom()
    // generic over both the plain-jlong deque and this pair deque.
    operator jlong() const { return tag; }
  };
  std::deque<AtRiskAnchor> _static_anchor_fifo;

  // Membership index over _static_anchor_fifo (push-side dedupe: one
  // lap's repeated static edges onto the same holder push it once).
  // Full-FIFO pushes are dropped - the natural throttle.
  PriorityExpandSet _static_anchor_fifo_set;
  static constexpr size_t STATIC_ANCHOR_FIFO_CAP = PRIORITY_EXPAND_CAP;

  // Per-class occupancy of _static_anchor_fifo, maintained exactly by push/drain/requeue (the
  // klass rides in each AtRiskAnchor), so one class cannot dominate the lane; a class at its
  // quota dropping further pushes is correct - it is already represented.
  std::unordered_map<u32, u32> _static_anchor_fifo_klass_counts;
  static constexpr u32 STATIC_ANCHOR_ATRISK_PER_KLASS_CAP = 64;

  // Index of root-attached STATIC_FIELD/JNI_GLOBAL frontier entries, so
  // collectStaticFieldAnchorsForRotation() iterates O(anchors) instead of
  // scanning the full frontier table. Cleared on restartSearch().
  std::vector<jlong> _static_anchor_index;

  // Parallel to _static_anchor_index: the OWN class tag of each anchor object (the class of
  // the static field's VALUE, not the holder class), so selection can tier anchors by class
  // shape (see AnchorClassShape) without any JVMTI call.
  std::vector<jlong> _static_anchor_own_class_tags;

  // O(1) dedup companion for _static_anchor_index. Cleared with it.
  std::unordered_set<jlong> _static_anchor_index_tags;

  // Shape of a class as an anchor candidate: does it implement java/util/Collection or
  // java/util/Map (directly or via superclasses/interfaces)? A leak holder is typically a
  // container, while the anchor population is dominated by non-containers (String/
  // Class/boxed/primitive-array/enum statics).
  enum class AnchorClassShape : u8 { UNKNOWN = 0, CONTAINER = 1, NON_CONTAINER = 2 };

  // class tag -> AnchorClassShape, process-lifetime (class tags are never reused). Classified once.
  std::unordered_map<jlong, u8> _class_shape_cache;

  // java/util/Collection and java/util/Map class tags, resolved once by
  // resolveContainerInterfaceTags() (0 = not yet resolved; a resolved
  // value is NEGATIVE). Class tags are stable for the JVM's lifetime.
  jlong _collection_iface_class_tag = 0;
  jlong _map_iface_class_tag = 0;

  // Fair-rotation cursors (index POSITIONS, not tags) for the two cursor-fair tiers of
  // collectStaticFieldAnchorsForRotation(): container-shaped anchors, then everything else.
  size_t _anchor_container_cursor = 0;
  size_t _anchor_other_cursor = 0;

  // Fresh-admission lane: FIFO of anchors awaiting their one first-look walk,
  // drained ahead of the fair tiers - admission order = loaded-class order, so
  // a leak holder held by a late-loaded class lands at the fair tiers' lap END
  // and a short search never reaches it. Displaced entries fall back to the
  // fair tiers at their index position (covered, just not urgent).
  std::deque<jlong> _static_anchor_fresh_queue;

  // The queue normally empties every call (the collector drains and
  // DROPS); the cap only guards a pathological burst.
  static constexpr size_t STATIC_ANCHOR_FRESH_CAP = 1024;

  // java/lang/Object jclass cache for the holder-array element type, resolved once via
  // FindClass()+NewGlobalRef(). MUST be a GLOBAL ref: a local ref is freed when its
  // creating JNI invocation returns - caching one across invocations crashed.
  jclass _cached_object_class = nullptr;

  // 1-based tag to resume collectStaleRootKindEntriesForRotation() from, so consecutive calls
  // sweep forward through the table instead of always re-examining the same low-tag entries.
  jlong _root_kind_rotation_cursor;

  // Same role as _root_kind_rotation_cursor, but for
  // collectStaleExpandedEntriesForRotation(): without its own persistent cursor, that sweep
  // restarted from tag 1 every call, and a frontier holding >= STALE_EXPANDED_ROTATION_BUDGET
  // permanently-EXPANDED low-tag entries filled the per-pass cap alone, starving any
  // higher-tag entry (e.g. a static field's collection).
  jlong _stale_expanded_rotation_cursor;

  // Per-pass cap on transient-root_kind entries collectStaleRootKindEntriesForRotation()
  // selects.
  static constexpr int ROOT_KIND_ROTATION_BUDGET = 16;

  // Per-pass cap on EXPANDED entries collectStaleExpandedEntriesForRotation() re-queues,
  // uniformly across the whole table - the low-priority fallback tier (the targeted tier is
  // collectLeakAccumulationCandidatesForRotation()).
  static constexpr int STALE_EXPANDED_ROTATION_BUDGET = 256;

  // Candidate-scoped reach: how many hops BELOW a descend walk's anchor the walk may admit.
  static constexpr int DESCENT_HOPS = 16;

  // Per-pass cap on how many candidate threads walkCandidateThreadLocals() descend-walks.
  static constexpr int THREAD_WALK_MAX_ANCHORS = 4;

  // Per-pass cap on how many root-attached static holders walkStaticFieldAnchors() resolves +
  // descend-walks.
  static constexpr int STATIC_ANCHOR_ROTATION_BUDGET = 32;

  // Per-pass cap on how many DISTINCT anchor classes reconcileAnchorClassShapes() classifies
  // (one GetObjectsWithTags call for the batch + a depth-bounded interface walk per class).
  static constexpr int ANCHOR_SHAPE_RECONCILE_BUDGET = 128;

  // Per-pass cap on how many AT-RISK static holders (parent_tag != 0) drainStaticAnchorFifo()
  // pops for the walkStaticFieldAnchors() batch.
  static constexpr int STATIC_ANCHOR_FIFO_DRAIN = 16;


  // Cursor over the flattened (slot, tid) enumeration of _candidate_qualifying_tids, so THREAD_WALK_MAX_ANCHORS rotates fairly.
  int _thread_walk_anchor_cursor;

  // Per-pass cap on how many EXPANDED entries collectLeakAccumulationCandidatesForRotation()
  // re-queues.
  static constexpr int LEAK_ACCUMULATION_ROTATION_BUDGET = 16;

  // Snapshot of gcFinishEpoch() as of the end of the last pass. Written and
  // read only from the BFS thread, so no locking.
  u64 _last_pass_gc_finish_epoch;

  // End-of-last-pass timestamp; read cross-thread by buildAbandonedEvent(), so volatile like _search_state.
  volatile u64 _last_pass_ns;

  // Total passes run this search; read cross-thread by
  // passesRun()/buildAbandonedEvent(), so volatile like _search_state.
  volatile int _passes_run;

  // Resolved reference chains, keyed by the frontier tag of the instance each was
  // reconstructed for.
  struct CachedChain {
    ReferenceChainEvent event;
    jlong source_tag;
    u64 source_search_ns;
  };
  // Bounded by discovered instances across all slots
  // (5 x 8 = 40, plus up to 5 canary chains); 128 gives headroom.
  static constexpr int MAX_RESOLVED_CHAINS = 128;
  // Keyed by frontier tag (per-instance identity), NOT by klass_id: common classes may have
  // many live instances with different chains - the first chain found may be noise while the
  // real leak is a deep static-field-held instance.
  std::unordered_map<jlong, CachedChain> _resolved_chains;
  SpinLock _resolved_chains_lock;

  // Abandoned-search events awaiting Profiler::dump().
  static constexpr int MAX_PENDING_ABANDONED_EVENTS = 16;
  std::vector<ReferenceChainAbandonedEvent> _pending_abandoned_events;
  SpinLock _pending_abandoned_events_lock;

  // Search-restart gate: leaky bucket over the wall-clock cost of past searches (PainBudget,
  // painBudget.h) - see canAffordNewSearch().
  PainBudget _safepoint_pain_budget;
  // Cached refill rate from start(), reused by resetSearchStateForTest()
  // so a test reset rebuilds the budget with the same rate.
  double _pain_budget_refill_rate = 0.0;
  u64 _search_pain_ms;

  // Non-safepoint CPU-time pain budget, gating shouldRunPass() independently of
  // _safepoint_pain_budget (which only cools down restarts) and _pause_pid's per-pass signal
  // (fed only the genuine in-safepoint portion of each pass).
  PainBudget _cpu_pain_budget;

  // _resolved_chains is mutated on the BFS scheduling thread (pollWatchedTargets()) and read
  // on the dump() thread (drainPendingChainEvents()); _resolved_chains_lock is the only
  // synchronization. The write is deferred to dump()'s thread - it can block ~50ms/event.

  // Fallback cadence for shouldRunPass()'s cadence trigger. Provisional:
  // a round one-second value so an idle search still makes progress
  // between GC-triggered wakeups without burning CPU.
  static constexpr u64 PASS_CADENCE_NS = 1000000000ULL; // 1s

  // Heap-wide time-to-OOM urgency threshold: hasLeakSignal() forces a search to start
  // immediately once LivenessTracker::secondsToOOM() drops under this, rather than waiting
  // for a klass to clear selectLeakCandidates()'s per-klass hysteresis gate - an aggressive,
  // heap-wide leak can OOM the process before any single klass clears that gate.
  static constexpr double OOM_URGENT_THRESHOLD_S = 300.0; // 5 minutes

  // Release side of the urgency hysteresis (see _urgent_latched): secondsToOOM() swings
  // across the threshold in both directions on the same growing heap, so urgency is only
  // released once the projection has stayed clear of this (deliberately higher) bar for
  // URGENT_RELEASE_CONSECUTIVE consecutive observations.
  static constexpr double OOM_URGENT_RELEASE_S = 2 * OOM_URGENT_THRESHOLD_S;
  static constexpr int URGENT_RELEASE_CONSECUTIVE = 5;

  // Horizon over which threadLoop() ramps the pause target and cadence toward their urgent
  // ceilings as secondsToOOM() falls.
  static constexpr double OOM_RAMP_START_S = 1800.0; // 30 minutes

  // Ceilings the pause target and cadence ramp toward as secondsToOOM() approaches zero: the
  // ramp is exponential since the process is likely to die anyway and diagnostic data
  // collected right before that is worth spending STW time and CPU on.
  static constexpr long URGENT_PAUSE_TARGET_MS = 100; // ceiling STW ms per pass
  static constexpr u64 URGENT_CADENCE_NS = 10000000ULL;  // 10ms floor between passes


  // Auto-scaled default for _first_pass_budget when unset (see _first_pass_budget for why
  // plain _budget is the wrong fallback).
  static constexpr int AUTO_FIRST_PASS_BUDGET_MULTIPLIER = 50;
  static constexpr int AUTO_FIRST_PASS_BUDGET_CAP = 200000;

  // Minimum wall-clock gap between root/stack-ref enumeration attempts after the search's
  // first pass.
  static constexpr u64 ROOT_ENUM_MIN_INTERVAL_NS = 2000000000ULL; // 2s

  // Pacing-controller bounds and conversion constants - see updatePacing(). Every value is a
  // round, provisional guess, a future benchmark the intended path to measured values.
  static constexpr int MIN_EFFECTIVE_BUDGET = 2000;

  // Cadence bounds. The lower bound is not 0: threadLoop() sleeps
  // exactly this long each iteration, so a true 0 would busy-loop the
  // BFS thread.
  static constexpr u64 MIN_EFFECTIVE_CADENCE_NS = 10000000ULL;      // 10ms
  static constexpr u64 MAX_EFFECTIVE_CADENCE_NS = PASS_CADENCE_NS * 4; // 4s

  // Conversion from "edges of budget overflow the clamp could not
  // absorb" to a cadence adjustment - different units with no natural
  // exchange rate, so a round provisional choice.
  static constexpr u64 CADENCE_NS_PER_EDGE_OVERFLOW = 1000000ULL; // 1ms/edge

  // Budget borrowing: consecutive comfortably-under-target passes
  // required before updatePacing() starts growing _borrowed_budget.
  // Large enough that a brief lull cannot itself unlock headroom.
  static constexpr int BORROW_WARMUP_PASSES = 5;

  // A pass counts toward BORROW_WARMUP_PASSES only when pass_ms is at most this fraction of
  // _pause_target_ms - deliberately stricter than merely "under the ceiling", so growth is
  // gated on comfortable headroom, not shaving the pass in just under the wire.
  static constexpr double BORROW_UNDER_TARGET_FRACTION = 0.5;

  // Budget borrowing: hard cap on how far (_budget + _borrowed_budget) may exceed _budget alone.
  static constexpr int BORROW_CEILING_MULTIPLIER = 4;

  // Budget borrowing: growth per qualifying pass; a fraction of the configured budget, so growth stays linear.
  static constexpr double BORROW_GROWTH_FRACTION = 0.25;

  // Agent-owned BFS thread; threadLoop() implements the scheduling loop, with a pthread
  // lifecycle mirroring J9WallClock's (j9/j9WallClock.cpp). start()/stop() themselves do NOT
  // create/join this thread - threadLoop()'s VM::attachThread() crashes on a null VM::_vm,
  // and referenceChains_ut.cpp calls start() directly with no live JVM.
  // startThread()/stopThread() own the lifecycle, called from Profiler::start()/stop() once
  // the JVM/JVMTI environment is up.
  pthread_t _thread;
  // std::atomic<bool>, not volatile: volatile gives no acquire/release guarantees, so on a
  // weakly-ordered CPU the stopThread()-side write could become visible to threadLoop() late,
  // missing the shutdown request on one wakeup. release from startThread()/stopThread(),
  // acquire from threadLoop().
  std::atomic<bool> _running;

  // Cooperative-cancellation flag for an in-flight FollowReferences walk: stopThread() sets
  // this before pthread_kill()/pthread_join() (the signal alone cannot interrupt a call
  // inside the JVM), and heapReferenceCallback() checks it per invocation, aborting the
  // walk within one callback. startThread() resets it (stale abort would kill the next
  // cycle's first pass).
  std::atomic<bool> _abort_pass_requested;

  // Wall-clock deadline for the pass in flight (0 = none). Set once at the top of
  // runPassManualWalk() and shared across that call's static-field sweep, expandFrontier(),
  // and the rotation candidate scan.
  u64 _pass_deadline_ns = 0;

  // Last time root/stack-ref enumeration ran; decides between the cheap expandFrontier()-only path and a new attempt.
  u64 _last_root_enum_ns = 0;

  // Set when the most recent root enumeration attempt ended via BUDGET_EXHAUSTED - runPass()
  // then retries enumeration on the very next pass regardless of ROOT_ENUM_MIN_INTERVAL_NS,
  // so a still-incomplete attempt doesn't wait out the full interval. Cleared as soon as
  // an attempt completes without truncating.
  bool _root_enum_truncated_last_time = false;

  ReferenceChainTracker()
      : _enabled(false),
        _frontier(nullptr), _configured_frontier_cap(0),
        _last_class_map_generation(0),
        _last_resolved_class_count(0),
        _last_static_field_class_count(-1),
        _static_field_sweep_cursor(0),
        _static_field_sweep_cycle_truncated(false),
        _gc_start_epoch(0),
        _gc_finish_epoch(0), _next_tag(1),
        _hop_cap(0), _budget(0), _first_pass_budget(0), _ttl_ms(0), _pause_target_ms(0),
        _effective_pause_target_ms(0), _passes_since_last_progress(0),
        _passes_since_last_candidate_progress(0), _last_candidate_progress_mark(0),
        _canary_backoff_mult(1), _canary_pass_ema_ms(0),
        _last_canary_pass_ns(0), _oom_ramp_active(false),
        _canary_stuck_restart_count(0),
        _effective_budget(0), _effective_cadence_ns(PASS_CADENCE_NS),
        _pause_pid(1, 1.0, 1.0, 1.0, 1, 1.0), _search_started(false),
        _tags_released(true), _urgent_latched(false),
        _urgent_release_ticks(0), _urgent_search_spent(false),
        _urgency_budget_boosted(false), _configured_budget(0),
        _search_state(SearchState::RUNNING),
        _abandon_reason(SearchAbandonReason::NONE), _search_start_ns(0),
        _last_pass_gc_finish_epoch(0), _last_pass_ns(0),
        _passes_run(0),
        _root_kind_rotation_cursor(1),
        _stale_expanded_rotation_cursor(1),
        _thread_walk_anchor_cursor(0),
        _safepoint_pain_budget(0.0), _search_pain_ms(0), _cpu_pain_budget(0.0),
        _thread(), _running(false), _abort_pass_requested(false) {}

  void onGCStart();
  void onGCFinish();

  static void *threadEntry(void *self) {
    ((ReferenceChainTracker *)self)->threadLoop();
    return nullptr;
  }
  void threadLoop();

  // Pass-scheduling trigger: true if the GC-finish epoch advanced since the last pass ("a GC
  // just happened, a pass may be worth running soon") or the cadence elapsed, whichever comes
  // first; also true before the first pass.
  bool shouldRunPass(u64 now_ns);

  // Cheap probe (max=1, not the full poll pollWatchedTargets() makes) into LivenessTracker's
  // population-trend table: true if at least one klass shows a positive population slope
  // worth chasing.
  bool hasLeakSignal();

  // Latched, hysteretic view of secondsToOOM() crossing OOM_URGENT_THRESHOLD_S (see
  // _urgent_latched).
  bool isUrgent() const;

  // Search restart gate: true once _safepoint_pain_budget has drained back to zero
  // (canStartNow()) AND hasLeakSignal() reports a leak candidate.
  bool canAffordNewSearch(u64 now_ns);

  // Resets every per-search field to its just-constructed value so the next runPass() takes
  // the first-pass branch again. Called by shouldRunPass() once a terminal search's tags are
  // already released and canAffordNewSearch() approved.
  void restartSearch();

  // Marks every entry still queued in _pending_expand EXPANDED and drains the queue.
  void markAllFrontierExpanded();

  // Resumed-pass counterpart to the first pass's root-seeded walk: resolves every
  // not-yet-expanded entry queued in _pending_expand via GetObjectsWithTags - objects that
  // fail to resolve are dead and pruned for free - then calls FollowReferences with each
  // resolved object as initial_object to discover its outgoing edges.
  void expandFrontier(jvmtiEnv *jvmti, JNIEnv *jni, int hop_cap, int budget,
                       int *edges_admitted, bool *truncated,
                       bool *frontier_cap_hit, u64 *safepoint_ticks);

  // Static-field counterpart to heapRootCallback()'s GC-root enumeration:
  // a chunked FollowReferences sweep over the loaded classes' static fields
  // (STATIC_FIELD_SWEEP_CHUNK_CLASSES per call), resumable via
  // _static_field_sweep_cursor so one truncated chunk cannot make classes
  // after it unreachable for the rest of the lap. Each call re-sorts classes
  // app-classes-first so likely leak holders are swept early; *cycle_complete
  // reports a completed full lap, which gates _last_static_field_class_count.
  void admitStaticFieldRoots(jvmtiEnv *jvmti, JNIEnv *jni, int hop_cap,
                              int budget, int *edges_admitted,
                              bool *truncated, bool *frontier_cap_hit,
                              bool *cycle_complete, u64 *safepoint_ticks);

  // Clears the live JVMTI tag (SetTag(obj, 0)) of every frontier entry not
  // already ABANDONED, keeping the table's own records. Returns false when
  // GetObjectsWithTags() fails - which tags are still live is then unknown,
  // so nothing is marked ABANDONED; retries are safe, and restartSearch()
  // must not run until this returns true.
  bool releaseSearchTags(jvmtiEnv *jvmti, JNIEnv *jni);

  // Pause-time pacing: feeds `pass_wall_ticks` - the wall-clock duration of the
  // FollowReferences/GetObjectsWithTags call runPass() just made (the safepoint-triggering
  // call itself; no new instrumentation) - into _pause_pid, and scales _effective_budget/
  // _effective_cadence_ns from its output.
  void updatePacing(u64 pass_wall_ticks);

  // Root/stack-ref enumeration passes never reach updatePacing() (their fixed
  // dispatch cost would wrongly throttle the PID signal), but still spend real
  // pause-time budget, so this runs in updatePacing()'s place for such a pass
  // and only ever revokes _borrowed_budget - never grows the warmup streak,
  // which is calibrated against expandFrontier()'s per-node cost.
  void maybeRevokeBorrowForRootEnumPass(u64 pass_wall_ticks);

  // Tags every not-yet-tagged loaded class with a fresh nextClassTag() and resolves its name
  // into _class_tags, via the same GetClassSignature + normalizeClassSignature +
  // Profiler::lookupClass sequence ObjectSampler::recordAllocation() uses
  // (objectSampler.cpp).
  void resolveLoadedClasses(jvmtiEnv *jvmti, JNIEnv *jni);

  // jvmtiHeapReferenceCallback for runPass()'s FollowReferences calls.
  // `user_data` is a PassContext* (private to referenceChains.cpp -
  // only runPass() constructs one).
  static jint JNICALL heapReferenceCallback(
      jvmtiHeapReferenceKind reference_kind,
      const jvmtiHeapReferenceInfo *reference_info, jlong class_tag,
      jlong referrer_class_tag, jlong size, jlong *tag_ptr,
      jlong *referrer_tag_ptr, jint length, void *user_data);

  // Outcome of admitObject(), letting each call site (heapReferenceCallback() and the
  // root/stack-ref callbacks, both in referenceChains.cpp) translate the same admission
  // decision into its own callback-shape-appropriate return value/truncation flag.
  enum class AdmitResult {
    ALREADY_ADMITTED, // *tag_ptr != 0: nothing to do, not a truncation
    HOP_CAP,          // depth >= hop_cap: not admitted, not a truncation
    BUDGET_EXHAUSTED,  // edges_admitted >= budget: this pass's cap
    FRONTIER_CAP_HIT,  // FrontierTable::insert() is full: stops admitting
                       // new entries but does not itself abandon the search -
                       // the no-progress detector abandons only if the
                       // frontier then stops growing
    ADMITTED,
  };

  // First-discovery admission core, factored out of heapReferenceCallback()'s inline branch
  // so the manual-walk driver's root/stack-ref callbacks stay in sync with FollowReferences'
  // own admission by construction, not by copy-paste.
  AdmitResult admitObject(FrontierTable *frontier, int hop_cap, int budget,
                           int *edges_admitted, jlong *tag_ptr,
                           jlong parent_tag, u32 referrer_klass, u32 depth,
                           u8 root_kind, jlong class_tag,
                           bool priority = false,
                           jint edge_field_index = -1, u8 edge_kind = 0,
                           jlong edge_referrer_class_tag = 0);

  // Called by admitObject() on every ADMITTED result - the single shared admission path, so
  // no duplicate call site in the callbacks. O(1) in the common case
  // (_watched_leak_klass_count == 0).
  void trackLeakAccumulation(FrontierTable *frontier, jlong class_tag,
                              jlong parent_tag, jlong tag);

  // Builds and caches chain events for every discovered instance recorded
  // against the slot holding klass_id - slot-driven, so instances recorded
  // while a candidate still qualified are not stranded when it stops.
  void buildDiscoveredInstanceChains(jvmtiEnv *jvmti, JNIEnv *jni,
                                    u32 klass_id, u64 current_search_ns);

  // Records a discovered instance's frontier tag in the class's discovery
  // slots. A leak-correlated instance may evict an uncorrelated (noise) one
  // when all slots are full - without that, noise instances observed before
  // the leak-tagged ones would permanently occupy the slots. Noise never
  // displaces anything on its own.
  void recordDiscoveredInstance(u32 klass_id, jlong frontier_tag,
                                bool leak_correlated);


  // One-time retroactive catch-up for a klass_id the moment it FIRST enters
  // _watched_leak_klass_ids. trackLeakAccumulation() only fires on NEW admissions - it cannot
  // see objects already admitted before this klass started being watched, which for a klass
  // that has been growing a while can be nearly all of them: the container that actually
  // needs re-expansion typically got fully admitted in an early pass, leaving the
  // accumulators permanently empty.
  void seedLeakAccumulationForNewlyWatchedKlass(u32 klass_id);

  // Durability tie-break for an object rediscovered as a heap root while already admitted,
  // factored out of the callbacks so it is unit-testable without a PassContext/JVMTI mock
  // (their user_data type is private to referenceChains.cpp).
  bool maybeUpgradeRootAttachedRootKind(FrontierTable *frontier, jlong tag,
                                        u8 new_root_kind);

  // True if `tag` is already queued in _priority_expand - either queued earlier this pass by
  // the other rotation collector, or left over from a prior pass's truncated batch.
  bool isQueuedForRotation(jlong tag) const {
    return _priority_expand_set.contains(tag);
  }

  // Bounded rotating re-expansion: each pass, feed up to `max_count` already-EXPANDED,
  // root-attached entries whose root_kind is still transient (isTransientRootKind()) back
  // into _priority_expand so expandFrontier() re-walks their fields - giving a stale
  // root_kind another chance to be superseded by a durable root discovered elsewhere in the
  // interim, via the same admitObject()/tie-break machinery every other admission uses.
  std::vector<jlong> collectStaleRootKindEntriesForRotation(int max_count);

  // Bounded rotating re-expansion for stale mutable fields: expandFrontier() observes an
  // object's outgoing references exactly once (the call that marks it EXPANDED) and never
  // revisits it, so a field later reassigned to a different object - e.g. HashMap.table on
  // resize - has its new value permanently unobserved, orphaning everything only reachable
  // through the CURRENT table. Re-walks up to `max_count` EXPANDED entries; already-admitted
  // children are no-ops, so only a genuinely new edge (a mutated field) is admitted.
  std::vector<jlong> collectStaleExpandedEntriesForRotation(int max_count);

  // Bounded rotating re-expansion targeting the accumulation point of a klass LivenessTracker
  // has flagged as growing - the rotation design's targeted tier.
  std::vector<jlong> collectLeakAccumulationCandidatesForRotation(
      int max_count);

  // CANDIDATE-SCOPED REACH: bounded descend walk from an anchor object via
  // FollowReferences(initial_object = anchor), reusing heapReferenceCallback()
  // unchanged; the walk's hop cap is min(_hop_cap, anchor_depth + DESCENT_HOPS).
  // A non-zero `anchor_descend_class_tag` additionally gates the ANCHOR's own
  // outgoing edges to descend only into referees of that exact class
  // (walkCandidateThreadLocals() passes ThreadLocal$ThreadLocalMap's class tag,
  // skipping the Thread's other fields).
  void descendFromAnchor(jvmtiEnv *jvmti, JNIEnv *jni, jobject anchor,
                         jlong anchor_tag, u32 anchor_depth,
                         jlong anchor_descend_class_tag, int budget,
                         int *edges_admitted, bool *truncated,
                         bool *frontier_cap_hit, u64 *safepoint_ticks);

  // Prong 1 of candidate-scoped reach (thread-retained taxonomy): per pass,
  // descend from up to THREAD_WALK_MAX_ANCHORS of the current candidates'
  // qualifying tids' live Thread objects (see _thread_objects) via
  // descendFromAnchor() - a thread-local holder chain lives inside the
  // Thread's own ThreadLocalMap subgraph, so this reaches the tagged instances
  // regardless of the ordinary BFS frontier backlog.
  void walkCandidateThreadLocals(jvmtiEnv *jvmti, JNIEnv *jni, int budget,
                                 int *edges_admitted, bool *truncated,
                                 bool *frontier_cap_hit, u64 *safepoint_ticks);

  // Prong 2 (durable-root-retained taxonomy): select up to `max_count` root-attached entries
  // held by a DURABLE root kind (parent_tag == 0, root_kind STATIC_FIELD or JNI_GLOBAL,
  // FRONTIER or EXPANDED), tiered leak-tagged -> fresh -> container-shaped -> cursor-fair,
  // and descend-walk each via walkStaticFieldAnchors().
  std::vector<jlong> collectStaticFieldAnchorsForRotation(int max_count);
  // The B' at-risk push (both call sites): dedupe via the set, cap-drop when the FIFO is
  // full, per-class quota drop at STATIC_ANCHOR_ATRISK_PER_KLASS_CAP.
  void pushAtRiskStaticAnchor(jlong tag, u32 klass_id);
  // Add `tag` to _static_anchor_index if its root_kind is a durable anchor-tier kind
  // (STATIC_FIELD or JNI_GLOBAL). Called at first admission and at root-kind upgrade.
  void addToStaticAnchorIndex(jlong tag, jlong own_class_tag, u8 root_kind);

  // True iff `klass` implements java/util/Collection or java/util/Map, directly or
  // transitively (superclass chain + interfaces of every visited class, depth-bounded,
  // visited set for interface diamonds).
  bool classImplementsContainerOrMap(jvmtiEnv *jvmti, JNIEnv *jni,
                                     jclass klass);

  // Resolve the two interface tags once; returns false if they cannot be
  // resolved yet (leaves the unresolved ones at 0 so the next call retries).
  bool resolveContainerInterfaceTags(jvmtiEnv *jvmti, JNIEnv *jni);

  // Lazy shape reconciliation for the anchor index: scans _static_anchor_own_class_tags for
  // class tags not yet in _class_shape_cache, resolves up to ANCHOR_SHAPE_RECONCILE_BUDGET
  // per pass via one GetObjectsWithTags call and classifies each.
  void reconcileAnchorClassShapes(jvmtiEnv *jvmti, JNIEnv *jni);
  // Pops up to max_count AtRiskAnchor entries off _static_anchor_fifo's front into `out`
  // (appending), decrementing each popped entry's class occupancy, and re-derives the set
  // from the deque's remaining contents.
  int drainStaticAnchorFifo(int max_count, std::vector<AtRiskAnchor> &out);
  // Pushes `entries` back to _static_anchor_fifo's FRONT in reverse order (preserving FIFO
  // order), re-incrementing each entry's class occupancy, and rebuilds the set - the
  // truncated-walk requeue path.
  void requeueStaticAnchorFifoFront(const std::vector<AtRiskAnchor> &entries);
  // When non-null, receives the tags of RESOLVED-but-unwalked anchors at the truncation break
  // point - GetObjectsWithTags may return fewer anchors than requested (dead tags drop out)
  // in its own order, so the caller cannot recover the un-walked set from a consumed index.
  void walkStaticFieldAnchors(jvmtiEnv *jvmti, JNIEnv *jni,
                              const std::vector<jlong> &anchor_tags,
                              int budget, int *edges_admitted, bool *truncated,
                              bool *frontier_cap_hit, u64 *safepoint_ticks,
                              std::vector<jlong> *unwalked = nullptr);

  // jvmtiHeapRootCallback/jvmtiStackReferenceCallback for runPassManualWalk()'s
  // IterateOverReachableObjects call; `user_data` is a PassContext* (same private type as
  // heapReferenceCallback()).
  static jvmtiIterationControl JNICALL
  heapRootCallback(jvmtiHeapRootKind root_kind, jlong class_tag, jlong size,
                    jlong *tag_ptr, void *user_data);
  static jvmtiIterationControl JNICALL stackRefCallback(
      jvmtiHeapRootKind root_kind, jlong class_tag, jlong size,
      jlong *tag_ptr, jlong thread_tag, jint depth, jmethodID method,
      jint slot, void *user_data);

  // Manual-walk pass driver: when `run_root_enum` is true, seeds/refreshes root-attached
  // frontier entries via IterateOverReachableObjects using `root_enum_budget`; then,
  // regardless, drains _pending_expand via admitStaticFieldRoots()/expandFrontier() up to
  // `expand_budget`.
  void runPassManualWalk(jvmtiEnv *jvmti, JNIEnv *jni, bool run_root_enum,
                          int root_enum_budget, int expand_budget,
                          int *edges_admitted, bool *truncated,
                          bool *frontier_cap_hit, u64 *safepoint_ticks);

  // Inserts (or refreshes) a resolved chain in _resolved_chains, recording the
  // source_tag/source_search_ns it was reconstructed from so a later poll can
  // tell a stale entry from a current one. Returns false when a brand-new
  // source_tag arrives with the cache already at MAX_RESOLVED_CHAINS (dropped
  // and counted, never evicting another live chain) so the caller skips
  // coverage accounting for a chain that will never be emitted.
  bool cacheResolvedChain(jlong source_tag, ReferenceChainEvent &&event,
                          jlong source_tag_val, u64 source_search_ns);

  // Remove a cached chain so pollWatchedTargets rebuilds it on the next poll.
  void invalidateResolvedChain(jlong source_tag);

  // Snapshots the just-abandoned search into _pending_abandoned_events - called from
  // runPass() immediately after it writes SearchState::ABANDONED, while the source fields are
  // still valid (see _pending_abandoned_events).
  void enqueuePendingAbandonedEvent();

public:
  static ReferenceChainTracker *instance() {
    static ReferenceChainTracker instance;
    return &instance;
  }

  // tid -> java.lang.Thread global-ref registry (see _thread_objects). registerThreadObject()
  // no-ops while !_enabled; unregisterThreadObject() is deliberately NOT gated on _enabled -
  // a thread that started while enabled must release its global ref even after recording
  // stopped, otherwise the ref leaks.
  void registerThreadObject(JNIEnv *jni, int tid, jthread thread);
  void unregisterThreadObject(JNIEnv *jni, int tid);

  // Deletes the global refs unregisterThreadObject() queued in _thread_refs_pending_delete
  // (see that member for why deletion is deferred).
  void releaseEndedThreadRefs(JNIEnv *jni);

  // Recording-stop cleanup: delete EVERY remaining registered Thread global ref and empty the
  // registry.
  void releaseAllThreadObjects(JNIEnv *jni);

  // One-time sweep over the JVM's CURRENTLY LIVE threads at recording start, registering each
  // into the same tid -> Thread-object registry.
  void registerExistingThreads(jvmtiEnv *jvmti, JNIEnv *jni);

  // Correlate a leak tag with an instance the BFS admitted BEFORE tagLeakInstances() tagged
  // it (its JVMTI tag is a frontier tag, its frontier entry has leak_tag == 0).
  bool correlateAdmittedLeakTag(jlong frontier_tag, jlong leak_tag,
                                u32 klass_id);

  // Abandon the search after this many consecutive passes with zero new frontier entries
  // admitted (genuinely stuck, not just slow - a large heap takes more passes simply because
  // there are more objects to explore).
  static constexpr int NO_PROGRESS_PASS_LIMIT = 30;

  // Base limit for the canary-specific stuck detector: candidate-discovery must show no
  // progress for this many consecutive passes AND the whole-graph frontier must also have
  // stalled for NO_PROGRESS_PASS_LIMIT passes before a canary search is abandoned - the
  // frontier can still grow tens of thousands of entries deep while chasing a specific,
  // confirmed-reachable candidate, so a canary search is not "stuck" just because it hasn't
  // found its candidate yet if the walk is making real progress toward it.
  // canaryStuckPassLimit() escalates this base across consecutive CANARY_STUCK restarts.
  static constexpr int CANARY_NO_PROGRESS_PASS_LIMIT = 30;

  // Upper bound on how many times canaryStuckPassLimit() doubles the base limit, so a search that is ACTUALLY stuck still gets abandoned.
  static constexpr int MAX_CANARY_STUCK_BACKOFF_SHIFT = 8;

  // The canary-stuck pass limit for the current restart attempt:
  // CANARY_NO_PROGRESS_PASS_LIMIT doubled once per consecutive CANARY_STUCK
  // restart of this candidate-chase sequence, capped by
  // MAX_CANARY_STUCK_BACKOFF_SHIFT.
  int canaryStuckPassLimit() const {
    return CANARY_NO_PROGRESS_PASS_LIMIT
           << std::min(_canary_stuck_restart_count,
                        MAX_CANARY_STUCK_BACKOFF_SHIFT);
  }

  // Multiplier cap for the canary lane's work-scaled backoff (see _canary_backoff_mult).
  static constexpr int CANARY_BACKOFF_MULT_MAX = 16;

  // While a canary search has candidates still unresolved, shouldRunPass() raises
  // _cpu_pain_budget's refill rate by this factor (capped at 100%/wall-clock).
  static constexpr double CANARY_PAIN_BUDGET_REFILL_MULTIPLIER = 100.0;

  // Coverage tracking for the adaptive CPU budget: leak tags assigned per
  // tagging round vs chains resolved for them.
  int _leak_tags_assigned = 0;
  int _leak_tags_resolved = 0;

  // Base marker tag for canary-search candidates: candidate i gets MARKER_TAG_BASE - i
  // (distinct negative values) so heapReferenceCallback() can tell which candidate was found.
  static constexpr jlong MARKER_TAG_BASE = -(1LL << 62);

  // Leak tags are positive JVMTI tags in a dedicated range, assigned by LivenessTracker's tag
  // pool to specific tracked leaking objects.
  static constexpr jlong LEAK_TAG_BASE = 0x40000000LL;
  static constexpr int LEAK_TAG_POOL_SIZE = 256;

  // Check whether a JVMTI tag is a leak tag (from LivenessTracker's pool).
  static bool isLeakTag(jlong tag) {
    return tag >= LEAK_TAG_BASE && tag < LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE;
  }


  // Test accessor for _passes_since_last_progress.
  int passesSinceLastProgressForTest() const { return _passes_since_last_progress; }
  // Canary-lane backoff state.
  int canaryBackoffMultForTest() const { return _canary_backoff_mult; }
  u64 canaryPassEmaMsForTest() const { return _canary_pass_ema_ms; }
  u64 lastCanaryPassNsForTest() const { return _last_canary_pass_ns; }
  void setCanaryBackoffForTest(int mult, u64 ema_ms, u64 last_pass_ns) {
    _canary_backoff_mult = mult;
    _canary_pass_ema_ms = ema_ms;
    _last_canary_pass_ns = last_pass_ns;
  }
  void setOomRampActiveForTest(bool active) { _oom_ramp_active = active; }
  int candidateCountForTest() const { return _candidate_count; }
  void setCandidateCountForTest(int n) { _candidate_count = n; }
  void setCandidateKlassIdForTest(int idx, u32 klass_id) {
    _candidate_klass_ids[idx] = klass_id;
  }
  jlong candidateDiscoveredTagForTest(int slot, int idx) const {
    return _candidate_discovered_tags[slot][idx];
  }
  int candidateDiscoveredCountForTest(int slot) const {
    return _candidate_discovered_count[slot];
  }
  u64 candidateFoundBitsForTest() const { return _candidate_found_bits; }
  void setCandidateFrontierTagForTest(int idx, jlong tag) { _candidate_frontier_tags[idx] = tag; }
  int passesSinceLastCandidateProgressForTest() const { return _passes_since_last_candidate_progress; }
  int canaryStuckRestartCountForTest() const { return _canary_stuck_restart_count; }

  ReferenceChainTracker(const ReferenceChainTracker &) = delete;
  ReferenceChainTracker &operator=(const ReferenceChainTracker &) = delete;

  Error start(Arguments &args);

  // Scales unset referencechains defaults (budget, ttl, framecap, pausetarget, painbudget,
  // firstpassbudget) from the process's max heap size and available processor count, so a
  // large heap doesn't starve the BFS (small-heap defaults abandon via TTL before meaningful
  // progress).
  void autoTuneDefaults(Arguments &args);
  void stop();

  // Spawns the BFS thread if tracking is enabled and no thread is already running.
  void startThread();

  // Stops and joins the BFS thread, mirroring BaseWallClock::stop()'s
  // pthread_kill(WAKEUP_SIGNAL) + pthread_join() shape (wallClock.cpp) - WAKEUP_SIGNAL is
  // already installed unconditionally in vmEntry.cpp, so no extra signal setup is needed.
  void stopThread();

  bool enabled() const { return _enabled; }

  u64 gcStartEpoch() { return load(_gc_start_epoch); }
  u64 gcFinishEpoch() { return load(_gc_finish_epoch); }

  // Tag round-trip helpers driving FrontierTable's tag-indexed slots.
  jlong nextTag() { return atomicIncRelaxed(_next_tag, (jlong)1); }

  // Serializes runPass()+pollWatchedTargets() between threadLoop() and the test seams (see
  // runPassSerialized()).
  Mutex _engine_lock;
  jlong tagObject(jvmtiEnv *jvmti, jobject obj);
  jlong getTag(jvmtiEnv *jvmti, jobject obj);
  void clearTag(jvmtiEnv *jvmti, jobject obj);

  // Hands out a fresh negative class tag, from the shared process-wide counter both this
  // class and LivenessTracker mint from - see classTagAllocator.h for why this must be shared
  // rather than a private counter.
  jlong nextClassTag() { return ClassTagAllocator::next(); }

  // Returns the frontier metadata table, or nullptr if the subsystem was
  // never started with the flag enabled.
  FrontierTable *frontierTable() { return _frontier; }

  // Returns the class-tag resolution table. Exposed for testing in
  // isolation, matching frontierTable()'s existing rationale.
  ClassTagTable *classTags() { return &_class_tags; }

  // Runs exactly one bounded BFS pass and returns.
  bool runPass(jvmtiEnv *jvmti, JNIEnv *jni, bool *out_truncated = nullptr);

  // Serialized entry points for the two engine drivers: the real BFS thread (threadLoop())
  // and the debug seams (javaApi.cpp's
  // runReferenceChainPass0()/pollReferenceChainTargets0()).
  bool runPassSerialized(jvmtiEnv *jvmti, JNIEnv *jni) {
    MutexLocker engine_guard(_engine_lock);
    return runPass(jvmti, jni);
  }

  void pollWatchedTargetsSerialized(jvmtiEnv *jvmti, JNIEnv *jni) {
    MutexLocker engine_guard(_engine_lock);
    pollWatchedTargets(jvmti, jni);
  }

  // Search-level outcome (SearchState's constants).
  u8 searchState() { return loadAcquire(_search_state); }

  // Total passes run for the current/most recent search. Exposed for tests
  // to confirm multi-pass resumption actually happened.
  int passesRun() { return load(_passes_run); }

  // Which SearchAbandonReason cutoff moved the search out of RUNNING, or NONE.
  u8 abandonReason() { return load(_abandon_reason); }

  // Resolves one chain hop's retention-edge label into `out` (NUL-terminated,
  // at most out_cap bytes incl. the NUL): the referrer field's NAME for a
  // resolvable FIELD/STATIC_FIELD edge (decoded via the HopLabelClass cache),
  // or the edge KIND label otherwise - never a fabricated name. Legal only
  // OUTSIDE heap callbacks (GetClassFields/GetFieldName are not callable
  // during heap iteration), so fillHopEdgeLabels()/buildChainEvent() call it
  // on the BFS thread between walks.
  void resolveHopEdgeLabel(jvmtiEnv *jvmti, JNIEnv *jni, ChainHopEdge edge,
                           char *out, size_t out_cap);

  // Fills *out with one label per chain hop, aligned with the chain's leaf-to-root order
  // (edges[i] = the retention edge INTO chain[i]), via resolveHopEdgeLabel().
  static constexpr size_t MAX_HOP_EDGE_LABEL =
      MAX_REFERENCE_CHAIN_EDGE_LABEL;
  // Per-referrer-class ordinal->name list cache behind resolveHopEdgeLabel(): decoding the
  // ordinal requires walking the class's whole interface closure + superclass chain
  // (GetClassFields + GetFieldName per field), and chains re-emit on every dump, so each
  // chain-relevant class's decoded ordinal space is built once here.
  static constexpr size_t HOP_LABEL_CLASS_CACHE_CAP = 1024;
  struct HopLabelClass {
    jlong class_tag;
    // One entry per ordinal in the class's flattened field space - the
    // i-th element is the name of ordinal i. Empty when decoding failed.
    std::vector<std::string> field_names;
    bool decode_failed;
  };
  std::unordered_map<jlong, HopLabelClass> _hop_label_cache;

  // Cache lookup/decode behind resolveHopEdgeLabel(). Never returns
  // null (a failed decode is cached as decode_failed).
  const HopLabelClass *hopLabelClassFor(jvmtiEnv *jvmti, JNIEnv *jni,
                                        jlong class_tag);

  void fillHopEdgeLabels(jvmtiEnv *jvmti, JNIEnv *jni,
                         const std::vector<ChainHopEdge> &edges,
                         std::vector<ReferenceChainHop> *out);

  // Reference-chain JFR event surface: reconstructs the chain for target_tag
  // from the frontier table into *out. Returns false (leaving *out untouched)
  // if target_tag was never inserted into the frontier table.
  bool buildChainEvent(jvmtiEnv *jvmti, JNIEnv *jni, jlong target_tag,
                       ReferenceChainEvent *out);

  // Appends the root TYPE element (the declaring class, resolved from
  // FrontierEntry::referrer_class_tag) to a static-field-rooted chain - see the definition in
  // referenceChains.cpp for the rationale and skip conditions.
  void appendStaticFieldRootType(const FrontierEntry &terminal,
                                 std::vector<u32> *chain,
                                 std::vector<ChainHopEdge> *edges);

  // Canary-search chain reconstruction: builds the chain for a canary candidate from the
  // per-candidate chain link recorded at pruning time (_candidate_parent_tags[] etc.),
  // walking parent_tag through the frontier table (positive tags, so lookup() works).
  bool buildCanaryChainEvent(int candidate_idx, ReferenceChainEvent *out);

  // Abandoned-search JFR event surface: unlike buildChainEvent(), this needs no target_tag -
  // it reports the search's own termination state.
  bool buildAbandonedEvent(ReferenceChainAbandonedEvent *out) {
    // Acquire-load, not a plain relaxed load - see searchState()'s own
    // comment for why: this is the same guard-then-read-details pattern.
    if (out == nullptr || loadAcquire(_search_state) != SearchState::ABANDONED) {
      return false;
    }
    out->_reason = load(_abandon_reason);
    out->_passes_run = (u32)load(_passes_run);
    out->_frontier_size = _frontier != nullptr ? (u32)_frontier->size() : 0;
    out->_hop_cap = _hop_cap;
    out->_budget = _budget;
    out->_ttl_ms = _ttl_ms;
    out->_elapsed_ns = load(_last_pass_ns) - load(_search_start_ns);
    return true;
  }

  // Target-selection bridge: polls LivenessTracker::selectLeakCandidates() and, for each
  // candidate whose representative instance has already been discovered by an ordinary
  // runPass() walk (getTag() > 0 - a read, never a SetTag seed: seeding a candidate before
  // the forward walk reached it would break the walk's tag bookkeeping), reconstructs its
  // datadog.ReferenceChain and caches it in _resolved_chains. The write is deferred to
  // drainPendingChainEvents() on the dump() thread; cached entries whose representative no
  // longer resolves are pruned here. No-op if disabled or null jvmti/jni.
  void pollWatchedTargets(jvmtiEnv *jvmti, JNIEnv *jni);

  // Targeted holder re-walk: enqueues `tag`'s chain-root entry (the root-attached ancestor of
  // its frontier chain) onto _priority_expand so the next rotation/expand pass re-walks the
  // holder that retains everything below `tag`.
  void requeueChainRootForRotation(jlong tag);

  // Appends a copy of every currently-cached resolved chain to *out, re-stamped with a fresh
  // _start_time so it lands in the dumping chunk's time window, WITHOUT clearing the cache -
  // a repeatable snapshot, not a drain, so the same live sample's chain is re-emitted into
  // every JFR chunk it survives into.
  void drainPendingChainEvents(std::vector<ReferenceChainEvent> *out);

  // Appends every abandoned-search event queued since the last call and clears the queue - a
  // true drain, unlike drainPendingChainEvents(): an abandoned search is a discrete past
  // occurrence, not an ongoing live sample, so there is nothing to re-report once emitted.
  void drainPendingAbandonedEvents(std::vector<ReferenceChainAbandonedEvent> *out);

  static void JNICALL GarbageCollectionStart(jvmtiEnv *jvmti_env);
  static void JNICALL GarbageCollectionFinish(jvmtiEnv *jvmti_env);

  // Test seam - not part of the production API (see LivenessTracker's "Test seams" block in
  // livenessTracker.h).
  jlong tagAsRootForTest(jvmtiEnv *jvmti, JNIEnv *jni, jobject obj);

  // Test seam - not part of the production API.
  void resetSearchStateForTest(jvmtiEnv *jvmti, JNIEnv *jni);

  // Test seam - diagnostic-only: reports how far a given (already-tagged) object sits from
  // the front of _pending_expand's FIFO, to distinguish "not yet expanded" from "already
  // expanded" or "never admitted" without a debugger.
  long pendingExpandPositionForTest(jlong tag) const;

  // Test seam: companion to pendingExpandPositionForTest() for computing a
  // position's fraction of the current backlog.
  size_t pendingExpandSizeForTest() const;

  // Test seam: exposes the private shouldRunPass() gate directly, so a test can assert
  // whether a fresh/terminal search would be allowed to start right now - in particular
  // whether the urgent-OOM bypass (hasLeakSignal(), see OOM_URGENT_THRESHOLD_S) opens this
  // gate even with zero per-klass leak candidates - something runReferenceChainPass0()
  // (javaApi.cpp) cannot show, since it calls runPass() directly and never consults
  // this gate.
  bool shouldRunPassForTest(u64 now_ns) { return shouldRunPass(now_ns); }
};

#endif // _REFERENCECHAINS_H
