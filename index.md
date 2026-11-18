---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-18 13:37 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#154315571](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154315571) | ✅ | main | - |
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
| 2026-11-18 | Integration | [#154315571](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154315571) | main | - | ✅ |
| 2026-11-18 | Integration | [#154314864](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154314864) | main | - | ✅ |
| 2026-11-18 | Integration | [#154311647](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154311647) | main | - | ✅ |
| 2026-11-18 | Integration | [#154312512](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154312512) | main | - | ✅ |
| 2026-11-18 | Integration | [#154305601](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154305601) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
