---
id: ev-leaktag-onpod-round4
type: evidence
status: confirmed
depends_on: [find-per-tid-qualification-design, ev-leaktag-onpod-round3]
related: [find-canary-search-forces-max-cadence, find-getobjectswithtags-quadratic-bottleneck, q-coverage-tracking-per-combination]
tags: [pod-verification, option-C, per-tid, crawl-throughput, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# Pod round 4: per-tid gate works exactly as designed; interception still blocked by crawl throughput

Build c5490156e (per-tid qualification + PriorityExpandSet), JVM 120642,
13 min into the run, logs in build/logs local copy /tmp/hotdog-round4.log
(58257 lines). Binary verified via marker strings in the extracted lib
("klass trend OK but no qualifying tid - skipped", "selectLeakCandidates
entry", "PriorityExpandSet").

## What works (option C confirmed on-pod)

- selectLeakCandidates logged 183 "klass trend OK but no qualifying tid -
  skipped" (klass_id=7 among them: klass slope 1.40, consecutive 9 - a
  genuine klass-level rise rejected because no single thread qualifies).
- Exactly ONE candidate qualifies: klass_id=2 ([B), and all pool tags go
  to ONE thread: tid=120852, 75 MiB byte[]s (size=78643216), ages 4-18
  rising. Compare round 3: 247 tags scattered over machinery byte[]s
  (16-24KB, many tids, flat retention). Pool pollution eliminated.
- Poll cadence: candidate[0] klass_id=2 tag=1073742079 needRefresh=1
  each pass; tagLeakInstances tagged=5 per poll, need_set=0 (stable
  waiters, never admitted).

## What still fails (unchanged from round 3)

- Zero interceptions ("leak-tag intercepted" absent), zero
  recordDiscoveredInstance/requeueChainRootForRotation,
  candidateFound=0/1 every pass -> shouldRunPass -> true (canary search)
  on all 183 passes (forced cadence persists).
- buildChainEvent false: target_tag=1073742079 not in frontier - all
  183 polls.

## New precise numbers (the throughput wall, quantified)

- frontierSize=242106 (grew from 199k in round 3); pendingExpand=126,895
  CONSTANT (never meaningfully drained); priorityExpand=1016.
- expandFrontier: 877 gotw calls, batch 8-9 (GOTW_MIN regime), resolved
  =batch, edges=0 on 701/877 calls; total edges admitted ~1389 in 13 min
  (~7.5/pass, occasional 100+).
- gotw_ms: min 14 / median 24 / p90 34 / max 41 - the O(tag-map) floor at
  a 242k-entry map, EXCEEDING the ~10ms pass expand window, so the
  proportional control ratchets to MIN_BATCH and each pass fits only
  ~2-4 calls.
- Backlog drain rate ~120-200 objects/min vs 127k backlog = ~10-17
  hours per lap; the leak holder (elementData-style Object[] of the
  growing list) sits unexpanded in that backlog, so the tagged byte[]s'
  incoming edge is never enumerated post-tagging -> interception never
  fires. PROVEN not-retagged: need_set=0 with leak tags means SetTag ran
  while the objects were unvisited (tag 0), and zero intercepts since.
- Pass rate DROPPED: 183 passes/13min = ~14/min vs 88/min in round 3
  (inferred ~4.3s/pass; per-pass duration decomposition needs a TEMP
  timing log - static sweep full 33007-static lap happens every pass,
  cursor=0 each time).
- rotation_candidates every pass: root_kind_tags=16
  leak_accumulation_tags=0 stale_expanded_tags=0-9,
  leak_signatures=476->487, leak_parents=50248->51033.

## Root cause of the dead targeted tier (code-confirmed)

collectLeakAccumulationCandidatesForRotation (referenceChains.cpp:2482)
Tier 2 only selects parents whose frontier state is EXPANDED
(:2527-ish lookup + entry.state == EXPANDED check). The growing holders
of the watched leak klass are freshly admitted FRONTIER-state backlog
entries that never get expanded (starvation above) - so the tier that is
supposed to target exactly the accumulation point selects ZERO every
pass while holding 51k known parent candidates.
