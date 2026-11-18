---
id: find-parallel-urgent-timing
title: Parallel-session corroboration: urgent-latch timing, threshold split, and the stop sequence
kind: finding
tags: [urgent-oom, timing, threshold-split, parallel-session]
applies_to: []
source: writing-any-code-thoroughly/find-parallel-urgent-timing
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Parallel-session corroboration: urgent-latch timing, threshold split, and the stop sequence

## Reasoning chain
Operator's parallel investigation (gpt-6.1-sol subagent, two executed
reproducers; full write-up .../subagent-artifacts/108a93b9-*_jvm-investigator_output.md,
reproducers in /tmp/rc-investigation.JRtDyL) independently reached the urgent-
latch explanation and added timing detail:

- Threshold split matters: liveness_urgent_boost_admits counts admits during
  urgent tracking, which engages at secondsToOOM() < 1800s (OOM_RAMP_START_S);
  the candidate-free search entitlement used the < 300s bar
  (OOM_URGENT_THRESHOLD_S). The boost counter alone does not prove the 300s
  bar was crossed. (My rec3 read treats 2495 as the urgent episode marker;
  the split caveat is fair - the latch, not just the ramp, is what entitled
  the search.)
- secondsToOOM() needs only 10 GC samples and has NO JVM-age requirement.
  Reproduced with the compiled regression helpers: a 30-GC transient-growth
  profile projects 135s (-> latch); after plateau/reclaim the same helpers
  return -1. Startup growth passes the estimator.
- Episode shape in the recording: armed ~2m38s, stopped ~3m28s; old-gen
  collapse 8.9 -> 2.7 GB supports a transient warmup episode.
- Stop sequence: a completed search emits no abandonment event; TTL does not
  fit (auto-tunes to 30 min at 17 GiB); urgency release does not cancel a
  running search; the spent one-per-episode urgent entitlement blocked the
  restart once the signal decayed.

## Evidence
- Parallel session reproducers: /tmp/rc-investigation.JRtDyL
- Consistent with find-urgent-path-candidate-less-search's mechanism (search
  keeps RUNNING past the signal; restart gate blocks).

## Open questions
- The parallel session's "stop at ~3m28s" needs reconciling with my TTL-read
  (search RUNNING to recording end). Both explain zero abandonment events;
  the exact terminal path (COMPLETED vs RECORDING_END) is not pinned by
  counters alone. A DEBUG-build run with TEST_LOG would settle it.
