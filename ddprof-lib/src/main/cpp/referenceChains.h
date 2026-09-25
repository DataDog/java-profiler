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

#include "referenceChainFrontier.h"

// Incremental reference-chain search driven by a dedicated JVMTI agent thread.
class ReferenceChainTracker {
  // Test-only accessor (referenceChains_ut.cpp), mirroring vmEntry.h's VMTestAccessor pattern:
  // since instance() is a process-wide singleton, the search-lifecycle fields
  // (_search_state/_search_started/etc.) would otherwise leak across separate TEST_F cases in the
  // same gtest binary.
  friend class ReferenceChainsTestAccessor;

private:
  bool _enabled;

  // Frontier metadata table. Constructed lazily on the first start() with the flag enabled, sized
  // from args._reference_chains_frontier_cap; like LivenessTracker's table (LivenessTracker's own
  // table does the same) it survives stop() so it persists across multiple start/stop recording
  // cycles.
  FrontierTable *_frontier;

  // args._reference_chains_frontier_cap as of the most recent start() call - recorded
  // unconditionally (even once _frontier already exists and start() itself skips reconstructing
  // it), so resetSearchStateForTest() has something to rebuild the table at other than whatever cap
  // the first start() in this JVM happened to use (see _frontier's own comment).
  int _configured_frontier_cap;

  // The args-configured per-pass budget (Arguments::_reference_chains_budget), recorded at start().
  int _configured_budget;

  // Class-tag -> StringDictionary id table. Populated by resolveLoadedClasses(), read by
  // heapReferenceCallback().
  ClassTagTable _class_tags;

  // Profiler::classMap()'s generation as of the last resolveLoadedClasses() call.
  u64 _last_class_map_generation;

  // GetLoadedClasses() count as of the last resolveLoadedClasses() call that actually ran its
  // per-class GetTag()/GetClassSignature() scan - lets that method skip the scan entirely on a
  // resumed pass where the loaded-class count has not CHANGED (see resolveLoadedClasses()'s own
  // comment for why this must be an equality check, not just a "grew" check: the count is not
  // monotonic once class unloading is in play).
  int _last_resolved_class_count;

  // GetLoadedClasses() count as of the last runPassManualWalk() call whose admitStaticFieldRoots()
  // sweep actually ran (i.e. was not skipped by the guard below) AND completed without being
  // truncated.
  int _last_static_field_class_count;

  // Index into the (per-call, app-classes-first-partitioned) loaded-class list that
  // admitStaticFieldRoots() resumes from on its next call - see that method's own comment for why a
  // single FollowReferences over every loaded class at once (no cursor) could never finish within
  // one pass's safepoint deadline on a JVM with tens of thousands of loaded classes.
  int _static_field_sweep_cursor;

  // Set when any chunk within the current lap (the cursor's walk from 0 back to 0) truncates.
  bool _static_field_sweep_cycle_truncated;

  // Per-call cap on how many classes admitStaticFieldRoots() includes in one FollowReferences call
  // - see that method's own comment.
  static constexpr int STATIC_FIELD_SWEEP_CHUNK_CLASSES = 512;

  // Per-class cap on non-STATIC_FIELD edges admitted during one admitStaticFieldRoots() lap.
  static constexpr int STATIC_FIELD_SWEEP_NON_STATIC_CAP_PER_CLASS = 32;

  // GC epoch counters, bumped from the JVMTI GC callbacks and read by shouldRunPass().
  volatile u64 _gc_start_epoch;
  volatile u64 _gc_finish_epoch;

  // Monotonically increasing tag source for frontier objects.
  volatile jlong _next_tag;

  // Per-pass tunables, copied from Arguments in start().
  int _hop_cap;
  int _budget;

  // Larger one-shot edge budget for the search's root-seeded first pass.
  int _first_pass_budget;

  // Wall-clock TTL for one search; <= 0 disables the cutoff.
  long _ttl_ms;

  // Pause-time pacing controller: pause-time-SLO ceiling copied from Arguments in start()
  // (Arguments::_reference_chains_pause_target_ms) - the single pause-time-SLO target, in place of
  // guessing _budget/PASS_CADENCE_NS directly.
  long _pause_target_ms;
  // Runtime-adjusted pause target: when isUrgent(), this is bumped to URGENT_PAUSE_TARGET_MS so
  // each pass can explore more edges.
  long _effective_pause_target_ms;
  // Passes since the frontier last grew. Reset to 0 whenever _frontier->size() increases (new
  // entries admitted).
  int _passes_since_last_progress;
  // Passes since _candidate_found_bits last changed (a candidate was newly found, or a new
  // candidate was admitted into a slot).
  int _passes_since_last_candidate_progress;
  // candidate_count + popcount(found_bits) as of the last pass this was updated.
  int _last_candidate_progress_mark;

  // Canary-lane pass pacing, work-scaled: the chase's inter-pass spacing is _canary_backoff_mult x
  // _canary_pass_ema_ms - a multiple of what a pass actually COSTS, not a fixed wall-clock
  // constant.
  int _canary_backoff_mult;
  // 0.8/0.2 EMA of each pass's whole-call wall duration in ms
  // (TSC::ticks_to_millis(pass_wall_ticks), runPass()), updated every pass - kept warm regardless
  // of canary state so a chase that opens on a known-cost crawl sizes correctly from its first
  // held-off decision.
  u64 _canary_pass_ema_ms;
  // End-of-pass timestamp of the last pass that ran with a canary chase still open (the reference
  // point for the spacing above).
  u64 _last_canary_pass_ns;
  // Whether threadLoop()'s OOM urgency ramp is currently active, set each loop iteration BEFORE
  // shouldRunPass() (same thread, no atomics needed).
  bool _oom_ramp_active;

  // How many consecutive times in a row runPass()'s canary-stuck check
  // (CANARY_NO_PROGRESS_PASS_LIMIT below) has abandoned this same candidate-chase sequence.
  int _canary_stuck_restart_count;

  // Canary-search candidate set: LivenessTracker-flagged leak klasses this
  // tracker chases, one slot per klass. The retired marker-tag pre-tagging
  // (each candidate's representative pre-tagged MARKER_TAG_BASE - i for an
  // identity match in the walk) was replaced by leak-tag interception -
  // LivenessTracker tags specific tracked instances, and discovery records
  // _candidate_found_bits/_candidate_frontier_tags when one is resolved.
  static constexpr int MAX_LEAK_CANDIDATES_FROM_LT = 5;

  // How many klass_ids _watched_leak_klass_ids tracks at once - matches
  // LivenessTracker::MAX_LEAK_CANDIDATES (livenessTracker.h), the cap
  // LivenessTracker::topKlassesByGenerationCount() itself already enforces; duplicated here for the
  // same reason MAX_LEAK_CANDIDATES_FROM_LT above already duplicates it, rather than depending on a
  // private LivenessTracker constant.
  static constexpr int MAX_WATCHED_LEAK_KLASSES = 5;
  int _candidate_count;
  u64 _candidate_found_bits;
  // klass_id occupying each slot, so pollWatchedTargets() can tell whether a klass_id
  // selectLeakCandidates() returns this poll already has a slot (and must not be
  // re-tagged/re-admitted) or is new (and should be admitted into the next free slot).
  u32 _candidate_klass_ids[MAX_LEAK_CANDIDATES_FROM_LT];
  jlong _candidate_frontier_tags[MAX_LEAK_CANDIDATES_FROM_LT];
  // Per-candidate chain link recorded at pruning time: parent_tag (referrer's frontier tag,
  // positive) and referrer_klass.
  jlong _candidate_parent_tags[MAX_LEAK_CANDIDATES_FROM_LT];
  u32 _candidate_referrer_klasses[MAX_LEAK_CANDIDATES_FROM_LT];
  u32 _candidate_depths[MAX_LEAK_CANDIDATES_FROM_LT];

  // Per-SLOT snapshot of the qualifying allocating-thread tids
  // LivenessTracker::selectLeakCandidates() reported for that slot's klass this poll, refreshed by
  // pollWatchedTargets() (zeroed first, then filled from the poll's candidates so a klass that
  // stops qualifying stops walking its tids too).
  static constexpr int MAX_CANDIDATE_QUALIFYING_TIDS = 16;
  jint _candidate_qualifying_tids[MAX_LEAK_CANDIDATES_FROM_LT]
                                [MAX_CANDIDATE_QUALIFYING_TIDS];
  int _candidate_qualifying_tid_count[MAX_LEAK_CANDIDATES_FROM_LT];

