---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-06 18:42 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#111829645](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111829645) | ✅ | main | - |
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
| 2026-05-06 | Integration | [#111829645](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111829645) | main | - | ✅ |
| 2026-05-06 | Integration | [#111820037](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111820037) | main | - | ✅ |
| 2026-05-06 | Integration | [#111818795](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111818795) | main | - | ✅ |
| 2026-05-06 | Integration | [#111797455](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111797455) | main | - | ✅ |
| 2026-05-06 | Integration | [#111753153](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111753153) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
