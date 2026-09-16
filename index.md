---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-16 16:12 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#137909237](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/137909237) | ✅ | main | - |
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
| 2026-09-16 | Integration | [#137909237](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/137909237) | main | - | ✅ |
| 2026-09-16 | Integration | [#137909221](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/137909221) | main | - | ⚠️ |
| 2026-09-16 | Integration | [#137811385](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/137811385) | main | - | ✅ |
| 2026-09-14 | Integration | [#137297383](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/137297383) | main | - | ⚠️ |
| 2026-09-05 | Integration | [#135640576](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/135640576) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
