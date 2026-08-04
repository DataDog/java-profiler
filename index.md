---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-04 09:24 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128782557](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128782557) | ❓ | main | - |
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
| 2026-08-04 | Integration | [#128782557](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128782557) | main | - | ❓ |
| 2026-08-04 | Integration | [#128778547](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128778547) | main | - | ❓ |
| 2026-08-04 | Integration | [#128775802](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128775802) | main | - | ❓ |
| 2026-08-04 | Integration | [#128757417](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128757417) | main | - | ❓ |
| 2026-08-04 | Integration | [#128745403](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128745403) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
