---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-10 19:41 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#152000470](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152000470) | ❓ | main | - |
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
| 2026-11-10 | Integration | [#152000470](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152000470) | main | - | ❓ |
| 2026-11-10 | Integration | [#151982233](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151982233) | main | - | ✅ |
| 2026-11-10 | Integration | [#151962369](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151962369) | main | - | ✅ |
| 2026-11-10 | Integration | [#151962327](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151962327) | main | - | ✅ |
| 2026-11-10 | Integration | [#151948026](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151948026) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
