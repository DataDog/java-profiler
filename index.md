---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-18 09:30 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#119643846](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119643846) | ❌ | main | - |
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
| 2026-06-18 | Integration | [#119643846](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119643846) | main | - | ❌ |
| 2026-06-18 | Integration | [#119642982](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119642982) | main | - | ❌ |
| 2026-06-18 | Integration | [#119635501](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119635501) | main | - | ❌ |
| 2026-06-18 | Integration | [#119605709](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119605709) | main | - | ❌ |
| 2026-06-17 | Integration | [#119561196](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119561196) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
