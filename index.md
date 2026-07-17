---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-17 14:04 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125282336](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125282336) | ❌ | main | - |
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
| 2026-07-17 | Integration | [#125282336](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125282336) | main | - | ❌ |
| 2026-07-17 | Integration | [#125281635](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125281635) | main | - | ❌ |
| 2026-07-17 | Integration | [#125274475](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125274475) | main | - | ❌ |
| 2026-07-17 | Integration | [#125250199](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125250199) | main | - | ❌ |
| 2026-07-17 | Integration | [#125238289](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125238289) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
