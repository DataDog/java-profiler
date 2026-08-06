---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-06 06:20:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 12 |
| Allocations | 129 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 10 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1786011339 52
1786011344 52
1786011349 52
1786011354 52
1786011359 47
1786011364 47
1786011369 47
1786011374 47
1786011379 47
1786011384 47
1786011389 47
1786011394 47
1786011399 47
1786011404 47
1786011409 47
1786011414 47
1786011419 47
1786011424 47
1786011429 47
1786011434 47
```
</details>

---

