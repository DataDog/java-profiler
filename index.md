---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-22 07:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#146630636](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146630636) | ✅ | main | - |
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
| 2026-10-22 | Integration | [#146630636](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146630636) | main | - | ✅ |
| 2026-10-22 | Integration | [#146611812](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146611812) | main | - | ✅ |
| 2026-10-21 | Integration | [#146563702](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146563702) | main | - | ✅ |
| 2026-10-21 | Integration | [#146557046](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146557046) | main | - | ✅ |
| 2026-10-21 | Integration | [#146556530](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146556530) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
