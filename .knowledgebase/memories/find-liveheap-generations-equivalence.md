---
id: find-liveheap-generations-equivalence
title: generations and liveheap drive the same liveness mechanisms; liveheap additionally preserves stack traces
kind: finding
tags: [liveness, generations, liveheap, semantics]
applies_to: [ddprof-lib/src/main/cpp/arguments.cpp]
source: writing-any-code-thoroughly/find-liveheap-generations-equivalence
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# generations and liveheap drive the same liveness mechanisms; liveheap additionally preserves stack traces

## Reasoning chain
Operator-stated semantics, verified against source. `memory=<interval>b:l|L`
sets `_record_liveness` (+`_record_heap_usage` for 'L'); `generations=` sets
`_gc_generations`. Both flags feed `ObjectSampler::onSample ->
LivenessTracker::track()` (objectSampler.cpp:151). The leak-signal machinery —
per-klass population table (cleanup_table population accumulation,
livenessTracker.cpp:278/362), heap-floor ring (onGC, :2538), secondsToOOM()
(:1574), maybeForceCleanup() (:2482) — was gated on `_gc_generations` alone,
which is why liveheap-only deployments produced HeapLiveObject samples but
never filled the population table.

Per the operator: EITHER option allows constructing the population-trend
signal; liveheap = generations + stacktrace preservation for live samples.
The documented intent "liveheap profiles imply generations" did not exist in
the native parser before this fix.

## Evidence
- arguments.cpp:200-260 (memory option), 282-291 (generations option)
- livenessTracker.cpp:2096-2104 (initialize: both flags read)
- Verified the agent side (dd-trace-java@jb/reference_chains e188d0ff7f +
  158078255f) forces `generations=true` when reference chains are enabled —
  but the deployed runtime recorded gcGenerations=false anyway.

## What this rules out
- "Missing generations flag is only an agent wiring problem" — the native
  parser had no coupling either; the profiler must treat either source as
  sufficient.
