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
#include "vmEntry.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unordered_set>

// Candidate-scoped reach: bounded descend walks from anchor objects (see
namespace {

// Class tags to neither admit nor descend into during a descend walk (see
// ReferenceChainPassContext::_no_descend_class_tags' own comment).
const char *const kNoDescendClassNames[] = {
    "java/lang/ClassLoader", "java/lang/ThreadGroup",
    "java/security/ProtectionDomain",
};

int resolveNoDescendClassTags(jvmtiEnv *jvmti, JNIEnv *jni,
                               jlong *out, int cap) {
  int count = 0;
  for (const char *name : kNoDescendClassNames) {
    if (count >= cap) {
      break;
    }
    jclass cls = jni->FindClass(name);
    if (cls == nullptr) {
      // Not loadable in this JVM (e.g. java.security classes stripped by a minimal runtime) - skip;
      // the gate simply does not cover it.
      jni->ExceptionClear();
      continue;
    }
    jlong tag = 0;
    if (jvmti->GetTag(cls, &tag) == JVMTI_ERROR_NONE && tag != 0) {
      out[count++] = tag;
    }
    jni->DeleteLocalRef(cls);
  }
  return count;
}

// java.lang.ThreadLocal$ThreadLocalMap's class tag for walkCandidateThreadLocals()'s anchor gate
// (see ReferenceChainPassContext:: _anchor_descend_class_tag's own comment): the value type of BOTH
// of Thread's threadLocals and inheritableThreadLocals fields, and its exact class tag is what the
// anchor gate compares against.
jlong resolveThreadLocalMapClassTag(jvmtiEnv *jvmti, JNIEnv *jni) {
  jlong tag = 0;
  jclass cls = jni->FindClass("java/lang/ThreadLocal$ThreadLocalMap");
  if (cls == nullptr) {
    jni->ExceptionClear();
    return 0;
  }
  jvmti->GetTag(cls, &tag);
  jni->DeleteLocalRef(cls);
  return tag;
}

} // namespace

void ReferenceChainTracker::replayAnchorObservations(
    const AnchorObservation *records, u32 count, bool static_retry) {
  // Strict arrival order, no dedup or coalescing: the helpers apply their own caps, promotion and
  // eviction, so the index mutations happen here, after the JVMTI call has returned.
  for (u32 i = 0; i < count; i++) {
    const AnchorObservation &r = records[i];
    if (r.actions & AnchorObservation::LOCAL) {
      noteLocalRootHolder(r.tag, r.own_class_tag);
    }
    if (r.actions & AnchorObservation::DURABLE_ADD) {
      addToStaticAnchorIndex(r.tag, r.own_class_tag, r.durable_root_kind);
    }
    if (r.actions & AnchorObservation::REENLIST_ELIGIBLE) {
      // Eligibility was decided at callback time against the frontier snapshot: root-attached
      // durable kind, or a CONTAINER-shaped holder (isSelectableAnchor) - the admission contract
      // for a rediscovered evicted anchor, which can carry parent_tag != 0 and a stale transient
      // root_kind after reparenting. No recheck here.
      if (_static_anchor_index_tags.count(r.tag) == 0) {
        indexAnchorForRotation(r.tag, r.own_class_tag);
      }
    }
    if (r.actions & AnchorObservation::AT_RISK) {
      pushAtRiskStaticAnchor(r.tag, r.at_risk_klass_id);
    }
  }
  if (static_retry) {
    _durable_anchor_resweep_gen++; // one retry request for the rejected static-field report(s)
  }
}

void ReferenceChainTracker::descendFromAnchor(
    jvmtiEnv *jvmti, JNIEnv *jni, ReferenceChainAnchorObservationScope &scope,
    jobject anchor, jlong anchor_tag, u32 anchor_depth,
    jlong anchor_descend_class_tag, int budget, int *edges_admitted,
    bool *truncated, bool *frontier_cap_hit, u64 *safepoint_ns,
    bool *anchor_observation_overflow) {
  jlong resolved_chain_tags[MAX_RESOLVED_CHAINS];
  ReferenceChainPassContext ctx(scope);
  ctx.tracker = this;
  ctx.frontier = _frontier;
  ctx.resolved_chain_tags = resolved_chain_tags;
  ctx.resolved_chain_tag_count = snapshotResolvedChainTags(resolved_chain_tags);
  // Bound admission to DESCENT_HOPS below the anchor, still subject to the global hop cap.
  int descent_cap = (int)anchor_depth + DESCENT_HOPS;
  ctx.hop_cap = descent_cap < _hop_cap ? descent_cap : _hop_cap;
  ctx.budget = budget;
  ctx.edges_admitted = 0;
  ctx.truncated = false;
  ctx.frontier_cap_hit = false;

  ctx._no_descend_class_tag_count =
      resolveNoDescendClassTags(jvmti, jni, ctx._no_descend_class_tags,
                                ReferenceChainPassContext::NO_DESCEND_CLASS_CAP);
  if (anchor_descend_class_tag != 0) {
    ctx._descent_anchor_tag = anchor_tag;
    ctx._anchor_descend_class_tag = anchor_descend_class_tag;
  }

  jvmtiHeapCallbacks callbacks;
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.heap_reference_callback = heapReferenceCallback;
  u64 follow_start_ns = OS::nanotime();
  jvmti->FollowReferences(0, nullptr, anchor, &callbacks, &ctx);
  *safepoint_ns += OS::nanotime() - follow_start_ns;
  *edges_admitted += ctx.edges_admitted;
  *truncated = *truncated || ctx.truncated;
  *frontier_cap_hit = *frontier_cap_hit || ctx.frontier_cap_hit;
  // observeReturn() takes the buffer lock, ordering the callbacks' writes before this read.
  *anchor_observation_overflow =
      scope.observeReturn() || ctx.anchor_observation_overflow;
}

