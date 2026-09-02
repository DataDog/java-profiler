---
id: find-default-live-samples-ratio-lottery
type: finding
status: fixed
depends_on: [ev-leaktag-correlation-local-repro, find-per-tid-qualification-design]
related: [ev-leaktag-onpod-round4, find-test-seam-aliasing]
tags: [fix, livenessTracker, tests, flakiness, sampler, NEW-THIS-SESSION]
created: 20260901
updated: 20260901
---

# The intermittent "sampler-dead" suite failures were the default 10% live-sample ratio lottery

## The failure (mis-named "sampler dead")

Intermittently (suite-only at first glance, ~2 of 7 full-suite runs,
both LeakTagCorrelation children failing together some runs), the
leak-correlation child JVM produced zero leak tagging: zero folds
with leak-klass scratch, tagLeakInstances matched nothing, result
[correlation-tag-out-of-pool]/NOT_FOUND. Isolated reruns always
passed. Looked environmental (machine load).

## Root cause (instrumented, then code-proven)

`memory=64:l` without an explicit ratio leaves
`Arguments::_live_samples_ratio` at its default **0.1**
(arguments.h: "default to liveness-tracking 10% of the allocation
samples"). LivenessTracker::track() drops each tracked instance with
p=0.9 (the `skipped` accumulator compensates in JFR weights - fine
for volume workloads, silent for tiny cohorts).

The leak-correlation scenario's leak cohort is ~35-50 1MB chunks -
P(zero survivors) lands in the observed few-percent tail, and the
per-run pass/fail was literally this lottery. The scenario's own
comment ("every allocation is sampled, tracked, and taggable") was
never true under the default. The passing runs' stable "tagged=5"
is exactly the ~10% of ~50 chunks.

Instrumentation (now fully reverted) pinned it: track() entries
showed the chunks arriving, zero subsample-DROP logs with an
explicit ratio, and the class-id red herrings (cached_klass_id=0,
id namespace 1-vs-2) dissolved once the cohort actually survived
to be resolved.

## Fix

LeakTagCorrelationReferenceChainTest now passes
`memory=64:l:1.0` (arguments.cpp parses the third segment as the
live-sample ratio, clamped [0.01,1.0]) with a comment explaining
the lottery. Verified: post-fix suite runs show zero
leak-correlation failures, correlation-found every time.

Follow-up: the same explicit `:l:1.0` was applied to the other three
`:l`-without-ratio reference-chain sites (ReferenceChainTrackingTest's
shared config; both ExternalProcessReferenceChainTest children) -
removes the silent probabilistic default from every reference-chain
test and matches the scenarios' documented "every allocation is
tracked" intent. Effect on the TrackingTest scenarios: the
"representative could not be resolved (died/evicted)" symptom is GONE
(10x thicker rep pool), but the ToGcRoot chase-pacing flakiness is NOT
this bug - see q-togcroot-acceptance-paths.

## Why NOT the pod

The pod's `--preset cpu_live_heap` also uses the default ratio, but
the simulated-leak thread allocates continuously - a 90% drop just
subsamples a large population (round 4's stable "tagged=5 need_set=0"
tags). The lottery only bites cohorts of tens. No pod change needed.

## Remaining known flaky family (separate, NOT this bug)

ReferenceChainTrackingTest ToGcRoot/UnboundedCache still fail under
heavy machine load (observed at load 25-55; the in-process executor
JVM's passes run ~4.4s under the 5s pausetarget, and the canary
backoff spaces the chase by design - see
find-canary-lane-backoff-design). Load-sensitive timing, not the
ratio lottery.
