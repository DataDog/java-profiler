---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-18 09:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#131525874](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131525874) | ✅ | main | - |
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
| 2026-08-18 | Integration | [#131525874](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131525874) | main | - | ✅ |
| 2026-08-18 | Integration | [#131517982](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131517982) | main | - | ✅ |
| 2026-08-18 | Integration | [#131517979](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131517979) | main | - | ✅ |
| 2026-08-18 | Integration | [#131517980](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131517980) | main | - | ⚠️ |
| 2026-08-18 | Integration | [#131517864](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131517864) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
