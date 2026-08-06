---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-06 06:20:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1786011309 35
1786011314 35
1786011319 35
1786011324 35
1786011329 35
1786011334 35
1786011339 35
1786011344 35
1786011349 35
1786011354 35
1786011359 35
1786011364 35
1786011369 35
1786011374 35
1786011379 35
1786011384 35
1786011389 35
1786011394 35
1786011399 40
1786011404 40
```
</details>

---

