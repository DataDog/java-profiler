---
id: find-urgent-path-candidate-less-search
title: Second root cause: urgent-OOM latch authorized a candidate-less search (exposed by generations=true experiment)
kind: finding
tags: [reference-chains, urgent-oom, warmup, second-root-cause]
applies_to: []
source: writing-any-code-thoroughly/find-urgent-path-candidate-less-search
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Second root cause: urgent-OOM latch authorized a candidate-less search (exposed by generations=true experiment)

## Reasoning chain
Operator added `generations=true` to staging args; rec3
(~/Downloads/20261029-085919_prof-analyzer_AaGG44LTAABrEm9tdOyoPAAA/main.jfr,
agent 1.69.0-SNAPSHOT~2a7b8e49bb, gcGenerations=true, fresh watermark 262144/16.8MB
=> process restarted) still showed the collector churning. Discriminator:
`liveness_urgent_boost_admits = 2495` (0 in rec1/rec2) -> the urgent-OOM path,
not the short-circuit, authorized the search.

Mechanism (verified at v_1.52.1 tag - deployed binary contains the gate):
1. Fresh process -> heap floor rises during warmup -> secondsToOOM()'s linear
   extrapolation reads < 5 min -> isUrgent() latches -> one search entitled
   with NO candidate requirement (old hasLeakSignal urgent branch).
2. The search cannot exit early: completion requires a pass with no truncated
   work (referenceChainTraversal.cpp:1113 - every pass truncates on this heap),
   and the 30-pass no-progress abandonment is suppressed while urgent (:1140
   `!isUrgent()`).
3. Result: candidate-less whole-heap BFS to the auto-tuned TTL (up to 30 min);
   zero chains (nothing tagged), zero abandonments (RECORDING_END emits none).

## Fix (A+B, implemented 2026-10-29, uncommitted, same worktree change set)
- A: hasLeakSignal() returns selectLeakCandidates(probe,1) > 0 only - the
  urgent latch no longer entitles searches. _urgent_search_spent removed
  entirely (behaviorally dead). Urgency still drives the ramp (cadence, pause
  target, budget boost, 100% liveness admission) and suppresses the
  no-progress abandonment for legitimate candidate-driven searches.
- B: warmup guard in isUrgent() - a projection in the urgent band whose
  observation window (ring time span, new secondsToOOM(out_window) out-param)
  is shorter than OOM_URGENT_THRESHOLD_S (300s) neither latches nor touches
  the release counter. The 30-min ramp still sees the raw projection.
- Tests: WarmupShortWindowDoesNotLatchUrgency (new, B);
  UrgentLatchWithoutCandidateDoesNotStartSearch (rewrites
  UrgentOOMProjectionBypassesCandidateGate, which asserted the removed
  bypass); OomUrgencyTest project() reseated to 15s sample spacing (window
  435s >= 300s) and BFS CanaryStuck seeding to 60s spacing - short-window
  seedings would silently never latch under B.
- Docs: ReferenceChainsSignalsExplained.md (search gate = candidate only;
  warmup guard documented).

Verification: full :ddprof-lib:gtestDebug 1017 OK / 0 failed (2026-10-29).

## What this rules out
- "The fix from find-fix-leak-signal-gate was wrong" - it was correct for the
  gcGenerations=false signature; rec3 simply exercised the second, independent
  authorization path.
