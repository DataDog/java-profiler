# Reference Chain Canary Search — Implementation Plan

**Status:** Planning (local-only, not committed)
**Date:** 2026-08-19
**Jira:** [PROF-15341](https://datadoghq.atlassian.net/browse/PROF-15341)
**Design doc:** `doc/architecture/ReferenceChainCanarySearch.md` (local-only)

## Overview

Replace the whole-graph forward BFS with a pruned forward BFS that treats
leaked objects as leaves and terminates early when all leaked
candidates are found.

## Prerequisites

- The progress-based termination + urgency-driven budget escalation
  (commits `979bd0139`, `b56c65c63`) must be on the branch.
- `LivenessTracker::selectLeakCandidates()` must be functional
  (it is — shipped with the liveness/generations feature).

## Phase 1: Candidate state fields on ReferenceChainTracker

**Files:** `referenceChains.h`, `referenceChains.cpp`

### 1.1 Define MARKER_TAG_BASE

In `referenceChains.h`, in the public section near `NO_PROGRESS_PASS_LIMIT`:

```cpp
// Base marker tag for canary-search candidates. Each candidate i
// gets MARKER_TAG_BASE - i (distinct negative values) so
// heapReferenceCallback() can tell which candidate was found.
// Negative to avoid collision with frontier tags (positive
// jlong from _next_tag, referenceChains.h:623). Class tags are
// always negative (nextClassTag() at referenceChains.h:1671),
// so a negative marker is disjoint from the frontier
// tag space.
static constexpr jlong MARKER_TAG_BASE = -(1LL << 62);
```

### 1.2 Add candidate-tracking fields

In `referenceChains.h`, private section near `_passes_since_last_progress`:

```cpp
// Canary-search candidate set: pre-tagged with distinct
// marker tags (MARKER_TAG_BASE - i) before the walk.
// _candidate_found is a packed bitmap (bit i = candidate i found).
// _candidate_tags[i] holds the marker tag for candidate i.
// Reset by resetSearchStateForTest().
int _candidate_count;
u64 _candidate_found_bits; // bitmap, up to 64 candidates
jlong _candidate_tags[MAX_LEAK_CANDIDATES]; // per-candidate marker tag
```

### 1.3 Initialize in start()

In `referenceChains.cpp`, `start()`, after `_passes_since_last_progress = 0`:

```cpp
_candidate_count = 0;
_candidate_found_bits = 0;
// _candidate_tags will be filled by Phase 2 pre-tagging.
```

### 1.4 Reset in resetSearchStateForTest()

In `referenceChains.cpp`, `resetSearchStateForTest()`, after `_passes_since_last_progress = 0`:

```cpp
_candidate_count = 0;
_candidate_found_bits = 0;
// Also clear any marker tags left by a previous test's canary search.
// (GetObjectsWithTags cleanup runs in runPass() on completion, but
// resetSearchStateForTest() may be called before that.)
```

**Exit criteria:** Fields exist, initialize to 0, reset in test seam. Compiles.

## Phase 2: Pre-tag candidates in threadLoop()

**Files:** `referenceChains.cpp`

### 2.1 Pre-tag before first pass

In `threadLoop()`, before the first `runPass()` call (after the `isUrgent()`
cadence/pause-target block, before `shouldRunPass`):

```cpp
// Canary pre-tagging: tag each leaked candidate with a
// distinct marker tag (MARKER_TAG_BASE - i) so
// heapReferenceCallback() can tell which candidate was
// found. Runs on the BFS thread (same thread that
// calls FollowReferences). Only done once per search
// (when !_search_started).
if (!_search_started && _candidate_count == 0) {
    KlassCandidate candidates[MAX_LEAK_CANDIDATES];
    int n = LivenessTracker::instance()->selectLeakCandidates(
        candidates, MAX_LEAK_CANDIDATES);
    _candidate_count = n;
    _candidate_found_bits = 0;
    jvmtiEnv *jvmti = VM::jvmti();
    JNIEnv *jni = VM::jni();
    if (jvmti != nullptr && jni != nullptr) {
        for (int i = 0; i < n; i++) {
            jobject obj = jni->NewLocalRef(candidates[i].representative);
            if (obj != nullptr) {
                jlong tag = MARKER_TAG_BASE - i;
                _candidate_tags[i] = tag;
                jvmti->SetTag(obj, tag);
            }
            jni->DeleteLocalRef(obj);
        }
    }
}
```

### 2.2 Guard: only when generations + reference chains are enabled

Wrap the pre-tagging in a check:
```cpp
if (!_search_started && _candidate_count == 0 &&
    LivenessTracker::instance()->gcGenerationsEnabled()) {
    // ... pre-tag ...
}
```

This ensures the canary search only runs when the leak-detection
gate (generations) is active. Without generations,
`selectLeakCandidates()` returns 0, so `_candidate_count` stays 0 and
the canary pruning is a no-op (the walk behaves as before).

**Exit criteria:** Candidates are pre-tagged before the first pass.
`_candidate_count` reflects the number of candidates. Compiles.

## Phase 3: Prune heapReferenceCallback() at candidates

**Files:** `referenceChains.cpp`

### 3.1 Check marker tag in heapReferenceCallback()

In `heapReferenceCallback()`, before the existing `admitObject()` call,
after the class-tag check (`*tag_ptr < 0` block):

```cpp
// Canary pruning: if this object is a pre-tagged leak
// candidate, record its chain link but do NOT enqueue
// its children (treat as a leaf). Do not return
// JVMTI_VISIT_ABORT -- that aborts the entire
// FollowReferences walk (JVMTI spec). Just skip
// admitObject() for this object.
//
// Check *tag_ptr against each candidate's marker tag.
// A marker tag is MARKER_TAG_BASE - i (negative).
if (*tag_ptr < 0 && *tag_ptr <= MARKER_TAG_BASE) {
    // Identify which candidate this is.
    int candidate_idx = (int)(MARKER_TAG_BASE - *tag_ptr);
    if (candidate_idx >= 0 && candidate_idx < _candidate_count) {
        jlong rtag = *referrer_tag_ptr;
        if (rtag > 0) {
            FrontierEntry parent{};
            if (ctx->frontier->lookup(rtag, &parent)) {
                // Record this candidate's chain link.
                // Assign a normal frontier tag to this candidate
                // (via nextTag()) so buildChainEvent() can
                // reconstruct the chain from the frontier
                // table. The marker tag is NOT the tag
                // stored in the frontier -- the frontier
                // uses the normal positive tag.
                jlong frontier_tag = nextTag();
                ctx->frontier->insert(frontier_tag, rtag,
                                        ctx->referrer_klass,
                                        ctx->depth,
                                        FrontierEntryState::FRONTIER,
                                        ctx->root_kind);
                _candidate_found_bits |= (1ULL << candidate_idx);
            }
        }
    }
    // Do NOT enqueue children for this object.
    // Return 0 (continue the walk) -- NOT
    // JVMTI_VISIT_ABORT.
    return 0;
}
```

### 3.2 Implementation note: recording the chain link without enqueuing

The code snippet above calls `FrontierTable::insert()` directly with a
fresh `nextTag()` value, bypassing `admitObject()` (which would enqueue
children into `_pending_expand`). The candidate's `parent_tag` and
`referrer_klass` are recorded in the frontier table, but its children are
never added to `_pending_expand`. `buildChainEvent(frontier_tag, ...)` can
then reconstruct the chain from the frontier table.

Note: `nextTag()` increments `_next_tag`, so the candidate gets both a
marker tag (negative, for pruning) and a frontier tag (positive, for chain
reconstruction). The `heapReferenceCallback()` returns 0 (continue walk)
without enqueuing children) — the marker tag stays on the object so
future passes still recognize it, but the frontier tag is what
`buildChainEvent()` uses.

