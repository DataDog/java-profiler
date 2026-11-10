---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-10 11:47 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#151806612](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151806612) | ✅ | main | - |
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
| 2026-11-10 | Integration | [#151806612](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151806612) | main | - | ✅ |
| 2026-11-10 | Integration | [#151804618](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151804618) | main | - | ✅ |
| 2026-11-10 | Integration | [#151788852](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151788852) | main | - | ✅ |
| 2026-11-10 | Integration | [#151777627](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151777627) | main | - | ✅ |
| 2026-11-10 | Integration | [#151756718](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151756718) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
