---
id: find-one-shot-pretag-gate
type: finding
status: confirmed
depends_on: [ev-candidate-count-latch-mismatch, ev-source-poll-vs-callback]
supersedes: []
related: [find-marker-tag-slot-index-mismatch, find-canary-search-cannot-terminate, find-canary-stuck-abandon-detector, q-implement-two-fixes, ev-fixes-compile-and-gtest-pass]
tags: [self-heal, pre-tagging, candidate-count, latch, fixed]
created: 2026-08-24
updated: 2026-08-24
---

# Second defect (FIXED): candidate pre-tagging was one-shot, so the tag→slot map desynchronised from selectLeakCandidates()

## Reasoning chain

Even if the slot/index mismatch were a transient, the design cannot
recover from it, because marker tags are assigned exactly once:

```cpp
if (_candidate_count == 0) {                 // referenceChains.cpp:3375
  _candidate_count = candidate_count;
  _candidate_found_bits = 0;
  for (int i = 0; i < candidate_count; i++) {
    jlong tag = MARKER_TAG_BASE - i;
    _candidate_tags[i] = tag;
    … jvmti->SetTag(obj, tag); …
  }
}
```

`_candidate_count` is only reset when `runPass()` leaves `RUNNING`. So
once latched, later `selectLeakCandidates()` orderings and counts are
never reflected in the tags — the loop index `i` in `pollWatchedTargets()`
refers to the *current* selection while the tags encode the *original*
one. The two only agree by accident.

Live proof of the divergence on the hotdog pod:

- `pollWatchedTargets candidate_count=5` every poll (current selection),
- `shouldRunPass … 0/3 candidates found` (latched `_candidate_count == 3`),
- exactly one representative still carrying a marker tag,
- `runPassManualWalk … watched_leak_klass_count=5`,
- no `"candidates pre-tagged with marker tags"` line in a 40-minute window.

So the candidate set legitimately churned (grew 3 → 5 as more klasses
passed the hysteresis threshold) and the tagging state never followed.

## Evidence
- `evidence/ev-candidate-count-latch-mismatch.md`
- `evidence/ev-source-poll-vs-callback.md`
- `ddprof-lib/src/main/cpp/referenceChains.cpp:3375-3397`

## What this rules out
- "It will fix itself on the next search generation" — it will not, because
  the search can never leave `RUNNING`
  (`find-canary-search-cannot-terminate`), so `_candidate_count` never
  resets and the gate never reopens.
- Fixing only the slot decode being sufficient: with a shrinking/churning
  candidate set, dead slots stay latched and new candidates never get
  tagged at all, so they can never be found.

## Fix implemented (this session, uncommitted on `jb/reference-chains`)

Replaced the one-shot `if (_candidate_count == 0) { ... }` block with a
growing-admission loop that runs on **every** poll where `candidate_count > 0`:
for each candidate in the current `selectLeakCandidates()` result, skip it
if a slot already tracks its `klass_id` (new `_candidate_klass_ids[]`
array added to `referenceChains.h`, one entry per slot); otherwise, if a
free slot exists (`_candidate_count < MAX_LEAK_CANDIDATES_FROM_LT`), admit
it into the next slot, tag its representative object, and grow
`_candidate_count`. Slots that fill up when `MAX_LEAK_CANDIDATES_FROM_LT`
is reached are logged and left untracked for that search (no eviction).

Design decision, made explicitly with the user via a clarifying question:
**slots are never retired/reused for the lifetime of a search** — a
candidate that later drops out of `selectLeakCandidates()`'s result stays
tagged and occupies its slot until the search resets. Rejected alternative:
retiring/reusing slots was ruled out as added complexity/risk (re-deriving
`_candidate_found_bits` semantics and untagging live objects mid-walk) that
the user judged not worth it for a bug of this shape. This is why
`find-canary-stuck-abandon-detector` (Fix C) had to be added alongside —
never-retire means completion (`popcount(found_bits) == candidate_count`)
can be permanently blocked by one never-found candidate, and Fix B alone
does not close that gap.

`Counters::increment(REFERENCE_CHAIN_CANDIDATE_COUNT, 1)` is called once
per newly-admitted candidate (delta-based counter, confirmed via
`counters.h`), replacing the old one-shot absolute-count call.

All three lifecycle reset sites (`start()`, `resetSearchStateForTest()`,
and `runPass()`'s terminal-state cleanup) reset `_candidate_count`,
`_candidate_found_bits`, and (per Fix C) the new progress-tracking fields
together, so a fresh search always starts from an empty admission table.

Verified: compiles cleanly and both `referenceChains` gtest suites pass
(89 + 1 tests) — see `ev-fixes-compile-and-gtest-pass`.