**Exit criteria:** `heapReferenceCallback()` prunes at marker-tagged
objects. Children of candidates are not enqueued. Non-candidates
behave as before. Compiles.

## Phase 4: Early termination — all candidates found

**Files:** `referenceChains.cpp`

### 4.1 Check after each pass

In `runPass()`, after the existing termination checks (frontier cap,
no-progress, natural completion), add:

```cpp
// Canary early termination: if all candidates have been
// found, the search is complete -- no need to
// continue the BFS.
if (_candidate_count > 0 &&
    __builtin_popcountll(_candidate_found_bits) == _candidate_count) {
    storeRelease(_search_state, (u8)SearchState::COMPLETED);
}
```

### 4.2 Verify in shouldRunPass()

`shouldRunPass()` already checks `_search_state`. Once
`runPass()` sets `COMPLETED`, `shouldRunPass()` will return false (terminal
state, `canAffordNewSearch()` not called). No change needed — just
confirming the interaction.

**Exit criteria:** Search transitions to `COMPLETED` when all
candidates are found. `shouldRunPass()` respects it.

## Phase 5: Cleanup

**Files:** `referenceChains.cpp`

### 5.1 Release marker tags on completion/abandonment

In `runPass()`, after the existing tag-release block (`if
(load(_search_state) != SearchState::RUNNING) { _tags_released =
releaseSearchTags(...); }`), add canary cleanup:

```cpp
// Release canary marker tags.
if (_candidate_count > 0) {
    jvmtiEnv *jvmti = VM::jvmti();
    JNIEnv *jni = VM::jni();
    if (jvmti != nullptr && jni != nullptr) {
        // GetObjectsWithTags to find all live
        // marker-tagged objects and clear them.
        // Must DeleteLocalRef each object before
        // Deallocate-ing the array (matches the
        // existing pattern at referenceChains.cpp:2125-2133).
        for (int i = 0; i < _candidate_count; i++) {
            jlong tag = _candidate_tags[i];
            jint count = 0;
            jobject *objects = nullptr;
            jvmtiError err = jvmti->GetObjectsWithTags(
                &tag, 1, &count, &objects);
            if (err == JVMTI_ERROR_NONE && count > 0) {
                for (jint j = 0; j < count; j++) {
                    jvmti->SetTag(objects[j], 0);
                    jni->DeleteLocalRef(objects[j]);
                }
                jvmti->Deallocate((unsigned char *)objects);
            }
        }
    }
    _candidate_count = 0;
    _candidate_found_bits = 0;
}
```

