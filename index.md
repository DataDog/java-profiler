---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-02 01:28 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#149268042](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149268042) | ✅ | main | - |
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
| 2026-11-02 | Integration | [#149268042](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149268042) | main | - | ✅ |
| 2026-11-01 | Integration | [#149231247](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149231247) | main | - | ✅ |
| 2026-11-01 | Integration | [#149216481](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149216481) | main | - | ✅ |
| 2026-10-31 | Integration | [#149173311](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149173311) | main | - | ✅ |
| 2026-10-31 | Integration | [#149145415](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/149145415) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
