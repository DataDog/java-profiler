---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-30 09:44 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#121801631](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121801631) | ❌ | main | - |
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
| 2026-06-30 | Integration | [#121801631](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121801631) | main | - | ❌ |
| 2026-06-30 | Integration | [#121800098](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121800098) | main | - | ❌ |
| 2026-06-30 | Integration | [#121788633](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121788633) | main | - | ❌ |
| 2026-06-30 | Integration | [#121782804](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121782804) | main | - | ❌ |
| 2026-06-30 | Integration | [#121767581](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121767581) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
