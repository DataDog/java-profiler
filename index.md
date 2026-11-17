---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-17 17:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#154029442](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154029442) | ❓ | main | - |
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
| 2026-11-17 | Integration | [#154029442](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154029442) | main | - | ❓ |
| 2026-11-17 | Integration | [#154013329](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154013329) | main | - | ✅ |
| 2026-11-17 | Integration | [#154013813](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154013813) | main | - | ❓ |
| 2026-11-17 | Integration | [#154005413](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154005413) | main | - | ✅ |
| 2026-11-17 | Integration | [#154008608](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154008608) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
