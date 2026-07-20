---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-20 16:23 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125711587](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125711587) | ❌ | main | - |
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
| 2026-07-20 | Integration | [#125711587](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125711587) | main | - | ❌ |
| 2026-07-20 | Integration | [#125688907](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125688907) | main | - | ❌ |
| 2026-07-20 | Integration | [#125680917](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125680917) | main | - | ❌ |
| 2026-07-20 | Integration | [#125680407](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125680407) | main | - | ❌ |
| 2026-07-20 | Integration | [#125663339](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125663339) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
