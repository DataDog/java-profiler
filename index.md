---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-16 13:43 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#125003307](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125003307) | ❌ | main | - |
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
| 2026-07-16 | Integration | [#125003307](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125003307) | main | - | ❌ |
| 2026-07-16 | Integration | [#125000076](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/125000076) | main | - | ❓ |
| 2026-07-16 | Integration | [#124994544](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124994544) | main | - | ❌ |
| 2026-07-16 | Integration | [#124992775](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124992775) | main | - | ❌ |
| 2026-07-16 | Integration | [#124992958](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124992958) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
