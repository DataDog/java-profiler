---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-18 20:56 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#119842345](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119842345) | ❓ | main | - |
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
| 2026-06-18 | Integration | [#119842345](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119842345) | main | - | ❓ |
| 2026-06-18 | Integration | [#119829815](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119829815) | main | - | ❌ |
| 2026-06-18 | Integration | [#119824038](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119824038) | main | - | ❌ |
| 2026-06-18 | Integration | [#119818189](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119818189) | main | - | ❌ |
| 2026-06-18 | Integration | [#119817868](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119817868) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
