---
id: find-detector-rule
title: Detector rule: warn when arena_count > 8 x ceil(quota CPUs) AND non-main arenas hold more than P% (default 25%, override arenawarn=) of native headroom (memory limit - max heap)
kind: finding
tags: [detection, rule, arena, design, thresholds]
applies_to: []
source: malloc-arena-detection/find-detector-rule
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# Detector rule: warn when arena_count > 8 x ceil(quota CPUs) AND non-main arenas hold more than P% (default 25%, override arenawarn=) of native headroom (memory limit - max heap)

## Purpose (agreed with user 2026-10-26)
The warning reports ONE specific, fixable problem: glibc malloc holds a lot of native memory across many per-thread
arenas because its arena limit ignores the container CPU quota; remedy MALLOC_ARENA_MAX=N.
- Condition 1 = cause (limit not quota-aware AND exercised); condition 2 = relevance (headroom is only the yardstick
  for "material", NOT the subject of the warning); recommendedArenaMax = remedy.
- NOT a general low-native-memory warning (metaspace/stacks/direct buffers do not satisfy condition 1); NOT an OOM
  prediction.
- "Held" = arena system_mem (reserved), not in use. Free share only via optional freeHeldBytes when mallinfo2 is
  available (PROF-16350).

## Rule
Evaluated once per JFR chunk on the flush path (not signal context).

Inputs:
- `arena_count`, per-arena `system_mem` and `attached_threads`, `main` flag: lock-free arena walk with runtime
  layout calibration (find-arena-walk-safe, find-el7-layout-backport).
- `quota_cpus`: cgroup v2 `cpu.max` quota/period, else v1 `cpu.cfs_quota_us`/`cpu.cfs_period_us`.
- `mem_limit`: cgroup v2 `memory.max`, else v1 `memory.limit_in_bytes`.
- `arena_limit` and its source: `GLIBC_TUNABLES` glibc.malloc.arena_max, else `MALLOC_ARENA_MAX`, else
  8 x get_nprocs() (online CPUs, the value glibc uses).

Conditions (both required):
1. `arena_count > 8 x ceil(quota_cpus)` — the limit is not quota-aware AND the workload used the extra arenas.
2. `sum(system_mem of non-main arenas) > P% of native_headroom`, native_headroom = mem_limit - max_heap — the
   extra arenas hold a material share of the memory not reserved for the Java heap.
   Uses committed arena bytes, NOT the free-held ratio (find-detection-signature: that ratio is ~100% after frees
   in both bad and healthy runs).

Characterization reported with the warning (not a gate):
- `attached_threads` distribution: ~1 per arena = thread-private arenas, the many-threads x small-allocs pattern
  (reproducer: T <= 64 -> arena_count = T + 2, attached 1 on all targets; binding limit -> 23-155).
- Largest per-arena `system_mem` / `max_system_mem` (per-thread peak).

Remedy carried in the event: `MALLOC_ARENA_MAX = 8 x ceil(quota_cpus)` (reproducer, T=256: 4-9x less retained).

## Where the rule runs
Decision (user, 2026-10-26): evaluate the rule IN THE PROFILER and emit a dedicated structured warning JFR event
with the relevant details; do not rely on backend computation. Rationale: only the profiler knows input validity
(calibrated layout, walk status, attached_threads availability); evaluation cost is negligible (comparisons over
values already collected per chunk); one versioned, tested implementation.
Conditions agreed in the proposal:
- P is runtime-configurable (profiler argument, conservative default) — a hardcoded P needs an agent release per change.
- Raw inputs travel with the warning or in a lean stats event (arena_count, sums, largest arena, quota, mem limit,
  limit source, layout, walk status) — needed to debug false positives/negatives and to calibrate P.
- Edge-triggered emission: on condition entry, on worsening, on clearing — not one event per chunk.
- Not `profiler.Log` (jfrMetadata.cpp:425): free text only, and the Log::log -> JFR path is commented out
  (log.cpp:97); a structured event avoids backend string parsing.

## Degraded paths
- No CPU quota: condition 1 cannot exceed glibc's own limit, so the rule does not fire. Correct for the
  quota-mismatch case; plain many-thread blowup on an unconstrained host is NOT covered by this rule.
