---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-20 16:31 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#132177131](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132177131) | ✅ | main | - |
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
| 2026-08-20 | Integration | [#132177131](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132177131) | main | - | ✅ |
| 2026-08-20 | Integration | [#132172833](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132172833) | main | - | ✅ |
| 2026-08-20 | Integration | [#132143309](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132143309) | main | - | ✅ |
| 2026-08-20 | Integration | [#132127934](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132127934) | main | - | ✅ |
| 2026-08-20 | Integration | [#132123098](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132123098) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
