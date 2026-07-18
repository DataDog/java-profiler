---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-18 05:51 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125445199](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125445199) | ❌ | main | - |
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
| 2026-07-18 | Integration | [#125445199](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125445199) | main | - | ❌ |
| 2026-07-17 | Integration | [#125377451](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125377451) | main | - | ❌ |
| 2026-07-17 | Integration | [#125374142](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125374142) | main | - | ❓ |
| 2026-07-17 | Integration | [#125370095](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125370095) | main | - | ❌ |
| 2026-07-17 | Integration | [#125368543](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125368543) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
