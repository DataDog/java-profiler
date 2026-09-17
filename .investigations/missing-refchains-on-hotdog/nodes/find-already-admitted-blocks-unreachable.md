---
id: find-already-admitted-blocks-unreachable
type: finding
status: confirmed
depends_on: [find-anchor-holder-eviction, find-already-admitted-blocks-deeper-chain, find-depth0-durable-root-upgrade-gap]
related: [find-anchor-live-feed-design, find-leak-tag-pool-implementation]
tags: [root-cause, PRODUCTION-BUG, referenceChains, heapReferenceCallback, improveChain, maybeUpgradeRootAttachedRootKind, dead-code, nesting, NEW-THIS-SESSION]
created: 20260914
updated: 20260914
---

# PRE-EXISTING PRODUCTION BUG (found while implementing B'): the already-admitted re-attribution blocks in heapReferenceCallback were unreachable

## The bug

Commit 57aec4895 ("Fix improveChain: call from heapReferenceCallback,
not admitObject", 2026-08-28) intended to move improveChain out of
admitObject's first-admission-only path into the already-tagged path of
heapReferenceCallback. The diff placed the call right after the
`switch (result)` — which is INSIDE the `if (*tag_ptr == 0)` first-
admission block. Every subsequently-added already-admitted behavior was
placed in the same nest:

- improveChain (57aec4895) — dead for its stated purpose: a freshly
  admitted entry carries exactly this edge's (parent_tag, depth), so the
  `depth > entry.depth` check is a guaranteed no-op where it sat.
- reparentToDurableRoot (f4c73ba0f round) — same nest, same deadness.
- maybeUpgradeRootAttachedRootKind + the B' sweep push
  (find-depth0-durable-root-upgrade-gap's fix) — same nest.

For an object with *tag_ptr != 0 at callback entry, the whole block was
skipped: the callback ran the descend gates and returned. So from the
sweep/BFS/descend paths, NO already-admitted entry was ever improved,
re-parented, or root-kind-upgraded. (heapRootCallback has its own working
ALREADY_ADMITTED handling — only the root-walk path could upgrade
root kinds.)

## Why the gtests never caught it

The verifying tests drove the functions DIRECTLY via
ReferenceChainsTestAccessor (maybeUpgradeRootAttachedRootKindForTest,
insertFrontierEntry + improveChain), not the callback wiring — classic
"tested the function, not the call site". The B' end-to-end test failed
deterministically (pushed_total=0, entries never improving), which
surfaced it.

## Impact on prior findings

- find-anchor-holder-eviction's mechanism 2 (improveChain demotion) NEVER
  fired on any pod round — the pod's holder was excluded purely by
  mechanism 1 (admission order: born chain-attached via the BFS before
  the sweep's lap reached its class) + the then-dead upgrade path
  (mechanism 3). The eviction OBSERVATION stands; the demotion
  CONTRIBUTOR was never live.
- The round-3-observed "depth-0 root upgrades (76)" came from
  heapRootCallback's own path, not this callback.

## The fix (implemented with B')

Restructured into a real `else if (*tag_ptr > 0)` arm after the
first-admission block: parent_tag != 0 → improveChain / reparent (+ B'
demotion push); parent_tag == 0 → maybeUpgradeRootAttachedRootKind (+ B'
sweep push). Verified: 112 gtests green (no existing test depended on
the dead behavior), full gtestDebug suite green, ddprof-test
*ReferenceChain* family green (1 pre-existing failure on HEAD unrelated:
AggressiveLeakReferenceChainTest.shouldOpenSearchGate... fails 3/3 on
clean ff060cfac too — flagged separately, not caused by B').