  // tid -> JNI global reference to the live java.lang.Thread object, fed from
  // Profiler::onThreadStart/onThreadEnd (registerThreadObject()/unregisterThreadObject()).
  Mutex _thread_objects_lock;
  std::unordered_map<jint, jobject> _thread_objects;
  // Global refs of ended threads awaiting deletion. unregisterThreadObject() must NOT
  // DeleteGlobalRef() directly: walkCandidateThreadLocals() copies the jobject out of
  // _thread_objects under _thread_objects_lock, releases the lock, and can still be using it as a
  // FollowReferences anchor when a concurrent ThreadEnd erases the entry - deleting there would be
  // JNI use-after-free (once deleted, a global ref is invalid for every other JNI call).
  std::vector<jobject> _thread_refs_pending_delete;

  // Auto-marked instances: when the BFS walk discovers ANY object whose class matches a watched
  // leak class (not just the pre-tagged representative), its frontier tag is recorded here so
  // pollWatchedTargets() can build chain events for all of them.
  static constexpr int MAX_DISCOVERED_INSTANCES_PER_CLASS = 8;
  jlong _candidate_discovered_tags[MAX_LEAK_CANDIDATES_FROM_LT]
                                   [MAX_DISCOVERED_INSTANCES_PER_CLASS];
  int _candidate_discovered_count[MAX_LEAK_CANDIDATES_FROM_LT];

  // klass_ids from LivenessTracker::topKlassesByGenerationCount() (a faster, un-hysteresis-gated
  // ranking than the canary candidate set above - see that method's own comment), refreshed once
  // per BFS-thread tick but only once hasLeakSignal() has already fired via the slower,
  // hysteresis-gated selectLeakCandidates() path (per design discussion: this whole mechanism only
  // cranks once the trend detector has already triggered, so it never needs to wait out that same
  // hysteresis a second time on its own).
  u32 _watched_leak_klass_ids[MAX_WATCHED_LEAK_KLASSES];
  int _watched_leak_klass_count = 0;

  // Packs a (leaf_klass_id, parent_class_id) pair into one map key for
  // _leak_signature_totals/_leak_signature_prev_totals below - both are StringDictionary ids (u32),
  // so this never loses information and avoids defining a custom hash/equality functor for a
  // 2-field struct key.
  static u64 leakSignatureKey(u32 leaf_klass_id, u32 parent_class_id) {
    return ((u64)leaf_klass_id << 32) | (u64)parent_class_id;
  }

  // Tier 1 of the leak-accumulation rotation design (see
  // collectLeakAccumulationCandidatesForRotation()'s own comment for the full design): aggregate,
  // per (leaf_klass_id, parent_class_id) signature - not per object - how many admitted children of
  // that leaf klass_id have been observed under a parent of that class.
  std::unordered_map<u64, u32> _leak_signature_totals;

  // Snapshot of _leak_signature_totals as of the END of the previous pass - runPassManualWalk()
  // computes each signature's delta (totals - this) to rank signatures by growth before rolling
  // this forward to the current totals for the next pass's comparison.
  std::unordered_map<u64, u32> _leak_signature_prev_totals;

  // Tier 2 of the leak-accumulation rotation design: per PARENT TAG (not per class), how many
  // admitted children of a watched leaf klass_id this specific parent object holds, plus which
  // signature it belongs to (so rotation-selection can filter to the pass's winning signature
  // without a second lookup).
  struct LeakParentFanoutEntry {
    u64 signature_key;
    u32 fanout;
  };
  std::unordered_map<jlong, LeakParentFanoutEntry> _leak_parent_fanout;

  // Rotating skip-count over _leak_parent_fanout's iteration order for
  // collectStaleExpandedEntriesForRotation()'s leak-parent-priority tier - advances by the number
  // of parents selected each pass so, across passes, every fanout parent gets re-walked within
  // ceil(fanout_size/budget) passes instead of only whichever entries the hash iteration happens to
  // yield first.
  u64 _leak_parent_rotation_cursor = 0;

  // Pause-time pacing controller: the actual per-pass budget runPass() passes to
  // FollowReferences/expandFrontier(), replacing _budget's old role as a literal per-pass value -
  // _budget above becomes this controller's ceiling instead (never exceeded, see updatePacing()),
  // while this field is what updatePacing() actually raises/lowers pass to pass.
  int _effective_budget;

  // Pause-time pacing controller: the actual fallback cadence shouldRunPass()/threadLoop() compare
  // against, replacing the fixed PASS_CADENCE_NS constant below in that role once updatePacing()
  // starts adjusting it - see PASS_CADENCE_NS's own comment for why that constant survives as this
  // field's starting value rather than being deleted outright.
  u64 _effective_cadence_ns;

  // Budget-borrowing: extra headroom updatePacing() has temporarily granted above _budget's own
  // ceiling, earned by a sustained run of comfortably- under-target passes (see
  // BORROW_WARMUP_PASSES's own comment).
  int64_t _borrowed_budget;

  // Budget-borrowing: number of consecutive passes (since the last reset) that came in comfortably
  // under _pause_target_ms (see BORROW_UNDER_TARGET_FRACTION).
  int _consecutive_under_target_passes;

  // Pause-time pacing controller: this tracker's own PidController instance - see updatePacing()
  // below for the full mechanism, and PASS_CADENCE_NS's neighboring constants for why its gains are
  // not copied from ObjectSampler/ MallocTracer/NativeSocketSampler's shared triple.
  PidController _pause_pid;

  // Self-calibrating adaptive batch sizing for GetObjectsWithTags (see expandFrontier()'s own
  // comment).
  size_t _gotw_batch_size = 0; // 0 = unset, use GOTW_INITIAL_BATCH_SIZE
  u64 _gotw_ema_call_ns = 0;    // EMA of per-call elapsed, 0 = unset

  // Nominal per-call window for the proportional batch control above when no phase deadline is set
  // (expandFrontier()'s window is the REMAINING deadline, which the phases refresh per invocation).
  static constexpr u64 GOTW_CPU_BUDGET_NS = 25000000; // 25ms

  // Effective window for the proportional batch control (expandFrontier() calls this with the
  // remaining pass deadline and the depth of the lane the next GetObjectsWithTags call will drain).
  u64 gotwWindowNs(u64 remaining_ns, size_t lane_depth) const {
    u64 window_ns = remaining_ns != 0 ? remaining_ns : GOTW_CPU_BUDGET_NS;
    if (lane_depth >= GOTW_BACKLOG_MIN_DEPTH &&
        _gotw_ema_call_ns > window_ns) {
      window_ns = std::max(window_ns,
                            _gotw_ema_call_ns * GOTW_BACKLOG_WINDOW_MULT);
    }
    return window_ns;
  }

  // Lane depth beyond which gotwWindowNs()'s backlog widening applies.
  static constexpr size_t GOTW_BACKLOG_MIN_DEPTH = 4096;

  // How many measured per-call floors one widened window may cost - see gotwWindowNs() above.
  static constexpr u64 GOTW_BACKLOG_WINDOW_MULT = 3;

  // Conservative initial batch_size before the first GetObjectsWithTags measurement.
  static constexpr int GOTW_INITIAL_BATCH_SIZE = 64;
  // AIMD bounds for the adaptive batch: MAX bounds JNI local refs per call, MIN keeps each call
  // from resolving a single object.
  static constexpr size_t GOTW_MAX_BATCH = 512;
  static constexpr size_t GOTW_MIN_BATCH = 8;

  // Search lifecycle state. _search_started distinguishes a search's first pass (seed
  // FollowReferences from the heap roots) from a resumed pass (expand the persisted frontier, see
  // expandFrontier()) - runPass() below.
  bool _search_started;
  volatile u8 _search_state;

  // True once releaseSearchTags() has confirmed every live tag this search owned was actually
  // cleared (or there were none) - see that method's own comment for why a GetObjectsWithTags()
  // failure must NOT be treated as "released".
  bool _tags_released;

  // Whether threadLoop()'s urgency ramp currently holds the multiplied _budget (see the urgency
  // block there and _configured_budget's own comment).
  bool _urgency_budget_boosted;

  // Hysteresis state behind isUrgent(), which used to be a bare `secondsToOOM() <
  // OOM_URGENT_THRESHOLD_S` comparison.
  mutable bool _urgent_latched;
  mutable int _urgent_release_ticks;
  mutable bool _urgent_search_spent;

