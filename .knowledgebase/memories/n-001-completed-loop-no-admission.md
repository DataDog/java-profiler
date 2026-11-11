---
id: n-001-completed-loop-no-admission
title: n-001: Failing child loops COMPLETED/restart; holders never admitted
kind: finding
tags: [reference-chains, admission, restart]
applies_to: []
source: frontier-wait-untagged/n-001-completed-loop-no-admission
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


# n-001: Failing child loops COMPLETED/restart; holders never admitted

- status: confirmed
- evidence: build/logs/20261014-170327-_ddprof-test_testSlowDebug.log (child section, DD_PROFILING_REFERENCE_CHAINS_DEBUG=2)

## Finding

In the failing run every pass ends `searchState=1` (SearchState::COMPLETED,
referenceChainFrontier.h:33) with `abandonReason=0 truncated=0`. The COMPLETED
branch is `!has_pending_frontier && _watched_leak_klass_count == 0`
(referenceChainTraversal.cpp:1110): the scenario deliberately wires no
representative, so `_watched_leak_klass_count==0`, and the pass was not
truncated. `canAffordNewSearch` then cools down the safepoint pain budget
(balance 1.5–83ms, refill 0.04) and `restartSearch()` runs — the identical
walk repeats (edges_admitted=19058 twice). Passes never progress.

LEAK_BUFFER's holders (SynchronizedList, backing ArrayList, elementData) are
never tagged: frontier states read -1 (FRONTIER_STATE_NONE) for the whole 45s
wait window (StaticFieldGrowingCollectionScenario.java:205-214).

## Supporting facts

- `static_sweep_gate resolved=1246 swept=-1 cursor=0/512/1024` cycling: the
  sweep cursor laps all classes every pass, but `swept`
  (`_last_static_field_class_count`) never latches because `restartSearch()`
  (referenceChains.cpp:921-922) resets `_last_resolved_class_count=0` and
  `_last_static_field_class_count=-1` on EVERY restart.
- The scenario class IS resolved: `resolveClassMap id=9
  name=.../StaticFieldGrowingCollectionScenario`, `id=35
  java/util/Collections$SynchronizedList`.
- `walkStaticFieldAnchors selected=48 walked=48 edges_admitted=0`.
- The sweep segment of the log (static_sweep_gate → expand_phase) contains
  zero level-2 lines: the sweep's FollowReferences callback emitted no
  diagnostics — what it does with the scenario class is currently invisible.

## Open question

Why does the sweep's FollowReferences over the scenario class's chunk never
admit the SynchronizedList as a frontier entry?
