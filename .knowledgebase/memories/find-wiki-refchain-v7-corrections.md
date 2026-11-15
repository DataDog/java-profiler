---
id: find-wiki-refchain-v7-corrections
title: Wiki "Reference Chain Collection" (page 6973555518) corrected to v7 — v6 had 3 wrong claims
kind: finding
tags: [java-profiler, reference-chains, confluence, documentation]
applies_to: []
source: user-invoked-sphinx-arguments/find-wiki-refchain-v7-corrections
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Wiki "Reference Chain Collection" (page 6973555518) corrected to v7 — v6 had 3 wrong claims

## Reasoning chain
Confluence page v6 (2026-07-14) vs code audit found: (1) first pass described as
whole-heap FollowReferences(0,nullptr,nullptr) — actual first pass is
IterateOverReachableObjects root/stack-ref enum + chunked static-field sweep;
(2) output path wrong — enqueueChainEvent()/Profiler::writeReferenceChain() and
"drain from runPass()" no longer exist; actual: per-pass cacheResolvedChain into
_resolved_chains (≤128, keyed by instance tag), dump/stop-time snapshot via
drainPendingChainEvents (snapshot, not drain; re-emitted every chunk),
FlightRecorder::recordReferenceChain, datadog.ReferenceChainAbandoned events;
(3) budget story incomplete — _pain_budget is now _safepoint_pain_budget +
_cpu_pain_budget, plus PID pacing/borrow/cutoffs/urgency ramp missing.
Component 1 (LivenessTracker knobs) was verified correct and left untouched.
v7 published 2026-10-13 with these corrections; page structure preserved.

## Evidence
- Confluence page update accepted, version.number=7, versionMessage names the 3 corrections
- jfrMetadata.cpp:209 (datadog.ReferenceChain), :224 (ReferenceChainAbandoned)
- profiler.cpp:1856/2052 (dump/stop drains), flightRecorder.cpp:2770
