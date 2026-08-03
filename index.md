---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-03 01:18 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128487140](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128487140) | ❓ | main | - |
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
| 2026-08-03 | Integration | [#128487140](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128487140) | main | - | ❓ |
| 2026-08-03 | Integration | [#128484060](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128484060) | main | - | ❓ |
| 2026-08-02 | Integration | [#128453780](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128453780) | main | - | ❓ |
| 2026-08-02 | Integration | [#128443132](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128443132) | main | - | ❓ |
| 2026-08-01 | Integration | [#128412294](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128412294) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
