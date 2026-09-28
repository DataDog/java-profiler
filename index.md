---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-28 13:39 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#140542594](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140542594) | ✅ | main | - |
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
| 2026-09-28 | Integration | [#140542594](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140542594) | main | - | ✅ |
| 2026-09-28 | Integration | [#140533140](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140533140) | main | - | ❓ |
| 2026-09-28 | Integration | [#140528692](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140528692) | main | - | ✅ |
| 2026-09-28 | Integration | [#140509983](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140509983) | main | - | ✅ |
| 2026-09-28 | Integration | [#140509773](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140509773) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