std::vector<jlong>
ReferenceChainTracker::collectStaticFieldAnchorsForRotation(
    int max_count, std::vector<FreshAnchor> *fresh_picked) {
  if (fresh_picked != nullptr) {
    fresh_picked->clear();
  }
  std::vector<jlong> selected;
  const size_t fresh_queue_len = _static_anchor_fresh_queue.size();
  if (max_count <= 0 ||
      (_static_anchor_index.empty() && fresh_queue_len == 0)) {
    return selected;
  }
  size_t idx_size = _static_anchor_index.size();
  if (_anchor_container_cursor >= idx_size) {
    _anchor_container_cursor = 0;
  }
  if (_anchor_other_cursor >= idx_size) {
    _anchor_other_cursor = 0;
  }
  struct TierPick {
    size_t pos;
    jlong tag;
  };
  const size_t max_picks = std::min(
      std::max(idx_size, fresh_queue_len), static_cast<size_t>(max_count));
  const size_t fair_pick_limit = std::min(idx_size, max_picks * 2);
  std::vector<TierPick> leak_picks;
  std::vector<TierPick> fresh_picks;
  std::vector<TierPick> container_picks;
  std::vector<TierPick> other_picks;
  // Fresh-pick membership for the fair tiers' dedup: a set, not a vector - the fair tiers probe
  // it once per scanned pick on the per-pass hot path.
  std::unordered_set<jlong> fresh_kept_tags;
  std::vector<jlong> fresh_spent_tags;
  selected.reserve(max_picks);
  leak_picks.reserve(max_picks);
  fresh_picks.reserve(std::min(fresh_queue_len, max_picks));
  container_picks.reserve(fair_pick_limit);
  other_picks.reserve(fair_pick_limit);
  fresh_kept_tags.reserve(std::min(fresh_queue_len, max_picks));
  fresh_spent_tags.reserve(fresh_queue_len + max_picks);
  std::unordered_set<jlong> leak_spent_tags;
  bool container_before_cursor = false;
  bool other_before_cursor = false;
  _frontier->withSharedLock([&](const FrontierTable *frontier) {
    for (size_t i = 0; i < idx_size; i++) {
      jlong tag = _static_anchor_index[i];
      jlong own_class_tag = i < _static_anchor_own_class_tags.size()
                               ? _static_anchor_own_class_tags[i]
                               : 0;
      FrontierEntry entry{};
      if (!frontier->lookupLocked(tag, &entry) ||
          !isSelectableAnchor(entry, own_class_tag) ||
          (entry.state != FrontierEntryState::FRONTIER &&
           entry.state != FrontierEntryState::EXPANDED) ||
          isQueuedForRotation(tag)) {
        continue;
      }
      if (entry.leak_tag != 0) {
        if (leak_picks.size() < max_picks) {
          leak_picks.push_back(TierPick{i, tag});
        } else {
          // Capped out: a leak-tagged anchor never falls to the fair tiers (only this tier and
          // the fresh lane can select it, and the fresh lane's filter rejects leak tags), so a
          // skipped suffix pick must not keep a fresh-lane turn it can never spend on a walk.
          // Spend the first look here - the leak tier's own cap is the only wait, and once the
          // head drains the anchor is still leak-tagged and still selectable by this scan.
          fresh_spent_tags.push_back(tag);
          leak_spent_tags.insert(tag);
        }
      } else {
        bool is_container = false;
        if (i < _static_anchor_own_class_tags.size()) {
          auto shape_it =
              _class_shape_cache.find(_static_anchor_own_class_tags[i]);
          is_container = shape_it != _class_shape_cache.end() &&
                         shape_it->second == (u8)AnchorClassShape::CONTAINER;
        }
        if (is_container) {
          if (i < _anchor_container_cursor) {
            container_before_cursor = true;
          } else if (container_picks.size() < fair_pick_limit) {
            container_picks.push_back(TierPick{i, tag});
          }
        } else if (i < _anchor_other_cursor) {
          other_before_cursor = true;
        } else if (other_picks.size() < fair_pick_limit) {
          other_picks.push_back(TierPick{i, tag});
        }
      }
    }

    int fresh_room =
        (max_count - (int)leak_picks.size()) -
        (max_count - (int)leak_picks.size()) / 2;
    if (fresh_room <= 0 && !_static_anchor_fresh_queue.empty()) {
      // The leak tier saturated the whole selection budget: the fresh lane got NO budget this
      // pass, so queued entries would never pop and never receive fair-tier budget either -
      // spend their first look now (the old queue.clear() semantics) so they fall back to the
      // fair tiers at their index positions once the leak tier ebbs. With a positive fresh
      // budget the queue keeps its entries' turns across passes (FIFO order, nothing jumps the
      // queue).
      while (!_static_anchor_fresh_queue.empty()) {
        fresh_spent_tags.push_back(
            _static_anchor_fresh_queue.front().tag);
        _static_anchor_fresh_queue.pop_front();
      }
    }
    while (!_static_anchor_fresh_queue.empty() && fresh_room > 0) {
      FreshAnchor anchor = _static_anchor_fresh_queue.front();
      _static_anchor_fresh_queue.pop_front();
      FrontierEntry entry{};
      if (!frontier->lookupLocked(anchor.tag, &entry) ||
          !isSelectableAnchor(entry, anchor.own_class_tag) ||
          (entry.state != FrontierEntryState::FRONTIER &&
           entry.state != FrontierEntryState::EXPANDED) ||
          isQueuedForRotation(anchor.tag) || entry.leak_tag != 0) {
        // Dead/ineligible/queued/leak-tier: first look spent, not fresh-kept (the leak tier
        // selects it via the scan if it is leak-tagged).
        fresh_spent_tags.push_back(anchor.tag);
        continue;
      }
      auto shape_it = _class_shape_cache.find(anchor.own_class_tag);
      bool keep = shape_it == _class_shape_cache.end() ||
                  shape_it->second == (u8)AnchorClassShape::CONTAINER;
      if (!keep) {
        // Classified non-container: the other tier owns it - first look spent here.
        fresh_spent_tags.push_back(anchor.tag);
        continue;
      }
      fresh_picks.push_back(TierPick{idx_size, anchor.tag});
      fresh_kept_tags.insert(anchor.tag);
      if (fresh_picked != nullptr) {
        fresh_picked->push_back(anchor);
      }
      fresh_room--;
    }
  });
  auto consume_tier_fair = [&](const std::vector<TierPick> &picks,
                               bool has_pick_before_cursor, size_t &cursor,
                               int want) {
    int took = 0;
    if (want <= 0) {
      return took;
    }
    if (picks.empty()) {
      if (has_pick_before_cursor) {
        cursor = 0;
      }
      return took;
    }
    size_t consumed_pos = 0;
    for (size_t k = 0; k < picks.size() && took < want; k++) {
      const TierPick &p = picks[k];
      if (fresh_kept_tags.count(p.tag) != 0) {
        continue;
      }
      selected.push_back(p.tag);
      consumed_pos = p.pos;
      took++;
    }
    if (took > 0) {
      cursor = consumed_pos + 1 >= idx_size ? 0 : consumed_pos + 1;
    }
    return took;
  };
  int budget_left = max_count;
  for (const TierPick &p : leak_picks) {
    if (budget_left <= 0) {
      break;
    }
    selected.push_back(p.tag);
    budget_left--;
  }
  for (const TierPick &p : fresh_picks) {
    if (budget_left <= 0) {
      break;
    }
    selected.push_back(p.tag);
    budget_left--;
  }
  budget_left -= consume_tier_fair(container_picks, container_before_cursor,
                                    _anchor_container_cursor, budget_left);
  consume_tier_fair(other_picks, other_before_cursor, _anchor_other_cursor,
                    budget_left);

  if (!selected.empty() || !leak_spent_tags.empty()) {
    // Selection alone no longer consumes a fresh anchor's first look: walked anchors are marked
    // served after their descent (the caller, post-flush), and unwalked fresh picks are requeued
    // to the queue front. Erase the tags whose look IS spent this pass and that must not sit in
    // the queue: selected tags (leak- or fair-tier picks - their look happens via the walk, and
    // leaving them queued would re-serve them next pass) and the cap-skipped leak suffix (spent
    // in the scan above).
    std::unordered_set<jlong> served(selected.begin(), selected.end());
    served.insert(leak_spent_tags.begin(), leak_spent_tags.end());
    _static_anchor_fresh_queue.erase(
        std::remove_if(_static_anchor_fresh_queue.begin(),
                       _static_anchor_fresh_queue.end(),
                       [&](const FreshAnchor &anchor) {
                         return served.count(anchor.tag) != 0;
                       }),
        _static_anchor_fresh_queue.end());
  }
  // First looks spent WITHOUT a walk: entries the fresh-lane filters rejected (dead, leak-tier,
  // non-container), the leak-tier cap's skipped suffix, and the no-budget overflow drain. These
  // never descend this pass, so their look is spent here; walked anchors' looks are spent by the
  // caller after the scope flush.
  _frontier->markAnchorRotationServed(fresh_spent_tags.data(),
                                      fresh_spent_tags.size());
  return selected;
}

