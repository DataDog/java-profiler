---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-31 12:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128218754](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128218754) | ❓ | main | - |
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
| 2026-07-31 | Integration | [#128218754](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128218754) | main | - | ❓ |
| 2026-07-31 | Integration | [#128207451](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128207451) | main | - | ❓ |
| 2026-07-31 | Integration | [#128204847](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128204847) | main | - | ❓ |
| 2026-07-31 | Integration | [#128201602](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128201602) | main | - | ❓ |
| 2026-07-31 | Integration | [#128194430](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128194430) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
