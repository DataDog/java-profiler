---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-22 13:43:33 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 12 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (3 unique values: 87-90 cores)</summary>

```
1776879503 88
1776879508 88
1776879513 90
1776879518 90
1776879523 90
1776879528 87
1776879533 87
1776879538 87
1776879543 87
1776879548 87
1776879553 87
1776879558 87
1776879563 87
1776879568 87
1776879573 87
1776879578 87
1776879583 87
1776879588 87
1776879593 87
1776879598 87
```
</details>

---

