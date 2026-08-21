---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-21 11:48 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#132369148](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132369148) | ✅ | main | - |
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
| 2026-08-21 | Integration | [#132369148](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132369148) | main | - | ✅ |
| 2026-08-21 | Integration | [#132363486](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132363486) | main | - | ✅ |
| 2026-08-21 | Integration | [#132362923](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132362923) | main | - | ✅ |
| 2026-08-21 | Integration | [#132349806](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132349806) | main | - | ✅ |
| 2026-08-21 | Integration | [#132348188](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132348188) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
