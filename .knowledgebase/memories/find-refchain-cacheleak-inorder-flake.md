---
id: find-refchain-cacheleak-inorder-flake
title: shouldReconstructReferrerChainThroughUnboundedCacheLeak flakes in-order, pre-existing
kind: finding
tags: [flaky-test, e2e, pr-921, pre-existing]
applies_to: [ddprof-test/src/test/java/com/datadoghq/profiler/referencechains/ReferenceChainTrackingTest.java]
source: writing-any-code-thoroughly/find-refchain-cacheleak-inorder-flake
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# shouldReconstructReferrerChainThroughUnboundedCacheLeak flakes in-order, pre-existing

Verified by stash-bisection (2026-10-29): the in-order failure ("Never observed a
datadog.ReferenceChain event whose chain[0] is CachedPayload after N cached entries
across up to 16 rounds") reproduces on the COMMITTED tree (aa527d27d) as well as on
the delta-fix tree - committed: 1 pass / 1 fail; delta: 3 fail / 1 isolated pass.
Passes reliably with -Ptests=...shouldReconstructReferrerChainThroughUnboundedCacheLeak
(single method, fresh JVM). The sphinx verify-v1 failure and the fix child's
repeated-run loop were chasing this flake, NOT a delta regression.

Tracked as PROF-16383 (filed 2026-10-29, assigned to the operator); linked from PR #921 via a CI-triage comment. Fix candidate noted in the ticket: force System.gc() per growth round + failure-message diagnostics.

Shape: heavy E2E leak scenario, shared no-forkEvery JVM, self-adjusting 16-round
budget, per-test stop()/start() (@AfterEach), population/hook state from the @Order(1)
GC-root test. Sensitive to machine load and in-class ordering. NOT addressed in this
PR (out of scope; separate follow-up if wanted).
