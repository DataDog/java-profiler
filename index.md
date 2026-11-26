---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-26 16:54 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#156696392](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156696392) | ✅ | main | - |
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
| 2026-11-26 | Integration | [#156696392](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156696392) | main | - | ✅ |
| 2026-11-26 | Integration | [#156686275](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156686275) | main | - | ✅ |
| 2026-11-26 | Integration | [#156681273](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156681273) | main | - | ✅ |
| 2026-11-26 | Integration | [#156678451](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156678451) | main | - | ✅ |
| 2026-11-26 | Integration | [#156678452](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156678452) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
