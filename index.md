---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-02 04:54 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128443132](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128443132) | ❓ | main | - |
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
| 2026-08-02 | Integration | [#128443132](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128443132) | main | - | ❓ |
| 2026-08-01 | Integration | [#128412294](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128412294) | main | - | ❓ |
| 2026-08-01 | Integration | [#128403258](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128403258) | main | - | ❓ |
| 2026-08-01 | Integration | [#128392581](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128392581) | main | - | ❓ |
| 2026-08-01 | Integration | [#128379260](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128379260) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
