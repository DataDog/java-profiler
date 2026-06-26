---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-26 12:02 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#121256816](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121256816) | ❌ | main | - |
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
| 2026-06-26 | Integration | [#121256816](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121256816) | main | - | ❌ |
| 2026-06-26 | Integration | [#121234479](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121234479) | main | - | ❌ |
| 2026-06-26 | Integration | [#121203643](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121203643) | main | - | ❌ |
| 2026-06-25 | Integration | [#121124432](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121124432) | main | - | ❌ |
| 2026-06-25 | Integration | [#121098708](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121098708) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
