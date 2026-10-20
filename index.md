---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-20 22:16 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#146217840](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146217840) | ⚠️ | main | - |
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
| 2026-10-20 | Integration | [#146217840](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146217840) | main | - | ⚠️ |
| 2026-10-20 | Integration | [#146209340](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146209340) | main | - | ✅ |
| 2026-10-20 | Integration | [#146205178](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146205178) | main | - | ⚠️ |
| 2026-10-20 | Integration | [#146174946](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146174946) | main | - | ⚠️ |
| 2026-10-20 | Integration | [#146148472](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146148472) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
