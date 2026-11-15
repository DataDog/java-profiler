---
id: find-arena-limit-ignores-cgroup
title: glibc's arena limit is 8 x online CPUs (__get_nprocs), ignoring cgroup CPU quota; arenas are never freed
kind: finding
tags: [glibc, arena_max, container]
applies_to: []
source: malloc-arena-detection/find-arena-limit-ignores-cgroup
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# glibc's arena limit is 8 x online CPUs (__get_nprocs), ignoring cgroup CPU quota; arenas are never freed

## Reasoning chain
__get_nprocs() in 2.17 (arena.c:848), 2.28 (:888), 2.39 (:834) reads online CPUs; 2.35-2.38 used affinity (per glibc agent; reverted BZ 30945). Overridable via MALLOC_ARENA_MAX / glibc.malloc.arena_max. A 2-CPU-quota container on a 96-core host may create 768 arenas.

## Evidence
- Full derivation and citations in hyp-static-risk-score and evidence/ev-glibc-source-answers.md.

## What this rules out
- See hyp-static-risk-score.
