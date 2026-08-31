---
id: find-sweep-completes-but-bfs-starved
type: finding
status: confirmed
depends_on: [ev-timing-split-callback-vs-jvmti, ev-postfix-static-field-onpod-live-verification]
supersedes: []
related: [find-candidate1-never-tagged, find-static-field-sweep-cursor-fix]
tags: [root-cause, referenceChains, bfs, expandFrontier, backlog, throughput, sweep, NEW-THIS-SESSION]
created: 2026-08-26
updated: 2026-08-26
---

# Sweep completes full lap, but BFS can't reach sweep-admitted entries through 144k backlog

## Observation

With the 200ms deadline (commit `fd18425c6`), the static-field sweep
completes cleanly: `cycle_complete=1` observed, `last_static_field_class_count`
advanced from 33677 → 33752, `truncated=0` on all chunks, real edges
admitted (369-2155/chunk). See `ev-timing-split-callback-vs-jvmti`.

Despite this, candidates are **still 0/1** (only 1 candidate, klass_id=12,
unresolved). The sweep is working; the problem has moved downstream.

## Root cause: two-hop chain architecture

The static-field sweep admits only **one hop** past the class object.
At `referenceChains.cpp:1813`, `batch_tags` is an empty set for the sweep
call, so `heapReferenceCallback()` returns `0` (no descent) for every
referent. A static field value (e.g., an `ArrayList`) gets admitted to
the frontier and pushed to the **back** of `_pending_expand`
(`:1847`), but its elements are NOT visited by the sweep.

`expandFrontier()` is what reaches the leaking object. It picks entries
from the **front** of `_pending_expand` (FIFO deque, `:2654`), puts
their tags into `batch_tags`, calls `FollowReferences` on them — that's
when the `ArrayList`'s elements get visited and the canary match can
fire.

The chain is:
```
Sweep:        class → STATIC_FIELD → ArrayList   [admitted to frontier, pushed to BACK of _pending_expand]
expandFrontier: processes FRONT of _pending_expand (65-87/pass) → ... → eventually ArrayList → elements → leakingObject
```

## The throughput bottleneck

Live data from the pod (200ms deadline build):
- `frontierSize=144k`, `edges_admitted=65-87/pass`
- The sweep admitted the ArrayList to the **back** of `_pending_expand` —
  behind ~144k entries already queued
- At 65-87 edges/pass, it would take ~1700-2200 passes to drain the
  backlog and reach the ArrayList
- `_priority_expand` is drained first (`:2654`), but rotation selects
  entries for priority — the sweep-admitted ArrayList isn't automatically
  prioritized

## Why only 65-87 edges/pass when budget is 3741?

The `runPass done` lines show `effectiveBudget=3741` but only 65-87 edges
admitted per pass. This suggests the per-pass deadline (even at 200ms) is
being consumed by other sub-operations (root enum, rotation) before
`expandFrontier` gets its full share, OR `expandFrontier`'s batch sizing
(`:2680`, capped at `min(budget, _budget)`) limits how many entries are
processed per `FollowReferences` call. Not yet investigated which.

## Possible fixes (not yet proposed to user)

1. **Prioritize sweep-admitted entries** — push them to
   `_priority_expand` instead of `_pending_expand`, so they get expanded
   before the 144k backlog. The `_priority_expand` lane already exists
   for rotation-selected entries; sweep-admitted entries are a natural
   fit (they're the actual leak candidates the sweep found).
2. **Increase BFS throughput** — the 65-87 edges/pass is the real
   bottleneck; increasing the per-pass budget or cadence would help.

## Status

Confirmed: the sweep works, the BFS is starved. Not yet reported to user
in full (conversation was interrupted by checkpoint). Next: report and
propose a fix direction.