  // Set (once) at the same point runPass() moves _search_state to ABANDONED - see
  // SearchAbandonReason's own comment for why this exists and buildAbandonedEvent()/abandonReason()
  // below for how it is read.
  volatile u8 _abandon_reason;

  // Wall-clock timestamp (OS::nanotime()) of the search's first pass - baseline for the TTL cutoff
  // above.
  volatile u64 _search_start_ns;

  // Tags currently in FrontierEntryState::FRONTIER (admitted but not yet expanded), in admission
  // order.
  std::deque<jlong> _pending_expand;

  // Fast-lane counterpart to _pending_expand above: entries admitted while re-walking a
  // rotation-selected (already-EXPANDED) parent go here instead, and expandFrontier() drains this
  // queue ahead of the ordinary one.
  std::deque<jlong> _priority_expand;

  // Which lane the NEXT expandFrontier() batch comes from when both lanes are non-empty (the
  // alternation toggle).
  bool _expand_lane_prefer_priority = true;

  // Upper bound on _priority_expand above. 1024 holds a few passes' worth of rotation selection
  // (budgets sum to ~272/pass) so a truncating rotation phase still has work waiting next pass.
  static constexpr size_t PRIORITY_EXPAND_CAP = 1024;

  // O(1) membership index over _priority_expand, backing isQueuedForRotation(): the rotation
  // collectors run that check for EVERY FrontierTable slot they visit (~199k EXPANDED entries on a
  // large heap), and the original linear scan over the deque cost up to ~200M comparisons per
  // rotation pass at the cap - observed prominently in profiles.
  class PriorityExpandSet {
   private:
    // 2^11 == 2 * PRIORITY_EXPAND_CAP == 2048 slots. The shift below derives from it; keep both in
    // sync.
    static constexpr u64 SLOT_SHIFT = 11;
    static constexpr u64 SLOT_MASK = (1ULL << SLOT_SHIFT) - 1;
    jlong _keys[1ULL << SLOT_SHIFT];
    u8 _used[1ULL << SLOT_SHIFT]; // 0 = empty, 1 = occupied

    static u64 mix(jlong tag) {
      // Fibonacci hashing: spreads near-sequential integer tags evenly across the table's
      // power-of-two slot space.
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

    // Re-derives the index from the deque's CURRENT contents.
    template <typename Deque> void rebuildFrom(const Deque &queue) {
      clear();
      for (jlong tag : queue) {
        insert(tag);
      }
    }
  } _priority_expand_set;

  // B' (find-anchor-holder-eviction / find-anchor-live-feed-design): a static holder richly
  // referenced from the running graph is EXCLUDED from the static-anchor tier forever once its
  // frontier entry is chain-attached (first admitted via a non-root path, or demoted by
  // improveChain) - maybeUpgradeRootAttachedRootKind() refuses entries with parent_tag != 0 by
  // design, so collectStaticFieldAnchorsForRotation() (parent_tag == 0 filter) can never select it.
  struct AtRiskAnchor {
    jlong tag;
    u32 klass_id;
    // PriorityExpandSet::rebuildFrom() iterates `jlong tag : queue` - the implicit conversion keeps
    // that template generic over both the plain-jlong _priority_expand deque and this pair deque.
    operator jlong() const { return tag; }
  };
  std::deque<AtRiskAnchor> _static_anchor_fifo;

  // Membership index over _static_anchor_fifo (push-side dedupe, so one lap's repeated static edges
  // onto the same chain-attached holder push it once) - a second instance of PriorityExpandSet,
  // whose fixed 2048 slot table keeps the cap at PRIORITY_EXPAND_CAP (1024).
  PriorityExpandSet _static_anchor_fifo_set;
  static constexpr size_t STATIC_ANCHOR_FIFO_CAP = PRIORITY_EXPAND_CAP;

  // Per-class admission counts backing the per-klass cap on at-risk anchor pushes.
  std::unordered_map<u32, u32> _static_anchor_fifo_klass_counts;
  static constexpr u32 STATIC_ANCHOR_ATRISK_PER_KLASS_CAP = 64;

  // Index of root-attached STATIC_FIELD/JNI_GLOBAL frontier entries, so
  // collectStaticFieldAnchorsForRotation() iterates O(anchors) instead of scanning the full
  // frontier table O(frontier_size).
  std::vector<jlong> _static_anchor_index;

  // Parallel to _static_anchor_index: the OWN class tag of each anchor object (the class of the
  // static field's VALUE, not the holder class).
  std::vector<jlong> _static_anchor_own_class_tags;

  // Dedup companion for _static_anchor_index (O(1) membership; the population is ~28k on a real JVM
  // - see addToStaticAnchorIndex()'s own comment).
  std::unordered_set<jlong> _static_anchor_index_tags;

  // Shape of a class as an anchor candidate: does the class implement java/util/Collection or
  // java/util/Map (directly or via superclasses/ interfaces)?
  enum class AnchorClassShape : u8 { UNKNOWN = 0, CONTAINER = 1, NON_CONTAINER = 2 };

  // class tag -> AnchorClassShape, process-lifetime (class tags are never reused - the shared
  // class-tag allocator is deliberately not reset by restartSearch()).
  std::unordered_map<jlong, u8> _class_shape_cache;

  // java/util/Collection and java/util/Map class tags, resolved once lazily by
  // resolveContainerInterfaceTags() (0 = not yet resolved; a resolved value is NEGATIVE - class
  // tags are a negative namespace, see nextClassTag()'s own comment).
  jlong _collection_iface_class_tag = 0;
  jlong _map_iface_class_tag = 0;

  // Fair-rotation cursors (index POSITIONS, not tags) for the two cursor-fair tiers of
  // collectStaticFieldAnchorsForRotation(): _anchor_container_cursor for container-shaped anchors,
  // _anchor_other_cursor for everything else.
  size_t _anchor_container_cursor = 0;
  size_t _anchor_other_cursor = 0;

  // FIFO of newly admitted anchors awaiting their first walk.
  std::deque<jlong> _static_anchor_fresh_queue;

  // Cap for _static_anchor_fresh_queue. The queue normally holds only ~one pass of sweep admits
  // (admits happen in passes, the collector drains every pass, and the drain DROPS everything it
  // does not keep, so the queue empties each call); the cap only guards a pathological burst (e.g.
  // a pass admitting thousands) from growing it unbounded in native memory.
  static constexpr size_t STATIC_ANCHOR_FRESH_CAP = 1024;

  // java/lang/Object jclass cache for expandFrontier()'s and admitStaticFieldRoots()'s holder-array
  // element type (referenceChains.cpp) - resolved once via FindClass()+NewGlobalRef() and reused
  // for the tracker's lifetime.
  jclass _cached_object_class = nullptr;

  // Rotation cursor for collectStaleRootKindEntriesForRotation(): 1-based tag to resume scanning
  // from on the next call, so consecutive calls sweep forward through the table instead of always
  // re-examining the same low-tag entries first.
  jlong _root_kind_rotation_cursor;

  // Same role as _root_kind_rotation_cursor above, but for
  // collectStaleExpandedEntriesForRotation(): without its own persistent cursor, that sweep always
  // restarted from tag 1 on every call, so a frontier table holding >=
  // STALE_EXPANDED_ROTATION_BUDGET low-tag entries that stay EXPANDED forever (long-lived
  // infrastructure objects) filled its entire per-pass cap from that population alone, every pass,
  // permanently starving any EXPANDED entry with a higher tag (e.g. a static field's collection,
  // admitted only once its class loads well after startup) of ever being re-queued.
  jlong _stale_expanded_rotation_cursor;

  // Per-pass cap on how many transient-root_kind entries collectStaleRootKindEntriesForRotation()
  // selects - round, provisional like this subsystem's other unbenchmarked constants (see e.g.
  // MIN_EFFECTIVE_BUDGET's own comment): small enough that a pass dominated by rotation work never
  // meaningfully competes with genuinely new discoveries for the same pass's budget, large enough
  // that a search with a modest number of transient roots converges to durable attribution within a
  // handful of passes rather than needing hundreds.
  static constexpr int ROOT_KIND_ROTATION_BUDGET = 16;

  // Per-pass cap on how many EXPANDED entries collectStaleExpandedEntriesForRotation() re-queues
  // for expansion, uniformly across the WHOLE frontier table regardless of lineage.
  static constexpr int STALE_EXPANDED_ROTATION_BUDGET = 256;

