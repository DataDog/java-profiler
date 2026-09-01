---
id: find-canary-search-forces-max-cadence
type: finding
status: confirmed
depends_on: [find-cpu-pain-budget-blocks-bfs]
related: [find-representative-changes-lose-canary, find-leak-tag-pool-implementation, q-allocation-site-selection]
tags: [root-cause, cpu-burn, canary, shouldRunPass, pod-logs, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# An unfindable candidate canary forces a pass at EVERY iteration - the 30%+ CPU burn

Observed on hotdog (JVM 75258, build 663784137): the user flagged 30%+
CPU burn. The threadLoop logs show `shouldRunPass -> true (canary
search, 0/1 candidates found)` on EVERY logged decision, `blocked` (cpu
pain budget) never firing, `passesRun=2803` in 32 min = ~88 passes/min
(the ~12/min figure in round-2 evidence was pre-proportional-build).

Mechanism: candidate[0]'s marker/canary is never found by the walks
(`needRefresh=1` persistent - the same never-found-marker state as the
seams test, but here in production). While any candidate's canary is
unfound, `shouldRunPass` returns true every iteration (10ms cadence),
bypassing the cadence throttle AND the pain budget. Each pass costs
~5 GetObjectsWithTags scans (18-21ms each, O(tag-map) under the tag-map
lock) + a ~15ms STW walk VM op -> roughly 100-130ms of tagged-CPU+STW
work per pass, ~90 passes/min ~= 15%+ of one core in scanning alone,
before GC/pause interference - matching the user's 30%+ observation
shape.

Two ways it ends:
- The candidate is retired (e.g. by (klass,tid)-qualified selection -
  the [B candidate looks like machinery churn: tagged instances are
  24-16KB kafka-ish byte[]s with stable, not rising, per-site retention)
  -> no candidate -> no canary search -> cadence returns to throttle.
- The marker becomes findable (needs the holders of tagged instances to
  be walked - the disjoint-set lottery; without a bridge this never
  resolves on a large heap).

Implication for planning: option C (per-(klass,tid) candidate
qualification, no walks needed) is not just signal quality - it is the
CPU-burn fix. It attacks the forced-cadence burn at zero walk cost.
B (full-graph intercept sweep) would have ADDED ~10s STW per lap and is
retracted (find-jvmti-heap-walk-stw-vmop).

## Correction (post option-C implementation)

On hotdog specifically, C does NOT end the canary search by retiring the
candidate: the pod runs a DELIBERATE simulated-memory-leak thread whose
per-tid signal is real and rising (ev-tid-clustering evidence), so
per-(klass,tid) qualification SCOPES the tagging to the leak thread
instead. Burn relief there must come from interception becoming possible
(tagged objects = leak-site instances under holders the crawl rotates
to), closing the canary the normal way. The "retire the false candidate"
path remains C's effect for genuine machinery-churn false positives.
