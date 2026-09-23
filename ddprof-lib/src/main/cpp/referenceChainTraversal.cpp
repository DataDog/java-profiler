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

// Manual walk driver - IterateOverReachableObjects root/stack-ref enumeration

namespace {
// jvmtiHeapRootKind (IterateOverReachableObjects's root/stack-ref callbacks, ordinals 1-7) and
// jvmtiHeapReferenceKind (FrontierEntry::root_kind's own type, FollowReferences' callback, ordinals
// 8/21-27) are different, disjoint enums per the real jvmti.h - storing a raw jvmtiHeapRootKind
// value into root_kind unmodified would make flightRecorder.cpp's rootKindName() report "unknown"
// for every root-callback-attributed chain.
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
  ReferenceChainPassContext *ctx = (ReferenceChainPassContext *)user_data;
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
    if (isLeakTag(*tag_ptr)) {
      // Leak-tagged object met as a DIRECT heap root (JNI global, stack local, ...): convert the
      // leak tag exactly like heapReferenceCallback()'s interception branch so a chain can be built
      // when the direct root is the only retention path.
      jlong leak_tag = *tag_ptr;
      jlong frontier_tag = ctx->tracker->nextTag();
      if (ctx->frontier->insert(frontier_tag, /*parent_tag=*/0, referrer_klass,
                                /*depth=*/0, FrontierEntryState::FRONTIER,
                                translated_root_kind, class_tag)) {
        ctx->frontier->setLeakTag(frontier_tag, leak_tag);
        *tag_ptr = frontier_tag;
        ctx->edges_admitted++;
        ctx->tracker->trackLeakAccumulation(ctx->frontier, class_tag, 0,
                                            frontier_tag);
        // Index maintenance, mirroring the edge path's interception branch: a leak-tagged root
        // attached by a durable root edge is the highest-priority anchor tier.
        if (translated_root_kind == (u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD ||
            translated_root_kind == (u8)JVMTI_HEAP_REFERENCE_JNI_GLOBAL) {
          ctx->tracker->addToStaticAnchorIndex(frontier_tag, class_tag,
                                               translated_root_kind);
        }
        if (ctx->tracker->_candidate_count > 0) {
          u32 klass_id = ctx->tracker->classTags()->resolve(class_tag);
          ctx->tracker->recordDiscoveredInstance(klass_id, frontier_tag, true);
        }
        // Queue for expandFrontier() - the plain backlog lane, mirroring admitObject()'s
        // non-priority push tail.
        ctx->tracker->_pending_expand.push_back(frontier_tag);
      } else {
        // Frontier cap hit - same outcome as admitObject()'s own failure.
        ctx->truncated = true;
        ctx->frontier_cap_hit = true;
        return JVMTI_ITERATION_ABORT;
      }
      break;
    }
    // Prefer the more durable root when an object is rediscovered.
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
  // Stack-local/JNI-local roots carry thread/frame/slot detail JVMTI reports via this callback's
  // richer shape, but FrontierEntry has nowhere to record it (depth/method/slot are not part of the
  // record) - admission is otherwise identical to heapRootCallback() above, so this just forwards.
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

  // Safe point to delete the global refs of threads that ended since the last drain: this runs on
  // the BFS thread before any walk phase, and refs erased from _thread_objects
  // (unregisterThreadObject()) can no longer be copied out by walkCandidateThreadLocals(), so no
  // walk holds them.
  releaseEndedThreadRefs(jni);

  *safepoint_ticks = 0;

  // Shared wall-clock ceiling for this whole call's static-field sweep, expandFrontier(), and
  // rotation sub-calls below (see _pass_deadline_ns's own comment) - deliberately NOT applied to
  // root/stack-ref enumeration itself, which is instead cadence-gated by run_root_enum/
  // ROOT_ENUM_MIN_INTERVAL_NS.
  _pass_deadline_ns = _effective_pause_target_ms > 0
                          ? OS::nanotime() + (u64)_effective_pause_target_ms * 1000000ULL
                          : 0;

  *edges_admitted = 0;
  *truncated = false;
  *frontier_cap_hit = false;

  // Reserve a slice for rotation up front, across all three tiers (see
  // ROOT_KIND_ROTATION_BUDGET/LEAK_ACCUMULATION_ROTATION_BUDGET/ STALE_EXPANDED_ROTATION_BUDGET's
  // own comments) so rotation still gets to run this pass even when ordinary work below spends
  // everything else and truncates.
  int rotation_reserved_budget = std::min(
      expand_budget / 2, ROOT_KIND_ROTATION_BUDGET +
                              LEAK_ACCUMULATION_ROTATION_BUDGET +
                              STALE_EXPANDED_ROTATION_BUDGET);
  int budget = expand_budget - rotation_reserved_budget;

  // Root/stack-ref enumeration alone (unlike a root-seeded FollowReferences call on the fallback
  // path) never discovers a root's own transitive children - IterateOverReachableObjects's
  // root/stack-ref callbacks are given no oop, only a tag_ptr (see heapRootCallback()'s own
  // comment) - so even when it runs this pass, the expandFrontier() call below is still needed to
  // make any further progress.
  if (run_root_enum) {
    ReferenceChainPassContext ctx;
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
    // ROOT_ENUM_MIN_INTERVAL_NS's own comment) - ctx.edges_admitted is written straight into
    // *edges_admitted so the static-field/expand/ rotation budget math below is never shrunk by
    // whatever root enumeration admitted.
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
      // Only a budget-exhausted truncation (not a frontier-cap-hit, which abandons the search
      // outright) is grounds to retry root enumeration on the very next pass - see
      // _root_enum_truncated_last_time's own comment.
      _root_enum_truncated_last_time = !ctx.frontier_cap_hit;
      return;
    }
    _root_enum_truncated_last_time = false;
  }

