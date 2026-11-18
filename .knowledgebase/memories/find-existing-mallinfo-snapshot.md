---
id: find-existing-mallinfo-snapshot
title: A process-wide mallinfo2() snapshot already runs on every JFR chunk finish, independent of nativemem
kind: dead-end
tags: [mallinfo, counters, always-on, existing-infra]
applies_to: []
source: malloc-arena-detection/find-existing-mallinfo-snapshot
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# A process-wide mallinfo2() snapshot already runs on every JFR chunk finish, independent of nativemem

## Reasoning chain
`Recording::finishChunk` path calls `updateNativeMemStats()` (ddprof-lib/src/main/cpp/flightRecorder.cpp:1082) which calls
`updateMallocArenaStats()` (ddprof-lib/src/main/cpp/flightRecorder.cpp:2214). That calls `mallinfo2()` (2170) when glibc >= 2.33 headers
(DD_HAVE_MALLINFO2, ddprof-lib/src/main/cpp/flightRecorder.cpp:13-17) and `glibcMallocActive()` (no `mallctl`/`tc_malloc_size`, not ASan/TSan).
Published as internal counters (Counters::set, compiled in for all Linux/macOS configs incl. release via -DCOUNTERS, build-logic/conventions/src/main/kotlin/com/datadoghq/native/config/ConfigurationPresets.kt:93): MALLOC_ARENA_BYTES (mi.arena), MALLOC_IN_USE_BYTES (uordblks), MALLOC_FREE_HELD_BYTES (fordblks),
MALLOC_TRIMMABLE_BYTES (keepcost), MALLOC_MMAP_BYTES (hblkhd) -> writeCounters() (ddprof-lib/src/main/cpp/flightRecorder.cpp:1083,2296) emits one `datadog.ProfilerCounter` event (startTime,name,count; ddprof-lib/src/main/cpp/jfrMetadata.cpp:344) per counter per chunk; also readable via JavaProfiler.getDebugCounters() (ddprof-lib/src/main/java/com/datadoghq/profiler/JavaProfiler.java:444). This is the profiler's internal diagnostics table, not a user-facing signal. Added in #759 (2b4ace6c7).
So the "always-on cheap poll" baseline exists; the cost was already accepted at once-per-chunk cadence.

## Evidence
- ddprof-lib/src/main/cpp/flightRecorder.cpp:2159-2161 comment: mallinfo2 walks every arena taking each lock; flush path only.
- ddprof-lib/src/main/cpp/flightRecorder.cpp:2178-2182 Counters::set(...)
- Gap: no arena COUNT, no per-arena distribution, no thread-count correlation, no attribution; built only against glibc>=2.33 headers.
- Possible doc inaccuracy to verify: comment at 2171 says `arena` = "bytes obtained from the OS via brk"; glibc int_mallinfo sums system_mem over ALL arenas (pending glibc-source check).

## What this rules out
- Building a new mallinfo poller from scratch: the detector should extend this snapshot, not duplicate it.
