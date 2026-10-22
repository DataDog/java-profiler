---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-22 20:56 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#146881944](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146881944) | ✅ | main | - |
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
| 2026-10-22 | Integration | [#146881944](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146881944) | main | - | ✅ |
| 2026-10-22 | Integration | [#146881183](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146881183) | main | - | ✅ |
| 2026-10-22 | Integration | [#146853468](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146853468) | main | - | ✅ |
| 2026-10-22 | Integration | [#146808596](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146808596) | main | - | ✅ |
| 2026-10-22 | Integration | [#146803741](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146803741) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
