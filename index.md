---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-03 11:43 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128546757](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128546757) | ❓ | main | - |
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
| 2026-08-03 | Integration | [#128546757](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128546757) | main | - | ❓ |
| 2026-08-03 | Integration | [#128546980](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128546980) | main | - | ❓ |
| 2026-08-03 | Integration | [#128546499](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128546499) | main | - | ❓ |
| 2026-08-03 | Integration | [#128541596](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128541596) | main | - | ❓ |
| 2026-08-03 | Integration | [#128541594](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128541594) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
