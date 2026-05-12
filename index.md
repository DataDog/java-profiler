---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-12 12:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112683524](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112683524) | ⚠️ | main | - |
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
| 2026-05-12 | Integration | [#112683524](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112683524) | main | - | ⚠️ |
| 2026-05-12 | Integration | [#112680037](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112680037) | main | - | ❌ |
| 2026-05-12 | Integration | [#112674210](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112674210) | main | - | ❌ |
| 2026-05-12 | Integration | [#112670850](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112670850) | main | - | ⚠️ |
| 2026-05-12 | Integration | [#112669656](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112669656) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
