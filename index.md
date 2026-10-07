---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-07 11:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#143008521](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143008521) | ✅ | main | - |
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
| 2026-10-07 | Integration | [#143008521](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143008521) | main | - | ✅ |
| 2026-10-07 | Integration | [#143007026](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143007026) | main | - | ✅ |
| 2026-10-07 | Integration | [#142989409](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142989409) | main | - | ❓ |
| 2026-10-07 | Integration | [#142984400](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142984400) | main | - | ⚠️ |
| 2026-10-07 | Integration | [#142947131](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/142947131) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
