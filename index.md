---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-04 01:20 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#111141112](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111141112) | ✅ | main | - |
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
| 2026-05-04 | Integration | [#111141112](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111141112) | main | - | ✅ |
| 2026-05-01 | Integration | [#110982908](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110982908) | main | - | ⚠️ |
| 2026-05-01 | Integration | [#110893160](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110893160) | main | - | ⚠️ |
| 2026-04-30 | Integration | [#110842814](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110842814) | main | - | ⚠️ |
| 2026-04-30 | Integration | [#110779878](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110779878) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
