---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-20 09:56 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#132082898](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132082898) | ✅ | main | - |
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
| 2026-08-20 | Integration | [#132082898](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132082898) | main | - | ✅ |
| 2026-08-20 | Integration | [#132079927](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132079927) | main | - | ✅ |
| 2026-08-20 | Integration | [#132076150](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132076150) | main | - | ✅ |
| 2026-08-20 | Integration | [#132046278](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132046278) | main | - | ✅ |
| 2026-08-20 | Integration | [#132027900](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132027900) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