  // Candidate-scoped reach (see descendFromAnchor()/walkCandidateThreadLocals()/
  // walkStaticFieldAnchors()'s own comments): how many hops BELOW a descend walk's anchor the walk
  // may admit.
  static constexpr int DESCENT_HOPS = 16;

  // Per-pass cap on how many candidate threads walkCandidateThreadLocals() descend-walks.
  static constexpr int THREAD_WALK_MAX_ANCHORS = 4;

  // Per-pass cap on how many root-attached static holders walkStaticFieldAnchors() resolve +
  // descend-walk.
  static constexpr int STATIC_ANCHOR_ROTATION_BUDGET = 32;

  // Per-pass cap on how many DISTINCT anchor classes reconcileAnchorClassShapes() classifies (one
  // GetObjectsWithTags call for the batch + a depth-bounded interface walk per class).
  static constexpr int ANCHOR_SHAPE_RECONCILE_BUDGET = 128;

  // Per-pass cap on how many AT-RISK static holders (frontier entries with parent_tag != 0 - the
  // find-anchor-holder-eviction population) drainStaticAnchorFifo() pops for the same
  // walkStaticFieldAnchors() batch.
  static constexpr int STATIC_ANCHOR_FIFO_DRAIN = 16;

  // (Removed: the old single wrapping-index-cursor selection was replaced by tiered selection with
  // per-tier cursors — see collectStaticFieldAnchorsForRotation()'s own comment and
  // _anchor_container_cursor/_anchor_other_cursor.)

  // Cursor over the flattened (slot, tid) enumeration of _candidate_qualifying_tids above, so
  // walkCandidateThreadLocals()'s THREAD_WALK_MAX_ANCHORS-per-pass cap rotates fairly instead of
  // always walking the same first candidates' tids.
  int _thread_walk_anchor_cursor;

  // Per-pass cap on how many EXPANDED entries collectLeakAccumulationCandidatesForRotation()
  // re-queues - see that method's own comment.
  static constexpr int LEAK_ACCUMULATION_ROTATION_BUDGET = 16;

  // Snapshot of gcFinishEpoch() as of the end of the last pass.
  u64 _last_pass_gc_finish_epoch;

  // OS::nanotime() as of the end of the last pass. Written by runPass() on the BFS thread; also
  // read cross-thread by buildAbandonedEvent()'s elapsed-time calculation, so
  // volatile/load()-accessed like _search_state above.
  volatile u64 _last_pass_ns;

  // Total passes run this search. Written by runPass() on the BFS thread; read cross-thread by
  // passesRun()/buildAbandonedEvent(), so volatile/ load()-accessed like _search_state above.
  volatile int _passes_run;

  // Resolved reference chains, keyed by the leak-candidate klass_id pollWatchedTargets()
  // reconstructed each one for.
  struct CachedChain {
    ReferenceChainEvent event;
    jlong source_tag;
    u64 source_search_ns;
  };
  // Bounded by the number of discovered instances across all candidate slots:
  // MAX_LEAK_CANDIDATES_FROM_LT * MAX_DISCOVERED_INSTANCES_PER_CLASS = 5 * 8 = 40, plus up to 5
  // canary chains.
  static constexpr int MAX_RESOLVED_CHAINS = 128;
  // Keyed by frontier tag (individual instance identity), NOT by klass_id.
  std::unordered_map<jlong, CachedChain> _resolved_chains;
  SpinLock _resolved_chains_lock;

  // Abandoned-search events awaiting Profiler::dump() (profiler.cpp).
  static constexpr int MAX_PENDING_ABANDONED_EVENTS = 16;
  std::vector<ReferenceChainAbandonedEvent> _pending_abandoned_events;
  SpinLock _pending_abandoned_events_lock;

  // leaky bucket over the wall-clock cost of past searches, gating how soon a *restarted* search
  // may take its first pass - see PainBudget's own comment (painBudget.h) and canAffordNewSearch()
  // below.
  PainBudget _safepoint_pain_budget;
  // Cached refill rate from start(), reused by resetSearchStateForTest() so a test reset rebuilds
  // the budget with the same rate.
  double _pain_budget_refill_rate = 0.0;
  u64 _search_pain_ms;

  // Non-safepoint CPU-time pain budget: gates shouldRunPass() independently of both
  // _safepoint_pain_budget above (which only cools down *restarts*, spent once per finished search)
  // and _pause_pid's per-pass signal (updatePacing(), now fed only the genuine in-safepoint portion
  // of each pass - see runPass()'s own comment).
  PainBudget _cpu_pain_budget;

  // The cache above is mutated on this tracker's own BFS scheduling thread (pollWatchedTargets())
  // and read on whatever thread calls Profiler::dump() (drainPendingChainEvents());
  // _resolved_chains_lock (declared with the cache) is the only synchronization between them.

  // Fallback cadence between passes.
  static constexpr u64 PASS_CADENCE_NS = 1000000000ULL; // 1s

  // Heap-wide time-to-OOM urgency threshold (LivenessTracker::secondsToOOM()) - hasLeakSignal()
  // below forces a search to start immediately once the projection drops under this, rather than
  // waiting for a klass to clear selectLeakCandidates()'s own per-klass ring-fill/hysteresis gate
  // (KLASS_POPULATION_MIN_FILL_FOR_TREND plus LEAK_TREND_HYSTERESIS_BASE/ CORROBORATED epochs,
  // livenessTracker.h).
  static constexpr double OOM_URGENT_THRESHOLD_S = 300.0; // 5 minutes

  // Release side of OOM_URGENT_THRESHOLD_S's hysteresis (see _urgent_latched).
  static constexpr double OOM_URGENT_RELEASE_S = 2 * OOM_URGENT_THRESHOLD_S;
  static constexpr int URGENT_RELEASE_CONSECUTIVE = 5;

  // Horizon over which threadLoop() ramps the pause target and cadence toward their urgent ceilings
  // as secondsToOOM() falls, once it reports a confirmed rising trend (see secondsToOOM()'s own
  // NOT_RISING gate — a non-negative value already means real growth, not noise).
  static constexpr double OOM_RAMP_START_S = 1800.0; // 30 minutes

  // Ceilings the pause target and cadence ramp toward as secondsToOOM() approaches zero within
  // OOM_RAMP_START_S: the ramp is exponential (slow near OOM_RAMP_START_S out, aggressive near OOM)
  // since the process is likely to die anyway and diagnostic data collected right before that is
  // worth spending STW time and CPU on.
  static constexpr long URGENT_PAUSE_TARGET_MS = 100; // ceiling STW ms per pass
  static constexpr u64 URGENT_CADENCE_NS = 10000000ULL;  // 10ms floor between passes

  // True when LivenessTracker::secondsToOOM() projects exhaustion sooner

  // Auto-scaled default for _first_pass_budget when Arguments::_reference_chains_first_pass_budget
  // is unset (0) - see _first_pass_budget's own comment for why plain _budget is the wrong
  // fallback.
  static constexpr int AUTO_FIRST_PASS_BUDGET_MULTIPLIER = 50;
  static constexpr int AUTO_FIRST_PASS_BUDGET_CAP = 200000;

  // Minimum wall-clock gap between root/stack-ref enumeration attempts (runPassManualWalk()'s
  // IterateOverReachableObjects call) after the search's own first pass.
  static constexpr u64 ROOT_ENUM_MIN_INTERVAL_NS = 2000000000ULL; // 2s

  // Pause-time pacing controller: bounds and conversion constants for updatePacing()'s
  // budget/cadence adjustment - see that method's own comment for the full mechanism.
  static constexpr int MIN_EFFECTIVE_BUDGET = 2000;

  // Bounds for _effective_cadence_ns. The lower bound is not 0: threadLoop() sleeps for exactly
  // this many nanoseconds each loop iteration (below), so a true 0 would busy-loop the BFS thread.
  static constexpr u64 MIN_EFFECTIVE_CADENCE_NS = 10000000ULL;      // 10ms
  static constexpr u64 MAX_EFFECTIVE_CADENCE_NS = PASS_CADENCE_NS * 4; // 4s

  // Conversion factor from "edges of budget signal updatePacing()'s clamp could not absorb" to a
  // cadence adjustment in nanoseconds - the two are different units (edge count vs.
  static constexpr u64 CADENCE_NS_PER_EDGE_OVERFLOW = 1000000ULL; // 1ms/edge

  // Budget-borrowing (see _borrowed_budget's own comment): how many consecutive
  // comfortably-under-target passes (BORROW_UNDER_TARGET_FRACTION) must be observed before
  // updatePacing() starts growing _borrowed_budget at all.
  static constexpr int BORROW_WARMUP_PASSES = 5;

