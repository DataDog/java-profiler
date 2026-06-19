---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-19 22:21 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#120012544](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120012544) | ❌ | main | - |
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
| 2026-06-19 | Integration | [#120012544](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120012544) | main | - | ❌ |
| 2026-06-19 | Integration | [#120012740](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120012740) | main | - | ❌ |
| 2026-06-19 | Integration | [#120010549](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120010549) | main | - | ❌ |
| 2026-06-19 | Integration | [#120008679](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120008679) | main | - | ❌ |
| 2026-06-19 | Integration | [#120007233](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/120007233) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
