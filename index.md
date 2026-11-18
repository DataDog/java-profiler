---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-18 11:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#154272006](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154272006) | ✅ | main | - |
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
| 2026-11-18 | Integration | [#154272006](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154272006) | main | - | ✅ |
| 2026-11-18 | Integration | [#154265563](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154265563) | main | - | ⚠️ |
| 2026-11-18 | Integration | [#154262394](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154262394) | main | - | ✅ |
| 2026-11-18 | Integration | [#154257594](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154257594) | main | - | ✅ |
| 2026-11-18 | Integration | [#154256279](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154256279) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
