---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-03 04:57 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#116687655](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116687655) | ❌ | main | - |
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
| 2026-06-03 | Integration | [#116687655](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116687655) | main | - | ❌ |
| 2026-06-02 | Integration | [#116672408](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116672408) | main | - | ❌ |
| 2026-06-02 | Integration | [#116640317](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116640317) | main | - | ❌ |
| 2026-06-02 | Integration | [#116623722](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116623722) | main | - | ❌ |
| 2026-06-02 | Integration | [#116581109](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116581109) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
