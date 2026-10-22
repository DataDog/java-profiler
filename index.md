---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-22 12:08 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#146685945](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146685945) | ✅ | main | - |
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
| 2026-10-22 | Integration | [#146685945](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146685945) | main | - | ✅ |
| 2026-10-22 | Integration | [#146683863](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146683863) | main | - | ✅ |
| 2026-10-22 | Integration | [#146684170](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146684170) | main | - | ✅ |
| 2026-10-22 | Integration | [#146670204](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146670204) | main | - | ✅ |
| 2026-10-22 | Integration | [#146668546](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146668546) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
