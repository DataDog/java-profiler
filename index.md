---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-07 04:52 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#111911314](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111911314) | ✅ | main | - |
| [Benchmarks](benchmarks/) | - | - | - | - |
| [Reliability](reliability/) | - | - | - | - |

---

## Test Types

### Integration Tests
dd-trace-java compatibility tests verifying profiler works correctly with the Datadog tracer.
Tests run on every main branch build across multiple JDK versions and platforms.

### Benchmarks
Performance regression testing using Renaissance benchmark suite.
Compares profiler overhead against baseline (no profiling).

### Reliability Tests
Long-running stability tests checking for memory leaks and crashes.
Tests multiple allocator configurations (gmalloc, tcmalloc, jemalloc).

---

## Recent Runs (All Types)

| Date | Type | Pipeline | Branch | PR | Status |
|------|------|----------|--------|-----|--------|
| 2026-05-07 | Integration | [#111911314](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111911314) | main | - | ✅ |
| 2026-05-06 | Integration | [#111889969](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111889969) | main | - | ✅ |
| 2026-05-06 | Integration | [#111841865](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111841865) | main | - | ⚠️ |
| 2026-05-06 | Integration | [#111830786](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111830786) | main | - | ✅ |
| 2026-05-06 | Integration | [#111829645](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111829645) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
