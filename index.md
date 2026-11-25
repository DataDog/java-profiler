---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-25 15:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#156529831](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156529831) | ✅ | main | - |
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
| 2026-11-25 | Integration | [#156529831](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156529831) | main | - | ✅ |
| 2026-11-25 | Integration | [#156526384](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156526384) | main | - | ✅ |
| 2026-11-25 | Integration | [#156523739](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156523739) | main | - | ✅ |
| 2026-11-25 | Integration | [#156516822](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156516822) | main | - | ✅ |
| 2026-11-25 | Integration | [#156516799](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156516799) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
