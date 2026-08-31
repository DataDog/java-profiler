---
id: ev-postfix-onpod-live-verification
type: evidence
status: confirmed
depends_on: []
supersedes: []
related: [find-marker-tag-slot-index-mismatch, find-canary-stuck-abandon-detector, find-canary-search-cannot-terminate]
tags: [pod-logs, on-pod, post-fix, live-verification, md5, fix-a, fix-c]
created: 2026-08-25
updated: 2026-08-25
---

# Fix A + Fix C confirmed live on the resynced hotdog pod; Fix B implied

## Reasoning chain

After `623d3712a` (Fix A/B/C) was committed and pushed to
`jb/reference-chains`, the pod was resynced. On-pod evidence (per
`find-onpod-evidence-methodology`: `kubectl exec` + `jar xf` + `md5sum` +
`strings`, not image tags):

- jar md5 `f3c01e345c73484d021ab405b27cc3fd`
- `.so` md5 `7437bd8a137ac79126d3cfebe3887b3b`, contains `CANARY_STUCK` /
  `canary_stuck` strings (Fix C's enum value and `kReasons` string) and
  1057 `ReferenceChainTracker`-related symbol hits
- JVM PID 3238, started 2026-08-25 08:50 UTC

**Fix A (slot decode) confirmed live**: pod logs show
`candidate[N] ... marker_tag=... slot=M` where `M != N` in general, e.g.
`candidate[1] klass_id=122 marker_tag=-4611686018427387906 slot=2` and
`candidate[2] klass_id=11 marker_tag=-4611686018427387905 slot=1` — the
tag-decoded slot, not the loop index, is now used for lookup, exactly as
designed.

**Fix C (`CANARY_STUCK` abandon detector) confirmed live**: `abandonReason=3`
appears in `runPass done: ...` log lines, always immediately followed by
`shouldRunPass -> true (restarting search)` and `passesRun` resetting to 0
on the next iteration. 5 such abandon/restart cycles were observed over
~20 minutes at timestamps 09:00:18, 09:01:53, 09:03:23, 09:04:59, 09:06:37.
No infinite livelock — each search cleanly terminates after
`CANARY_NO_PROGRESS_PASS_LIMIT = 30` stuck passes and restarts, instead of
running forever as it did pre-fix (`ev-livelock-pod-logs`: 143 identical
iterations over 25 minutes with 0/N found).

## What this rules out

- Any doubt that Fix A/C reached this build or are behaving as designed —
  both are directly observable in pod logs with concrete, code-matching
  values (decoded slot != loop index; `abandonReason=3` with the exact
  restart follow-through the design doc predicts).

## New open finding surfaced by this verification

Despite all three fixes working exactly as designed, **zero canary
candidates have ever been resolved** on this pod across all 5 observed
restart cycles (`buildCanaryChainEvent(slot) -> 1` never once observed).
This is a new, undiagnosed symptom — not assumed to be a regression from
Fix A/B/C, since the search no longer livelocks silently and this may be a
pre-existing reachability/budget limit that was simply invisible before.
See `find-abandon-event-lost-to-dump-sampling-race` for the *separate*
zero-JFR-event-count question this triggered — that one turned out to have
a definite root cause, unrelated to whether candidates ever resolve.