- No cgroup memory limit: physical RAM as mem_limit (memoryLimitSource=physical); headroom computed from it.
- Zing: walk turned off (no fault recovery there; q-zing-walk-safety) -> no warning, walkStatus=unsupported-jvm.
- Walk disabled (no calibrated layout passes, seed lands only in main_arena, unsupported allocator): no warning;
  the stats event reports walkStatus with the reason.
- `attached_threads` absent (upstream 2.17-2.22 layout): emit without the characterization.
- mallinfo2 unavailable (glibc < 2.33, or PROF-16350 unfixed): condition 2 falls back to committed non-main
  system_mem (may overstate reclaimable memory) -> PROF-16350 is a prerequisite for an accurate rule.

## Condition 2 measure (revised after JVM baseline, find-jvm-baseline)
- Use FREE-HELD bytes (mallinfo2 fordblks: reserved but not in use) as condition 2's numerator, not committed
  non-main system_mem: fewer arenas reclaim free space, not in-use bytes. x86_64 JDK8 http: committed 46.7 MiB
  (fires) vs free-held 26.5 MiB (silent at 32 MiB threshold). On aarch64/2.43 both are equal (2 MiB THP floor is
  free top space).
- Fallback without mallinfo2 (glibc < 2.33 or PROF-16350 unfixed): committed non-main system_mem, flagged in the event.
- mallinfo2 includes main_arena free space (not caused by arena count); accepted, condition 1 gates the cause.
- Condition 1 does not filter JVMs (arenas ~= threads > 8 x quota almost always); it remains the cause gate that
  guarantees MALLOC_ARENA_MAX would bind.

## Native headroom and threshold P (user, 2026-10-26: good default + override; heap defaults are not a basis, apps set -Xmx)
- max_heap = effective `Runtime.maxMemory()` (reflects -Xmx / MaxRAMPercentage / ergonomics), resolved ONCE at
  profiler start (JNIEnv available) and cached — fixed for process lifetime; no JNI on the flush path.
  Precedent: HeapUsage::getMaxHeap() (hotspot/vmStructs.cpp:1087), cached by the liveness tracker
  (livenessTracker.h:417). That helper is under hotspot/ -> shared detector code must use the JVM abstraction layer
  or call Runtime.maxMemory() via JNI itself (standard API on HotSpot/J9/Zing).
- mem_limit = cgroup limit, else physical RAM (sysinfo); memoryLimitSource reports which.
- Fallbacks: max_heap unknown or Long.MAX_VALUE -> headroom = mem_limit (headroomSource=limit-only);
  max_heap >= mem_limit -> headroom = mem_limit and heapExceedsLimit=true.
- Max (not committed) heap is correct: the heap may grow to max; the question is whether heap + native fits.
- Default P = 25% of native headroom; override `arenawarn=<percent>` (arguments.cpp style), `arenawarn=0` disables
  the warning, stats event stays. Policy default: headroom also holds metaspace, code cache, thread stacks, GC
  structures, direct buffers; stranded arenas from the quota mismatch should not take a quarter of it.
- Not measurable by the reproducer (no Java heap; per-thread peak is workload-specific). The rule is insensitive to
  the exact P because the two regimes differ 3.7-9x at T=256. Refine from datadog.MallocArenaStats, which must carry
  maxHeap and memoryLimit so headroom and P can be recomputed offline.
- Superseded earlier draft: 10% of the memory limit justified by JDK MaxRAMPercentage defaults — rejected (user):
  apps commonly set -Xmx explicitly, so heap defaults are not a valid basis.

## Events
- `datadog.MallocArenaWarning` (state raised/worsened/cleared; rule inputs; thresholdPercent; threadPrivateArenas,
  largest arena; recommendedArenaMax; glibcVersion, layout, walkStatus).
- `datadog.MallocArenaStats` lean per-chunk raw values for every process where the walk runs.
- Hysteresis: `worsened` when nonMainArenaBytes grows >= 25% over the last emitted warning; `cleared` when either
  condition turns false.

## Evidence
- Implementation ticket: PROF-16351 (2026-10-26), full design + open questions.
- build/arena-repro/results/*.txt (144 results, 6 targets), summarize.py; doc/temp/MallocArenaDetectionOptions.md
  "Detection signature" (worktree start-cairn-investigation).

## What this rules out
- A fragmentation-ratio detector; a version-table-only walk; gating on mallinfo2.
