---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-03 10:02 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128531428](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128531428) | ❓ | main | - |
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
| 2026-08-03 | Integration | [#128531428](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128531428) | main | - | ❓ |
| 2026-08-03 | Integration | [#128530716](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128530716) | main | - | ❓ |
| 2026-08-03 | Integration | [#128529014](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128529014) | main | - | ❓ |
| 2026-08-03 | Integration | [#128528356](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128528356) | main | - | ❓ |
| 2026-08-03 | Integration | [#128525566](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128525566) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
