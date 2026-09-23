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

// Heap-walk engine

void ReferenceChainTracker::resolveLoadedClasses(jvmtiEnv *jvmti,
                                                  JNIEnv *jni) {
  // Profiler::start() resets the class-name StringDictionary (_class_map.clearAll(), profiler.cpp)
  // whenever `reset || _start_time == 0` - which restarts its id namespace at 1, but does NOT touch
  // any class's JVMTI-level class-object tag (JVM-level state, unrelated to our dictionary).
  u64 current_generation = Profiler::instance()->classMap()->generation();
  bool class_map_reset = current_generation != _last_class_map_generation;
  if (class_map_reset) {
    TEST_LOG_SUMMARY("ReferenceChainTracker::resolveLoadedClasses class_map generation "
             "changed: old=%llu new=%llu - clearing _class_tags and "
             "candidate klass_ids may be stale",
             (unsigned long long)_last_class_map_generation,
             (unsigned long long)current_generation);
    _class_tags.clear();
    // Force the scan below to run even if GetLoadedClasses()'s count happens to match the last-seen
    // count - -1 can never equal `class_count` (always >= 0), unlike 0 which is a legitimate "no
    // classes loaded yet" starting value.
    _last_resolved_class_count = -1;
    _last_class_map_generation = current_generation;
  }

  jclass *classes = nullptr;
  jint class_count = 0;
  if (jvmti->GetLoadedClasses(&class_count, &classes) != JVMTI_ERROR_NONE ||
      classes == nullptr) {
    return;
  }

  // Skip the per-class GetTag()/GetClassSignature() scan entirely once the loaded-class count has
  // not CHANGED since the last time this ran it: every already-tagged class stays tagged forever
  // (tags are never cleared once assigned - see _class_tags' own comment), so a resumed pass with
  // no newly-loaded classes has nothing left to resolve.
  if (class_count != _last_resolved_class_count) {
    for (jint i = 0; i < class_count; i++) {
      jclass klass = classes[i];
      jlong tag = 0;
      // Resolve if not yet tagged (ordinary case: a newly-loaded class), or unconditionally on a
      // class-map reset (class_map_reset above) - a class already tagged from a prior generation
      // still carries that same JVMTI tag (untouched by clearAll()), but the dictionary id it used
      // to map to is gone, so its name must be re-resolved into the new generation too.
      if (jvmti->GetTag(klass, &tag) == JVMTI_ERROR_NONE &&
          (tag == 0 || class_map_reset)) {
        // Resolve its name now, via the same GetClassSignature + normalizeClassSignature +
        // Profiler::lookupClass sequence ObjectSampler::recordAllocation() already uses
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
              // Reuse the existing tag if this class was already tagged by a prior generation -
              // only the resolved id needs refreshing, not the tag identity heapReferenceCallback()
              // keys off of.
              jlong class_tag = tag != 0 ? tag : nextClassTag();
              if (tag != 0 ||
                  jvmti->SetTag(klass, class_tag) == JVMTI_ERROR_NONE) {
                if (tag == 0) {
                  // Adopt the tag actually installed on the class object: LivenessTracker's
                  // mintStableClassTagIfNeeded() may have installed its own tag between our GetTag
                  // and SetTag (two SetTag calls on the same untagged class - the last writer wins
                  // on the class).
                  jlong installed = 0;
                  if (jvmti->GetTag(klass, &installed) == JVMTI_ERROR_NONE &&
                      installed != 0) {
                    class_tag = installed;
                  }
                }
                _class_tags.insert(class_tag, (u32)id);
              }
            }
          }
          jvmti->Deallocate((unsigned char *)class_name);
        }
      }
      // GetLoadedClasses() hands back class_count fresh JNI local refs - delete each immediately
      // rather than holding all of them alive at once, since class_count can run into the
      // thousands.
      if (jni != nullptr) {
        jni->DeleteLocalRef(klass);
      }
    }
    _last_resolved_class_count = class_count;
  } else if (jni != nullptr) {
    // Still owe DeleteLocalRef for every fresh local ref GetLoadedClasses() just handed back, even
    // though the scan above was skipped.
    for (jint i = 0; i < class_count; i++) {
      jni->DeleteLocalRef(classes[i]);
    }
  }
  jvmti->Deallocate((unsigned char *)classes);
}

