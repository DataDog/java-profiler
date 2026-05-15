---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-15 10:39 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#113345608](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113345608) | ❌ | main | - |
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
| 2026-05-15 | Integration | [#113345608](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113345608) | main | - | ❌ |
| 2026-05-15 | Integration | [#113343714](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113343714) | main | - | ❌ |
| 2026-05-15 | Integration | [#113340639](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113340639) | main | - | ✅ |
| 2026-05-15 | Integration | [#113326802](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113326802) | main | - | ❌ |
| 2026-05-14 | Integration | [#113230770](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113230770) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
