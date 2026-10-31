---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-31 01:17 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#149145415](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149145415) | ✅ | main | - |
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
| 2026-10-31 | Integration | [#149145415](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149145415) | main | - | ✅ |
| 2026-10-30 | Integration | [#149138235](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149138235) | main | - | ✅ |
| 2026-10-30 | Integration | [#149103517](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149103517) | main | - | ✅ |
| 2026-10-30 | Integration | [#149068960](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149068960) | main | - | ✅ |
| 2026-10-30 | Integration | [#149033135](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149033135) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
