---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-18 13:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#119704087](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119704087) | ❌ | main | - |
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
| 2026-06-18 | Integration | [#119704087](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119704087) | main | - | ❌ |
| 2026-06-18 | Integration | [#119696413](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119696413) | main | - | ❌ |
| 2026-06-18 | Integration | [#119695903](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119695903) | main | - | ❌ |
| 2026-06-18 | Integration | [#119692991](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119692991) | main | - | ❌ |
| 2026-06-18 | Integration | [#119671428](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119671428) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
