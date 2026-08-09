---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-09 10:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#129832779](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129832779) | ✅ | main | - |
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
| 2026-08-09 | Integration | [#129832779](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129832779) | main | - | ✅ |
| 2026-08-09 | Integration | [#129823776](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129823776) | main | - | ✅ |
| 2026-08-08 | Integration | [#129791419](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129791419) | main | - | ✅ |
| 2026-08-08 | Integration | [#129781854](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129781854) | main | - | ✅ |
| 2026-08-07 | Integration | [#129748253](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129748253) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
