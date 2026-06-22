---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-22 18:48 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#120301626](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120301626) | ❌ | main | - |
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
| 2026-06-22 | Integration | [#120301626](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120301626) | main | - | ❌ |
| 2026-06-22 | Integration | [#120231530](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120231530) | main | - | ❌ |
| 2026-06-22 | Integration | [#120147655](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120147655) | main | - | ❌ |
| 2026-06-22 | Integration | [#120122211](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120122211) | main | - | ❌ |
| 2026-06-22 | Integration | [#120118410](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120118410) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
