---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-18 08:30 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#138394940](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138394940) | ✅ | main | - |
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
| 2026-09-18 | Integration | [#138394940](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138394940) | main | - | ✅ |
| 2026-09-18 | Integration | [#138394931](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138394931) | main | - | ✅ |
| 2026-09-18 | Integration | [#138394957](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138394957) | main | - | ✅ |
| 2026-09-18 | Integration | [#138385733](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138385733) | main | - | ✅ |
| 2026-09-18 | Integration | [#138385723](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138385723) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
