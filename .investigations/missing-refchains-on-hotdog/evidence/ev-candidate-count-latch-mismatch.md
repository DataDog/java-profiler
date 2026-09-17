---
id: ev-candidate-count-latch-mismatch
type: evidence
status: confirmed
depends_on: [ev-livelock-pod-logs]
supersedes: []
related: [find-one-shot-pretag-gate, find-canary-search-cannot-terminate]
tags: [pod-logs, candidate-count, latch, pre-tagging]
created: 2026-08-24
updated: 2026-08-24
---

# Live proof that _candidate_count is latched while the selected set has moved on

## Source
`kubectl logs -n profiling-stg prof-analyzer-hotdog-jb-c944876b9-f762h
 -c prof-analyzer --since=40m`

## Raw excerpts

`selectLeakCandidates()` currently offers 5 candidates, every poll:

```
[TEST::INFO] ReferenceChainTracker::pollWatchedTargets candidate_count=5
[TEST::INFO] ReferenceChainTracker::pollWatchedTargets candidate_count=5
[TEST::INFO] ReferenceChainTracker::pollWatchedTargets candidate_count=5
   ... (10 shown, all identical)
```

but the latched `_candidate_count` (the one `shouldRunPass()` prints) is
still 3, from the single pre-tag event:

```
[TEST::INFO] ReferenceChainTracker::shouldRunPass -> true (canary search, 0/3 candidates found)
```

and only one representative in the whole 25-minute window still carries a
marker tag:

```
$ ... | grep -oE "canary candidate\[[0-9]+\] klass_id=[0-9]+ marker_tag=-?[0-9]+" | sort -u
canary candidate[0] klass_id=8 marker_tag=-4611686018427387905
```

The corresponding run-pass line independently reports 5 watched leak
klasses:

```
[TEST::INFO] ReferenceChainTracker::runPassManualWalk rotation_candidates root_kind_tags=0 leak_accumulation_tags=0 stale_expanded_tags=0 watched_leak_klass_count=5 leak_signatures=1 leak_parents=1
```

No `"candidates pre-tagged with marker tags"` line appeared in the
40-minute window — pre-tagging ran once, before the log window, and the
`if (_candidate_count == 0)` gate (`referenceChains.cpp:3375`) has kept it
from running again.
