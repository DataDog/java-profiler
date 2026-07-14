---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-14 14:23 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124534799](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124534799) | ❓ | main | - |
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
| 2026-07-14 | Integration | [#124534799](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124534799) | main | - | ❓ |
| 2026-07-14 | Integration | [#124525231](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124525231) | main | - | ❌ |
| 2026-07-14 | Integration | [#124513188](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124513188) | main | - | ❌ |
| 2026-07-14 | Integration | [#124513643](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124513643) | main | - | ❌ |
| 2026-07-14 | Integration | [#124510286](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124510286) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
