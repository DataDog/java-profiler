---
id: find-canary-found-criterion-unmigrated
type: root-cause
status: confirmed-fixed-pending-pod-verification
depends_on: [find-round16-endgoal-verification, ev-leaktag-onpod-round16-results]
related: [find-representative-changes-lose-canary, find-canary-continue-skips-discovered-instances, find-refchains-log-flood-configurable]
tags: [root-cause, canary, leak-tag, found-criterion, design-migration, fix, round-19, NEW-THIS-SESSION]
created: 20260916
updated: 20260916
---

# ROOT CAUSE: canary chase structurally unresolvable — the marker→leak-tag migration never migrated the found criterion (round 19, FIXED 788d7b2a7)

Evidence chain (all pod 289f8, JVM pid_28570, level-1/2 runtime windows
via the rcDebugLevel knob — no deploys needed): "canary search, 0/1
candidates found" on EVERY JVM since the leak-tag design change, while
`drainPendingChainEvents re-emitted` grew (2→34) — events flowing, chase
never resolving. The representative `candidate[0] tag=<LEAK TAG>
needRefresh=1` on every tick, with `buildChainEvent false: target_tag
not in frontier` for its leak tag.

## The mechanism (three unmigrated pieces)

1. **Found bits**: `_candidate_found_bits` (the chase's ONLY exit
   criterion, popcount in shouldRunPass) is set ONLY in
   heapReferenceCallback()'s MARKER-tag block — and markers are never
   set since the slot registration changed to `_candidate_tags[slot]=0;
   // no marker tags — using leak tags now`. Under leak tags NOTHING
   sets found bits → the canary can never report 1/1 → every search ends
   via frontier-cap/no-progress instead of "all candidates found".
2. **Rep path check**: `_resolved_chains.find(rep_leak_tag)` — the cache
   is keyed by FRONTIER tags (disc_tag); the rep's leak tag is never a
   key → needRefresh=1 forever.
3. **Rep path build**: `buildChainEvent(rep_leak_tag)` →
   `frontier->lookup(leak_tag)` always misses (interceptions insert with
   a FRESH frontier tag; entry.leak_tag rides inside the entry) → a
   doomed rebuild every poll (~4/s frontier lookups + level-2 noise).

Why this survived rounds 15-18: events flow via the DISCOVERED-instance
path (recordDiscoveredInstance → buildDiscoveredInstanceChains →
auto-mark with target_tag = the leak tag), which is orthogonal to the
chase exit. The 0/1 state was chase lifecycle noise (search churn,
backoff CPU), not an event blocker — which is why the end goal verified
while the canary stayed stuck.

## The fix (788d7b2a7)

In `buildDiscoveredInstanceChains`, where leak-tag chains are built: a
chain with `target_tag >= LEAK_TAG_BASE` for a candidate slot marks the
slot found and records its canary link (frontier tag = disc_tag, parent
0, depth, referrer klass) — the leak-tag-world "canary found" = a walk
reached the leaked population AND the correlation carried. Noise chains
(targets below LEAK_TAG_BASE) do not mark found. The rep path resolves
by the slot's chain key and stops the doomed rebuilds. Regression test
`LeakTagChainMarksCanaryFound` (leak slot → found + link; noise slot →
not found); 122/122.

## Design decision recorded

The criterion is per-SLOT-any-instance (any leak-tag-target chain of the
candidate klass), not the representative's own tag. Rationale: the
per-instance guarantee moved INTO the leak-tag correlation (events
carry target_tag = leak tags); the rep's own chain still emits via the
discovered path whenever its instance is intercepted (its leak tag is
the event target). Exit-on-first-leak-chain ends the search promptly
instead of chasing one specific chunk through sporadic subtree coverage
(5-min window on 289f8: zero NEW interceptions, wrapper not walked,
34 cached chains from earlier in the search — coverage is sporadic at
batch scale, a separate upstreaming-round topic).

## What to verify on the next deploy

`canary search, 1/1 candidates found` (level 1) → the chase exits → the
search completes → `releaseSearchTags` → a clean restart cycle
(`canary found: klass_id=%u slot=%d leak chain target_tag=...` at
level 1 is the new marker). The rep path's needRefresh should clear
(no more `buildChainEvent false: target_tag=<leak> not in frontier`
retry spam at level 2).
