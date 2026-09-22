---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-22 11:06 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#139120791](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139120791) | ⚠️ | main | - |
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
| 2026-09-22 | Integration | [#139120791](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139120791) | main | - | ⚠️ |
| 2026-09-22 | Integration | [#139104334](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139104334) | main | - | ✅ |
| 2026-09-22 | Integration | [#139067999](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139067999) | main | - | ✅ |
| 2026-09-21 | Integration | [#139023990](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139023990) | main | - | ⚠️ |
| 2026-09-21 | Integration | [#139008637](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139008637) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
