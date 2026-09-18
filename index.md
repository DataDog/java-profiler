---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-18 11:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#138438828](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138438828) | ✅ | main | - |
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
| 2026-09-18 | Integration | [#138438828](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138438828) | main | - | ✅ |
| 2026-09-18 | Integration | [#138438818](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138438818) | main | - | ✅ |
| 2026-09-18 | Integration | [#138438817](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138438817) | main | - | ✅ |
| 2026-09-18 | Integration | [#138438806](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138438806) | main | - | ⚠️ |
| 2026-09-18 | Integration | [#138438605](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138438605) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
