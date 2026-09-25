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

// Target-selection bridging step - LivenessTracker's leak-candidate ranking feeds

void ReferenceChainTracker::requeueChainRootForRotation(jlong tag) {
  if (_frontier == nullptr || tag <= 0) {
    return;
  }
  // Walk the parent chain up to the root-attached entry - the same links reconstructChain() walks,
  // but we only need the tag, not the class ids.
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
  _priority_expand_set.insert(root_tag);
}

namespace {

// The discovered-chain gate's suppression predicate, shared by EVERY site that caches a resolved
// chain - the poll's discovered-instances loop AND both representative build paths (the
// canary/marker path and the normal-tag path).
bool suppressChainEvent(const ReferenceChainEvent &event) {
  return event._depth < 2 && isTransientRootKind(event._root_kind);
}

}  // namespace

// Chain-event reconstruction for a discovered/correlated instance (out of line from
// referenceChains.h so these sites share the TU's level-gated TEST_LOG; per-instance outcomes are
// level-2 diagnostics).
bool ReferenceChainTracker::buildChainEvent(jvmtiEnv *jvmti, JNIEnv *jni,
                                            jlong target_tag,
                                            ReferenceChainEvent *out) {
  if (_frontier == nullptr || out == nullptr) {
    TEST_LOG("ReferenceChainTracker::buildChainEvent false: "
             "frontier=%p out=%p", (void *)_frontier, (void *)out);
    return false;
  }
  FrontierEntry entry{};
  if (!_frontier->lookup(target_tag, &entry)) {
    TEST_LOG("ReferenceChainTracker::buildChainEvent false: "
             "target_tag=%lld not in frontier", (long long)target_tag);
    return false;
  }
  std::vector<u32> chain;
  std::vector<ChainHopEdge> edges;
  u8 root_kind = 0;
  FrontierEntry terminal{};
  if (!_frontier->reconstructChain(target_tag, &chain, &root_kind, &edges,
                                   &terminal)) {
    TEST_LOG("ReferenceChainTracker::buildChainEvent false: "
             "reconstructChain failed for target_tag=%lld",
             (long long)target_tag);
    return false;
  }
  appendStaticFieldRootType(terminal, &chain, &edges);
  TEST_LOG("ReferenceChainTracker::buildChainEvent target_tag=%lld chain_size=%zu "
           "chain[0]=%u depth=%u root_kind=%u leak_tag=%lld",
           (long long)target_tag, chain.size(), chain.empty() ? 0u : chain[0],
           entry.depth, (unsigned)root_kind, (long long)entry.leak_tag);
  out->_target_tag = entry.leak_tag != 0 ? (u64)entry.leak_tag : (u64)target_tag;
  out->_depth = entry.depth;
  out->_root_kind = root_kind;
  out->_hops.resize(chain.size());
  for (size_t i = 0; i < chain.size(); i++) {
    out->_hops[i].klass_id = chain[i];
  }
  // Retention-edge labels, aligned with the hops (see fillHopEdgeLabels()).
  fillHopEdgeLabels(jvmti, jni, edges, &out->_hops);
  return true;
}

