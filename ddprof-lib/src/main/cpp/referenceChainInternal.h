/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef _REFERENCECHAININTERNAL_H
#define _REFERENCECHAININTERNAL_H

#include "arch.h"
#include "common.h"
#include "referenceChains.h"
#include <cstring>
#include <jni.h>
#include <new>

class FrontierTable;

ASSERT_ONLY(extern thread_local bool t_inGCCallback;)

// Caller-side owner of one traversal group's journal lease. Callbacks only reserve/commit; the
// caller observes the return and flushes. Destruction flushes any remaining prefix, then releases
// the lease. A flush whose captured epoch is stale discards before any tag lookup.
class ReferenceChainAnchorObservationScope {
public:
  explicit ReferenceChainAnchorObservationScope(ReferenceChainTracker *tracker)
      : _tracker(tracker), _buffer(&tracker->_anchor_observations),
        _lease(_buffer->tryLease()) {
    resetStagingBudgets();
  }
  ~ReferenceChainAnchorObservationScope() {
    flush();
    _buffer->releaseLease(_lease); // no-op for a non-owning or stale scope
  }
  ReferenceChainAnchorObservationScope(const ReferenceChainAnchorObservationScope &) = delete;
  ReferenceChainAnchorObservationScope &operator=(const ReferenceChainAnchorObservationScope &) = delete;

  // Every journal operation goes through the scope's token; a non-owning scope's calls are
  // rejected by the buffer and never touch another scope's journal.
  AnchorObservationReservation reserve() { return AnchorObservationReservation(*_buffer, _lease); }
  bool containsAction(jlong tag, u8 action) {
    return _buffer->containsAction(_lease, tag, action);
  }

  // Unknown shapes can use only pending slots; confirmed containers can use the local share,
  // then a pending slot, then displace a staged unknown. The master budget bounds the scope's
  // buffer FOOTPRINT: only growing admissions spend it, so a confirmed container whose record
  // displaces a pending unknown stays admissible after the unknowns exhausted the buffer.
  bool reserveLocalStaging(jlong tag, jlong class_tag) {
    // Branch on the shape first: an exhausted budget must fail without paying
    // localHolderNeedsObservation()'s up-to-three hash lookups (this runs per local-root edge
    // inside the JVMTI enumeration callback, and the exhausted case is the saturated norm).
    auto shape = _tracker->_class_shape_cache.find(class_tag);
    const bool unclassified = shape == _tracker->_class_shape_cache.end();
    const bool confirmed_container =
        !unclassified &&
        (shape->second == (u8)ReferenceChainTracker::AnchorClassShape::CONTAINER ||
         shape->second ==
             (u8)ReferenceChainTracker::AnchorClassShape::UNKNOWN_TRUNCATED);
    if (unclassified) {
      if (_local_staging_budget == 0 || _local_pending_budget == 0 ||
          !_tracker->localHolderNeedsObservation(tag, class_tag)) {
        return false;
      }
      _local_pending_budget--;
      _local_staging_budget--;
      // The unknown this record parks in the pending buffer is itself displaceable: replay's
      // eviction replaces the oldest unknown slot with a later confirmed container, so the
      // container's own staging can spend this budget instead of being rejected.
      _local_evictable_budget++;
      return true;
    }
    if (!confirmed_container) {
      return false;
    }
    if (_local_index_budget > 0) {
      if (!_tracker->localHolderNeedsObservation(tag, class_tag)) {
        return false;
      }
      _local_index_budget--;
      _local_staging_budget--;
      return true;
    }
    if (_local_pending_budget > 0) {
      if (!_tracker->localHolderNeedsObservation(tag, class_tag)) {
        return false;
      }
      _local_pending_budget--;
      _local_staging_budget--;
      return true;
    }
    if (_local_evictable_budget > 0) {
      if (!_tracker->localHolderNeedsObservation(tag, class_tag)) {
        return false;
      }
      // Displacement: replay's eviction replaces a pending unknown with this holder, so the
      // buffer footprint is unchanged and replay can always absorb the record.
      _local_evictable_budget--;
      return true;
    }
    return false;
  }

