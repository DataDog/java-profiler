---
id: ev-leaktag-onpod-round15-results
type: evidence
status: confirmed
depends_on: [find-tier1-tail-starvation]
related: [find-fresh-lane-verification, find-wrapper-demotion-self-parent]
tags: [pod-verification, round-15, fresh-lane, wrapper-walk, NEW-THIS-SESSION]
created: 20260916
---

# Round 15 on-pod verification (ev) — first wrapper walk, first events; new gap measured

Pod: NEW replacement `prof-analyzer-hotdog-jb-d9d8cf-cgdtx` (rz992 replaced by
the deploy; new JVM ~05:24Z 2026-09-16). Round-15 build f7b1ea416 verified in
the loaded .so (fresh_tier/fresh_queue strings). Streams (buffer rotates in
SECONDS at the current ~800k lines/min — the 10MB container cap cannot hold a
minute): /tmp/r15_stream.log (05:35-05:48), /tmp/r15_stream2.log (05:49+,
8M+ lines), tails in /tmp/r15_tail.log.

## VERIFIED — the round-15 machinery works end-to-end up to the chains

1. **Fresh lane**: `anchorTierHistogram … fresh_tier=1-11 fresh_queue=2-615
   container_tier=304-352 other_tier=8564-9205 budget=32` — the queue stays
   ~one pass of admits (≪ 1024 cap), the lane keeps its picks. Arithmetic
   gate passed.
2. **THE WRAPPER WAS ADMITTED ROOT-ATTACHED AND WALKED** (search #2, ~05:44Z):
   `walkStaticFieldAnchors anchor tag=164392
   class=Ljava/util/Collections$SynchronizedRandomAccessList; klass_id=28366
   parent=0 root_kind=8 state=0 field_index=41` + the wrapper diagnostic line
   (`wrapper anchor … holder_class=Lcom/…/steps/ProfileAnalyzer; field_index=41`)
   + the round-12 walk diag: 21 entries — klass 64 (ArrayList), 28366 (wrapper,
   seen_as=2 already-admitted), 8, then **17 [B chunks (klass_id=6) all
   seen_as=0 (fresh plain admissions)** — `edges=19 truncated=0`. The walk
   covered the whole subtree. (seen_as: 0=plain admission, 1=leak-tag
   interception — none, the chunks were untagged at that instant.)
3. **The chunks were discovered, auto-marked, and got CHAINS**: discovered
   slot filled (recordDiscoveredInstance klass 6 count=8), auto-marked chains
   `tag=5748-5762` with `buildChainEvent … chain_size=6-12 depth=5-6
   root_kind=21` — deep multi-hop chains cached for the leak-class [B.
   (root_kind 21 = the tracker's own root-kind enum, not the static 8 — the
   chains root through a thread-root path; the STATIC shape is proven by the
   walk diag instead.)
4. **datadog.ReferenceChain events are being emitted**: 
   `drainPendingChainEvents re-emitted=4` and `=6` on successive dumps —
   cached chains are flowing into recordings for the first time on this pod.
5. Search #2 then hit the frontier cap and died; its tags/entries/chains were
   wiped (tagLeakInstances tagged count collapsed 137→13 on
   releaseSearchTags) and re-tagging restarted (tagged grew 12→36 — the
   retained [B, which include the wrapper's chunks, now carry LEAK TAGS,
   waiting for one interception).

## NEW GAP (round-16 items, all measured live, in priority order)

A. **Wrapper entry demotion — root-attached becomes chain-attached with
   parent==its-own-tag**. Every holder-class crossing after search #2
   probes: `wrapper_tag=2469/2679/2853 frontier_found=1 parent=<SAME TAG>
   root_kind=0 state=1 leak_tag=0 depth=1-3 referrer_klass=28366`. The
   entry is no longer parent=0/root_kind=8, so the collector's eligibility
   filter skips it — the wrapper is never re-walked (0
   SynchronizedRandomAccessList walk lines in stream2, across 3 holder-class
   crossings). parent==self smells like a self-edge insert (improveChain? a
   fanout/seed insert with parent==child?). FIND THE DEMOTER.
B. **B' at-risk FIFO cap-pinned by noise**: `pushAtRiskStaticAnchor …
   fifo_size=988-1024` — klass 1 (1396 pushes), 1733, 215 (1063) flood the
   1024 cap; pushes for the wrapper's class 28366: ZERO (dropped at the cap).
   The designed repair path for demoted static holders (the sweep re-encounter
   push) cannot fire. Per-class quota or flood eviction needed (round-10's
   known flood shape, now with measured per-klass counts).
C. **Leak correlation never fires**: zero `correlateAdmittedLeakTag` logs.
   The emitted chunk chains carry target_tag = frontier tags (leak_correlated=0)
   — real ReferenceChain events, but without the leakTag correlation the
   backend cannot tie them to the leak (HeapLiveObject.leakTag). Correlation
   fires via the state machine's frontier-tag branch — the wrapper's chunks
   simply haven't been in the frontier while a poll ran since they were
   tagged. ONE wrapper re-walk (fix A or B) while the chunks hold leak tags
   converts everything: interception (seen_as=1) → entry.leak_tag set →
   chain built with targetTag=leak tag → canary target resolves → events
   correlate.

The canary target (leak tag 1073741943, then later ones) still resolves
`not in frontier` — expected until the first interception.

## Operational notes

- Log flood ~800k lines/min (TEMP diagnostics × search churn × canary
  polls) — rotate in seconds; verification MUST use `kubectl logs -f`
  piped to files. Remove TEMP diagnostics after this round (the list is in
  STATE.md).
- Search lifetimes observed: 44-100 passes (one search #3 lived 84+); sweep
  laps ~10-20 min during class churn; holder class at index 24611-24874
  (drifts +60/lap with class churn).
- Class 1733's pushes at 988-1024: the flooders are klass 1/215/1733 —
  one per-class quota would free the FIFO for the wrapper.
