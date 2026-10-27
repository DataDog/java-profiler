---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-27 21:57 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#148025365](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148025365) | ✅ | main | - |
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
| 2026-10-27 | Integration | [#148025365](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/148025365) | main | - | ✅ |
| 2026-10-27 | Integration | [#147996952](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147996952) | main | - | ✅ |
| 2026-10-27 | Integration | [#147970224](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147970224) | main | - | ✅ |
| 2026-10-27 | Integration | [#147946243](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147946243) | main | - | ⚠️ |
| 2026-10-27 | Integration | [#147939548](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147939548) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
