---
id: ev-leaktag-onpod-round2
type: evidence
status: verified
related: [find-ema-batch-collapse, find-priority-queue-starves-bfs-crawl, find-leak-tag-pool-implementation, find-leaktag-jfr-field-misalignment]
tags: [pod-logs, on-pod, post-fix, live-verification, aimd, leak-tag, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# On-pod round 2 of the leak-tag redesign (build 0db70994d, PID 48355)

Two deploys happened: JVM 44624 (11:11Z) was still the round-1 build — its
logs showed the old `ema=` per-tag format; the user redeployed again and
JVM 48355 (11:24Z) had the round-2 format (`ema_call_ms=`/`next_batch=`).

## What worked (round-2 fixes verified)

- **AIMD**: no collapse. Oscillates correctly around the 25ms per-call
  budget: `batch_size=34 gotw_ms=24 ema_call_ms=25 next_batch=17` → halve;
  `batch 17 → next 81` → +64. Batch settles ~17-80 because the O(tag_map)
  call floor (~20-25ms at ~200k entries) dominates; AIMD converges to the
  largest affordable batch, as designed.
- **Cadence**: ~12 runPass/min (was 0.2/min), ~5 gotw calls/pass,
  deadline-bounded; no more 10s-CPU passes. `pendingExpand=66k` though.
- **Pool tagging**: tagged up to 129 instances, by age-diversity priority.
- **Emergency**: `emergency=0` but multiplier 15× firing correctly on
  candidate progress (no false emergency).
- **Drains**: `Profiler::dump reference-chain batch=8 write_dropped=0` x3.

## What failed → find-priority-queue-starves-bfs-crawl

- `_priority_expand` 39k→103k in 20 min; `_pending_expand` never drained
  (priority-first drain); zero `intercepted:` logs; zero
  `auto-marked chain ... leak_tag=`; only the 8 depth-1 noise chains
  (cached, re-emitted); `leak_accumulation_tags=0` every pass;
  `leak_parents=19058` unreachable; `isQueuedForRotation` linear scan over
  the 103k queue under the frontier lock (hidden per-pass cost).

## Operational lessons

- **Build identification via distinctive TEST_LOG strings**: concatenate
  split source string literals before grepping pod logs — the interception
  log is "heapReferenceCallback leak-tag intercepted: ..." in output but
  "leak-tag " + "intercepted:" in source; grepping "leak-tag intercepted"
  for the OUTPUT is correct, but earlier confusion came from grepping for
  a field name that changed (`ema=` vs `ema_call_ms=`). Verify the deployed
  build by a log field that prints EVERY iteration (e.g. the gotw line),
  not an event-driven one.
- Pod chunk JFRs still show no `datadog.ReferenceChain` /
  `datadog.HeapLiveObject` types in jafar (both "Event type not found") —
  the chains appear only in the uploaded/merged recording, same as round 1.
- Chunk dir path: `/tmp/ddprof_root/pid_<PID>/jfr/<start_ts>_<PID>/`, only
  the last ~6 minutes of chunks retained (grab immediately).

Fix round 3 = commit f4c73ba0f (see find-priority-queue-starves-bfs-crawl).
Awaits redeploy.
