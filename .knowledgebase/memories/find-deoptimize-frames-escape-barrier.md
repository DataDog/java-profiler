---
id: find-deoptimize-frames-escape-barrier
title: IterateOverReachableObjects forces EA-object materialization: 626 DeoptimizeFrames proven, not GetObjectsWithTags
kind: finding
tags: [hotspot, jvmti, escape-analysis, deoptimization, cost-model, parallel-session]
applies_to: [ddprof-lib/src/main/cpp/referenceChains.cpp]
source: writing-any-code-thoroughly/find-deoptimize-frames-escape-barrier
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# IterateOverReachableObjects forces EA-object materialization: 626 DeoptimizeFrames proven, not GetObjectsWithTags

## Reasoning chain
Parallel session PROVED (earlier hand-waving corrected) the source of the 626
DeoptimizeFrames in the recording:

- Path: IterateOverReachableObjects (BFS root enumeration) -> HotSpot
  JvmtiTagMap -> EscapeBarrier -> materializes EA-optimized (scalar-replaced)
  objects across ALL threads -> Deoptimization::deoptimize_frame per eligible
  frame -> posts VM_DeoptimizeFrame, then HeapWalkOperation. Verified in
  jdk-27+35 source (escapeBarrier.cpp -> deoptimize_frame,
  deoptimization.cpp:1553).
- Reproduced standalone (Temurin 26): each enumeration = 1 global handshake
  (HandshakeAllThreads) + 8 deopts + 1 walk; with -XX:-DoEscapeAnalysis:
  0 deopts. GetObjectsWithTags is NOT the source.
- Only frames holding objects that DO NOT EXIST ON THE HEAP are affected:
  scalar-replaced allocations (object lives only in registers/stack slots of
  the compiled frame) or locked-in-compiled-frame monitors. Normal frame-held
  oops are walked directly - those threads are untouched.
- Deopt semantics: per-frame, per-activation. The killed activation continues
  interpreted until it returns (hot loop: OSR rescues after ~10k+ backedges +
  compile latency). The nmethod stays valid - subsequent invocations enter
  compiled code directly, NO re-warmup, no recompilation storm. This is NOT
  jdk.Deoptimization (uncommon trap): no speculation failure, no method
  invalidation.
- Recurrence shape: each enumeration pass re-materializes whatever
  EA-optimized frames are live at that moment, so ~5 passes/s during warmup
  re-deopts a fresh batch (~48 eligible frames per handshake observed) on an
  EA-heavy C2 workload like prof-analyzer (446 threads).
- Measured: 626 ops / 0.24 ms total VM-op time - the deopts themselves are
  cheap; the real cost is the 13 global handshakes plus the interpreter dip
  for each killed frame's remaining lifetime. 253 HeapWalks during the ~50s
  episode each paid handshake + deopt batch.

## Evidence
- Parallel-session reproducers: /tmp/rc-investigation.JRtDyL (Temurin 26
  standalone: handshake/deopt/walk counts, +/-EscapeAnalysis).

## What this rules out
- GetObjectsWithTags as the DeoptimizeFrame source.
- Recompilation-storm theories: forced per-frame materialization deopts do
  not invalidate nmethods.

## Cost implication for the fix sizing
Every candidate-less or not, each BFS pass pays handshake + deopt batch -
bounding pass counts (the TTL/no-progress exits) bounds this cost; the
candidate-gate fixes (A/B) do exactly that by preventing pointless searches.
