---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-22 19:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#132586046](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132586046) | ✅ | main | - |
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
| 2026-08-22 | Integration | [#132586046](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132586046) | main | - | ✅ |
| 2026-08-22 | Integration | [#132582839](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132582839) | main | - | ✅ |
| 2026-08-22 | Integration | [#132579294](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132579294) | main | - | ✅ |
| 2026-08-22 | Integration | [#132575359](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132575359) | main | - | ✅ |
| 2026-08-22 | Integration | [#132568951](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132568951) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
