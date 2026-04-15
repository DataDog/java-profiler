---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-15 12:57 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#107800458](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107800458) | ✅ | main | - |
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
| 2026-04-15 | Integration | [#107800458](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107800458) | main | - | ✅ |
| 2026-04-15 | Integration | [#107788203](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107788203) | main | - | ✅ |
| 2026-04-15 | Integration | [#107782518](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107782518) | main | - | ✅ |
| 2026-04-14 | Integration | [#107713459](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107713459) | main | - | ✅ |
| 2026-04-14 | Integration | [#107674043](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107674043) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
