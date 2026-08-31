---
id: find-shared-deadline-starves-expand
type: finding
status: fixed
depends_on: [find-getobjectswithtags-quadratic-bottleneck]
supersedes: []
related: [find-sweep-completes-but-bfs-starved, q-safepoint-budget-model]
tags: [root-cause, fix, referenceChains, deadline, expandFrontier, sweep, pause-target, NEW-THIS-SESSION]
created: 2026-08-27
updated: 2026-08-27
---

# Shared _pass_deadline_ns starves expandFrontier to 0-1 edges/pass

## Observation

After the adaptive batch_size fix, `GetObjectsWithTags` was bounded at
~25ms and expand admitted 456-971 edges/pass when it got time. But on
the live pod, expand_phase showed `edges_admitted=0 truncated=1` with
`remaining_budget=27500-28527`. The static_field_phase ate the entire
shared `_pass_deadline_ns` (5-50ms), leaving expand with zero wall-clock.

## Root cause

`runPassManualWalk()` sets `_pass_deadline_ns` once at the top, then
calls `admitStaticFieldRoots()`, `expandFrontier()`, and rotation in
sequence — all sharing that one deadline. The sweep's `FollowReferences`
over 512 loaded classes takes ~50ms (the full budget), so expand gets
0ms and truncates immediately.

This is the bug identified in `q-safepoint-budget-model`: one shared
deadline across all sub-operations, instead of each getting its own
per-call cap.

## Fix (COMMITTED b2acdaee2, DEPLOYED, CONFIRMED LIVE ON-POD)

Reset `_pass_deadline_ns` before each sub-operation (expand, rotation).
Each gets its own fresh `_effective_pause_target_ms` budget. The
cumulative rate is still capped by the pass cadence
(effectiveCadenceNs).

### On-pod results

| Phase | Before fix | After fix |
|-------|-----------|-----------|
| static_field_phase | 0-11 edges | 252-377 edges |
| expand_phase | 0-1 edges | 793-1606 edges |
| rotation_phase | 0-7 edges | 578-1138 edges |
| **Total** | **0-21 edges** | **1708-2766 edges** |

~100x improvement over the adaptive batch_size alone, ~1000x over the
original 3-4 edges/pass.
