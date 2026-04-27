---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-27 14:56 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#109921192](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109921192) | ❓ | main | - |
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
| 2026-04-27 | Integration | [#109921192](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109921192) | main | - | ❓ |
| 2026-04-27 | Integration | [#109828551](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109828551) | main | - | ✅ |
| 2026-04-27 | Integration | [#109819115](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109819115) | main | - | ✅ |
| 2026-04-27 | Integration | [#109814010](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109814010) | main | - | ✅ |
| 2026-04-27 | Integration | [#109798162](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/109798162) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
