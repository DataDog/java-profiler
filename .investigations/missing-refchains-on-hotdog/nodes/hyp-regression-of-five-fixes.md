---
id: hyp-regression-of-five-fixes
type: hypothesis
status: refuted
depends_on: [ev-source-poll-vs-callback, ev-marker-tag-arithmetic]
supersedes: []
related: [find-marker-tag-slot-index-mismatch]
tags: [regression-check, sibling-investigation, refuted]
created: 2026-08-24
updated: 2026-08-24
---

# Hypothesis (REFUTED): this is a regression of one of the five fixes from the `reference-chains` investigation

## Reasoning chain

The outer symptom — `buildCanaryChainEvent(candidate=0) -> 0` repeating
forever with `needRefresh=1` — is *literally the same log line* recorded in
the sibling investigation `.investigations/reference-chains/`
(`ev-integration-test-still-zero`), which was declared resolved by five
fixes. So the obvious first guess was a regression.

It is not. The five fixes, all confirmed and committed on this branch
(`209336ea1`, `8114019c2`), are:

- `find-classtag-stability-fix` — shared `ClassTagAllocator` / stable `class_tag`
- `find-test-seam-classtag-mint` — `mintStableClassTagIfNeeded()` in the
  `klassPopulationSetRepresentativeForTest()` seam
- `find-urgent-signal-latch` — hysteresis on `isUrgent()`/`hasLeakSignal()`
- `find-runpass-completion-gating` — gate `COMPLETED` on
  `_watched_leak_klass_count == 0`
- `find-livenesstracker-generation-sync` — sync
  `LivenessTracker::_last_class_map_generation` in `initialize()`

None of them touches the correspondence between a marker tag's encoded
slot and the array index used to read it back, nor the one-shot
`if (_candidate_count == 0)` pre-tagging gate. Those two are untouched
original code.

Shape difference from the sibling evidence: the local integration test
that drove those five fixes exercised a **single** candidate, so index 0
was trivially self-consistent with slot 0 and the defect was invisible.
Production selected multiple candidates (3 latched, 5 currently offered),
which is the first time slot != index could occur. That multi-candidate
path was never exercised by a test.

## Evidence
- `evidence/ev-source-poll-vs-callback.md`
- `evidence/ev-marker-tag-arithmetic.md`
- `.investigations/reference-chains/STATE.md`, `INDEX.md`,
  `evidence/ev-integration-test-still-zero.md`

## What this rules out
- Reverting or re-auditing the five committed fixes as a remedy.
- Re-deriving any of the five root causes — see the sibling investigation,
  which is `status: done`.

## Caveat on one sub-claim
The "single candidate in the local test" reading is the session's
inference from `ev-integration-test-still-zero` (which logs
`candidate[0]`, `klass_id=987302`, `class_name=[B` and a consistently
assigned `marker_tag`); that evidence file does not record the
`candidate_count` value or the numeric marker tag, so slot-0/index-0
self-consistency there is inferred, not directly measured. Worth
re-checking against the raw test log
(`build/logs/20260824-100906-_ddprof-test_testSlowDebug.log`) before
relying on it.
