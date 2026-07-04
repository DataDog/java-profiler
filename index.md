---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-04 04:57 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#122675380](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122675380) | ❌ | main | - |
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
| 2026-07-04 | Integration | [#122675380](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122675380) | main | - | ❌ |
| 2026-07-03 | Integration | [#122649819](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122649819) | main | - | ❌ |
| 2026-07-03 | Integration | [#122648867](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122648867) | main | - | ❓ |
| 2026-07-03 | Integration | [#122632111](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122632111) | main | - | ❌ |
| 2026-07-03 | Integration | [#122605974](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122605974) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
