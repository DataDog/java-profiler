---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-29 15:32 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#148595051](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148595051) | ⚠️ | main | - |
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
| 2026-10-29 | Integration | [#148595051](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148595051) | main | - | ⚠️ |
| 2026-10-29 | Integration | [#148560084](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148560084) | main | - | ⚠️ |
| 2026-10-29 | Integration | [#148548274](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148548274) | main | - | ✅ |
| 2026-10-29 | Integration | [#148545063](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148545063) | main | - | ✅ |
| 2026-10-29 | Integration | [#148545849](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148545849) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
