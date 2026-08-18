# Reference Chain Canary Search

**Status:** Proposed
**Date:** 2026-08-19
**Jira:** [PROF-15341](https://datadoghq.atlassian.net/browse/PROF-15341)

## Problem

The current reference chain implementation (`ReferenceChainTracker::runPass()`) does
a **whole-graph forward BFS** from GC roots. On a 4 GiB heap with ~4M objects, the
search needs ~2000 passes at 2000 edges/pass (the auto-tuned default) to explore the
entire reachable graph. The progress-based termination (no TTL kill) lets the search
run to completion, but it takes ~83 minutes — during which the app may OOM if the
leak is fast enough, or the search may be abandoned by the frontier cap before it
reaches the leaking objects.

The root cause: we explore the **entire** reachable graph even though we already
know **which** objects are leaking (from
`LivenessTracker::selectLeakCandidates()`). The search doesn't need to find
*all* reachable objects — it needs reference chains from GC roots to a small set
of leaked objects.

## Goal

Replace the whole-graph BFS with a **canary search**: a forward BFS from GC
roots that treats leaked objects as **leaves** (records their path, does not
enqueue their children) and stops as soon as all leaked objects have been found
and their paths recorded.

This is dramatically less work than a full-graph BFS: instead of exploring ~4M
objects, the search explores only enough of the graph to reach the ~3-5 leaked
candidates, then stops.

## JVMTI constraint

JVMTI's `FollowReferences` / `IterateThroughHeap` only walks **forward**
(object → children). There is no JVMTI API to ask "who points to this object?"
(backward traversal). A true backward BFS from leaked objects is impossible
with JVMTI alone.

The canary approach works within this constraint: it is still a **forward**
walk from GC roots — it just **prunes** at leaked objects instead of exploring
the whole graph.

## Inspiration

LeakCanary PR [#2800](https://github.com/square/leakcanary/pull/2800)
replaces a dominator-tree-based retained-size computation with a two-phase BFS:

1. **Phase 1**: Forward BFS from GC roots, leaked objects as leaves.
   The resulting visited set is R₀ — all objects reachable from GC roots
   without passing through any leaked object.
2. **Phase 2**: For each leaked object found in Phase 1, compute
   retained size via a restricted BFS (objects not in R₀).

We adapt Phase 1 only — we don't need retained sizes, just reference
chains (referrer *type* sequences from GC root to leaked object).

## Design

### Current architecture (what changes)

```
ReferenceChainTracker::runPass()
  └─ runPassManualWalk()     // forward BFS from GC roots
       └─ expandFrontier()    // expands ALL frontier entries
            └─ heapReferenceCallback()  // admits every edge
  └─ pollWatchedTargets()      // reads chains for tagged candidates
```

The search explores the entire root-reachable graph (bounded by
hop/budget/frontier caps), then `pollWatchedTargets()` reconstructs chains
for candidates the walk happened to tag. A candidate not reached by the
walk gets no chain.

### Proposed architecture

```
ReferenceChainTracker::runPass()
  └─ runPassManualWalk()     // forward BFS from GC roots
       │   // BUT: heapReferenceCallback() checks each visited object
       │   // against the leaked-candidate set BEFORE enqueuing children.
       │   // If the object IS a candidate: record its path, do NOT enqueue.
       │   // If it is NOT a candidate: enqueue children as normal.
       └─ expandFrontier()
            └─ heapReferenceCallback()
  └─ pollWatchedTargets()      // chains for found candidates
  └─ checkAllCandidatesFound() // if all candidates found → COMPLETED
```

### Key change: `heapReferenceCallback()` prunes at candidates

The single change that makes this work: in
`heapReferenceCallback()` (the JVMTI callback invoked for each edge
during `FollowReferences`), check whether the destination object
is a leaked candidate **before** enqueuing its children.

- If the destination object **is** a candidate:
  - Record its `parent_tag` and `referrer_klass` (the chain link).
  - Do **not** enqueue its children (treat as a leaf — skip the `admitObject()` call for this object).
  - Mark it as "found" in the candidate set.
  - **Do not** return `JVMTI_VISIT_ABORT` — that aborts the entire `FollowReferences` walk, not just this subtree (JVMTI spec: *"If this value is returned, the follow references operation immediately terminates"*). The walk continues normally for other edges; the candidate's children are simply never enqueued.
- If the destination object **is not** a candidate:
  - Enqueue children as normal (current behavior).

This means the BFS frontier only grows along paths that **don't** pass
through leaked objects. Paths that reach a leaked object stop there —
the leaked object's subtree is never explored.

### Early termination: all candidates found

After each pass, check whether **all** leaked candidates have been
found (their paths recorded). If so, transition the search to
`SearchState::COMPLETED` immediately — no need to continue the
BFS.

This replaces the current termination logic:
- ~~TTL abandonment~~ (removed by the progress-based termination commit)
- ~~No-progress abandonment~~ (still applies: if the frontier stops
  growing and not all candidates are found, abandon after
  `NO_PROGRESS_PASS_LIMIT` stale passes)
- **Frontier cap** (still applies: if the frontier fills up before all
  candidates are found, abandon — the graph is too interconnected
  to reach the candidates within the resource bound)
- **All-candidates-found** (new: natural completion as soon as
  every candidate's path has been recorded)

### Candidate set: how `heapReferenceCallback()` knows the candidates

`LivenessTracker::selectLeakCandidates()` returns up to
`MAX_LEAK_CANDIDATES = 5` `KlassCandidate` entries, each carrying a klass
id and a `jweak` representative instance.

The current `pollWatchedTargets()` already resolves each
candidate's `jweak` to a `jobject` and checks `GetTag(obj, &tag)` to see
if the walk has tagged it. The canary search needs the same set, but
**earlier** — at callback time, not just at poll time.

Two options:

1. **Pre-tag the candidates** before the walk: call `SetTag(candidate_obj, marker_tag)` for each candidate before `FollowReferences`. Then `heapReferenceCallback()` checks `*tag_ptr == marker_tag` — if so, it's a candidate, prune. This is cheap (a handful of `SetTag` calls) but requires resolving the `jweak` representatives before the walk. The marker tag must be **negative** (in the class-tag range, e.g., `-(1 << 62)`) to avoid collision with frontier tags, which are positive `jlong` values starting at 1 from `_next_tag` (`referenceChains.h:623`). Class tags are always negative (`nextClassTag()` at `referenceChains.h:1671`), so a negative marker is disjoint from the frontier tag space.
2. **Pass a klass-id set to the callback**: `heapReferenceCallback()` already receives the destination object's klass via `class_tag` (JVMTI provides `jvmtiHeapReferenceCallback`'s `class_tag` field). Compare against the candidate klass ids. This avoids pre-tagging but matches by *klass*, not *instance* — if multiple instances of the same leaking klass exist, all are treated as leaves. For reference-chain purposes this is fine (any instance's chain is evidence of the same leak).

**Recommendation: Option 1** (pre-tag candidates). It's exact (instance-level, not klass-level), reuses the existing tag mechanism, and the number of `SetTag` calls is tiny (≤5). The marker tag must be negative to avoid collision with frontier tags.

### What stays the same

- **Frontier table** (`FrontierTable`): unchanged. Still stores `(tag, parent_tag, referrer_klass, depth)` records.
- **EdgeStore / chain reconstruction**: unchanged. `buildChainEvent(tag, ...)` still walks `parent_tag` links.
- **JVMTI tag lifecycle**: unchanged. Tags are still assigned by the walk, released on completion/abandonment.
- **`pollWatchedTargets()`**: still runs after each pass, but now also checks
  "all candidates found?" rather than just "was this candidate tagged?".
- **Pain budget, PID controller, pause-time SLO**: unchanged.
- **`isUrgent()` / `secondsToOOM()`**: unchanged. When urgent, the search
  runs to completion (no TTL, no no-progress abandon) — now also with
  early termination when all candidates are found.

## Algorithm (revised)

1. **In `threadLoop()`'s first iteration** (before the first `runPass()`), after
   `LivenessTracker::selectLeakCandidates()` returns the candidate set:
   - Resolve each `KlassCandidate::representative` (`jweak` to `jobject`) on the BFS thread.
   - `SetTag(obj, MARKER_TAG)` for each. `MARKER_TAG` is negative (e.g., `-(1 << 62)`).
   - Store the candidate count and a `found` bitmap (or counter) as fields on
     `ReferenceChainTracker` so they survive across passes on the BFS thread.
2. **Pass 1** (root enumeration): `FollowReferences(0, nullptr, nullptr, ...)`
   - forward BFS from all GC roots. For each edge's destination object:
   - If `*tag_ptr == MARKER_TAG`: record chain link, mark candidate
     as found. **Do not** clear the tag.
     **Do not** return `JVMTI_VISIT_ABORT` -- that aborts the
     entire walk (JVMTI spec). Simply skip the `admitObject()`
     call for this object (don't enqueue children).
   - Otherwise: enqueue children as normal (admit to frontier).
3. **After pass 1**: check if all candidates are found. If so,
   `SearchState::COMPLETED`.
4. **Pass 2+** (resumed): `expandFrontier()` --
   `GetObjectsWithTags` for the persisted frontier, then
   `FollowReferences` from each resolved frontier object. Same pruning logic.
5. **Termination**:
   - All candidates found -> `COMPLETED` (new).
   - Frontier cap hit -> `ABANDONED` (existing).
   - No progress for `NO_PROGRESS_PASS_LIMIT` passes -> `ABANDONED` (existing).
   - Urgent (`secondsToOOM() < 300s`): suppress all abandonment
     except frontier cap (existing from the progress-based termination commit).
6. **Cleanup**: on completion or abandonment, use `GetObjectsWithTags(MARKER_TAG)` to find
   all live marker-tagged objects and `SetTag(obj, 0)` for each. Do not re-resolve `jweak`
   references -- a candidate may have died between pre-tagging and cleanup.

## Cost/benefit

| Metric | Current (whole-graph BFS) | Canary (pruned BFS) |
|--------|--------------------------|---------------------|
| Edges explored | ~4M (entire reachable graph) | ~10K-100K (enough to reach ≤5 candidates) |
| Passes to completion | ~2000 | ~5-50 |
| Wall-clock to completion | ~83 min | ~5-50 sec |
| STW per pass | ~5ms (PID-controlled) | ~5ms (unchanged) |
| Total STW | ~10s | ~0.25s |
| Chains produced | All reachable objects' chains (if walk completes) | Only leaked candidates' chains (the ones that matter) |

The canary search reduces total work by **10-100x** on typical heaps (candidates close to GC roots), with no change to per-pass STW cost. In the worst case (candidates deep in the graph), the search explores a similar fraction of the heap as the whole-graph BFS -- but never more. The search completes in seconds rather than minutes on typical heaps, making it viable for real-time leak diagnosis.

## Risk: candidates not reachable from GC roots

If a leaked object is not reachable from any GC root (e.g., it's only reachable via another leaked object, or via a
native data structure not visible to `FollowReferences`), the canary BFS
won't find it. The search will exhaust the frontier and abandon via the
no-progress detector.

This is the same failure mode as the current whole-graph BFS —
if the walk never reaches the object, `pollWatchedTargets()` never
sees it tagged. The canary search doesn't make this worse: the current
implementation also can't chain objects it doesn't visit. It just wastes
the entire graph traversal before giving up.

### Mitigation: sub-leaked objects

If Phase 1's BFS exhausts without finding all candidates,
the remaining candidates are only reachable through other leaked
objects (or through non-JVMTI-visible paths). These can be reported
as "sub-leaked" — their chain terminates at another leaked
object rather than a GC root. This is the LeakCanary Phase 1b
approach: seed a secondary BFS from already-found leaked objects
(now traversed normally, children enqueued) to find the remaining
candidates.

This is a **future enhancement**, not part of the initial canary
implementation. The initial version simply abandons if
not all candidates are found — the same outcome as today, but
arrived at in seconds rather than ~83 minutes.

## Implementation plan

### Phase 1: Pre-tag candidates

- In `threadLoop()`'s first iteration (before the first `runPass()`), after
  `LivenessTracker::selectLeakCandidates()` returns the candidate set:
  - Resolve each `KlassCandidate::representative` (`jweak` to `jobject`) on the BFS thread.
  - `SetTag(obj, MARKER_TAG)` for each.
  - Store the candidate count and a `found` bitmap (or counter) as fields on
    `ReferenceChainTracker`.
- Define `MARKER_TAG` as a reserved **negative** tag value (e.g., `-(1 << 62)`)
  that `heapReferenceCallback()` checks before normal admission.
  Negative to avoid collision with frontier tags (positive `jlong` from
  `_next_tag`, `referenceChains.h:623`). Class tags are always negative
  (`nextClassTag()` at `referenceChains.h:1671`).

### Phase 2: Prune `heapReferenceCallback()` at candidates

- In `heapReferenceCallback()`, before the existing
  `admitObject()` call:
  - Check `*tag_ptr == MARKER_TAG`.
  - If yes: record `parent_tag` and `referrer_klass` into the
    frontier/EdgeStore (same as a normal admission, but **without** enqueuing
    children). Mark candidate as found. **Do not** return
    `JVMTI_VISIT_ABORT` -- that aborts the entire walk (JVMTI spec).
    Simply skip the `admitObject()` call for this object.
  - If no: proceed with normal admission (current behavior).

### Phase 3: Early termination

- After each pass in `runPass()`, check if all candidates are found
  (candidate `found` flags all true).
- If so: `storeRelease(_search_state, COMPLETED)`.
- Otherwise: existing termination logic (frontier cap, no-progress, urgency).

### Phase 4: Cleanup

- On completion or abandonment, use `GetObjectsWithTags(MARKER_TAG)` to find
  all live marker-tagged objects and `SetTag(obj, 0)` for each. Do not
  re-resolve `jweak` references -- a candidate may have died between
  pre-tagging and cleanup.
- Reset the `found` bitmap.
- `resetSearchStateForTest()` must also reset the candidate set (marker tags +
  found flags) so a second test's canary search doesn't prune at stale
  candidates.

### Phase 5: Tests

- **gtest**: Update `referenceChains_ut.cpp` mock to verify pruning
  behavior (candidates are leaves, non-candidates are expanded; no `JVMTI_VISIT_ABORT` returned).
- **gtest**: Verify early termination when all candidates are found.
- **gtest**: Verify `resetSearchStateForTest()` resets the candidate set.
- **Java integration**: Update `ReferenceChainTrackingTest` to verify
  that a canary search completes faster than a whole-graph BFS
  on a large synthetic heap.

## Open questions

1. **Marker tag vs. klass-id matching**: Pre-tagging is exact
   (instance-level) but requires `SetTag` calls. Klass-id
   matching is cheaper but coarser (all instances of a klass
   are pruned). Which to ship?
   - **Recommendation**: Pre-tag (marker tag). The number of
     `SetTag` calls is ≤5, and exactness matters — if two
     klasses have similar leak patterns, pruning the wrong one
     wastes the search.

2. **Multiple instances of the same leaking klass**:
   `selectLeakCandidates()` returns one representative
   `jweak` per klass. If there are 1000 leaked
   `HashMap$Node` instances, pre-tagging one representative
   only prunes that one instance — the other 999 are still
   expanded. Should we tag *all* live instances of the
   klass? (Requires iterating `GetObjectsWithTags` or
   `IterateThroughHeap` with a klass filter — more expensive.)
   - **Recommendation**: For the initial version, tag the
     representative only. If the representative's chain is
     found, that's the evidence. The other instances
     are the same leak.

3. **Sub-leaked objects** (Phase 1b): When the BFS
   exhausts without finding all candidates, should we
   seed a secondary BFS from found leaked objects
   to discover sub-leaked candidates? This is a
   future enhancement — the initial version abandons
   (same as today, but faster).

4. **Interaction with `isUrgent()`**: When urgent,
   the search runs to completion (no TTL/no-progress
   abandon). With canary pruning, "completion" is
   "all candidates found" — which may happen *faster*
   under urgency (more edges per pass). This is
   the desired behavior: urgent leaks should be
   diagnosed quickly. No change needed — just
   confirming the interaction is correct.

5. **Frontier cap sizing**: With canary pruning,
   the frontier grows slower (leaked subtrees
   are not expanded). The auto-tuned
   `framecap` may be oversized. This is
   harmless (the table just doesn't fill up) and
   can be revisited after measuring real
   frontier occupancy with canary pruning.
