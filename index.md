---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-14 21:08 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124633408](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124633408) | ❌ | main | - |
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
| 2026-07-14 | Integration | [#124633408](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124633408) | main | - | ❌ |
| 2026-07-14 | Integration | [#124625059](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124625059) | main | - | ❌ |
| 2026-07-14 | Integration | [#124618290](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124618290) | main | - | ❌ |
| 2026-07-14 | Integration | [#124597089](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124597089) | main | - | ❌ |
| 2026-07-14 | Integration | [#124590044](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124590044) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
