---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-29 14:18 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#127708531](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127708531) | ❌ | main | - |
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
| 2026-07-29 | Integration | [#127708531](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127708531) | main | - | ❌ |
| 2026-07-29 | Integration | [#127708321](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127708321) | main | - | ❓ |
| 2026-07-29 | Integration | [#127697425](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127697425) | main | - | ❌ |
| 2026-07-29 | Integration | [#127696070](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127696070) | main | - | ❓ |
| 2026-07-29 | Integration | [#127690543](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127690543) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
