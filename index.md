---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-03-06 11:14 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#100859742](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100859742) | ✅ | main | - |
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
| 2026-03-06 | Integration | [#100859742](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100859742) | main | - | ✅ |
| 2026-03-06 | Integration | [#100859404](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100859404) | main | - | ✅ |
| 2026-03-06 | Integration | [#100854218](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100854218) | main | - | ✅ |
| 2026-03-06 | Integration | [#100839688](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100839688) | dependabot/github_actions/actions/upload-artifact-7 | [#403](https://github.com/DataDog/java-profiler/pull/403) | ✅ |
| 2026-03-06 | Integration | [#100839156](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/100839156) | jb/native_allocs | [#398](https://github.com/DataDog/java-profiler/pull/398) | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
