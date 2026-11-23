---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 09:03:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 42-48 cores)</summary>

```
1795442312 42
1795442317 42
1795442322 42
1795442327 42
1795442332 42
1795442337 42
1795442342 42
1795442347 42
1795442352 42
1795442357 42
1795442362 42
1795442367 42
1795442372 42
1795442377 42
1795442382 48
1795442387 48
1795442392 48
1795442397 48
1795442402 48
1795442407 48
```
</details>

---

