---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-10 16:54 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124054078](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124054078) | ❌ | main | - |
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
| 2026-07-10 | Integration | [#124054078](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124054078) | main | - | ❌ |
| 2026-07-10 | Integration | [#124025390](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124025390) | main | - | ❌ |
| 2026-07-10 | Integration | [#124024161](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124024161) | main | - | ❌ |
| 2026-07-10 | Integration | [#123998232](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123998232) | main | - | ❌ |
| 2026-07-10 | Integration | [#123958428](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123958428) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
