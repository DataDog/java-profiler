---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-29 05:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#140793777](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140793777) | ✅ | main | - |
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
| 2026-09-29 | Integration | [#140793777](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140793777) | main | - | ✅ |
| 2026-09-28 | Integration | [#140720049](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140720049) | main | - | ✅ |
| 2026-09-28 | Integration | [#140706301](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140706301) | main | - | ❓ |
| 2026-09-28 | Integration | [#140673014](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140673014) | main | - | ✅ |
| 2026-09-28 | Integration | [#140673179](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140673179) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
