---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-21 07:04 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#132316107](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132316107) | ✅ | main | - |
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
| 2026-08-21 | Integration | [#132316107](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132316107) | main | - | ✅ |
| 2026-08-21 | Integration | [#132295449](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132295449) | main | - | ✅ |
| 2026-08-20 | Integration | [#132191537](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132191537) | main | - | ✅ |
| 2026-08-20 | Integration | [#132177131](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132177131) | main | - | ✅ |
| 2026-08-20 | Integration | [#132172833](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132172833) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
