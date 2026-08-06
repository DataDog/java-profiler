---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-06 11:56 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#129371753](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129371753) | ✅ | main | - |
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
| 2026-08-06 | Integration | [#129371753](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129371753) | main | - | ✅ |
| 2026-08-06 | Integration | [#129369146](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129369146) | main | - | ❓ |
| 2026-08-06 | Integration | [#129365082](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129365082) | main | - | ✅ |
| 2026-08-06 | Integration | [#129363957](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129363957) | main | - | ❓ |
| 2026-08-06 | Integration | [#129363175](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129363175) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
