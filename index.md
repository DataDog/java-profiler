---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-27 15:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#156806976](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156806976) | ⚠️ | main | - |
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
| 2026-11-27 | Integration | [#156806976](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156806976) | main | - | ⚠️ |
| 2026-11-27 | Integration | [#156803434](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156803434) | main | - | ✅ |
| 2026-11-27 | Integration | [#156804562](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156804562) | main | - | ✅ |
| 2026-11-27 | Integration | [#156802570](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156802570) | main | - | ✅ |
| 2026-11-27 | Integration | [#156783546](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156783546) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
