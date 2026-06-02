---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-02 08:47 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#116439464](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116439464) | ❌ | main | - |
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
| 2026-06-02 | Integration | [#116439464](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116439464) | main | - | ❌ |
| 2026-06-02 | Integration | [#116439338](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116439338) | main | - | ❌ |
| 2026-06-02 | Integration | [#116436995](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116436995) | main | - | ❓ |
| 2026-06-02 | Integration | [#116429542](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116429542) | main | - | ❌ |
| 2026-06-02 | Integration | [#116423871](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116423871) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
