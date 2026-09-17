---
id: find-fresh-lane-verification
type: fix-verification
status: confirmed
depends_on: [find-tier1-tail-starvation, ev-leaktag-onpod-round15, ev-leaktag-onpod-round15-results]
related: [find-wrapper-demotion-self-parent]
tags: [fix-verification, fresh-lane, pod-verification, round-15, NEW-THIS-SESSION]
created: 20260916
updated: 20260916
---

# Find: fresh-admission lane verified live on pod (round 15) — wrapper walked once, events emitted

Parent: find-tier1-tail-starvation (the round-15 diagnosis this fix
answers). Evidence: ev-leaktag-onpod-round15.md (design + discarded
mark-vs-queue lesson), ev-leaktag-onpod-round15-results.md (live
verification). Build f7b1ea416, new pod prof-analyzer-hotdog-jb-d9d8cf-cgdtx
(the deploy REPLACED rz992 — always re-find the pod name after a deploy),
JVM from ~05:24Z 2026-09-16.

## What the pod verified (all from kubectl logs -f streams; the log flood
is ~800k lines/min — the 10MB container cap rotates in SECONDS, --since
windows are useless for early-lap evidence)

1. **The fresh lane works mechanically**: anchorTierHistogram shows
   fresh_tier=1-11 kept per pass, fresh_queue=2-615 (one pass of sweep
   admits, far under the 1024 cap), budget=32. The arithmetic gate
   (fresh demand vs budget) passed.
2. **The wrapper admitted root-attached AND was walked** — the first
   successful walk in the whole investigation: 
   `walkStaticFieldAnchors anchor tag=164392
   class=Ljava/util/Collections$SynchronizedRandomAccessList; klass_id=28366
   parent=0 root_kind=8 state=0 field_index=41`, holder-class diagnostic
   `ProfileAnalyzer; field_index=41`, round-12 diag: 21 entries (ArrayList,
   wrapper seen_as=2 already-admitted, Object[], then 17 [B chunks all
   seen_as=0 = fresh plain admissions), edges=19 truncated=0 — the whole
   subtree covered in one bounded call.
3. **The chunks were discovered, auto-marked, and got deep chains**
   (chain_size=6-12, depth=5-6) — the leak-class [B instances have
   multi-hop holder chains in the frontier.
4. **datadog.ReferenceChain events were emitted**: 
   drainPendingChainEvents re-emitted=4, then =6 — cached chains flowed
   into JFR dump chunks. First events on this pod.

## Why the end goal still isn't closed (chain continues in
find-wrapper-demotion-self-parent)

Search #2 (the one that walked the wrapper) hit the frontier cap and
died; releaseSearchTags wiped the chunk entries; the chunks (retained,
tracked, tid-matched) got re-tagged with leak tags by the poll loop
(tagged grew 12→36→48 — they now INCLUDE the wrapper's chunks, waiting
for one interception). In later searches the wrapper's frontier entry is
DEMOTED (parent==its-own-tag, root_kind=0 — collector-invisible) and the
B' at-risk FIFO is cap-pinned by noise floods, so the wrapper never
re-walks: zero wrapper walk lines across 3 holder-class crossings. One
re-walk while the chunks hold leak tags converts everything
(interception → entry.leak_tag → correlated chains → canary resolves).

## Reasoning chain (design level)

Fresh-priority is the correct invariant for late-loaded holder classes:
admission order = sweep order = class order, so any holder whose class
loads late admits at the index tail and fair-only coverage needs
ceil(cohort/budget) passes — which must fit inside the MEASURED search
lifetime, not the designed one. The queue form (one first-look per
anchor) is order-immune to stale cross-search/cross-test state where the
mark form (positions-since-watermark) reorders selection — caught
in-test by StaticAnchorRotation* in order runs; see
find-test-seam-aliasing for the singleton-leakage lesson pattern.
