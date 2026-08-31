---
id: ev-leaktag-correlation-local-repro
type: evidence
status: verified
related: [find-rotation-resize-blindspot, find-gate-bypass-representative-paths, find-klass-id-notation-mismatch, find-test-seam-aliasing, find-ema-batch-collapse, find-leak-tag-pool-implementation]
tags: [local-repro, E2E, post-fix, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# Local repro (LeakTagCorrelationScenario) - build + debugging trail

The hotdog deployment loop replaced by a local E2E:
`ddprof-test/.../referencechains/LeakTagCorrelationScenario` +
`ExternalLauncher` mode `leak-correlation` +
`LeakTagCorrelationReferenceChainTest` (slow suite, ~2min). Child JVM:
static growing List leak (1MB byte[] chunks), ephemeral stack-local
NoisePayload churn on a noise thread, ~100k FillerNode scale graph.
Asserts: in-pool targetTag == a byte[] HeapLiveObject's leakTag, durable
root, depth>=1, no transient-rooted shallow chains, no NoisePayload
chains. Failing runs embed a filtered child TEST_LOG tail in the
assertion message (queue depths, gotw batches, interception lines).

## What the harness peeled apart, in order

1. Run 1: `NoisePayload@depth0:static_field` chain - the fixture held the
   noise rep in a static field (truthful output; fixed the fixture).
2. Run 2: `NoisePayload@depth1:first_observed_via:stack_local` chain
   EMITTED -> the canary/rep path gate bypass (real bug, fixed).
3. Depth-0 durable chains suppressed by the round-4 gate -> predicate
   corrected (design flaw, fixed).
4. Slow-suite run: 3 scenarios broken since the redesign -> synthetic-id
   seam breakage -> aliasing seam (fixed; LeakingCache + StaticField +
   in-process gcRoot/cache tests green again).
5. `tagged=0` forever for synthetic ids; then real-id candidates but
   `resolveClassMap` ChainLink id 2 vs LT candidate id 63 -> dot/slash
   notation bug (production, fixed).
6. Tagging selection: 288B payloads flaked (sampling-dependent);
   300KB companion arrays sampled the ARRAY not the payload (companion
   steals sampling - exactly CachedPayload's documented warning). Fix:
   the leaked object IS the big allocation (1MB byte[] chunks) + scan
   every 3rd round (JMC parse churn was evicting chunks from the tracking
   table before they aged into tagging priority). Result: `tagged` lines
   show size=1000016, ages accumulating - tagging deterministic.
7. Zero interceptions with everything above: fixed-slot array still 0 ->
   the resize-blindspot series (fair-share, hygiene, ancestor fanout,
   requeueChainRootForRotation). After all four: 4 interceptions at
   depth 2 under the live elementData, correlated discoveries recorded
   with noise eviction.
8. Last-mile found: the byte[] candidate dropped (hysteresis aging) right
   after the interceptions -> per-round seeding added to the scenario
   (find-test-seam-aliasing). FINAL RUN RESULT PENDING - the verification
   run was interrupted by the checkpoint; re-run first thing next session.

Also verified locally: proportional batch control behaves on a real JVM
(batch 270, next 512, gotw 16-18ms) and the fair-share lane drain +
`filtered depth=1 root_kind=24` gate lines fire in a real run.
