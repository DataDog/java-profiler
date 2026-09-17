---
id: find-anchor-holder-eviction
type: finding
status: open
depends_on: [ev-leaktag-onpod-round9, find-option-c-descend-walk-design, find-already-admitted-blocks-deeper-chain, find-depth0-durable-root-upgrade-gap]
related: [find-priority-queue-starves-bfs-crawl]
tags: [root-cause, referenceChains, anchor-tier, improveChain, parent-tag, eviction, NEW-THIS-SESSION]
created: 20260903
updated: 20260914
---

# ROOT CAUSE (round 9): static holders get evicted from the anchor tier — parent_tag==0 is unidirectional and improveChain actively destroys it

## The observation chain

Pod round 9 (ev-leaktag-onpod-round9): all 76 walked anchors are
machinery statics; the LEAK_BUFFER holder (a static `List<byte[]>` 3-4
hops from the root static, textbook prong-2) NEVER enters the anchor
tier, while the sweep demonstrably enumerates ~1000 STATIC_FIELD edges
per chunk and laps all 33k classes.

## The mechanism (code-confirmed; CORRECTED 20260914 — see find-already-admitted-blocks-unreachable)

The anchor collector (collectStaticFieldAnchorsForRotation,
referenceChains.cpp:3161) requires `entry.parent_tag == 0 && root_kind in
{STATIC_FIELD, JNI_GLOBAL}`. Three code paths interact to make a
dual-reachable holder lose that shape PERMANENTLY. MECHANISM CORRECTION:
mechanism 2 (improveChain demotion) NEVER FIRED from heapReferenceCallback
on any pod round — the call sat inside the `*tag_ptr == 0` first-admission
block since 57aec4895, dead for already-admitted entries. The pod's holder
was excluded purely by mechanism 1 (admission order) + the then-dead
upgrade path. The eviction OBSERVATION and outcome stand unchanged.

1. **Admission order**: if the holder's FIRST admission comes via a
   non-root edge (e.g. Thread → target → lambda → captured list — the
   classic self-registering-collection shape; Thread objects ARE
   admitted+expanded in the frontier, proven by the on-pod chains ending
   in ForkJoinWorkerThread), the entry is chain-attached (parent!=0,
   root_kind=0) from birth. The sweep's later static edge hits the
   ALREADY_ADMITTED path.
2. **improveChain (referenceChains.cpp:2083)**: a root-attached (depth-0)
   entry reached via any NEW deeper path is REPLACED with the deeper
   chain-attached entry — find-already-admitted-blocks-deeper-chain's
   fix, which had no anchor-tier awareness. A static holder that is also
   a task-closure capture gets demoted the first time a walk reaches it
   through the thread path.
3. **Re-rooting is refused (referenceChains.cpp:2376)**:
   maybeUpgradeRootAttachedRootKind returns false for parent_tag != 0 by
   design ("known, documented limitation" — reconstructChain() can't
   walk a re-rooted chain). So once chain-attached, the entry can NEVER
   regain anchor eligibility, no matter how many laps re-prove the
   static edge. The eviction is permanent for the search's lifetime.

Net: the anchor tier only ever holds statics whose values are reachable
by NO other path — i.e., leaf-like machinery constants (exactly the 76
observed: charsets, jnr enums, Method singletons). Any holder richly
referenced from the running graph (the interesting leaks by definition)
is systematically EXCLUDED. This also explains round 7's "exactly 4
anchors" and round 8's "walk magnitudes vary but interception zero".

## Why interception depends on it

The tagged 78MB chunks are only enumerated by walking DOWN from the
holder (anchor walk enumerates holder → elementData → chunk → leak-tag
interception in one bounded STW). The BFS backlog (pendingExpand
190k+) can't reach them in practice, and thread walks are
ThreadLocalMap-gated.

## Fix options (re-evaluated after standards survey, B' recommended)

- **A. Sticky durable roots**: improveChain must not replace an entry
  whose current attribution is root-attached STATIC_FIELD. **REFUTED
  20260914** by find-attribution-standards-survey: freezes one guess where
  every standard system re-derives or queries; still does not cover the
  admission-order case. Do not implement.
- **B. Static-attachment registry**: when the sweep's root-like
  STATIC_FIELD edge hits an already-admitted chain-attached entry
  (parent!=0), record the tag in a small bounded set; the anchor collector
  selects from root-attached entries PLUS this registry. Covers both
  orders. Defensible (lazy per-lap re-derivation) but keeps selection
  coupled to the mutated table + preserves the full-frontier scan.
  Minimal-diff fallback only.
- **B'. Live feed (RECOMMENDED)** — see find-anchor-live-feed-design:
  feed the anchor FIFO directly from the sweep's static-edge enumeration
  (at-risk filter: frontier-present, not root-attached-static), drain in
  walkStaticFieldAnchors. Anchor selection stops reading
  parent_tag/root_kind entirely → eviction structurally impossible.

## Open verification

Which order actually evicted the pod's holder is NOT yet proven by logs
(needs a TEMP counter/log on the sweep's static-edge-onto-chain-attached
path — the eviction symptom regardless of order). The fix (B especially)
works for both, so the distinction is not load-bearing for the fix.
