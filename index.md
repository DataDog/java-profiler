---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-15 19:05 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#107882221](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107882221) | ❓ | main | - |
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
| 2026-04-15 | Integration | [#107882221](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107882221) | main | - | ❓ |
| 2026-04-15 | Integration | [#107880045](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107880045) | main | - | ✅ |
| 2026-04-15 | Integration | [#107875673](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107875673) | main | - | ✅ |
| 2026-04-15 | Integration | [#107877018](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107877018) | main | - | ❓ |
| 2026-04-15 | Integration | [#107867882](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107867882) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