  // Budget-borrowing: a pass counts toward BORROW_WARMUP_PASSES/keeps _borrowed_budget only when
  // pass_ms is at most this fraction of _pause_target_ms - deliberately stricter than merely "under
  // the ceiling" (which the ordinary _effective_budget clamp already guarantees), so growth is
  // gated on *comfortable* headroom, not on shaving the pass in just under the wire.
  static constexpr double BORROW_UNDER_TARGET_FRACTION = 0.5;

  // Budget-borrowing: hard cap on how far updatePacing() may grow (_budget + _borrowed_budget)
  // above _budget alone - _borrowed_budget itself is clamped so the resulting ceiling never exceeds
  // _budget * BORROW_CEILING_MULTIPLIER.
  static constexpr int BORROW_CEILING_MULTIPLIER = 4;

  // Budget-borrowing: fraction of _budget by which _borrowed_budget grows on each pass once
  // BORROW_WARMUP_PASSES has been reached - a fraction of the configured budget rather than of the
  // current borrowed amount, so growth stays linear (predictable, boundable within a known number
  // of passes) rather than compounding.
  static constexpr double BORROW_GROWTH_FRACTION = 0.25;

  // Agent-owned BFS thread; startThread()/stopThread() own its lifecycle.
  pthread_t _thread;
  // std::atomic<bool> rather than plain volatile bool - volatile alone gives no C++ memory-model
  // acquire/release guarantees (it only prevents the compiler from eliding/reordering that one
  // variable's own accesses), so a weakly-ordered CPU (e.g. arm64) could let the BFS thread's
  // stopThread()- side write (see stopThread()'s own comment) become visible to threadLoop() later
  // than intended, missing the shutdown request on one wakeup and sleeping/looping an extra cycle
  // before pthread_join() unblocks it.
  std::atomic<bool> _running;

  // Cooperative-cancellation flag for an in-flight JVMTI FollowReferences walk: stopThread() sets
  // this before pthread_kill()/pthread_join() (that signal alone cannot interrupt a call already
  // inside the JVM/JVMTI implementation), and heapReferenceCallback() checks it on every
  // invocation, aborting the walk within one callback rather than letting pthread_join() block
  // until the walk finishes on its own - see both methods' own comments.
  std::atomic<bool> _abort_pass_requested;

  // Wall-clock deadline for the pass currently in flight (OS::nanotime() ticks; 0 = no deadline).
  u64 _pass_deadline_ns = 0;

  // Last time root/stack-ref enumeration actually ran (OS::nanotime() ticks; 0 before the search's
  // first pass).
  u64 _last_root_enum_ns = 0;

  // Set true when the most recent root/stack-ref enumeration attempt ended via BUDGET_EXHAUSTED
  // (not FRONTIER_CAP_HIT, which stops admitting new frontier entries but leaves the search RUNNING
  // - see runPass()'s frontier_cap_hit handling) - runPass() treats this as grounds to retry root
  // enumeration on the very next pass regardless of ROOT_ENUM_MIN_INTERVAL_NS, so a
  // still-incomplete attempt is not left waiting out the full interval before continuing.
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

  // Runs a pass when the GC-finish epoch advanced or the cadence elapsed.
  bool shouldRunPass(u64 now_ns);

  // Cheap probe (max=1, not the real poll pollWatchedTargets() makes) into LivenessTracker's
  // population-trend table: true if at least one klass shows a positive population slope worth
  // chasing.
  bool hasLeakSignal();

  // Latched, hysteretic view of LivenessTracker::secondsToOOM() crossing OOM_URGENT_THRESHOLD_S -
  // see _urgent_latched for the latch/release rules and why the raw comparison flaps.
  bool isUrgent() const;

  // Search restart gate (this class's own header comment): true once _safepoint_pain_budget has
  // drained back to zero (canStartNow()) *and* hasLeakSignal() above reports at least one leak
  // candidate.
  bool canAffordNewSearch(u64 now_ns);

  // Resets every per-search field back to its just-constructed value so the next runPass() call
  // takes the "first pass of a search" branch again, exactly like a fresh ReferenceChainTracker
  // would.
  void restartSearch();

  // Marks every entry still queued in _pending_expand EXPANDED and drains the queue.
  void markAllFrontierExpanded();

  // Resolves pending frontier entries via GetObjectsWithTags (dead objects prune for free), then
  // expands each with FollowReferences.
  void expandFrontier(jvmtiEnv *jvmti, JNIEnv *jni, int hop_cap, int budget,
                       int *edges_admitted, bool *truncated,
                       bool *frontier_cap_hit, u64 *safepoint_ticks);

  // Static-field counterpart to heapRootCallback()'s GC-root enumeration:
  // IterateOverReachableObjects's root/stack-ref callbacks never report a class's static fields
  // (there is no jvmtiHeapRootKind for STATIC_FIELD - translateHeapRootKind()'s own comment), so
  // without this call an object retained only via `SomeClass.staticField` is never discovered by
  // either root enumeration or expandFrontier() (which only descends from already-admitted,
  // non-class frontier entries - class objects are never admitted, see heapReferenceCallback()'s
  // own comment).
  void admitStaticFieldRoots(jvmtiEnv *jvmti, JNIEnv *jni, int hop_cap,
                              int budget, int *edges_admitted,
                              bool *truncated, bool *frontier_cap_hit,
                              bool *cycle_complete, u64 *safepoint_ticks);

  // Clears every live JVMTI tag this search still owns; frontier metadata is kept so
  // reconstructChain() keeps working.
  bool releaseSearchTags(jvmtiEnv *jvmti, JNIEnv *jni);

  // Feeds the measured pass duration into _pause_pid and rescales the effective budget and
  // cadence; _budget remains the hard ceiling.
  void updatePacing(u64 pass_wall_ticks);

  // Root/stack-ref enumeration passes never reach updatePacing() (runPass()'s own comment: their
  // fixed dispatch cost would wrongly throttle _effective_budget for every unrelated later pass),
  // but a slow one still spends real pause-time-SLO budget the borrow ceiling promised was safe to
  // hand out.
  void maybeRevokeBorrowForRootEnumPass(u64 pass_wall_ticks);

  // Tags every not-yet-tagged loaded class (GetLoadedClasses()) with a fresh nextClassTag() and
  // resolves its name into _class_tags, via the same GetClassSignature + normalizeClassSignature +
  // Profiler::lookupClass sequence ObjectSampler::recordAllocation() already uses
  // (objectSampler.cpp:76-90) - reusing that normalization helper rather than re-deriving it.
  void resolveLoadedClasses(jvmtiEnv *jvmti, JNIEnv *jni);

  // jvmtiHeapReferenceCallback for runPass()'s FollowReferences call (see runPass() below for the
  // full walk).
  static jint JNICALL heapReferenceCallback(
      jvmtiHeapReferenceKind reference_kind,
      const jvmtiHeapReferenceInfo *reference_info, jlong class_tag,
      jlong referrer_class_tag, jlong size, jlong *tag_ptr,
      jlong *referrer_tag_ptr, jint length, void *user_data);

  // Outcome of admitObject() below - lets each of its two call sites (heapReferenceCallback() above
  // and the IterateOverReachableObjects root/ stack-ref callbacks, both in referenceChains.cpp)
  // translate the same admission decision into its own callback-shape-appropriate return
  // value/truncation flag, instead of duplicating the decision twice.
  enum class AdmitResult {
    ALREADY_ADMITTED, // *tag_ptr != 0: nothing to do, not a truncation
    HOP_CAP,          // depth >= hop_cap: not admitted, not a truncation
    BUDGET_EXHAUSTED,  // edges_admitted >= budget: this pass's cap
    FRONTIER_CAP_HIT,  // FrontierTable::insert() itself is full: stops
                       // admitting new entries but does not itself abandon the search (see
                       // runPass()'s frontier_cap_hit handling - the no-progress detector abandons
                       // only if the frontier then stops growing)
    ADMITTED,
  };

  // First-discovery admission core: factored out of heapReferenceCallback()'s inline admission
  // branch so the manual-walk driver's root/stack-ref callbacks stay in sync with FollowReferences'
  // own admission by construction, not by copy-paste.
  AdmitResult admitObject(FrontierTable *frontier, int hop_cap, int budget,
                           int *edges_admitted, jlong *tag_ptr,
                           jlong parent_tag, u32 referrer_klass, u32 depth,
                           u8 root_kind, jlong class_tag,
                           bool priority = false,
                           jint edge_field_index = -1, u8 edge_kind = 0,
                           jlong edge_referrer_class_tag = 0);

