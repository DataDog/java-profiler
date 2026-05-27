---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-27 08:34 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#115328894](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115328894) | ❌ | main | - |
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
| 2026-05-27 | Integration | [#115328894](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115328894) | main | - | ❌ |
| 2026-05-27 | Integration | [#115314963](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115314963) | main | - | ❌ |
| 2026-05-26 | Integration | [#115300623](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115300623) | main | - | ❌ |
| 2026-05-26 | Integration | [#115299415](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115299415) | main | - | ❓ |
| 2026-05-26 | Integration | [#115286726](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115286726) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
