---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-04 19:11 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#150294444](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150294444) | ✅ | main | - |
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
| 2026-11-04 | Integration | [#150294444](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150294444) | main | - | ✅ |
| 2026-11-04 | Integration | [#150275782](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150275782) | main | - | ✅ |
| 2026-11-04 | Integration | [#150247309](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150247309) | main | - | ✅ |
| 2026-11-04 | Integration | [#150230525](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150230525) | main | - | ❓ |
| 2026-11-04 | Integration | [#150221871](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150221871) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
