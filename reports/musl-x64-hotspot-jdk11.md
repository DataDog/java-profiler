---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 06:20:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (5 unique values: 85-92 cores)</summary>

```
1786011313 89
1786011318 89
1786011323 89
1786011328 89
1786011333 89
1786011338 87
1786011343 87
1786011348 85
1786011354 85
1786011359 85
1786011364 85
1786011369 85
1786011374 90
1786011379 90
1786011384 90
1786011389 90
1786011394 90
1786011399 90
1786011404 92
1786011409 92
```
</details>

---

