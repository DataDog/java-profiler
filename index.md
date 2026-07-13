---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-13 16:32 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124353765](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124353765) | ❌ | main | - |
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
| 2026-07-13 | Integration | [#124353765](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124353765) | main | - | ❌ |
| 2026-07-13 | Integration | [#124348005](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124348005) | main | - | ❌ |
| 2026-07-13 | Integration | [#124343591](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124343591) | main | - | ❌ |
| 2026-07-13 | Integration | [#124331099](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124331099) | main | - | ❌ |
| 2026-07-13 | Integration | [#124308934](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124308934) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
