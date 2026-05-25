---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-25 10:48 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#115000017](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115000017) | ❌ | main | - |
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
| 2026-05-25 | Integration | [#115000017](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115000017) | main | - | ❌ |
| 2026-05-25 | Integration | [#114992653](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114992653) | main | - | ❌ |
| 2026-05-25 | Integration | [#114988778](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114988778) | main | - | ❌ |
| 2026-05-25 | Integration | [#114973374](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114973374) | main | - | ❌ |
| 2026-05-25 | Integration | [#114973333](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114973333) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
