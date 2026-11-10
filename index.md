---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-10 15:42 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#151890940](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151890940) | ⚠️ | main | - |
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
| 2026-11-10 | Integration | [#151890940](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151890940) | main | - | ⚠️ |
| 2026-11-10 | Integration | [#151887322](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151887322) | main | - | ✅ |
| 2026-11-10 | Integration | [#151884174](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151884174) | main | - | ✅ |
| 2026-11-10 | Integration | [#151881097](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151881097) | main | - | ⚠️ |
| 2026-11-10 | Integration | [#151880911](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151880911) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
