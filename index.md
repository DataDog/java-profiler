---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-03 11:36 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#122559979](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122559979) | ❌ | main | - |
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
| 2026-07-03 | Integration | [#122559979](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122559979) | main | - | ❌ |
| 2026-07-03 | Integration | [#122557100](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122557100) | main | - | ❓ |
| 2026-07-03 | Integration | [#122547356](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122547356) | main | - | ❌ |
| 2026-07-03 | Integration | [#122543319](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122543319) | main | - | ❌ |
| 2026-07-03 | Integration | [#122542106](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122542106) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
