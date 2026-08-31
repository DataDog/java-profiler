---
id: ev-postfixEF-onpod-live-verification
type: evidence
status: confirmed
depends_on: [find-canary-fixes-e-f, find-abandon-event-queue-fix]
supersedes: []
related: [find-cpu-pain-budget-starves-canary-passes, find-threadloop-presleep-blocks-back-to-back]
tags: [pod-logs, on-pod, post-fix, live-verification, fix-e, fix-f, fix-d, canary-stuck, frontier-wipe]
created: 2026-08-25
updated: 2026-08-25
---

# Fix D/E/F confirmed live; new bottleneck surfaced: CANARY_STUCK abandon/restart every ~20s wipes the frontier before reaching the candidate

## Deployment observed

Pod redeployed again since the last check (without an explicit ask from the
user this turn - discovered by routine "watch the pod" polling): new JVM
PID `39108` (started `2026-08-25T11:38Z`), jar md5
`c5140ef0e4ee45bc7365f337480bed43`, loaded `.so` at
`/tmp/ddprof_root/pid_39108/scratch/libjavaProfiler-dd-tmp18062115394516649584.so`,
md5 `22497e41e381bec86cd549972fd557e0`. Confirmed this build contains this
session's fixes via `strings`: `CANARY_PAIN_BUDGET_REFILL_MULTIPLIER` (1
hit) and `pending_abandoned_events` (2 hits) both present.

## 40-second live trace (`kubectl logs -f --since=1s > /tmp/hotdog_trace2.log`, 382,388 lines)

```
grep -c "runPass done"                          -> 50   (was 0 pre-fix)
grep -c "pollWatchedTargets"                    -> 47025
grep -c "shouldRunPass -> true (canary search"  -> 45
grep -c "enqueuePendingAbandonedEvent"          -> 2
grep -c "REFERENCE_CHAIN_EVENTS_DROPPED"        -> 0
```

**Fix E + F confirmed working**: `runPass` now fires continuously (50 times
in 40s, `effectiveCadenceNs=10000000` = 10ms) instead of the pre-fix zero
over a 45s window (`ev-hotdog-trace-zero-runpass`). The pain-budget
starvation and the threadLoop double-sleep are both resolved.

**Fix D confirmed working**: both abandons in this window were correctly
queued -
```
enqueuePendingAbandonedEvent reason=3 queue_size=2
enqueuePendingAbandonedEvent reason=3 queue_size=3
```
(`reason=3` = `CANARY_STUCK`). No drops, well under
`MAX_PENDING_ABANDONED_EVENTS=16`.

## New bottleneck surfaced (not yet fixed, not yet fully diagnosed)

Despite passes now running continuously, **still 0/5 candidates found**
throughout the entire window (`grep -oE "canary search, [0-9]/[0-9]
candidates found"` -> 45× `0/5`). `candidate[0]`'s `klass_id` stayed stable
at `2` (`[B`, byte array) across the whole window (2545 hits, no churn) -
class-tag stability is not the problem here.

Two full search cycles were captured, both ending in the same way:
```
runPass done: ... searchState=2 abandonReason=3 frontierSize=12776 ...
runPass done: ... searchState=2 abandonReason=3 frontierSize=15699 ...
```
i.e. `CANARY_STUCK` abandon fires once the frontier reaches roughly
12-16k entries, then `restartSearch()` wipes it back to a fresh walk (per
`restartSearch()`'s own documented behavior, `referenceChains.cpp:1054-1056`
- `_frontier->resetForRestart()` + `_next_tag = 1`). Two cycles happened in
this 40s window alone - each search gets roughly ~20s and ~13-16k frontier
entries before being killed and restarted from scratch, with zero carryover.

This matches, and is now live confirmation for, the previously-flagged
(not yet fixed) concern in `find-canary-search-cannot-terminate`/the
`CANARY_NO_PROGRESS_PASS_LIMIT` design comment
(`referenceChains.h:1988-1999`): the canary-specific stuck detector fires
on zero *candidate* progress specifically, independent of how much the
*general* frontier is still healthily growing elsewhere. If `candidate[0]`
(a `byte[]`) sits behind a long, indirect reference chain that takes more
than `CANARY_NO_PROGRESS_PASS_LIMIT=30` passes worth of BFS expansion to
reach, this search design can never reach it: every restart re-walks from
scratch, so cumulative BFS "reach" never exceeds what one ~20s cycle can
cover.

## What this confirms / rules out

- Confirms `find-cpu-pain-budget-starves-canary-passes` and
  `find-threadloop-presleep-blocks-back-to-back` are genuinely fixed - not
  just gtest-clean, but observably changing pod behavior (0 -> 50 runPass
  in a comparable window).
- Confirms `find-abandon-event-queue-fix` (Fix D) works end-to-end on a
  live pod, not just in gtest.
- Rules out candidate churn (LivenessTracker offering a different
  candidate list each restart) as a contributor here - `klass_id=2` was
  stable across both cycles.
- Does NOT yet confirm the frontier-wipe-on-restart / `CANARY_NO_PROGRESS_PASS_LIMIT`
  hypothesis as proven root cause of the *new* zero-resolution pattern -
  it is the most consistent explanation given this evidence, but has not
  been isolated from alternatives (e.g. the candidate genuinely being
  unreachable from any sampled root in this heap at all, independent of
  pass count).

## Not yet done

- No fix proposed or requested for this new bottleneck - user only asked
  to "continue watching"; this is a fresh observation to report, not an
  ask to act on.
