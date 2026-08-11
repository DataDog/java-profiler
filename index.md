---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-11 15:48 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#130226247](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130226247) | ⚠️ | main | - |
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
| 2026-08-11 | Integration | [#130226247](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130226247) | main | - | ⚠️ |
| 2026-08-11 | Integration | [#130206116](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130206116) | main | - | ❓ |
| 2026-08-11 | Integration | [#130194586](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130194586) | main | - | ✅ |
| 2026-08-11 | Integration | [#130187695](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130187695) | main | - | ✅ |
| 2026-08-11 | Integration | [#130184460](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130184460) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
