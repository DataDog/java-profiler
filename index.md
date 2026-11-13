---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-13 15:54 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#153031977](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153031977) | ✅ | main | - |
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
| 2026-11-13 | Integration | [#153031977](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153031977) | main | - | ✅ |
| 2026-11-13 | Integration | [#153030061](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153030061) | main | - | ✅ |
| 2026-11-13 | Integration | [#153021473](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153021473) | main | - | ✅ |
| 2026-11-13 | Integration | [#153018367](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153018367) | main | - | ⚠️ |
| 2026-11-13 | Integration | [#153017560](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153017560) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
