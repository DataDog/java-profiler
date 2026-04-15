---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-15 17:31 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#107867882](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107867882) | ✅ | main | - |
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
| 2026-04-15 | Integration | [#107867882](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107867882) | main | - | ✅ |
| 2026-04-15 | Integration | [#107867397](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107867397) | main | - | ✅ |
| 2026-04-15 | Integration | [#107867301](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107867301) | main | - | ❓ |
| 2026-04-15 | Integration | [#107863460](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107863460) | main | - | ⚠️ |
| 2026-04-15 | Integration | [#107861801](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/107861801) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
