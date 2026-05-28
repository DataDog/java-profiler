---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-28 20:03 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#115710884](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115710884) | ❌ | main | - |
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
| 2026-05-28 | Integration | [#115710884](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115710884) | main | - | ❌ |
| 2026-05-28 | Integration | [#115711304](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115711304) | main | - | ❓ |
| 2026-05-28 | Integration | [#115703648](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115703648) | main | - | ❓ |
| 2026-05-28 | Integration | [#115680462](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115680462) | main | - | ❌ |
| 2026-05-28 | Integration | [#115668131](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115668131) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
