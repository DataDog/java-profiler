---
id: find-wrapper-not-in-anchor-tier
type: root-cause
status: confirmed
depends_on: [ev-leaktag-onpod-round12, find-anchor-live-feed-design]
related: [find-anchor-holder-eviction, find-option-c-descend-walk-design, find-rotation-resize-blindspot]
tags: [root-cause, referenceChains, anchor-tier, collector-lottery, wrapper, SynchronizedRandomAccessList, NEW-THIS-SESSION]
created: 20260915
updated: 20260915
---

# ROOT CAUSE: wrapper is root-attached STATIC_FIELD but the collector cursor never reaches it

## The wrapper class

Bytecode inspection confirmed: `LEAK_BUFFER = Collections.synchronizedList(new ArrayList<>())`.
The wrapper is `Collections$SynchronizedRandomAccessList`, NOT
`UnmodifiableRandomAccessList` (the round-12 diagnostic checked for the
wrong class — fixed).

## What the deployed diagnostics show

1. **The sweep DOES process the wrapper.** The sweep's STATIC_FIELD edge
   hits the wrapper as an already-admitted entry (`*tag_ptr > 0`). The
   wrapper was admitted by the BFS before the sweep reached it.

2. **The wrapper IS root-attached STATIC_FIELD (root_kind=8).** The sweep
   log shows entries with `root_kind=8 state=0 found=1` — already
   root-attached. The wrapper is among the 29 unique klass_ids with
   root_kind=8 in the sweep's already-admitted encounters.

3. **The collector cursor never reaches the wrapper.**
   `collectStaticFieldAnchorsForRotation` scans the frontier table in
   tag order with a wrapping cursor, selecting 4 entries per pass
   (`STATIC_ANCHOR_ROTATION_BUDGET=4`) + 16 FIFO-drained = 20 total.
   The frontier has 228k entries. The walked root_kind=8 anchors are all
   in tag range 5890-6030 — the cursor is stuck in a small range. The
   root_kind=8 entries span tags 23-89608. At 20/pass, ~3s/pass, covering
   228k entries takes ~9 hours. The candidate flaps out (terminal) long
   before the cursor reaches the wrapper.

4. **The `SynchronizedRandomAccessList` never appears in anchor walks.**
   Zero matches across the entire log. The wrapper IS in the anchor tier
   (root_kind=8) but the collector's wrapping cursor lottery never
   selects it.

5. **The round-11 "wrapper was walked" observation was a decoy.** The
   `UnmodifiableRandomAccessList` walked at 21:10 UTC (round 11) was
   held by `io/netty/util/NetUtil`, NOT by `ProfileAnalyzer`. The actual
   LEAK_BUFFER wrapper was never walked.

## The bottleneck

`collectStaticFieldAnchorsForRotation` does a full frontier table scan
(228k slots) with a wrapping cursor, selecting only 4 root-attached
STATIC_FIELD/JNI_GLOBAL entries per pass (`STATIC_ANCHOR_ROTATION_BUDGET=4`).
The scan is O(frontier_size) per selection — most slots are NOT
root-attached, so the cursor advances past thousands of non-matching
slots to find each anchor. With 228k entries and ~29 root_kind=8
anchors scattered across tags 23-89608, the cursor takes hours to
sweep the whole table.

The candidate is STABLE in this recording (klass_id=9, tid=349994,
33 tagged at 78MB, no flap-out). The collector has unlimited time.
But at 4 anchors/pass, ~3s/pass, covering 228k entries takes ~6+
hours. The cursor IS advancing — just far too slowly.

## Fix options

1. **Raise `STATIC_ANCHOR_ROTATION_BUDGET`** (4→16 or higher): nearly
   free under the GOTW floor (the GOTW call resolves all 20 in one shot),
   but the cursor still scans the whole table.

2. **Index root_kind=8 entries**: maintain a separate list/vector of
   root-attached STATIC_FIELD entries, so the collector iterates only
   the anchor set (O(anchors) instead of O(frontier_size)). The scan
   becomes O(29) instead of O(228k).

3. **Prioritize anchors by leak-tagged children**: walk anchors that
   have leak-tagged descendants first. The wrapper holds the [B] chunks
   (klass_id=4, 33 tagged at 78MB) — it should be walked before any
   machinery static.

Option 2 is the structural fix. Option 3 is the targeted fix. Both are
needed: option 2 makes the collector fast enough, option 3 makes it
walk the right anchor first.
