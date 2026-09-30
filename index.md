---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-30 12:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#141237617](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141237617) | ✅ | main | - |
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
| 2026-09-30 | Integration | [#141237617](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141237617) | main | - | ✅ |
| 2026-09-30 | Integration | [#141223947](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141223947) | main | - | ✅ |
| 2026-09-30 | Integration | [#141219807](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141219807) | main | - | ✅ |
| 2026-09-30 | Integration | [#141219725](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141219725) | main | - | ✅ |
| 2026-09-30 | Integration | [#141215359](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141215359) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
