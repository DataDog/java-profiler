---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-18 19:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#113803675](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113803675) | ❌ | main | - |
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
| 2026-05-18 | Integration | [#113803675](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113803675) | main | - | ❌ |
| 2026-05-18 | Integration | [#113753441](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113753441) | main | - | ❌ |
| 2026-05-18 | Integration | [#113749658](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113749658) | main | - | ❌ |
| 2026-05-18 | Integration | [#113739652](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113739652) | main | - | ❌ |
| 2026-05-18 | Integration | [#113679038](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/113679038) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
