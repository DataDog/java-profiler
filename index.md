---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-18 14:33 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#154335981](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154335981) | ✅ | main | - |
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
| 2026-11-18 | Integration | [#154335981](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154335981) | main | - | ✅ |
| 2026-11-18 | Integration | [#154338456](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154338456) | main | - | ✅ |
| 2026-11-18 | Integration | [#154336915](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154336915) | main | - | ✅ |
| 2026-11-18 | Integration | [#154328985](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154328985) | main | - | ✅ |
| 2026-11-18 | Integration | [#154327745](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154327745) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
