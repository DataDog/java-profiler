---
id: ev-postCB-onpod-live-verification
type: evidence
status: confirmed
depends_on: [q-canary-stuck-fix-alternatives]
supersedes: []
related: [find-canary-stuck-restart-wipes-frontier, find-static-field-sweep-never-completes]
tags: [pod-logs, on-pod, post-fix, live-verification, fix-c, fix-b, canary-stuck, frontier-growth]
created: 2026-08-25
updated: 2026-08-25
---

# Fix C+B confirmed live: zero CANARY_STUCK abandons, frontier grows unbroken past 80k; candidates still 0/5

## Deployment observed

User resynced the agent on `prof-analyzer-hotdog-jb-c944876b9-f762h` (same
pod, PID 62384). Confirmed via `strings` on the loaded `.so`
(`/tmp/ddprof_root/pid_62384/scratch/libjavaProfiler-dd-tmp8721684202363682288.so`,
md5 `f92957d3e32ecfbce358f1d854d66182`) that this session's new symbols are
present: `CANARY_PAIN_BUDGET_REFILL_MULTIPLIER` (1 hit),
`canaryStuckPassLimit`/`CanaryStuckRestartCount`/`_canary_stuck_restart_count`
(4 hits combined).

## Three live traces (`/tmp/hotdog_trace{3,4,5}.log`, 40s + 90s + 300s, 122+276 `runPass done` samples total)

```
CANARY_STUCK abandons (reason=3): 0   (was 2 per ~40s pre-fix)
any abandon at all:                0
searchState:                        always 0 (RUNNING)
abandonReason:                      always 0 (NONE)
frontier_cap_hit:                   always 0
frontierSize progression: 25,040 -> 26,626 -> 33,137 -> 38,075 -> 80,382
candidates found: 0/5 throughout all three traces (~430s combined)
```

**C+B confirmed working as designed**: the search that previously died
every ~20s at 12k-16k frontier entries (`ev-postfixEF-onpod-live-verification`)
now runs uninterrupted, growing its frontier past 80k entries with zero
restarts. This is exactly the mechanism the fix targeted.

## Candidate-slot identity: verified stable (initial concern retracted)

Mid-session, misread two different "candidate[N]" log-line families as
evidence of candidate churn:
- `pollWatchedTargets candidate[i] klass_id=...` (referenceChains.cpp:3486)
  - `i` is the position in `LivenessTracker::selectLeakCandidates()`'s
    freshly re-ranked top-N list for that single poll. Reshuffles every
    poll by design (trend/growth score re-ranking) - cosmetic, unrelated to
    search bookkeeping.
- `canary candidate[i] klass_id=... marker_tag=... slot=N` - the `slot=N`
  field is the actual persistent identity, decoded from the JVMTI marker
  tag (`MARKER_TAG_BASE - slot`).

Verified directly: extracting only `(klass_id, slot)` pairs from the 5-min
trace yields exactly 2 distinct pairs for the whole window - `klass_id=10
([B]) -> slot=0` and `klass_id=232 ([Ljava/lang/Class;) -> slot=3` - zero
reassignment. Confirms the code's own guarantee
(referenceChains.cpp:3433-3440: "Slots are never retired or reassigned once
occupied") holds on a live pod. Candidate-identity churn is ruled out as a
contributor to the 0/5 result.

## What this confirms / rules out

- Confirms `find-canary-stuck-restart-wipes-frontier`'s fix (C+B) is
  effective: destructive restart-on-stuck no longer fires, frontier
  accumulates unbroken.
- Rules out candidate-slot reassignment/churn as an explanation for
  continued 0/5 candidate resolution.
- Does NOT explain the continued 0/5 result by itself - see
  `find-static-field-sweep-never-completes` for the new root cause
  surfaced by digging into per-pass diagnostic counters after this trace.
