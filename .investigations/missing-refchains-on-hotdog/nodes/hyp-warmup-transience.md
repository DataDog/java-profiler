---
id: hyp-warmup-transience
type: hypothesis
status: refuted
depends_on: [ev-livelock-pod-logs, ev-jafar-zero-refchain-events]
supersedes: []
related: [find-marker-tag-slot-index-mismatch, find-canary-search-cannot-terminate]
tags: [warm-up, transient, refuted]
created: 2026-08-24
updated: 2026-08-24
---

# Hypothesis (REFUTED): zero events is just warm-up — the paced BFS hasn't had time yet

## Reasoning chain

The first reaction on seeing `datadog.ReferenceChain: count 0` in a
recording from a JVM that had only been up ~20 minutes was that this is
expected: the search needs a leak signal to accumulate over several GC
epochs, then runs a deliberately slow, pause-budgeted BFS.

Refuted by three independent readings of the pod logs:

1. The leak-detection hysteresis had long since fired for the very klass
   under investigation: `klass_id=8 … consecutive_positive=11 required=3`
   (and `klass_id=160` likewise at 11). `heapFloorRising … floor_rising=1`.
2. The search was not "still working" — it was repeating a bit-identical
   iteration. 143 identical iterations over 25 minutes, with
   `0/3 candidates found` never moving, and exactly one distinct
   `canary candidate[…]` log line in the whole window.
3. The state machine has no exit at 0/N
   (`find-canary-search-cannot-terminate`), so more time provably cannot
   help.

## Evidence
- `evidence/ev-livelock-pod-logs.md`
- `evidence/ev-jafar-zero-refchain-events.md`

## What this rules out
- "Wait longer and re-check" as a next step. Do not spend another
  observation window on this pod expecting events without a code fix.
