---
id: find-per-tid-qualification-design
type: finding
status: implemented
depends_on: [ev-leaktag-onpod-round3, find-canary-search-forces-max-cadence, find-jvmti-heap-walk-stw-vmop]
related: [find-leak-tag-pool-implementation, q-allocation-site-selection, find-lambda-fragments-calltrace-id]
tags: [fix, design, livenessTracker, leak-tag, option-C, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# Option C implemented: (klass, tid) qualification - trend OR retained-count bar

Option C (chosen after B was retracted - full-graph walks are one STW
pause, find-jvmti-heap-walk-stw-vmop). selectLeakCandidates() now requires,
on top of the klass-level trend gate, that at least one ALLOCATING thread
qualify; KlassCandidate carries the qualifying tids and
tagLeakInstances() tags ONLY tracked instances those tids allocated
(production tagging scope = the leak site, not the whole klass).

## The gate (LivenessTracker::recordTidTrendSamplesLocked / tidPushQualifies)

Per-klass TidTrend rings (8 tids x 16 slots) folded from the EXISTING
KlassCountScratch per-thread data (insertThreadGen) once per GC epoch -
no JVMTI call, pure table work. A tid qualifies for an epoch push if:

1. sustained age-trend: mean-of-thirds rise on its distinct-surviving-age
   ring (min fill 6, same LEAK_GROWTH bars), consecutive for the same
   hysteresis as the klass gate; OR
2. retained-count bar: surviving tracked instances of this one klass
   from this tid >= TID_RETAINED_COUNT_BAR (8) that epoch.

The OR is load-bearing and NOT arbitrary: pure age-trend structurally
cannot see one-cohort-per-thread accumulation (each one-shot worker's
instances share one age -> distinct-age count stays 1 forever, exactly
LeakingCacheScenario's per-round allocator-thread shape - a genuine
leak that would have been rejected). Machinery threads fail BOTH
discriminators (stable low count, flat age span). Decay: absent tids
push 0 (resets hysteresis - a thread whose instances died must not keep
a stale rising ring); eviction beyond 8 tids picks the weakest
non-synthetic trend. Test-seeded trends are synthetic=1 and exempt from
real-fold updates/decay/eviction (scenarios interleave System.gc() folds
with seeded ramps).

## Pod implication (corrects the earlier "C retires the pod candidate" claim)

Hotdog runs a DELIBERATE simulated-memory-leak thread (tid 172 / 92169
on different JVMs, age_count rising 2->3; ev-tid-clustering evidence) -
so per-tid qualification does NOT retire the pod's [B candidate: it
SCOPES the tagging to the leak thread's instances. The 247 tagged
machinery byte[]s (flat per-site retention, never intercepted) are out
of scope by construction; the pool tags go to leak-site instances whose
holders are the crawl's actual rotation targets. CPU-burn relief on the
pod comes from interception becoming possible, not from the candidate
disappearing.

## Test seam

seedTidTrendSample0 (JavaProfiler/javaApi.cpp -> tidTrendRecordForTest):
one seeded value lands in BOTH rings (age + retained-count), so tests
can qualify either way. Scenarios seed the REAL allocating tid
(JavaProfiler.getTid(), captured on the leaking thread - the noise
thread publishes its tid via the handoff) because production tagging
matches tracked instances by tid. gtests use fixed synthetic tids
(gate-only, no live heap).

## Verified

543 gtests (4 new: no-tid skip, flat-tid reject, retained-bar qualify,
rising-below-bar qualify); slow suite 8/8 including
LeakTagCorrelationReferenceChainTest's [correlation-found] through the
per-tid-scoped production tagging path; testDebug unchanged (5
pre-existing env failures).

## Inference (not verified) + commits

LeakingCacheScenario's CachedPayload allocations are far below the
allocation-sampling floor (300 small objects per round vs a ~512KiB
interval), so its chain most likely comes from the representative
machinery (seed-0 via setKlassPopulationRepresentativeForTest0), not
leak tagging - its main-tid seeding is therefore gate-only in practice.
Inferred from the sampling floor + the scenario passing with zero
interception mechanics observed; not directly instrumented.

Commits: 5d498811f (PriorityExpandSet), c5490156e (per-tid
qualification), 14add8140 (memory sync), pushed as
1a5055548..14add8140 on jb/reference-chains-pi.
