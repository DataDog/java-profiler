---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-13 15:33 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124331099](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124331099) | ❌ | main | - |
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
| 2026-07-13 | Integration | [#124331099](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124331099) | main | - | ❌ |
| 2026-07-13 | Integration | [#124308934](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124308934) | main | - | ❌ |
| 2026-07-13 | Integration | [#124306363](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124306363) | main | - | ❌ |
| 2026-07-13 | Integration | [#124302454](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124302454) | main | - | ❌ |
| 2026-07-13 | Integration | [#124299819](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124299819) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
