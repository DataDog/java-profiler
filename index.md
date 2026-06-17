---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-17 21:01 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#119540805](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119540805) | ❌ | main | - |
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
| 2026-06-17 | Integration | [#119540805](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119540805) | main | - | ❌ |
| 2026-06-17 | Integration | [#119529682](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119529682) | main | - | ❌ |
| 2026-06-17 | Integration | [#119483874](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119483874) | main | - | ❌ |
| 2026-06-17 | Integration | [#119425633](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119425633) | main | - | ❌ |
| 2026-06-17 | Integration | [#119405298](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119405298) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