  // Called by admitObject() on every successful ADMITTED result (root or non-root, ordinary or
  // priority) - the single shared admission path, so this needs no duplicate call site at
  // heapReferenceCallback()/ heapRootCallback()/stackRefCallback().
  void trackLeakAccumulation(FrontierTable *frontier, jlong class_tag,
                              jlong parent_tag, jlong tag);

  // Record a discovered instance for a watched candidate class: store its frontier tag in the
  // class's discovery slots so pollWatchedTargets() can build its chain event.
  void buildDiscoveredInstanceChains(jvmtiEnv *jvmti, JNIEnv *jni,
                                    u32 klass_id, u64 current_search_ns);

  void recordDiscoveredInstance(u32 klass_id, jlong frontier_tag,
                                bool leak_correlated);

  // Correlate a leak tag with an instance the BFS admitted BEFORE tagLeakInstances() tagged it (its
  // JVMTI tag is a frontier tag, its frontier entry has leak_tag == 0).

  // One-time retroactive catch-up for a klass_id the moment it FIRST enters _watched_leak_klass_ids
  // (pollWatchedTargets() calls this only for the newly-added ids in each refresh, never for ones
  // already being watched).
  void seedLeakAccumulationForNewlyWatchedKlass(u32 klass_id);

  // Upgrades root_kind when a rediscovered heap root is more durable; testable without a JVMTI mock.
  bool maybeUpgradeRootAttachedRootKind(FrontierTable *frontier, jlong tag,
                                        u8 new_root_kind);

  // True if `tag` is already sitting in _priority_expand - either queued earlier this same pass by
  // the other rotation collector, or left over from a prior pass's truncated batch
  // (expandFrontier() leaves those at the front of the queue for a later retry rather than popping
  // them).
  bool isQueuedForRotation(jlong tag) const {
    return _priority_expand_set.contains(tag);
  }

  // Re-queues transient-rooted expanded entries so a durable root can supersede a stale
  // attribution.
  std::vector<jlong> collectStaleRootKindEntriesForRotation(int max_count);

  // Bounded rotating re-expansion for stale mutable fields: expandFrontier() observes an object's
  // outgoing references exactly once (on the FollowReferences call that marks it EXPANDED) and
  // never revisits it, so a field that is later reassigned to point at a different object - e.g.
  // HashMap.table on resize - has its new value permanently unobserved once the map itself is
  // EXPANDED; the old table array's own frontier entry eventually resolves to a dead object via
  // GetObjectsWithTags and gets silently cleared with zero children, orphaning everything only
  // reachable through the *current* table.
  std::vector<jlong> collectStaleExpandedEntriesForRotation(int max_count);

  // Bounded rotating re-expansion targeting the accumulation point of a klass LivenessTracker has
  // flagged as growing (LivenessTracker:: topKlassesByGenerationCount(), _watched_leak_klass_ids) -
  // the design's actual targeted tier.
  std::vector<jlong> collectLeakAccumulationCandidatesForRotation(
      int max_count);

  // CANDIDATE-SCOPED REACH: bounded descend walk from an anchor object.
  void descendFromAnchor(jvmtiEnv *jvmti, JNIEnv *jni, jobject anchor,
                         jlong anchor_tag, u32 anchor_depth,
                         jlong anchor_descend_class_tag, int budget,
                         int *edges_admitted, bool *truncated,
                         bool *frontier_cap_hit, u64 *safepoint_ticks);

  // Prong 1 of the candidate-scoped reach design (thread-retained taxonomy: ThreadLocal-held caches
  // and thread-owned collections): per pass, walk up to THREAD_WALK_MAX_ANCHORS of the current
  // candidates' qualifying tids' live Thread objects (registerThreadObject()'s map above) with
  // descendFromAnchor() (anchor-gated to ThreadLocalMap, see above).
  void walkCandidateThreadLocals(jvmtiEnv *jvmti, JNIEnv *jni, int budget,
                                 int *edges_admitted, bool *truncated,
                                 bool *frontier_cap_hit, u64 *safepoint_ticks);

  // Selects root-attached durable entries with a tiered cursor: leak-tagged, fresh, container-shaped,
  // then everything else fairly.
  std::vector<jlong> collectStaticFieldAnchorsForRotation(int max_count);
  // At-risk anchor push: deduped, capped, and quota-limited per klass.
  void pushAtRiskStaticAnchor(jlong tag, u32 klass_id);
  // Add `tag` to _static_anchor_index if its root_kind is a durable anchor-tier kind (STATIC_FIELD
  // or JNI_GLOBAL).
  void addToStaticAnchorIndex(jlong tag, jlong own_class_tag, u8 root_kind);

  // True iff `klass` implements java/util/Collection or java/util/Map, directly or transitively
  // (superclass chain + interfaces of every visited class, depth-bounded, visited set to survive
  // interface diamonds).
  bool classImplementsContainerOrMap(jvmtiEnv *jvmti, JNIEnv *jni,
                                     jclass klass);

  // Resolve _collection_iface_class_tag/_map_iface_class_tag once; returns false if the interfaces
  // cannot be resolved yet (leaves them at -1 so the next call retries).
  bool resolveContainerInterfaceTags(jvmtiEnv *jvmti, JNIEnv *jni);

  // Lazy shape reconciliation for the anchor index: scans _static_anchor_own_class_tags for class
  // tags not yet in _class_shape_cache, resolves up to ANCHOR_SHAPE_RECONCILE_BUDGET of them per
  // pass via one GetObjectsWithTags call (class objects are tagged with their class tags) and
  // classifies each.
  void reconcileAnchorClassShapes(jvmtiEnv *jvmti, JNIEnv *jni);
  // Pops up to max_count AtRiskAnchor entries off _static_anchor_fifo's front into `out`
  // (appending), decrementing each popped entry's class occupancy in
  // _static_anchor_fifo_klass_counts (erased at zero, so the map tracks the FIFO's live contents),
  // and re-derives the set from the deque's remaining contents (PriorityExpandSet's tombstone-free
  // rebuildFrom contract).
  int drainStaticAnchorFifo(int max_count, std::vector<AtRiskAnchor> &out);
  // Pushes `entries` back to _static_anchor_fifo's FRONT in reverse order (preserving FIFO order),
  // re-incrementing each entry's class occupancy, and rebuilds the set - the truncated-walk requeue
  // path.
  void requeueStaticAnchorFifoFront(const std::vector<AtRiskAnchor> &entries);
  // When non-null, receives the tags of RESOLVED-but-unwalked anchors at the truncation break point
  // - GetObjectsWithTags may return fewer anchors than requested (dead tags drop out) in its own
  // order, so the caller cannot recover the un-walked set from a consumed index; the walk hands the
  // exact tags back instead.
  void walkStaticFieldAnchors(jvmtiEnv *jvmti, JNIEnv *jni,
                              const std::vector<jlong> &anchor_tags,
                              int budget, int *edges_admitted, bool *truncated,
                              bool *frontier_cap_hit, u64 *safepoint_ticks,
                              std::vector<jlong> *unwalked = nullptr);

  // jvmtiHeapRootCallback/jvmtiStackReferenceCallback for runPassManualWalk()'s
  // IterateOverReachableObjects call (referenceChains.cpp).
  static jvmtiIterationControl JNICALL
  heapRootCallback(jvmtiHeapRootKind root_kind, jlong class_tag, jlong size,
                    jlong *tag_ptr, void *user_data);
  static jvmtiIterationControl JNICALL stackRefCallback(
      jvmtiHeapRootKind root_kind, jlong class_tag, jlong size,
      jlong *tag_ptr, jlong thread_tag, jint depth, jmethodID method,
      jint slot, void *user_data);

  // Manual-walk pass driver: when `run_root_enum` is true, seeds/refreshes root-attached frontier
  // entries via IterateOverReachableObjects (heapRootCallback()/stackRefCallback() above) using
  // `root_enum_budget`; then, regardless of `run_root_enum`, drains _pending_expand via
  // admitStaticFieldRoots()/expandFrontier() up to `expand_budget`.
  void runPassManualWalk(jvmtiEnv *jvmti, JNIEnv *jni, bool run_root_enum,
                          int root_enum_budget, int expand_budget,
                          int *edges_admitted, bool *truncated,
                          bool *frontier_cap_hit, u64 *safepoint_ticks);