// Appends the root TYPE as a chain element for a static-field-rooted chain: the frontier path's
// root-side end is the static field's HOLDER instance (the object stored in the field), but the
// chain's root is the DECLARING CLASS - the holder is "the field instance referenced by the root
// type", one hop below it.
void ReferenceChainTracker::appendStaticFieldRootType(
    const FrontierEntry &terminal, std::vector<u32> *chain,
    std::vector<ChainHopEdge> *edges) {
  if (chain == nullptr ||
      terminal.root_kind != (u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD ||
      terminal.referrer_class_tag == 0) {
    return;
  }
  u32 root_klass = classTags()->resolve(terminal.referrer_class_tag);
  if (root_klass == 0) {
    return;
  }
  chain->push_back(root_klass);
  if (edges != nullptr) {
    ChainHopEdge root_edge{};
    root_edge.field_index = -1;
    root_edge.edge_kind = terminal.root_kind;
    root_edge.referrer_class_tag = 0;
    edges->push_back(root_edge);
  }
}

// Canary chain reconstruction (out of line for the same reason).
bool ReferenceChainTracker::buildCanaryChainEvent(int candidate_idx,
                                                  ReferenceChainEvent *out) {
  if (_frontier == nullptr || out == nullptr || candidate_idx < 0 ||
      candidate_idx >= _candidate_count) {
    TEST_LOG_SUMMARY("ReferenceChainTracker::buildCanaryChainEvent false: "
                     "frontier=%p out=%p idx=%d count=%d",
                     (void *)_frontier, (void *)out, candidate_idx,
                     _candidate_count);
    return false;
  }
  jlong parent_tag = _candidate_parent_tags[candidate_idx];
  u32 candidate_klass = _candidate_referrer_klasses[candidate_idx];
  jlong frontier_tag = _candidate_frontier_tags[candidate_idx];
  std::vector<u32> chain;
  u8 root_kind = 0;
  // The root-attached entry the walk ends at - both branches below leave `entry` holding it (the
  // walk's last lookup, or the candidate's own entry for a root-referenced candidate).
  FrontierEntry terminal{};
  if (parent_tag > 0) {
    // Walk parent_tag back to root through the frontier table.
    FrontierEntry entry{};
    if (!_frontier->lookup(parent_tag, &entry)) {
      TEST_LOG_SUMMARY("ReferenceChainTracker::buildCanaryChainEvent false: "
                       "parent_tag=%lld not in frontier (candidate=%d)",
                       (long long)parent_tag, candidate_idx);
      return false;
    }
    // Bounded like every sibling walk over this same parent chain:
    // FrontierTable::reconstructChain() bounds at maxCapacity() hops and
    // returns false on a "cyclic or corrupt parent chain",
    // requeueChainRootForRotation() bounds at _hop_cap, and improveChain()'s
    // cycle guard bounds at 4096. improveChain() structurally prevents cycles
    // (it refuses a parent whose chain routes through the entry), but the
    // table's contents are also written by insert() with no such validation,
    // so a corrupt chain must fail safe instead of spinning this poll-thread
    // walk forever: every tag maps to a distinct slot (tags are never
    // reused), so a well-formed chain can visit at most maxCapacity() entries
    // before reaching parent_tag == 0 or repeating a slot.
    const int hop_bound = _frontier->maxCapacity();
    int hops = 0;
    for (jlong tag = parent_tag; tag > 0; hops++) {
      if (hops > hop_bound) {
        TEST_LOG_SUMMARY("ReferenceChainTracker::buildCanaryChainEvent false: "
                         "chain walk exceeded hop bound (%d) - cyclic or "
                         "corrupt parent chain (candidate=%d)",
                         hops, candidate_idx);
        return false;
      }
      if (!_frontier->lookup(tag, &entry)) {
        TEST_LOG_SUMMARY("ReferenceChainTracker::buildCanaryChainEvent false: "
                         "chain walk: tag=%lld not in frontier (candidate=%d)",
                         (long long)tag, candidate_idx);
        return false;
      }
      chain.push_back(entry.referrer_klass);
      tag = entry.parent_tag;
    }
    // The root kind describes the chain's ROOT, not the candidate-side parent:
    // the walk's last iteration is always the root-attached entry (parent_tag
    // == 0, root_kind != 0), so `entry` holds it here - same terminal-root
    // semantics reconstructChain() uses for *out_root_kind. The parent-side
    // entry read before the loop would almost always yield 0 (interior entries
    // carry root_kind == 0), misreporting every walk-reconstructed chain and
    // defeating suppressChainEvent()'s transient-root gate.
    root_kind = entry.root_kind;
    terminal = entry;
  } else if (parent_tag == 0 && frontier_tag > 0) {
    // Root-referenced candidate: chain is just [candidate_klass].
    FrontierEntry entry{};
    if (!_frontier->lookup(frontier_tag, &entry)) {
      TEST_LOG_SUMMARY("ReferenceChainTracker::buildCanaryChainEvent false: "
                       "frontier_tag=%lld not in frontier (candidate=%d)",
                       (long long)frontier_tag, candidate_idx);
      return false;
    }
    root_kind = entry.root_kind;
    terminal = entry;
  } else {
    TEST_LOG_SUMMARY("ReferenceChainTracker::buildCanaryChainEvent false: "
                     "never pruned (candidate=%d parent_tag=%lld frontier_tag=%lld)",
                     candidate_idx, (long long)parent_tag,
                     (long long)frontier_tag);
    return false; // never pruned (candidate not reached)
  }
  // Prepend the candidate's own referrer_klass.
  chain.push_back(candidate_klass);
  // The chain was built root-to-parent; reverse to get candidate-to-root.
  std::reverse(chain.begin(), chain.end());
  // Same root-type element buildChainEvent() appends: the canary walk's terminal entry is the
  // root-attached entry, and for a static-field root the declaring class belongs at the chain's
  // root-side end (after the reverse).
  appendStaticFieldRootType(terminal, &chain, nullptr);
  out->_target_tag = (u64)frontier_tag;
  out->_depth = _candidate_depths[candidate_idx];
  out->_root_kind = root_kind;
  const size_t chain_size = chain.size();
  out->_hops.resize(chain_size);
  for (size_t i = 0; i < chain.size(); i++) {
    out->_hops[i].klass_id = chain[i];
  }
  TEST_LOG_SUMMARY("ReferenceChainTracker::buildCanaryChainEvent candidate=%d "
                   "parent_tag=%lld chain_size=%zu",
                   candidate_idx, (long long)parent_tag, chain_size);
  return true;
}

void ReferenceChainTracker::pollWatchedTargets(jvmtiEnv *jvmti, JNIEnv *jni) {
  if (!_enabled || jvmti == nullptr || jni == nullptr ||
      !LivenessTracker::instance()->gcGenerationsEnabled()) {
    // Avoid candidate-table work when generation tracking is disabled.
    return;
  }

  // Stamp every entry this poll refreshes with the current search generation.
  const u64 current_search_ns = load(_search_start_ns);

  // klass_ids resolved (and therefore already pruned-if-dead) by the candidate loop below, so the
  // prune pass afterwards skips re-resolving them - it only needs to cover cached klasses that are
  // no longer flagged.

  // selectLeakCandidates() clamps this to its private candidate limit.
  constexpr int kMaxWatchedCandidates = 8;
  KlassCandidate candidates[kMaxWatchedCandidates];
  int candidate_count = LivenessTracker::instance()->selectLeakCandidates(
      candidates, kMaxWatchedCandidates);

  // Publish this poll's qualifying tids as LivenessTracker's watched-admission set (see
  // noteSelectedCandidates()'s own comment, livenessTracker.h): exactly the (klass, tid) scope
  // tagLeakInstances() tags and this chase intercepts gets its allocations admitted at 100% instead
  // of the default 10% ratio lottery.
  LivenessTracker::instance()->noteSelectedCandidates(candidates,
                                                       candidate_count);

  // Refresh the faster, un-hysteresis-gated klass_id ranking rotation priority uses (see
  // _watched_leak_klass_ids' own comment) - but only once selectLeakCandidates() above has ALREADY
  // found at least one qualifying candidate via its own slower hysteresis gate: this mechanism is
  // meant to crank once the trend detector has triggered, not to run the ranking independently
  // before that gate has ever fired.
  if (candidate_count > 0) {
    // Snapshot the OLD watched set before overwriting it, so any klass_id that's newly appearing
    // this refresh can get its one-time retroactive catch-up
    // (seedLeakAccumulationForNewlyWatchedKlass() - see _watched_leak_klass_ids' own comment for
    // why admission-time tracking alone cannot see objects admitted before watching started).
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
  // Only log when there are candidates to act on - this poll runs on every BFS-thread wake (once
  // per second), so logging a zero count is per-second noise for the common idle case.
  if (candidate_count > 0) {
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate_count=%d", candidate_count);
    // Admit any candidate selectLeakCandidates() returns this poll that doesn't already occupy a
    // slot, into the next free slot.
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
        TEST_LOG_SUMMARY("ReferenceChainTracker::pollWatchedTargets canary: klass_id=%u "
                 "qualifies but all %d slots are occupied - not tracked this search",
                 klass_id, MAX_LEAK_CANDIDATES_FROM_LT);
        continue;
      }
      // Candidate admission: the marker->leak-tag migration retired
      // pre-tagging the representative object (the retired marker-tag decode
      // branches are gone); this candidate is discovered when the walk or the
      // poll intercepts one of its leak-tagged instances.
      int slot = _candidate_count;
      _candidate_klass_ids[slot] = klass_id;
      _candidate_count = slot + 1;
      TEST_LOG_SUMMARY("ReferenceChainTracker::pollWatchedTargets canary: admitted klass_id=%u "
               "into slot=%d (candidate_count now %d)",
               klass_id, slot, _candidate_count);
      Counters::increment(REFERENCE_CHAIN_CANDIDATE_COUNT, 1);
    }
    // Refresh the per-slot qualifying-tid snapshot the walk phases read
    // (walkCandidateThreadLocals()): zero every slot first, then fill from THIS poll's candidates -
    // a klass whose per-tid trend stopped qualifying must stop having its tids walked, exactly like
    // it stops consuming pool tags (tagLeakInstances() below keeps the same per-poll-candidates
    // scope for the same reason).
    memset(_candidate_qualifying_tid_count, 0,
           sizeof(_candidate_qualifying_tid_count));
    for (int i = 0; i < candidate_count; i++) {
      for (int s = 0; s < _candidate_count; s++) {
        if (_candidate_klass_ids[s] != candidates[i].klass_id) {
          continue;
        }
        int n = candidates[i].qualifying_tid_count;
        if (n > MAX_CANDIDATE_QUALIFYING_TIDS) {
          n = MAX_CANDIDATE_QUALIFYING_TIDS;
        }
        for (int q = 0; q < n; q++) {
          _candidate_qualifying_tids[s][q] = candidates[i].qualifying_tids[q];
        }
        _candidate_qualifying_tid_count[s] = n;
        break;
      }
    }
    // Tag the tracked instances of THIS poll's candidates with leak tags.
    int tagged = LivenessTracker::instance()->tagLeakInstances(
        jvmti, candidates, candidate_count);
    _leak_tags_assigned = tagged;
    _leak_tags_resolved = 0; // reset on each tagging round
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets tagLeakInstances tagged=%d",
             tagged);
  }

  for (int i = 0; i < candidate_count; i++) {
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate[%d] klass_id=%u", i,
             candidates[i].klass_id);
    // Deliberately does NOT resolve candidates[i].representative directly: that field is a snapshot
    // taken under selectLeakCandidates()'s own shared-lock scan, which can go stale (LRU-evicted
    // and DeleteWeakGlobalRef()'d by LivenessTracker's cleanup_table(), running concurrently on a
    // different thread) at any point between that call and this one - see selectLeakCandidates()'s
    // comment (livenessTracker.h) for why resolving it here would be undefined behavior, not just a
    // null result.
    const u32 klass_id = candidates[i].klass_id;
    jobject obj = LivenessTracker::instance()->resolveCandidateRepresentative(
        jni, klass_id);
    if (obj == nullptr) {
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate[%d] klass_id=%u "
               "representative could not be resolved (died/evicted)",
               i, klass_id);
      // The representative died, but the canary chain (if the candidate was pruned by BFS before
      // the representative died) only needs the frontier table — not the live representative.
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
        // The representative died. Per-instance caching means we don't erase by klass_id — chains
        // for other instances of this class may still be valid.
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

    // Read the existing tag; seeding here would bypass the forward walk.
    jlong tag = getTag(jvmti, obj);

    // NOTE: the retired canary marker-tag decode used to live here (an object
    // pre-tagged with MARKER_TAG_BASE - slot took the legacy canary chain
    // reconstruction). The marker->leak-tag migration stopped pre-tagging
    // candidate representatives entirely - no JVMTI tag in the process can
    // ever be <= MARKER_TAG_BASE (-2^62): leak tags are positive
    // (LEAK_TAG_BASE), frontier tags positive, class tags small negative
    // magnitudes - so the branch was unreachable, and a stale negative tag
    // (a class tag) could never silently take the legacy canary path.
    // Candidate chain reconstruction now runs through the leak-tag discovery
    // block below and the dead-representative canary path earlier in this
    // loop.

    // Normal path: tag > 0 means the walk visited this object and assigned it a
    // frontier tag.

    // Keep the holder chain's root warm in the rotation queue: a growing container's current
    // internals are only reachable via the holder's re-walk (requeueChainRootForRotation()'s own
    // comment).
    if (tag > 0) {
      requeueChainRootForRotation(tag);
    }

    // Reconstruct only when this klass has no current chain cached: either nothing cached yet, or
    // what is cached was built from a different tag or an earlier search generation (see
    // current_search_ns above).
    bool need_refresh = false;
    jlong rep_chain_key = 0;
    for (int s = 0; s < _candidate_count; s++) {
      if (_candidate_klass_ids[s] == klass_id) {
        rep_chain_key = _candidate_frontier_tags[s];
        break;
      }
    }
    if (rep_chain_key != 0) {
      _resolved_chains_lock.lock();
      auto it = _resolved_chains.find(rep_chain_key);
      need_refresh = (it == _resolved_chains.end() ||
                      it->second.source_search_ns != current_search_ns);
      _resolved_chains_lock.unlock();
    }
    TEST_LOG("ReferenceChainTracker::pollWatchedTargets candidate[%d] klass_id=%u tag=%lld "
             "needRefresh=%d",
             i, klass_id, (long long)tag, need_refresh);
    if (need_refresh) {
      ReferenceChainEvent event;
      bool built = buildChainEvent(jvmti, jni, tag, &event);
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
        // Provisional stamp; drainPendingChainEvents() re-stamps each copy at dump time so the
        // event lands in that chunk's window.
        event._start_time = TSC::ticks();
        cacheResolvedChain(tag, std::move(event), tag, current_search_ns);
      }
    }
    // tag == 0: The representative object has no tag — the BFS walk hasn't reached it yet AND it is
    // not yet leak-tagged.

    // Build chain events for auto-marked discovered instances of this class.
    buildDiscoveredInstanceChains(jvmti, jni, klass_id, current_search_ns);

    jni->DeleteLocalRef(obj);
  }

  // Orphan fix: slots whose klass is NOT among this poll's candidates.
  for (int s = 0; s < _candidate_count; s++) {
    u32 slot_klass = _candidate_klass_ids[s];
    bool in_poll = false;
    for (int i = 0; i < candidate_count; i++) {
      if (candidates[i].klass_id == slot_klass) {
        in_poll = true;
        break;
      }
    }
    if (!in_poll && slot_klass != 0) {
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets orphan slot "
               "sweep: slot=%d klass_id=%u not in poll candidates - building "
               "its discovered chains",
               s, slot_klass);
      buildDiscoveredInstanceChains(jvmti, jni, slot_klass, current_search_ns);
    }
  }

  // Per-instance caching: chains are keyed by frontier tag, not klass_id.
}

