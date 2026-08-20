---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-20 11:23 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#132098573](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132098573) | ✅ | main | - |
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
| 2026-08-20 | Integration | [#132098573](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132098573) | main | - | ✅ |
| 2026-08-20 | Integration | [#132081427](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132081427) | main | - | ✅ |
| 2026-08-20 | Integration | [#132093552](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132093552) | main | - | ✅ |
| 2026-08-20 | Integration | [#132087754](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132087754) | main | - | ✅ |
| 2026-08-20 | Integration | [#132082898](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132082898) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
