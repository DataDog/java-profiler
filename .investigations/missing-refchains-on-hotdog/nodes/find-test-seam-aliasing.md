---
id: find-test-seam-aliasing
type: finding
status: confirmed-and-fixed
depends_on: [find-leak-tag-pool-implementation, find-klass-id-notation-mismatch]
related: [find-leak-tag-pool-implementation, find-klass-id-notation-mismatch]
tags: [fix, test-seams, klass-id, aliasing, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# Leak-tag redesign broke synthetic-klass-id test seams; fixed by real-id aliasing

## What broke

Since the redesign, every consumer keys candidates by REAL klass ids:
tagLeakInstances() scans the live-heap tracking table's cached_klass_id,
discovered recording resolves admitted objects' classes to the same
space. Synthetic seeded ids (987301/987302/987201/987202...) match
nothing: observed `tagged=0` every poll and
`resolved but no candidate match` for every auto-mark. None of the
pre-existing scenarios (LeakingCacheScenario,
StaticFieldGrowingCollectionScenario, ReferenceChainTrackingTest) had
been run since the redesign - the first full slow-suite run after the
redesign found all of them broken.

## Fix: alias map in the debug seams (livenessTracker.h)

`klassPopulationSetRepresentativeForTest()` is the only seam holding an
actual instance; it now resolves the representative's REAL klass id
(resolveKlassId) and registers a synthetic->real alias
(_test_klass_aliases, max 8, cleared by klassPopulationResetForTest()).
`klassPopulationRecordForTest()` re-routes seeding through the alias. The
seam also RE-KEYS an already-seeded synthetic entry to the real id (ring
history preserved) and creates the entry if absent (set-representative-
first is now the load-bearing order - previously a no-op when absent).

## Scenario-side rules

- Representative BEFORE seeding (alias must exist before seeds land).
- Per-round trend maintenance: a one-shot seeded ramp ages out of
  hysteresis once real fold samples interleave (observed: the byte[]
  candidate dropped right after the first interceptions, stranding the
  correlated discoveries) - StaticFieldGrowingCollectionScenario's
  per-round single-epoch seeding is the pattern.
- Durable fixtures: a stack-held "leak" is gate-suppressed BY DESIGN;
  fixtures needing chains must retain via static fields (gcRootHolder
  became static; the in-process cache test's HashMap chains are depth>=3
  so gate-legal as a local).
