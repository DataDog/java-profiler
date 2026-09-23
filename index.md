---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-23 11:21 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#139437807](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139437807) | ✅ | main | - |
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
| 2026-09-23 | Integration | [#139437807](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139437807) | main | - | ✅ |
| 2026-09-23 | Integration | [#139433476](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139433476) | main | - | ✅ |
| 2026-09-23 | Integration | [#139412222](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139412222) | main | - | ✅ |
| 2026-09-23 | Integration | [#139409168](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139409168) | main | - | ⚠️ |
| 2026-09-23 | Integration | [#139378206](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139378206) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
