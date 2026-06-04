---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-04 11:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#117017475](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117017475) | ❓ | main | - |
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
| 2026-06-04 | Integration | [#117017475](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117017475) | main | - | ❓ |
| 2026-06-04 | Integration | [#117013069](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117013069) | main | - | ❌ |
| 2026-06-04 | Integration | [#117010862](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117010862) | main | - | ❓ |
| 2026-06-04 | Integration | [#116957860](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116957860) | main | - | ❌ |
| 2026-06-03 | Integration | [#116923161](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116923161) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
