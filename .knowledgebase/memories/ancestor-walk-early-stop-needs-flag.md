---
id: ancestor-walk-early-stop-needs-flag
title: trackLeakAccumulation's ancestor walk may stop early only at entries flagged ancestors_recorded
kind: finding
tags: [refchains, leak-fanout, stw]
applies_to: [ddprof-lib/src/main/cpp/referenceChainWalk.cpp]
source: feedback-1/find-ancestor-walk-early-stop-soundness
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---


Stopping the ancestor walk at the first parent already present in `_leak_parent_fanout` is
unsound. `seedLeakAccumulationForNewlyWatchedKlass()` inserts direct parents without walking their
ancestors, so a present entry does not imply its chain to the root was recorded.

`LeakParentFanoutEntry::ancestors_recorded` is set by the walk and left false by the seed path; the
walk stops only when it is set. Regression tests: `TrackLeakAccumulationWalksPastSeededAncestor`,
`TrackLeakAccumulationSiblingsShareRecordedAncestors`.

Refuted alternative: "break on any existing ancestor" drops chains above seeded entries.
