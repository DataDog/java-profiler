---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-16 10:05 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124960845](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124960845) | ❌ | main | - |
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
| 2026-07-16 | Integration | [#124960845](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124960845) | main | - | ❌ |
| 2026-07-16 | Integration | [#124958055](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124958055) | main | - | ❌ |
| 2026-07-16 | Integration | [#124958133](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124958133) | main | - | ❌ |
| 2026-07-16 | Integration | [#124953798](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124953798) | main | - | ❌ |
| 2026-07-16 | Integration | [#124946467](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124946467) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
