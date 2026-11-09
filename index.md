---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-09 20:05 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#151613535](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151613535) | ✅ | main | - |
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
| 2026-11-09 | Integration | [#151613535](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151613535) | main | - | ✅ |
| 2026-11-09 | Integration | [#151608221](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151608221) | main | - | ✅ |
| 2026-11-09 | Integration | [#151610424](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151610424) | main | - | ❓ |
| 2026-11-09 | Integration | [#151573027](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151573027) | main | - | ❓ |
| 2026-11-09 | Integration | [#151546620](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151546620) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
