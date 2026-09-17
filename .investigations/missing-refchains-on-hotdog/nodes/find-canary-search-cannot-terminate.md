---
id: find-canary-search-cannot-terminate
type: finding
status: confirmed
depends_on: [ev-source-poll-vs-callback, ev-livelock-pod-logs]
supersedes: []
related: [find-marker-tag-slot-index-mismatch, find-one-shot-pretag-gate, find-canary-stuck-abandon-detector, ev-fixes-compile-and-gtest-pass]
tags: [livelock, search-state, completion-gating, urgent, partially-fixed]
created: 2026-08-24
updated: 2026-08-24
---

# Third element (PARTIALLY ADDRESSED): with 0/N candidates found the canary search could neither complete nor abandon

## Reasoning chain

Once `find-marker-tag-slot-index-mismatch` pins `_candidate_found_bits` at
0, all three exits from the canary search are closed:

1. **Completion** requires
   `popcount(_candidate_found_bits) == _candidate_count`
   (`referenceChains.cpp:3101-3103`). At 0/3 that is unreachable.
2. **TTL / no-progress abandon** is gated on `!isUrgent()`
   (`referenceChains.cpp:3090-3091`), and the search on this pod IS urgent
   (heap floor rising, `FLOOR_RISING … floor_rising=1`). So the abandon
   branch is suppressed by design — the very safety valve that would have
   reset state is disabled exactly when the leak signal is strongest.
3. **Cadence back-off** does not apply: `shouldRunPass()` short-circuits to
   `true` for as long as any candidate bit is unset
   (`referenceChains.cpp:914-922`), so a pass runs on every wake.

Net effect is a livelock: passes keep running (`passesRun=60`,
`iteration=61` at read time), the frontier keeps growing
(`frontierSize 10027 → 10211`), STW pause budget keeps being spent, and
nothing is ever emitted. 143 identical iterations were observed over 25
minutes.

This is also why `datadog.ReferenceChainAbandoned` is 0 alongside
`datadog.ReferenceChain` — the search never abandons either.

## Evidence
- `evidence/ev-source-poll-vs-callback.md` (`:3090-3108`, `:914-922`)
- `evidence/ev-livelock-pod-logs.md`

## What this rules out
- Any expectation that leaving the pod running longer would produce
  events. It is a stable fixed point, not a slow convergence.
- The theory that a bad candidate would be aged out by the TTL/abandon
  path — that path is explicitly suppressed while urgent.

## Status update (this session)

Fixing `find-marker-tag-slot-index-mismatch` (Fix A) and
`find-one-shot-pretag-gate` (Fix B) removes the *original* trigger (a
candidate that can never be marked found because of the index bug, or
because it was never admitted). But Fix B's never-retire design means a
different, narrower version of this same livelock is still reachable: a
candidate that legitimately drops out of `selectLeakCandidates()`'s later
polls (e.g. it stopped growing) stays latched in its slot and can never be
found, so `popcount(found_bits) == candidate_count` still can't be
satisfied for that search. Point 2 (TTL/abandon suppressed while urgent)
is unchanged and is exactly the case that matters most, since urgency is
what makes the search run in the first place.

`find-canary-stuck-abandon-detector` (Fix C, new node) closes this
remaining gap with a completion-agnostic stuck detector that is
deliberately NOT suppressed by `isUrgent()`. This finding is not fully
superseded — its point 3 (`shouldRunPass()` always true while any bit is
unset) and the general "no exit while urgent" shape of the problem are
still the reason Fix C exists — but the specific livelock instance
observed on the hotdog pod is expected to be fixed by A+B+C together.
