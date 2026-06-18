---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-18 16:48 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#119777574](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119777574) | ❌ | main | - |
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
| 2026-06-18 | Integration | [#119777574](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119777574) | main | - | ❌ |
| 2026-06-18 | Integration | [#119768075](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119768075) | main | - | ❌ |
| 2026-06-18 | Integration | [#119719690](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119719690) | main | - | ❌ |
| 2026-06-18 | Integration | [#119753127](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119753127) | main | - | ❌ |
| 2026-06-18 | Integration | [#119750883](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119750883) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
