---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-01 06:09 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#116149750](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116149750) | ❌ | main | - |
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
| 2026-06-01 | Integration | [#116149750](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116149750) | main | - | ❌ |
| 2026-06-01 | Integration | [#116147280](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116147280) | main | - | ❌ |
| 2026-06-01 | Integration | [#116140679](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116140679) | main | - | ❌ |
| 2026-06-01 | Integration | [#116140684](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116140684) | main | - | ❌ |
| 2026-05-31 | Integration | [#116135133](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116135133) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
