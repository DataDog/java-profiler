---
id: find-recommended-design
title: Minimal always-on arena-blowup detector = repaired mallinfo2 + static arena-limit risk + lock-free arena walk, emitted as a dedicated JFR event
kind: finding
tags: [design, arena, synthesis]
applies_to: []
source: malloc-arena-detection/find-recommended-design
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Minimal always-on arena-blowup detector = repaired mallinfo2 + static arena-limit risk + lock-free arena walk, emitted as a dedicated JFR event

## Reasoning chain
- hyp-mallinfo-poll: mallinfo2 is acceptable only at JFR-chunk cadence; totals only. Currently dead in release (PROF-16350) -> option C (repair) is a prerequisite.
- hyp-static-risk-score: arena limit = 8 x online CPUs, cgroup quota ignored -> option A flags the precondition at negligible cost.
- hyp-arena-list-walk: lock-free, memory-safe, self-validating via (mstate)(heap_info+1) -> option B gives arena count and per-arena committed bytes/attached threads without hooks.
- hyp-ptr-arena-attribution + hyp-mmap-threshold-drift: attribution and drift need nativemem samples -> optional layer after PROF-16349 (find-hook-global-cas).
- q-output-surface: user decided on a dedicated event (draft datadog.MallocArenaStats, optional datadog.MallocArena).

## Evidence
- Synthesis document: <worktree start-cairn-investigation>/doc/temp/MallocArenaDetectionOptions.md
- Tickets: PROF-16349 (per-thread nativemem countdown), PROF-16350 (runtime mallinfo2).

## What this rules out
- smaps as baseline (find-ddtrace-smaps-not-baseline), free hook (hyp-cross-thread-free), always-on hooks (hyp-hooks-always-on).
- Open: thresholds unvalidated (needs native reproducer on glibc 2.17/2.28/2.39, x64+aarch64); RHEL backports of malloc_state unverified.
