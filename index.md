---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-19 18:48 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#154877951](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154877951) | ✅ | main | - |
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
| 2026-11-19 | Integration | [#154877951](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154877951) | main | - | ✅ |
| 2026-11-19 | Integration | [#154877964](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154877964) | main | - | ✅ |
| 2026-11-19 | Integration | [#154872701](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154872701) | main | - | ✅ |
| 2026-11-19 | Integration | [#154867920](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154867920) | main | - | ⚠️ |
| 2026-11-19 | Integration | [#154867829](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154867829) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