// Inserts or refreshes klass_id's resolved chain - see _resolved_chains' comment
// (referenceChains.h) for why a resolved chain is cached and re-emitted rather than emitted once.
bool ReferenceChainTracker::cacheResolvedChain(jlong source_tag,
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
    return false;
  }
  CachedChain &slot = _resolved_chains[source_tag];
  slot.event = std::move(event);
  slot.source_tag = source_tag_val;
  slot.source_search_ns = source_search_ns;
  TEST_LOG("ReferenceChainTracker::cacheResolvedChain source_tag=%lld cache_size=%d",
           (long long)source_tag, (int)_resolved_chains.size());
  _resolved_chains_lock.unlock();
  return true;
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

// Builds and caches chain events for every auto-marked discovered instance recorded against a slot
// holding klass_id (see the auto-mark block in heapReferenceCallback() for how instances get
// recorded).
void ReferenceChainTracker::buildDiscoveredInstanceChains(jvmtiEnv *jvmti,
                                                           JNIEnv *jni,
                                                           u32 klass_id,
                                                           u64 current_search_ns) {
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
    // Skip if already cached for this instance - but only for the CURRENT search generation:
    // restartSearch() resets the frontier tag namespace, so a cached entry under the same numeric
    // tag from an earlier search describes a different object and must not suppress the rebuild
    // (the generation check mirrors the rep-refresh paths in pollWatchedTargets()).
    const u64 current_search_ns = load(_search_start_ns);
    _resolved_chains_lock.lock();
    auto cached_it = _resolved_chains.find(disc_tag);
    bool already_cached = (cached_it != _resolved_chains.end() &&
                           cached_it->second.source_search_ns ==
                               current_search_ns);
    _resolved_chains_lock.unlock();
    if (already_cached) {
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
               "already_cached disc_tag=%lld klass_id=%u slot=%d idx=%d",
               (long long)disc_tag, klass_id, s, d);
      continue;
    }
    ReferenceChainEvent event;
    bool built = buildChainEvent(jvmti, jni, disc_tag, &event);
    // Retention-explanation filter. Only applies to discovered instances, not canary.
    if (built && suppressChainEvent(event)) {
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
               "filtered depth=%u root_kind=%d disc_tag=%lld klass_id=%u",
               event._depth, (int)event._root_kind,
               (long long)disc_tag, klass_id);
      built = false;
      // Also drop any chain cached for this tag before the filter existed (or before an
      // improveChain/reparent upgraded it) - drainPendingChainEvents() re-emits cached chains
      // unconditionally, so suppressing only the build would leave the noise chains re-emitting
      // forever.
      invalidateResolvedChain(disc_tag);
    }
    if (built) {
      event._start_time = TSC::ticks();
      // Coverage accounting below must only advance for a chain that was actually stored - a
      // cache-full drop would let the search report the candidate as found without ever emitting
      // its chain.
      if (cacheResolvedChain(disc_tag, std::move(event), disc_tag,
                             current_search_ns)) {
      // Track coverage for adaptive CPU budget
      if (event._target_tag >= (u64)LEAK_TAG_BASE) {
        _leak_tags_resolved++;
        // A qualifying thread must discover at least one candidate instance.
        if (!(_candidate_found_bits & (1ULL << s))) {
          _candidate_found_bits |= (1ULL << s);
          _candidate_frontier_tags[s] = disc_tag;
          _candidate_parent_tags[s] = 0;
          _candidate_depths[s] = event._depth;
          _candidate_referrer_klasses[s] = klass_id;
          TEST_LOG_SUMMARY("ReferenceChainTracker::pollWatchedTargets canary "
                   "found: klass_id=%u slot=%d leak chain target_tag=%llu "
                   "via disc_tag=%lld (%d/%d candidates found)",
                   klass_id, s, (unsigned long long)event._target_tag,
                   (long long)disc_tag,
                   __builtin_popcountll(_candidate_found_bits),
                   _candidate_count);
        }
      }
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
               "auto-marked chain for klass_id=%u tag=%lld target_tag=%llu",
               klass_id, (long long)disc_tag,
               (unsigned long long)event._target_tag);
      }
    } else {
      TEST_LOG("ReferenceChainTracker::pollWatchedTargets "
               "buildChainEvent failed for discovered tag=%lld "
               "klass_id=%u slot=%d disc_idx=%d",
               (long long)disc_tag, klass_id, s, d);
    }
  }
  break;
}
}

