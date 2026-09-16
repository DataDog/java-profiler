---
id: ev-leaktag-onpod-round6
type: evidence
status: confirmed
depends_on: [ev-leaktag-onpod-round5]
related: [find-per-tid-qualification-design, q-resize-instrumentation-rescan-priority]
tags: [pod-verification, round-6, crawl-reach, option-C, NEW-THIS-SESSION]
created: 20260902
updated: 20260902
---

# Pod round 6: full sweep lap + 31 min, interception still zero - breadth-first reach is the correctness gap

Build c7f207a51 (round 5 + per-poll tag summary), JVM 18354, ~31 min,
summary log fix verified live (one summary line per poll: "summary
klass_id=4 tid=18565 tagged=15 ... max_size=78643216" - no per-instance
flood; log-head survived the whole window).

## Verified this round

- Per-poll tag summary works on-pod; leak thread identified: tid 18565,
  78MB chunks, ages 7-129.
- Per-tid gate + warmup: candidate qualified after ~20 min (klass 4
  trend consecutive_positive=30 with many short-lived tids at
  age_count=1 skipped; the leak tid crossed the age-trend cusp).
- Backoff: mult=16 x ema ~180-195ms, 407 held-offs - pacing as designed.
- Tier-2 re-walk: 1351 selections (all EXPANDED, mostly fanout=1
  machinery); static sweep completed ~1 full lap (cursor 30666/33275,
  512/pass); passes admit 146-645 edges each.

## The verdict: breadth-first reach is a correctness gap, not a throughput gap

- pendingExpand ~98.5k, NET GROWING (193k -> 194k frontier in 3 passes):
  the sweep's per-lap re-admissions replenish the queue as fast as the
  crawl drains it. The backlog will NEVER drain on a rising heap.
- Interception 0 after 31 min + a full sweep lap. The tagged chunks
  (need_set=0, ages up to 129) sit under a holder that was admitted
  (sweep lapped past the app's classes) but never EXPANDED - buried
  behind ~98k machinery entries.
- Rounds 5+6 with all machinery verified live (backoff, boost, pool
  targeting, Tier-2, gotw widening, summary) eliminate every other
  factor. Option C (candidate-scoped frontier) is now a CORRECTNESS
  requirement, exactly as predicted in ev-leaktag-onpod-round5.

## Option C concrete sub-moves (for the design discussion)

- C1 THREAD-SCOPED WALK: the candidate's allocating thread objects are
  known (qualifying tids -> live Thread objects). A FollowReferences
  starting at the Thread OBJECT (not the whole heap) is a BOUNDED walk
  of that thread's reachable graph (thread-locals map, its Entry[]
  arrays, the tagged chunks) - tiny STW cost, and heapReferenceCallback
  intercepts the leak tags during it. Directly serves the user's leak
  taxonomy "thread-local leaks via Thread objects".
- C2 STATIC-HOLDER PRIORITY: for static-held leaks, the sweep re-admits
  the holder's CURRENT backing array every lap - those fresh
  root-attached entries should take a priority lane (durable root_kind +
  admitted-since-last-pass) instead of FIFO behind 98k machinery.
- Unknown which shape hotdog's simulated leak uses; the two prongs
  cover both taxonomy categories.
