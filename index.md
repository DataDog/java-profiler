---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-30 14:25 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#121862090](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121862090) | ❌ | main | - |
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
| 2026-06-30 | Integration | [#121862090](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121862090) | main | - | ❌ |
| 2026-06-30 | Integration | [#121848831](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121848831) | main | - | ❌ |
| 2026-06-30 | Integration | [#121847651](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121847651) | main | - | ❌ |
| 2026-06-30 | Integration | [#121802370](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121802370) | main | - | ❌ |
| 2026-06-30 | Integration | [#121800513](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121800513) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