### 5.2 Reset in resetSearchStateForTest()

Already added in Phase 1.4.

**Exit criteria:** Marker tags are released on completion
and abandonment. `resetSearchStateForTest()` resets candidate state.

## Phase 6: Tests

### 6.1 gtest — canary pruning

**File:** `ddprof-lib/src/test/cpp/referenceChains_ut.cpp`

Add a test:
- Pre-tag a candidate with `MARKER_TAG`.
- Run a pass with a graph where the candidate is reachable.
- Verify the candidate's chain link is recorded but its children are not in
  `_pending_expand`.
- Verify `_candidate_found_bits` is set.

### 6.2 gtest — early termination

- Pre-tag 2 candidates.
- Run passes until both are found.
- Verify `searchState() == COMPLETED` after 2 passes (both found),
  not after the full graph is explored.

### 6.3 gtest — resetSearchStateForTest resets candidate state

- Pre-tag candidates, run a search, stop.
- Call `resetSearchStateForTest()`.
- Verify `_candidate_count == 0` and `_candidate_found_bits == 0`
  (via a test accessor).

### 6.4 Java integration — canary search completes faster

**File:** `ddprof-test/src/test/java/com/datadoghq/profiler/referencechains/ReferenceChainTrackingTest.java`

- Allocate a large synthetic heap (thousands of objects).
- Enable `generations=true,referencechains=true`.
- Verify the search completes (produces `datadog.ReferenceChain` events)
  in seconds, not minutes.
- Compare against a baseline run with `referencechains=true` but
  `generations=false` (no candidates → whole-graph BFS → slow) to
  demonstrate the speedup.

**Exit criteria:** All gtests pass. Java integration test passes.

## Phase 7: Wire up the candidate feed

**Files:** `referenceChains.cpp`

### 7.1 pollWatchedTargets() integration

The current `pollWatchedTargets()` calls
`selectLeakCandidates()` and checks `GetTag(obj, &tag)`
for each candidate's `jweak` — if the walk tagged it (positive tag from `_next_tag`), it builds the chain via `buildChainEvent(tag, ...)`.

With canary search, candidates are pre-tagged with
**marker tags** (negative, `MARKER_TAG_BASE - i`). But `buildChainEvent()` expects a **frontier tag** (positive). The Phase 3 pruning assigns a frontier tag via `nextTag()` when recording the chain link. `pollWatchedTargets()` must use that frontier tag, not the marker tag, when calling `buildChainEvent()`.

**Change needed:** `pollWatchedTargets()` must track the mapping from marker tag to frontier tag. Store the frontier tag assigned in Phase 3 (e.g., in `_candidate_frontier_tags[MAX_LEAK_CANDIDATES]`) and pass that to `buildChainEvent()` instead of re-reading `GetTag(obj)` (which would return the marker tag, not the frontier tag).

Alternatively, `pollWatchedTargets()` can iterate `_candidate_found_bits`, and for each found candidate, look up its frontier tag from the frontier table by searching for the marker tag's corresponding entry. But the simpler approach is to store the frontier tag at pruning time.

**Exit criteria:** `pollWatchedTargets()` passes the frontier tag (not the marker tag) to `buildChainEvent()`. Chains are emitted for found candidates with correct frontier tags.

## Risk register

| Risk | Mitigation |
|------|------------|
| Marker tag collision with frontier tags | MARKER_TAG_BASE is negative; frontier tags are positive. Disjoint. Each candidate gets a distinct tag (BASE - i). |
| JVMTI_VISIT_ABORT aborts entire walk | Do not return it — skip admitObject() instead. |
| buildChainEvent expects frontier tag, not marker tag | Assign a frontier tag via nextTag() at pruning time; store it for pollWatchedTargets(). |
| Candidate dies between pre-tagging and walk | GetObjectsWithTags on cleanup only finds live objects. DeleteLocalRef each before Deallocate. |
| Candidate not reachable from GC roots | Same as current — search abandons via no-progress. Future: sub-leaked Phase 1b. |
| Multiple instances of same leaking klass | Tag representative only. Other instances are the same leak. |
| resetSearchStateForTest() stale state | Reset _candidate_count, _candidate_found_bits, and _candidate_tags. |
| selectLeakCandidates() lock ordering | Call before runPass(); SetTag takes JVMTI tag-map mutex, not LivenessTracker or FrontierTable locks. No overlap. |
