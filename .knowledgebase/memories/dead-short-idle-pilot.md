---
id: dead-short-idle-pilot
title: An enabled but idle reference-chain collector is not an active-cost baseline
kind: dead-end
tags: [reference-chains, experiment, activation, liveness]
applies_to: [ddprof-lib/src/main/cpp/livenessTracker.cpp:maybeForceCleanup]
source: refchain-fragmentation/dead-short-idle-pilot
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


An allocation/fragmentation comparison between collector-on and collector-off needs proof of ACTIVE work, not merely an enabled setting: with no periodic dump, the collector can sit at zero candidates (LivenessTracker::maybeForceCleanup uses a 30-second fallback interval, and many GCs do not establish a folded population history). With identical periodic production dumps in both arms, candidates appear naturally and chain events fire.

Use candidate/traversal counters and emitted chain events as activity evidence. Frontier gauges alone are insufficient across recordings: Profiler::start resets counters while the backing table survives without reallocating, so a zero capacity counter does not establish an idle search.