  bool reserveAtRiskStaging(jlong tag, u32 klass_id) {
    if (_at_risk_staging_budget == 0 ||
        !_tracker->atRiskAnchorNeedsObservation(tag, klass_id) ||
        containsAction(tag, AnchorObservation::AT_RISK)) {
      return false;
    }
    auto live = _tracker->_static_anchor_fifo_klass_counts.find(klass_id);
    u32 live_count = live == _tracker->_static_anchor_fifo_klass_counts.end()
                         ? 0
                         : live->second;
    // Look the slot up WITHOUT claiming it: a rejection (table full or per-klass cap exceeded)
    // must not burn a class-set slot for the rest of the scope - a claimed-but-unused slot
    // accumulates across callbacks and can fill the fixed table, silently refusing later
    // eligible classes.
    bool found = false;
    u32 slot = findAtRiskClassSlot(klass_id, found);
    u32 staged = found ? _at_risk_class_counts[slot].count : 0;
    if (slot == AT_RISK_CLASS_SET_SLOTS ||
        live_count + staged >=
            ReferenceChainTracker::STATIC_ANCHOR_ATRISK_PER_KLASS_CAP) {
      return false;
    }
    if (!found) {
      _at_risk_class_used[slot >> 3] |=
          static_cast<u8>(1u << (slot & 7));
      _at_risk_class_counts[slot] = AtRiskClassCount{klass_id, 0};
    }
    _at_risk_class_counts[slot].count++;
    _at_risk_staging_budget--;
    return true;
  }

  void markOverflow(bool static_attachment) { _buffer->markOverflow(_lease, static_attachment); }
  bool ownsLease() const { return _lease.id != 0; }

  // Acquires the buffer lock so the caller sees the callbacks' writes; true if the journal overflowed.
  bool observeReturn() { return _buffer->observeOverflow(_lease); }

  // Replays the accepted prefix, then resets count/static-retry/overflow while keeping the lease.
  void flush() {
    const AnchorObservation *records = nullptr;
    u32 count = 0;
    bool static_retry = false;
    if (!_buffer->snapshot(_lease, &records, &count, &static_retry)) {
      return;
    }
    if (count > 0 || static_retry) {
      _tracker->replayAnchorObservations(records, count, static_retry);
    }
    _buffer->clearPrefix(_lease);
    resetStagingBudgets();
  }

private:
  static constexpr u32 AT_RISK_CLASS_SET_SLOTS =
      ReferenceChainTracker::STATIC_ANCHOR_FIFO_CAP * 2;
  static constexpr u32 AT_RISK_CLASS_SET_BITMAP_BYTES =
      AT_RISK_CLASS_SET_SLOTS / 8;
  struct AtRiskClassCount {
    u32 klass_id;
    u8 count;
  };
  static_assert((AT_RISK_CLASS_SET_SLOTS & (AT_RISK_CLASS_SET_SLOTS - 1)) == 0,
                "at-risk staging set must be a power of two");
  // This fixed table accounts staged classes without allocating in heap callbacks.
  // Twice the FIFO cap holds one distinct class per staged record at half load.

  u32 findAtRiskClassSlot(u32 klass_id, bool &found) const {
    u32 slot = klass_id * 0x9E3779B9U >> 21;
    for (u32 probes = 0; probes < AT_RISK_CLASS_SET_SLOTS; probes++) {
      bool used = (_at_risk_class_used[slot >> 3] &
                   static_cast<u8>(1u << (slot & 7))) != 0;
      if (!used) {
        found = false;
        return slot;
      }
      if (_at_risk_class_counts[slot].klass_id == klass_id) {
        found = true;
        return slot;
      }
      slot = (slot + 1) & (AT_RISK_CLASS_SET_SLOTS - 1);
    }
    found = false;
    return AT_RISK_CLASS_SET_SLOTS;
  }

