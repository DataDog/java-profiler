---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-13 08:09 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#96301049](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/96301049) | ⚠️ | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) |
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
| 2026-02-13 | Integration | [#96301049](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/96301049) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |
| 2026-02-12 | Integration | [#96164787](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/96164787) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |
| 2026-02-12 | Integration | [#96142573](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/96142573) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |
| 2026-02-12 | Integration | [#96095537](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/96095537) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |
| 2026-02-12 | Integration | [#96067392](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/96067392) | jb/gradle_9 | [#365](https://github.com/DataDog/java-profiler/pull/365) | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
