---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-09 13:34 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#117781882](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117781882) | ❌ | main | - |
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
| 2026-06-09 | Integration | [#117781882](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117781882) | main | - | ❌ |
| 2026-06-09 | Integration | [#117781072](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117781072) | main | - | ❌ |
| 2026-06-09 | Integration | [#117776636](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117776636) | main | - | ❌ |
| 2026-06-09 | Integration | [#117777552](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117777552) | main | - | ❌ |
| 2026-06-09 | Integration | [#117774002](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117774002) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
