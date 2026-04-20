---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-19 21:17:21 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 369 |
| Sample Rate | 6.15/sec |
| Health Score | 384% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 10-32 cores)</summary>

```
1776647582 12
1776647587 12
1776647592 12
1776647597 10
1776647602 10
1776647607 10
1776647612 10
1776647617 10
1776647622 10
1776647627 17
1776647632 17
1776647637 17
1776647642 17
1776647647 17
1776647652 17
1776647657 17
1776647662 17
1776647667 17
1776647672 17
1776647677 17
```
</details>

---

