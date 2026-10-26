---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-26 01:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#147367601](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147367601) | ✅ | main | - |
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
| 2026-10-26 | Integration | [#147367601](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147367601) | main | - | ✅ |
| 2026-10-25 | Integration | [#147335310](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147335310) | main | - | ✅ |
| 2026-10-25 | Integration | [#147331339](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147331339) | main | - | ✅ |
| 2026-10-25 | Integration | [#147318157](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147318157) | main | - | ✅ |
| 2026-10-24 | Integration | [#147274053](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147274053) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
