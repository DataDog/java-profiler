---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-05 09:48 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#129088107](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129088107) | ❌ | main | - |
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
| 2026-08-05 | Integration | [#129088107](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129088107) | main | - | ❌ |
| 2026-08-05 | Integration | [#129088427](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129088427) | main | - | ❓ |
| 2026-08-05 | Integration | [#129081534](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129081534) | main | - | ❌ |
| 2026-08-05 | Integration | [#129068308](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129068308) | main | - | ❓ |
| 2026-08-05 | Integration | [#129056858](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129056858) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
