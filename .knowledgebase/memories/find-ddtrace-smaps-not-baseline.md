---
id: find-ddtrace-smaps-not-baseline
title: dd-trace-java smaps events are opt-in, JDK 23+ only, and do not identify malloc arenas
kind: finding
tags: [dd-trace-java, smaps, jfr, always-on]
applies_to: []
source: malloc-arena-detection/find-ddtrace-smaps-not-baseline
status: active
recorded: 2026-11-02
valid_at: 2026-11-02
---



# dd-trace-java smaps events are opt-in, JDK 23+ only, and do not identify malloc arenas

## Reasoning chain
dd-trace-java (HEAD c3ea2067) emits `datadog.SmapEntry` (one event per mapping, @Period beginChunk) and
`datadog.AggregatedSmapEntry` (rss summed by nmtCategory). Both default off
(`profiling.smap.collection.enabled`, `profiling.smap.aggregation.enabled`). Registration requires Linux, non-J9,
not Oracle JDK8, and the `System.map` DiagnosticCommand (JDK 23+). Classification is by exact start address
against System.map descriptions; arena heaps land in UNKNOWN/UNDEFINED. No 64MB-alignment/PROT_NONE heuristic.
Pure Java, no ddprof involvement.

## Evidence
- profiling-controller-openjdk/.../events/SmapEntryEvent.java:14-18, AggregatedSmapEntryEvent.java:14,36-39
- SmapEntryCache.java:41,154-271,274-309; ProfilingConfig.java:252-260; SmapEntryFactory.java:27-58; OpenJdkController.java:250-271

## What this rules out
- Using smaps as the always-on detection baseline (off by default, JDK>=23).
- Still useful as offline confirmation: when enabled, per-mapping data lets a backend count 64MB-aligned anon
  regions (arena heaps) post hoc — a complementary, not primary, signal.
