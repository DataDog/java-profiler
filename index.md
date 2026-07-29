---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-29 01:15 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#127596245](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127596245) | ❌ | main | - |
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
| 2026-07-29 | Integration | [#127596245](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127596245) | main | - | ❌ |
| 2026-07-29 | Integration | [#127596235](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127596235) | main | - | ❌ |
| 2026-07-28 | Integration | [#127582605](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127582605) | main | - | ❌ |
| 2026-07-28 | Integration | [#127579318](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127579318) | main | - | ❌ |
| 2026-07-28 | Integration | [#127554086](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127554086) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
