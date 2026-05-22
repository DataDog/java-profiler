---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-22 15:26 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#114764331](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114764331) | ❌ | main | - |
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
| 2026-05-22 | Integration | [#114764331](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114764331) | main | - | ❌ |
| 2026-05-22 | Integration | [#114746625](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114746625) | main | - | ❌ |
| 2026-05-22 | Integration | [#114730945](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114730945) | main | - | ❌ |
| 2026-05-22 | Integration | [#114690132](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114690132) | main | - | ❌ |
| 2026-05-22 | Integration | [#114685368](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114685368) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
