---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-17 10:43 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125238289](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125238289) | ❌ | main | - |
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
| 2026-07-17 | Integration | [#125238289](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125238289) | main | - | ❌ |
| 2026-07-17 | Integration | [#125233867](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125233867) | main | - | ❌ |
| 2026-07-17 | Integration | [#125231095](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125231095) | main | - | ❌ |
| 2026-07-17 | Integration | [#125231026](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125231026) | main | - | ❌ |
| 2026-07-17 | Integration | [#125226081](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125226081) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