jint JNICALL ReferenceChainTracker::heapReferenceCallback(
    jvmtiHeapReferenceKind reference_kind,
    const jvmtiHeapReferenceInfo *reference_info, jlong class_tag,
    jlong referrer_class_tag, jlong size, jlong *tag_ptr,
    jlong *referrer_tag_ptr, jint length, void *user_data) {
  ReferenceChainPassContext *ctx = (ReferenceChainPassContext *)user_data;

  if (ctx->tracker->_abort_pass_requested.load(std::memory_order_relaxed)) {
    // stopThread() has set this right before pthread_kill()/pthread_join() - see that method's own
    // comment.
    ctx->truncated = true;
    return JVMTI_VISIT_ABORT;
  }

  if (ctx->tracker->_pass_deadline_ns != 0 &&
      (++ctx->deadline_check_counter & 0xFFF) == 0 &&
      OS::nanotime() >= ctx->tracker->_pass_deadline_ns) {
    // This pass has run past its wall-clock share (see _pass_deadline_ns's own comment) - treat it
    // exactly like ordinary budget exhaustion so it ends early without abandoning the search; a
    // later pass re-enumerates whatever roots/edges this one didn't get to.
    ctx->truncated = true;
    return JVMTI_VISIT_ABORT;
  }

  // Retention-edge identity for every admission site below: the JVMTI heap callback's field ordinal
  // (the JVMTI-SPECIFICATION numbering over the referrer's flattened field space - see
  // FrontierEntry:: referrer_field_index's own comment) for FIELD/STATIC_FIELD edges, -1 otherwise;
  // and the referrer's class tag when the referrer is a CLASS OBJECT (root-attached static edges -
  // interior hops get their referrer class from the parent entry at chain-reconstruction time, so
  // only the parent_tag==0 case needs it recorded here).
  jint edge_field_index = -1;
  if (reference_info != nullptr &&
      (reference_kind == JVMTI_HEAP_REFERENCE_FIELD ||
       reference_kind == JVMTI_HEAP_REFERENCE_STATIC_FIELD)) {
    edge_field_index = reference_info->field.index;
  }
  jlong edge_referrer_class_tag = 0;
  if (referrer_tag_ptr != nullptr && *referrer_tag_ptr < 0) {
    edge_referrer_class_tag = *referrer_tag_ptr;
  }

  // Canary pruning: if this object is the pre-tagged representative of a leaked candidate (marker
  // tag MARKER_TAG_BASE - i, negative), record its chain link but do NOT enqueue its children
  // (treat as a leaf).
  if (ctx->tracker->_candidate_count > 0 &&
      *tag_ptr <= ReferenceChainTracker::MARKER_TAG_BASE) {
    int candidate_idx = (int)(ReferenceChainTracker::MARKER_TAG_BASE - *tag_ptr);
    if (candidate_idx >= 0 && candidate_idx < ctx->tracker->_candidate_count) {
      jlong rtag = (referrer_tag_ptr != nullptr) ? *referrer_tag_ptr : 0;
      u32 candidate_klass = ctx->tracker->classTags()->resolve(class_tag);
      if (rtag > 0) {
        FrontierEntry parent{};
        if (ctx->frontier->lookup(rtag, &parent)) {
          // Use the marker tag itself as the frontier table key - it is already a unique
          // per-candidate value, so no nextTag() is needed.
          jlong frontier_tag = *tag_ptr;
          ctx->frontier->insert(frontier_tag, rtag,
                                  parent.referrer_klass,
                                  parent.depth + 1,
                                  FrontierEntryState::FRONTIER,
                                  parent.root_kind,
                                  /*class_tag=*/0, edge_field_index,
                                  (u8)reference_kind);
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
                                (u8)reference_kind,
                                /*class_tag=*/0, edge_field_index,
                                /*edge_kind=*/0, edge_referrer_class_tag);
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
      // admitStaticFieldRoots()'s own holder[i] -> class edge: referrer_tag_ptr points at the
      // transient, never-tagged seed array itself (tag 0), not at a frontier-admitted parent.
      return JVMTI_VISIT_OBJECTS;
    }
    // Referee is a class object already tagged negative by resolveLoadedClasses() (that pre-pass
    // runs before FollowReferences in runPass(), so every loaded class already carries a negative
    // tag by this point).
    return 0;
  }
  if (reference_kind == JVMTI_HEAP_REFERENCE_CLASS ||
      reference_kind == JVMTI_HEAP_REFERENCE_SYSTEM_CLASS) {
    // Definitionally a class by reference_kind (CLASS: "reference from an object to its class";
    // SYSTEM_CLASS: a root reference to a class) even if resolveLoadedClasses() failed to
    // resolve/tag this particular one (e.g. a transient StringDictionary contention failure) and
    // its tag is therefore not yet negative.
    return 0;
  }

  if (ctx->truncated) {
    // Defensive: FollowReferences should already have stopped delivering callbacks after a
    // JVMTI_VISIT_ABORT return below; this just avoids doing further work if one more callback
    // arrives anyway.
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
      // lookup() failing for a positive rtag should not happen - a referrer must already be one of
      // our tagged frontier objects for its own outgoing edges to be traversed at all
      // (FollowReferences only explores past an object this callback returned JVMTI_VISIT_OBJECTS
      // for) - but fall back to root-like (parent_tag=0/depth=0) rather than corrupt the chain if
      // it ever does.
    }
    // rtag < 0: referrer is a pre-tagged class object (e.g. a static field holding this reference)
    // - treated as root-like rather than attributed to a parent hop, since class objects are never
    // admitted as frontier entries and so have no depth/parent_tag of their own (see the *tag_ptr <
    // 0 check above).
  }
  // referrer_tag_ptr == nullptr: a heap-root reference (JNI global, thread stack local/JNI local,
  // monitor, thread, system class, ...) - parent_tag and depth stay 0.

  if (depth >= (u32)ctx->hop_cap) {
    // Hop cap: do not admit this object into the frontier, and do not expand further from it -
    // enforced here rather than discovering-then-discarding.
    return 0;
  }

  if (ctx->static_field_seed && referrer_tag_ptr != nullptr &&
      *referrer_tag_ptr < 0) {
    // Referrer is the class object opened by the static_field_seed branch above.
    if (*referrer_tag_ptr != ctx->_seed_class_tag) {
      ctx->_seed_class_tag = *referrer_tag_ptr;
      ctx->_class_other_admitted = 0;
      ctx->_classes_in_chunk_visited++;
    }
    if (reference_kind != JVMTI_HEAP_REFERENCE_STATIC_FIELD) {
      if (ctx->_class_other_cap > 0 &&
          ctx->_class_other_admitted >= ctx->_class_other_cap) {
        // Quota exhausted for this class - drop the edge. Count every drop, and count the first
        // drop for this class separately so the two counters together distinguish "a few fat
        // outlier classes dropping many edges" from "systematic drops across almost all classes"
        // (cap too low).
        Counters::increment(REFERENCE_CHAIN_STATIC_SWEEP_NON_STATIC_DROPPED);
        if (ctx->_class_other_admitted == ctx->_class_other_cap) {
          Counters::increment(REFERENCE_CHAIN_STATIC_SWEEP_CLASSES_CAPPED);
        }
        return 0;
      }
      ctx->_class_other_admitted++;
    }
  }

  // Leak tag: this object was directly tagged by LivenessTracker's tagLeakInstances() because it's
  // a tracked leaking object.
  if (isLeakTag(*tag_ptr)) {
    jlong leak_tag = *tag_ptr;
    // Allocate a frontier tag for this object
    jlong frontier_tag = ctx->tracker->nextTag();
    u32 referrer_klass = ctx->tracker->classTags()->resolve(class_tag);
    u8 root_kind = parent_tag == 0 ? (u8)reference_kind : 0;
    if (ctx->frontier->insert(frontier_tag, parent_tag, referrer_klass,
                               depth, FrontierEntryState::FRONTIER,
                               root_kind, class_tag, edge_field_index,
                               (u8)reference_kind,
                               parent_tag == 0 ? edge_referrer_class_tag : 0)) {
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
      // Index maintenance: a leak-tagged object admitted root-attached by a durable root edge (e.g.
      // a static field directly holding a tagged chunk) is the highest-priority anchor tier
      // (leak_tag != 0).
      if (parent_tag == 0 &&
          (root_kind == (u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD ||
           root_kind == (u8)JVMTI_HEAP_REFERENCE_JNI_GLOBAL)) {
        ctx->tracker->addToStaticAnchorIndex(frontier_tag, class_tag,
                                             root_kind);
      }
      // Auto-mark: record this as a discovered instance, with eviction rights over uncorrelated
      // noise slots (see recordDiscoveredInstance).
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

  // DESCEND-WALK GATES (no-ops on every ordinary walk - the ReferenceChainPassContext fields below
  // are zero-initialized and only descendFromAnchor() sets them).
  if (ctx->_no_descend_class_tag_count > 0) {
    for (int i = 0; i < ctx->_no_descend_class_tag_count; i++) {
      if (ctx->_no_descend_class_tags[i] == class_tag) {
        return 0;
      }
    }
  }
  if (ctx->_descent_anchor_tag != 0 && ctx->_anchor_descend_class_tag != 0 &&
      referrer_tag_ptr != nullptr &&
      *referrer_tag_ptr == ctx->_descent_anchor_tag &&
      class_tag != ctx->_anchor_descend_class_tag) {
    // This descend walk's ANCHOR object's own edge, and the referee is not the gate class (see
    // ReferenceChainPassContext::_anchor_descend_class_tag's own comment - e.g.
    // walkCandidateThreadLocals() walks ONLY the Thread's ThreadLocalMap edges, never enumerating
    // the Thread's other fields).
    return 0;
  }

  if (*tag_ptr == 0) {
    // First time this object is visited in this pass.
    u32 referrer_klass = ctx->tracker->classTags()->resolve(class_tag);
    // reference_kind describes this admitting edge; only meaningful for a root-attached entry
    // (parent_tag == 0) - see FrontierEntry::root_kind's own comment for why a non-root entry's
    // edge kind is not recorded.
    u8 root_kind = parent_tag == 0 ? (u8)reference_kind : 0;
    ReferenceChainTracker::AdmitResult result = ctx->tracker->admitObject(
        ctx->frontier, ctx->hop_cap, ctx->budget, &ctx->edges_admitted,
        tag_ptr, parent_tag, referrer_klass, depth, root_kind, class_tag,
        ctx->admit_priority, edge_field_index, (u8)reference_kind,
        parent_tag == 0 ? edge_referrer_class_tag : 0);
    switch (result) {
    case ReferenceChainTracker::AdmitResult::BUDGET_EXHAUSTED:
      ctx->truncated = true;
      return JVMTI_VISIT_ABORT;
    case ReferenceChainTracker::AdmitResult::FRONTIER_CAP_HIT:
      // Stop this pass when the frontier table is full.
      ctx->truncated = true;
      ctx->frontier_cap_hit = true;
      return JVMTI_VISIT_ABORT;
    default:
      // ADMITTED, or HOP_CAP/ALREADY_ADMITTED (neither reachable here: the hop-cap check above
      // already returned before this branch, and *tag_ptr == 0 rules out ALREADY_ADMITTED) -
      // nothing further to do.
      break;
    }
    // Index maintenance: track root-attached durable anchors for O(anchors) collector iteration
    // instead of O(frontier_size) table scan.
    if (result == ReferenceChainTracker::AdmitResult::ADMITTED &&
        parent_tag == 0) {
      ctx->tracker->addToStaticAnchorIndex(*tag_ptr, class_tag, root_kind);
    }
    // Auto-mark: if this object's class matches a watched leak class, record its frontier tag so
    // pollWatchedTargets() can build a chain event for it.
    if (result == ReferenceChainTracker::AdmitResult::ADMITTED &&
        ctx->tracker->_candidate_count > 0) {
      u32 klass_id = ctx->tracker->classTags()->resolve(class_tag);
      if (klass_id == 0) {
        // class_tag not in _class_tags - either class map rotated (resolveLoadedClasses hasn't
        // re-resolved yet) or this class was never tagged.
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
          // klass_id resolved but doesn't match any candidate - likely class map rotation made
          // candidate klass_ids stale
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
  } else if (*tag_ptr > 0) {
    // Already-tagged object reached via a new edge. This arm - NOT the first-admission block above
    // - is where an already-admitted entry's shape can be corrected:
    // improveChain/reparentToDurableRoot for a deeper/equal-durable path,
    // maybeUpgradeRootAttachedRootKind for a new root-like edge.
    if (parent_tag != 0) {
      // This new path is deeper - replace the shallow root-attached entry with the deeper
      // chain-attached entry.
      u32 referrer_klass = ctx->tracker->classTags()->resolve(class_tag);
      // Pre-read the CURRENT shape: if improveChain() below succeeds, this root-attached durable
      // entry is about to be replaced with a deeper chain-attached one - i.e. it is leaving the
      // population collectStaticFieldAnchorsForRotation() can select, at exactly this moment.
      FrontierEntry pre_improve_entry{};
      bool was_root_attached_durable =
          ctx->frontier->lookup(*tag_ptr, &pre_improve_entry) &&
          pre_improve_entry.parent_tag == 0 &&
          rootKindDurability(pre_improve_entry.root_kind) >= 2;
      if (ctx->frontier->improveChain(*tag_ptr, parent_tag, referrer_klass,
                                       depth, 0, edge_field_index,
                                       (u8)reference_kind)) {
        // Chain was improved — invalidate any cached chain for this tag so pollWatchedTargets
        // rebuilds it with the deeper path.
        ctx->tracker->invalidateResolvedChain(*tag_ptr);
        if (was_root_attached_durable) {
          // Demotion push (B'): the replaced entry's static/JNI-global attribution was its only
          // anchor-tier eligibility, and it is gone now.
          ctx->tracker->pushAtRiskStaticAnchor(
              *tag_ptr, ctx->tracker->classTags()->resolve(class_tag));
        }
      } else if (ctx->frontier->reparentToDurableRoot(
                     *tag_ptr, parent_tag, referrer_klass, edge_field_index,
                     (u8)reference_kind)) {
        // Equal-depth re-parent from a transient root to a durable one (improveChain() cannot
        // express it - see its declaration) - same cache invalidation so the rebuilt chain uses the
        // durable root.
        ctx->tracker->invalidateResolvedChain(*tag_ptr);
      }
    } else {
      // Already-admitted entry reached via a NEW root-like edge (parent_tag == 0): the static-field
      // sweep's class -> field edge reports the class as the referrer with a negative tag, which
      // the rtag < 0 branch above treats as root-like (class objects are never frontier entries),
      // and heap-root references arrive here with referrer_tag_ptr == nullptr.
      if (ctx->tracker->maybeUpgradeRootAttachedRootKind(ctx->frontier,
                                                          *tag_ptr,
                                                          (u8)reference_kind)) {
        ctx->tracker->invalidateResolvedChain(*tag_ptr);
      } else if (reference_kind == JVMTI_HEAP_REFERENCE_STATIC_FIELD) {
        // The upgrade refused (maybeUpgradeRootAttachedRootKind returns false for parent_tag != 0
        // by design), so this STATIC_FIELD edge just proved an at-risk static attachment the anchor
        // tier's parent_tag == 0 filter can never see: a holder already admitted as a non-root
        // child (find-anchor-holder-eviction).
        FrontierEntry entry{};
        if (ctx->frontier->lookup(*tag_ptr, &entry) &&
            entry.parent_tag != 0) {
          ctx->tracker->pushAtRiskStaticAnchor(
              *tag_ptr, ctx->tracker->classTags()->resolve(class_tag));
        }
      }
    }
  }

  if (ctx->batch_tags != nullptr) {
    // ARRAY-HOLDER BATCHING one-hop descent control (see ReferenceChainPassContext:: batch_tags).
    jlong my_tag = *tag_ptr;
    if (my_tag > 0 && ctx->batch_tags->count(my_tag) != 0) {
      // The previously visited batch entry (if any) is now fully processed - record it for the
      // order-independent truncated-batch resume (see
      // ReferenceChainPassContext::_completed_batch_tags' own comment).
      if (ctx->_last_visited_batch_tag != 0 &&
          ctx->_last_visited_batch_tag != my_tag &&
          ctx->_completed_batch_tags != nullptr) {
        ctx->_completed_batch_tags->insert(ctx->_last_visited_batch_tag);
      }
      // Track this batch entry as visited for the rolling resume cursor (see
      // _last_visited_batch_tag's own comment).
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
    u8 root_kind, jlong class_tag, bool priority,
    jint edge_field_index, u8 edge_kind, jlong edge_referrer_class_tag) {
  // edge_* default-declared in the header; heapRootCallback() passes the defaults (a root reference
  // is not a field edge) unchanged.
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
                         FrontierEntryState::FRONTIER, root_kind, class_tag,
                         edge_field_index, edge_kind, edge_referrer_class_tag)) {
    return AdmitResult::FRONTIER_CAP_HIT;
  }
  *tag_ptr = tag;
  (*edges_admitted)++;
  // Queue for expandFrontier()/markAllFrontierExpanded() - see _pending_expand's/_priority_expand's
  // own declaration comments for why this replaces a scan over the admitted range, and for why a
  // rotation-discovered child (priority=true) skips the ordinary backlog.
  if (priority && _priority_expand.size() < PRIORITY_EXPAND_CAP) {
    _priority_expand.push_back(tag);
    _priority_expand_set.insert(tag);
  } else {
    // Priority lane full: the rotation backpressure falls back to the ordinary backlog rather than
    // silently dropping the re-discovered subtree (see PRIORITY_EXPAND_CAP's own comment).
    _pending_expand.push_back(tag);
  }
  trackLeakAccumulation(frontier, class_tag, parent_tag, tag);
  return AdmitResult::ADMITTED;
}

void ReferenceChainTracker::trackLeakAccumulation(FrontierTable *frontier,
                                                   jlong class_tag,
                                                   jlong parent_tag,
                                                   jlong tag) {
  // Cheapest checks first: no klass_id is currently watched (the common case before hasLeakSignal()
  // has ever fired - see _watched_leak_klass_ids' own comment), or this admission has no real
  // parent to attribute to (a root-attached entry - nothing to aggregate by, since the "container"
  // concept this tracks is specifically about a PARENT object's field holding the leaf, not the
  // leaf itself being root-attached).
  if (_watched_leak_klass_count <= 0 || parent_tag == 0 || class_tag == 0) {
    return;
  }
  // (u32) truncation matches _watched_leak_klass_ids' own storage (see that field's comment) -
  // class tags are small, negative, sequentially-minted values in practice
  // (ClassTagAllocator::next()), so this never actually loses distinguishing information; it just
  // keeps the comparison and the signature-key packing below in the same 32-bit space both already
  // used for the (superseded) classMap-id scheme.
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
    // Parent since pruned/dead between its own admission and this child's, or admitted before this
    // field existed on it (should not happen in practice - class_tag is set at every admission -
    // but a stale/unknown parent identity is not something to attribute this observation to either
    // way.
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
    // The signature key for a given parent_tag is fixed once recorded (parent_entry.class_tag never
    // changes once admitted; the LEAF side of the key is fixed by which klass_id is currently
    // watched at the time of THIS call, which could in principle differ between two children of the
    // same parent if _watched_leak_klass_ids itself changed between them - overwrite rather than
    // accumulate under a stale key in that case, since the stored signature_key should always
    // reflect the most recently observed watched klass_id for this parent).
    it->second.signature_key = key;
    it->second.fanout++;
  }
  // ANCESTOR FANOUT: the direct parent is not necessarily the part of the holder chain that STAYS
  // LIVE.
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
    // pollWatchedTargets() can run before the first pass has ever created the frontier table -
    // nothing to seed from yet.
    return;
  }
  int table_size = _frontier->size();
  if (table_size <= 0) {
    return;
  }
  // Inlines trackLeakAccumulation()'s own signature/fanout update logic (rather than calling it per
  // matching entry) deliberately: this whole scan already holds _frontier's shared lock for its
  // duration (matching collectStaleExpandedEntriesForRotation()'s own lockShared() rationale - a
  // per-tag SpinLock acquisition would double the cost of this O(table_size) sweep), and
  // trackLeakAccumulation() takes that same lock itself via frontier->lookup() - calling it from
  // inside an already-held shared section would risk a reentrant-lock deadlock if a writer is ever
  // concurrently pending, so this uses lookupLocked() throughout instead.
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
    // Not root-attached - per this phase's option (a) resolution of the parent_tag==0/root_kind
    // invariant conflict (referenceChains.h's FrontierEntry::root_kind comment), only a
    // root-context update may ever write a non-zero root_kind, and only onto an entry that is
    // already root-attached.
    return false;
  }
  if (rootKindDurability(new_root_kind) <= rootKindDurability(entry.root_kind)) {
    return false;
  }
  frontier->updateRootKind(tag, new_root_kind);
  addToStaticAnchorIndex(tag, entry.class_tag, new_root_kind);
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

  // Held for the whole sweep below (potentially wrapping all the way around table_size) rather than
  // once per tag via lookup() - the same rationale as collectStaleExpandedEntriesForRotation()'s
  // own lockShared() use: a per-tag SpinLock acquisition would double this scan's cost under a
  // large frontier table.
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
        _priority_expand_set.insert(tag);
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
  // LEAK-PARENT PRIORITY, FAIR-SHARED WITH THE BLIND LAP: _leak_parent_fanout knows the EXPANDED
  // parents that actually lead to watched leak-klass children - re-walking one of those re-sees its
  // current children (improveChain() upgrades children first admitted via a shallower path,
  // leak-tag interception for the tagged ones) and catches elements added since its expansion,
  // which is exactly the mutation this rotation exists to observe.
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
      // Dead parent: either the frontier slot is gone entirely, or it was clear()'d (dead object /
      // restart wipe) - clear() marks the slot ABANDONED rather than removing it, so both
      // conditions must erase (tags are never reused within a search and the fanout is wiped on
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
      _priority_expand_set.insert(parent_tag);
      ++it;
    }
    _leak_parent_rotation_cursor += selected.size() + 1;
    if ((int)selected.size() >= max_count) {
      // Budget exhausted by the fanout alone (only possible for max_count == 1, where the fanout's
      // ceil-half share is the whole budget) - fanout-priority preserved, and the lap below has
      // nothing left to do this pass.
      return selected;
    }
  }
  if (_stale_expanded_rotation_cursor <= 0 ||
      _stale_expanded_rotation_cursor > table_size) {
    _stale_expanded_rotation_cursor = 1;
  }
  // Resume scanning from _stale_expanded_rotation_cursor rather than always restarting at tag 1: a
  // frontier table can accumulate far more than max_count entries that are EXPANDED and stay that
  // way forever (long-lived infrastructure objects - caches, maps, bootstrap classes).
  int deadline_check_counter = 0;
  jlong start_tag = _stale_expanded_rotation_cursor;
  jlong tag = start_tag;
  _frontier->withSharedLock([&](const FrontierTable *frontier) {
    do {
      if (_pass_deadline_ns != 0 &&
          (++deadline_check_counter & 0xFFF) == 0 &&
          OS::nanotime() >= _pass_deadline_ns) {
        // Ran past this pass's wall-clock share - stop scanning with whatever was already selected
        // (possibly none) and resume from here next call.
        break;
      }
      FrontierEntry entry{};
      if (frontier->lookupLocked(tag, &entry) &&
          entry.state == FrontierEntryState::EXPANDED &&
          !isQueuedForRotation(tag) &&
          _priority_expand.size() < PRIORITY_EXPAND_CAP) {
        selected.push_back(tag);
        _priority_expand.push_back(tag);
        _priority_expand_set.insert(tag);
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

// Select high-fanout parents of classes reported as growing.
std::vector<jlong>
ReferenceChainTracker::collectLeakAccumulationCandidatesForRotation(
    int max_count) {
  std::vector<jlong> selected;
  if (max_count <= 0 || _leak_signature_totals.empty()) {
    return selected;
  }

  // Tier 1: rank signatures by growth since the last pass's snapshot.
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
  // Roll the snapshot forward for the NEXT pass's comparison regardless of whether this pass found
  // a winner - a signature that didn't grow this pass still needs its current total remembered so a
  // future pass's delta is computed against the right baseline, not against however many passes ago
  // it was last checked.
  _leak_signature_prev_totals = _leak_signature_totals;
  if (!have_winner) {
    // Nothing grew since last pass - nothing to prioritize this tier this time
    // (collectStaleExpandedEntriesForRotation()'s unprioritized fallback still covers this
    // population eventually).
    return selected;
  }

  // Tier 2: within the winning signature only, rank concrete parent objects by their own fanout -
  // collected first, then partially sorted, since _leak_parent_fanout's total size is what bounds
  // this method's cost (not table_size), and is expected to be small (see that map's own comment).
  std::vector<std::pair<jlong, u32>> candidates; // (parent_tag, fanout)
  for (const auto &kv : _leak_parent_fanout) {
    if (kv.second.signature_key == winning_key && !isQueuedForRotation(kv.first)) {
      FrontierEntry entry{};
      if (_frontier->lookup(kv.first, &entry) &&
          (entry.state == FrontierEntryState::EXPANDED ||
           entry.state == FrontierEntryState::FRONTIER)) {
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
    _priority_expand_set.insert(c.first);
    FrontierEntry state_entry{};
    bool is_expanded = _frontier->lookup(c.first, &state_entry) &&
                       state_entry.state == FrontierEntryState::EXPANDED;
    TEST_LOG("ReferenceChainTracker::"
             "collectLeakAccumulationCandidatesForRotation selected "
             "parent_tag=%lld state=%s fanout=%u",
             (long long)c.first, is_expanded ? "EXPANDED" : "FRONTIER",
             c.second);
  }
  // Place the whole selection at the head of the priority lane, keeping the fanout ranking order
  // (see the FRONTIER-state case in the Tier 2 comment above for why the head and not the tail):
  // push_front reverses, so insert back-to-front.
  for (auto it = selected.rbegin(); it != selected.rend(); ++it) {
    _priority_expand.push_front(*it);
  }
  return selected;
}

