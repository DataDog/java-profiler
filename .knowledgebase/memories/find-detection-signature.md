---
id: find-detection-signature
title: Measured signature of the pattern: arena count above 8 x quota CPUs with ~1 attached thread per arena; free-held ratio alone does not discriminate
kind: finding
tags: [detection, measurement, arena, reproducer]
applies_to: []
source: malloc-arena-detection/find-detection-signature
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Measured signature of the pattern: arena count above 8 x quota CPUs with ~1 attached thread per arena; free-held ratio alone does not discriminate

## Reasoning chain
From 144 reproducer results (find-repro-arm64-results):
- Thread-private arenas: in the retained phase with T <= 64, walk_count = T + 2 and max_attached = 1 -> every
  allocating thread owns an arena. With a binding limit (ARENA_MAX 2/16) attached rises to 23-155 (all targets).
- Free-held ratio (sum_sys - in_use) / sum_sys is ~100% after frees in BOTH default and capped runs (2.39 mi2),
  so a ratio threshold cannot tell the pathological case from a healthy one. The discriminator is magnitude
  relative to what a quota-aware limit would retain: T=256 default / quota-aware(16) = 3.7x-9x across all targets.
- Hence the rule shape: (1) arena_count > 8 x ceil(quota CPUs) [config not quota-aware AND exercised], plus
  (2) sum of non-main system_mem large relative to the container memory limit. The percentage in (2) is a policy
  choice; the reproducer cannot calibrate it (workload-dependent per-thread peak).
- Remedy hint the event can carry: MALLOC_ARENA_MAX ~ 8 x quota CPUs (measured 4-9x lower retention).

## Evidence
- build/arena-repro/results/*.txt; summarize.py table.

## What this rules out
- A pure fragmentation-ratio detector (free/arena) as the arena-blowup signal.
- Requires attached_threads, present in all three calibrated layouts seen (absent only in upstream 2.17-2.22).
