---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-31 18:39 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#128318578](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128318578) | ❓ | main | - |
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
| 2026-07-31 | Integration | [#128318578](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128318578) | main | - | ❓ |
| 2026-07-31 | Integration | [#128307526](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128307526) | main | - | ❓ |
| 2026-07-31 | Integration | [#128307357](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128307357) | main | - | ❓ |
| 2026-07-31 | Integration | [#128285500](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128285500) | main | - | ❓ |
| 2026-07-31 | Integration | [#128281352](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/128281352) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
