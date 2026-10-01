---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-01 05:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#141505108](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141505108) | ✅ | main | - |
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
| 2026-10-01 | Integration | [#141505108](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141505108) | main | - | ✅ |
| 2026-09-30 | Integration | [#141402038](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141402038) | main | - | ✅ |
| 2026-09-30 | Integration | [#141354699](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141354699) | main | - | ✅ |
| 2026-09-30 | Integration | [#141340401](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141340401) | main | - | ✅ |
| 2026-09-30 | Integration | [#141336758](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141336758) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
