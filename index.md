---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-07 17:01 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#123320051](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123320051) | ❌ | main | - |
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
| 2026-07-07 | Integration | [#123320051](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123320051) | main | - | ❌ |
| 2026-07-07 | Integration | [#123300793](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123300793) | main | - | ❌ |
| 2026-07-07 | Integration | [#123297145](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123297145) | main | - | ❌ |
| 2026-07-07 | Integration | [#123297355](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123297355) | main | - | ❌ |
| 2026-07-07 | Integration | [#123245767](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/123245767) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
