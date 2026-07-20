---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-20 03:26 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125570001](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125570001) | ❌ | main | - |
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
| 2026-07-20 | Integration | [#125570001](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125570001) | main | - | ❌ |
| 2026-07-20 | Integration | [#125566926](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125566926) | main | - | ❌ |
| 2026-07-20 | Integration | [#125563813](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125563813) | main | - | ❌ |
| 2026-07-19 | Integration | [#125557926](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125557926) | main | - | ❌ |
| 2026-07-19 | Integration | [#125553848](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125553848) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
