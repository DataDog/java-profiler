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

void ReferenceChainTracker::descendFromAnchor(
    jvmtiEnv *jvmti, JNIEnv *jni, jobject anchor, jlong anchor_tag,
    u32 anchor_depth, jlong anchor_descend_class_tag, int budget,
    int *edges_admitted, bool *truncated, bool *frontier_cap_hit,
    u64 *safepoint_ticks) {
  ReferenceChainPassContext ctx;
  ctx.tracker = this;
  ctx.frontier = _frontier;
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
  u64 follow_start_ticks = TSC::ticks();
  jvmti->FollowReferences(0, nullptr, anchor, &callbacks, &ctx);
  *safepoint_ticks += TSC::ticks() - follow_start_ticks;
  *edges_admitted += ctx.edges_admitted;
  *truncated = *truncated || ctx.truncated;
  *frontier_cap_hit = *frontier_cap_hit || ctx.frontier_cap_hit;
}

std::vector<jlong>
ReferenceChainTracker::collectStaticFieldAnchorsForRotation(int max_count) {
  std::vector<jlong> selected;
  if (max_count <= 0 || _static_anchor_index.empty()) {
    return selected;
  }
  // Tiered selection over _static_anchor_index (O(anchors) per pass, under ONE shared lock - the
  // lookups below are lookupLocked()).
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
  std::vector<TierPick> leak_picks;
  std::vector<TierPick> fresh_picks;
  std::vector<TierPick> container_picks;
  std::vector<TierPick> other_picks;
  leak_picks.reserve(16);
  // Fresh picks kept by the queue drain (bounded by max_count) - used to keep the fair-tier
  // consumption below from double-selecting them.
  std::unordered_set<jlong> fresh_kept_tags;
  const size_t fresh_queue_len = _static_anchor_fresh_queue.size();
  _frontier->withSharedLock([&](const FrontierTable *frontier) {
    // Index scan: partition every eligible anchor into the leak tier or one of the two fair tiers
    // (the fresh lane is decided by the queue drain below - a fresh-kept anchor also lands in a
    // fair pick vector here and is skipped at consumption time via fresh_kept_tags).
    for (size_t i = 0; i < idx_size; i++) {
      jlong tag = _static_anchor_index[i];
      FrontierEntry entry{};
      if (!frontier->lookupLocked(tag, &entry) ||
          entry.parent_tag != 0 ||
          (entry.root_kind != (u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD &&
           entry.root_kind != (u8)JVMTI_HEAP_REFERENCE_JNI_GLOBAL) ||
          (entry.state != FrontierEntryState::FRONTIER &&
           entry.state != FrontierEntryState::EXPANDED) ||
          isQueuedForRotation(tag)) {
        continue;
      }
      if (entry.leak_tag != 0) {
        leak_picks.push_back(TierPick{i, tag});
      } else if (i < _static_anchor_own_class_tags.size()) {
        auto shape_it =
            _class_shape_cache.find(_static_anchor_own_class_tags[i]);
        if (shape_it != _class_shape_cache.end() &&
            shape_it->second == (u8)AnchorClassShape::CONTAINER) {
          container_picks.push_back(TierPick{i, tag});
        } else {
          other_picks.push_back(TierPick{i, tag});
        }
      } else {
        other_picks.push_back(TierPick{i, tag});
      }
    }
    // Fresh-lane drain. Every queue entry is popped (its ONE first look is spent either way): kept
    // if eligible AND (container-shaped OR not-yet-classified) AND room remains in the budget;
    // dropped otherwise.
    int fresh_room = max_count - (int)leak_picks.size();
    size_t drain_pos = fresh_queue_len <= idx_size ? idx_size - fresh_queue_len : 0;
    while (!_static_anchor_fresh_queue.empty()) {
      if (fresh_room <= 0) {
        // Budget exhausted before the queue drained: everything remaining spends its first look now
        // and falls back to the fair tiers at its index position (covered, not urgent).
        _static_anchor_fresh_queue.clear();
        break;
      }
      jlong tag = _static_anchor_fresh_queue.front();
      _static_anchor_fresh_queue.pop_front();
      size_t pos = drain_pos;
      drain_pos++;
      if (pos >= idx_size || _static_anchor_index[pos] != tag) {
        // The suffix-window invariant broke (cannot happen today; defensive): fall back to a search
        // rather than mis-shape the entry - the queue is small, this is not a hot path once
        // healthy.
        auto it =
            std::find(_static_anchor_index.begin(),
                     _static_anchor_index.end(), tag);
        if (it == _static_anchor_index.end()) {
          continue;
        }
        pos = (size_t)(it - _static_anchor_index.begin());
      }
      FrontierEntry entry{};
      if (!frontier->lookupLocked(tag, &entry) ||
          entry.parent_tag != 0 ||
          (entry.root_kind != (u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD &&
           entry.root_kind != (u8)JVMTI_HEAP_REFERENCE_JNI_GLOBAL) ||
          (entry.state != FrontierEntryState::FRONTIER &&
           entry.state != FrontierEntryState::EXPANDED) ||
          isQueuedForRotation(tag) || entry.leak_tag != 0) {
        continue; // dead/demoted/queued/leak-tier: first look spent, not
                  // fresh-kept (the leak tier selects it via the scan if it is leak-tagged)
      }
      bool keep = false; // container or not-yet-classified rides the
                         // lane; the wrapper admits one pass before reconcile can classify its
                         // class
      if (pos < _static_anchor_own_class_tags.size()) {
        auto shape_it =
            _class_shape_cache.find(_static_anchor_own_class_tags[pos]);
        keep = shape_it == _class_shape_cache.end() ||
               shape_it->second == (u8)AnchorClassShape::CONTAINER;
      } else {
        keep = true; // no own-class tag recorded - treat as unknown
      }
      if (!keep) {
        continue; // classified non-container: the other tier owns it
      }
      fresh_picks.push_back(TierPick{pos, tag});
      fresh_kept_tags.insert(tag);
      fresh_room--;
    }
  });
  // Cursor-fair consumption of one tier: scan picks (sorted by pos by construction) starting at
  // entries with pos >= cursor, stop at `want` OR at the lap end (NO within-call wrap: re-walking
  // anchors this same call already covered would waste walk budget - the leftover budget flows to
  // the next tier instead, and the cursor resets to 0 so the NEXT call starts a fresh lap).
  auto consume_tier_fair = [&](const std::vector<TierPick> &picks,
                               size_t &cursor, int want) {
    int took = 0;
    if (want <= 0 || picks.empty()) {
      return took;
    }
    size_t consumed_pos = 0;
    for (size_t k = 0; k < picks.size() && took < want; k++) {
      const TierPick &p = picks[k];
      if (p.pos < cursor) {
        continue;
      }
      if (fresh_kept_tags.count(p.tag) > 0) {
        continue;
      }
      selected.push_back(p.tag);
      consumed_pos = p.pos;
      took++;
    }
    if (took > 0) {
      cursor = consumed_pos + 1 >= idx_size ? 0 : consumed_pos + 1;
    } else {
      // Took nothing AND no pick sits at or ahead of the cursor: this lap
      // already passed every current member of the tier (members selected in
      // earlier calls and since demoted out of eligibility). Without a reset
      // the cursor never wraps again - every later call skips them all
      // (p.pos < cursor) and the tier starves until a NEW anchor is appended
      // at a higher pos. Treat the lap as completed-but-unproductive and
      // restart it, matching the wrap semantics applied above.
      bool any_ahead = false;
      for (const TierPick &p : picks) {
        if (p.pos >= cursor) {
          any_ahead = true;
          break;
        }
      }
      if (!any_ahead) {
        cursor = 0;
      }
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
  // Fresh lane: queue order (admission order) so a burst larger than the budget spends the oldest
  // first looks first and nothing jumps the queue; outranked fresh anchors fall back to the fair
  // tiers at their positions (the drain already dropped them from the queue).
  for (const TierPick &p : fresh_picks) {
    if (budget_left <= 0) {
      break;
    }
    selected.push_back(p.tag);
    budget_left--;
  }
  budget_left -= consume_tier_fair(container_picks, _anchor_container_cursor,
                                    budget_left);
  // The other tier is the last consumer of the budget - its leftover has no further reader, so
  // don't accumulate it back into budget_left (a dead store clang scan-build flags).
  consume_tier_fair(other_picks, _anchor_other_cursor, budget_left);
  return selected;
}

void ReferenceChainTracker::pushAtRiskStaticAnchor(jlong tag, u32 klass_id) {
  if (_static_anchor_fifo_set.contains(tag)) {
    return;
  }
  if (_static_anchor_fifo.size() >= STATIC_ANCHOR_FIFO_CAP) {
    // The per-class quota prevents a single class from saturating this queue.
    return;
  }
  auto count_it = _static_anchor_fifo_klass_counts.find(klass_id);
  if (count_it != _static_anchor_fifo_klass_counts.end() &&
      count_it->second >= STATIC_ANCHOR_ATRISK_PER_KLASS_CAP) {
    // Per-class quota drop: this class already holds its share of the lane, and its oldest entry
    // drains within a few passes (STATIC_ANCHOR_FIFO_DRAIN=16/pass).
    return;
  }
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
  // Dedup: a push at first admission and another at upgrade would double-add.
  if (!_static_anchor_index_tags.insert(tag).second) {
    return;
  }
  _static_anchor_index.push_back(tag);
  _static_anchor_own_class_tags.push_back(own_class_tag);
  // Walk newly admitted anchors before the fair cursors.
  _static_anchor_fresh_queue.push_back(tag);
  if (_static_anchor_fresh_queue.size() > STATIC_ANCHOR_FRESH_CAP) {
    _static_anchor_fresh_queue.pop_front();
  }
}

bool ReferenceChainTracker::resolveContainerInterfaceTags(
    jvmtiEnv *jvmti, JNIEnv *jni) {
  if (_collection_iface_class_tag != 0 && _map_iface_class_tag != 0) {
    return true;
  }
  // resolveLoadedClasses() tags every loaded class (including these bootstrap interfaces) with its
  // class-tag-allocator tag (a NEGATIVE value - see nextClassTag()'s own comment) before any anchor
  // can be admitted, but classify defensively: if an interface object somehow carries no tag yet,
  // mint one via the shared allocator (same sequence resolveLoadedClasses() itself uses) so the
  // comparison below is well-defined.
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
    jlong tag = 0;
    bool ok = jvmti->GetTag(local, &tag) == JVMTI_ERROR_NONE;
    if (ok && tag == 0) {
      jlong new_tag = nextClassTag();
      if (jvmti->SetTag(local, new_tag) == JVMTI_ERROR_NONE) {
        // Adopt-on-reread, same cross-tracker race as
        // resolveLoadedClasses()/mintStableClassTagIfNeeded(): another tracker may have installed
        // its own tag between our GetTag and SetTag - keep the one tag the interface object
        // carries.
        jlong installed = 0;
        if (jvmti->GetTag(local, &installed) == JVMTI_ERROR_NONE &&
            installed != 0) {
          tag = installed;
        } else {
          tag = new_tag;
        }
      } else {
        ok = false;
      }
    }
    if (ok && tag != 0) {
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
  // BFS over the superclass chain + every visited class's interfaces, comparing GetTag() against
  // the two cached interface class tags.
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

void ReferenceChainTracker::reconcileAnchorClassShapes(jvmtiEnv *jvmti,
                                                        JNIEnv *jni) {
  if (jni == nullptr) {
    return;
  }
  if (_static_anchor_own_class_tags.empty()) {
    return;
  }
  // Collect up to ANCHOR_SHAPE_RECONCILE_BUDGET distinct class tags that appear in the anchor index
  // but are not yet classified.
  std::vector<jlong> unknown;
  unknown.reserve(8);
  std::unordered_set<jlong> seen;
  for (jlong class_tag : _static_anchor_own_class_tags) {
    if (class_tag == 0 || seen.count(class_tag) > 0 ||
        _class_shape_cache.count(class_tag) > 0) {
      continue;
    }
    seen.insert(class_tag);
    unknown.push_back(class_tag);
    if ((int)unknown.size() >= ANCHOR_SHAPE_RECONCILE_BUDGET) {
      break;
    }
  }
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

void ReferenceChainTracker::walkStaticFieldAnchors(
    jvmtiEnv *jvmti, JNIEnv *jni, const std::vector<jlong> &anchor_tags,
    int budget, int *edges_admitted, bool *truncated, bool *frontier_cap_hit,
    u64 *safepoint_ticks, std::vector<jlong> *unwalked) {
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
    descendFromAnchor(jvmti, jni, objects[i], resolved_tags[i], entry.depth,
                      /*anchor_descend_class_tag=*/0, remaining, edges_admitted,
                      truncated, frontier_cap_hit, safepoint_ticks);
    TEST_LOG("ReferenceChainTracker::walkStaticFieldAnchors anchor walk "
             "outcome tag=%lld edges=%d truncated=%d cap_hit=%d",
             (long long)resolved_tags[i], *edges_admitted - edges_before,
             (int)*truncated, (int)*frontier_cap_hit);
    walked++;
    jni->DeleteLocalRef(objects[i]);
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
    bool *truncated, bool *frontier_cap_hit, u64 *safepoint_ticks) {
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
          descendFromAnchor(jvmti, jni, thread_obj, anchor_tag, anchor_depth,
                            descend_class_tag, remaining, edges_admitted,
                            truncated, frontier_cap_hit, safepoint_ticks);
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
  if (!_enabled || jvmti == nullptr || jni == nullptr) {
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
  if (!_enabled || jni == nullptr || thread == nullptr) {
    return;
  }
  jobject ref = jni->NewGlobalRef(thread);
  if (ref == nullptr) {
    return;
  }
  MutexLocker ml(_thread_objects_lock);
  auto it = _thread_objects.find(tid);
  if (it != _thread_objects.end()) {
    // Same deferred-deletion rule as unregisterThreadObject(): a walk may still hold a copy of the
    // replaced ref.
    _thread_refs_pending_delete.push_back(it->second);
  }
  _thread_objects[tid] = ref;
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

