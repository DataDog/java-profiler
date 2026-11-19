---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-19 07:47 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#154638266](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154638266) | ✅ | main | - |
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
| 2026-11-19 | Integration | [#154638266](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154638266) | main | - | ✅ |
| 2026-11-19 | Integration | [#154623637](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154623637) | main | - | ✅ |
| 2026-11-18 | Integration | [#154509020](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154509020) | main | - | ⚠️ |
| 2026-11-18 | Integration | [#154488155](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154488155) | main | - | ✅ |
| 2026-11-18 | Integration | [#154474466](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154474466) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
