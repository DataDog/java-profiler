---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-15 16:28 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#118852064](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118852064) | ❌ | main | - |
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
| 2026-06-15 | Integration | [#118852064](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118852064) | main | - | ❌ |
| 2026-06-15 | Integration | [#118849031](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118849031) | main | - | ❌ |
| 2026-06-15 | Integration | [#118837519](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118837519) | main | - | ❌ |
| 2026-06-15 | Integration | [#118833539](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118833539) | main | - | ❌ |
| 2026-06-15 | Integration | [#118833364](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118833364) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
