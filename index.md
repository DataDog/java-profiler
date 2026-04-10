---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-10 10:54 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#107060401](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107060401) | ✅ | main | - |
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
| 2026-04-10 | Integration | [#107060401](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107060401) | main | - | ✅ |
| 2026-04-10 | Integration | [#107050837](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107050837) | main | - | ✅ |
| 2026-04-10 | Integration | [#107026167](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107026167) | main | - | ✅ |
| 2026-04-09 | Integration | [#106910994](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/106910994) | main | - | ✅ |
| 2026-04-09 | Integration | [#106906293](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/106906293) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
