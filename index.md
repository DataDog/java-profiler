---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-20 10:39 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#155103855](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155103855) | ✅ | main | - |
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
| 2026-11-20 | Integration | [#155103855](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155103855) | main | - | ✅ |
| 2026-11-20 | Integration | [#155094765](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155094765) | main | - | ✅ |
| 2026-11-20 | Integration | [#155090802](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155090802) | main | - | ✅ |
| 2026-11-20 | Integration | [#155084362](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155084362) | main | - | ✅ |
| 2026-11-19 | Integration | [#154989725](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154989725) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
