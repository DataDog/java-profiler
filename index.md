---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-28 09:45 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#121477106](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121477106) | ❌ | main | - |
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
| 2026-06-28 | Integration | [#121477106](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121477106) | main | - | ❌ |
| 2026-06-28 | Integration | [#121467588](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121467588) | main | - | ❌ |
| 2026-06-27 | Integration | [#121446697](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121446697) | main | - | ❌ |
| 2026-06-27 | Integration | [#121438399](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121438399) | main | - | ❓ |
| 2026-06-27 | Integration | [#121431787](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121431787) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
