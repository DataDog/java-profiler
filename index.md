---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-09 04:54 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#123685738](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123685738) | ❌ | main | - |
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
| 2026-07-09 | Integration | [#123685738](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123685738) | main | - | ❌ |
| 2026-07-08 | Integration | [#123650246](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123650246) | main | - | ❌ |
| 2026-07-08 | Integration | [#123611521](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123611521) | main | - | ❌ |
| 2026-07-08 | Integration | [#123606984](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123606984) | main | - | ❌ |
| 2026-07-08 | Integration | [#123594185](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123594185) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
