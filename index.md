---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-27 12:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#147785205](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147785205) | ❓ | main | - |
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
| 2026-10-27 | Integration | [#147785205](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147785205) | main | - | ❓ |
| 2026-10-27 | Integration | [#147772294](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147772294) | main | - | ✅ |
| 2026-10-27 | Integration | [#147757322](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147757322) | main | - | ✅ |
| 2026-10-27 | Integration | [#147712503](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147712503) | main | - | ✅ |
| 2026-10-27 | Integration | [#147689882](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147689882) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
