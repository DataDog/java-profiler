---
id: find-refchains-architecture-verified
title: Reference-chain collection architecture end-to-end verified against code (worktree java-profiler-rc-6-java-tests, 2026-10-13)
kind: finding
tags: [java-profiler, reference-chains, liveness-tracker, architecture, verified]
applies_to: []
source: user-invoked-sphinx-arguments/find-refchains-architecture-verified
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Reference-chain collection architecture end-to-end verified against code (worktree java-profiler-rc-6-java-tests, 2026-10-13)

## Reasoning chain
LivenessTracker (allocation-sampled per-klass population rings, ring=30, min-fill=10,
hysteresis 5/3) nominates ≤5 leak-candidate klasses and tags tracked instances with
leak tags (`tagLeakInstances()`); ReferenceChainTracker runs a dedicated BFS agent
thread (~1 s loop). Pass gates: safepoint pain budget drained AND leak signal (or OOM
urgent <5 min, latched, 1 search/episode). Pass = IterateOverReachableObjects root/stack-ref
enum (first pass, then every ≥2 s / after truncation, budget ≈10× per-pass) + chunked
static-field sweep (admitStaticFieldRoots, 512-class chunks) + batched per-holder
FollowReferences expansion (batch 8–512 AIMD) + fair-rotation re-walks. Guardrails:
PID pause pacing (50 ms target), borrow (5 passes ≤½ target → +25%/pass up to 4×),
CPU pain budget (1% wall clock), TTL 60 s, frontier cap 65 536, hop cap 200,
no-progress 30 passes, canary-stuck 30×2ᵏ, OOM urgency ramp (30 min→OOM: pause→100 ms,
cadence→10 ms, budget ×4). Reconstruction runs per pass on the engine thread
(pollWatchedTargets → buildChainEvent → cache, ≤128 keyed by instance tag);
dump-time emission is a snapshot (re-emitted every chunk), abandoned searches emit
datadog.ReferenceChainAbandoned.

## Evidence
- ddprof-lib/src/main/cpp/referenceChains.h (constants, gate fields), referenceChains.cpp
  (shouldRunPass/canAffordNewSearch/isUrgent/threadLoop, autoTuneDefaults at :179-229)
- referenceChainTraversal.cpp (runPass :994-1230, updatePacing :1240, expansion)
- referenceChainEvents.cpp (pollWatchedTargets :145, buildChainEvent, cache)
- profiler.cpp :1856/:2052 (dump/stop drains), flightRecorder.cpp :2770, jfrMetadata.cpp :209-235
