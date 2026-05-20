---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-20 16:12 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#114274860](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114274860) | ❌ | main | - |
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
| 2026-05-20 | Integration | [#114274860](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114274860) | main | - | ❌ |
| 2026-05-20 | Integration | [#114269604](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114269604) | main | - | ❌ |
| 2026-05-20 | Integration | [#114253357](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114253357) | main | - | ❌ |
| 2026-05-20 | Integration | [#114252183](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114252183) | main | - | ❌ |
| 2026-05-20 | Integration | [#114231115](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114231115) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
