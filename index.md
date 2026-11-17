---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-17 16:50 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#154005413](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154005413) | ✅ | main | - |
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
| 2026-11-17 | Integration | [#154005413](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154005413) | main | - | ✅ |
| 2026-11-17 | Integration | [#154008608](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154008608) | main | - | ❓ |
| 2026-11-17 | Integration | [#154006641](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154006641) | main | - | ❓ |
| 2026-11-17 | Integration | [#153992944](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153992944) | main | - | ✅ |
| 2026-11-17 | Integration | [#153987504](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153987504) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
