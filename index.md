---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-13 07:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#130657915](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130657915) | ✅ | main | - |
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
| 2026-08-13 | Integration | [#130657915](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130657915) | main | - | ✅ |
| 2026-08-13 | Integration | [#130646012](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130646012) | main | - | ✅ |
| 2026-08-13 | Integration | [#130628650](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130628650) | main | - | ✅ |
| 2026-08-12 | Integration | [#130543060](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130543060) | main | - | ✅ |
| 2026-08-12 | Integration | [#130496946](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/130496946) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
