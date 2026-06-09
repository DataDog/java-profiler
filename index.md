---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-09 05:53 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#117738576](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117738576) | ❌ | main | - |
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
| 2026-06-09 | Integration | [#117738576](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117738576) | main | - | ❌ |
| 2026-06-09 | Integration | [#117730863](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117730863) | main | - | ❌ |
| 2026-06-09 | Integration | [#117730591](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117730591) | main | - | ❌ |
| 2026-06-08 | Integration | [#117729220](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117729220) | main | - | ❌ |
| 2026-06-08 | Integration | [#117701160](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117701160) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
