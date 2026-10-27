---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-27 16:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#147894717](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147894717) | ⚠️ | main | - |
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
| 2026-10-27 | Integration | [#147894717](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147894717) | main | - | ⚠️ |
| 2026-10-27 | Integration | [#147862012](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147862012) | main | - | ⚠️ |
| 2026-10-27 | Integration | [#147838458](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147838458) | main | - | ✅ |
| 2026-10-27 | Integration | [#147812584](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147812584) | main | - | ❓ |
| 2026-10-27 | Integration | [#147797020](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147797020) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
