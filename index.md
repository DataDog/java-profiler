---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-17 19:42 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#138290881](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138290881) | ✅ | main | - |
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
| 2026-09-17 | Integration | [#138290881](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138290881) | main | - | ✅ |
| 2026-09-17 | Integration | [#138290846](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138290846) | main | - | ✅ |
| 2026-09-17 | Integration | [#138290882](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138290882) | main | - | ✅ |
| 2026-09-17 | Integration | [#138290871](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138290871) | main | - | ✅ |
| 2026-09-17 | Integration | [#138290832](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138290832) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