  int expand_phase_edges_admitted = 0;

  // Candidate-scoped reach, prong 1: descend-walk the current candidates' qualifying threads'
  // ThreadLocalMap subgraphs BEFORE any breadth-first work this pass - reaching the tagged
  // instances under a thread-retained holder must not queue behind the ordinary backlog (see
  // walkCandidateThreadLocals()'s own comment).
  if (_candidate_count > 0) {
    int thread_walk_edges_admitted = 0;
    bool thread_walk_truncated = false;
    bool thread_walk_frontier_cap_hit = false;
    // Give the thread walk its own fresh deadline so the root-enum walk above never eats its slice
    // (per-sub-op reset rationale, see expand below).
    _pass_deadline_ns = _effective_pause_target_ms > 0
                            ? OS::nanotime() +
                                  (u64)_effective_pause_target_ms * 1000000ULL
                            : 0;
    walkCandidateThreadLocals(jvmti, jni, budget, &thread_walk_edges_admitted,
                              &thread_walk_truncated,
                              &thread_walk_frontier_cap_hit, safepoint_ticks);
    expand_phase_edges_admitted += thread_walk_edges_admitted;
    *edges_admitted += thread_walk_edges_admitted;
    if (thread_walk_frontier_cap_hit) {
      // Frontier-cap mid-thread-walk is the same search-abandonment grounds as anywhere else - do
      // not spend more of this pass's budget.
      *truncated = true;
      *frontier_cap_hit = true;
      return;
    }
    if (thread_walk_truncated) {
      *truncated = true;
    }
  }

  // Static-field roots (SomeClass.staticField -> obj) are not reachable via
  // IterateOverReachableObjects' root/stack-ref callbacks above - see admitStaticFieldRoots()'s own
  // comment - so this pass would otherwise never discover an object retained only that way.
  TEST_LOG_SUMMARY("ReferenceChainTracker::runPassManualWalk static_sweep_gate "
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
    if (static_field_truncated) {
      *truncated = true;
      *frontier_cap_hit = static_field_frontier_cap_hit;
      if (static_field_frontier_cap_hit) {
        // Frontier-size cap hit while admitting static-field roots is the same "grounds to ABANDON
        // the whole search" outcome BUDGET_EXHAUSTED/FRONTIER_CAP_HIT handling above gives root
        // enumeration - do not spend any more of this pass's budget on the ordinary expansion
        // below.
        return;
      }
    }
    if (static_field_cycle_complete) {
      // The chunk cursor completed a full lap over the loaded-class list with no chunk truncating
      // along the way (possibly discovering nothing, if every static field seen was already
      // ALREADY_ADMITTED) - remember the class count it covered so a later pass with no new classes
      // can skip re-running the sweep entirely.
      _last_static_field_class_count = _last_resolved_class_count;
    }
  }

  int expand_edges_admitted = 0;
  bool expand_truncated = false;
  bool expand_frontier_cap_hit = false;
  int remaining_budget = std::max(budget - expand_phase_edges_admitted, 0);
  // Give expand its own fresh deadline so the static-field sweep's FollowReferences calls don't eat
  // expand's time.
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
  TEST_LOG_SUMMARY("ReferenceChainTracker::runPassManualWalk expand_phase "
           "edges_admitted=%d truncated=%d frontier_cap_hit=%d "
           "remaining_budget=%d",
           expand_edges_admitted, (int)expand_truncated,
           (int)expand_frontier_cap_hit, remaining_budget);

  // Note: unlike a hard truncation during root/stack-ref enumeration or the static-field sweep
  // above (which return early - the pass never even reached ordinary expansion), a truncated
  // ordinary expansion does NOT skip rotation below: rotation runs on its own reserved slice of
  // budget (see rotation_reserved_budget's own comment above) precisely because ordinary expansion
  // truncates on nearly every pass under a sustained fast-growing backlog, and that is exactly the
  // situation - a mutable field reassigned out from under an already-EXPANDED entry - rotation
  // exists to correct.

