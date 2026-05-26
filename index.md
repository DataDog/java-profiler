---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-26 09:41 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#115088006](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115088006) | ❌ | main | - |
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
| 2026-05-26 | Integration | [#115088006](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115088006) | main | - | ❌ |
| 2026-05-26 | Integration | [#115086813](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115086813) | main | - | ❌ |
| 2026-05-26 | Integration | [#115086639](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115086639) | main | - | ❌ |
| 2026-05-26 | Integration | [#115075079](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115075079) | main | - | ❌ |
| 2026-05-25 | Integration | [#115058004](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115058004) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
