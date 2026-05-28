---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-28 21:35 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#115779973](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115779973) | ❓ | main | - |
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
| 2026-05-28 | Integration | [#115779973](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115779973) | main | - | ❓ |
| 2026-05-28 | Integration | [#115770768](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115770768) | main | - | ❌ |
| 2026-05-28 | Integration | [#115773404](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115773404) | main | - | ❓ |
| 2026-05-28 | Integration | [#115767050](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115767050) | main | - | ❌ |
| 2026-05-28 | Integration | [#115757985](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115757985) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
