---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-04 16:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128898992](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128898992) | ❓ | main | - |
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
| 2026-08-04 | Integration | [#128898992](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128898992) | main | - | ❓ |
| 2026-08-04 | Integration | [#128876488](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128876488) | main | - | ❓ |
| 2026-08-04 | Integration | [#128883004](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128883004) | main | - | ❓ |
| 2026-08-04 | Integration | [#128879165](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128879165) | main | - | ❓ |
| 2026-08-04 | Integration | [#128868371](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128868371) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
