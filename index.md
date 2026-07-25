---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-25 21:40 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#126983460](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126983460) | ❌ | main | - |
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
| 2026-07-25 | Integration | [#126983460](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126983460) | main | - | ❌ |
| 2026-07-25 | Integration | [#126983111](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126983111) | main | - | ❌ |
| 2026-07-25 | Integration | [#126956249](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126956249) | main | - | ❌ |
| 2026-07-25 | Integration | [#126945142](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126945142) | main | - | ❌ |
| 2026-07-25 | Integration | [#126938017](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126938017) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