  // Inserts (or refreshes) klass_id's resolved chain in _resolved_chains, recording the
  // source_tag/source_search_ns it was reconstructed from so a later poll can tell a stale entry
  // from a current one.
  bool cacheResolvedChain(jlong source_tag, ReferenceChainEvent &&event,
                          jlong source_tag_val, u64 source_search_ns);

  // Remove a cached chain so pollWatchedTargets rebuilds it on the next poll.
  void invalidateResolvedChain(jlong source_tag);

  // Snapshots the just-abandoned search into _pending_abandoned_events - called from runPass()
  // (referenceChains.cpp) immediately after it writes SearchState::ABANDONED, while
  // buildAbandonedEvent()'s source fields are still valid (see _pending_abandoned_events' own
  // comment for why this cannot be deferred to dump()-time).
  void enqueuePendingAbandonedEvent();

public:
  static ReferenceChainTracker *instance() {
    static ReferenceChainTracker instance;
    return &instance;
  }

  // tid -> java.lang.Thread global-ref registry (see _thread_objects).
  void registerThreadObject(JNIEnv *jni, int tid, jthread thread);
  void unregisterThreadObject(JNIEnv *jni, int tid);

  // Delete the global refs unregisterThreadObject() queued in _thread_refs_pending_delete (see that
  // member's comment for why the deletion is deferred).
  void releaseEndedThreadRefs(JNIEnv *jni);

  // Recording-stop cleanup: delete EVERY remaining registered Thread global ref (dead threads'
  // queued refs first, then the live registry) and empty the registry.
  void releaseAllThreadObjects(JNIEnv *jni);

  // One-time sweep over the JVM's CURRENTLY LIVE threads at recording start, registering each into
  // the same tid -> Thread-object registry via JVMThread::nativeThreadId().
  void registerExistingThreads(jvmtiEnv *jvmti, JNIEnv *jni);

  // Correlate a leak tag with an instance the BFS admitted BEFORE tagLeakInstances() tagged it (its
  // JVMTI tag is a frontier tag, its frontier entry has leak_tag == 0).
  bool correlateAdmittedLeakTag(jlong frontier_tag, jlong leak_tag,
                                u32 klass_id);

  // Abandon the search after this many consecutive passes with zero new frontier entries admitted
  // (genuinely stuck, not just slow).
  static constexpr int NO_PROGRESS_PASS_LIMIT = 30;

  // Base limit for the canary-specific stuck detector: candidate-discovery must show no progress
  // (no change to _candidate_found_bits, no new candidate admitted into a slot) for this many
  // consecutive passes AND the whole-graph frontier must also have stalled for
  // NO_PROGRESS_PASS_LIMIT passes (see runPass()'s CANARY_STUCK branch) before a canary search is
  // abandoned.
  static constexpr int CANARY_NO_PROGRESS_PASS_LIMIT = 30;

  // Upper bound on how many times canaryStuckPassLimit() doubles the base limit (2^8 = 256x -> 7680
  // passes at the default base of 30) - bounds the escalation so a search that is ACTUALLY stuck
  // forever (as opposed to merely deep) still gets abandoned in finite time rather than growing its
  // patience without limit.
  static constexpr int MAX_CANARY_STUCK_BACKOFF_SHIFT = 8;

  // The canary-stuck pass limit for the *current* restart attempt: CANARY_NO_PROGRESS_PASS_LIMIT
  // doubled once per consecutive CANARY_STUCK restart of this candidate-chase sequence, capped at
  // MAX_CANARY_STUCK_BACKOFF_SHIFT doublings.
  int canaryStuckPassLimit() const {
    return CANARY_NO_PROGRESS_PASS_LIMIT
           << std::min(_canary_stuck_restart_count,
                        MAX_CANARY_STUCK_BACKOFF_SHIFT);
  }

  // Multiplier cap for the canary lane's work-scaled backoff (see _canary_backoff_mult's own
  // comment).
  static constexpr int CANARY_BACKOFF_MULT_MAX = 16;

  // While a canary search has candidates still unresolved, shouldRunPass() raises
  // _cpu_pain_budget's refill rate by this factor (capped at 100%/wall-clock).
  static constexpr double CANARY_PAIN_BUDGET_REFILL_MULTIPLIER = 100.0;

  // Coverage tracking: how many leak tags have been assigned vs resolved.
  int _leak_tags_assigned = 0;
  int _leak_tags_resolved = 0;

  // Leak tags are positive JVMTI tags in a dedicated range, assigned by LivenessTracker's tag pool
  // to specific tracked leaking objects.
  static constexpr jlong LEAK_TAG_BASE = 0x40000000LL;
  static constexpr int LEAK_TAG_POOL_SIZE = 256;

  // Check whether a JVMTI tag is a leak tag (from LivenessTracker's pool).
  static bool isLeakTag(jlong tag) {
    return tag >= LEAK_TAG_BASE && tag < LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE;
  }

  // Max candidates LivenessTracker::selectLeakCandidates() can return.

  // Test accessor for _passes_since_last_progress.
  int passesSinceLastProgressForTest() const { return _passes_since_last_progress; }
  // Canary-lane backoff state - see _canary_backoff_mult's own comment.
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
  void setCandidateParentTagForTest(int idx, jlong tag) { _candidate_parent_tags[idx] = tag; }
  void setCandidateReferrerKlassForTest(int idx, u32 klass_id) {
    _candidate_referrer_klasses[idx] = klass_id;
  }
  void setCandidateDepthForTest(int idx, u32 depth) { _candidate_depths[idx] = depth; }
  int passesSinceLastCandidateProgressForTest() const { return _passes_since_last_candidate_progress; }
  int canaryStuckRestartCountForTest() const { return _canary_stuck_restart_count; }

  ReferenceChainTracker(const ReferenceChainTracker &) = delete;
  ReferenceChainTracker &operator=(const ReferenceChainTracker &) = delete;

  Error start(Arguments &args);

  // Scales unset referencechains defaults (budget, ttl, framecap, pausetarget, painbudget,
  // firstpassbudget) from the process's max heap size and available processor count, so a large
  // heap doesn't starve the BFS (the defaults are tuned for a small heap and abandon via TTL before
  // making meaningful progress).
  void autoTuneDefaults(Arguments &args);
  void stop();

  // Spawns the BFS thread (threadEntry()/threadLoop()) if reference chain tracking is enabled and
  // no thread is already running.
  void startThread();

  // Stops and joins the BFS thread started by startThread(), mirroring BaseWallClock::stop()'s
  // pthread_kill(WAKEUP_SIGNAL) + pthread_join() shape (wallClock.cpp) - WAKEUP_SIGNAL is already
  // installed unconditionally in vmEntry.cpp, so no extra signal setup is needed here.
  void stopThread();

  bool enabled() const { return _enabled; }

  u64 gcStartEpoch() { return load(_gc_start_epoch); }
  u64 gcFinishEpoch() { return load(_gc_finish_epoch); }

  // JVMTI tag helpers used by the heap-walk callbacks.
  jlong nextTag() { return atomicIncRelaxed(_next_tag, (jlong)1); }

  // Serializes runPass()+pollWatchedTargets() between threadLoop() and the test seams - see
  // runPassForTest()'s comment.
  Mutex _engine_lock;
  jlong tagObject(jvmtiEnv *jvmti, jobject obj);
  jlong getTag(jvmtiEnv *jvmti, jobject obj);
  void clearTag(jvmtiEnv *jvmti, jobject obj);

  // Hands out a fresh negative class tag, from the shared, process-wide counter both this class and
  // LivenessTracker mint from - see classTagAllocator.h's own header comment for why this must be
  // shared rather than a private counter here.
  jlong nextClassTag() { return ClassTagAllocator::next(); }

  // Returns the frontier metadata table, or nullptr if the subsystem was never started with the
  // flag enabled.
  FrontierTable *frontierTable() { return _frontier; }

  // Returns the class-tag resolution table. Exposed for testing in isolation, matching
  // frontierTable()'s existing rationale.
  ClassTagTable *classTags() { return &_class_tags; }

  // Runs exactly one bounded BFS pass and returns. The first call for a search seeds
  // FollowReferences from the heap roots (heap_filter=0, klass=NULL, initial_object=NULL - see this
  // method's own comment in referenceChains.cpp for why FollowReferences rather than
  // IterateThroughHeap); every later call resumes from the persisted frontier via expandFrontier()
  // instead of re-walking from the roots (see expandFrontier()'s comment for why - re-walking from
  // the roots each call would re-traverse the entire already-discovered subgraph every pass,
  // defeating the point of a per-pass budget).
  bool runPass(jvmtiEnv *jvmti, JNIEnv *jni, bool *out_truncated = nullptr);

