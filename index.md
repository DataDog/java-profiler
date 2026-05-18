---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-18 12:46 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#113679038](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113679038) | ❌ | main | - |
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
| 2026-05-18 | Integration | [#113679038](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113679038) | main | - | ❌ |
| 2026-05-18 | Integration | [#113661680](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113661680) | main | - | ❌ |
| 2026-05-18 | Integration | [#113647710](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113647710) | main | - | ❌ |
| 2026-05-18 | Integration | [#113640801](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113640801) | main | - | ❌ |
| 2026-05-18 | Integration | [#113614787](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113614787) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
