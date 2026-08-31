---
id: find-canary-stuck-abandon-detector
type: finding
status: confirmed
depends_on: [find-canary-search-cannot-terminate, find-one-shot-pretag-gate]
supersedes: []
related: [find-marker-tag-slot-index-mismatch, q-implement-two-fixes, ev-fixes-compile-and-gtest-pass]
tags: [fix, livelock, search-state, urgent-abandon, canary, new-this-session]
created: 2026-08-24
updated: 2026-08-24
---

# Fix C (implemented, this session): canary-specific stuck/abandon detector not suppressed by isUrgent()

## Reasoning chain

`find-canary-search-cannot-terminate` identified that the ordinary
TTL/no-progress abandon path is gated on `!isUrgent()`
(`referenceChains.cpp:3090-3091`), so a search that is both urgent
(heap floor rising, near projected OOM) and livelocked has **no exit at
all** — it keeps running every scheduling cycle at urgency-boosted
(higher-budget, higher-cadence) settings, because nothing in the urgent
path ever asks "am I actually converging."

Fix B (`find-one-shot-pretag-gate`) makes `_candidate_count` growing-only
and never retires a slot once a candidate is admitted. That is deliberate
(never-retire was the user-approved design), but it means a single
candidate that stops appearing in `selectLeakCandidates()`'s later results
(and so is never walked-to and never marked found) can permanently block
completion (`popcount(_candidate_found_bits) == _candidate_count`) for the
rest of that search's life — even after Fix A/B, not just before them.

This finding's fix is a completion-agnostic stuck detector, independent of
`isUrgent()`, so a livelocked urgent search can still terminate and free
its STW/frontier budget instead of running forever.

## Design

Two counters added to `ReferenceChainTracker` (`referenceChains.h`):

- `int _passes_since_last_candidate_progress` — passes since candidate
  discovery last advanced.
- `int _last_candidate_progress_mark` — high-water mark of a monotonic
  "progress" quantity.
- `static constexpr int CANARY_NO_PROGRESS_PASS_LIMIT = 30` (same value as
  the existing `NO_PROGRESS_PASS_LIMIT`, but tracked separately and
  independently gated).
- `SearchAbandonReason::CANARY_STUCK = 3` added to the existing
  `NONE/FRONTIER_CAP/TTL` enum (`referenceChains.h`), kept in lockstep with
  `flightRecorder.cpp`'s `kReasons` string table
  (`{"none","frontier_cap","ttl","canary_stuck"}`) and its bounds check
  (`< 3` -> `< 4`) — the existing code comment explicitly warns these two
  must match index-for-index for JFR serialization.

Progress mark, computed once per pass in `runPass()`:

```cpp
int candidate_progress_mark =
    _candidate_count + (int)__builtin_popcountll(_candidate_found_bits);
if (candidate_progress_mark > _last_candidate_progress_mark) {
  _last_candidate_progress_mark = candidate_progress_mark;
  _passes_since_last_candidate_progress = 0;
} else {
  _passes_since_last_candidate_progress++;
}
```

This mark is provably monotonic **because** of Fix B: `_candidate_count`
only grows (never-retire) and `_candidate_found_bits` bits are only ever
set, never cleared, while `RUNNING`. That guarantee did not hold before
Fix B (a retire/reuse design would have made the mark oscillate), which is
why this detector was designed and landed together with Fix B rather than
independently.

Abandon branch added to `runPass()`'s completion/abandon `if/else if`
chain, after the existing branches:

```cpp
} else if (_candidate_count > 0 &&
           _passes_since_last_candidate_progress >=
               CANARY_NO_PROGRESS_PASS_LIMIT) {
  store(_abandon_reason, (u8)SearchAbandonReason::CANARY_STUCK);
  storeRelease(_search_state, (u8)SearchState::ABANDONED);
}
```

Deliberately has no `!isUrgent()` guard — this is the whole point: it must
fire *especially* when urgent, since that's the only condition under which
the ordinary TTL path is disabled.

Reset alongside `_candidate_count`/`_candidate_found_bits` at all three
existing lifecycle reset sites: `start()`, `resetSearchStateForTest()`, and
`runPass()`'s terminal-state tag-release cleanup block.

## Why this was scoped in, not deferred

The user's own framing, quoted back mid-session: "a search that's both
urgent and livelocked has no exit at all... since nothing in the urgent
path checks 'am I actually converging.'" I proposed this as a fix; the
user's instruction was explicit: "implement alongside; seems like a
'minor' change." Scope was user-approved, not self-initiated scope creep.

## Evidence
- `ddprof-lib/src/main/cpp/referenceChains.cpp` — `runPass()` diff (Fix C)
- `ddprof-lib/src/main/cpp/referenceChains.h` — new fields/constants/enum
  value
- `ddprof-lib/src/main/cpp/flightRecorder.cpp` — `kReasons` table update
- `ev-fixes-compile-and-gtest-pass` — build + gtest verification

## What this does not cover
- Does not fix `find-canary-search-cannot-terminate` point 3
  (`shouldRunPass()` always true while any candidate bit is unset) as a
  cadence/backoff concern — it only guarantees the search eventually
  reaches `ABANDONED` and gets a fresh restart, not that intermediate
  passes back off before that point.
- No on-pod re-verification yet; no multi-candidate regression test added
  (open sub-question carried over from `q-implement-two-fixes`).
