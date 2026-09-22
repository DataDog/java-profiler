---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-22 20:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#139309884](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139309884) | ✅ | main | - |
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
| 2026-09-22 | Integration | [#139309884](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139309884) | main | - | ✅ |
| 2026-09-22 | Integration | [#139274654](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139274654) | main | - | ⚠️ |
| 2026-09-22 | Integration | [#139273886](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139273886) | main | - | ✅ |
| 2026-09-22 | Integration | [#139273738](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139273738) | main | - | ✅ |
| 2026-09-22 | Integration | [#139241329](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139241329) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