  // Revisit a bounded subset of expanded entries to observe changed references.
  std::vector<jlong> rotation_tags =
      collectStaleRootKindEntriesForRotation(ROOT_KIND_ROTATION_BUDGET);
  std::vector<jlong> leak_accumulation_tags =
      collectLeakAccumulationCandidatesForRotation(
          LEAK_ACCUMULATION_ROTATION_BUDGET);
  // Also re-walk a bounded, rotating subset of EXPANDED entries regardless of root attribution: a
  // mutable field reassigned since an object's one-time expansion - e.g. HashMap.table on resize -
  // is otherwise never observed again, silently orphaning everything only reachable through the
  // field's current value.
  std::vector<jlong> stale_expanded_tags =
      collectStaleExpandedEntriesForRotation(STALE_EXPANDED_ROTATION_BUDGET);
  // Candidate-scoped reach, prong 2: root-attached static holders are descend-walked directly (see
  // collectStaticFieldAnchorsForRotation()/ walkStaticFieldAnchors()'s own comments) - not pushed
  // onto the priority lane, so they are independent of the queue tiers above.
  reconcileAnchorClassShapes(jvmti, jni);
  std::vector<jlong> static_anchor_tags =
      collectStaticFieldAnchorsForRotation(STATIC_ANCHOR_ROTATION_BUDGET);
  std::vector<AtRiskAnchor> static_anchor_fifo_drained;
  drainStaticAnchorFifo(STATIC_ANCHOR_FIFO_DRAIN, static_anchor_fifo_drained);
  for (const AtRiskAnchor &at_risk : static_anchor_fifo_drained) {
    static_anchor_tags.push_back(at_risk.tag);
  }
  if (rotation_tags.empty() && leak_accumulation_tags.empty() &&
      stale_expanded_tags.empty() && static_anchor_tags.empty()) {
    return;
  }
  // rotation_reserved_budget + max(budget - expand_phase_edges_admitted, 0) is exactly
  // expand_budget - expand_phase_edges_admitted: budget already IS expand_budget -
  // rotation_reserved_budget (above), and expand_phase_edges_ admitted can never exceed budget (the
  // static-field sweep and ordinary expandFrontier() calls above are both capped to budget-derived
  // slices), so the max() is never actually needed to avoid going negative.
  int rotation_budget = expand_budget - expand_phase_edges_admitted;
  int rotation_edges_admitted = 0;
  bool rotation_truncated = false;
  // Give rotation its own fresh deadline, same as expand above.
  _pass_deadline_ns = _effective_pause_target_ms > 0
                          ? OS::nanotime() + (u64)_effective_pause_target_ms * 1000000ULL
                          : 0;
  bool rotation_frontier_cap_hit = false;
  // Prong 2 static-anchor descend walks run FIRST inside rotation's slice: they are the
  // highest-value rotation work (bounded, targeted, and the only rotation tier that can reach a
  // collection-shaped static holder's internals in one pass), and their edges draw down the same
  // rotation budget the queue-tier batch below uses - a pass whose anchor walks admit the holder's
  // whole internal structure needs less one-hop rotation work, not more.
  if (!static_anchor_tags.empty() && rotation_budget > 0) {
    int static_anchor_edges_admitted = 0;
    bool static_anchor_truncated = false;
    bool static_anchor_frontier_cap_hit = false;
    std::vector<jlong> static_anchor_unwalked;
    walkStaticFieldAnchors(jvmti, jni, static_anchor_tags, rotation_budget,
                           &static_anchor_edges_admitted,
                           &static_anchor_truncated,
                           &static_anchor_frontier_cap_hit, safepoint_ticks,
                           &static_anchor_unwalked);
    rotation_edges_admitted += static_anchor_edges_admitted;
    rotation_budget -= static_anchor_edges_admitted;
    *truncated = *truncated || static_anchor_truncated;
    // B' requeue: resolved-but-unwalked anchors that came from this pass's FIFO drain go back to
    // the FIFO front, order-preserving, so a pass whose budget died mid-batch walks them first next
    // pass instead of waiting for the next sweep lap's re-push.
    if (!static_anchor_unwalked.empty() &&
        !static_anchor_fifo_drained.empty()) {
      std::vector<AtRiskAnchor> static_anchor_requeue;
      for (jlong tag : static_anchor_unwalked) {
        FrontierEntry entry{};
        if (!_frontier->lookup(tag, &entry)) {
          continue;
        }
        for (const AtRiskAnchor &at_risk : static_anchor_fifo_drained) {
          if (tag == at_risk.tag) {
            static_anchor_requeue.push_back(at_risk);
            break;
          }
        }
      }
      if (!static_anchor_requeue.empty()) {
        requeueStaticAnchorFifoFront(static_anchor_requeue);
      }
    }
    if (static_anchor_frontier_cap_hit) {
      *frontier_cap_hit = true;
      return;
    }
  }
  // expandFrontier() SETS (does not add into) its edges output - see its entry - so the anchor
  // walks' edges are kept in a separate counter and summed here.
  int queue_tier_edges_admitted = 0;
  expandFrontier(jvmti, jni, _hop_cap, rotation_budget,
                 &queue_tier_edges_admitted, &rotation_truncated,
                 &rotation_frontier_cap_hit, safepoint_ticks);
  rotation_edges_admitted += queue_tier_edges_admitted;
  *edges_admitted += rotation_edges_admitted;
  // OR, not overwrite: the ordinary expand phase above may have already set these to true (real
  // truncation/cap-hit left in _pending_expand), and a rotation batch that happens to finish
  // cleanly must not erase that - has_pending_frontier (runPass()) and the FRONTIER_CAP abandon
  // check both read these as "did any of this pass's sub-phases truncate/cap-hit", not just the
  // last one that ran.
  *truncated = *truncated || rotation_truncated;
  *frontier_cap_hit = *frontier_cap_hit || rotation_frontier_cap_hit;
}

// Incremental resumption across passes.

