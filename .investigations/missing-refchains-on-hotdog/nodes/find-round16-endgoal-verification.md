---
id: find-round16-endgoal-verification
type: fix-verification
status: confirmed
depends_on: [find-wrapper-demotion-self-parent, ev-leaktag-onpod-round16-results]
related: [find-fresh-lane-verification]
tags: [fix-verification, pod-verification, END-GOAL, leak-tag-interception, control-run, canary, round-16, NEW-THIS-SESSION]
created: 20260916
updated: 20260916
---

# Find: round-16 end-goal verification — leak-correlated ReferenceChain events flowing on the pod

Parent: find-wrapper-demotion-self-parent (the round-16 fixes this
verifies; FIXED + verified). Evidence:
ev-leaktag-onpod-round16-results.md (pod cgdtx, build 4afe870a2, JVM
07:45:11Z 2026-09-16, stream /tmp/r16_stream2.log).

## The milestone

For the first time in the entire investigation, the full chain works
end-to-end on the real leak:

1. Leak-tag INTERCEPTION fires (12+ and climbing): 
   `leak-tag intercepted: leak_tag=1073742xx -> frontier_tag=... 
   depth=3 parent_tag=<chain>` — leak-tagged [B chunks (the real leak
   instances, tags ≥ LEAK_TAG_BASE = 2^30) admitted into the frontier
   WITH their leak tags and parent chains. Never fired before round 16
   (round 15: 0 interceptions, all chains carried frontier-tag
   targets).
2. Leak-correlated chains cached: `auto-marked chain for klass_id=5 …
   target_tag=1073742071/72/77` — leak-tag targets, not noise.
3. Events flowing: `drainPendingChainEvents re-emitted=6 → 14`,
   sustained on every dump.

Fix A verified at scale — and wider than designed: the app has MANY
synchronized-list statics (LEAK_BUFFER's wrapper, but also
`ProcessTags$Lazy` field 3 and more — the round-12 wrapper diag fires
for all of them), and self_edge_skips=30816+ means the round-15
parent==self demotion was corrupting a whole POPULATION of anchors, not
just the wrapper. The guard keeps them all collector-selectable
(wrapper admitted root-attached parent=0 root_kind=8, walked as anchor
tag 2184). Fix B verified: quota_drops=6351 with fifo_size=132 — the
floods (same shapes as round 15) are contained; 16 drained/pass.

## The accidental control run (unplanned, valuable)

The first redeploy of this round put the pod on the NON-LEAKING app
image: 3h with the round-16 .so loaded and ZERO reference-chain
activity — no candidates, no searches, only boot/liveness logs. The
candidate/generations gate keeps the entire machinery dormant on a
healthy app — a production-readiness property verified live, not just
by unit tests. (Also operationally: a quiet app after deploy does NOT
mean the build is broken — check whether the app is the leaking
version and whether traffic is flowing before debugging the tracker.)

## Remaining at verification time (watch, not blockers)

- Canary 0/1: the chase hunts its ONE pre-tagged representative while
  interceptions correctly hit the rest of the pool population; the
  round-15 chase DEADLOCK (chase needing the never-happening walk) is
  broken — walks + interceptions every pass, so exit is expected as
  coverage reaches the representative (which also validates the
  chase-exit path end-to-end). When it exits, the search completes and
  restarts clean.
- `buildChainEvent false: reconstructChain failed` for small
  frontier-tag targets (noise instances whose entries died mid-pass) —
  benign; look during the cleanup round.
- Log rate at healthy search activity ≈ 24k lines/min (the round-15
  800k/min flood was the deadlocked chase's TEST_LOG spam) — the TEMP
  diagnostics removal list is in STATE.md; keep self_edge_skips and the
  quota counters as permanent low-rate observability candidates.
