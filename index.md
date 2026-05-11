---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-11 23:24 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112614511](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112614511) | ✅ | main | - |
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
| 2026-05-11 | Integration | [#112614511](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112614511) | main | - | ✅ |
| 2026-05-11 | Integration | [#112610148](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112610148) | main | - | ✅ |
| 2026-05-11 | Integration | [#112609106](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112609106) | main | - | ⚠️ |
| 2026-05-11 | Integration | [#112608653](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112608653) | main | - | ✅ |
| 2026-05-11 | Integration | [#112608439](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112608439) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
