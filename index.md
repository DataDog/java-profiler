---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-20 05:41 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125576923](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125576923) | ❌ | main | - |
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
| 2026-07-20 | Integration | [#125576923](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125576923) | main | - | ❌ |
| 2026-07-20 | Integration | [#125574602](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125574602) | main | - | ❌ |
| 2026-07-20 | Integration | [#125570076](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125570076) | main | - | ❌ |
| 2026-07-20 | Integration | [#125570080](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125570080) | main | - | ❌ |
| 2026-07-20 | Integration | [#125570001](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125570001) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