  void resetStagingBudgets() {
    _local_staging_budget = _tracker->localStagingAbsorbable();
    _local_index_budget = ReferenceChainTracker::LOCAL_ANCHOR_INDEX_CAP -
                          _tracker->_local_anchor_tags.size();
    _local_pending_budget = ReferenceChainTracker::PENDING_LOCAL_ANCHOR_CAP -
                            _tracker->_pending_local_anchors.size();
    _local_evictable_budget = _tracker->_pending_local_evictable_count;
#ifdef UNIT_TEST
    if (_tracker->_local_staging_budget_override_for_test != 0) {
      _local_index_budget = _local_staging_budget;
      _local_pending_budget = _local_staging_budget;
      _local_evictable_budget = _local_staging_budget;
    }
#endif
    _at_risk_staging_budget = ReferenceChainTracker::STATIC_ANCHOR_FIFO_CAP -
                              _tracker->_static_anchor_fifo.size();
    memset(_at_risk_class_used, 0, sizeof(_at_risk_class_used));
  }

  ReferenceChainTracker *_tracker;
  AnchorObservationBuffer *_buffer;
  AnchorObservationLease _lease;
  u32 _local_staging_budget = 0;
  size_t _local_index_budget = 0;
  size_t _local_pending_budget = 0;
  size_t _local_evictable_budget = 0;
  size_t _at_risk_staging_budget = 0;
  AtRiskClassCount _at_risk_class_counts[AT_RISK_CLASS_SET_SLOTS] = {};
  u8 _at_risk_class_used[AT_RISK_CLASS_SET_BITMAP_BYTES] = {};
};

