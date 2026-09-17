---
id: ev-livelock-pod-logs
type: evidence
status: confirmed
depends_on: [ev-post-resync-deployment-verified]
supersedes: []
related: [find-marker-tag-slot-index-mismatch, find-canary-search-cannot-terminate, hyp-warmup-transience]
tags: [pod-logs, livelock, canary, buildCanaryChainEvent, TEST_LOG]
created: 2026-08-24
updated: 2026-08-24
---

# Phase 2: pod logs show a stable livelock, not warm-up

## Source
`kubectl logs -n profiling-stg prof-analyzer-hotdog-jb-c944876b9-f762h
 -c prof-analyzer --since=25m`, filtered on reference-chain / liveness
TEST_LOG lines. JVM started 14:29; logs read ~14:55.

## The repeating pair (dozens of identical occurrences)

```
[TEST::INFO] ReferenceChainTracker::pollWatchedTargets canary candidate[0] klass_id=8 marker_tag=-4611686018427387905 needRefresh=1
[TEST::INFO] ReferenceChainTracker::pollWatchedTargets canary buildCanaryChainEvent(candidate=0) -> 0
[TEST::INFO] ReferenceChainTracker::shouldRunPass -> true (canary search, 0/3 candidates found)
```

`grep -oE "canary candidate\[[0-9]+\] klass_id=[0-9]+ marker_tag=-?[0-9]+" | sort -u`
over the whole 25-minute window returned exactly ONE distinct line:

```
canary candidate[0] klass_id=8 marker_tag=-4611686018427387905
```

The session summary records `143 identical iterations over 25 minutes`
with `0/3 candidates found` never advancing (derived from the
`grep -oE "canary search, [0-9]+/[0-9]+ candidates found" | sort | uniq -c`
count; the raw uniq -c output line was truncated in the captured transcript).

There were **no** `chain-found`, `writeReferenceChain`,
`drainPendingChainEvents` or `ERROR.*chain` lines at all.

## The search itself is healthy and running

```
[TEST::INFO] ReferenceChainTracker::threadLoop iteration=61 shouldRunPass=1 searchState=0 passesRun=60 effectiveCadenceNs=1000000000 effectiveBudget=3741 gcFinishEpoch=27 lastPassGcFinishEpoch=27 nowMinusLastPassNs=3000773439
[TEST::INFO] ReferenceChainTracker::runPass starting JVMTI walk: search_started=1 frontierSize=10027
[TEST::INFO] ReferenceChainTracker::runPassManualWalk static_field_phase edges_admitted=0 truncated=1 frontier_cap_hit=0 last_resolved_class_count=33501 last_static_field_class_count=-1
[TEST::INFO] ReferenceChainTracker::runPassManualWalk expand_phase edges_admitted=1 truncated=1 frontier_cap_hit=0 remaining_budget=3453
[TEST::INFO] ReferenceChainTracker::runPassManualWalk rotation_candidates root_kind_tags=0 leak_accumulation_tags=0 stale_expanded_tags=0 watched_leak_klass_count=5 leak_signatures=1 leak_parents=1
[TEST::INFO] ReferenceChainTracker::runPass done: err=0 edges_admitted=184 truncated=1 frontier_cap_hit=0 searchState=0 abandonReason=0 frontierSize=10211 effectiveBudget=3741 effectiveCadenceNs=1000000000
```

## Leak signal is real and past hysteresis (rules out warm-up)

```
[TEST::INFO] LivenessTracker::heapFloorRising FLOOR_RISING recent_mean=1138212368 earliest_mean=286975797 recent_min=773009712 earliest_min=223877728 floor_bar=2238777 floor_rising=1
[TEST::INFO] LivenessTracker::selectLeakCandidates scanning 118 klass_population entries
[TEST::INFO] LivenessTracker::selectLeakCandidates entry[0] klass_id=160 ring_fill=20 has_trend=1 slope=19.000000 consecutive_positive=11 required=3 representative=0x7da38c0956e1
[TEST::INFO] LivenessTracker::selectLeakCandidates entry[1] klass_id=8   ring_fill=20 has_trend=1 slope=20.000000 consecutive_positive=11 required=3 representative=0x7da38c0956f9
[TEST::INFO] LivenessTracker::selectLeakCandidates entry[4] klass_id=44  ring_fill=12 has_trend=1 slope=17.384615 consecutive_positive=3  required=3 representative=0x7da2f00886c1
```

`consecutive_positive=11 >= required=3` for the very klass (`klass_id=8`)
that the canary poll is stuck on.
