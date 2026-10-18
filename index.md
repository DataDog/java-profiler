---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-18 05:04 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#145518248](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145518248) | ✅ | main | - |
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
| 2026-10-18 | Integration | [#145518248](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145518248) | main | - | ✅ |
| 2026-10-17 | Integration | [#145473016](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145473016) | main | - | ✅ |
| 2026-10-17 | Integration | [#145461688](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145461688) | main | - | ✅ |
| 2026-10-16 | Integration | [#145300463](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145300463) | main | - | ✅ |
| 2026-10-16 | Integration | [#145285201](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145285201) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
