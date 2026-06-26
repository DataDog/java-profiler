---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-26 20:37 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#121381849](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121381849) | ❌ | main | - |
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
| 2026-06-26 | Integration | [#121381849](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121381849) | main | - | ❌ |
| 2026-06-26 | Integration | [#121379176](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121379176) | main | - | ❌ |
| 2026-06-26 | Integration | [#121366852](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121366852) | main | - | ❌ |
| 2026-06-26 | Integration | [#121306917](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121306917) | main | - | ❌ |
| 2026-06-26 | Integration | [#121303438](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121303438) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
