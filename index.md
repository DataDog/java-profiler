---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-12 03:04 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#143999918](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143999918) | ✅ | main | - |
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
| 2026-10-12 | Integration | [#143999918](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143999918) | main | - | ✅ |
| 2026-10-11 | Integration | [#143981718](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143981718) | main | - | ✅ |
| 2026-10-11 | Integration | [#143980709](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143980709) | main | - | ✅ |
| 2026-10-11 | Integration | [#143971083](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143971083) | main | - | ✅ |
| 2026-10-11 | Integration | [#143959311](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143959311) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
