---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-12 13:10 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#118422072](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118422072) | ❌ | main | - |
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
| 2026-06-12 | Integration | [#118422072](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118422072) | main | - | ❌ |
| 2026-06-12 | Integration | [#118408165](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118408165) | main | - | ❌ |
| 2026-06-12 | Integration | [#118402594](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118402594) | main | - | ❌ |
| 2026-06-12 | Integration | [#118398877](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118398877) | main | - | ❌ |
| 2026-06-12 | Integration | [#118398768](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118398768) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
