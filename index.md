---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-12 11:01 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#152519207](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152519207) | ✅ | main | - |
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
| 2026-11-12 | Integration | [#152519207](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152519207) | main | - | ✅ |
| 2026-11-12 | Integration | [#152518764](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152518764) | main | - | ✅ |
| 2026-11-12 | Integration | [#152519712](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152519712) | main | - | ❓ |
| 2026-11-12 | Integration | [#152515154](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152515154) | main | - | ✅ |
| 2026-11-12 | Integration | [#152515119](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152515119) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