  // Serialized entry points for the two engine drivers: the real BFS thread (threadLoop(), below)
  // and the debug seams (javaApi.cpp's runReferenceChainPass0()/pollReferenceChainTargets0()).
  bool runPassSerialized(jvmtiEnv *jvmti, JNIEnv *jni) {
    MutexLocker engine_guard(_engine_lock);
    return runPass(jvmti, jni);
  }

  void pollWatchedTargetsSerialized(jvmtiEnv *jvmti, JNIEnv *jni) {
    MutexLocker engine_guard(_engine_lock);
    pollWatchedTargets(jvmti, jni);
  }

  // Search-level outcome (SearchState's constants) - see runPass()'s comment for exactly when this
  // leaves RUNNING.
  u8 searchState() { return loadAcquire(_search_state); }

  // Total passes run for the current/most recent search. Exposed for tests to confirm multi-pass
  // resumption actually happened.
  int passesRun() { return load(_passes_run); }

  // Which SearchAbandonReason cutoff moved the search out of RUNNING, or SearchAbandonReason::NONE
  // if it never left RUNNING or left via SearchState::COMPLETED instead.
  u8 abandonReason() { return load(_abandon_reason); }

  // Reference-chain JFR event surface: fills *out from frontierTable()->
  // reconstructChain(target_tag, ...) (see that method's own comment for the leaf-to-root ordering
  // and the parent_tag walk it performs).
  void resolveHopEdgeLabel(jvmtiEnv *jvmti, JNIEnv *jni, ChainHopEdge edge,
                           char *out, size_t out_cap);

  // Fills *out with one label per chain hop, aligned with the chain's leaf-to-root order (edges[i]
  // = the retention edge INTO chain[i]), via resolveHopEdgeLabel() above.
  static constexpr size_t MAX_HOP_EDGE_LABEL =
      MAX_REFERENCE_CHAIN_EDGE_LABEL;
  // Per-referrer-class ordinal->name list cache behind resolveHopEdgeLabel(): decoding the spec
  // ordinal requires walking the class's whole interface closure + superclass chain (GetClassFields
  // + GetFieldName per field), and chains re-emit on every dump, so the decoded ordinal space of
  // each chain-relevant class is built once here.
  static constexpr size_t HOP_LABEL_CLASS_CACHE_CAP = 1024;
  struct HopLabelClass {
    jlong class_tag;
    // One entry per ordinal in the class's flattened field space - the i-th element is the name of
    // ordinal i.
    std::vector<std::string> field_names;
    bool decode_failed;
  };
  std::unordered_map<jlong, HopLabelClass> _hop_label_cache;

  // Cache lookup/decode behind resolveHopEdgeLabel() - see HopLabelClass's own comment.
  const HopLabelClass *hopLabelClassFor(jvmtiEnv *jvmti, JNIEnv *jni,
                                        jlong class_tag);

  void fillHopEdgeLabels(jvmtiEnv *jvmti, JNIEnv *jni,
                         const std::vector<ChainHopEdge> &edges,
                         std::vector<ReferenceChainHop> *out);

  bool buildChainEvent(jvmtiEnv *jvmti, JNIEnv *jni, jlong target_tag,
                       ReferenceChainEvent *out);

  // Appends the root TYPE element (the declaring class, resolved from
  // FrontierEntry::referrer_class_tag) to a static-field-rooted chain - see the definition's
  // comment in referenceChains.cpp for the full rationale and the skip conditions.
  void appendStaticFieldRootType(const FrontierEntry &terminal,
                                 std::vector<u32> *chain,
                                 std::vector<ChainHopEdge> *edges);

  // Canary-search chain reconstruction: builds the chain for a canary candidate from the
  // per-candidate chain link recorded at pruning time (_candidate_parent_tags[] etc.), walking
  // parent_tag through the frontier table (positive tags, so lookup() works).
  bool buildCanaryChainEvent(int candidate_idx, ReferenceChainEvent *out);

  // Reports a search's termination state without needing a target tag.
  bool buildAbandonedEvent(ReferenceChainAbandonedEvent *out) {
    // Acquire-load, not a plain relaxed load - see searchState()'s own comment for why: this is the
    // same guard-then-read-details pattern.
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

  // Bridges LivenessTracker leak candidates into cached ReferenceChain events; reads the existing
  // tag, never seeds one.
  void pollWatchedTargets(jvmtiEnv *jvmti, JNIEnv *jni);

  // Targeted holder re-walk: enqueues `tag`'s chain-root entry (the root-attached ancestor of its
  // frontier chain) onto _priority_expand so the next rotation/expand pass re-walks the holder that
  // retains everything below `tag`.
  void requeueChainRootForRotation(jlong tag);

  // Appends a copy of every currently-cached resolved chain to *out, re-stamped with a fresh
  // _start_time so it lands in the dumping chunk's time window, WITHOUT clearing the cache - a
  // repeatable snapshot, not a drain, so the same live sample's chain is re-emitted into every JFR
  // chunk it survives into (see _resolved_chains' own comment).
  void drainPendingChainEvents(std::vector<ReferenceChainEvent> *out);

  // Appends every abandoned-search event queued since the last call and clears the queue - a true
  // drain, unlike drainPendingChainEvents() above: an abandoned search is a discrete past
  // occurrence, not an ongoing live sample, so there is nothing left to re-report once
  // Profiler::dump() (profiler.cpp) has emitted it.
  void drainPendingAbandonedEvents(std::vector<ReferenceChainAbandonedEvent> *out);

  static void JNICALL GarbageCollectionStart(jvmtiEnv *jvmti_env);
  static void JNICALL GarbageCollectionFinish(jvmtiEnv *jvmti_env);

  // Test seam - not part of the production API. Mirrors LivenessTracker's own "Test seams" block
  // (livenessTracker.h).
  jlong tagAsRootForTest(jvmtiEnv *jvmti, JNIEnv *jni, jobject obj);

  // Test seam - not part of the production API. Since ReferenceChainTracker is a process-wide
  // singleton (ExternalProcessReferenceChainTest's own class javadoc explains why that matters:
  // only the *first* test to ever call runPass() in a shared JVM gets a real root-seeded walk,
  // since runPass() only re-walks from the roots once per search's whole lifetime), an in-process
  // test that needs its own genuine first-ever root walk calls this at the start of its test body
  // to force exactly that - releasing any tags a previous test's search still held, then resetting
  // search/frontier state to the same "brand-new tracker" state restartSearch()
  // (referenceChains.cpp) produces, plus the target- dedup/pending-event state restartSearch()
  // itself intentionally leaves for pollWatchedTargets()/drainPendingChainEvents() to self-clear
  // (this is an immediate, out-of-band reset - there is no next real pass here to observe the
  // change and clear them the ordinary way).
  void resetSearchStateForTest(jvmtiEnv *jvmti, JNIEnv *jni);

  // Test seam - not part of the production API. Diagnostic-only: reports how far a given
  // (already-tagged) object sits from the front of _pending_expand's FIFO queue, to distinguish
  // "not yet expanded because its own FIFO position hasn't come up yet" from "already expanded" or
  // "never admitted at all" without needing a debugger.
  long pendingExpandPositionForTest(jlong tag) const;

  // Test seam - not part of the production API. Companion to pendingExpandPositionForTest() above,
  // for computing a position's fraction of the current backlog.
  size_t pendingExpandSizeForTest() const;

  // Test seam - not part of the production API. Exposes the private shouldRunPass() gate directly,
  // so a test can assert whether a fresh/terminal search would be allowed to start right now - in
  // particular, whether LivenessTracker::secondsToOOM()'s urgent-OOM bypass (hasLeakSignal(), see
  // OOM_URGENT_THRESHOLD_S's own comment above) opens this gate even with zero per-klass leak
  // candidate (confirmable in the same test via
  // LivenessTracker::selectLeakCandidates()/JavaProfiler's selectLeakCandidateKlassIds0() seam) -
  // something runReferenceChainPass0() (javaApi.cpp) cannot show, since it calls runPass() directly
  // and never consults this gate at all.
  bool shouldRunPassForTest(u64 now_ns) { return shouldRunPass(now_ns); }
};

#endif // _REFERENCECHAINS_H
