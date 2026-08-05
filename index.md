---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-05 16:57 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#129203514](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129203514) | ❓ | main | - |
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
| 2026-08-05 | Integration | [#129203514](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129203514) | main | - | ❓ |
| 2026-08-05 | Integration | [#129194434](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129194434) | main | - | ❓ |
| 2026-08-05 | Integration | [#129190616](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129190616) | main | - | ❓ |
| 2026-08-05 | Integration | [#129180300](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129180300) | main | - | ❓ |
| 2026-08-05 | Integration | [#129175569](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129175569) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
