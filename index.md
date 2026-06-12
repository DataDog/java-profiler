---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-12 08:23 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#118361682](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118361682) | ❌ | main | - |
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
| 2026-06-12 | Integration | [#118361682](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118361682) | main | - | ❌ |
| 2026-06-12 | Integration | [#118359056](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118359056) | main | - | ❌ |
| 2026-06-12 | Integration | [#118354316](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118354316) | main | - | ❌ |
| 2026-06-12 | Integration | [#118347428](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118347428) | main | - | ❌ |
| 2026-06-11 | Integration | [#118215692](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118215692) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
