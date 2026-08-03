---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-03 13:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128578988](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128578988) | ❓ | main | - |
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
| 2026-08-03 | Integration | [#128578988](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128578988) | main | - | ❓ |
| 2026-08-03 | Integration | [#128568469](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128568469) | main | - | ❓ |
| 2026-08-03 | Integration | [#128567633](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128567633) | main | - | ❓ |
| 2026-08-03 | Integration | [#128556047](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128556047) | main | - | ❓ |
| 2026-08-03 | Integration | [#128551328](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128551328) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
