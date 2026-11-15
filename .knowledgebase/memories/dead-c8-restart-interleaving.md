---
id: dead-c8-restart-interleaving
title: Reviewer's "Profiler::start() on restart vs GC thread" cgroup interleaving is unreachable
kind: dead-end
tags: [pr-797, os_linux, cgroup]
applies_to: []
source: feedback-1/dead-c8-restart-interleaving
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Reviewer's "Profiler::start() on restart vs GC thread" cgroup interleaving is unreachable

## Reasoning chain
Both writers of g_memory_limit_cgroup_path run once per process: SanityChecker via `static bool sanity_checked`
(profiler.cpp:1452) and initialize_table via `if (_initialized) return _stored_error` (livenessTracker.cpp:2122-2130).
A restart never re-runs them. The real window is the first gc_generations-enabled start after RC already enabled GC events.

## What this rules out
- Don't argue the race via restart; argue it via _initialized/_gc_generations publish-before-init ordering.

## Evidence
- evidence/C.md
