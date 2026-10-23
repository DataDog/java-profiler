---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-23 14:30 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#147074380](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147074380) | ✅ | main | - |
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
| 2026-10-23 | Integration | [#147074380](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147074380) | main | - | ✅ |
| 2026-10-23 | Integration | [#147063358](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147063358) | main | - | ⚠️ |
| 2026-10-23 | Integration | [#147056203](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147056203) | main | - | ✅ |
| 2026-10-23 | Integration | [#147050857](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147050857) | main | - | ✅ |
| 2026-10-23 | Integration | [#147050690](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/147050690) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
