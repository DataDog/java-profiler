---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-29 12:24 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#140884517](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140884517) | ✅ | main | - |
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
| 2026-09-29 | Integration | [#140884517](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140884517) | main | - | ✅ |
| 2026-09-29 | Integration | [#140874515](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140874515) | main | - | ✅ |
| 2026-09-29 | Integration | [#140865235](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140865235) | main | - | ✅ |
| 2026-09-29 | Integration | [#140864263](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140864263) | main | - | ✅ |
| 2026-09-29 | Integration | [#140856590](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140856590) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
