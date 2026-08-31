---
id: ev-source-poll-vs-callback
type: evidence
status: confirmed
depends_on: []
supersedes: []
related: [find-marker-tag-slot-index-mismatch, find-one-shot-pretag-gate, find-canary-search-cannot-terminate]
tags: [source, referenceChains, citations, verified-at-head]
created: 2026-08-24
updated: 2026-08-24
---

# Source excerpts: writer decodes the slot, reader uses the loop index

All line numbers re-verified against the working tree at HEAD
`8114019c2e97ca7641e151e4f7de080e3ec6fc5b`.

## Writer — `heapReferenceCallback()`, `referenceChains.cpp:1508-1529` (CORRECT)

```cpp
  if (ctx->tracker->_candidate_count > 0 &&
      *tag_ptr <= ReferenceChainTracker::MARKER_TAG_BASE) {
    int candidate_idx = (int)(ReferenceChainTracker::MARKER_TAG_BASE - *tag_ptr);   // :1510
    if (candidate_idx >= 0 && candidate_idx < ctx->tracker->_candidate_count) {
      jlong rtag = (referrer_tag_ptr != nullptr) ? *referrer_tag_ptr : 0;
      u32 candidate_klass = ctx->tracker->classTags()->resolve(class_tag);
      if (rtag > 0) {
        FrontierEntry parent{};
        if (ctx->frontier->lookup(rtag, &parent)) {
          jlong frontier_tag = *tag_ptr;
          ctx->frontier->insert(frontier_tag, rtag, parent.referrer_klass,
                                parent.depth + 1, FrontierEntryState::FRONTIER,
                                parent.root_kind);
          ctx->tracker->_candidate_parent_tags[candidate_idx]      = rtag;        // :1525
          ctx->tracker->_candidate_frontier_tags[candidate_idx]    = frontier_tag;// :1526
          ctx->tracker->_candidate_referrer_klasses[candidate_idx] = candidate_klass;
          ctx->tracker->_candidate_depths[candidate_idx]           = parent.depth + 1;
          ctx->tracker->_candidate_found_bits |= (1ULL << candidate_idx);         // :1529
```

## Reader — `pollWatchedTargets()`, `referenceChains.cpp:3456-3490` (BUG)

```cpp
    jlong tag = getTag(jvmti, obj);                                    // :3456
    if (tag <= MARKER_TAG_BASE) {                                      // :3465
      bool need_refresh = false;
      _resolved_chains_lock.lock();
      auto it = _resolved_chains.find(klass_id);
      need_refresh = (it == _resolved_chains.end() ||
                      it->second.source_tag != tag ||
                      it->second.source_search_ns != current_search_ns);  // :3469-3471
      _resolved_chains_lock.unlock();
      TEST_LOG("...canary candidate[%d] klass_id=%u marker_tag=%lld needRefresh=%d",
               i, klass_id, (long long)tag, need_refresh);             // :3473-3475
      if (need_refresh) {
        ReferenceChainEvent event;
        bool built = buildCanaryChainEvent(i, &event);                 // :3478  <-- i, not slot
        TEST_LOG("...buildCanaryChainEvent(candidate=%d) -> %d", i, built);
        if (built) {
          event._start_time = TSC::ticks();
          cacheResolvedChain(klass_id, std::move(event),
                              _candidate_frontier_tags[i],             // :3485  <-- same bug
                              current_search_ns);
        }
      }
      jni->DeleteLocalRef(obj);
      continue;
    }
```

## Failure path actually taken — `referenceChains.h:2093-2141`

```cpp
bool buildCanaryChainEvent(int candidate_idx, ReferenceChainEvent *out) {   // :2093
  if (_frontier == nullptr || out == nullptr ||
      candidate_idx < 0 || candidate_idx >= _candidate_count) return false; // :2094-2097
  jlong parent_tag   = _candidate_parent_tags[candidate_idx];
  u32 candidate_klass= _candidate_referrer_klasses[candidate_idx];
  jlong frontier_tag = _candidate_frontier_tags[candidate_idx];
  ...
  if (parent_tag > 0) {
    if (!_frontier->lookup(parent_tag, &entry)) return false;               // :2107
    for (jlong tag = parent_tag; tag > 0;) {
      if (!_frontier->lookup(tag, &entry)) return false;                    // :2112
      ...
    }
  } else if (parent_tag == 0 && frontier_tag > 0) {
    if (!_frontier->lookup(frontier_tag, &entry)) return false;             // :2122-2124
    ...
  } else {
    return false; // never pruned (candidate not reached)                   // :2127  <-- HIT
  }
```

With slot 0 never written, `parent_tag == 0 && frontier_tag == 0`, so the
`:2127` branch fires every time.

## Self-heal blockers

`referenceChains.cpp:3375-3397` — one-shot pre-tagging:

```cpp
    if (_candidate_count == 0) {                                        // :3375
      _candidate_count = candidate_count;
      _candidate_found_bits = 0;
      for (int i = 0; i < candidate_count; i++) {
        jlong tag = MARKER_TAG_BASE - i;
        _candidate_tags[i] = tag;
        jobject obj = LivenessTracker::instance()->resolveCandidateRepresentative(
            jni, candidates[i].klass_id);
        if (obj != nullptr) { jvmti->SetTag(obj, tag); jni->DeleteLocalRef(obj); }
      }
      TEST_LOG("...canary: %d candidates pre-tagged with marker tags", _candidate_count);
      Counters::increment(REFERENCE_CHAIN_CANDIDATE_COUNT, _candidate_count);
    }
```

`referenceChains.cpp:3090-3108` — abandon suppressed while urgent, and
completion needs all bits set:

```cpp
  } else if (_passes_since_last_progress >= NO_PROGRESS_PASS_LIMIT &&
             !isUrgent()) {                                             // :3090-3091
    store(_abandon_reason, (u8)SearchAbandonReason::TTL);
    storeRelease(_search_state, (u8)SearchState::ABANDONED);
  } else if (_candidate_count > 0 &&
             __builtin_popcountll(_candidate_found_bits) ==
                 (u64)_candidate_count) {                               // :3101-3103
    storeRelease(_search_state, (u8)SearchState::COMPLETED);
    Counters::increment(REFERENCE_CHAIN_CANDIDATES_FOUND,
                             __builtin_popcountll(_candidate_found_bits));
  }
```

`referenceChains.cpp:914-922` — `shouldRunPass()` keeps returning true for
as long as any candidate bit is unset (so the search never idles out):

```cpp
  if (_candidate_count > 0 &&
      __builtin_popcountll(_candidate_found_bits) < (u64)_candidate_count) {
    TEST_LOG("ReferenceChainTracker::shouldRunPass -> true (canary search, "
             "%d/%d candidates found)",
             (int)__builtin_popcountll(_candidate_found_bits),
             (int)_candidate_count);
    return true;
  }
```
