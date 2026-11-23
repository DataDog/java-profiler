---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-23 11:01 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#155645241](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155645241) | ✅ | main | - |
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
| 2026-11-23 | Integration | [#155645241](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155645241) | main | - | ✅ |
| 2026-11-23 | Integration | [#155645171](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155645171) | main | - | ✅ |
| 2026-11-23 | Integration | [#155645215](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155645215) | main | - | ✅ |
| 2026-11-23 | Integration | [#155642293](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155642293) | main | - | ✅ |
| 2026-11-23 | Integration | [#155642413](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155642413) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
