---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-28 09:23 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#127368844](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127368844) | ❓ | main | - |
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
| 2026-07-28 | Integration | [#127368844](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127368844) | main | - | ❓ |
| 2026-07-28 | Integration | [#127364329](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127364329) | main | - | ❌ |
| 2026-07-28 | Integration | [#127365929](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127365929) | main | - | ❓ |
| 2026-07-28 | Integration | [#127337115](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127337115) | main | - | ❌ |
| 2026-07-27 | Integration | [#127261539](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/127261539) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