inline bool isDurableAnchorRootKind(u8 root_kind) {
  return root_kind == (u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD ||
         root_kind == (u8)JVMTI_HEAP_REFERENCE_JNI_GLOBAL;
}

// Callback branches reserve only when they can publish an anchor observation.
// Placement-new avoids moving the non-movable reservation; destruction cancels an unused slot.
class AnchorObservationReservationGuard {
public:
  AnchorObservationReservationGuard() = default;
  AnchorObservationReservationGuard(const AnchorObservationReservationGuard &) = delete;
  AnchorObservationReservationGuard &operator=(const AnchorObservationReservationGuard &) = delete;
  ~AnchorObservationReservationGuard() {
    if (_live) {
      get()->~AnchorObservationReservation();
    }
  }

  bool acquire(ReferenceChainAnchorObservationScope &scope) {
    new (&_storage) AnchorObservationReservation(scope.reserve());
    _live = true;
    return get()->held();
  }

  void commit(const AnchorObservation &record) {
    if (_live) {
      get()->commit(record);
    }
  }

private:
  AnchorObservationReservation *get() {
    return reinterpret_cast<AnchorObservationReservation *>(&_storage);
  }

  alignas(AnchorObservationReservation) unsigned char _storage[sizeof(AnchorObservationReservation)];
  bool _live = false;
};

struct ReferenceChainPassContext {
  // Required binding: the owning caller's scope; there is no unscoped immediate-mutation path.
  explicit ReferenceChainPassContext(ReferenceChainAnchorObservationScope &scope)
      : anchor_scope(scope) {}

  ReferenceChainAnchorObservationScope &anchor_scope;

  // Attempt stamps let each durable-report traversal skip its accepted prefix on retry.
  u32 root_report_attempt_id = 0;
  u32 root_report_previous_attempt_id = 0;
  bool root_report_retrying_incomplete = false;
  // The current incomplete retry sequence's first attempt id (0 outside root enumeration): the
  // recognized-stamp window in rootReportCompleted() widens to the whole sequence.
  u32 root_report_retry_base_id = 0;

  // Set with `truncated` when the journal had no room; distinct from frontier_cap_hit. The rejected
  // transition is not performed, so the source traversal obligation stays unserved.
  bool anchor_observation_overflow = false;

  // Records the overflow under the buffer lock; static_attachment requests a static-scan retry.
  void abortForObservationOverflow(bool static_attachment) {
    anchor_scope.markOverflow(static_attachment);
    anchor_observation_overflow = true;
    truncated = true;
  }

  ReferenceChainTracker *tracker;
  FrontierTable *frontier;
  int hop_cap;
  int budget;
  int edges_admitted;
  bool truncated;

  // Set only when `truncated` became true because frontier->insert() itself reported capacity
  // exhaustion, as opposed to edges_admitted reaching budget.
  bool frontier_cap_hit;

  // Immutable snapshot of the resolved-chain source tags that were cached before this synchronous
  // traversal started. Callback code uses this fixed caller-owned array to decide whether a shape
  // change needs invalidation without taking the resolved-chain cache lock.
  const jlong *resolved_chain_tags = nullptr;
  int resolved_chain_tag_count = 0;

  // ARRAY-HOLDER BATCHING: non-null only in expandFrontier() (the batch's members) and
  // admitStaticFieldRoots() (empty - reset with no members - for exactly one hop past each
  // class); null in every other walk.
  ReferenceChainBatchSet *batch = nullptr;

  // Rolling resume cursor for expandFrontier(): tracks the tag of the batch entry that is
  // currently the REFERRER of the child edges FollowReferences is delivering (updated by the
  // callback at the batch descent-gate, which also markCompleted()s the previous entry on each
  // referrer transition). HotSpot's iterate_over_array() reports every top-level batch entry
  // (referrer == the transient holder array, not a batch tag) before descending into any of
  // their children, so a top-level-visit transition cannot signal that an entry's own children
  // are done; only a change in the referrer of an admitted child edge can. An entry with zero
  // children is never marked complete; callers must be prepared to re-visit
  // it on a later pass rather than assume absence means "still has
  // unreported children".
  jlong _last_visited_batch_tag = 0;

  // Set only by admitStaticFieldRoots(): the seed holder array for that sweep holds loaded-class
  // objects (negative-tagged by resolveLoadedClasses(), see the *tag_ptr < 0 branch below), and the
  // whole point of the sweep is to walk past that holder->class edge into each class's own outgoing
  // references - chiefly STATIC_FIELD - which the *tag_ptr < 0 check would otherwise stop cold
  // before FollowReferences ever gets to report them.
  bool static_field_seed = false;

  // PER-CLASS NON-STATIC QUOTA (admitStaticFieldRoots() only).
  jlong _seed_class_tag = 0;     // negative tag of the class currently
                                // being descended (0 before the first class edge is seen)
  int _class_other_admitted = 0; // non-STATIC_FIELD edges admitted for
                                // the current class this lap
  int _class_other_cap = 0;      // per-class cap; 0 disables the quota
                                // (admit all) when not in seed sweep
  // Number of distinct classes entered so far in this chunk's descent (incremented on each
  // class-boundary tag change).
  int _classes_in_chunk_visited = 0;

  // Amortizes tracker->_pass_deadline_ns's OS::nanotime() check (heapReference
  // Callback()/heapRootCallback() run once per visited edge/root - checking wall-clock on literally
  // every call would add real overhead on a large heap) - checked only every 4096th call, local to
  // this ctx so each of runPassManualWalk()'s several sub-calls (root enum, static-field sweep,
  // expandFrontier(), rotation) starts its own count.
  int deadline_check_counter = 0;

  // True while expandFrontier() is walking a batch drawn from _priority_expand (a
  // rotation-selected, already-EXPANDED parent) rather than the ordinary _pending_expand backlog -
  // see _priority_expand's own comment.
  bool admit_priority = false;

  // DESCEND-WALK controls (descendFromAnchor()'s calls only; null/0 everywhere else, so every gate
  // below is a no-op for the ordinary walk phases): _no_descend_class_tags: exact class tags to
  // neither admit nor descend into for the duration of this walk.
  static constexpr int NO_DESCEND_CLASS_CAP = 8;
  jlong _no_descend_class_tags[NO_DESCEND_CLASS_CAP] = {0};
  int _no_descend_class_tag_count = 0;
  jlong _descent_anchor_tag = 0;
  jlong _anchor_descend_class_tag = 0;
};

#endif // _REFERENCECHAININTERNAL_H
