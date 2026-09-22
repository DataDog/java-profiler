---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-22 15:30 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#139199484](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139199484) | ✅ | main | - |
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
| 2026-09-22 | Integration | [#139199484](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139199484) | main | - | ✅ |
| 2026-09-22 | Integration | [#139190643](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139190643) | main | - | ⚠️ |
| 2026-09-22 | Integration | [#139181126](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139181126) | main | - | ✅ |
| 2026-09-22 | Integration | [#139181294](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139181294) | main | - | ✅ |
| 2026-09-22 | Integration | [#139175928](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139175928) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
