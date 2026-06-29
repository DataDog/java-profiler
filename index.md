---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-29 09:47 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#121548599](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121548599) | ❌ | main | - |
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
| 2026-06-29 | Integration | [#121548599](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121548599) | main | - | ❌ |
| 2026-06-29 | Integration | [#121533216](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121533216) | main | - | ❌ |
| 2026-06-29 | Integration | [#121530667](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121530667) | main | - | ❌ |
| 2026-06-29 | Integration | [#121521840](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121521840) | main | - | ❌ |
| 2026-06-29 | Integration | [#121519139](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121519139) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
