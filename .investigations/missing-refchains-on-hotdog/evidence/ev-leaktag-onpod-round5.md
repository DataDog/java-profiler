---
id: ev-leaktag-onpod-round5
type: evidence
status: confirmed
depends_on: [ev-leaktag-onpod-round4, find-canary-lane-backoff-design, find-admission-boost-implementation, find-togcroot-orphaned-slot-stranding]
related: [find-priority-queue-starves-bfs-crawl, q-resize-instrumentation-rescan-priority]
tags: [pod-verification, round-5, backoff, admission-boost, crawl-throughput, NEW-THIS-SESSION]
created: 20260902
updated: 20260902
---

# Pod round 5: all machinery fixes verified live; interception still blocked by crawl reach

Accumulated build (A+B+backoff+boost+orphan sweep, post-7c37ee833),
deployed by the user (in-place, pkill). JVM 6600, ~20 min in, log tail
~13 min (container 10MB rotation - the per-tag tagLeakInstances flood
re-logs all 256 stable tags every poll, ~600k lines/20min). Extracted
lib marker-verified: backoff, Tier-2 state=%s selection, watched tids,
orphan sweep, per-tid gate, PriorityExpandSet - all present.

## Verified live this round

- Canary backoff: mult=16 x ema_ms=184-190 -> ~3s spacing, ~292
  passes/20 min, burn structurally bounded. (Round 3: back-to-back 1
  core for 32 min.)
- Fix B (gotw window widening): batch_size=196-512 under a 107k
  pendingExpand backlog with ema_call_ms=63-65 - no MIN-collapse
  (round 4 collapsed to batch=8).
- Fix B+backoff pass walls: pass ema_ms=190 (round 4: 0.7-4s); passes
  admit real edges again (100-198/pass, truncated=1).
- Admission boost: noteSelectedCandidates watched tids=859 polls,
  tid=6809 published throughout.
- Pool economy PERFECT: every tag line is klass_id=6 tid=6809
  size=78643216 (the real 78MB leak chunks, ages 64-75); 656 polls
  tag the full 256-pool + 203 tag 16; zero machinery noise (round 3:
  247 scattered tags).
- Orphan sweep: live, 0 firings - candidate qualifies every poll
  (correct; sweep is the fallback).

## Still blocked (the one remaining gap)

- Interception 0, need_set=0 (stable waiters never admitted):
  the 256 tagged real leak chunks are never ENUMERATED - they sit
  under holders the crawl has not reached. pendingExpand=107,526-
  107,547 (drains ~10-20/pass = hours); static sweep cursor advances
  512/pass (lap ~67 passes, multiple laps done) but the flood of
  machinery admissions keeps the queue buried.
- Fix A (FRONTIER-state Tier-2): 48 selections all state=EXPANDED
  (fanout 648-2048 - machinery arrays; [B is the watched class so any
  byte[] admission builds fanout). 0 FRONTIER selections: the leak
  holder has ZERO leak-accumulation edges because its children (the
  tagged chunks) were never admitted - chicken-egg: edges exist only
  after expansion; selection needs edges. The signature path needs at
  least one admitted (leaf,parent) edge of the real leak to exist.
- discoveredCounts=[8,...]: 8 noise [B recorded as the candidate's
  "discovered instances" - [B is too broad a candidate class on-pod;
  first-8-fresh-[B-wins, none are the leak chunks. No chains built
  from them (no auto-marked-chain lines in the tail).

## Conclusions / next actions

1. All landed machinery is verified live and behaving exactly as
   designed; the remaining blocker is pure crawl REACH - the same
   diagnosis as round 4, now with every other factor eliminated.
   This is the strongest evidence yet for the deferred option C
   (candidate-scoped frontier: prioritize expansion toward the
   candidate's holders/tids rather than FIFO over the whole graph).
2. The tag flood: make tagLeakInstances log per-poll summary, not per
   instance (or skip re-logging stable tags) - it rotates the
   container log every ~10MB and cost us log-head this round.
3. Re-check the pod after the run accumulates (1-2h): if interception
   lands as the backlog drains, option C is a throughput win, not a
   correctness gap; if not, it is the correctness gap.
