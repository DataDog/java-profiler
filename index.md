---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-24 18:28 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#132852133](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132852133) | ✅ | main | - |
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
| 2026-08-24 | Integration | [#132852133](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132852133) | main | - | ✅ |
| 2026-08-24 | Integration | [#132826922](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132826922) | main | - | ⚠️ |
| 2026-08-24 | Integration | [#132798242](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132798242) | main | - | ❓ |
| 2026-08-24 | Integration | [#132775188](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132775188) | main | - | ❓ |
| 2026-08-24 | Integration | [#132754230](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/132754230) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
