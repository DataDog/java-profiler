---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-12 17:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#118508341](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118508341) | ❓ | main | - |
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
| 2026-06-12 | Integration | [#118508341](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118508341) | main | - | ❓ |
| 2026-06-12 | Integration | [#118507723](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118507723) | main | - | ❌ |
| 2026-06-12 | Integration | [#118471249](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118471249) | main | - | ❌ |
| 2026-06-12 | Integration | [#118468305](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118468305) | main | - | ❌ |
| 2026-06-12 | Integration | [#118463955](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/118463955) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