void ReferenceChainTracker::markAllFrontierExpanded() {
  while (!_priority_expand.empty()) {
    _frontier->markExpanded(_priority_expand.front());
    _priority_expand.pop_front();
  }
  _priority_expand_set.clear();
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

  ReferenceChainPassContext ctx;
  ctx.tracker = this;
  ctx.frontier = _frontier;
  ctx.hop_cap = hop_cap;
  ctx.budget = budget;
  ctx.edges_admitted = 0;
  ctx.truncated = false;
  ctx.frontier_cap_hit = false;

  // ARRAY-HOLDER BATCHING: expand a whole batch of boundary objects with ONE
  // FollowReferences(initial_object=holder_array) call per BFS level, instead of one
  // FollowReferences PER frontier entry.
  std::unordered_set<jlong> batch_tags;
  ctx.batch_tags = &batch_tags;
  // Completed-batch-entry tracking for the order-independent truncated-batch resume (see
  // ReferenceChainPassContext::_completed_batch_tags) - reset per batch along with the rolling
  // cursor.
  std::unordered_set<jlong> completed_batch_tags;
  ctx._completed_batch_tags = &completed_batch_tags;

  jvmtiHeapCallbacks callbacks;
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.heap_reference_callback = heapReferenceCallback;

  // java/lang/Object element type for the transient frontier-holder array.
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
  // FAIR-SHARE DRAIN: alternate batches between _priority_expand and _pending_expand whenever both
  // are non-empty (priority still takes the first batch of each call).
  while (!ctx.truncated && progress && object_class != nullptr) {
    // Wall-clock deadline check per iteration: GetObjectsWithTags runs OUTSIDE any FollowReferences
    // callback, so heapReferenceCallback()'s amortized deadline check never sees its cost.
    if (_pass_deadline_ns != 0 && OS::nanotime() >= _pass_deadline_ns) {
      ctx.truncated = true;
      break;
    }
    progress = false;

    // Alternate lanes (see FAIR-SHARE DRAIN above); priority still goes first so a
    // rotation-selected parent's re-discovery keeps its head-of-queue property, but no lane can
    // monopolize the drain.
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
    size_t gotw_batch_size =
        _gotw_batch_size != 0 ? _gotw_batch_size : GOTW_INITIAL_BATCH_SIZE;
    size_t batch_size = std::min(
        source.size(),
        std::min((size_t)std::max(std::min(budget, _budget), 1),
                 gotw_batch_size));
    std::vector<jlong> candidate_tags(source.begin(),
                                       source.begin() + batch_size);

    // Resolve this batch's live boundary objects. GetObjectsWithTags iterates the whole tag map,
    // but does so under a no-safepoint mutex on this (Java) thread - it is NOT a stop-the-world VM
    // operation, unlike the FollowReferences below (jvmtiTagMap.cpp: get_objects_with_tags takes
    // Mutex::_no_safepoint_check_flag and calls entry_iterate directly, whereas follow_references
    // does VMThread::execute()).
    jint resolved_count = 0;
    jobject *resolved_objects = nullptr;
    jlong *resolved_tags = nullptr;
    u64 gotw_start_ns = OS::nanotime();
    jvmtiError resolve_err = jvmti->GetObjectsWithTags(
        (jint)candidate_tags.size(), candidate_tags.data(), &resolved_count,
        &resolved_objects, &resolved_tags);
    u64 gotw_elapsed_ns = OS::nanotime() - gotw_start_ns;
    // Self-calibrate (PROPORTIONAL batch control): update the EMA of PER-CALL elapsed time, then
    // scale the batch so ONE call fills the remaining wall-clock window.
    if (batch_size > 0 && gotw_elapsed_ns > 0) {
      if (_gotw_ema_call_ns == 0) {
        _gotw_ema_call_ns = gotw_elapsed_ns;
      } else {
        _gotw_ema_call_ns = _gotw_ema_call_ns * 4 / 5 + gotw_elapsed_ns / 5;
      }
      u64 now_ns = OS::nanotime();
      u64 window_ns =
          gotwWindowNs(
              _pass_deadline_ns != 0 && _pass_deadline_ns > now_ns
                  ? _pass_deadline_ns - now_ns
                  : 0,
              source.size());
      // window_ns / ema_call_ns == how many such calls fit the window; scaling the CURRENT
      // calibration batch by that ratio sizes the next call to consume the whole window in one go.
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

    std::unordered_map<jlong, jobject> live;
    for (jint i = 0; i < resolved_count; i++) {
      live[resolved_tags[i]] = resolved_objects[i];
    }

    // Build the frontier-holder array from the live boundary objects and record their tags so
    // heapReferenceCallback() descends into exactly these (one hop).
    batch_tags.clear();
    jobjectArray holder = nullptr;
    if (resolved_count > 0) {
      jint capacity_err = jni->EnsureLocalCapacity(resolved_count + 16);
      if (capacity_err < 0 || jniExceptionCheck(jni)) {
        // Could not guarantee local-ref headroom for this batch - treat like any other batch-level
        // failure below (JVMTI error / OOM building the holder array): retry this batch on a later
        // pass rather than proceeding into NewObjectArray with no capacity guarantee.
        ctx.truncated = true;
      } else {
        holder = jni->NewObjectArray(resolved_count, object_class, nullptr);
        if (jniExceptionCheck(jni)) {
          // OutOfMemoryError building the holder array (or any other exception NewObjectArray
          // raised) left `holder` null; make sure the pending exception does not survive into the
          // next JNI call below or the next expandFrontier() invocation on this same long-lived
          // BFS-thread JNIEnv (JNI spec: undefined behavior with a pending exception across
          // ordinary JNI calls).
          holder = nullptr;
        }
        if (holder != nullptr) {
          for (jint i = 0; i < resolved_count; i++) {
            jni->SetObjectArrayElement(holder, i, resolved_objects[i]);
            if (jniExceptionCheck(jni)) {
              // e.g. an array-store-class failure. Abort building this batch's holder rather than
              // handing a partially-populated array (with a just-cleared pending exception) to
              // FollowReferences.
              ctx.truncated = true;
              break;
            }
            batch_tags.insert(resolved_tags[i]);
          }
        }
        if (holder == nullptr) {
          // NewObjectArray failed (OOM/local-ref exhaustion) - the FollowReferences call below
          // (which would have discovered this batch's children) never runs.
          ctx.truncated = true;
        } else if (!ctx.truncated) {
          // A single FollowReferences over the holder array expands this whole BFS level in one
          // stop-the-world HeapWalkOperation (instead of one per frontier entry).
          ctx._last_visited_batch_tag = 0; // reset rolling cursor
          completed_batch_tags.clear();
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
      // The whole batch had all its direct children admitted this level: dead entries are pruned,
      // live ones are marked EXPANDED, and all are popped off the front.
      for (jlong tag : candidate_tags) {
        if (live.find(tag) == live.end()) {
          _frontier->clear(tag);
        } else {
          _frontier->markExpanded(tag);
        }
        source.pop_front();
      }
      progress = true;
    } else if (!completed_batch_tags.empty()) {
      // ROLLING RESUME (order-independent): FollowReferences truncated mid-batch, but the callback
      // recorded exactly which batch entries it finished visiting (see
      // ReferenceChainPassContext::_completed_batch_tags).
      std::vector<jlong> keep;
      keep.reserve(candidate_tags.size());
      for (jlong tag : candidate_tags) {
        if (completed_batch_tags.count(tag) != 0) {
          if (live.find(tag) == live.end()) {
            _frontier->clear(tag);
          } else {
            _frontier->markExpanded(tag);
          }
        } else {
          keep.push_back(tag);
        }
        source.pop_front();
      }
      // Re-queue the unvisited remainder at the front, preserving input order (push_front in
      // reverse).
      for (size_t i = keep.size(); i-- > 0;) {
        source.push_front(keep[i]);
      }
    }
    // else truncated with no batch entry visited (e.g. GetObjectsWithTags error, holder allocation
    // failure, or truncation before the first batch entry was reached): leave the entire batch at
    // the front of the source queue for a later pass to retry, same as before.

    if (from_priority) {
      // This batch popped entries off _priority_expand's front (or, on truncation, was left
      // untouched) - re-derive the membership index from the deque's current contents either way so
      // isQueuedForRotation() stays exact for the rotation collectors that run later in this same
      // pass.
      _priority_expand_set.rebuildFrom(_priority_expand);
    }

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

  // object_class is NOT deleted here - it is now cached in _cached_object_class and reused across
  // calls on this same JNIEnv (see above), not a per-call local ref.

  if (!ctx.truncated && jni != nullptr && object_class == nullptr &&
      (!_pending_expand.empty() || !_priority_expand.empty())) {
    // FindClass("java/lang/Object") failed for this (attached) JNIEnv, so the batching loop above
    // never ran even though pending frontier work remains.
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
    // No JNIEnv to build the holder array on (some test seams) - see expandFrontier()'s own
    // identical guard.
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

  // GetLoadedClasses() gives no ordering guarantee across separate calls, so the cursor below is
  // only meaningful as an index into THIS call's array - reprioritize it every call rather than
  // trying to cache an ordering.
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

  // Stable chunk order: GetLoadedClasses() returns an arbitrary order per call, so an index cursor
  // over raw call order can MISS classes entirely within a lap (each chunk would cover a different
  // random subset).
  {
    std::vector<jlong> tags((size_t)class_count, 0);
    for (jint i = 0; i < class_count; i++) {
      jvmti->GetTag(classes[i], &tags[i]);
    }
    std::vector<jint> order((size_t)class_count);
    for (jint i = 0; i < class_count; i++) {
      order[i] = i;
    }
    std::sort(order.begin(), order.begin() + app_boundary,
              [&tags](jint a, jint b) { return tags[a] < tags[b]; });
    std::sort(order.begin() + app_boundary, order.end(),
              [&tags](jint a, jint b) { return tags[a] < tags[b]; });
    std::vector<jclass> sorted((size_t)class_count);
    for (jint i = 0; i < class_count; i++) {
      sorted[i] = classes[order[i]];
    }
    memcpy(classes, sorted.data(), (size_t)class_count * sizeof(jclass));
  }

  if (_static_field_sweep_cursor >= class_count) {
    // Loaded-class count shrank since the last chunk (classes unloaded) - restart the lap rather
    // than reading out of range.
    _static_field_sweep_cursor = 0;
    _static_field_sweep_cycle_truncated = false;
  }
  jint chunk_start = _static_field_sweep_cursor;
  jint chunk_end =
      std::min(chunk_start + STATIC_FIELD_SWEEP_CHUNK_CLASSES, class_count);
  jint chunk_count = chunk_end - chunk_start;

  // Same java/lang/Object element-type cache expandFrontier() uses for its own frontier-holder
  // array - shared across both call sites on this same attached JNIEnv rather than a second
  // FindClass() per pass.
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
    // OutOfMemoryError (or any other exception) building the holder - clear it rather than let it
    // survive into the DeleteLocalRef() calls below (JNI spec: undefined behavior with a pending
    // exception across ordinary JNI calls), same as expandFrontier()'s identical case.
    holder = nullptr;
  }
  if (holder != nullptr) {
    // Fill in REVERSE chunk order: holder[0] = classes[chunk_end-1], ..., holder[chunk_count-1] =
    // classes[chunk_start].
    for (jint i = 0; i < chunk_count; i++) {
      jni->SetObjectArrayElement(holder, i, classes[chunk_end - 1 - i]);
      if (jniExceptionCheck(jni)) {
        holder = nullptr;
        break;
      }
    }
  }

  // GetLoadedClasses() returned a local ref for every class regardless of chunk selection - free
  // all of them here, not just the chunk.
  for (jint i = 0; i < class_count; i++) {
    jni->DeleteLocalRef(classes[i]);
  }
  jvmti->Deallocate((unsigned char *)classes);

  if (holder == nullptr) {
    // OOM/local-ref exhaustion/array-store failure - skip this pass's sweep rather than treating it
    // like the manual walk's own truncation (see this method's own header comment).
    return;
  }

  ReferenceChainPassContext ctx;
  ctx.tracker = this;
  ctx.frontier = _frontier;
  ctx.hop_cap = hop_cap;
  ctx.budget = budget;
  ctx.edges_admitted = 0;
  ctx.truncated = false;
  ctx.frontier_cap_hit = false;
  // Empty (not null) batch_tags forces heapReferenceCallback() to stop at exactly one hop past each
  // class - see this method's own header comment for why a deeper descent here would reintroduce
  // the whole-graph FollowReferences cost the array-holder batching design otherwise avoids.
  std::unordered_set<jlong> empty_batch_tags;
  ctx.batch_tags = &empty_batch_tags;
  // Lets heapReferenceCallback() walk past the holder->class seed edge (see
  // ReferenceChainPassContext::static_field_seed's own comment) so this sweep actually reaches each
  // class's static fields instead of stopping at the negative-tagged class object itself.
  ctx.static_field_seed = true;
  // Per-class non-STATIC_FIELD admission cap (see ReferenceChainPassContext::_class_other_cap's own
  // comment).
  ctx._class_other_cap = STATIC_FIELD_SWEEP_NON_STATIC_CAP_PER_CLASS;

  jvmtiHeapCallbacks callbacks;
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.heap_reference_callback = heapReferenceCallback;
  u64 follow_start_ticks = TSC::ticks();
  jvmtiError follow_err =
      jvmti->FollowReferences(0, nullptr, holder, &callbacks, &ctx);
  *safepoint_ticks += TSC::ticks() - follow_start_ticks;
  jni->DeleteLocalRef(holder);
  if (follow_err != JVMTI_ERROR_NONE) {
    return;
  }

  *edges_admitted = ctx.edges_admitted;
  *truncated = ctx.truncated;
  *frontier_cap_hit = ctx.frontier_cap_hit;

  if (ctx.truncated) {
    _static_field_sweep_cycle_truncated = true;
    // Resumable cursor: instead of skipping to chunk_end (losing every class after the interruption
    // point for the rest of this lap), redo the chunk on the next pass.
    _static_field_sweep_cursor = chunk_start;
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
    // GetObjectsWithTags() itself failed (e.g. JVMTI_ERROR_OUT_OF_MEMORY): we do NOT know which, if
    // any, of live_tags are still live objects, so do not mark any of them ABANDONED here - doing
    // so while their JVMTI tag might still be set would let a restarted search's nextTag() sequence
    // eventually reissue the same numeric tag to a brand-new object, corrupting FrontierTable's
    // tag-uniqueness invariant (see this method's own header comment).
    Counters::increment(REFERENCE_CHAIN_TAG_RELEASE_FAILED);
    Log::warn("ReferenceChains: GetObjectsWithTags failed while releasing "
              "%zu search tag(s); will retry before allowing a search "
              "restart",
              live_tags.size());
    return false;
  }

  for (jint i = 0; i < resolved_count; i++) {
    // clearTag() rather than a raw SetTag() call - reuses the same helper (and its GC-callback
    // self-consistency assert) tagObject/ getTag already go through.
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
  // Tags that failed to resolve above are already dead (JVMTI forgot them with their object) -
  // nothing to release, just mark the record ABANDONED below like every other entry this search
  // owned.
  for (jlong tag : live_tags) {
    _frontier->clear(tag);
  }
  return true;
}

bool ReferenceChainTracker::runPass(jvmtiEnv *jvmti, JNIEnv *jni,
                                     bool *out_truncated) {
  if (!_enabled || jvmti == nullptr || _frontier == nullptr) {
    TEST_LOG_SUMMARY("ReferenceChainTracker::runPass early-exit: enabled=%d jvmti=%p frontier=%p",
             _enabled, (void *)jvmti, (void *)_frontier);
    return false;
  }

  if (_search_state != SearchState::RUNNING) {
    // The search already reached a terminal outcome - nothing left for another pass to do until
    // shouldRunPass() decides to restartSearch() (this class's header comment), which flips
    // _search_started back to false before this method is called again.
    if (!_tags_released) {
      _tags_released = releaseSearchTags(jvmti, jni);
    }
    TEST_LOG_SUMMARY("ReferenceChainTracker::runPass no-op: searchState=%d already terminal "
             "tagsReleased=%d",
             (int)_search_state, _tags_released);
    if (out_truncated != nullptr) {
      *out_truncated = false;
    }
    return true;
  }

  resolveLoadedClasses(jvmti, jni);

  TEST_LOG_SUMMARY("ReferenceChainTracker::runPass starting JVMTI walk: "
           "search_started=%d frontierSize=%zu",
           _search_started, _frontier != nullptr ? _frontier->size() : (size_t)0);

  int edges_admitted = 0;
  bool truncated = false;
  bool frontier_cap_hit = false;
  jvmtiError err;
  // Whole-call wall-clock duration of runPassManualWalk() below - includes root/stack-ref
  // enumeration dispatch, frontier-table bookkeeping, and rotation-candidate collection, in
  // addition to the actual in-safepoint JVMTI calls.
  u64 pass_wall_ticks = 0;
  // Genuine in-safepoint cost of this pass, accumulated by runPassManualWalk() across every
  // IterateOverReachableObjects/ FollowReferences call it makes (root enum, static-field sweep,
  // ordinary expansion, rotation re-expansion) - explicitly excluding GetObjectsWithTags (not a
  // safepoint call) and every bookkeeping line in between.
  u64 safepoint_ticks = 0;

  // Every pass is driven by the manual walk (runPassManualWalk() - IterateOverReachableObjects for
  // roots, then a batched array-holder FollowReferences per BFS level in expandFrontier()), on
  // every collector.
  bool manual_first_pass = !_search_started;
  if (manual_first_pass) {
    _search_started = true;
    store(_search_start_ns, OS::nanotime());
  }

  // Root/stack-ref enumeration alone never discovers a root's transitive children
  // (runPassManualWalk()'s own comment) - there is no "first pass walks the whole graph inline"
  // shortcut here, so every pass (first or resumed) takes the same expand-frontier shape.
  u64 now_ns = OS::nanotime();
  bool run_root_enum = manual_first_pass || _root_enum_truncated_last_time ||
                       (now_ns - _last_root_enum_ns >= ROOT_ENUM_MIN_INTERVAL_NS);

  int frontier_size_before_pass = _frontier != nullptr ? _frontier->size() : 0;

  u64 call_start_ticks = TSC::ticks();
  runPassManualWalk(jvmti, jni, run_root_enum, _first_pass_budget,
                     _effective_budget, &edges_admitted, &truncated,
                     &frontier_cap_hit, &safepoint_ticks);
  pass_wall_ticks = TSC::ticks() - call_start_ticks;
  // TSC::ticks() is monotonic but not necessarily free of measurement noise between the outer
  // call_start_ticks snapshot and the several inner TSC::ticks() snapshots safepoint_ticks is built
  // from - clamp rather than underflow if the accumulated safepoint portion ever reads back larger
  // than the whole-call wall time it's a subset of.
  u64 non_safepoint_ticks =
      pass_wall_ticks > safepoint_ticks ? pass_wall_ticks - safepoint_ticks : 0;
  err = JVMTI_ERROR_NONE;

  store(_passes_run, load(_passes_run) + 1);
  _last_pass_gc_finish_epoch = gcFinishEpoch();
  store(_last_pass_ns, OS::nanotime());
  if (!run_root_enum) {
    // A pass that ran root/stack-ref enumeration spends _first_pass_budget, not _effective_budget -
    // its duration is not a signal about the per-pass cost updatePacing() is trying to regulate
    // (expandFrontier()'s cheap, per-node expansion calls), so feeding it in here would throttle
    // _effective_budget down for every one of those unrelated later passes based on a single,
    // deliberately oversized outlier.
    updatePacing(safepoint_ticks);
  } else {
    // Excluded from the budget/cadence controller above, but not from the borrow ceiling's
    // revocation check (see maybeRevokeBorrowForRootEnumPass()'s own comment) - a root-enum pass's
    // in-safepoint cost is real pause time and must still be able to revoke a borrowed-budget grant
    // the pacing controller would otherwise keep believing is safe.
    maybeRevokeBorrowForRootEnumPass(safepoint_ticks);
  }
  // accumulate this pass's own in-safepoint cost toward the running total restartSearch() will
  // spend into _safepoint_pain_budget once the search reaches a terminal state - same
  // TSC::ticks_to_millis() conversion updatePacing() already uses for its own pass-duration signal.
  _search_pain_ms += TSC::ticks_to_millis(safepoint_ticks);
  // Independent leaky bucket for the non-safepoint remainder of this pass (root/stack-ref
  // enumeration dispatch, frontier-table admission, rotation-candidate collection) - see
  // _cpu_pain_budget's own comment (referenceChains.h) for why this needs to be tracked separately
  // from both _safepoint_pain_budget above and _pause_pid's safepoint_ticks signal.
  _cpu_pain_budget.spend(TSC::ticks_to_millis(non_safepoint_ticks));

  // Apply terminal conditions in priority order.
  bool has_pending_frontier = truncated;
  int frontier_size_after = _frontier->size();
  if (frontier_cap_hit) {
    // Frontier table is full -- no new entries can ever be admitted, so frontier_size_after can
    // never exceed frontier_size_before_pass again.
    store(_abandon_reason, (u8)SearchAbandonReason::FRONTIER_CAP);
    storeRelease(_search_state, (u8)SearchState::ABANDONED);
    enqueuePendingAbandonedEvent();
    TEST_LOG_SUMMARY("ReferenceChainTracker::runPass frontier cap hit -- "
             "abandoning search (size=%d)",
             frontier_size_after);
  } else if (!has_pending_frontier && _watched_leak_klass_count == 0) {
    storeRelease(_search_state, (u8)SearchState::COMPLETED);
  } else if (_ttl_ms > 0 &&
             TSC::ticks_to_millis(OS::nanotime() - load(_search_start_ns)) >=
                 (u64)_ttl_ms) {
    // TTL bounds stop-the-world work independently of frontier progress.
    store(_abandon_reason, (u8)SearchAbandonReason::TTL);
    storeRelease(_search_state, (u8)SearchState::ABANDONED);
    enqueuePendingAbandonedEvent();
    TEST_LOG_SUMMARY("ReferenceChainTracker::runPass ttl expired -- abandoning search "
             "(ttl=%ldms elapsed_ms=%llu)",
             _ttl_ms,
             (unsigned long long)TSC::ticks_to_millis(OS::nanotime() -
                                                      load(_search_start_ns)));
  } else if (_passes_since_last_progress >= NO_PROGRESS_PASS_LIMIT &&
             !isUrgent()) {
    // The frontier hasn't grown for NO_PROGRESS_PASS_LIMIT consecutive passes — the search is
    // genuinely stuck (not just slow), so abandon.
    store(_abandon_reason, (u8)SearchAbandonReason::TTL);
    storeRelease(_search_state, (u8)SearchState::ABANDONED);
    enqueuePendingAbandonedEvent();
  } else if (_candidate_count > 0 &&
             __builtin_popcountll(_candidate_found_bits) ==
                 (u64)_candidate_count) {
    // Canary early termination: all leaked candidates have been found -- the search is complete.
    storeRelease(_search_state, (u8)SearchState::COMPLETED);
    Counters::increment(REFERENCE_CHAIN_CANDIDATES_FOUND,
                             __builtin_popcountll(_candidate_found_bits));
  } else if (_candidate_count > 0 &&
             _passes_since_last_progress >= NO_PROGRESS_PASS_LIMIT &&
             _passes_since_last_candidate_progress >=
                 canaryStuckPassLimit()) {
    // Canary-specific stuck detector - deliberately NOT suppressed by isUrgent() (contrast the
    // ordinary TTL check above).
    store(_abandon_reason, (u8)SearchAbandonReason::CANARY_STUCK);
    storeRelease(_search_state, (u8)SearchState::ABANDONED);
    enqueuePendingAbandonedEvent();
    if (_canary_stuck_restart_count < MAX_CANARY_STUCK_BACKOFF_SHIFT) {
      _canary_stuck_restart_count++;
    }
  }

  // Track progress: if the frontier grew this pass, reset the no-progress counter.
  if (frontier_size_after > frontier_size_before_pass) {
    _passes_since_last_progress = 0;
  } else {
    _passes_since_last_progress++;
  }

  // Track canary-specific progress separately - see _passes_since_last_candidate_progress's own
  // comment for why frontier growth above does not substitute for this.
  {
    u64 pass_wall_ms = (u64)TSC::ticks_to_millis(pass_wall_ticks);
    _canary_pass_ema_ms = _canary_pass_ema_ms == 0
        ? pass_wall_ms
        : _canary_pass_ema_ms * 4 / 5 + pass_wall_ms / 5;
  }
  int candidate_progress_mark =
      _candidate_count + (int)__builtin_popcountll(_candidate_found_bits);
  if (candidate_progress_mark > _last_candidate_progress_mark) {
    _last_candidate_progress_mark = candidate_progress_mark;
    _passes_since_last_candidate_progress = 0;
    // Real chase progress (a candidate found or a new one admitted) - the canary lane gets its
    // back-to-back spacing back (multiplier 1, see _canary_backoff_mult's own comment).
    _canary_backoff_mult = 1;
  } else {
    _passes_since_last_candidate_progress++;
    // No chase progress: double the canary lane's work-scaled spacing multiplier, capped.
    if (_candidate_count > 0 &&
        __builtin_popcountll(_candidate_found_bits) < (u64)_candidate_count) {
      _canary_backoff_mult =
          std::min(_canary_backoff_mult * 2, CANARY_BACKOFF_MULT_MAX);
      _last_canary_pass_ns = OS::nanotime();
    }
  }

  if (load(_search_state) != SearchState::RUNNING) {
    _tags_released = releaseSearchTags(jvmti, jni);
    // Release canary marker tags: use GetObjectsWithTags to find all live marker-tagged objects and
    // clear them.
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
      memset(_candidate_qualifying_tid_count, 0,
             sizeof(_candidate_qualifying_tid_count));
      _passes_since_last_candidate_progress = 0;
    }
    // Only CANARY_STUCK should keep escalating canaryStuckPassLimit() - any other terminal reason
    // (natural completion, all candidates found, frontier cap, TTL) is an unrelated outcome for
    // this chase sequence, so a fresh restart afterward should start back at the base limit.
    if (load(_abandon_reason) != SearchAbandonReason::CANARY_STUCK) {
      _canary_stuck_restart_count = 0;
    }
  }

  if (out_truncated != nullptr) {
    *out_truncated = truncated;
  }

  TEST_LOG_SUMMARY("ReferenceChainTracker::runPass done: err=%d edges_admitted=%d truncated=%d "
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

// Pause-time-SLO feedback loop (see this method's declaration in

void ReferenceChainTracker::updatePacing(u64 pass_wall_ticks) {
  // Truncating to whole milliseconds matches every other PidController usage in this codebase
  // (ObjectSampler/MallocTracer/NativeSocketSampler all feed it integer counts, pidController.h's
  // `compute(u64 input, ...)`) - sub-ms precision is not meaningful against a millisecond-scale
  // target anyway.
  u64 pass_ms = TSC::ticks_to_millis(pass_wall_ticks);
  // time_delta_coefficient is deliberately 1.0, not a real-elapsed-time ratio - unlike
  // ObjectSampler's usage (objectSampler.cpp), which rescales an event count accumulated over a
  // variable-length real-time window against a fixed-real-time target, _pause_pid was constructed
  // with sampling_window=1 (its own constructor comment above, in start()): one compute() call *is*
  // one pass, and pass_ms already IS the per-call quantity being compared against the per-call
  // ceiling _target encodes.
  double signal = _pause_pid.compute(pass_ms, 1.0);

  // Budget-borrowing (referenceChains.h's _borrowed_budget comment): only a sustained run of
  // comfortably-under-target passes earns extra headroom above _budget, and any pass that is not
  // comfortably under target revokes it immediately - _budget itself must stay the ceiling the
  // instant this search stops proving it has pause-time room to spare.
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
  // Whatever part of `desired` the clamp above could not absorb - positive when there was more
  // headroom than the ceiling allows, negative when the pass is still over the pause-time target
  // even at the floor.
  int64_t overflow = desired - clamped;
  _effective_budget = (int)clamped;

  if (overflow < 0) {
    // Still over the pause-time ceiling even at the minimum budget - widen the fallback interval
    // instead of shrinking the budget further.
    u64 step = (u64)(-overflow) * CADENCE_NS_PER_EDGE_OVERFLOW;
    _effective_cadence_ns =
        std::min(_effective_cadence_ns + step, MAX_EFFECTIVE_CADENCE_NS);
  } else if (overflow > 0) {
    // Comfortably under the ceiling even at the maximum (config) budget - relax the fallback
    // interval.
    u64 step = (u64)overflow * CADENCE_NS_PER_EDGE_OVERFLOW;
    _effective_cadence_ns =
        step >= _effective_cadence_ns
            ? MIN_EFFECTIVE_CADENCE_NS
            : std::max(_effective_cadence_ns - step, MIN_EFFECTIVE_CADENCE_NS);
  }
  // overflow == 0: the budget clamp alone fully absorbed this pass's correction - leave the cadence
  // at its current value.
}

// A root/stack-ref enumeration pass never reaches updatePacing() above (see runPass()'s own comment
// on why its wall-clock cost is excluded from the per-pass PID/effective-budget signal), but it
// still spends real pause-time-SLO time.
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
    // The ceiling updatePacing() would compute right now collapses to _budget alone (no
    // _borrowed_budget term above) - re-clamp _effective_budget immediately instead of leaving the
    // borrow-inflated value in place until the next ordinary pass's updatePacing() call.
    _effective_budget = std::min(_effective_budget, (int)_budget);
  }
}

