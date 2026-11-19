---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-19 17:14 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#154831558](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154831558) | ⚠️ | main | - |
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
| 2026-11-19 | Integration | [#154831558](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154831558) | main | - | ⚠️ |
| 2026-11-19 | Integration | [#154830361](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154830361) | main | - | ✅ |
| 2026-11-19 | Integration | [#154823444](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154823444) | main | - | ✅ |
| 2026-11-19 | Integration | [#154808794](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154808794) | main | - | ✅ |
| 2026-11-19 | Integration | [#154772007](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/154772007) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
