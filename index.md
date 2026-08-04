---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-04 05:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128757417](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128757417) | ❓ | main | - |
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
| 2026-08-04 | Integration | [#128757417](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128757417) | main | - | ❓ |
| 2026-08-04 | Integration | [#128745403](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128745403) | main | - | ❓ |
| 2026-08-04 | Integration | [#128741772](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128741772) | main | - | ❓ |
| 2026-08-03 | Integration | [#128729954](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128729954) | main | - | ❓ |
| 2026-08-03 | Integration | [#128714480](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128714480) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
