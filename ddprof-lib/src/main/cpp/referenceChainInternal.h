/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef _REFERENCECHAININTERNAL_H
#define _REFERENCECHAININTERNAL_H

#include "arch.h"
#include <jni.h>
#include <unordered_set>

class FrontierTable;
class ReferenceChainTracker;

extern thread_local bool t_inGCCallback;

struct ReferenceChainPassContext {
  ReferenceChainTracker *tracker;
  FrontierTable *frontier;
  int hop_cap;
  int budget;
  int edges_admitted;
  bool truncated;

  // Set only when `truncated` became true because frontier->insert() itself reported capacity
  // exhaustion, as opposed to edges_admitted reaching budget.
  bool frontier_cap_hit;

  // ARRAY-HOLDER BATCHING: when non-null, expandFrontier() is driving a one-hop expansion of a
  // batch of boundary objects passed to a single FollowReferences(initial_object=holder_array)
  // call.
  std::unordered_set<jlong> *batch_tags = nullptr;

  // Rolling resume cursor for expandFrontier(): tracks the tag of the last batch entry that
  // FollowReferences visited (the callback at the batch_tags descent-gate updates this).
  jlong _last_visited_batch_tag = 0;

  // Batch entries the callback finished visiting before the truncation (set only by
  // heapReferenceCallback()'s batch_tags descent gate).
  std::unordered_set<jlong> *_completed_batch_tags = nullptr;

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