void ReferenceChainTracker::recordDiscoveredInstance(u32 klass_id,
                                                     jlong frontier_tag,
                                                     bool leak_correlated) {
  // See the declaration's own comment (referenceChains.h) for the noise-eviction rationale.
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
    // All slots full and this instance is leak-correlated: evict the first slot held by an entry
    // with no leak tag (a noise instance).
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
  // LivenessTracker::tagLeakInstances() on this same thread (pollWatchedTargets ->
  // tagLeakInstances), so _candidate_* slot access here never races heapReferenceCallback's
  // auto-mark path.
  if (_frontier == nullptr) {
    return false;
  }
  FrontierEntry entry{};
  if (!_frontier->lookup(frontier_tag, &entry)) {
    return false; // not a live frontier tag (or the search restarted)
  }
  if (entry.leak_tag != 0) {
    // Already correlated (idempotent) - e.g. a second tagLeakInstances round after a post-restart
    // re-admission.
    return true;
  }
  _frontier->setLeakTag(frontier_tag, leak_tag);
  TEST_LOG_SUMMARY("ReferenceChainTracker::correlateAdmittedLeakTag "
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
  // Snapshot-and-keep, not a drain: every cached chain is copied out (and re-stamped so it lands in
  // the dumping chunk's window) while the cache itself is left intact, so the same live sample's
  // chain re-emits into every chunk it survives into (see _resolved_chains' comment).
  u64 now = TSC::ticks();
  _resolved_chains_lock.lock();
  for (const auto &kv : _resolved_chains) {
    out->push_back(kv.second.event);
    out->back()._start_time = now;
  }
  _resolved_chains_lock.unlock();
  TEST_LOG_SUMMARY("ReferenceChainTracker::drainPendingChainEvents re-emitted=%d",
           (int)out->size());
}

void ReferenceChainTracker::enqueuePendingAbandonedEvent() {
  // Called right after runPass() (referenceChains.cpp) writes SearchState::ABANDONED, on the same
  // thread, before shouldRunPass() gets a chance to call restartSearch() - so
  // buildAbandonedEvent()'s live read of _search_state/_abandon_reason/etc.
  ReferenceChainAbandonedEvent event;
  if (!buildAbandonedEvent(&event)) {
    return;
  }
  // Stamp when the search actually stopped, not when a later dump writes the queued event - an
  // abandon is a point-in-time occurrence and dump() can lag it by a whole chunk rotation.
  event._start_time = TSC::ticks();
  _pending_abandoned_events_lock.lock();
  if ((int)_pending_abandoned_events.size() >= MAX_PENDING_ABANDONED_EVENTS) {
    _pending_abandoned_events_lock.unlock();
    Counters::increment(REFERENCE_CHAIN_EVENTS_DROPPED);
    TEST_LOG_SUMMARY("ReferenceChainTracker::enqueuePendingAbandonedEvent dropped, "
             "queue full (at MAX_PENDING_ABANDONED_EVENTS=%d)",
             MAX_PENDING_ABANDONED_EVENTS);
    return;
  }
  _pending_abandoned_events.push_back(event);
  TEST_LOG_SUMMARY("ReferenceChainTracker::enqueuePendingAbandonedEvent reason=%d "
           "queue_size=%d",
           (int)event._reason, (int)_pending_abandoned_events.size());
  _pending_abandoned_events_lock.unlock();
}

void ReferenceChainTracker::drainPendingAbandonedEvents(
    std::vector<ReferenceChainAbandonedEvent> *out) {
  if (out == nullptr) {
    return;
  }
  // True drain, unlike drainPendingChainEvents() above: each queued event describes a discrete past
  // occurrence, not an ongoing live sample, so once Profiler::dump() (profiler.cpp) has emitted it
  // there is nothing left to re-report on the next dump.
  _pending_abandoned_events_lock.lock();
  out->insert(out->end(), _pending_abandoned_events.begin(),
              _pending_abandoned_events.end());
  _pending_abandoned_events.clear();
  _pending_abandoned_events_lock.unlock();
  TEST_LOG_SUMMARY("ReferenceChainTracker::drainPendingAbandonedEvents drained=%d",
           (int)out->size());
}
