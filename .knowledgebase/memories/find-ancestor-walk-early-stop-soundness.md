---
id: find-ancestor-walk-early-stop-soundness
title: Ancestor-walk early stop needs a per-entry "ancestors recorded" flag
kind: finding
tags: [refchains, leak-fanout, stw]
applies_to: []
source: feedback-1/find-ancestor-walk-early-stop-soundness
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Ancestor-walk early stop needs a per-entry "ancestors recorded" flag

## Reasoning chain
Stopping trackLeakAccumulation's ancestor walk at the first already-present _leak_parent_fanout entry is
unsound: seedLeakAccumulationForNewlyWatchedKlass() inserts direct parents WITHOUT walking their ancestors,
so a present entry does not imply its chain is recorded. Fix: LeakParentFanoutEntry::ancestors_recorded
(true from the walk, false from seed); stop only when set.
Other interactions checked: rotation hygiene erases only dead (absent/ABANDONED) parents
(referenceChainWalk.cpp:769-771) so not re-adding them is harmless; restartSearch() clears the fanout
(referenceChains.cpp:838) and tags are not reused within a search, so stale flags cannot leak across searches.
Caveat: near _hop_cap an earlier walk may have stopped closer to the root.

## Evidence
- referenceChainWalk.cpp seed path emplace LeakParentFanoutEntry{key, 1, false}
- mutation: seed=true -> TrackLeakAccumulationWalksPastSeededAncestor fails

## What this rules out
- "break on any existing ancestor" (the originally proposed #4 hot-path fix) - drops chains above seeded entries.
