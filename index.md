---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-21 19:18 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#146512450](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146512450) | ✅ | main | - |
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
| 2026-10-21 | Integration | [#146512450](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146512450) | main | - | ✅ |
| 2026-10-21 | Integration | [#146463644](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146463644) | main | - | ✅ |
| 2026-10-21 | Integration | [#146454076](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146454076) | main | - | ✅ |
| 2026-10-21 | Integration | [#146445389](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146445389) | main | - | ✅ |
| 2026-10-21 | Integration | [#146421032](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146421032) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
