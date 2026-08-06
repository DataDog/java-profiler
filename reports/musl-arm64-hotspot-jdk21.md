---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-06 06:20:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 9 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 33-38 cores)</summary>

```
1786011344 35
1786011349 35
1786011354 35
1786011359 35
1786011364 33
1786011369 33
1786011374 33
1786011379 33
1786011384 33
1786011389 33
1786011394 33
1786011399 33
1786011404 33
1786011409 33
1786011414 38
1786011419 38
1786011424 38
1786011429 38
1786011434 38
1786011439 33
```
</details>

---

