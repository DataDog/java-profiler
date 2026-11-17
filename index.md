---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-17 05:08 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#153795065](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153795065) | ⚠️ | main | - |
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
| 2026-11-17 | Integration | [#153795065](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153795065) | main | - | ⚠️ |
| 2026-11-16 | Integration | [#153695131](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153695131) | main | - | ❓ |
| 2026-11-16 | Integration | [#153676749](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153676749) | main | - | ✅ |
| 2026-11-16 | Integration | [#153607955](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153607955) | main | - | ✅ |
| 2026-11-16 | Integration | [#153608704](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153608704) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
