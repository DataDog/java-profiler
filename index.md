---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-03 12:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#135181660](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135181660) | ❓ | main | - |
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
| 2026-09-03 | Integration | [#135181660](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135181660) | main | - | ❓ |
| 2026-09-03 | Integration | [#135160317](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135160317) | main | - | ❓ |
| 2026-09-03 | Integration | [#135142723](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135142723) | main | - | ✅ |
| 2026-09-03 | Integration | [#135106644](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135106644) | main | - | ✅ |
| 2026-09-02 | Integration | [#135042431](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135042431) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
