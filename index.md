---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-11 14:17 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#152217828](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152217828) | ⚠️ | main | - |
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
| 2026-11-11 | Integration | [#152217828](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152217828) | main | - | ⚠️ |
| 2026-11-11 | Integration | [#152126354](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152126354) | main | - | ✅ |
| 2026-11-11 | Integration | [#152204163](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152204163) | main | - | ✅ |
| 2026-11-11 | Integration | [#152201157](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152201157) | main | - | ✅ |
| 2026-11-11 | Integration | [#152197954](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152197954) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
