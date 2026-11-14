---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-14 03:10 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#153234137](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153234137) | ✅ | main | - |
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
| 2026-11-14 | Integration | [#153234137](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153234137) | main | - | ✅ |
| 2026-11-13 | Integration | [#153192552](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153192552) | main | - | ✅ |
| 2026-11-13 | Integration | [#153173050](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153173050) | main | - | ✅ |
| 2026-11-13 | Integration | [#153172867](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153172867) | main | - | ✅ |
| 2026-11-13 | Integration | [#153171962](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153171962) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
