---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-23 19:40 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#120595380](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120595380) | ❌ | main | - |
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
| 2026-06-23 | Integration | [#120595380](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120595380) | main | - | ❌ |
| 2026-06-23 | Integration | [#120585063](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120585063) | main | - | ❌ |
| 2026-06-23 | Integration | [#120551285](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120551285) | main | - | ❌ |
| 2026-06-23 | Integration | [#120517513](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120517513) | main | - | ❌ |
| 2026-06-23 | Integration | [#120497023](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120497023) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
