---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-08 11:28 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#117631803](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117631803) | ❌ | main | - |
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
| 2026-06-08 | Integration | [#117631803](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117631803) | main | - | ❌ |
| 2026-06-08 | Integration | [#117616755](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117616755) | main | - | ❌ |
| 2026-06-08 | Integration | [#117614576](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117614576) | main | - | ❌ |
| 2026-06-08 | Integration | [#117613600](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117613600) | main | - | ❌ |
| 2026-06-08 | Integration | [#117612708](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117612708) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