bool ReferenceChainTracker::atRiskAnchorNeedsObservation(jlong tag,
                                                          u32 klass_id) const {
  if (_static_anchor_fifo_set.contains(tag) ||
      _static_anchor_fifo.size() >= STATIC_ANCHOR_FIFO_CAP) {
    return false;
  }
  auto count_it = _static_anchor_fifo_klass_counts.find(klass_id);
  return count_it == _static_anchor_fifo_klass_counts.end() ||
         count_it->second < STATIC_ANCHOR_ATRISK_PER_KLASS_CAP;
}

void ReferenceChainTracker::pushAtRiskStaticAnchor(jlong tag, u32 klass_id) {
  if (!atRiskAnchorNeedsObservation(tag, klass_id)) {
    return;
  }
  auto count_it = _static_anchor_fifo_klass_counts.find(klass_id);
  if (count_it == _static_anchor_fifo_klass_counts.end()) {
    count_it = _static_anchor_fifo_klass_counts.emplace(klass_id, 0U).first;
  }
  count_it->second++;
  _static_anchor_fifo.push_back(AtRiskAnchor{tag, klass_id});
  _static_anchor_fifo_set.insert(tag);
}

void ReferenceChainTracker::addToStaticAnchorIndex(jlong tag,
                                                   jlong own_class_tag,
                                                   u8 root_kind) {
  if (root_kind != (u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD &&
      root_kind != (u8)JVMTI_HEAP_REFERENCE_JNI_GLOBAL) {
    return;
  }
  // A local holder later attached by a durable root now belongs to the capped durable share;
  // release its slot in the local cap (it stays indexed - the dedup below is a no-op for it).
  // INVARIANT (_local_anchor_tags ⊆ _static_anchor_index_tags): erasing here keeps the subset
  // relation evictOldestDurableAnchors()'s durable-share subtraction relies on - the tag stays
  // in _static_anchor_index_tags, so a local-share tag is always an indexed tag, never the
  // reverse.
  _local_anchor_tags.erase(tag);
  // The upgrade grows the durable share without a new index push (the dedup in
  // indexAnchorForRotation() returns early), so the durable cap is checked here too. The just
  // upgraded tag may itself be among the evicted oldest entries; replay of its next durable-edge
  // observation re-indexes it.
  evictOldestDurableAnchors();
  indexAnchorForRotation(tag, own_class_tag);
}

void ReferenceChainTracker::advancePendingLocalAnchorEvictionCursor() {
  if (_pending_local_evict_cursor > _pending_local_anchors.size()) {
    _pending_local_evict_cursor = 0;
  }
  while (_pending_local_evict_cursor < _pending_local_anchors.size()) {
    auto shape = _class_shape_cache.find(
        _pending_local_anchors[_pending_local_evict_cursor].class_tag);
    if (shape == _class_shape_cache.end() ||
        shape->second != (u8)AnchorClassShape::CONTAINER) {
      break;
    }
    _pending_local_evict_cursor++;
  }
}

void ReferenceChainTracker::preparePendingLocalAnchorEvictionCursor() {
  if (_pending_local_anchors.size() >= PENDING_LOCAL_ANCHOR_CAP) {
    advancePendingLocalAnchorEvictionCursor();
  }
}

bool ReferenceChainTracker::localHolderNeedsObservation(
    jlong tag, jlong own_class_tag) const {
  auto shape = _class_shape_cache.find(own_class_tag);
  if (shape != _class_shape_cache.end() &&
      shape->second != (u8)AnchorClassShape::CONTAINER) {
    return false;
  }
  if (_static_anchor_index_tags.count(tag) > 0 ||
      _pending_local_anchor_tags.count(tag) > 0) {
    return false;
  }
  if (shape == _class_shape_cache.end()) {
    return _pending_local_anchors.size() < PENDING_LOCAL_ANCHOR_CAP;
  }
  if (_local_anchor_tags.size() < LOCAL_ANCHOR_INDEX_CAP ||
      _pending_local_anchors.size() < PENDING_LOCAL_ANCHOR_CAP) {
    return true;
  }
  return _pending_local_evict_cursor < _pending_local_anchors.size();
}

void ReferenceChainTracker::noteLocalRootHolder(jlong tag,
                                                jlong own_class_tag) {
  auto shape = _class_shape_cache.find(own_class_tag);
  if (shape != _class_shape_cache.end() &&
      shape->second != (u8)AnchorClassShape::CONTAINER) {
    return; // classified non-container: never indexed
  }
  if (_static_anchor_index_tags.count(tag) > 0) {
    return; // already indexed (durable root or earlier local report)
  }
  bool confirmed_container = false;
  if (shape != _class_shape_cache.end()) {
    if (_local_anchor_tags.size() < LOCAL_ANCHOR_INDEX_CAP) {
      // INVARIANT (_local_anchor_tags ⊆ _static_anchor_index_tags): every local-share insert is
      // immediately followed by indexAnchorForRotation(), which inserts the same tag into
      // _static_anchor_index_tags (dedup no-op if already indexed) - the subset relation
      // evictOldestDurableAnchors()'s durable-share subtraction relies on.
      _local_anchor_tags.emplace(tag, own_class_tag);
      indexAnchorForRotation(tag, own_class_tag);
      return;
    }
    // At the cap: defer to resolvePendingLocalAnchors(), which may compact dead local entries
    // on the BFS thread.
    confirmed_container = true;
  }
  if (_pending_local_anchors.size() >= PENDING_LOCAL_ANCHOR_CAP) {
    if (!confirmed_container || _pending_local_anchor_tags.count(tag) > 0) {
      return; // re-reported by the next root enumeration
    }
    // A confirmed container is walkable as soon as a local slot frees, so it outranks an entry not
    // yet confirmed as a container: evict the oldest such entry (re-reported by the next root
    // enumeration). Forward-only cursor: while the buffer is full nothing is appended, the only
    // overwrite is at the cursor with a container, and skipped slots are containers, so every slot
    // below the cursor stays a confirmed container and the scan totals <= PENDING_LOCAL_ANCHOR_CAP
    // per enumeration.
    advancePendingLocalAnchorEvictionCursor();
    if (_pending_local_evict_cursor >= _pending_local_anchors.size()) {
      return; // only confirmed containers parked: dropped, re-reported by the next enumeration
    }
    PendingLocalAnchor &victim = _pending_local_anchors[_pending_local_evict_cursor++];
    _pending_local_anchor_tags.erase(victim.tag);
    assert(_pending_local_evictable_count > 0);
    _pending_local_evictable_count--;
    victim = PendingLocalAnchor{tag, own_class_tag};
    _pending_local_anchor_tags.insert(tag);
    return;
  }
  if (!_pending_local_anchor_tags.insert(tag).second) {
    return;
  }
  if (shape == _class_shape_cache.end()) {
    _pending_local_evictable_count++;
  }
  _pending_local_anchors.push_back(PendingLocalAnchor{tag, own_class_tag});
}

void ReferenceChainTracker::resolvePendingLocalAnchors() {
  if (_pending_local_anchors.empty()) {
    return;
  }
  bool compacted = false;
  for (const PendingLocalAnchor &pending : _pending_local_anchors) {
    if (_static_anchor_index_tags.count(pending.tag) > 0) {
      continue;
    }
    auto shape = _class_shape_cache.find(pending.class_tag);
    if (shape == _class_shape_cache.end() ||
        shape->second != (u8)AnchorClassShape::CONTAINER) {
      continue; // non-container, or still unclassified: dropped (see the buffer's comment)
    }
    if (_local_anchor_tags.size() >= LOCAL_ANCHOR_INDEX_CAP && !compacted) {
      // At most one compaction attempt per call. After a compaction that removed nothing (local
      // share full of live containers), skip the next LOCAL_ANCHOR_COMPACT_BACKOFF attempts so a
      // saturated-but-live share does not pay the locked O(cap) scan every pass.
      compacted = true;
      if (_local_compact_backoff > 0) {
        _local_compact_backoff--;
      } else {
        const size_t reclaimed = compactLocalAnchors();
        _local_compact_backoff =
            reclaimed < LOCAL_ANCHOR_COMPACT_MIN_RECLAIM
                ? LOCAL_ANCHOR_COMPACT_BACKOFF
                : 0;
      }
    }
    if (_local_anchor_tags.size() >= LOCAL_ANCHOR_INDEX_CAP) {
      continue; // still full (live containers, or compaction backed off): the cap holds
    }
    _local_anchor_tags.emplace(pending.tag, pending.class_tag);
    // INVARIANT (_local_anchor_tags ⊆ _static_anchor_index_tags): same contract as
    // noteLocalRootHolder()'s insert - indexAnchorForRotation() below adds the tag to
    // _static_anchor_index_tags in the same step.
    indexAnchorForRotation(pending.tag, pending.class_tag);
  }
  // Keep capacity: the buffer refills on every root enumeration.
  _pending_local_anchors.clear();
  _pending_local_anchor_tags.clear();
  _pending_local_evict_cursor = 0;
  _pending_local_evictable_count = 0;
}

size_t ReferenceChainTracker::compactLocalAnchors() {
  if (_local_anchor_tags.empty()) {
    return 0;
  }
  std::unordered_set<jlong> removed;
  _frontier->withSharedLock([&](const FrontierTable *frontier) {
    // Only the local share (O(cap)): the durable share is never compacted here.
    for (const auto &local : _local_anchor_tags) {
      FrontierEntry entry{};
      // Same eligibility as collectStaticFieldAnchorsForRotation(): a released (ABANDONED) entry
      // is a dead object and can never be selected again.
      if (!frontier->lookupLocked(local.first, &entry) ||
          !isSelectableAnchor(entry, local.second) ||
          (entry.state != FrontierEntryState::FRONTIER &&
           entry.state != FrontierEntryState::EXPANDED)) {
        removed.insert(local.first);
      }
    }
  });
  if (removed.empty()) {
    return 0;
  }
  eraseAnchorEntries(removed);
  return removed.size();
}

size_t ReferenceChainTracker::evictOldestDurableAnchors() {
  // The local share is capped and self-compacting; only entries outside it count against the
  // durable cap.
  size_t durable = _static_anchor_index_tags.size() - _local_anchor_tags.size();
  if (durable <= DURABLE_ANCHOR_INDEX_CAP) {
    return 0;
  }
  // Evict enough oldest entries to drop the share to cap - DURABLE_ANCHOR_EVICT_BATCH, so one
  // O(index) compaction amortizes over ~DURABLE_ANCHOR_EVICT_BATCH admissions instead of being
  // paid per admission. to_evict <= durable always (DURABLE_ANCHOR_INDEX_CAP > batch).
  size_t to_evict =
      durable - DURABLE_ANCHOR_INDEX_CAP + DURABLE_ANCHOR_EVICT_BATCH;
  // FIFO by index position (appends are at the back). Local-share entries keep their slots -
  // their cap and compaction live in noteLocalRootHolder()/compactLocalAnchors().
  std::unordered_set<jlong> evicted;
  evicted.reserve(to_evict);
  for (size_t i = 0;
       i < _static_anchor_index.size() && evicted.size() < to_evict;
       i++) {
    jlong tag = _static_anchor_index[i];
    if (_local_anchor_tags.count(tag) > 0) {
      continue;
    }
    evicted.insert(tag);
  }
  eraseAnchorEntries(evicted, /*preserve_pending_turns=*/true);
  // Record a resweep request unconditionally (see _durable_anchor_resweep_gen): a holder
  // displaced while admissions keep the population above the cap must be re-swept even when
  // evictions stop. No cursor restart here: with churn above the cap an eviction fires every
  // pass, and an unpaced cursor restart on each eviction would reset a mid-lap cursor so laps
  // over large class lists never complete (later static fields never visited). The unserved generation alone is the scheduling contract - the lap in flight
  // finishes, then the next fresh lap from class 0 serves the request.
  _durable_anchor_resweep_gen++;
  return evicted.size();
}

// See the declaration in referenceChains.h.
void ReferenceChainTracker::removeMissingAnchors(
    const std::vector<jlong> &missing) {
  if (missing.empty()) {
    return;
  }
  eraseAnchorEntries(
      std::unordered_set<jlong>(missing.begin(), missing.end()));
}

// See the declaration in referenceChains.h.
void ReferenceChainTracker::eraseAnchorEntries(
    const std::unordered_set<jlong> &removed, bool preserve_pending_turns) {
  if (removed.empty()) {
    return;
  }
  // Stable compaction preserves index order and the parallel class-tag alignment.
  // Durable eviction preserves pending first-look turns outside the capped index.
  size_t out = 0;
  for (size_t i = 0; i < _static_anchor_index.size(); i++) {
    jlong tag = _static_anchor_index[i];
    if (removed.count(tag) > 0) {
      continue;
    }
    _static_anchor_index[out] = tag;
    if (i < _static_anchor_own_class_tags.size()) {
      _static_anchor_own_class_tags[out] = _static_anchor_own_class_tags[i];
    }
    out++;
  }
  _static_anchor_index.resize(out);
  if (_static_anchor_own_class_tags.size() > out) {
    _static_anchor_own_class_tags.resize(out);
  }
  for (jlong tag : removed) {
    _static_anchor_index_tags.erase(tag);
    _local_anchor_tags.erase(tag);
  }
  if (!preserve_pending_turns) {
    std::vector<jlong> pending_removed;
    pending_removed.reserve(
        std::min(_static_anchor_fresh_queue.size(), removed.size()));
    _static_anchor_fresh_queue.erase(
        std::remove_if(_static_anchor_fresh_queue.begin(),
                       _static_anchor_fresh_queue.end(),
                       [&](const FreshAnchor &anchor) {
                         if (removed.count(anchor.tag) == 0) {
                           return false;
                         }
                         pending_removed.push_back(anchor.tag);
                         return true;
                       }),
        _static_anchor_fresh_queue.end());
    _frontier->clearAnchorRotationPending(pending_removed.data(),
                                         pending_removed.size());
  }
}

bool ReferenceChainTracker::isSelectableAnchor(const FrontierEntry &entry,
                                               jlong own_class_tag) const {
  if (entry.parent_tag == 0 &&
      (entry.root_kind == (u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD ||
       entry.root_kind == (u8)JVMTI_HEAP_REFERENCE_JNI_GLOBAL)) {
    return true;
  }
  auto shape = _class_shape_cache.find(own_class_tag);
  return shape != _class_shape_cache.end() &&
         shape->second == (u8)AnchorClassShape::CONTAINER;
}

void ReferenceChainTracker::indexAnchorForRotation(jlong tag,
                                                   jlong own_class_tag) {
  // Dedup: a push at first admission and another at upgrade would double-add.
  if (!_static_anchor_index_tags.insert(tag).second) {
    return;
  }
  // Checked after the insert so the count includes the incoming tag; the batch evicts only the
  // oldest positions, never the tag being admitted here.
  evictOldestDurableAnchors();
  _static_anchor_index.push_back(tag);
  _static_anchor_own_class_tags.push_back(own_class_tag);
  if (_frontier != nullptr &&
      _static_anchor_fresh_queue.size() < STATIC_ANCHOR_FRESH_CAP &&
      _frontier->tryMarkAnchorRotationPending(tag)) {
    _static_anchor_fresh_queue.push_back(FreshAnchor{tag, own_class_tag});
  }
}

bool ReferenceChainTracker::resolveContainerInterfaceTags(
    jvmtiEnv *jvmti, JNIEnv *jni) {
  if (_collection_iface_class_tag != 0 && _map_iface_class_tag != 0) {
    return true;
  }
  // resolveLoadedClasses() tags every loaded class (including these bootstrap interfaces) with its
  // class-tag-allocator tag (a NEGATIVE value - see classTagAllocator.h's header comment) before
  // any anchor can be admitted, but classify defensively: if an interface object somehow carries
  // no tag yet, mint one via ClassTagAllocator::getOrMint() (as resolveLoadedClasses() does) so
  // the comparison below is well-defined.
  struct Iface {
    const char *name;
    jlong *tag_out;
  };
  Iface ifaces[2] = {{"java/util/Collection", &_collection_iface_class_tag},
                     {"java/util/Map", &_map_iface_class_tag}};
  for (const Iface &iface : ifaces) {
    if (*iface.tag_out != 0) {
      continue;
    }
    // Each interface is resolved independently: a transient JVMTI error on
    // one of them (GetTag/SetTag/FindClass failing for exactly one) must not
    // abort the other's resolution - the already-resolved tag stays cached in
    // its slot either way, and a per-interface failure only leaves THAT tag
    // at 0 for this call (the caller treats a false return as "shapes
    // unknown this pass" and retries on the next reconcile). Failing the
    // whole call on the first error would keep both anchors unclassified for
    // as long as one interface keeps erroring, even though the other resolved
    // fine.
    jclass local = jni->FindClass(iface.name);
    if (jniExceptionCheck(jni) || local == nullptr) {
      jni->ExceptionClear();
      continue;
    }
    jlong tag = ClassTagAllocator::getOrMint(jvmti, local);
    if (tag != 0) {
      *iface.tag_out = tag;
    }
    jni->DeleteLocalRef(local);
    // A per-interface GetTag/SetTag failure leaves that tag at 0 - the final
    // check below reports false only if an interface genuinely has no tag,
    // never as an early abort that skips the other interface.
  }
  return _collection_iface_class_tag != 0 && _map_iface_class_tag != 0;
}

bool ReferenceChainTracker::classImplementsContainerOrMap(jvmtiEnv *jvmti,
                                                          JNIEnv *jni,
                                                          jclass klass) {
  // LIFO (depth-first) walk over the superclass chain + every visited class's interfaces, not BFS:
  // interfaces are pushed after the superclass, so under LIFO every interface subtree is explored
  // before the superclass chain - the only path to an inherited Collection/Map. The 64-pop budget
  // counts duplicate pops too (already-visited classes burn hops). GetTag() is compared against the
  // two cached interface class tags.
  std::vector<jclass> work;
  std::unordered_set<jlong> visited;
  work.push_back(klass);
  bool found = false;
  int hops = 0;
  while (!found && !work.empty() && hops++ < 64) {
    jclass cur = work.back();
    work.pop_back();
    jlong cur_tag = 0;
    if (jvmti->GetTag(cur, &cur_tag) != JVMTI_ERROR_NONE || cur_tag == 0) {
      // Early exit: the popped ref is this walk's own (GetSuperclass/ GetImplementedInterfaces
      // local, or the caller's klass) - delete it like the loop bottom does, or the long-lived
      // engine thread leaks a JNI local ref per untagged hop.
      if (cur != klass) {
        jni->DeleteLocalRef(cur);
      }
      continue;
    }
    if (visited.count(cur_tag) > 0) {
      // Early exit: same local-ref ownership as above - delete before continuing (a hierarchy
      // diamond revisits interfaces here).
      if (cur != klass) {
        jni->DeleteLocalRef(cur);
      }
      continue;
    }
    visited.insert(cur_tag);
    if (cur_tag == _collection_iface_class_tag ||
        cur_tag == _map_iface_class_tag) {
      found = true;
      // The popped `cur` ref never reaches the loop's bottom delete.
      if (cur != klass) {
        jni->DeleteLocalRef(cur);
      }
      break;
    }
    jclass super = jni->GetSuperclass(cur);
    if (!jniExceptionCheck(jni) && super != nullptr) {
      work.push_back(super);
    } else {
      jni->ExceptionClear();
    }
    jint iface_count = 0;
    jclass *ifaces = nullptr;
    if (jvmti->GetImplementedInterfaces(cur, &iface_count, &ifaces) ==
            JVMTI_ERROR_NONE &&
        ifaces != nullptr) {
      for (jint i = 0; i < iface_count; i++) {
        if (ifaces[i] != nullptr) {
          work.push_back(ifaces[i]);
        }
      }
      jvmti->Deallocate((unsigned char *)ifaces);
    }
    // `cur` is either the caller-provided klass (caller-managed ref - NOT deleted here) or a ref
    // this walk minted (GetSuperclass/ GetImplementedInterfaces locals, deleted immediately after
    // use).
    if (cur != klass) {
      jni->DeleteLocalRef(cur);
    }
  }
  // Single exit: every remaining ref minted into `work` (early hop-bound exit or the found-break)
  // is deleted here rather than leaking locals for the process lifetime (the engine thread never
  // detaches).
  for (jclass r : work) {
    if (r != nullptr && r != klass) {
      jni->DeleteLocalRef(r);
    }
  }
  return found;
}

std::vector<jlong>
ReferenceChainTracker::collectUnclassifiedAnchorClassTags() const {
  // Collect up to ANCHOR_SHAPE_RECONCILE_BUDGET distinct class tags that appear in the pending
  // local-holder buffer or the anchor index but are not yet classified. Pending holders go first:
  // resolvePendingLocalAnchors() drops any still unclassified after this call, while indexed
  // durable anchors simply wait for a later pass.
  std::vector<jlong> unknown;
  unknown.reserve(8);
  std::unordered_set<jlong> seen;
  auto consider = [&](jlong class_tag) {
    if (class_tag == 0 || seen.count(class_tag) > 0 ||
        _class_shape_cache.count(class_tag) > 0) {
      return true;
    }
    seen.insert(class_tag);
    unknown.push_back(class_tag);
    return (int)unknown.size() < ANCHOR_SHAPE_RECONCILE_BUDGET;
  };
  bool room = true;
  for (size_t i = 0; room && i < _pending_local_anchors.size(); i++) {
    room = consider(_pending_local_anchors[i].class_tag);
  }
  for (size_t i = 0; room && i < _static_anchor_own_class_tags.size(); i++) {
    room = consider(_static_anchor_own_class_tags[i]);
  }
  return unknown;
}

void ReferenceChainTracker::reconcileAnchorClassShapes(jvmtiEnv *jvmti,
                                                        JNIEnv *jni) {
  if (jni == nullptr) {
    return;
  }
  if (_static_anchor_own_class_tags.empty() && _pending_local_anchors.empty()) {
    return;
  }
  std::vector<jlong> unknown = collectUnclassifiedAnchorClassTags();
  if (unknown.empty()) {
    return;
  }
  if (!resolveContainerInterfaceTags(jvmti, jni)) {
    return;
  }
  // The per-class interface walk below mints local refs (GetSuperclass, GetImplementedInterfaces)
  // that are only deleted as the BFS pops them; bound the outstanding count explicitly rather than
  // relying on the JVM to grow the local-ref table.
  if (jni->EnsureLocalCapacity(512) < 0 || jniExceptionCheck(jni)) {
    jni->ExceptionClear();
    return;
  }
  // One GetObjectsWithTags call resolves the class objects for the whole batch (class objects are
  // tagged with their class tags).
  jint obj_count = 0;
  jobject *objs = nullptr;
  jlong *obj_tags = nullptr;
  if (jvmti->GetObjectsWithTags((jint)unknown.size(), unknown.data(),
                               &obj_count, &objs, &obj_tags) !=
          JVMTI_ERROR_NONE ||
      obj_count <= 0) {
    if (objs != nullptr) {
      jvmti->Deallocate((unsigned char *)objs);
    }
    if (obj_tags != nullptr) {
      jvmti->Deallocate((unsigned char *)obj_tags);
    }
    return;
  }
  for (jint i = 0; i < obj_count; i++) {
    jclass klass = (jclass)objs[i];
    jlong class_tag = obj_tags[i];
    // class tags are NEGATIVE (a namespace disjoint from positive frontier tags); 0 means the
    // object was never tagged - skip only that.
    if (class_tag == 0 || klass == nullptr) {
      if (klass != nullptr) {
        jni->DeleteLocalRef(klass);
      }
      continue;
    }
    AnchorClassShape shape = classImplementsContainerOrMap(jvmti, jni, klass)
                                 ? AnchorClassShape::CONTAINER
                                 : AnchorClassShape::NON_CONTAINER;
    _class_shape_cache[class_tag] = (u8)shape;
    // GetObjectsWithTags() returned a local ref for every resolved class - this runs on the
    // long-lived BFS thread, where undeleted locals accumulate until detach and pin their classes
    // against unload.
    jni->DeleteLocalRef(klass);
  }
  jvmti->Deallocate((unsigned char *)objs);
  jvmti->Deallocate((unsigned char *)obj_tags);
}

int ReferenceChainTracker::drainStaticAnchorFifo(int max_count,
                                                 std::vector<AtRiskAnchor> &out) {
  if (max_count <= 0 || _static_anchor_fifo.empty()) {
    return 0;
  }
  int drained = 0;
  while (drained < max_count && !_static_anchor_fifo.empty()) {
    AtRiskAnchor entry = _static_anchor_fifo.front();
    _static_anchor_fifo.pop_front();
    auto count_it = _static_anchor_fifo_klass_counts.find(entry.klass_id);
    if (count_it != _static_anchor_fifo_klass_counts.end() &&
        --count_it->second == 0) {
      // Erased at zero so the map is bounded by the FIFO's live contents (<= 1024 distinct
      // classes), not by the search lifetime.
      _static_anchor_fifo_klass_counts.erase(count_it);
    }
    out.push_back(entry);
    drained++;
  }
  _static_anchor_fifo_set.rebuildFrom(_static_anchor_fifo);
  return drained;
}

void ReferenceChainTracker::requeueStaticAnchorFifoFront(
    const std::vector<AtRiskAnchor> &entries) {
  if (entries.empty()) {
    return;
  }
  // Reverse order onto the front preserves the tags' relative FIFO order (push_front of the LAST
  // entry first leaves the FIRST entry at the deque's front).
  for (size_t i = entries.size(); i-- > 0;) {
    _static_anchor_fifo_klass_counts[entries[i].klass_id]++;
    _static_anchor_fifo.push_front(entries[i]);
  }
  _static_anchor_fifo_set.rebuildFrom(_static_anchor_fifo);
}

void ReferenceChainTracker::requeueStaticAnchorFreshFront(
    const std::vector<FreshAnchor> &entries) {
  if (entries.empty()) {
    return;
  }
  // Reverse order onto the front preserves the tags' relative admission order (push_front of the
  // LAST entry first leaves the FIRST entry at the deque's front).
  for (size_t i = entries.size(); i-- > 0;) {
    _static_anchor_fresh_queue.push_front(entries[i]);
  }
}

void ReferenceChainTracker::walkStaticFieldAnchors(
    jvmtiEnv *jvmti, JNIEnv *jni, ReferenceChainAnchorObservationScope &scope,
    const std::vector<jlong> &anchor_tags, int budget, int *edges_admitted,
    bool *truncated, bool *frontier_cap_hit, u64 *safepoint_ns,
    bool *anchor_observation_overflow, std::vector<jlong> *unwalked) {
  *anchor_observation_overflow = false;
  if (anchor_tags.empty()) {
    return;
  }
  // Resolve all anchors in one O(tag_map) call.
  jint resolved_count = 0;
  jobject *objects = nullptr;
  jlong *resolved_tags = nullptr;
  if (jvmti->GetObjectsWithTags((jint)anchor_tags.size(), anchor_tags.data(),
                              &resolved_count, &objects,
                              &resolved_tags) != JVMTI_ERROR_NONE) {
    return;
  }
  if ((jint)anchor_tags.size() > resolved_count) {
    // Anchors absent from the resolution are collected: they can never be walked again, so their
    // index slots are pure capacity waste - and a dead local container's frontier record stays
    // selectable (EXPANDED), so compaction alone would keep rejecting replacement live containers
    // until a search restart cleared the frontier. Reclaim the slots here; the frontier record
    // itself stays - release machinery owns dead-entry cleanup.
    std::unordered_set<jlong> resolved(resolved_tags,
                                       resolved_tags + resolved_count);
    std::vector<jlong> missing;
    missing.reserve(anchor_tags.size() - resolved.size());
    for (jlong tag : anchor_tags) {
      if (resolved.count(tag) == 0) {
        missing.push_back(tag);
      }
    }
    removeMissingAnchors(missing);
  }
  int walked = 0;
  // First index the walk did NOT consume (breaks before an anchor's walk report i, breaks after
  // report i+1; a completed loop keeps the resolved_count sentinel).
  jint first_unwalked = resolved_count;
  // First index whose local ref has not been deleted yet. Every break path deletes objects[i]
  // before breaking, so anything at or after i+1 still holds a live local ref and must be cleaned
  // up below - this runs on the long-lived BFS thread, where undeleted locals accumulate until
  // detach and pin their objects against collection.
  jint first_undeleted = resolved_count;
  for (jint i = 0; i < resolved_count; i++) {
    FrontierEntry entry{};
    if (!_frontier->lookup(resolved_tags[i], &entry)) {
      // Dead-or-stale between selection and here - skip; release machinery owns dead-entry cleanup,
      // never here.
      jni->DeleteLocalRef(objects[i]);
      continue;
    }
    int remaining = budget - *edges_admitted;
    if (remaining <= 0) {
      jni->DeleteLocalRef(objects[i]);
      first_unwalked = i;
      first_undeleted = i + 1;
      break;
    }
    int edges_before = *edges_admitted;
    bool overflow = false;
    descendFromAnchor(jvmti, jni, scope, objects[i], resolved_tags[i],
                      entry.depth, /*anchor_descend_class_tag=*/0, remaining,
                      edges_admitted, truncated, frontier_cap_hit, safepoint_ns,
                      &overflow);
    TEST_LOG("ReferenceChainTracker::walkStaticFieldAnchors anchor walk "
             "outcome tag=%lld edges=%d truncated=%d cap_hit=%d",
             (long long)resolved_tags[i], *edges_admitted - edges_before,
             (int)*truncated, (int)*frontier_cap_hit);
    jni->DeleteLocalRef(objects[i]);
    if (overflow) {
      // The partially walked anchor stays unwalked (its rejected edge was not applied) so the
      // caller restores it with the remaining resolved tags. Edge-accounting contract:
      // ctx.edges_admitted counts NEW frontier admissions only (admitObject() counts a fresh
      // insert, never an already-admitted tag), and the partial descent's accepted observation
      // prefix IS replayed by the caller's scope flush - those admissions stay applied to the
      // frontier. Keeping them counted is what keeps the budget exact: the later re-walk re-
      // charges only edges that are still unadmitted (dedup by positive tag), so the anchor's
      // segment is charged once in total. Rolling the partial edges back would let applied-to-
      // frontier work escape the budget; incrementing the walk count would misreport the
      // descent as consumed, so only the walk count stays untouched here.
      *anchor_observation_overflow = true;
      first_unwalked = i;
      first_undeleted = i + 1;
      break;
    }
    walked++;
    if (*truncated && !*frontier_cap_hit) {
      // Budget/deadline exhausted mid-set - remaining anchors keep their rotation turn via the
      // cursor next pass (the wrapping cursor already tolerates a short selection).
      first_unwalked = i + 1;
      first_undeleted = i + 1;
      break;
    }
    if (*frontier_cap_hit) {
      first_unwalked = i + 1;
      first_undeleted = i + 1;
      break;
    }
  }
  // Release the local refs of anchors the early exits above skipped - each break only deleted its
  // own objects[i].
  for (jint i = first_undeleted; i < resolved_count; i++) {
    jni->DeleteLocalRef(objects[i]);
  }
  if (unwalked != nullptr && first_unwalked < resolved_count) {
    unwalked->insert(unwalked->end(), resolved_tags + first_unwalked,
                     resolved_tags + resolved_count);
  }
  jvmti->Deallocate((unsigned char *)objects);
  jvmti->Deallocate((unsigned char *)resolved_tags);
  TEST_LOG_SUMMARY("ReferenceChainTracker::walkStaticFieldAnchors selected=%zu "
           "walked=%d edges_admitted=%d truncated=%d frontier_cap_hit=%d",
           anchor_tags.size(), walked, *edges_admitted, (int)*truncated,
           (int)*frontier_cap_hit);
}

void ReferenceChainTracker::walkCandidateThreadLocals(
    jvmtiEnv *jvmti, JNIEnv *jni, int budget, int *edges_admitted,
    bool *truncated, bool *frontier_cap_hit, u64 *safepoint_ns) {
  if (_candidate_count <= 0) {
    return;
  }
  // Flatten the per-slot qualifying-tid snapshot into (slot, tid) pairs, then walk up to
  // THREAD_WALK_MAX_ANCHORS of them per pass, rotating via _thread_walk_anchor_cursor so every
  // qualifying tid gets a turn within ceil(total / THREAD_WALK_MAX_ANCHORS) passes instead of
  // always walking the first candidates' tids.
  int slot[MAX_CANDIDATE_QUALIFYING_TIDS * MAX_LEAK_CANDIDATES_FROM_LT];
  jint tid[sizeof(slot) / sizeof(slot[0])];
  int total = 0;
  for (int s = 0; s < _candidate_count; s++) {
    for (int q = 0; q < _candidate_qualifying_tid_count[s]; q++) {
      if (total >= (int)(sizeof(slot) / sizeof(slot[0]))) {
        break;
      }
      slot[total] = s;
      tid[total] = _candidate_qualifying_tids[s][q];
      total++;
    }
  }
  if (total == 0) {
    return;
  }
  jlong descend_class_tag = resolveThreadLocalMapClassTag(jvmti, jni);
  if (_thread_walk_anchor_cursor < 0 ||
      _thread_walk_anchor_cursor >= total) {
    _thread_walk_anchor_cursor = 0;
  }
  int walked = 0;
  const int start = _thread_walk_anchor_cursor;
  int i = start;
  do {
    jobject thread_obj;
    {
      MutexLocker ml(_thread_objects_lock);
      auto it = _thread_objects.find(tid[i]);
      if (it == _thread_objects.end()) {
        thread_obj = nullptr; // Thread died/never registered - skip
      } else {
        thread_obj = it->second;
      }
    }
    if (thread_obj != nullptr) {
      // Anchor admission, idempotent across passes: a tag that still maps to a live entry is reused
      // as-is (the Thread object is commonly root-attached by root enumeration already); a stale
      // positive tag (search restart reissued tags from 1, releaseSearchTags() did not clear this
      // object because release only touches FrontierTable entries) must be re-minted, otherwise the
      // walk would parent new children onto a dead table slot or, worse, onto the entry a reissued
      // tag now belongs to.
      jlong anchor_tag = getTag(jvmti, thread_obj);
      u32 anchor_depth = 0;
      FrontierEntry anchor_entry{};
      if (anchor_tag > 0 && _frontier->lookup(anchor_tag, &anchor_entry)) {
        anchor_depth = anchor_entry.depth;
      } else {
        jclass thread_class = jni->GetObjectClass(thread_obj);
        jlong class_tag = 0;
        jvmti->GetTag(thread_class, &class_tag);
        u32 referrer_klass = classTags()->resolve(class_tag);
        jlong fresh_tag = tagObject(jvmti, thread_obj);
        if (fresh_tag != 0 &&
            _frontier->insert(fresh_tag, 0, referrer_klass, 0,
                             FrontierEntryState::FRONTIER,
                             (u8)JVMTI_HEAP_REFERENCE_THREAD, class_tag)) {
          anchor_tag = fresh_tag;
        } else {
          if (fresh_tag != 0) {
            // Frontier insert failed (table full): the tag-release scan only touches inserted
            // frontier entries, so an installed-but-unowned tag would survive the search and
            // collide with a reused tag number after a restart (fresh _next_tag from 1).
            clearTag(jvmti, thread_obj);
          }
          anchor_tag = 0;
        }
        jni->DeleteLocalRef(thread_class);
      }
      if (anchor_tag != 0) {
        int remaining = budget - *edges_admitted;
        if (remaining > 0) {
          bool overflow = false;
          {
            ReferenceChainAnchorObservationScope scope(this);
            descendFromAnchor(jvmti, jni, scope, thread_obj, anchor_tag,
                              anchor_depth, descend_class_tag, remaining,
                              edges_admitted, truncated, frontier_cap_hit,
                              safepoint_ns, &overflow);
            // Flush this descent before the loop advances or retains its cursor.
            // Later traversal decisions must see its accepted observations.
            scope.flush();
          }
          if (overflow) {
            // The partially walked anchor stays unwalked (its rejected edge was not applied),
            // matching walkStaticFieldAnchors(): the descent is not misreported as consumed, so
            // the retained cursor re-walks it in full without the walked count charging it.
            break; // retain the cursor on this thread: its walk was cut short
          }
          walked++;
        }
      }
    }
    i = (i + 1) % total;
    if (*frontier_cap_hit || walked >= THREAD_WALK_MAX_ANCHORS ||
        budget - *edges_admitted <= 0) {
      break;
    }
  } while (i != start);
  _thread_walk_anchor_cursor = i;
  TEST_LOG_SUMMARY("ReferenceChainTracker::walkCandidateThreadLocals candidates=%d "
           "tids=%d walked=%d edges_admitted=%d truncated=%d "
           "frontier_cap_hit=%d",
           _candidate_count, total, walked, *edges_admitted, (int)*truncated,
           (int)*frontier_cap_hit);
}

void ReferenceChainTracker::registerExistingThreads(jvmtiEnv *jvmti,
                                                     JNIEnv *jni) {
  if (!enabled() || jvmti == nullptr || jni == nullptr) {
    return;
  }
  // onThreadStart() cannot register threads that predate profiler attachment.
  jint thread_count = 0;
  jthread *thread_objects = nullptr;
  if (jvmti->GetAllThreads(&thread_count, &thread_objects) != JVMTI_ERROR_NONE) {
    return;
  }
  for (jint i = 0; i < thread_count; i++) {
    jthread thread = thread_objects[i];
    if (thread == nullptr) {
      continue;
    }
    int tid = JVMThread::nativeThreadId(jni, thread);
    if (jni->ExceptionCheck()) {
      jni->ExceptionClear();
      continue;
    }
    if (tid >= 0) {
      registerThreadObject(jni, tid, thread);
    }
    jni->DeleteLocalRef(thread);
  }
  jvmti->Deallocate((unsigned char *)thread_objects);
}

void ReferenceChainTracker::registerThreadObject(JNIEnv *jni, int tid,
                                                 jthread thread) {
  if (!enabled() || jni == nullptr || thread == nullptr) {
    return;
  }
  jobject ref = jni->NewGlobalRef(thread);
  if (ref == nullptr) {
    return;
  }
  {
    MutexLocker ml(_thread_objects_lock);
    if (_thread_objects_open) {
      auto it = _thread_objects.find(tid);
      if (it != _thread_objects.end()) {
        // Same deferred-deletion rule as unregisterThreadObject(): a walk may still hold a copy of
        // the replaced ref.
        _thread_refs_pending_delete.push_back(it->second);
      }
      _thread_objects[tid] = ref;
      return;
    }
  }
  // Registry closed by releaseAllThreadObjects() (see _thread_objects_open's comment).
  jni->DeleteGlobalRef(ref);
}

void ReferenceChainTracker::unregisterThreadObject(JNIEnv *jni, int tid) {
  if (jni == nullptr) {
    return;
  }
  MutexLocker ml(_thread_objects_lock);
  auto it = _thread_objects.find(tid);
  if (it != _thread_objects.end()) {
    // NOT DeleteGlobalRef() here: walkCandidateThreadLocals() may have already copied this jobject
    // out of the map (lock released) and still be using it as a FollowReferences anchor - deleting
    // a global ref invalidates it for every other JNI call (JNI spec), so deletion is deferred to
    // releaseEndedThreadRefs() on the BFS thread (see _thread_refs_pending_delete's comment).
    _thread_refs_pending_delete.push_back(it->second);
    _thread_objects.erase(it);
  }
}

void ReferenceChainTracker::releaseEndedThreadRefs(JNIEnv *jni) {
  if (jni == nullptr) {
    return;
  }
  std::vector<jobject> pending;
  {
    MutexLocker ml(_thread_objects_lock);
    pending.swap(_thread_refs_pending_delete);
  }
  for (size_t i = 0; i < pending.size(); i++) {
    jni->DeleteGlobalRef(pending[i]);
  }
}

void ReferenceChainTracker::releaseAllThreadObjects(JNIEnv *jni) {
  if (jni == nullptr) {
    return;
  }
  // Recording stop: the BFS thread is joined (Profiler::stop() order), so no walk phase can hold a
  // copied ref - the deferred-deletion indirection of unregisterThreadObject() is unnecessary here
  // and every ref can go now.
  std::vector<jobject> pending;
  {
    MutexLocker ml(_thread_objects_lock);
    _thread_objects_open = false;
    for (auto &kv : _thread_objects) {
      pending.push_back(kv.second);
    }
    _thread_objects.clear();
    pending.insert(pending.end(), _thread_refs_pending_delete.begin(),
                   _thread_refs_pending_delete.end());
    _thread_refs_pending_delete.clear();
  }
  for (size_t i = 0; i < pending.size(); i++) {
    jni->DeleteGlobalRef(pending[i]);
  }
}

