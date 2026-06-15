---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-15 10:18 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#118741581](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118741581) | ❌ | main | - |
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
| 2026-06-15 | Integration | [#118741581](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118741581) | main | - | ❌ |
| 2026-06-15 | Integration | [#118697380](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118697380) | main | - | ❌ |
| 2026-06-14 | Integration | [#118645346](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118645346) | main | - | ❌ |
| 2026-06-13 | Integration | [#118605844](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118605844) | main | - | ❌ |
| 2026-06-12 | Integration | [#118577974](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118577974) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
