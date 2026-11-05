---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 07:14:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 41-64 cores)</summary>

```
1793880483 64
1793880488 64
1793880493 64
1793880498 64
1793880503 64
1793880508 64
1793880513 64
1793880518 64
1793880523 64
1793880528 64
1793880533 61
1793880538 61
1793880543 61
1793880548 61
1793880553 61
1793880558 61
1793880563 61
1793880568 41
1793880573 41
1793880578 41
```
</details>

---

