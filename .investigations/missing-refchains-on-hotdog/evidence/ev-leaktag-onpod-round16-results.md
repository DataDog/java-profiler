---
id: ev-leaktag-onpod-round16-results
type: evidence
status: confirmed
depends_on: [find-wrapper-demotion-self-parent]
related: [find-round16-endgoal-verification, find-refchains-log-flood-configurable]
tags: [pod-verification, round-16, END-GOAL, leak-tag-interception, control-run, NEW-THIS-SESSION]
created: 20260916
---

# Round 16 on-pod verification (ev) — LEAK-CORRELATED ReferenceChain events flowing

Pod `prof-analyzer-hotdog-jb-d9d8cf-cgdtx` (ns `profiling-stg`), build
`4afe870a2` verified in the loaded .so (self_edge_skips/quota_drops
markers; JVM pid 46655 from 07:45:11Z 2026-09-16). Stream:
`/tmp/r16_stream2.log` (~24k lines/min at steady search activity; the
~800k/min flood of round 15 was the canary-chase TEST_LOG spam, now
quieter because the chase is healthy).

## Accidental control run first (worth keeping): healthy app = dormant tracker

The first redeploy of this round put the pod on the NON-LEAKING app
image (v137233187): 3h of a healthy app, round-16 .so loaded, and
ZERO reference-chain activity — no candidates, no searches, only
boot-level + liveness logs. The candidate/generations gate held the
whole machinery dormant on a healthy app exactly as designed. (User's
observation; recorded as a production-readiness data point.)

## All round-16 gates verified live

1. **Fix A (self-edge guard) live at scale**: `self_edge_skips=30816+`
   and climbing — the guard refusing real `mutex == this` self-edges on
   every Synchronized* collection the walks touch. The LEAK_BUFFER
   wrapper itself: admitted ROOT-ATTACHED (`walkStaticFieldAnchors
   anchor tag=2184 class=Ljava/util/Collections$SynchronizedRandomAccessList;
   klass_id=28516 parent=0 root_kind=8`) and WALKED as a collector
   anchor — the round-15 demotion shape (parent==self root_kind=0) is
   gone. The round-12 wrapper diag also fires for OTHER
   synchronized-list statics (e.g. `ProcessTags$Lazy` field 3) — the
   app has many, which is why the skip count is 30k+.
2. **Fix B (per-class quota) live**: `static_anchor_fifo_quota_drops_
   total=6351` while `static_anchor_fifo_size=132` — the floods are
   back (6.3k quota-dropped pushes) and CONTAINED (round 15: FIFO
   pinned 1024/1024, wrapper's pushes dropped; now 16 drained/pass,
   room always available).
3. **THE INTERCEPTION CASCADE — live for the first time in the whole
   investigation**: `heapReferenceCallback leak-tag intercepted:
   leak_tag=1073742064..77 -> frontier_tag=186955+ depth=3
   parent_tag=<chain>` — 12+ leak-tagged [B chunks (the real leak
   instances, tags ≥ LEAK_TAG_BASE) admitted into the frontier WITH
   their leak tags and parent chains. Never fired before round 16.
4. **Leak-correlated chains cached and emitted**:
   `pollWatchedTargets auto-marked chain for klass_id=5 …
   target_tag=1073742071/72/77` (leak-tag targets, not frontier-tag
   noise) — 6 leak-tag chains in `_resolved_chains`; 
   `drainPendingChainEvents re-emitted=6 -> 14` sustained on every
   dump. datadog.ReferenceChain events tied to the leak's HeapLiveObject
   leakTags are flowing into recordings.
5. Fresh lane intact (`anchorTierHistogram … fresh_queue=12` on the
   first search); leak candidate live (`candidate[0] klass_id=5` =
   [B in this JVM; wrapper klass 28516).

## Still open (watch, not blockers)

- **Canary 0/1**: the chase still hunts its one pre-tagged
  representative instance (backoff_mult=16, ema ~190ms). The
  intercepted instances so far are other pool-assigned chunks; the
  representative is in the same LEAK_BUFFER population, so per-pass
  interceptions should reach it — round-15's chase DEADLOCK (chase
  needing the never-happening walk) is broken (walks + interceptions
  every pass). When it exits, the search completes and restarts clean.
- `buildChainEvent false: reconstructChain failed` lines exist for
  small frontier-tag targets (noise instances whose entries died) —
  the leak-tag chains build fine.
- TEMP diagnostics removal once this verification is accepted — the
  remaining log flood is ours.
