---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-10 19:42 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#107188445](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107188445) | ✅ | main | - |
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
| 2026-04-10 | Integration | [#107188445](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107188445) | main | - | ✅ |
| 2026-04-10 | Integration | [#107170617](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107170617) | main | - | ✅ |
| 2026-04-10 | Integration | [#107157087](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107157087) | main | - | ✅ |
| 2026-04-10 | Integration | [#107142255](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107142255) | main | - | ✅ |
| 2026-04-10 | Integration | [#107122290](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107122290) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
