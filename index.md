---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-24 13:09 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#156103196](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156103196) | ✅ | main | - |
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
| 2026-11-24 | Integration | [#156103196](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156103196) | main | - | ✅ |
| 2026-11-24 | Integration | [#156098546](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156098546) | main | - | ✅ |
| 2026-11-24 | Integration | [#156084688](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156084688) | main | - | ✅ |
| 2026-11-24 | Integration | [#156086761](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156086761) | main | - | ❓ |
| 2026-11-24 | Integration | [#156076813](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156076813) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
