---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-04 13:12 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128827941](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128827941) | ❓ | main | - |
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
| 2026-08-04 | Integration | [#128827941](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128827941) | main | - | ❓ |
| 2026-08-04 | Integration | [#128822564](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128822564) | main | - | ❓ |
| 2026-08-04 | Integration | [#128815647](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128815647) | main | - | ❓ |
| 2026-08-04 | Integration | [#128814781](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128814781) | main | - | ❓ |
| 2026-08-04 | Integration | [#128808945](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128808945) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
