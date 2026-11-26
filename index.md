---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-26 14:25 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#156669652](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156669652) | ✅ | main | - |
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
| 2026-11-26 | Integration | [#156669652](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156669652) | main | - | ✅ |
| 2026-11-26 | Integration | [#156669675](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156669675) | main | - | ✅ |
| 2026-11-26 | Integration | [#156669878](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156669878) | main | - | ❓ |
| 2026-11-26 | Integration | [#156660667](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156660667) | main | - | ✅ |
| 2026-11-26 | Integration | [#156660543](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156660543) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
