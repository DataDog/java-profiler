---
id: ev-deadline-split-onpod-verification
type: evidence
source: pod logs (kubectl logs)
collected: 2026-08-27
tags: [pod-logs, on-pod, post-fix, live-verification, deadline-split, rolling-resume, NEW-THIS-SESSION]
---

# Deadline split + rolling resume confirmed live on-pod

Pod `prof-analyzer-hotdog-jb-c944876b9-q8vd8`, PID 286999, build `b2acdaee2`.

## Per-phase breakdown (after fix)

```
static_field_phase edges_admitted=322 truncated=1
expand_phase       edges_admitted=946 truncated=1 remaining_budget=3102
rotation_phase     edges_admitted=1138 truncated=1 rotation_budget=2444
runPass done: edges_admitted=2537 truncated=1 frontierSize=121565

static_field_phase edges_admitted=377 truncated=1
expand_phase       edges_admitted=1055 truncated=1 remaining_budget=3047
rotation_phase     edges_admitted=691 truncated=1 rotation_budget=2280
runPass done: edges_admitted=2218 truncated=1 frontierSize=123783

static_field_phase edges_admitted=320 truncated=1
expand_phase       edges_admitted=1606 truncated=1 remaining_budget=3104
rotation_phase     edges_admitted=742 truncated=1 rotation_budget=1786
runPass done: edges_admitted=2766 truncated=1 frontierSize=126549
```

## Before/after comparison

| Phase | Before deadline split | After deadline split |
|-------|----------------------|---------------------|
| static_field_phase | 0-11 edges (ate entire deadline) | 252-377 edges |
| expand_phase | 0-1 edges (no time left) | 793-1606 edges |
| rotation_phase | 0-7 edges | 578-1138 edges |
| **Total** | **0-21 edges/pass** | **1708-2766 edges/pass** |

5 candidates with `heapFloorRising=1`. Frontier growing from 92k → 179k
at ~2000 edges/pass. Canary candidates (klass_id=145, 211, 2292) have
marker tags but `buildCanaryChainEvent -> 0` (not yet reached by BFS).
[B candidate has `tag=0` (representative changed — see
find-representative-changes-lose-canary).
