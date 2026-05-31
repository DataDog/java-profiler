---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-31 23:19 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#116135133](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116135133) | ❌ | main | - |
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
| 2026-05-31 | Integration | [#116135133](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116135133) | main | - | ❌ |
| 2026-05-31 | Integration | [#116127854](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116127854) | main | - | ❌ |
| 2026-05-31 | Integration | [#116126115](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116126115) | main | - | ❌ |
| 2026-05-31 | Integration | [#116100974](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116100974) | main | - | ❌ |
| 2026-05-30 | Integration | [#116058828](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116058828) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
