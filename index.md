---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-09 13:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#123753828](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123753828) | ❌ | main | - |
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
| 2026-07-09 | Integration | [#123753828](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123753828) | main | - | ❌ |
| 2026-07-09 | Integration | [#123751755](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123751755) | main | - | ❌ |
| 2026-07-09 | Integration | [#123746444](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123746444) | main | - | ❌ |
| 2026-07-09 | Integration | [#123741367](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123741367) | main | - | ❌ |
| 2026-07-09 | Integration | [#123736079](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123736079) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
