---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-18 15:31 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#119750883](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119750883) | ❌ | main | - |
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
| 2026-06-18 | Integration | [#119750883](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119750883) | main | - | ❌ |
| 2026-06-18 | Integration | [#119740669](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119740669) | main | - | ❌ |
| 2026-06-18 | Integration | [#119733564](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119733564) | main | - | ❌ |
| 2026-06-18 | Integration | [#119729680](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119729680) | main | - | ❌ |
| 2026-06-18 | Integration | [#119726180](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119726180) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
