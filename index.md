---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-23 10:48 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#132619922](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132619922) | ✅ | main | - |
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
| 2026-08-23 | Integration | [#132619922](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132619922) | main | - | ✅ |
| 2026-08-23 | Integration | [#132607912](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132607912) | main | - | ✅ |
| 2026-08-23 | Integration | [#132596955](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132596955) | main | - | ✅ |
| 2026-08-22 | Integration | [#132586046](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132586046) | main | - | ✅ |
| 2026-08-22 | Integration | [#132582839](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132582839) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
