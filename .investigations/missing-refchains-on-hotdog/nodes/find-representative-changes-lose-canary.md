---
id: find-representative-changes-lose-canary
type: finding
status: fixed
depends_on: [find-candidate1-never-tagged]
supersedes: []
related: [find-candidate1-never-tagged]
tags: [root-cause, fix, referenceChains, canary, representative, lru-eviction, marker-tag, NEW-THIS-SESSION]
created: 2026-08-27
updated: 2026-08-27
---

# Canary representative changes lose marker tag for high-churn classes

## Observation

On the live pod, the [B (byte array) leak candidate consistently showed
`tag=0` in `pollWatchedTargets()`, while other candidates (klass_id=145,
211, 2292) had stable marker tags. The [B representative kept changing
because there are many leaking [B instances — LivenessTracker's ring
buffer evicted the old representative and selected a new one. The new
representative had no marker tag; the old one's marker tag was on a
dead/evicted object.

The canary mechanism pre-tagged one representative per class with a
marker tag. When the representative changed, the canary lost track —
no chain was ever built for [B.

## Root cause

`pollWatchedTargets()` admitted a candidate by `SetTag(obj, marker_tag)`
on the representative returned by `resolveCandidateRepresentative()`.
On subsequent polls, it called `getTag(obj)` on the NEW representative
(which returned 0) and treated `tag == 0` as "not yet discovered by the
walk" — but actually the marker tag was on the OLD (now dead)
representative.

## Fix (COMMITTED 7bd7255c3)

Two changes:

1. **Re-tag the representative** when `tag == 0` for an already-tracked
   candidate. `pollWatchedTargets()` finds the slot for this klass_id
   and `SetTag(obj, marker_tag)` on the new representative, so the canary
   mechanism can find it on the next walk pass.

2. **Auto-mark all discovered instances**: when the BFS walk admits an
   object whose class matches a watched leak class, record its frontier
   tag in `_candidate_discovered_tags[slot]` (fixed-size array, no heap
   allocation in the callback). `pollWatchedTargets()` builds chain
   events for all discovered instances, not just the pre-tagged
   representative. A leaking class typically has many live instances, each
   with an independently useful reference chain.

### Data structure

`_candidate_discovered_tags[MAX_LEAK_CANDIDATES][MAX_DISCOVERED_INSTANCES_PER_CLASS]`
where `MAX_DISCOVERED_INSTANCES_PER_CLASS = 8`. When the per-slot array
fills, further instances are silently dropped (the representative + up
to 8 others is still far more coverage than the single-representative
design it replaces).
