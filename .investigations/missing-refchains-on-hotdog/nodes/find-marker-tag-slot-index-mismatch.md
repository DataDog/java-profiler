---
id: find-marker-tag-slot-index-mismatch
type: finding
status: confirmed
depends_on: [ev-post-resync-deployment-verified, ev-jafar-zero-refchain-events, ev-livelock-pod-logs, ev-marker-tag-arithmetic, ev-source-poll-vs-callback]
supersedes: []
related: [find-one-shot-pretag-gate, find-canary-search-cannot-terminate, find-canary-stuck-abandon-detector, hyp-warmup-transience, hyp-regression-of-five-fixes, q-implement-two-fixes, ev-fixes-compile-and-gtest-pass]
tags: [root-cause, fixed, referenceChains, canary, marker-tag, off-by-slot]
created: 2026-08-24
updated: 2026-08-24
---

# ROOT CAUSE (FIXED): pollWatchedTargets() indexes candidate arrays by loop position instead of the tag-decoded slot

## Reasoning chain

After the resync the feature is provably deployed and enabled
(1097 symbol hits, `-Ddd.profiling.experimental.ddprof.referencechains.enabled=true`,
both event types registered in the JFR) yet jafar reports **count 0** for
`datadog.ReferenceChain` and `datadog.ReferenceChainAbandoned`.

The pod logs show why, and the two lines are *internally inconsistent*:

```
canary candidate[0] klass_id=8 marker_tag=-4611686018427387905 needRefresh=1
buildCanaryChainEvent(candidate=0) -> 0
```

- `MARKER_TAG_BASE = -(1LL << 62) = -4611686018427387904`
  (`ddprof-lib/src/main/cpp/referenceChains.h:1924`).
- The observed tag is `MARKER_TAG_BASE - 1`, i.e. candidate slot **1**.
- But the log — and the call — use `i`, the position in the *current*
  `candidates[]` array returned by `selectLeakCandidates()`, which is 0.

The write side is correct: `heapReferenceCallback()` decodes the slot out
of the tag (`referenceChains.cpp:1510`,
`int candidate_idx = (int)(MARKER_TAG_BASE - *tag_ptr);`) and writes
`_candidate_parent_tags` / `_candidate_frontier_tags` /
`_candidate_referrer_klasses` / `_candidate_depths` / `_candidate_found_bits`
at that decoded index (`:1525-1529`).

The read side is not: `pollWatchedTargets()` calls
`buildCanaryChainEvent(i, &event)` (`referenceChains.cpp:3478`) and later
`cacheResolvedChain(..., _candidate_frontier_tags[i], ...)`
(`referenceChains.cpp:3485`).

Consequence chain:

1. Slot 0 was never written by the pruner, so both `parent_tag` and
   `frontier_tag` read as 0.
2. `buildCanaryChainEvent()` falls through to
   `return false; // never pruned (candidate not reached)`
   (`referenceChains.h:2127`).
3. `built == false`, so `cacheResolvedChain()` is never invoked
   (`referenceChains.cpp:3482-3487`).
4. Hence no `_resolved_chains` entry for `klass_id`, hence
   `need_refresh` (`referenceChains.cpp:3469-3471`) is **1 forever** —
   which is a symptom, not an independent fault.
5. No chain is ever cached, so nothing is ever queued for the JFR writer:
   zero events.

Corroborating: `shouldRunPass -> true (canary search, 0/3 candidates found)`
means `_candidate_found_bits == 0`, i.e. **no** slot — not even slot 1 —
was ever written by the pruning code. So the walk hadn't reached the
representative either; but even if it had, the reader would still have
looked at the wrong slot.

## Evidence
- `evidence/ev-marker-tag-arithmetic.md` — the arithmetic, run in-session
- `evidence/ev-source-poll-vs-callback.md` — verified source excerpts
- `evidence/ev-livelock-pod-logs.md` — 25 min of identical iterations
- `evidence/ev-jafar-zero-refchain-events.md` — the observable outcome
- `ddprof-lib/src/main/cpp/referenceChains.h:1924`, `:2093-2141` (`:2127`)
- `ddprof-lib/src/main/cpp/referenceChains.cpp:1508-1529`, `:3456-3490`
  (`:3478`, `:3485`)

## What this rules out
- Warm-up / not-enough-time — see `hyp-warmup-transience` (REFUTED:
  `consecutive_positive=11 >= required=3`, 143 identical iterations over
  25 min, `0/3` never moving).
- Regression of the five previously-fixed causes — see
  `hyp-regression-of-five-fixes` (REFUTED: none of them touch
  slot↔index correspondence).
- Frontier/budget starvation: `runPass done: err=0 edges_admitted=184 …
  frontierSize=10211 effectiveBudget=3741` — the walk is running fine.
- A JFR-writer or upload problem: the types ARE registered in the
  uploaded recording; the events simply are never produced.

## Fix implemented (this session, uncommitted on `jb/reference-chains`)

Applied in `pollWatchedTargets()` (`referenceChains.cpp`, canary branch
under `if (tag <= MARKER_TAG_BASE)`): decode `candidate_slot = (int)(MARKER_TAG_BASE - tag)`,
bounds-check it against `_candidate_count` (out-of-range slot -> `TEST_LOG`
+ `continue`, matches the existing OOB-safe behavior of
`buildCanaryChainEvent()`), and use `candidate_slot` (not the loop index
`i`) for both `buildCanaryChainEvent(candidate_slot, &event)` and
`_candidate_frontier_tags[candidate_slot]`. This is the "Fix A" design from
`q-implement-two-fixes`, implemented as proposed with an added explicit
out-of-range guard.

Verified: `./gradlew :ddprof-lib:compileDebug -Pskip-gtest` succeeds;
`gtestDebug_referenceChains_ut` (89 tests) and
`gtestDebug_referenceChainJfrRoundtrip_ut` (1 test) both pass — see
`ev-fixes-compile-and-gtest-pass`.

Implemented together with `find-one-shot-pretag-gate`'s fix (Fix B) and a
new `find-canary-stuck-abandon-detector` (Fix C), because Fix A alone does
not stop the search livelocking once the candidate set churns (see that
finding for why they had to land together).

Not yet done: on-pod re-verification (the pod's `.so` still has the
pre-fix binary); a multi-candidate regression test, per the sub-question in
`q-implement-two-fixes`, has not been added.
