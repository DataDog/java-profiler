---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-09 17:24 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#151544989](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151544989) | ✅ | main | - |
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
| 2026-11-09 | Integration | [#151544989](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151544989) | main | - | ✅ |
| 2026-11-09 | Integration | [#151537878](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151537878) | main | - | ✅ |
| 2026-11-09 | Integration | [#151459101](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151459101) | main | - | ✅ |
| 2026-11-09 | Integration | [#151507836](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151507836) | main | - | ✅ |
| 2026-11-09 | Integration | [#151490586](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151490586) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
