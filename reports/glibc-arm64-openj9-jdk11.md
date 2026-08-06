---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-06 06:20:05 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 11 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1786011324 46
1786011329 46
1786011334 46
1786011339 46
1786011344 46
1786011349 46
1786011354 46
1786011359 46
1786011364 46
1786011369 46
1786011374 46
1786011379 46
1786011384 48
1786011389 48
1786011394 48
1786011399 48
1786011404 48
1786011409 48
1786011414 48
1786011419 48
```
</details>

---

