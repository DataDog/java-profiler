---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-10 10:02 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#123958428](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123958428) | ❌ | main | - |
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
| 2026-07-10 | Integration | [#123958428](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123958428) | main | - | ❌ |
| 2026-07-10 | Integration | [#123957681](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123957681) | main | - | ❌ |
| 2026-07-10 | Integration | [#123937946](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123937946) | main | - | ❌ |
| 2026-07-10 | Integration | [#123926179](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123926179) | main | - | ❌ |
| 2026-07-09 | Integration | [#123883305](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123883305) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
